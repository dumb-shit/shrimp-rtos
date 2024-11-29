#include "4gdtu.h"

int value[KEYWORD_COUNT];
int QueueReceive[KEYWORD_COUNT];
QueueHandle_t uartQueue;

char  tx[50];
int a=1;
uint8_t i = 0; 

// 定义关键词数组
const char* keywords[KEYWORD_COUNT] = {
    "LightSwitch", "Water", "Oxygen", "Feed1", "Feed2", "Feed3", "Feed4"
};

// 定义值关键字
const char* valueKey = "\"value\":";

// 接收缓冲区
char receivedString[BUFFER_SIZE];
uint8_t receivedData;

void vReceiveTask(void *pvParameters)
{
    while (1)
    {	 
/*
	提取字符串
*/
		for (int k = 0; k < KEYWORD_COUNT; k++)
          {
           if (strstr(receivedString, keywords[k]) != NULL)
            {
             char *valuePtr = strstr(receivedString, "\"value\":");		
			 valuePtr += strlen("\"value\":");
             value[k] = atoi(valuePtr);
			 xQueueSend(uartQueue,&value,portMAX_DELAY);
			}
          }		
		vTaskDelay(5);
    }
}

void vReceiveQueueTask(void *pvParameters)
{
    while (1)
    {	 
			if(xQueueReceive(uartQueue,&QueueReceive,portMAX_DELAY==pdPASS))
			{
				if(QueueReceive[0]==1)
  			{
   				light_control(1);
  			}
  			else
  			{
  				light_control(0);
  			}
			
  			if(QueueReceive[1]==1)
    		{
  				water_control(1);
  			}
				else
				{
					water_control(0);
				}
				if(QueueReceive[2]==1)
    		{
  				oxygen_control(1);
  			}
				else
				{
				 oxygen_control(0);
				}
				if(QueueReceive[3]==1)
    		{
  				PWM_START1();
  			}
				else
				{
					PWM_STOP1();
				}
				if(QueueReceive[4]==1)
    		{
  				PWM_START2();
  			}
				else
				{
				 PWM_STOP2();
				}
				if(QueueReceive[5]==1)
    		{
  				PWM_START3();
  			}
				else
				{
				 PWM_STOP3();
				}
				if(QueueReceive[6]==1)
    		{
  				PWM_START4();
  			}
				else
				{
				 PWM_STOP4();
				}
				
			}
					
			vTaskDelay(100);
		}
          		            
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART3)
	{
		if (receivedData == '\n') 
       {
           receivedString[i]='\0'; 
           i = 0;   
       }
    else
       {
           receivedString[i++] = receivedData; 
       }
	}
	HAL_UART_Receive_IT(&huart3, &receivedData, 1);
}

void HAL_UART_INTERRUPT(void)
{
  HAL_UART_Receive_IT(&huart3, &receivedData, 1);
}



