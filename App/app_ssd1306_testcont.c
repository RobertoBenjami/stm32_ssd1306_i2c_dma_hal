#include <stdio.h>
#include <string.h>
#include "main.h"

#include "ssd1306.h"

volatile uint8_t rast = 0;

void ssd1306_RasterIntCallback(uint8_t r)
{
  if(r == 1)
  {
    ssd1306_SetColor(Black);
    ssd1306_Fill();
  }

  else if(r == 2)
  {
    ssd1306_SetColor(White);
    ssd1306_Fill();
  }
}

void mainApp(void)
{
  ssd1306_Init();
  ssd1306_FlipScreenVertically();
  ssd1306_SetRasterInt(1 + 2 + 4 + 8 + 16 + 32 + 64 + 128 /* all PAGES */);
  while(1)
  {
  }
}
