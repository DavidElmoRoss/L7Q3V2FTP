/*
    Modify this code so that when motion is NOT detected, the LCD
    shows a YELLOW background, and when it is detected it shows a
    PURPLE background.  Refer to chart on Page 3 of Lab 6
    
    You should  get the message   HALt thE SPreAd  on the 4 digit display     
*/

// Include Section
#include "mbed.h"                   
#include "DigitDisplay.h" 
#include "Grove_LCD_RGB_Backlight.h"          

// Hardware definitions
DigitDisplay segment(D2,D3);
Grove_LCD_RGB_Backlight fred(D14,D15);          

// Global variables
unsigned char mess[]= {0x00,0x00,0x00,0x00,           
                       0x78,0x74,0x79,0x00,0x6D,0x73,0x50,0x79,0x77,0x5E,                 
                       0x00,0x00,0x00,0x00}; 
unsigned short i;
InterruptIn PIR(D6);                          
// Global Variables
short bob=0;                      

// Asynchronous Interrupt Service Routine
void LOW(void)
{
   bob=1;                       
} 
int main(void)
{
                                         // Statement to set LCD to YELLOW
    PIR.fall(&LOW);                       
    segment.clear();                
    segment.setColon(0);            
    segment.setBrightness(4);
           
    
    for(;;)
    { 
       if(bob==1)        
       {  
                                          // Statement to set LCD to PURPLE                             
          segment.writeRaw(0,0x74);    
          segment.writeRaw(1,0x77);
          segment.writeRaw(2,0x38);
          segment.writeRaw(3,0x78);  
          wait_ms(500);
          for(i=0;i<=14;++i)             
          {
             segment.writeRaw(&mess[i]); 
               wait_ms(250);
          }
          wait_ms(1000);                
          bob=0;
                                          // Statement to set LCD to YELLOW  
        }
    }                       
}