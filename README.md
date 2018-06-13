# LedCube 5x5x5

## Overview
This is a PUT student's project.


## Tools & Requirements
* STM32F4 Discovery microcontroller;
* 125 led diodes;
* 25 360Ω resistors;
* 5 2.2kΩ resistors;
* 5 BC338 transistors;
* Cables;
* Wires;
* Soldering kit;
* Some patience and free time. :)


## Code explanation
- Lighting the whole cube up
    ```
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
    ```
    >To enable all diodes we have to switch the levels of our cube in which we are closing the circuit, so to do it we are using a 50Hz timer. Every time when it overflows different transistor is being chosen to close the circuit on a particular level.



## Deployment

We recommend using [System Workbench for STM32](http://www.st.com/en/development-tools/sw4stm32.html#getsoftware-scroll) to deploy the code on your device.

## Authors
* Agnieszka Rusin - [GitHub](https://github.com/Agulaa)
* Michał Włodarczyk - [GitHub](https://github.com/m-wlodarczyk)

## Contact

* agnieszka.rusin@student.put.poznan.pl
* michal.mi.wlodarczyk@student.put.poznan.pl

## License
[MIT](https://choosealicense.com/licenses/mit/)
