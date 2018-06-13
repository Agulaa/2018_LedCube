/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
int i=0; 
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {

		if(i==0){
			GPIO_SetBits(GPIOD,GPIO_Pin_0);
			GPIO_ResetBits(GPIOD, GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6);
			i=1;
		} //1st layer from the bottom
		else if (i==1){
			GPIO_SetBits(GPIOD,GPIO_Pin_1);
			GPIO_ResetBits(GPIOD, GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6);
			i=2;
		} //2nd layer from the bottom
		else if(i==2){
			GPIO_SetBits(GPIOD,GPIO_Pin_2);
			GPIO_ResetBits(GPIOD, GPIO_Pin_1|GPIO_Pin_0|GPIO_Pin_3|GPIO_Pin_6);
				i=3;
		} //3rd layer from the bottom
		else if (i==3){
			GPIO_SetBits(GPIOD,GPIO_Pin_3);
			GPIO_ResetBits(GPIOD, GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_0|GPIO_Pin_6);
			i=4;
		} //4th layer from the bottom
		else if (i==4){
			GPIO_SetBits(GPIOD,GPIO_Pin_6);
			GPIO_ResetBits(GPIOD, GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_0);
			i=0;
		} //5th layer from the bottom


		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

	}


}


int main(void)
{
	//Diody - ANODY
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure1;
	GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure1.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure1.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOE, &GPIO_InitStructure1);


	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure2;
	GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure2.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure2.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure2);

	//Tranzystory - KATODY
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);


//------------------------------------------------------Main timer
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 1599;//1599;
	TIM_TimeBaseStructure.TIM_Prescaler = 99;//99;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM4, ENABLE);

	TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);


//-------------------------------------------------------przerwanie dla timera

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitTypeDef NVIC_InitStructure1;
	NVIC_InitStructure1.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure1.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure1.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure1.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure1);

	GPIO_SetBits(GPIOE,  GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);
	GPIO_SetBits(GPIOB, GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);



	for(;;);

}
