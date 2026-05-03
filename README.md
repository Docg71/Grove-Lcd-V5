# Grove LCD V5 : Upgraded RGB chip

The base of this project was founded by https://github.com/cbteeple.
He copied the original Arduino files, and changed it into a STM32 capable C version.

The problem with the Arduino version was, they never updated the software for use with the  new 
SGM 31323  RGB chip, introduced with the V5.0 version. 
## SGM 31323 module

In this version, all of the RGB chip function have been transferred to 
the SGM files. 
This makes that the total LCD code is virtually based on two devices. 
Where you first could work with one lcd instance, you now have two.
One for controlling the LCD itsself and one for the RGB chip. 

## C - Code / STM32 

Thanks to cb, The whole code is recoded to C and extended by me to learn/improve my C-Skills.
This also means that the original arduino base has been replaced by
the HAL libs from STM.  




# Founded on EasyLCD by cbteeple. 
Purpose: This library creates an easy-to-use interface for sending
full strings to i2c LCD screens. It also adds some functionallity
by allowing fading of the backlight on and off.


## License

Anyone can use this code, free of charge, as in the originals.
Still i would like updates to come back. 


Have questions, feedback or whatever.. Let me know. 

Happy coding

