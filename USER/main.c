#include "main.h"

/*USART_RX_BUF存放的是字符*/

cansend_buf sendbuf;
int main(void)
{	
	u8 i = 0, j = 0;
	static u8 cnt = 0;
	
	Peripheral();
	
 	while(1)
	{
		if((USART_RX_STA&0x8000)!=0)
		{
			sendbuf.count = (USART_RX_STA&0X3FFF)/8;
			if((sendbuf.count*8) < (USART_RX_STA&0X3FFF))
				sendbuf.count++;
			for(i = 0; i < sendbuf.count; i++)
			{
				for(j = 0; j < 8; j++)
				{
					if(USART_RX_BUF[cnt] != 0)
					{
						sendbuf.data[j] = USART_RX_BUF[cnt]-48;
					}
					cnt++;
				}
				Can_Send_Msg(sendbuf.data, 8);										//CAN有三级FIFO，所以一次只能传输3个buf,超过3个，需要延时发送
				memset(sendbuf.data,0,8);
				if(sendbuf.count>2)
				{
					delay_ms(10);
				}
			}
			cnt=0;
			USART_RX_STA=0;
		}

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

