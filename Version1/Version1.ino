//This is a blinking Program. We have to build a program that runs a buzzer for high and low temperature detection, one DS18B20 thermometer Probes, 3 lights for temperature checking
//Version 1 is for a low budget project
//Version 2 will have a buzzer for high and low temperature detection, two thermometer probes (average temperature will be calculated), 3 lights for temperature checking and 1 LCD display to show current temperature reading.


//                                                 CONNECTIONS
//      CONNECTING THE TEMPERATURE SENSOR
//         1. Connect one 4.7k ohm resistor from the power(5V) line to the data line of the temperature probe. 
//         2. Connect the Drain and Power lines of the sensor to the 5V and GND pins in the arduino respectively
//         3. Data line for the sensor is at Digital 30 of the arduino.
//         4. Connect the Data pin of the sensor to Digital pin 30 of the arduino mega and make sure that power passes through the line without running through the 4.7k ohm resistor.

void setup() {
  //Digital Pins for Arduino Mega
  //The Termperature sensor is working in non-parasite mode.
  
  pinMode(22, OUTPUT);     //Pin for Buzzer
  pinMode(24, OUTPUT);     //Pin for Blue  LED
  pinMode(25, OUTPUT);     //Pin for Green LED
  pinMode(26, OUTPUT);     //Pin for Red   LED
  pinMode(30, INPUT);      //Pin for Input for DS18B20
}

void loop() {
  //Beeping the buzzer
  digitalWrite(22, HIGH);  
  delay(1000);                      
  digitalWrite(22, LOW);  
  delay(1000);                      
}
