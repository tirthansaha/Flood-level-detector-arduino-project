#include <LiquidCrystal_I2C.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_BMP085.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
int buzzerPin = 8;
int distCM;
const  int trigger=6; // Ultrasonic Sensor pin
const  int echo=7; // Ultrasonic Sensor  pin
float  distance; // Ultrasonic Sensor 
float dist_inches; // Ultrasonic Sensor 

Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(9600);
  pinMode(buzzerPin, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.clear();

  pinMode(trigger,OUTPUT);
  pinMode(echo,INPUT);

  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP180 sensor, check wiring!");
    while (1) {}
    } 
    float a = bmp.readPressure();
    if (a>100850){
    lcd.setCursor(0,1);
    lcd.print(a);
    lcd.print("Pa");
    Serial.print("a");
  }
}
void loop() {
  char status;
  int value = analogRead(A0);
  digitalWrite(trigger,LOW);
  delayMicroseconds(5);
  digitalWrite(trigger,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger,LOW);
  distance=pulseIn(echo,HIGH);
  distCM=distance*0.034/2;
  Serial.println(distCM);
  //lcd.setCursor(0, 1);

  if (0 <= value && value  <= 50) {
    lcd.setCursor(0, 0);
    lcd.print("No Flood");
    digitalWrite(buzzerPin, LOW);
  } else if (value > 51 && value < 500) {
    lcd.setCursor(0, 0);
    lcd.print("FLOOD RISING  ");
    digitalWrite(buzzerPin, HIGH);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Rise: ");
    lcd.print(distCM);
    lcd.print("cm"); 
  } else if (value > 501){
    lcd.setCursor(0, 0);
    lcd.print("FLOOD HIGH  ");
    digitalWrite(buzzerPin, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("Rise: ");
    lcd.print(distCM);
    lcd.print("cm");  
  }  
}
