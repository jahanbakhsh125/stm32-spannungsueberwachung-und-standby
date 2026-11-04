# Hardware-Grundlage

| Anwendung / Signal | Zuordnung im Code |
|---|---|
| Zielcontroller | STM32F103C8Tx |
| PVD | Interne Versorgungsspannungsüberwachung, EXTI16 |
| PVD-Anzeigen | PB13 und PC13; unterschiedliche aktive Pegel im Code |
| Standby-Status | PC13 |
| RTC-Neuinitialisierung | PB2 beim Start |
| Standby-Motorsignale | PB4 / PB5 im Timer-/Motormodul |
| Wakeup | WKUP-Funktion per EWUP aktiviert; Pinbelegung am Board prüfen |

Taktfunktionen verwenden HSE/PLL; RTC-Code verwendet eine LSE-Konfiguration.
Quarze, tatsächlicher Boardtakt und Zustand der Backup-Domäne sind zu dokumentieren.
Der Motor benötigt einen geeigneten externen Treiber und eine passende Versorgung.

Für vergleichbare Verbrauchsmessungen den Messpunkt festlegen und angeschlossene
LEDs, Debugger, USB-Versorgung sowie die getrennte Motorversorgung berücksichtigen.
