#include "ds18b20.h"

char ds18b20_tx[150];

void DQ_OUT(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);

  /*Configure GPIO pins : PD8 PD9 PD10 PD11 */
  GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

void DQ_IN(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */

  /*Configure GPIO pin : PD11 */
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

uint8_t DS18B20_Read_Byte(void)
{
        uint8_t i=0,dat=0;

        for (i=0;i<8;i++)
        {
        DQ_OUT();//???????
        DQ(0); //??
        delay_us(2);
        DQ(1); //????
        DQ_IN();//???????
        delay_us(12);
        dat>>=1;
        if( DQ_GET() )
        {
            dat=dat|0x80;
        }
        delay_us(50);
     }
        return dat;
	
}

void DS18B20_Write_Byte(uint8_t dat)
{
        uint8_t i;
        DQ_OUT();//??????
        for (i=0;i<8;i++)
        {
                if ( (dat&0x01) ) //?1
                {
                        DQ(0);
                        delay_us(2);
                        DQ(1);
                        delay_us(60);
                }
                else //?0
                {
                        DQ(0);//??60us
                        delay_us(60);
                        DQ(1);//????
                        delay_us(2);
                }
        dat=dat>>1;//?????
        }
}
uint8_t DS18B20_Check(void)
{
        uint8_t timeout=0;
    //??DS18B20
        DQ_OUT(); //???????
        DQ(0); //??DQ
        delay_us(750); //??750us
        DQ(1); //??DQ
        delay_us(15);  //15us

    //???????
        DQ_IN();
    //????,???????
        while ( DQ_GET() &&timeout<200)
        {
                timeout++;//????
                delay_us(1);
        };
        //?????
        if(timeout>=200)
                return 1;
        else
                timeout=0;

        //??18B20????
        while ( !DQ_GET() &&timeout<240)
        {
                timeout++;//????
                delay_us(1);
        };
    //??????
        if(timeout>=240)
                return 1;

        return 0;
}

void DS18B20_Start(void)
{
        DS18B20_Check();                //?????????
        DS18B20_Write_Byte(0xcc);   //????????????
        DS18B20_Write_Byte(0x44);   //??????
}


float DS18B20_GetTemperture(void)
{
        uint16_t temp;
        uint8_t dataL=0,dataH=0;
        float value;

        DS18B20_Start();
        DS18B20_Check();
        DS18B20_Write_Byte(0xcc);//????????????
        DS18B20_Write_Byte(0xbe);// ??????
        dataL=DS18B20_Read_Byte(); //LSB
        dataH=DS18B20_Read_Byte(); //MSB
        temp=(dataH<<8)+dataL;

        if(dataH&0X80)
        {
                temp=(~temp)+1;
                value=temp*(-0.0625);
        }
        else
        {
                value=temp*0.0625;
        }
				
				if(value>40 || value <10)
				{
					return -1;
				}
        return value;
} 

/*
        创建发送温度传感器数据的任务
*/
void vTaskDS18B20Print(void *pvParameters)
{
	while(1)
	{
		//sprintf(ds18b20_tx, "{\"id\":1729489637321,\"params\":{\"Temperture\":%.2f},\"version\":\"1.0\",\"method\":\"thing.event.property.post\"}", DS18B20_GetTemperture());
		sprintf(ds18b20_tx, "tem:%.2f",DS18B20_GetTemperture());
		HAL_UART_Transmit(&huart1,(uint8_t *)ds18b20_tx,strlen(ds18b20_tx),HAL_MAX_DELAY);
		vTaskDelay(1000);
	}
}

