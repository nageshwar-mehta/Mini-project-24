#include "Servo.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal_I2C.h>

#define IR1 0x5A

Servo myservo;
Adafruit_MLX90614 mlx1 = Adafruit_MLX90614();
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {

  Serial.begin(9600);
  Serial.println("Adafruit MLX90614 test");  

  mlx1.begin(IR1); 

  lcd.init();
  lcd.clear();
  lcd.backlight();

  myservo.attach(9);
  myservo.write(180);

}

float temp1 = 0;
float temp2 = 0;
float temp3 = 0;
float CWSI = 0;

void loop() {

  delay(1000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PoSDePS");

  myservo.write(180);
  delay(2000);
  temp3 = mlx1.readObjectTempC();

  myservo.write(80);
  delay(2000);
  temp2 = mlx1.readObjectTempC();


  myservo.write(0);
  delay(2000);
  temp1 = mlx1.readObjectTempC();

  CWSI = (temp1 - temp2)/(temp3 - temp2);
  Serial.print("Leaf: ");
  Serial.println(temp1);
  Serial.print("Wet: ");
  Serial.println(temp2);
  Serial.print("Dry: ");
  Serial.println(temp3);

  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("CWSI: ");
  lcd.setCursor(2,1);
  lcd.print(CWSI);

}