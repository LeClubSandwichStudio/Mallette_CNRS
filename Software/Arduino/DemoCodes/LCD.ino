// TO CONTROL BUTTONS : PLEASE FIND SOME DETAILS OR TESTS HERE
// https://github.com/Klipper3d/klipper/issues/898

//Sample using LiquidCrystal library
#include <LiquidCrystal.h>

// select the pins used on the LCD panel
int rs=12, en=11, d4=5, d5=4, d6=3, d7=2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// Default settings
int thrs        = 2;  // 1, 2, 3 or 4 out of 0 to 5
int oct         = 2;  // 1, 2 or 3 out of 1 to 3
int vox         = 2;  // out of 1 to 8  
int bnk         = 5;  // out of 1 to 16 
int prog;
int chn         = 1;  // out of 1 to 16 

// read the buttons
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // read the value from the sensor 
 // we add approx 50 to those values and check to see if we are close
 if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
 // For V1.1 us this threshold
 if (adc_key_in < 150)   return btnLEFT;  
 if (adc_key_in < 195)  return btnDOWN; 
 if (adc_key_in < 380)  return btnSELECT; 
 if (adc_key_in < 555)  return btnRIGHT;
 if (adc_key_in < 790)  return btnUP;

 return btnNONE;  // when all others fail, return this...
}

void setup()
{
 lcd.begin(20,4);              // start the library
 lcd.clear();
 lcd.setCursor(0,1);
 lcd.print("Message Here"); // print a simple message
 delay(5000);
}
 
void loop()
{
 lcd.setCursor(0,0);
 lcd.print("Data sent:");
 lcd.setCursor(9,1);            // move cursor to second line "1" and 9 spaces over
 lcd.print(random(40,76));      // display seconds elapsed since power-up
 delay(500);

 lcd.setCursor(0,2);
 lcd.print("Button Pressed:");
 lcd.setCursor(11,2);            // move to the begining of the second line
 lcd_key = read_LCD_buttons();  // read the buttons

 switch (lcd_key)               // depending on which button was pushed, we perform an action
 {
   case btnRIGHT:
     {
     if(bnk == 15){bnk=-1;}
     bnk = bnk+1;
     lcd.print("Btn1     ");
     break;
     }
   case btnLEFT:
     {
     if(oct == 3){oct=0;}
     oct = oct+1;
     lcd.print("Btn2     ");
     break;
     }
   case btnUP:
     {
     if(thrs == 4){thrs=0;}
     thrs = thrs+1;
     lcd.print("Btn3     ");
     break;
     }
   case btnDOWN:
     {
     if(chn == 16){chn=0;}
     if(chn == 9){chn=10;}
     chn = chn+1;
     lcd.print("Btn4     ");
     break;
     }
   case btnSELECT:
     {
     if(vox == 8){vox=0;}
     vox = vox+1;
     lcd.print("Btn2     ");
     break;
     }
     case btnNONE:
     {
     lcd.print("None     ");
     break;
     }
 }

 lcd.setCursor(0,3);
 lcd.print("Dflt:");
 lcd.setCursor(6,3);
 lcd.print("T");
 lcd.print(thrs);
 lcd.setCursor(9,3);
 lcd.print("O");
 lcd.print(oct);
 lcd.setCursor(12,3);
 lcd.print("P");
 prog = (8*bnk)+vox;
 if(prog > 128){
  prog = prog-128;
 }
 lcd.print(String(prog)+"  ");
 lcd.setCursor(17,3);
 lcd.print("C");
 lcd.print(String(chn)+" ");
}
