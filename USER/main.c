#include "main.h"

/*USART_RX_BUF��ŵ����ַ�*/

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
				Can_Send_Msg(sendbuf.data, 8);										//CAN������FIFO������һ��ֻ�ܴ���3��buf,����3������Ҫ��ʱ����
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
		LED0=!LED0;//��ʾϵͳ��������		   
	}
}

void Peripheral(void)
{
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�	 	
	KEY_Init();				//������ʼ��		
	CAN_Mode_Init(CAN_SJW_1tq,CAN_BS2_8tq,CAN_BS1_9tq,4,CAN_Mode_Normal);//CAN��ʼ��������500Kbps  
}

