#include "main.h"

/*USART_RX_BUF��ŵ����ַ�*/


int main(void)
{	
	Peripheral();
	
 	while(1)
	{
		uart_can();
		
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


