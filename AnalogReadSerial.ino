#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>
#include <SimpleDHT.h>
#include <Wire.h>

//LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
LiquidCrystal_I2C lcd(0x27, 20, 4);
// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int mudao = A1;
int muddo = 7;
int pinDHT11 = 2;
int shit = A0;
int ledState = 0;
int turd = 0;
int pump = 9;
int water = 0;
unsigned long watert; 
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(60,5,NEO_GRB + NEO_KHZ800);
SimpleDHT11 dht11(pinDHT11);

void setup() {
  pixels.begin();
  pixels.setBrightness(100);
  pinMode(mudao, INPUT);
  pinMode(muddo, INPUT);
  pinMode(pump,OUTPUT);
  watert = millis();
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
}

void loop() {
  int light = analogRead(shit);
  int mo = analogRead(mudao);
  char c[20];
  Serial.println("=================================");
  Serial.println(light);
  Serial.println("Sample DHT11...");
  Serial.print("Moisture=");
  Serial.print(mo);
  Serial.print("|DO=");
  Serial.println(digitalRead(muddo));

  if( light < 300 ){
    turd = 300 - light;
    if ( turd > 255 )
      turd = 255;
  }
  if( light > 300 ){
    turd = 0;
  }
  for ( int i = 0; i <= 59; i++ ) {
    pixels.setPixelColor(i, pixels.Color(turd, turd, turd));
  }
  pixels.show();
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");
  Serial.println(turd);
  lcd.setCursor(0, 0);
  sprintf(c, "Light: %4d", light);
  lcd.print(c);
  lcd.setCursor(0, 1);
  sprintf(c, "Temp : %4d", temperature);
  lcd.print(c);
  lcd.setCursor(0, 2);
  sprintf(c, "Humid: %4d", humidity);
  lcd.print(c);
  lcd.setCursor(0, 3);
  sprintf(c, "MudMo: %4d", mo);
  lcd.print(c);
  if( mo > 1000 && water == 0 && millis() - watert > 10000) {
    digitalWrite(pump,HIGH);
    water = 1;
    watert = millis();
  } else if (water == 1 && millis() - watert > 10000) {
    digitalWrite(pump,LOW);
    water = 0;
    watert = millis();
  }
  delay(5000);
}
