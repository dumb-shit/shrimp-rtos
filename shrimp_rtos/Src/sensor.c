#include "sensor.h"


struct sensor{
	double temp_value;
	float print_value;
  char *name;
} ;

struct sensor pH;
struct sensor tur;
struct sensor tds;

double ADC_ConvertedValueLocal; 
uint16_t ADC_ConvertedValue;
char Sensor_Tx[30];
float adc_raw_value;

/*
	获取ADC值
*/
uint32_t Get_ADC_Value(ADC_HandleTypeDef *hadc)
{
    uint32_t adc_value = 0;
	HAL_ADC_Start(hadc);
    adc_value = HAL_ADC_GetValue(hadc);

    return adc_value;
}

float Calculate_PH(void)
{
   adc_raw_value = (float)Get_ADC_Value(&hadc1);
   pH.temp_value = (adc_raw_value * (3.3f / 4096.0f)); // 使用浮点数除法
    pH.temp_value = -5.8887f *  pH.temp_value + 21.677f;      // 使用浮点常量
	return  pH.temp_value;
}

float Calculate_tur(void)
{
	tur.temp_value=(float)Get_ADC_Value(&hadc2)*(VCC/4096);
	tur.temp_value = tur.temp_value*100/VCC;
		if(tur.temp_value>100)
	      {
			tur.temp_value=100;
	      }
		  
		return tur.temp_value;
}


float Calculate_tds(void)
{
	ADC_ConvertedValueLocal  =(double)Get_ADC_Value(&hadc3)/4096*VCC;
	tds.temp_value= 66.71*ADC_ConvertedValueLocal*ADC_ConvertedValueLocal*ADC_ConvertedValueLocal
	-127.93*ADC_ConvertedValueLocal*ADC_ConvertedValueLocal
	+428.7*ADC_ConvertedValueLocal;
	return tur.temp_value;
}

/*
	定时器中断回调函数，每秒获取一次数据
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM10)
	{	
		pH.print_value=Calculate_PH();
		tur.print_value =Calculate_tur();
		tds.print_value=Calculate_tds();		
	}
	HAL_TIM_Base_Start_IT(&htim10);
}

/*
	创建发送传感器数据的任务
*/

void vTaskTur(void *pvParameters)
{
	while(1)
	{
	sprintf(Sensor_Tx,"tur=%.2f\n",tur.print_value);
	HAL_UART_Transmit(&huart1,(uint8_t *)Sensor_Tx,strlen(Sensor_Tx),HAL_MAX_DELAY);
	vTaskDelay(1000);
	}
}

void vTaskpH(void *pvParameters)
{
	while(1)
	{
	//sprintf(Sensor_Tx,"pH=%d\n",Get_ADC_Value(&hadc1));
	sprintf(Sensor_Tx,"pH=%f\n",pH.print_value);
	HAL_UART_Transmit(&huart1,(uint8_t *)Sensor_Tx,strlen(Sensor_Tx),HAL_MAX_DELAY);
	vTaskDelay(1000);
	}
}

void vTaskTDS(void *pvParameters)
{
	while(1)
	{
	sprintf(Sensor_Tx,"TDS=%f\n",tds.print_value);
	HAL_UART_Transmit(&huart1,(uint8_t *)Sensor_Tx,strlen(Sensor_Tx),HAL_MAX_DELAY);
	vTaskDelay(1000);
	}
}
