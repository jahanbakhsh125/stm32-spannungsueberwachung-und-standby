#include "rtc.h"
#include "string.h"
#include "stdio.h"

uint32_t mysec;
char mybuf[50];
X_time_t mytime2;
RTC_CNT_typedef RTC_CNT_Base;

#define __RTC_BASE 0xFFFEAE80U

static inline X_StatusTypeDef Wait_RTOFF(void);
static inline X_StatusTypeDef RTC_EnterConfig(void);
static inline X_StatusTypeDef RTC_ExitConfig(void);
static inline X_StatusTypeDef RTC_WaitRSF(void);




RTC_CNT_typedef my_RTC_CNT;


static uint8_t RTC_IsLeapYear(uint16_t nYear)
{
  if ((nYear % 4U) != 0U)
  {
    return 0U;
  }

  if ((nYear % 100U) != 0U)
  {
    return 1U;
  }

  if ((nYear % 400U) == 0U)
  {
    return 1U;
  }
  else
  {
    return 0U;
  }
}


void ow_callback(void){


	RTC_EnterConfig();

	RTC->CNTH = RTC_CNT_Base.u16[1];
	RTC->CNTL = RTC_CNT_Base.u16[0];

	RTC_ExitConfig();


	 uint32_t year = 0U, month = 0U, day = 0U;


	  /* Get the current year*/
	  year = __YEAR;

	  /* Get the current month and day */
	  month = __MONTH;
	  day = __DAY;

	    if ((month == 1U) || (month == 3U) || (month == 5U) || (month == 7U) || \
	        (month == 8U) || (month == 10U) || (month == 12U)){
	      if (day < 31U){day++;}
	      /* Date structure member: day = 31 */
	      else
	      {
	        if (month != 12U)
	        {
	          month++;
	          day = 1U;
	        }
	        /* Date structure member: day = 31 & month =12 */
	        else
	        {
	          month = 1U;
	          day = 1U;
	          year++;
	        }
	      }
	    }
	    else if ((month == 4U) || (month == 6U) || (month == 9U) || (month == 11U))
	    {
	      if (day < 30U)
	      {
	        day++;
	      }
	      /* Date structure member: day = 30 */
	      else
	      {
	        month++;
	        day = 1U;
	      }
	    }
	    else if (month == 2U)
	    {
	      if (day < 28U)
	      {
	        day++;
	      }
	      else if (day == 28U)
	      {
	        /* Leap year */
	        if (RTC_IsLeapYear(year))
	        {
	          day++;
	        }
	        else
	        {
	          month++;
	          day = 1U;
	        }
	      }
	      else if (day == 29U)
	      {
	        month++;
	        day = 1U;
	      }
	    }


	  /* Update year */
	  __YEAR = year;

	  /* Update day and month */
	  __MONTH = month;
	  __DAY = day;




}






void RTC_GetTime(X_time_t * time){

	RTC_CNT_typedef cnt;

	cnt.u16[1] = RTC->CNTH;
	cnt.u16[0] = RTC->CNTL;

	if(cnt.u16[1] != RTC->CNTH){
		cnt.u16[1] = RTC->CNTH;
		cnt.u16[0] = RTC->CNTL;
	}


	cnt.u32-=__RTC_BASE;
	time->H  = cnt.u32 / 3600U;
	time->M = (cnt.u32 % 3600U) / 60U;
	time->S = (cnt.u32 % 3600U) % 60U;



}



static inline X_StatusTypeDef Wait_RTOFF(void){
	uint32_t timeout=100;
	uint32_t tickstart=uwTick;
	while(!(RTC->CRL & RTC_CRL_RTOFF)){
		if(uwTick-tickstart>timeout){
			return X_TIMEOUT;
		}
	}
	return X_OK;
}


static inline X_StatusTypeDef RTC_EnterConfig(void){

	X_StatusTypeDef status;
	status = Wait_RTOFF();
	if(status != X_OK){
		return status;
	}

	RTC->CRL |= RTC_CRL_CNF;
	return X_OK;

}

static inline X_StatusTypeDef RTC_ExitConfig(void){

	X_StatusTypeDef status;
	status = Wait_RTOFF();
	if(status != X_OK){
		return status;
	}

	RTC->CRL &= ~RTC_CRL_CNF;

	status = Wait_RTOFF();
	if(status != X_OK){
		return status;
	}

	return X_OK;

}


static inline X_StatusTypeDef RTC_WaitRSF(void){

	X_StatusTypeDef status;
	status = Wait_RTOFF();
	if(status != X_OK){
		return status;
	}

	RTC->CRL = ~RTC_CRL_RSF;

	uint32_t timeout=100;
	uint32_t tickstart=uwTick;
	while(!(RTC->CRL & RTC_CRL_RSF)){
		if(uwTick-tickstart>timeout){
			return X_TIMEOUT;
		}
	}

	return X_OK;
}

X_StatusTypeDef RTC_Init(void){

	X_StatusTypeDef status;

	RCC->BDCR |= RCC_BDCR_LSEON;

	while(!(RCC->BDCR & RCC_BDCR_LSERDY)){}

	RCC->BDCR &= ~RCC_BDCR_RTCSEL;
	RCC->BDCR |= RCC_BDCR_RTCSEL_0;

	RCC->BDCR |= RCC_BDCR_RTCEN;

	status = RTC_WaitRSF();
	if(status != X_OK){
		return status;}

	status = RTC_EnterConfig();
	if(status != X_OK){
		return status;}

	RTC->PRLH = 0;
	RTC->PRLL = 0x7FFF;

	status = RTC_ExitConfig();
	if(status != X_OK){
		return status;}


	return X_OK;

}

X_StatusTypeDef RTC_Init2(void){

	X_StatusTypeDef status;

	RTC_CNT_Base.u32 = __RTC_BASE;


	//enale sec interrupt

	status = Wait_RTOFF();
	if(status != X_OK){
		return status;}

	RTC->CRH |= ( RTC_CRH_OWIE);

	status = Wait_RTOFF();
	if(status != X_OK){
		return status;}

	RTC->CRL = ~(RTC_CRL_SECF|RTC_CRL_OWF);

	X_CallBack_RTC.OW = ow_callback;

	//sec interrupt enable in nvic
	uint32_t PG=NVIC_GetPriorityGrouping();
	NVIC_SetPriority(RTC_IRQn,NVIC_EncodePriority(PG, 5, 0));
	NVIC_EnableIRQ(RTC_IRQn);


	return X_OK;

}


//////////alarm
RTC_CNT_typedef mycntinalarm;
uint32_t RTC_ALR[3];
void (*alarm_callback_case[3])(void);

typedef struct{
	uint8_t H;
	uint8_t M;
}RTC_ALARM_TYPE;

RTC_ALARM_TYPE myAlarms[3];


uint8_t alarm_manager(void){

	uint8_t alarm_case=0;
	RTC_CNT_typedef cnt;

	cnt.u16[1]= RTC->CNTH;
	cnt.u16[0]= RTC->CNTL;

	if( (RTC_ALR[0] <= cnt.u32) && ( cnt.u32 < RTC_ALR[1])){
		cnt.u32 = RTC_ALR[1];
		alarm_case=0;
	}else if( (RTC_ALR[1] <= cnt.u32 ) && (cnt.u32 < RTC_ALR[2])){
		cnt.u32 = RTC_ALR[2];
		alarm_case = 1;
	}else if( RTC_ALR[2] <= cnt.u32){
		cnt.u32=RTC_ALR[0];
		alarm_case=2;
	}

	RTC_EnterConfig();
	RTC->ALRH = cnt.u16[1];
	RTC->ALRL = cnt.u16[0];
	RTC_ExitConfig();

	return alarm_case;


}



void alarm_callback(void){


}




void RTC_Alarm_init(void){

	RTC_CNT_typedef cnt;

	cnt.u16[1]= RTC->CNTH;
	cnt.u16[0]= RTC->CNTL;

	cnt.u32 +=10;

	RTC_EnterConfig();
	RTC->ALRH = cnt.u16[1];
	RTC->ALRL = cnt.u16[0];
	RTC_ExitConfig();

	/*

	EXTI->FTSR|= EXTI_FTSR_FT17;
	EXTI->PR = EXTI_PR_PR17;
	EXTI->IMR |= EXTI_IMR_MR17;

	X_CallBack_ALARM = alarm_callback;

	uint32_t PG= NVIC_GetPriorityGrouping();
	NVIC_SetPriority(RTC_Alarm_IRQn, NVIC_EncodePriority(PG, 4, 0));
	NVIC_EnableIRQ(RTC_Alarm_IRQn);

*/



}





















