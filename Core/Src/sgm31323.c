/*
 * sgm31323.c
 *
 *  Created on: 2 mei 2026
 *      Author: docge
 */

#include "sgm31323.h"
#include "bus_interface.h"





#define RGB_BRIGHT_OFF   0x00 // 0.125 mA
#define RGB_BRIGHT_MID   0x4F // 10 mA
#define RGB_BRIGHT_HIGH  0xFF // 24 mA

#define RGB_CHANNEL_MODE(ch, mode)   ((mode) << ((ch) * 2))

#define RGB_CHANNEL_DEFAULT_MODE RGB_LED_MODE_ON
#define RGB_CHANNEL_DEFAULT_BRIGHT RGB_BRIGHT_MID



static void _SetReg(I2C_Interface_t *i2c, RGB_Reg_t reg, uint8_t val);

//----------------------------------------------------------------------------------

/*---------------------------------------------------------------------------*/
// color control settings
/*---------------------------------------------------------------------------*/

const uint8_t color_define[4][3] =
{
    {255, 255, 255},            // white
    {255, 0, 0},                // red
    {0, 255, 0},                // green
    {0, 0, 255},                // blue
};





void sgm_Init(I2C_Interface_t *i2c)
{

	/* Registers
	RGB_REG_RESET_CONTROL = 0x00,
    RGB_REG_FLASH_PERIOD,
    RGB_REG_PWM1_TIMER,
    RGB_REG_PWM2_TIMER,
    RGB_REG_CHANNEL_ENABLE,
    RGB_REG_TRISE_TFALL,
    RGB_REG_LED_R_IOUT,
    RGB_REG_LED_G_IOUT,
    RGB_REG_LED_B_IOUT
	 */


	// channel 0
	sgm_RGB_SetReg0(i2c,
	            RGB_Reg0_RESET_TCTRL_TSLOT1,
	            RGB_Reg0_ENABLE_ALWAYS_ON,
	            RGB_Reg0_RAMP_SCALE_1X);
	// Channel 1
// TBD	_SetReg(i2c, RGB_REG_FLASH_PERIOD,    0x00);

	// Channel 2
// TBD	_SetReg(i2c, RGB_REG_PWM1_TIMER,      0x01);

	// Channel 3
//TBD	_SetReg(i2c, RGB_REG_PWM2_TIMER,      0x01);

	// Channel 4
	sgm_SetModeChannels_Reg4(i2c , RGB_CHANNEL_DEFAULT_MODE , RGB_CHANNEL_DEFAULT_MODE , RGB_CHANNEL_DEFAULT_MODE );

	// Channel 5
// TBD	_SetReg(i2c, RGB_REG_TRISE_TFALL,     0x00);


	sgm_SetRGB(i2c, RGB_CHANNEL_DEFAULT_BRIGHT, RGB_CHANNEL_DEFAULT_BRIGHT,RGB_CHANNEL_DEFAULT_BRIGHT);
	// Channel 6
	//_SetReg(i2c, RGB_REG_LED_R_IOUT,      RGB_CHANNEL_DEFAULT_BRIGHT);

	// Channel 7
	//_SetReg(i2c, RGB_REG_LED_G_IOUT,      RGB_CHANNEL_DEFAULT_BRIGHT);

	// Channel 8
	//_SetReg(i2c, RGB_REG_LED_B_IOUT,      RGB_CHANNEL_DEFAULT_BRIGHT);



//	LCD_SetColorWhite(i2c );

}



void sgm_SetModeChannels_Reg4(I2C_Interface_t *i2c , RGB_LedMode_t R , RGB_LedMode_t G , RGB_LedMode_t B )
{

	_SetReg( i2c , RGB_REG_CHANNEL_ENABLE, RGB_CHANNEL_MODE( Ch_R , R) |
										   RGB_CHANNEL_MODE( Ch_G , G) |
										   RGB_CHANNEL_MODE( Ch_B , B) );

}


void sgm_RGB_SetReg0(I2C_Interface_t *i2c,
                        RGB_Reg0_ResetCtrl_t reset_ctrl,
                        RGB_Reg0_EnableCtrl_t enable_ctrl,
                        RGB_Reg0_RampScale_t ramp_scale)
{
    uint8_t value = 0;

    value |= ((uint8_t)reset_ctrl & 0x07);
    value |= (((uint8_t)enable_ctrl & 0x03) << 3);
    value |= (((uint8_t)ramp_scale & 0x03) << 5);

    _SetReg(i2c, RGB_REG_RESET_CONTROL, value);
}


void sgm_SetPWM(I2C_Interface_t *i2c, uint8_t color, uint8_t pwm)
{
	// TBD _SetReg(i2c , color, pwm);
}

void sgm_setColor(I2C_Interface_t *i2c, uint8_t color)
{
	if(color > 3)
		return ;

	sgm_SetRGB(i2c , color_define[color][0], color_define[color][1], color_define[color][2]);
}

void sgm_SetColorAll(I2C_Interface_t *i2c)
{
	sgm_SetRGB(i2c , 0, 0, 0);
}

void sgm_SetColorWhite(I2C_Interface_t *i2c)
{
	sgm_SetRGB(i2c , 255, 255, 255);
}



void sgm_SetRGB(I2C_Interface_t *i2c, uint8_t r, uint8_t g, uint8_t b)
{

	// Channel 6
		_SetReg(i2c, RGB_REG_LED_R_IOUT, r);
		// Channel 7
		_SetReg(i2c, RGB_REG_LED_G_IOUT, g);
		// Channel 8
		_SetReg(i2c, RGB_REG_LED_B_IOUT, b);

}


static void _SetReg(I2C_Interface_t *i2c, RGB_Reg_t reg, uint8_t val)
{
	uint8_t data[2] = {reg, val};

	HAL_I2C_Master_Transmit(i2c->hi2c, (uint16_t) i2c->address << 1 , (uint8_t*)data, 2, 1000);
}
