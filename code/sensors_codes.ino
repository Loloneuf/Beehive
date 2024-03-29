sensors codes :


#include "DHT.h"
#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>

// include the DHT22 Sensor Library
#include "DHT.h"

//The HX711 board can be powered from 2.7V to 5V so the Arduino 5V power should be fine.


#include "HX711.h"
#include <OneWire.h>
#include <DallasTemperature.h>
// #include "Adafruit_Si7021.h"

#define DHTPIN 8 // Hum_Temp sensor
#define DHTTYPE DHT22 
#define ONE_WIRE_BUS 7 // Temp sensor
#define DOUT  3 // Weight sensor
#define CLK  4 // Weight sensor

#define calibration_factor -7050.00 //This value is obtained using the SparkFun_HX711_Calibration sketch


//Adafruit_Si7021 sensor = Adafruit_Si7021();

DHT dht(DHTPIN, DHTTYPE);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
HX711 scale(DOUT, CLK);

int temp_sensor = 7;       // Pin DS18B20 Sensor is connected to
float temperature = 0;      //Variable to store the temperature in
float weight;
float h;
float t;

int counter = 1;
float summW = 0;
float averageW;
float summT = 0;
float averageT;


void setup() {
  Serial.begin(9600);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  Serial.println("Readings:");
  sensors.begin();
  dht.begin();
}
void loop() {
  h = dht.readHumidity();//on lit l'hydrometrie
  t = dht.readTemperature();//on lit la temperature en celsius (par defaut)
  sensors.requestTemperatures(); 
  temperature = sensors.getTempCByIndex(0); //gets the temp data
  weight = scale.get_units()*.45;
  Serial.print("------------");
  Serial.println();
  Serial.print(weight, 1); //scale.get_units() returns a float
  Serial.print(" kgs"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();
  Serial.print(temperature);
  Serial.print(" degrees Celsius"); //printing temperature from DHT sensor
  Serial.println();
  Serial.print(t, 2);
  Serial.print(" degrees Celsius"); //printing temperature from DHT sensor
  Serial.println();
  Serial.print(h, 2); //printing_humidity
  Serial.println(" % humidity");
  Serial.println();
 
  //summW += weight;
  //averageW = summW/counter; 
  //Serial.print(averageW);
  //Serial.println(" Kgs average ");
 
  //summT += temperature;
  //averageT = summT/counter;
  //Serial.print(averageT);
  //Serial.println(" °C average ");

  //Serial.print("counter ");
  //Serial.print(counter);
  //Serial.println();
  //counter += 1;
  
  delay(1000);
  
  //if (counter == 11) {
  //  counter = 1;
  //  summW = 0;
  //  summT = 0;

 // }
}
