# stm32 ssd1306 i2c driver

The original source: https://github.com/taburyak/STM32_OLED_SSD1306_HAL_DMA

(I modified this a bit)

The driver can work in 3 modes

## Settings in CubeMX or CubeIDE
- Set I2C to I2C mode
- I2C Speed: Standard mode
- I2C Clock: 100000

If DMA mode is also used
- I2Cx_TX: memory to peripheral
- Mode: normal
- Increment address: memory on
- Data Width: byte, byte
- NVIC I2Cx event interrupt enabled

(please see the examples)

## Settings in "ssd1306_defines.h"
- #define SSD1306_I2C_PORT hi2c1 or hi2c2 or hi2c3 (which i2c are you using)
- #define SSD1306_ADDRESS 0x3C
- #define SSD1306_128X64 or SSD1306_128X32 (Your display is 64 or 32 lines)
- #define SSD1306_USE_DMA 0 or 1 (not use or use the DMA)
- #define SSD1306_CONTUPDATE 0 or 1 (display update mode in DMA mode)

## Without DMA 
(#define SSD1306_USE_DMA 0, #define SSD1306_CONTUPDATE 0)

The drawing functions work in the screen buffer memory. The ssd1306_UpdateScreen function then transmits it to the display. It will not exit this function until it has completed the transfer.

## With DMA 
(#define SSD1306_USE_DMA 1, #define SSD1306_CONTUPDATE 0)

The drawing functions work in the screen buffer memory. The ssd1306_UpdateScreen function then transmits it to the display. The Update function only starts the transfer, the transfer is done with DMA in the background. If you redraw in the screen buffer before the transfer is complete, it is possible that the contents of the modified screen buffer will only be partially transferred to the display. In this case, use the update function again to completely transfer the contents of the current screen buffer to the display. With the update function, it is not necessary to wait for the end of the previous update DMA transmission, you can use it at any time.
It is possible to query if the DMA transfer is complete (ssd1306_UpdateScreenCompleted). You can also use a callback function to detect the end of a DMA transmission (ssd1306_UpdateCompletedCallback).

## Continuous update with DMA 
(#define SSD1306_USE_DMA 1, #define SSD1306_CONTUPDATE 1)

The drawing functions work in the screen buffer memory, but the contents of the screen buffer are continuously transmitted to the display with DMA in the background. Therefore, it is not necessary to use the update function (the ssd1306_UpdateScreen macro is empty). If you do not draw for a long time, it is possible to pause continuous DMA transmission (ssd1306_ContUpdateDisable). If you draw again, you can re-enable continuous DMA transmission (ssd1306_ContUpdateEnable).
It is possible to request interrupts with the callback function when the DMA transmission is in a certain area of the display. Use the ssd1306_SetRasterInt function to set which display memory page you want to interrupt. The interrupt function must be named ssd1306_RasterIntCallback.
The 64-line display contains 8 memory pages and the 32-row display contains 4 memory pages (see the ssd1306 chip data sheet).

