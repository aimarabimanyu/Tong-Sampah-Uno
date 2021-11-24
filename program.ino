//Import Library
#include <NewPing.h>
#include <Servo.h> 
#include <LiquidCrystal_I2C.h>

//Define & SetUp Sensor Luar
#define trigg_pin 4
#define echo_pin 3
#define max_distance 350
NewPing sensorLuar(trigg_pin, echo_pin, max_distance);
float duration, distance;

//Define & SetUp Servo Motor
Servo servoSampah;

//Define & SetUp LCD
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,16,2);

const byte interruptPin = 2;

void setup() 
{
  servoSampah.attach(5);
  servoSampah.write(0);

  lcd.init();
  lcd.backlight();

  Serial.begin(9600);
  //pinMode(interruptPin, INPUT_PULLUP);
}

void loop() 
{
  duration = sensorLuar.ping();
  int test = trigg_pin;
  distance = (duration / 2) * 0.0343;

  if(distance<=10)
  {
    servoSampah.write(180);
  }
  else
  {
    servoSampah.write(0);
  }

  Serial.println(test);
  delay(50);
}

void LCD() 
{
  lcd.clear();
  lcd.setCursor(0, 0); //set kolom dan baris
  lcd.print("TEST");
}
