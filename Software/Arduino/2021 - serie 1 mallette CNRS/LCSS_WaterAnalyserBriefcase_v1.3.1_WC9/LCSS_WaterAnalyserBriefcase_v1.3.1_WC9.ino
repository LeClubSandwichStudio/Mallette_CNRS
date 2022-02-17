/*
 * file LCSS_WaterAnalyserBriefcase_v1.3.1 WC9
 * 
 * We use different example codes like : 
 *
 * >>> file DFRobot_EC.ino + libraries
 * @ https://github.com/DFRobot/DFRobot_EC
 * >>> file DFRobot_PH.ino + libraries
 * @ https://github.com/DFRobot/DFRobot_PH
 * 
 * 
 * VERSION 1.3 : 
 * - add voltage values for each sensor in json
 */

//////////////////////////////////////////////////
//                  Bill of Materials
/////////////////////////////////////////////////


//////////////////////////////////////////////////
//                  Wiring
/////////////////////////////////////////////////
/*

GND ->GND 
VCC:
  EC and PH:                  VCC to VIN (closest pin to usb connector in the corner)
  Temperature and turbidity:  VCC to 3.3v (third pin from the usb connector, same side as VIN)
Signal wire:
  EC          -> 17 (A3)
  Tunbidity   -> A21
  Temperature -> 33 (A14)
  PH          -> 23 (A9)
  
*/
//////////////////////////////////////////////////
//                  Commands
/////////////////////////////////////////////////
/*
  {"command":"start"}
  {"command":"stop"}
  {"command":"restart"}
  {"setinterval":"999"}
*/

//////////////////////////////////////////////////
//              PIN configuration
/////////////////////////////////////////////////
#define PHPIN  23
#define TEMPPIN 33
#define ECPIN  17
#define TURBPINSENSOR A21


//////////////////////////////////////////////////
//                  Libraries
/////////////////////////////////////////////////
#include <ArduinoJson.h>
#include "Korzhenevskiy_tick_tack_2.h"
#include "DFRobot_PH.h"
#include "DFRobot_EC.h"
#include <EEPROM.h>
#include <OneWire.h>
#include <TimeLib.h>
#include <stdio.h>
#include <time.h>
#include <LiquidCrystal.h>
#include <Math.h>

#include <TimeLib.h>

//////////////////////////////////////////////////
//                Declarations
/////////////////////////////////////////////////
void measure_sensors();
OneWire ds(TEMPPIN);
float phValue, temperature, turbidity, turbidityNTU, ecValue, voltageTurb, voltageEC, voltagePH;
DFRobot_PH ph;
DFRobot_EC ec;
Korzhenevskiy_tick_tack_2 sensor_timer(measure_sensors, 1000);
DynamicJsonDocument doc(256);

const int rs = 26, en = 25, d0 = 5, d1 = 6, d2 = 7, d3 = 8;
LiquidCrystal lcd(rs, en, d0, d1, d2, d3);
int i=0;
int p=0;

byte customChars[8][8] = {
    {
        B00000,
        B00000,
        B00000,
        B00000,
        B00000,
        B00001,
        B00011,
        B00101
    },{
        B00000,
        B00000,
        B00000,
        B00010,
        B10000,
        B01101,
        B11000,
        B11110
    },{
        B00000,
        B00000,
        B00010,
        B01000,
        B01100,
        B10010,
        B01100,
        B00010
    },{
        B01110,
        B01110,
        B01111,
        B11110,
        B11110,
        B11111,
        B11111,
        B11111
    },{
        B11100,
        B11100,
        B01100,
        B11110,
        B10111,
        B11001,
        B00111,
        B11101
    },{
        B10000,
        B00000,
        B00000,
        B00000,
        B00000,
        B10000,
        B11100,
        B11111
    },{
        B11111,
        B11111,
        B00000,
        B00000,
        B11111,
        B00000,
        B11111,
        B11111
    },{
        B11111,
        B11111,
        B00000,
        B11111,
        B00000,
        B00000,
        B00000,
        B00000
    }
};

byte Data[2][8] = {
    {
      B00000,
  B11111,
  B01010,
  B00111,
  B00010,
  B00010,
  B00010,
  B00010
    },{
  B00000,
  B11000,
  B10000,
  B00001,
  B00001,
  B00101,
  B10101,
  B10101
    }
};

int val=0;
void drawBanner();



//////////////////////////////////////////////////
//                   setup
/////////////////////////////////////////////////
void setup() {
  //sensor_timer.start();

  setSyncProvider(getTeensy3Time);
  
  Serial.begin(9600);
  Serial.println("START SERIAL");

  Serial.println("START RTC CHECK");
  delay(1000);
  if (timeStatus()!= timeSet) {
    Serial.println("Unable to sync with the RTC");
  } else {
    Serial.println("RTC has set the system time");
    displayTeensyTime();
  }

  Serial.println("PH SENSOR BEGIN");
  ph.begin();
  Serial.println("EC SENSOR BEGIN");
  ec.begin();
  Serial.println("SET PIN MODE");
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(24, INPUT);

  //Serial.begin(9600);

  Serial.println("LCD BEGIN");
  lcd.begin(20, 4);
  for(int i = 0; i < 8; i++)
        lcd.createChar(i, customChars[i]);
    
    for(int i = 17;  i >= 0; i--){
        lcd.clear();
        drawBanner(i);
        delay(250);
    }

  delay(2500);
  
  if (p==0){
    lcd.clear();
    lcd.home();
    lcd.blink();
    lcd.setCursor(2, 0);
    lcd.print("L");
    delay(250);
    lcd.print("E");
    delay(150);
    lcd.print(" ");
    delay(250);
    lcd.print("C");
    delay(250);
    lcd.print("L");
    delay(250);
    lcd.print("U");
    delay(250);
    lcd.print("B");
    delay(250);
    lcd.setCursor(10, 1);
    lcd.print("S");
    delay(250);
    lcd.print("A");
    delay(250);
    lcd.print("N");
    delay(250);
    lcd.print("D");
    delay(250);
    lcd.print("W");
    delay(250);
    lcd.print("I");
    delay(250);
    lcd.print("C");
    delay(250);
    lcd.print("H");
    lcd.setCursor(3, 2);
    lcd.print("S");
    delay(250);
    lcd.print("T");
    delay(250);
    lcd.print("U");
    delay(250);
    lcd.print("D");
    delay(250);
    lcd.print("I");
    delay(250);
    lcd.print("O");
    delay(250);
    delay(3000);
    lcd.noBlink();

    delay(250);
    lcd.clear();
    lcd.setCursor(3, 2);
    lcd.print("LOADING . . . ");
    delay(250);
  
    
    p=2;
    delay(3000);
    
  }

   lcd.clear();
    lcd.home();
    lcd.setCursor(0, 0);
    lcd.print("WIFI : WaterCase_9");

    lcd.setCursor(1, 1);
    lcd.print("MDP : kmvwqazh");

    lcd.createChar(0, Data[0]);
    lcd.setCursor(1, 3);
    lcd.write(byte(0));

    lcd.createChar(1, Data[1]);
    lcd.setCursor(2, 3);
    lcd.write(byte(1));
    
    lcd.setCursor(4, 3);
    lcd.print("IP: 10.3.141.19");
    p=2;
}

void drawBanner(int offset){
    for(int j = 1; j < 3; j++){
        for(int i = 0; i < 3; i++){
            lcd.setCursor(offset+i, j);
            int characterIndex = (j-1) * 3 + i;
            lcd.write(byte(characterIndex));
        }
    }
    
    lcd.setCursor(offset+4,1);
    lcd.write("WATER ANALYSER");
    lcd.setCursor(offset+7,2);
    lcd.write("BRIEFCASE");    
    
}

//////////////////////////////////////////////////
//                  loop
/////////////////////////////////////////////////
void loop() {
    Korzhenevskiy_tick_tack_2::mass_tick();   // check all timers and start if needed
    check_serial();                           // check if new command is received
}



void check_serial() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    Serial.print( "NEW MESSAGE : ");
    Serial.println(data);
    DeserializationError error = deserializeJson(doc, data);
    if (error) {
      Serial.println("JSON parse failed");
    }
    else { // {"command":"start"}
      if ( doc["command"] == "start") {
        Serial.println( "starting sensors");
        sensor_timer.start();
      }
      else if ( doc["command"] == "stop") {
        Serial.println( "stopping sensors");
        sensor_timer.stop ();
      }//{"setinterval":"999"}
      else if ( doc.containsKey("setinterval")) {
        int newinterval = doc["setinterval"];
        if ((newinterval > 500) && (newinterval < 1000 * 60)) {
          Serial.print( "setting new sensor interval");
          Serial.println(newinterval);
          sensor_timer.setinterval (newinterval);
        }
        else Serial.println("this interval is not allowed (500ms-1m)");
      }
      else if (doc["command"] == "restart") {

       delay(2000);
       _reboot_Teensyduino_();

      }
    }

  }
}



void measure_sensors()
{
  analogReadResolution(16);
//---------------------------------------------------------
//                  Temperature
//---------------------------------------------------------
  // READ TEMPERATURE
  temperature = readTemperature(); 
  // ARRONDI AVEC 1 DECIMAL       
  temperature = (round(temperature * 10));
  temperature = temperature / 10;
//---------------------------------------------------------
//                          PH
//---------------------------------------------------------
 // READ PH VOLTAGE
  voltagePH = analogRead(PHPIN) / 65535.0 * 3300; // read the voltage
  // ARRONDI AVEC 1 DECIMAL 
  voltagePH = (round(voltagePH * 10));
  voltagePH = voltagePH / 10;

  // CALCULATE PH VALUE
  phValue = ph.readPH(voltagePH, temperature); // convert voltage to pH with temperature compensation
  // ARRONDI AVEC 1 DECIMAL 
  phValue = (round(phValue * 10));
  phValue = phValue / 10;
//---------------------------------------------------------
//                     Turbidity
//---------------------------------------------------------
  // READ TURB VOLT
  voltageTurb = (analogRead(TURBPINSENSOR) / 65535.0 * 3300);
  // ARRONDI AVEC 1 DECIMAL 
  voltageTurb = (round(voltageTurb * 10));
  voltageTurb = voltageTurb / 10;

  // CALCULATE TURB VALUE
  // Please that voltage needs to be in Volts to integrate the formula
  turbidity = ((voltageTurb/1000 - 2.128)/-0.7021)*1000;
  // Precize value with offset calculated with scientist per briefcase
  turbidity =  0.1563 * turbidity + 366.99;
  // ARRONDI AVEC 1 DECIMAL
  turbidity = (round(turbidity * 10));
  turbidity = turbidity / 10;
//---------------------------------------------------------
//                        EC
//---------------------------------------------------------
  // READ EC VOLT
  voltageEC = analogRead(ECPIN) / 65535.0 * 3300;
  // ARRONDI AVEC 1 DECIMAL
  voltageEC = (round(voltageEC * 10));
  voltageEC = voltageEC / 10;

  // CALCULATE EC VALUE
  ecValue    = ec.readEC(voltageEC, temperature);      // convert voltage to EC with temperature compensation
  ecValue = ecValue * 1000;
  //  ARRONDI AVEC 0 decimal
  ecValue = (round(ecValue * 1));

//---------------------------------------------------------
//                        JSON
//---------------------------------------------------------

  send_json();

}


void  send_json() {
  //float phValue, temperature, turbidity, turbidityNTU, ec;
  DynamicJsonDocument doc(256);
  doc["from"] = "Teensy";
  JsonObject sensors = doc.createNestedObject("sensors");
  sensors["temperature"] = temperature;
  sensors["ph"] = phValue;
  sensors["ph_voltage"] = voltagePH;
  sensors["ec"] = ecValue;
  sensors["ec_voltage"] = voltageEC;
  sensors["turbidity"] = turbidity;
  sensors["turb_voltage"] = voltageTurb;
  unsigned long Time = Teensy3Clock.get();
  sensors["time"]= Time;

  serializeJson(doc, Serial);
  Serial.println();



}

//---------------------------------------------------------
//                        TIME FEATURES
//---------------------------------------------------------

void displayTeensyTime() {
  if (Serial.available()) {
    time_t t = processSyncMessage();
    if (t != 0) {
      Teensy3Clock.set(t); // set the RTC
      setTime(t);
    }
  }
  digitalClockDisplay();  
  delay(1000);
}
void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

/*  code to process time sync messages from the serial port   */
#define TIME_HEADER  "T"   // Header tag for serial time sync message

unsigned long processSyncMessage() {
  unsigned long pctime = 0L;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013 

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     return pctime;
     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
       pctime = 0L; // return 0 to indicate that the time is not valid
     }
  }
  return pctime;
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

float readTemperature()
{
  //add your code here to get the temperature from your temperature sensor
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) {
    //no more sensors on chain, reset search
    ds.reset_search();
    return -1000;
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) {
    Serial.println("CRC is not valid!");
    return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) {
    Serial.print("Device is not recognized");
    return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1); // start conversion, with parasite power on at the end

  byte present = ds.reset();
  ds.select(addr);
  ds.write(0xBE); // Read Scratchpad


  for (int i = 0; i < 9; i++) { // we need 9 bytes
    data[i] = ds.read();
  }

  ds.reset_search();

  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //using two's compliment
  float TemperatureSum = tempRead / 16;

  return TemperatureSum;
}
