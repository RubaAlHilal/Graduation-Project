#include "DHT.h"

#define DHTPIN 3                   // Temperature and Humidity Sensor
#define DHTTYPE DHT11             // obj for sensor DHT11

DHT dht(DHTPIN, DHTTYPE);

int soilMoistureValue = 0;
int percentage=0;

#define LIGHT A3 // define pint 2 for sensor
#define RELAY 4 // define pin 9 as for relay

boolean digital = false;// set true to use digital and control the sensitiviety with poentiometer on the module
                  // set to false to control with A3 value on Arduino
unsigned int LightValue = 350;// LightValue to determine
                      // at what value the realy should be ON   

void setup() {
 pinMode(A2,INPUT_PULLUP);
 pinMode(5,OUTPUT);

 dht.begin();

 pinMode(LIGHT, INPUT_PULLUP);// define pin as Input  sensor
 pinMode(RELAY, OUTPUT);// define pin as OUTPUT for relay

 Serial.begin(9600);// setup Serial Monitor to display information
}

void loop() {
  
  readDHT();

  relay();// call the realay() method

  soilMoistureValue = analogRead(A1);
  Serial.print(percentage);
  Serial.print("% ,");
   
  delay(500);

  percentage = map(soilMoistureValue, 490, 1023, 100, 0); //(sensor value , min value , max value , )

  if(percentage < 10 ){
    if (digitalRead(A2)== HIGH){
  
    Serial.print(" pump on ,");
    digitalWrite(5,LOW);
    
    Serial.println("High level of Water.");
    while(digitalRead(A2)== HIGH){}   //check water level is high
    

  } else {
    if (digitalRead(A2)== LOW){
    Serial.print("pump off ,");
    digitalWrite(5,HIGH);

    Serial.println("Low level of Water.");
    while(digitalRead(A2)== LOW) {}
    
    } 
 }}

  if (percentage >80 ){
    if (digitalRead(A2)== HIGH){
    Serial.print("pump off ,");
    digitalWrite(5,HIGH);

    Serial.println("High level of Water.");
    while(digitalRead(A2)== HIGH){}
    

  } else {
    if (digitalRead(A2)== LOW){
    Serial.print("pump off ,");
    digitalWrite(5,HIGH);

    Serial.println("Low level of Water.");
    while(digitalRead(A2)== LOW) {}
  


    }}
}} 

float readDHT(){
                              // wait 2 second
    float t = dht.readTemperature();        // Gets the values of the temperature
    float h = dht.readHumidity();           // Gets the values of the humidity

    // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
    }

  Serial.print("Room Temperature: ");
  Serial.print(t);
  Serial.print("C, ");
  Serial.print("Room Humidity: ");
  Serial.print(h);
  Serial.println("% ");

  }

  void relay()
{
   if(digital == true)
   {
  // Light LDR Sensor Code by Robojax.com 20180210
  int L =digitalRead(LIGHT);// read the sensor 
  
      if(L == 1){
        Serial.println(" light is ON");
        digitalWrite(RELAY,HIGH);// turn the relay ON
      }else{
         Serial.println("light is OFF");
         digitalWrite(RELAY,LOW);// turn the relay OFF
      } // if   
   }// if digital end
   else
   {
    int a3Value = analogRead(A3);// read A0 value
    
      if( a3Value >= LightValue){
        Serial.print(analogRead(A3));
        Serial.println(" Light is ON");
        digitalWrite(RELAY,HIGH);// turn the relay ON
      }else{
         Serial.print(analogRead(A3));
         Serial.println("  === light OFF");
         digitalWrite(RELAY,LOW);// turn the relay OFF
      } // if      
   }
}