//for github

#include <Wire.h>
#include <TM1650.h>

#define adctemp A0
#define adcset A1

TM1650 dsply;

int tmer=0;

int newsettemp=0;
int oldsettemp=0;

int dlaytoshow=0;

unsigned int rawsettemp=0;
unsigned int rawcurtemp=0;

int lasttmer=0;
int numofsamp=30;
int count=0;


unsigned int currenttemp=0;
unsigned int settingtemp=0;
char chrsettemp[4]={0};
char chrcurtemp[4]={0};
void setup() 
{
  Wire.begin(); //Join the bus as master
//
 Serial.begin(9600); //Start serial communication at 9600 for debug statements
//  Serial.println("TM1650 Example Code");
pinMode(adctemp,INPUT);
pinMode(adcset,INPUT);
  dsply.init();
//  char line[] = " 128";
//  dsply.displayString(line);
}

void loop() 
{
//  d.displayOff();
//  d.displayString("____");
//  d.setBrightness(TM1650_MIN_BRIGHT);
//  d.displayOn();
//  delay(100);
//  char line[] = "kay ";
//
//  d.displayString(line);
//  d.setBrightnessGradually(TM1650_MAX_BRIGHT);
//  delay(2000);
//  d.setBrightnessGradually(TM1650_MIN_BRIGHT);
//  d.displayOff();
//  delay(1000);
//  
//  line[1] |= 128;
//  d.displayOn();
//  d.setBrightnessGradually(TM1650_MAX_BRIGHT);
//  d.displayString(line);
//  delay(2000);
//  
//  for (int i=0; i<8; i++) {
//    d.setBrightness(i);
//    delay(500);
//  }
//  d.displayString("789 ");
//  delay(2000);
//  
//  if (d.displayRunning("1234567890abcdefghijklmnop")) {
//    while (d.displayRunningShift()) delay(500);
//  }
//  delay(2000);
  
//  for (int i = 0; i<20; i++) {
//    d.displayOff();
//    delay(200);
//    d.displayOn();
//    delay(200);
//  }
//  
//  for (int i = 0; i<20; i++) {
//    d.setBrightness(1);
//    delay(200);
//    d.setBrightness(7);
//    delay(200);
//  }
//
//  for (int i = 0; i<20; i++) {
//    for (int j = 0; j<4; j++) {
//       d.setDot(j,true);
//       delay(200);
//    }
//    for (int j = 0; j<4; j++) {
//       d.setDot(j,false);
//       delay(200);
//    }
//  }

 
  if(tmer>=12000){
    
    newsettemp=settingtemp;
    
    if(((oldsettemp-newsettemp)>=8)||((newsettemp-oldsettemp)>=8)){
      
            dsply.displayString(chrsettemp);
            dsply.setDot(3,true);
            if(dlaytoshow>=15){
              oldsettemp=newsettemp;
              dlaytoshow=0;
            }
            dlaytoshow++;
            
            
    }else{
    
            dsply.displayString(chrcurtemp);
             dsply.setDot(3,false);
    }

    
    tmer=0;    
    lasttmer=0;
  }

  if((tmer-lasttmer)>=20){
    
          lasttmer=tmer;     
             
          if(count>=numofsamp){
            
                  settingtemp=(rawsettemp/numofsamp);
                  currenttemp=(rawcurtemp/numofsamp);
        
                  sprintf(chrsettemp, "%d", settingtemp);
                  sprintf(chrcurtemp, "%d", currenttemp);
//                  Serial.print(currenttemp);
//                  Serial.print("\n");
                  count=0;
                   rawsettemp=0;
                   rawcurtemp=0;
            }else{
                   rawsettemp+=analogRead(adcset);
                   rawcurtemp+= analogRead(adctemp);
    }
    count++; 
  }  


  

  tmer++; 

}
