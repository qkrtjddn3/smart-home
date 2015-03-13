#include "DHT.h"
#include<SoftwareSerial.h> //bluetooth uart

//////What arduino's pin we're connected to
//digital pin
#define DHT_PIN 5
#define BL_UART_PIN1 6
#define BL_UART_PIN2 7
#define LED1_PIN 10    //dining room
#define LED2_PIN 11    //bath room
#define LED3_PIN 12    //working room
#define LED4_PIN 13    //living room
//analog pin
#define PRES1_PIN A0
#define PRES2_PIN A1
#define ILUM1_PIN A2
#define ILUM2_PIN A3
#define ILUM3_PIN A4
#define ILUM4_PIN A5

//Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22 (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHT_PIN, DHTTYPE);
SoftwareSerial blueSerial(BL_UART_PIN1, BL_UART_PIN2);   //bluetooth uart
//SoftwareSerial beatSerial(6,7);

//////Initialize variables
int timeCount = 0;
int aircon1_on_off = 0;
//int aircon2_on_off = 0;
int led1_on_off = 0;
int led2_on_off = 0;
int led3_on_off = 0;
int led4_on_off = 0;
int led1_state = HIGH;
int led2_state = HIGH;
int led3_state = HIGH;
int led4_state = HIGH;

void setup() {
  //////Arduino's pin config
  pinMode(LED1_PIN, INPUT);
  pinMode(LED2_PIN, INPUT);
  pinMode(LED3_PIN, INPUT);
  pinMode(LED4_PIN, INPUT);
  
  //////Begins
  Serial.begin(9600); 
  Serial.println("DHTxx test!");
  blueSerial.begin(9600);    //if rp speed 38400
  //beatSerial.begin(115200);
  dht.begin();
}

void loop() {
  //////Loop delay config
  delay(10);  //Wait a few seconds between measurements.
  timeCount++;  //Time calc
  
  ///////////////////////////
  //Sensor's values read part
  ///////////////////////////
  int led_button1 = digitalRead(LED1_PIN);    //dining
  int led_button2 = digitalRead(LED2_PIN);    //bath
  int led_button3 = digitalRead(LED3_PIN);    //working
  int led_button4 = digitalRead(LED4_PIN);    //living
  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();  //Read humidity
  float t = dht.readTemperature();  // Read temperature as Celsius
  float f = dht.readTemperature(true);  // Read temperature as Fahrenheit
  
  int presureValue1 = analogRead(PRES1_PIN);
  //int presureValue2 = analogRead(PRES2_PIN);
  int ilumValue1 = analogRead(ILUM1_PIN);
  //int ilumValue2 = analogRead(ILUM2_PIN);
  //int ilumValue3 = analogRead(ILUM3_PIN);
  //int ilumValue4 = analogRead(ILUM4_PIN);
  
  ///////////////////////////////////////
  //LED on/off Check & Transfer data part
  ///////////////////////////////////////
  //////dining room
  if(led_button1 == HIGH && led1_state == LOW) {      
    led1_state = HIGH;
    Serial.print("a/led1_dining/");
    Serial.println(0);
    blueSerial.print("a/dining/");
    blueSerial.println(0);
  } 
  else if(led_button1 == LOW && led1_state == HIGH){
    led1_state = LOW;
    Serial.print("a/led1_dining/");
    Serial.println(1);
    blueSerial.print("a/dining/");
    blueSerial.println(1);
  }
  //////bath room
  if(led_button2 == HIGH && led2_state == LOW) {        
    led2_state = HIGH;
    Serial.print("a/led2_bath/");
    Serial.println(0);
    blueSerial.print("a/bath/");
    blueSerial.println(0);
  } 
  else if(led_button2 == LOW && led2_state == HIGH){
    led2_state = LOW;
    Serial.print("a/led2_bath/");
    Serial.println(1);
    blueSerial.print("a/bath/");
    blueSerial.println(1);
  }
  //////working room
  if(led_button3 == HIGH && led3_state == LOW) {     
    led3_state = HIGH;
    Serial.print("a/led3_working/");
    Serial.println(0);
    blueSerial.print("a/working/");
    blueSerial.println(0);
  } 
  else if(led_button3 == LOW && led3_state == HIGH){
    led3_state = LOW;
    Serial.print("a/led3_working/");
    Serial.println(1);
    blueSerial.print("a/working/");
    blueSerial.println(1);
  }
  //////living room
  if(led_button4 == HIGH && led4_state == LOW) {     
    led4_state = HIGH;
    Serial.print("a/led4_living/");
    Serial.println(0);
    blueSerial.print("a/living/");
    blueSerial.println(0);
  } 
  else if(led_button4 == LOW && led4_state == HIGH){
    led4_state = LOW;
    Serial.print("a/led4_living/");
    Serial.println(1);
    blueSerial.print("a/living/");
    blueSerial.println(1);
  }
  
  //////////////////////////////////////////
  //Aircon on/off Check & Transfer data part
  //////////////////////////////////////////
  /*
  if(presureValue1 > 50){
    if(aircon1_on_off){
      aircon1_on_off = 0;
      blueSerial.print("a/aircon/");
      blueSerial.println(aircon1_on_off);
      Serial.print("a/aircon/");
      Serial.println(aircon1_on_off);
      Serial.println(presureValue1);
      timeCount += 50;
      delay(500);
    }
    else{
      aircon1_on_off = 1;
      blueSerial.print("a/aircon/");
      blueSerial.println(aircon1_on_off);
      Serial.print("a/aircon/");
      Serial.println(aircon1_on_off);
      Serial.println(presureValue1);
      timeCount += 50;
      delay(500);
    }
  }
  */
  
  /////////////////////////////////////////////////////////////
  //User status data part
  /////////////////////////////////////////////////////////////
  // Compute heat index
  // Must send in temp in Fahrenheit
  float hi = dht.computeHeatIndex(f, h);
  
  /////////////////////////////////////////////////////////////
  //Environment data are transferred to server every 10sec part
  /////////////////////////////////////////////////////////////
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
    //If this program is terminated here, followed code are ignored.
  }
  
  if(timeCount >= 1000){
    timeCount = 0;
    blueSerial.print("e/");    
    blueSerial.print(t);
    blueSerial.print("/");
    blueSerial.print(h);
    blueSerial.print("/");
    blueSerial.println(ilumValue1);
  
    Serial.print("e/");
    Serial.print(t);
    Serial.print("/"); 
    Serial.print(h);
    Serial.print("/");
    Serial.println(ilumValue1);
  }
}
