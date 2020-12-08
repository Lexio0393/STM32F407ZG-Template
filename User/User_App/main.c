#include "main.h"

int main(void)
{

	uint8_t i;
	
//	ConfigTask();
	
	while (1)
	{
		Delay_ms(5);
    i++;
		
		if( (i % 2) == 0)
		{
			#if 1

			#endif        
		}
		
		if( (i % 500) == 0)
		{
			#if 1

			#endif  
		}
	}
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif
