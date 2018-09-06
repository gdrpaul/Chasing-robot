

#include "MotorDriver.h"

#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   20

TM1637Display display(CLK, DIO);

int pushButton = 5;
int V = 0 ; //speed



int speedshow = 0;


void setup()
{
  
	motordriver.init();
  pinMode(pushButton, INPUT);
  Serial.begin(9600);
	
       
}
 
void loop()
{      


 V = analogRead(A0);
 if(digitalRead(pushButton) == HIGH)
 { speedshow = 1;}



while(speedshow == 1)
{
  int k;
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  display.setBrightness(0x0f);

 bool lz = false;
k = analogRead(A0);
display.showNumberDec(k, lz);
delay(TEST_DELAY);

V = k;  

if(digitalRead(pushButton) == LOW)
{ 
display.setBrightness(7, false);  // Turn off
display.setSegments(data);
delay(TEST_DELAY);
speedshow = 0;
}
}





  int x, delay_en;
    char val;
    if(Serial.available())
    {
        
        val = Serial.read();
       if (val != -1)
        {
            switch (val)
            {
               case 'w'://Move ahead
                 motordriver.setSpeed(V,MOTORB);
                 motordriver.setSpeed(V,MOTORA);
	         motordriver.goForward(); 
	         break;
	         
	             case 'x'://move back fast
                 motordriver.setSpeed(V,MOTORB);
                 motordriver.setSpeed(V,MOTORA);
	         motordriver.goBackward();
	         break;

                case 't'://tone on   
                  tone(6, 2000);// play 2khz tone on pin 6
                    break;
                case 'y'://tone off    
                    noTone(6);
                    break;

       
                case 's'://stop     
                   motordriver.stop();
                    break;
            
            }
        }
    }
  }
 
  
 
        
     
      

 
