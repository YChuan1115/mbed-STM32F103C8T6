#include "stm32f103c8t6.h"
#include "mbed.h"
#include "Adafruit_SSD1306.h"
#include "STM32_USB48MHz.h"
#include "USBSerial.h"

#define RELAY_BOARD_ADDR (0X3C)
DigitalOut  usbEn(PB_9);

// an I2C sub-class that provides a constructed default
class I2CPreInit : public I2C
{
public:
    I2CPreInit(PinName sda, PinName scl) : I2C(sda, scl)
    {
        frequency(400000);
        start();
    };
};

DigitalOut led1(PC_13);
DigitalIn sdaDummy(PB_9, PullUp);
DigitalIn sclDummy(PB_8, PullUp);
I2C gI2C(PB_9,PB_8);
Adafruit_SSD1306_I2c gOled2(gI2C, D4);
   
//SPIPreInit gSpi(p5,NC,p7);
//Adafruit_SSD1306_Spi gOled1(gSpi,p26,p25,p24);
 
int main()
{   uint16_t x=0;
//	usbEn = 0;
    STM32_HSI_USB48MHz();  
	Serial    pc(PA_2, PA_3);
	USBSerial serial; // tx, rx
	serial.printf("Hello World!\n");
	gOled2.splash();
	gOled2.printf("%ux%u OLED Display\r\n", gOled2.width(), gOled2.height());
    gOled2.display();
	gOled2.clearDisplay();
    //gOled1.printf("%ux%u OLED Display\r\n", gOled1.width(), gOled1.height());
    char data_write[2];
    char  data_counter = 0;
    
    data_write[0] = 0x12;
    data_write[1] = 0x02;	
    
    while(1)
    {
        led1 = !led1;
		
		serial.printf("COUNT:%u\r",x);
        gOled2.printf("COUNT:%u\r",x++);
        gOled2.display();
        gOled2.display();
        wait(1.0);
    }
}
