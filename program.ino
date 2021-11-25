//Import Library
#include <NewPing.h>
#include <Servo.h> 
#include <LiquidCrystal_I2C.h>

//Define or SetUp Sensor Luar
#define trigg_pin1 4
#define echo_pin1 3
#define max_distance 200
NewPing sensorLuar(trigg_pin1, echo_pin1, max_distance);
float durationS1, distanceS1;

//Define or SetUp Sensor Dalam
#define trigg_pin2 9
#define echo_pin2 8
NewPing sensorDalam(trigg_pin2, echo_pin2, max_distance);
float durationS2;
int distanceS2;

//Define or SetUp Servo Motor
Servo servoSampah;

//Define or SetUp LCD
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,16,2);

//Define or SetUp Timer/Counter & Interrupt
#define INT0 2


void setup() 
{
  //Inisialisasi Servo
  servoSampah.attach(5);
  servoSampah.write(0);

  //Inisialisasi Interrupt
  pinMode(INT0, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), manual, RISING);
  
  //Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("TongSampah");
  lcd.setCursor(4, 1);
  lcd.print("Otomatis");
  delay(3000);
  lcd.clear();
}

void loop() 
{
  // Deteksi Jarak Dari Kedua Sensor
  durationS1 = sensorLuar.ping();
  distanceS1 = (durationS1 / 2) * 0.0343;

  durationS2 = sensorDalam.ping();
  distanceS2 = (((((durationS2 / 2) * 0.0343)-10)/30)*100); //asumsi tinggi tong sampah 30 cm
  
  if (distanceS2 <= 10) //asumsi tinggi tong sampah 30 cm
  {
    lcd.setCursor(3, 0);
    lcd.print("Tong Sampah");
    lcd.setCursor(6, 1);
    lcd.print("Penuh");
    distanceS1 = -1;
  }
  else if (distanceS2 > 10) 
  {
    lcd.setCursor(3, 0);
    lcd.print("Kapasitas:");
    lcd.setCursor(6, 1);
    lcd.print(distanceS2);
    lcd.print("%");
  }
  
  // Jika Sensor Mendeteksi Orang Mendekati Tong Sampah dan Menjauhi Tong Sampah
  if(distanceS1<=10 && distanceS1>=0)
  {
    servoSampah.write(180);
    delay(4000);
  }
  else
  {
    servoSampah.write(0);
  }
  delay(50);
}

void manual() 
{
  servoSampah.write(180);
  delay(5000);
  servoSampah.write(0);
}
