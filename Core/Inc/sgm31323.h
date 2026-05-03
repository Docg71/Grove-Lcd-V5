/*
 * SGM31323.h
 *
 *  Created on: 2 mei 2026
 *      Author: docge
 */

#ifndef RGB_REG_H
#define RGB_REG_H

#include <stdint.h>
#include "bus_interface.h"


/*---------------------------------------------------------------------------*/
// typedefs
/*---------------------------------------------------------------------------*/

typedef enum
{
	Ch_R = 0x00,
	Ch_G,
	Ch_B

} RGB_Channels_t;



typedef enum
{
    RGB_LED_MODE_OFF  = 0x00,
    RGB_LED_MODE_ON   = 0x01,
    RGB_LED_MODE_PWM1 = 0x02,
    RGB_LED_MODE_PWM2 = 0x03

} RGB_LedMode_t;



/* SGM31323 Register map */
typedef enum
{
    RGB_REG_RESET_CONTROL = 0x00,
    RGB_REG_FLASH_PERIOD,
    RGB_REG_PWM1_TIMER,
    RGB_REG_PWM2_TIMER,
    RGB_REG_CHANNEL_ENABLE,
    RGB_REG_TRISE_TFALL,
    RGB_REG_LED_R_IOUT,
    RGB_REG_LED_G_IOUT,
    RGB_REG_LED_B_IOUT

} RGB_Reg_t;




typedef enum
{
    RGB_Reg0_RESET_TCTRL_TSLOT1        = 0x00,
    RGB_Reg0_RESET_TCTRL_TSLOT2        = 0x01,
    RGB_Reg0_RESET_TCTRL_TSLOT3        = 0x02,
    RGB_Reg0_RESET_TCTRL_TSLOT4        = 0x03,
    RGB_Reg0_DO_NOTHING                = 0x04,
    RGB_Reg0_RESET_REGISTERS_ONLY      = 0x05,
    RGB_Reg0_RESET_MAIN_DIGITAL_ONLY   = 0x06,
    RGB_Reg0_RESET_COMPLETE_CHIP       = 0x07
} RGB_Reg0_ResetCtrl_t;

typedef enum
{
    RGB_Reg0_ENABLE_SCL_HIGH_SDA_HIGH   = 0x00,
    RGB_Reg0_ENABLE_SCL_HIGH_SDA_TOGGLE = 0x01,
    RGB_Reg0_ENABLE_SCL_HIGH_ONLY       = 0x02,
    RGB_Reg0_ENABLE_ALWAYS_ON           = 0x03
} RGB_Reg0_EnableCtrl_t;

typedef enum
{
    RGB_Reg0_RAMP_SCALE_1X          = 0x00,
    RGB_Reg0_RAMP_SCALE_2X_SLOWER   = 0x01,
    RGB_Reg0_RAMP_SCALE_4X_SLOWER   = 0x02,
    RGB_Reg0_RAMP_SCALE_8X_FASTER   = 0x03
} RGB_Reg0_RampScale_t;



// Init
void sgm_Init(I2C_Interface_t *i2c);

// Register 0
void sgm_RGB_SetReg0(I2C_Interface_t *i2c,
                        RGB_Reg0_ResetCtrl_t reset_ctrl,
                        RGB_Reg0_EnableCtrl_t enable_ctrl,
                        RGB_Reg0_RampScale_t ramp_scale);


// Reg4 (channel mode)
void sgm_SetModeChannels_Reg4(I2C_Interface_t *i2c,
                             RGB_LedMode_t R,
                             RGB_LedMode_t G,
                             RGB_LedMode_t B);

// PWM / color
void sgm_SetPWM(I2C_Interface_t *i2c, uint8_t color, uint8_t pwm);
void sgm_setColor(I2C_Interface_t *i2c, uint8_t color);

// Presets
void sgm_SetColorAll(I2C_Interface_t *i2c);
void sgm_SetColorWhite(I2C_Interface_t *i2c);

// Direct RGB
void sgm_SetRGB(I2C_Interface_t *i2c, uint8_t r, uint8_t g, uint8_t b);



#endif /* INC_SGM31323_H_ */
