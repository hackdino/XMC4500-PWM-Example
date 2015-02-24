/*
Author: hackerdino
Date  : Feb 2015
*/

#include <stdint.h>
#include <stdbool.h>
#include "GPIO.h"

/*Funktion prototype*/
int _pwm(uint32_t dutyC);

/**
 * @brief Simple PWM Program
 */
int main(void)
{
	/*Variables*/
	int i=0;

	/*Pin Configuration*/
	P1_3_set_mode(OUTPUT_OD_AF3);
	P1_3_set_driver_strength(STRONG);
	P1_3_reset();

	/*Reset Timer*/
	SCU_RESET->PRSET0 |= 0x1C;
	CCU40_CC40->TCCLR |= 0x03;

	/*PWM CCU4 Configuration*/
	SCU_RESET->PRCLR0|= (1<<SCU_RESET_PRCLR0_CCU40RS_Pos);//De assert Reset

	SCU_CLK->CLKSET= (1<<SCU_CLK_CLKSET_CCUCEN_Pos); //CCU clk enable
	CCU40->GIDLC|=(1<<CCU4_GIDLC_SPRB_Pos); //Prescaller Run Bit set
	CCU40_CC40->PSC=0x1; //Prescaller select->0
	CCU40_CC40->TC|= (1<<CCU4_CC4_TC_CLST_Pos); //Enable Shadow Transfer on Timer clear

	CCU40->GIDLC|= (1<<CCU4_GIDLC_CS0I_Pos); //CC40 Idle clear
	SCU_GENERAL->CCUCON|=(1<<SCU_GENERAL_CCUCON_GSC40_Pos); //CCU40_CC40 global enable
	CCU40_CC40->TCSET=1; //Timer Run Bit set
	CCU40_CC40->PRS=0xEA5F; //Period set
	CCU40_CC40->CRS=0x8000;  //duty cycle set
	CCU40->GCSS|= (1<<CCU4_GCSS_S0SE_Pos); //Shadow transfer request

	CCU40_CC40->TCSET |= 0x1; //start timer

	while(1)
	{
	/*20% duty cycle*/
	_pwm(20);
	}
}



/*! \brief Function _pwm() generate a PWM output signal on an associated pin.
 *  \param dutyC ... duty cycle drom 0% to 100%
 *  \returns 0 upon success, >0 on error
 */
int _pwm(uint32_t dutyC){

	if(dutyC<0 || dutyC>100)
		return 1;

	double dc;
	int		idc;
	dc=dutyC*0.01;
	dc=0xEA5F-(0xEA5F*dc);
	idc=(int)dc;

	CCU40_CC40->CRS=dc;  //duty cycle set
	CCU40->GCSS|= (1<<CCU4_GCSS_S0SE_Pos); //Shadow transfer request

	return 0;
}

/** EOF */


