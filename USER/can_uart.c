#include "main.h"

cansend_buf sendbuf;

void uart_can(void)
{
	u8 i = 0, j = 0;
	static u8 cnt = 0;
	
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
}

void can_uart(CanRxMsg *RxMessage)
{
	int i;
	
	for(i = 0; i < 8; i++)
	{
		USART_SendData(USART1, RxMessage->Data[i]+48);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
	}
}
