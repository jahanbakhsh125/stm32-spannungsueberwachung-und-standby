#pragma once
#include <X_general.h>



typedef union{
	uint8_t u8[4];
	uint32_t u32;
	uint16_t u16[2];
}RTC_CNT_typedef;

typedef struct{
	uint8_t H;
	uint8_t M;
	uint8_t S;
}X_time_t;


typedef struct{
	uint8_t day;
	uint8_t month;
	uint16_t year;
}mydate_typedef;

#define __DAY BKP->DR1
#define __MONTH BKP->DR2
#define __YEAR BKP->DR3

X_StatusTypeDef RTC_Init(void);
void RTC_GetTime(X_time_t * time);
X_StatusTypeDef labview_time(void);
X_StatusTypeDef RTC_Init2(void);
void RTC_Alarm_init(void);


