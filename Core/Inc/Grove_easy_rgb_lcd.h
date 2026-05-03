/*
 * easy_rgb_lcd.h
 *
 *  Created on: Jul 10, 2019
 *  Author: @ArduinoEasy
 *	 Github:	https://github.com/mahmood-ul-hassan/Grove_LCD_RGB_Backlight
 *	 Source: Based on SeeedStudio Arduino Library 
 *			(https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight)
 *
 */

#ifndef __EASY_RGB_LCD_H_
#define __EASY_RGB_LCD_H_

//#include "main.h"
#include <sgm31323.h>
#include <stdint.h>
#include "i2c.h"



/*---------------------------------------------------------------------------*/
//	Type Defs
/*---------------------------------------------------------------------------*/


typedef struct
{
	//I2C_HandleTypeDef *hi2c; // Komt uit HAL
    /* CONFIG (const) */
    I2C_Interface_t i2c;
    //const I2C_Interface_t Rgb;

    const uint8_t Cols;
    const uint8_t NumLines;
    const uint8_t DotSize;

    /* STATE (runtime) */
   // uint8_t _displayfunction;
    uint8_t _displaycontrol;
    uint8_t _displaymode;

    uint8_t _LastAddress;

  //  uint8_t _initialized;
  //  uint8_t _currline;

} Grove_LCD_RGB_Config_t;



/*---------------------------------------------------------------------------*/
//	i2c-bit address
/*---------------------------------------------------------------------------*/
//  The address here is the bare address.
//  As soon as you use it in a HAL function like HAL_Master_Transmit,
//  Then shift one bit to left ( Address << 1 )

#define I2C_LCD_ADDR  0x3E
#define I2C_RGB_ADDR  0x30

/*---------------------------------------------------------------------------*/
// color define
/*---------------------------------------------------------------------------*/

#define LCD_WHITE           0
#define LCD_RED             1
#define LCD_GREEN           2
#define LCD_BLUE            3

#define LCD_READ			0x01
#define LCD_WRITE			~LCD_READ

//#define LCD_REG_RED         0x04        // pwm2
//#define LCD_REG_GREEN       0x03        // pwm1
//#define LCD_REG_BLUE        0x02        // pwm0

//#define LCD_REG_MODE1       0x00
//#define LCD_REG_MODE2       0x01
//#define LCD_REG_OUTPUT      0x08


/*---------------------------------------------------------------------------*/
// commands
/*---------------------------------------------------------------------------*/

#define LCD_CLEAR_DISPLAY 	0x01
#define LCD_RETURN_HOME 		0x02
#define LCD_ENTRYMODESET 	0x04
#define LCD_DISPLAYCONTROL 	0x08
#define LCD_CURSORSHIFT 	0x10
#define LCD_FUNCTIONSET 	0x20
#define LCD_SETCGRAMADDR 	0x40
#define LCD_SETDDRAMADDR 	0x80

/*---------------------------------------------------------------------------*/
// flags for display entry mode
/*---------------------------------------------------------------------------*/

#define LCD_ENTRY_LEFT 		0x02
#define LCD_ENTRY_RIGHT 	~LCD_ENTRY_LEFT

#define LCD_ENTRYSHIFT_INCREMENT 0x01
#define LCD_ENTRYSHIFT_DECREMENT ~LCD_ENTRYSHIFT_INCREMENT


/*---------------------------------------------------------------------------*/
// flags for display on/off control
/*---------------------------------------------------------------------------*/

#define LCD_DISPLAY_ON 		0x04
#define LCD_DISPLAY_OFF 	~LCD_DISPLAY_ON
#define LCD_CURSOR_ON 		0x02
#define LCD_CURSOR_OFF 		~LCD_CURSOR_ON
#define LCD_BLINK_ON 		0x01
#define LCD_BLINK_OFF 		~LCD_BLINK_ON

/*---------------------------------------------------------------------------*/
// flags for display/cursor shift
/*---------------------------------------------------------------------------*/

#define LCD_DISPLAY_MOVE 	0x08
#define LCD_CURSOR_MOVE 		0x00
#define LCD_MOVE_RIGHT 		0x04
#define LCD_MOVE_LEFT 		0x00

/*---------------------------------------------------------------------------*/
// flags for function set
/*---------------------------------------------------------------------------*/

#define LCD_8BITMODE 		0x10
#define LCD_4BITMODE 		0x00

#define LCD_2LINE 			0x08
#define LCD_1LINE 			0x00

#define LCD_5x10DOTS 		0x04
#define LCD_5x8DOTS 		0x00

/*---------------------------------------------------------------------------*/
//  Functions
/*---------------------------------------------------------------------------*/

void LCD_Begin( Grove_LCD_RGB_Config_t *lcd );   //uint8_t cols, uint8_t lines, uint8_t dotsize){


void LCD_Clear(Grove_LCD_RGB_Config_t *lcd);
void LCD_Home(Grove_LCD_RGB_Config_t *lcd);

void LCD_NoDisplay(Grove_LCD_RGB_Config_t *lcd);
void LCD_Display(Grove_LCD_RGB_Config_t *lcd);
void LCD_NoBlink(Grove_LCD_RGB_Config_t *lcd);
void LCD_Blink(Grove_LCD_RGB_Config_t *lcd);
void LCD_NoCursor(Grove_LCD_RGB_Config_t *lcd);
void LCD_Cursor(Grove_LCD_RGB_Config_t *lcd);
void LCD_ScrollDisplayLeft(Grove_LCD_RGB_Config_t *lcd);
void LCD_ScrollDisplayRight(Grove_LCD_RGB_Config_t *lcd);
void LCD_LeftToRight(Grove_LCD_RGB_Config_t *lcd);
void LCD_RightToLeft(Grove_LCD_RGB_Config_t *lcd);
void LCD_AutoScroll(Grove_LCD_RGB_Config_t *lcd);
void LCD_NoAutoScroll(Grove_LCD_RGB_Config_t *lcd);


void LCD_CreateChar(Grove_LCD_RGB_Config_t *lcd , uint8_t location, uint8_t charmap[]);
void LCD_SetCursor(Grove_LCD_RGB_Config_t *lcd , uint8_t col, uint8_t row);


/*---------------------------------------------------------------------------*/
// To display
/*---------------------------------------------------------------------------*/

void LCD_Write(Grove_LCD_RGB_Config_t *lcd ,uint8_t value);
void LCD_Print(Grove_LCD_RGB_Config_t *lcd, char* data, uint8_t size);
void LCD_Command(Grove_LCD_RGB_Config_t *lcd, uint8_t value);

/*---------------------------------------------------------------------------*/
// color control
/*---------------------------------------------------------------------------*/
void LCD_SetRGB(Grove_LCD_RGB_Config_t *lcd, uint8_t r, uint8_t g, uint8_t b);
void LCD_SetPWM(Grove_LCD_RGB_Config_t *lcd, uint8_t color, uint8_t pwm);


void LCD_SetColor(Grove_LCD_RGB_Config_t *lcd, uint8_t color);
void LCD_SetColorAll(Grove_LCD_RGB_Config_t *lcd);
void LCD_SetColorWhite(Grove_LCD_RGB_Config_t *lcd);



#endif /* SOURCE_EASY_RGB_LCD_H_ */
