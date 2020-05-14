#include <LiquidCrystal.h>
//rs,enable,d4,d5,d6,d7
LiquidCrystal lcd(12,11,5,4,3,2);
#define DHTPIN 6
#define DHTTYPE DHT11
#include<DHT.h>
#define trig1 8
#define echo1 7
#define piezo 9
DHT dht(DHTPIN, DHTTYPE);
int sensor_pin = A0;   // soil pins
int output_value;
int pumpPin= A3;
unsigned long durationo;
int distanceo;
  

void setup() {                          //void setup
pinMode(pumpPin, OUTPUT);  //pump pin
   Serial.begin(9600);
dht.begin();
pinMode(echo1,INPUT);
  digitalWrite(trig1,LOW);
pinMode(trig1,OUTPUT);
 lcd.begin(16,2);
}

void loop() {                     //void loop
  digitalWrite(trig1,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1,LOW);
  output_value= analogRead(sensor_pin);             //soil part
  output_value = map(output_value,1023,260,0,100);
 if(output_value < 40){
   digitalWrite(pumpPin,HIGH);
}
 if(output_value > 40){
  digitalWrite(pumpPin,LOW);
}
delay(1000);                 //end of soil part
 
lcd.setCursor(0,2);        
lcd.print("moisture=");
lcd.print(output_value);
lcd.print("%");  
delay(1000);                    //dth11  start
float h = dht.readHumidity();
float t = dht.readTemperature();
lcd.setCursor(0,0);
lcd.print("t=");
lcd.print(t);
lcd.setCursor(7,0);
lcd.print(" h=");
lcd.print(h);
lcd.print("%");            //dth end

Serial.print("soil moisture="); //serial print
Serial.print(output_value);
Serial.println("%");
Serial.print("temp=");
Serial.println(t);
Serial.print("humidity=");
Serial.print(h);
Serial.println("%");
Serial.println("----------------------------");
   
}
