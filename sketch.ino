#include <Wire.h>  
#include <LiquidCrystal_I2C.h>  
#include <Servo.h>

       
const int ledPin = 5; 
const int buttonPin = 2;          
const int buzzerPin = 7;            
const int servo2Pin = 10;
const int servo1Pin = 9;          


int metalCount = 0;
float cashback = 0.0; 


Servo servo1;
Servo servo2;


LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {

  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
 
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  
  
  lcd.init();
  lcd.backlight();  
  lcd.setCursor(0, 0);
  lcd.print("Cashback: R$ 0.00 ");
  lcd.setCursor(0, 1);
  lcd.print("Cont. metal: ");
}

void loop() {
  
  int buttonState = digitalRead(buttonPin);
  
  // Checa se o botão foi pressionado
  if (buttonState == HIGH) {
    bool ledState = digitalRead(ledPin);

    if (!ledState) {
      metalCount++;
      cashback += 0.01; 
    }

    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000, 100);
    servo1.write(90);
    servo2.write(90);
    delay(1000);
    
  } else {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
    servo1.write(0);
    servo2.write(0);
  } 
  
  
  lcd.setCursor(10, 0);
  lcd.print(cashback, 2); 
  lcd.setCursor(12, 1);
  lcd.print(metalCount);
  
  delay(200); 
}