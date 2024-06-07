# Sistema de Cashback e Contagem de Metais

## Descrição do Projeto
Este projeto utiliza um microcontrolador para criar um sistema que registra a quantidade de metal coletado e calcula o cashback associado. O sistema utiliza um display LCD para mostrar o valor do cashback e a contagem de metais, além de LEDs, buzzer e servos para indicar e gerenciar o processo.

## Componentes Utilizados
- Microcontrolador (ex: Arduino)
- Display LCD I2C
- Servo Motores
- LED
- Buzzer
- Botão
- Resistores
- Protoboard e Jumpers

## Bibliotecas Necessárias
- `Wire.h`
- `LiquidCrystal_I2C.h`
- `Servo.h`

## Conexões
- `ledPin` (pino 5): Conectado a um LED para indicar o estado.
- `buttonPin` (pino 2): Conectado a um botão para detectar quando o metal é inserido.
- `buzzerPin` (pino 7): Conectado a um buzzer para emitir um som.
- `servo1Pin` (pino 9): Conectado ao Servo Motor 1.
- `servo2Pin` (pino 10): Conectado ao Servo Motor 2.
- Display LCD I2C: Conectado aos pinos SDA e SCL do microcontrolador.

## Funcionalidades
- **Contagem de Metais:** Conta o número de metais inseridos.
- **Cálculo de Cashback:** Calcula o valor do cashback com base na quantidade de metais.
- **Indicações Visuais e Auditivas:** Usa LED e buzzer para feedback.
- **Controle de Servos:** Move servos em resposta à inserção de metais.
- **Display LCD:** Mostra o valor do cashback e a contagem de metais.

## Código

```cpp
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
  
  delay
