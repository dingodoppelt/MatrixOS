#include "WS2812.h"

namespace WS2812
{
	uint16_t numsOfLED ;
	uint8_t TH_DutyCycle;
	uint8_t TL_DutyCycle;
	TIM_HandleTypeDef* htim;
	unsigned int tim_Channel;
	Color* frameBuffer;
	uint8_t* pwmBuffer; //TODO: Reduce the memory footprint to 1byte
	uint16_t bufferSize;
	int32_t progress = -1; //# of led sent, -1 means signal end has been send and ready for new job

	void Init(TIM_HandleTypeDef *HTIM, unsigned int TIM_Channel, uint16_t NumsOfLED) {

		//Timer Setup
		htim = HTIM;
		tim_Channel = TIM_Channel;
//		TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
//		TIM_MasterConfigTypeDef sMasterConfig = { 0 };
//		TIM_OC_InitTypeDef sConfigOC = { 0 };

		numsOfLED = NumsOfLED;
		bufferSize = numsOfLED * 24 + LED_DMA_END_LENGTH * 2;
		pwmBuffer = (uint8_t*)calloc(bufferSize, 1);

		/* TIM Callback init */
		if (HAL_TIM_RegisterCallback(htim, HAL_TIM_PWM_PULSE_FINISHED_CB_ID, DMAHandler) != HAL_OK) //Complete
		{
			MatrixOS::SYS::Error_Handler();
		}
	}

	uint32_t GetTimerPeriod()
	{
		uint32_t timerPeriod;
		if (HAL_RCC_GetHCLKFreq() % 800000 == 0) {
			timerPeriod = (HAL_RCC_GetHCLKFreq() / 800000) - 1;
		} else {
			return -1; //		TODO: Error_Handler
		}

		TH_DutyCycle = (timerPeriod * 173) >> 8;
		TL_DutyCycle = (timerPeriod * 82) >> 8;

		return timerPeriod;
	}

	uint8_t Show(Color *array) {
		if(progress != -1)
			return -1;
		progress = 0;
		// HAL_TIM_PWM_Stop_DMA(htim, tim_Channel);
		frameBuffer = array;
		PrepLEDBuffer();
		SendData();
		return 1;
	}

	void DMAHandler(TIM_HandleTypeDef *htim)
	{
		HAL_TIM_PWM_Stop_DMA(htim, tim_Channel);
		progress = -1;
	}


	void SendData() {
		HAL_TIM_PWM_Start_DMA(htim, tim_Channel, (uint32_t*) pwmBuffer, bufferSize);
	}


	void PrepLEDBuffer() //Automatically load next half buffer
	{
		uint32_t index = 0;
		for(uint8_t i = 0; i < LED_DMA_END_LENGTH; i++)
		{
			pwmBuffer[index] = 0;
			index ++;
		}
		while (index <= (bufferSize - 24) && progress < numsOfLED) { //Fills pwm until buffer is full or all LED completely processed
			uint32_t GRB = frameBuffer[progress].GRB(32);
			for (int8_t i = 23; i >= 0; i--) {
				 pwmBuffer[index] = GRB & (1 << i) ? TH_DutyCycle : TL_DutyCycle;
				index++;
			}
			progress++;
		}
		for(uint8_t i = 0; i < LED_DMA_END_LENGTH; i++)
		{
			pwmBuffer[index] = 0;
			index ++;
		}
	}
}
