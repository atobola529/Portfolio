#ifndef __ST7735_H__
#define __ST7735_H__


/*
 *   Based on https://github.com/o-m-d/st7735_spi_stm32
 */

#include <LCD_color565.h>
#include <LCD_font5x7.h>
#include <Utility_Xtoa.h>
#include "MX_Initialize.h"
#include <string.h>



// Screen resolution in normal orientation
#define scr_w         140
#define scr_h         140
#define LOW 0
#define HIGH 1

// CS pin macros
#define CS_L() HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, LOW)
#define CS_H() HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, HIGH)

// A0 pin macros
#define A0_L() HAL_GPIO_WritePin(LCD_A0_GPIO_Port, LCD_A0_Pin, LOW)
#define A0_H() HAL_GPIO_WritePin(LCD_A0_GPIO_Port, LCD_A0_Pin, HIGH)

// RESET pin macros
#define RST_L() HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, LOW)
#define RST_H() HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, HIGH)

// SDA pin macros
#define SDA_L() HAL_GPIO_WritePin(SPI_SDA_GPIO_Port, SPI_SDA_Pin, LOW)
#define SDA_H() HAL_GPIO_WritePin(SPI_SDA_GPIO_Port, SPI_SDA_Pin, HIGH)

// SCK pin macros
#define SCK_L() HAL_GPIO_WritePin(SPI_SCK_GPIO_Port, SPI_SCK_Pin, LOW)
#define SCK_H() HAL_GPIO_WritePin(SPI_SCK_GPIO_Port, SPI_SCK_Pin, HIGH)

typedef enum
{
  scr_normal = 0,
  scr_90     = 1,
  scr_270    = 2,
  scr_180    = 3
} ScrOrientation_TypeDef;


void ST7735_write(uint8_t data);
void ST7735_Init();
void ST7735_AddrSet(uint16_t XS, uint16_t YS, uint16_t XE, uint16_t YE);
void ST7735_Orientation(uint8_t orientation);
void ST7735_Clear(uint16_t color);
void ST7735_Pixel(uint16_t X, uint16_t Y, uint16_t color);
void ST7735_HLine(uint16_t X1, uint16_t X2, uint16_t Y, uint16_t color);
void ST7735_VLine(uint16_t X, uint16_t Y1, uint16_t Y2, uint16_t color);
void ST7735_Line(int16_t X1, int16_t Y1, int16_t X2, int16_t Y2, uint16_t color);
void ST7735_Rect(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2, uint16_t color);
void ST7735_FillRect(uint16_t X1, uint16_t Y1, uint16_t X2, uint16_t Y2, uint16_t color);
void ST7735_PutChar5x7(uint16_t X, uint16_t Y, uint8_t chr, uint16_t color, uint16_t bgcolor);
void ST7735_PutStr5x7(uint8_t X, uint8_t Y, char *str, uint16_t color, uint16_t bgcolor);


#endif
