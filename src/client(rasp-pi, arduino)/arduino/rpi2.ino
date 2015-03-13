// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h" // 온습
#include<SoftwareSerial.h> // bluetooth uart

#define DHTPIN 5     // what pin we're connected to

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT11   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial mySerial(6,7); //bluetooth uart
//SoftwareSerial beatSerial(6,7);
int pres_on_off=0;
int light_on_off=0;
int count=0;
int led1 = 10;
int state=HIGH;

void setup() {
  Serial.begin(9600); 
  Serial.println("DHTxx test!");
  mySerial.begin(9600); // bluetooth
  //if rp speed 38400
  //beatSerial.begin(115200);
  pinMode(led1, INPUT);
 
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(10);
  count++; //time 10sec calc

  
  int sensorValue = analogRead(A0); // lightvalue
  int presureValue = analogRead(A1);
//  int light1 = analogRead(A2);
  int l_button_1 = digitalRead(led1);
  //Serial.println(buttonState);
  
  if (l_button_1==HIGH && state==LOW) {     
    // turn LED of:    
    state = HIGH;
    Serial.print("a/led1/");
    Serial.println(0);
    mySerial.print("a/led1/");
    mySerial.println(0);
  } 
  else if(l_button_1==LOW && state ==HIGH){
    // turn LED on:
    state = LOW;
    Serial.print("a/led1/");
    Serial.println(1);
    mySerial.print("a/led1/");
    mySerial.println(1);
    
  }
  
  
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index
  // Must send in temp in Fahrenheit!z
  float hi = dht.computeHeatIndex(f, h);
  
  //transfer aircon_on_off
  if(presureValue>50){
    if(pres_on_off){
      pres_on_off=0;
      //bluetooth to pi
      mySerial.print("a/aircon/");
      mySerial.println(pres_on_off);
      
      
      //from port
      Serial.print("a/aircon/");
      Serial.println(pres_on_off);
      Serial.println(presureValue);
    
      count=+50;
      delay(500);
    }
    else{
      pres_on_off=1;
      
      mySerial.print("a/aircon/");
      mySerial.println(pres_on_off);
      
      Serial.print("a/aircon/");
      Serial.println(pres_on_off);
      Serial.println(presureValue);
      
      
      count=+50;
      delay(500);
    }
  }
  //transfer every 10sec
  if(count>=1000){
    count=0;
    //mySerial.print("Humidity: "); 
    mySerial.print("e/");    
    mySerial.print(t);
    mySerial.print("/");
    //mySerial.print(" %\t");
    //mySerial.print("Temperature: "); 
    mySerial.print(h);
    mySerial.print("/");
    //mySerial.print(" *C ");
    //cmySerial.print(f);
    //mySerial.print(" *F\t");
    //mySerial.print("Heat index: ");
    //mySerial.print(hi);
    //mySerial.println(" *F");
    mySerial.println(sensorValue);
  
    Serial.print("e/");
    //Serial.print("Humidity: "); 
    Serial.print(t);
    Serial.print("/");
    //Serial.print(" %\t");
    //Serial.print("Temperature: "); 
    Serial.print(h);
    Serial.print("/");
    //Serial.print(" *C ");
    //Serial.print(f);
    //Serial.print(" *F\t");
    //Serial.print("Heat index: ");
    //Serial.print(hi);
    //Serial.println(" *F");
    //Serial.print("lux :");
    /*
    if(sensorValue>190){
      Serial.print("on");
      Serial.print("/");
    }
    else{
       Serial.print("off");
      Serial.print("/");
    }
    */
    
    Serial.println(sensorValue);
    //Serial.print(beatSerial.read());
    //Serial.print("/");
    
    
  }
  
  
}
