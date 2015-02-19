/*
Author: hackerdino
Date  : Feb 2015
*/

#include <stdint.h>
#include <stdbool.h>
#include "GPIO.h"

int _pwm(uint32_t dutyC);
void wait(unsigned long delay);

int main(void)
{
	int i=0;

	/*Pin Configuration*/
	P1_3_set_mode(OUTPUT_OD_AF3);
	P1_3_set_driver_strength(STRONG);
	P1_3_reset();

	/*Reset Timer*/
	SCU_RESET->PRSET0 |= 0x1C;
	CCU40_CC40->TCCLR |= 0x03;

	/*PWM CCU4 Configuration*/
	SCU_RESET->PRCLR0|= (1<<SCU_RESET_PRCLR0_CCU40RS_Pos);	//De assert Reset

	SCU_CLK->CLKSET= (1<<SCU_CLK_CLKSET_CCUCEN_Pos);        //CCU clk enable
	CCU40->GIDLC|=(1<<CCU4_GIDLC_SPRB_Pos);                 //Prescaller Run Bit set
	CCU40_CC40->PSC=0x1;                                    //Prescaller select->0
	CCU40_CC40->TC|= (1<<CCU4_CC4_TC_CLST_Pos);             //Enable Shadow Transfer on Timer clear

	CCU40->GIDLC|= (1<<CCU4_GIDLC_CS0I_Pos);                //CC40 Idle clear
	SCU_GENERAL->CCUCON|=(1<<SCU_GENERAL_CCUCON_GSC40_Pos); //CCU40_CC40 global enable
	CCU40_CC40->TCSET=1;                                    //Timer Run Bit set
	CCU40_CC40->PRS=0xFFFF;                                 //Period set
	CCU40_CC40->CRS=0x8000;                                 //duty cycle set
	CCU40->GCSS|= (1<<CCU4_GCSS_S0SE_Pos);                  //Shadow transfer request

	CCU40_CC40->TCSET |= 0x1;                               //start timer

	while(1)
	{
	if(i==100)
		i=0;
	_pwm(i++);
	wait(10000);
	}
}


int _pwm(uint32_t dutyC){

	if(dutyC<0 && dutyC>100)
		return 1;

	double dc;
	int		idc;
	dc=dutyC*0.01;
	dc=0xFFFF*dc;
	idc=(int)dc;

	CCU40_CC40->CRS=dc;  //duty cycle set
	CCU40->GCSS|= (1<<CCU4_GCSS_S0SE_Pos); //Shadow transfer request

	return 0;
}

void wait(unsigned long delay) {
	while (delay--) {
		__NOP();
	}
}

/** EOF */

