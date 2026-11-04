#!/usr/bin/env python3
"""Build der enthaltenen STM32-Beispiele mit einer lokalen Arm-GCC-Toolchain."""
from pathlib import Path
import argparse
import json
import os
import shutil
import subprocess

ROOT = Path(__file__).resolve().parents[1]

def main():
    projects = json.loads((ROOT / "tools/projects.json").read_text(encoding="utf-8"))
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--project", choices=list(projects), default=next(iter(projects)))
    parser.add_argument("--profile", choices=["Debug", "Release"], default="Debug")
    args = parser.parse_args()
    config = projects[args.project]
    gcc = os.environ.get("ARM_GCC") or shutil.which("arm-none-eabi-gcc")
    if not gcc:
        parser.error("Arm-GCC installieren oder ARM_GCC auf die Compilerdatei setzen.")
    base = ROOT / "firmware" / args.project
    build = ROOT / "build" / args.project / args.profile
    temp = build / "tmp"
    temp.mkdir(parents=True, exist_ok=True)
    env = os.environ.copy()
    env.update(TMP=str(temp), TEMP=str(temp), TMPDIR=str(temp))
    flags = ["-mcpu=cortex-m3", "-mthumb", "-std=gnu11", "-Og" if args.profile == "Debug" else "-Os", "-g0", "-ffunction-sections", "-fdata-sections", "-Wall", "-Wextra", "-DSTM32F103xB"]
    if config["hal"]:
        flags.append("-DUSE_HAL_DRIVER")
    if args.profile == "Debug":
        flags.append("-DDEBUG")
    flags.extend("-I" + str(base / folder) for folder in config["includes"])
    objects = []
    sources = sorted(p for p in base.rglob("*") if p.suffix in {".c", ".s"})
    for index, source in enumerate(sources):
        obj = build / (str(index) + ".o")
        subprocess.run([gcc, *flags, "-c", str(source), "-o", str(obj)], check=True, env=env, timeout=120)
        objects.append(str(obj))
    subprocess.run([gcc, "-mcpu=cortex-m3", "-mthumb", *objects,
                    "-T" + str(base / "STM32F103C8TX_FLASH.ld"),
                    "--specs=nano.specs", "--specs=nosys.specs", "-Wl,--gc-sections", "-static",
                    "-Wl,--start-group", "-lc", "-lm", "-Wl,--end-group",
                    "-o", str(build / "firmware.elf")], check=True, env=env, timeout=120)
    print(f"Erfolgreich: {args.project}, {args.profile}, {len(sources)} Quelldateien")

if __name__ == "__main__":
    main()
