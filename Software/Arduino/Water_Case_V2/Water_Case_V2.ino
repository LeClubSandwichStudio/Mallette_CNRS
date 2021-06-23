//////////////////////////////////////////////////
//                  Wiring
/////////////////////////////////////////////////
/*
 
GND ->GND 
VCC:
  EC and PH:                  VCC to VIN (closest pin to usb connector in the corner)
  Temperature and turbidity:  VCC to 3.3v (third pin from the usb connector, same side as VIN)
Signal wire:
  EC          -> 14 (A0)
  Tunbidity   -> 15 (A1)
  Temperature -> 33 (A14)
  PH          -> 35 (A16)
 */




//////////////////////////////////////////////////
//                  Commands
/////////////////////////////////////////////////
/*
  {"command":"start"}
  {"command":"stop"}
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



//////////////////////////////////////////////////
//                Declarations
/////////////////////////////////////////////////
void measure_sensors();
OneWire ds(TEMPPIN);
float phValue, temperature, turbidity, turbidityNTU, ecValue;
DFRobot_PH ph;
DFRobot_EC ec;
Korzhenevskiy_tick_tack_2 sensor_timer(measure_sensors, 1000);
DynamicJsonDocument doc(256);



//////////////////////////////////////////////////
//                   setup
/////////////////////////////////////////////////
void setup() {
  //sensor_timer.start();
  Serial.begin(9600);
  ph.begin();
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
//---------------------------------------------------------
//                  Temperature
//---------------------------------------------------------
  temperature = readTemperature();        
  temperature = (round(temperature * 10));
  temperature = temperature / 10;
  //float _temperature=temperature*10;
  //_temperature=round(_temperature);
  //temperature=_temperature/10;


//---------------------------------------------------------
//                          PH
//---------------------------------------------------------
  //Serial.print("analogread : ");
  //Serial.print(analogRead(PHPIN));
  float voltage;
  voltage = analogRead(PHPIN) / 1024.0 * 3300; // read the voltage
  //Serial.print("   voltage: ");
  //Serial.print(voltage);
  phValue = ph.readPH(voltage, temperature); // convert voltage to pH with temperature compensation
  phValue = (round(phValue * 100));
  phValue = phValue / 100;
  //Serial.print("   temperature:");
  //Serial.print(temperature, 1);
  //Serial.print("^C  pH:");
  //Serial.println(phValue, 2);

//---------------------------------------------------------
//                     Turbidity
//---------------------------------------------------------
  voltage = analogRead(TURBPINSENSOR) / 1024.0 * 3300;
  //turbidity = map(voltage, 0, 3300, 0, 100);
  turbidity = round(voltage);
  // Serial.print("turbidity:");
  //Serial.print(turbidity, 1);
  //Serial.println("mv");

//---------------------------------------------------------
//                        EC
//---------------------------------------------------------
  float voltageEC = analogRead(ECPIN) / 1024.0 * 3300;
  //Serial.print("EC voltage:");
  //Serial.println(voltageEC/1000);
  
  ecValue    = ec.readEC(voltageEC, temperature);      // convert voltage to EC with temperature compensation
  ecValue = (round(ecValue * 10));
  ecValue = ecValue / 10;
  //Serial.print("EC:");
  //Serial.print(ecValue);
  //Serial.println("ms/cm");



  send_json();

}


void  send_json() {
  //float phValue, temperature, turbidity, turbidityNTU, ec;
  DynamicJsonDocument doc(256);
  doc["from"] = "Teensy";
  JsonObject sensors = doc.createNestedObject("sensors");
  sensors["temperature"] = temperature;
  sensors["ph"] = phValue;
  sensors["turbidity"] = turbidity;
  sensors["ec"] = ecValue;
  unsigned long Time = Teensy3Clock.get();
  sensors["time"]= Time;

  serializeJson(doc, Serial);
  Serial.println();



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
