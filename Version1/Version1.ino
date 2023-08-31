//DEPENDENCIES
#include <CheckDS18B20.h>
#include <DiscoverFakeDS18B20.h>
#include <DallasTemperature.h>
#include <OneWire.h>

//This is a blinking Program. We have to build a program that runs a buzzer for high and low temperature detection, one DS18B20 thermometer Probes, 3 lights for temperature checking
//Version 1 is for a low budget project
//Version 2 will have a buzzer for high and low temperature detection, two thermometer probes (average temperature will be calculated), 3 lights for temperature checking and 1 LCD display to show current temperature reading.


//                                                 CONNECTIONS
//      CONNECTING THE TEMPERATURE SENSOR
//         1. Connect one 4.7k ohm resistor from the power(5V) line to the data line of the temperature probe. 
//         2. Connect the Drain and Power lines of the sensor to the 5V and GND pins in the arduino respectively
//         3. Data line for the sensor is at Digital 30 of the arduino.
//         4. Connect the Data pin of the sensor to Digital pin 30 of the arduino mega and make sure that power passes through the line without running through the 4.7k ohm resistor.

//      CONNECTING THE LEDS FOR TEMPERATURE
//         1. Ensure all LEDs are connected to a resistor of lower resistance(around 0.5 to 1k ohm)
//         2. Connect the Blue LED to digital pin 24
//         3. Connect the Green LED to digital pin 25
//         4. Connect the Red LED to digital pin 26

//      CONNECTING THE BUZZER
//         1. Ensure that Buzzer passes through a resistance similar to that of an LED.
//         2. Connect the Buzzer to digital pin 22

//Data wire for communication with the temperature sensor
#define ONE_WIRE_BUS 30

//Setting up a oneWire instance to communicate with any OneWire Device
OneWire oneWire(ONE_WIRE_BUS);

//Passing oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

//Variables
float idealT_C = 30;
int tolerance_C = 1;
float Temp_C;
float Time_operational_hours;     //Required Time is entered in this variable
float total_time_operational;     //T1 + T2 is added to this constantly for calculation

void setup() {
  
  //Digital Pins for Arduino Mega
  //The Termperature sensor is working in non-parasite mode.
  
  //Start serial communication for debugging purposes
  Serial.begin(9600);
  //Starting the library
  sensors.begin();

  pinMode(22, OUTPUT);     //Pin for Buzzer
  pinMode(24, OUTPUT);     //Pin for Blue  LED
  pinMode(25, OUTPUT);     //Pin for Green LED
  pinMode(26, OUTPUT);     //Pin for Red   LED
}

int counter(float A, float B){
  A = A/3600000;           //Conversion to Hours
  B = B/3600000;           //Conversion to Hours
  total_time_operational = A+B;
  if(total_time_operational >= Time_operational_hours)
    digitalWrite(22, HIGH); 
}
  
void loop() {  

  //Calling sensors.requestTemperatures() to issue a global temperature  
  sensors.requestTemperatures();              
  Serial.print("Celsius temperature: ");
  // byIndex(0) means it refers to the first sensor in the bus because we could have several sensors in the IC bus.
  Serial.print(sensors.getTempCByIndex(0)); 
  Serial.print(" - Fahrenheit temperature: ");
  Serial.println(sensors.getTempFByIndex(0));
  Serial.print("\nTime in temperature (hours): ");
  Serial.println(total_time_operational);
  Serial.print("\nTime in temperature (Minutes): ");
  Serial.println(total_time_operational*60);
  delay(1000);

  //Grabbing the temperatures to separate values
  Temp_C = sensors.getTempCByIndex(0);

  if(Temp_C < idealT_C - tolerance_C)
  {
    digitalWrite(24, HIGH); 
    digitalWrite(22, HIGH); 
    delay(200);                      
    digitalWrite(24, LOW);  
    digitalWrite(22, LOW);
    delay(200);
  }
  else if(Temp_C >= (idealT_C - tolerance_C) && Temp_C <= (idealT_C + tolerance_C))
  {
    T1 = millis();
    digitalWrite(25, HIGH); 
    delay(1000);                      
    digitalWrite(25, LOW);  
    delay(100);
    T2 = millis();
    counter(T1,T2);
  }
  else 
  {
    digitalWrite(26, HIGH);
    digitalWrite(22, HIGH);
    delay(200);                      
    digitalWrite(26, LOW); 
    digitalWrite(22, LOW); 
    delay(200);
  }
}
