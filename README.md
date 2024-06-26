# Sistema de lixo inteligente e cashback
## Autores

Este projeto foi desenvolvido por:

- Felipe Men (RM 557571)
- Matheus Alcantara Estevão (RM 558193)
- Otávio Ferrão (RM 556452)
  
## Descrição do Projeto
Este projeto é uma simulação de uma estação de lixo inteligente desenvolvida pela EcoSail, que visa ajudar na preservação dos oceanos. O sistema registra a quantidade de metal coletado e calcula o cashback associado, incentivando a reciclagem e promovendo a sustentabilidade e um turismo mais sustentável. 

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

##  Link para o Projeto Desenvolvido no Wokwi
- https://wokwi.com/projects/399880885973632001

## Projeto pronto
![image](https://github.com/EcoSail-Solucoes/GS-Edge-Computing/assets/162123418/b4555dde-9d1c-46f2-9fc6-edbd82a0c818)

## Funcionamento
- Ao ligar o aplicativo ele simula um detector de metais e a cada metal detectado ele adiciona um centavo de cashback junto à quantidade de metais detectados
![image](https://github.com/EcoSail-Solucoes/GS-Edge-Computing/assets/162123418/8371b37d-a0f4-4e47-b644-0e838f056ae6)

- Após detectar ele sinaliza o numero do cashback do cliente e a quantidade de metal detectado
![image](https://github.com/EcoSail-Solucoes/GS-Edge-Computing/assets/162123418/d3152aae-28a1-41d9-a6ae-9d37cd210e54)


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
