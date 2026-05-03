/*
 * easy_rgb_lcd.c
 *
 *  Created on: Jul 10, 2019
 *  Author: @ArduinoEasy
 *	Github:	https://github.com/mahmood-ul-hassan/Grove_LCD_RGB_Backlight
 *	Source: Based on SeeedStudio Arduino Library 
 *			(https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight)
 *
*/

#include "easy_rgb_lcd.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static void I2c_Send_Bytes(Grove_LCD_RGB_Config_t *lcd, uint8_t *data, uint32_t len);


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


void LCD_Begin( Grove_LCD_RGB_Config_t *lcd )   //uint8_t cols, uint8_t lines, uint8_t dotsize){
{
	uint8_t _displayfunction = 0x00;

	if (lcd->NumLines > 1) {
        _displayfunction |= LCD_2LINE;
    }

    //_numlines = lines;
    //_currline = 0;


//_____NEEDS  REVIEW
    // for some 1 line displays you can select a 10 pixel high font
    if ((lcd->DotSize != LCD_5x8DOTS) && (lcd->NumLines == 1)) {
        _displayfunction |= LCD_5x10DOTS;
    }

    // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
    // according to datasheet, we need at least 40ms after power rises above 2.7V
    // before sending commands. Arduino can turn on way before 4.5V so we'll wait 50 msec

    HAL_Delay(50);	// 50-msec delay

    // this is according to the hitachi HD44780 datasheet
    // page 45 figure 23

    // Send function set command sequence
    LCD_Command( lcd, LCD_FUNCTIONSET | _displayfunction );
    HAL_Delay(5);  // wait more than 4.1ms

    // second try
    LCD_Command( lcd, LCD_FUNCTIONSET | _displayfunction);
    HAL_Delay(1);

    // third go
    LCD_Command( lcd, LCD_FUNCTIONSET | _displayfunction);


    // finally, set # lines, font size, etc.
    LCD_Command( lcd, LCD_FUNCTIONSET | _displayfunction);

    // turn the display on with no cursor or blinking default
    lcd->_displaycontrol = LCD_DISPLAY_ON | LCD_CURSOR_OFF | LCD_BLINK_OFF;
    LCD_Command( lcd, LCD_DISPLAYCONTROL | lcd->_displaycontrol);

    // clear it off
    LCD_Clear(lcd);

    // Initialize to default text direction (for romance languages)
    lcd->_displaymode = LCD_ENTRY_LEFT | LCD_ENTRYSHIFT_DECREMENT;
    // set the entry mode
    LCD_Command(lcd, LCD_ENTRYMODESET | lcd->_displaymode);


}

void LCD_Clear(Grove_LCD_RGB_Config_t *lcd)
{
	LCD_Command(lcd, LCD_CLEAR_DISPLAY);        // clear display, set cursor position to zero
	HAL_Delay(2); // this command takes a long time!
}

void LCD_Home(Grove_LCD_RGB_Config_t *lcd)
{
	LCD_Command(lcd , LCD_RETURN_HOME);        // clear display, set cursor position to zero
	HAL_Delay(2); // this command takes a long time!
}

void LCD_DisplayOff(Grove_LCD_RGB_Config_t *lcd)
{
	lcd->_displaycontrol &= LCD_DISPLAY_OFF;
    LCD_Command(lcd, LCD_DISPLAYCONTROL | lcd->_displaycontrol);
}

void LCD_DisplayOn(Grove_LCD_RGB_Config_t *lcd)
{
	lcd->_displaycontrol |= LCD_DISPLAY_ON;
    LCD_Command(lcd, LCD_DISPLAYCONTROL | lcd->_displaycontrol);
}

void LCD_NoBlink(Grove_LCD_RGB_Config_t *lcd)
{
	lcd->_displaycontrol &= LCD_BLINK_OFF;
    LCD_Command(lcd, LCD_DISPLAYCONTROL | lcd->_displaycontrol);
}

void LCD_Blink(Grove_LCD_RGB_Config_t *lcd)
{
	lcd->_displaycontrol |= LCD_BLINK_ON;
    LCD_Command(lcd, LCD_DISPLAYCONTROL | lcd->_displaycontrol);
}

void LCD_CursorOff(Grove_LCD_RGB_Config_t *lcd)
{
	lcd->_displaycontrol &= LCD_CURSOR_OFF;
    LCD_Command(lcd, LCD_DISPLAYCONTROL | lcd->_displaycontrol);
}

void LCD_CursorOn(Grove_LCD_RGB_Config_t *lcd)
{
	lcd->_displaycontrol |= LCD_CURSOR_ON;
	LCD_Command(lcd, LCD_DISPLAYCONTROL | lcd->_displaycontrol);
}

void LCD_scrollDisplayLeft(Grove_LCD_RGB_Config_t *lcd)
{
	LCD_Command(lcd,LCD_CURSORSHIFT | LCD_DISPLAY_MOVE | LCD_MOVE_LEFT);
}

void LCD_ScrollDisplayRight(Grove_LCD_RGB_Config_t *lcd)
{
	LCD_Command(lcd,LCD_CURSORSHIFT | LCD_DISPLAY_MOVE | LCD_MOVE_RIGHT);
}
void LCD_LeftToRight(Grove_LCD_RGB_Config_t *lcd)
{
	lcd->_displaymode |= LCD_ENTRY_LEFT;
    LCD_Command(lcd,LCD_ENTRYMODESET | lcd->_displaymode);
}
void LCD_RightToLeft(Grove_LCD_RGB_Config_t *lcd)
{
	lcd->_displaymode &= LCD_ENTRY_RIGHT;
    LCD_Command(lcd,LCD_ENTRYMODESET | lcd->_displaymode);
}

void LCD_Autoscroll(Grove_LCD_RGB_Config_t *lcd)
{
	lcd->_displaymode |= LCD_ENTRYSHIFT_INCREMENT;
    LCD_Command(lcd,LCD_ENTRYMODESET | lcd->_displaymode);
}

void LCD_noAutoscroll(Grove_LCD_RGB_Config_t *lcd)
{
	lcd->_displaymode &= LCD_ENTRYSHIFT_DECREMENT;
    LCD_Command(lcd, LCD_ENTRYMODESET | lcd->_displaymode);
}

void LCD_CreateChar(Grove_LCD_RGB_Config_t *lcd, uint8_t location, uint8_t charmap[])
{
    location &= 0x7; // we only have 8 locations 0-7
    LCD_Command(lcd, LCD_SETCGRAMADDR | (location << 3));


    uint8_t dta[9];
    dta[0] = 0x40;
    for(int i=0; i<8; i++)
    {
        dta[i+1] = charmap[i];
    }

    I2c_Send_Bytes(lcd, dta, 9);
}

void LCD_SetCursor(Grove_LCD_RGB_Config_t *lcd, uint8_t col, uint8_t row)
{

	col = (row == 0 ? col|0x80 : col|0xc0);
    uint8_t dta[2] = {0x80, col};

    I2c_Send_Bytes(lcd, dta, 2);
}

void LCD_Write(Grove_LCD_RGB_Config_t *lcd, uint8_t value)
{

    uint8_t dta[2] = {0x40, value};

    I2c_Send_Bytes(lcd, dta, 2);
}

void LCD_Print(Grove_LCD_RGB_Config_t *lcd, char *data, uint8_t size)
{
	while(size > 0){
		LCD_Write(lcd, data[0]);
		data++;
		size--;
	}
}

void LCD_Command(Grove_LCD_RGB_Config_t *lcd , uint8_t value)
{
    uint8_t dta[2] = {0x80, value};
    I2c_Send_Bytes(lcd,  dta, 2);
}


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/


static void I2c_Send_Bytes(Grove_LCD_RGB_Config_t *lcd, uint8_t *data, uint32_t len)
{
	lcd->_LastAddress = lcd->i2c.address;
	HAL_I2C_Master_Transmit(lcd->i2c.hi2c, (uint16_t) lcd->i2c.address << 1 , (uint8_t*)data, len, 1000);
}


