#include "main.h"

/*USART_RX_BUF存放的是字符*/


int main(void)
{	
	Peripheral();
	
 	while(1)
	{
		uart_can();
		
		delay_ms(500);
		LED0=!LED0;//提示系统正在运行		   
	}
}

void Peripheral(void)
{
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	LED_Init();		  		//初始化与LED连接的硬件接口	 	
	KEY_Init();				//按键初始化		
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_Normal);//CAN初始化波特率500Kbps  
}


