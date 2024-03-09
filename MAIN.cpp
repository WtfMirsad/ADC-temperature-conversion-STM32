#include "stm32f10x.h"                  // Device header
	int raw;
	float temp,stepen =0.0008056640625;
int main(){

	//enable ADC1 in RCC , enable clock on PORTA and alternative function bit
		RCC->APB2ENR |=(1<<9);
		RCC->APB2ENR |=(1<<2);
		RCC->APB2ENR |=(1<<0);
		RCC->APB2ENR |=(1<<4);
		
	GPIOC-> CRH |= GPIO_CRH_MODE; 
	GPIOC-> CRH &=~ GPIO_CRH_CNF; 
	//set ADC clock -> CFGR prescaler   max 14MHZ recommended 12MHz
	  RCC->CFGR |=(2<<14);
	//select sampling time on ch0 pin A0 "SMPR2 register"  -> Tconve = cycles / ADCCLK  -> 111
		ADC1 -> SMPR2 |=(7<<0);
	//select sequence  -> we only have one on first chanel so we "point" to first sequence on SQR3 register
	ADC1->SQR3 |=(0<<0);
	//enable ADC_CR2_CONT
	ADC1->CR2 |=(1<<1);	
	//enable ADON bit -> wake up ADC
	ADC1->CR2 |=(1<<0);	
	// reset calibration in CR2
	ADC1->CR2 |=(1<<3);	
	//wait a litle bit
		while(ADC1->CR2 & ADC_CR2_RSTCAL){;}
	//CR2 register -> init calibration bit and wiat until HW reset it CAL bit
	ADC1->CR2 |=(1<<2);
	//wait a litle bit

	//once again set 1 to ADON bit -> first time wake up second time start conversion
	ADC1->CR2 |=(1<<0);	
	
	
			
	while(1)
		
	{
		
		//wait until EOC bit is set   ADC_SR registar Bit 1 EOC: End of conversion
		if(ADC1->SR & ADC_SR_EOC) {
			// read raw binary data from varible raw= ADC1->DR; register
		raw= ADC1->DR; 
			//wait until End of conversion EOC bit is "0"
		
	}
		temp = raw * stepen;
		

	}
}


	   


