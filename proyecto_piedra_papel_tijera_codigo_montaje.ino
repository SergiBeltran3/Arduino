// =======================================================
//  Proyecto: Piedra, Papel o Tijera automático
//  Autor: Sergi Beltran y Arturo Shagoyan
// =======================================================

#include <LiquidCrystal.h>
#include <Servo.h>

// ------------------------- LCD -------------------------

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);

// ------------------------- Variables -------------------------

volatile long A;

// ------------------------- Funciones -------------------------

float checkDistance() {
  digitalWrite(11, LOW);
  delayMicroseconds(2);
  digitalWrite(11, HIGH);
  delayMicroseconds(10);
  digitalWrite(11, LOW);

  float distance = pulseIn(10, HIGH) / 58.00;
  delay(10);
  return distance;
}

// ------------------------- Servos -------------------------

Servo servoPiedra;   // Pin 3
Servo servoPapel;    // Pin 6
Servo servoTijera;   // Pin 9

// ------------------------- LEDs y Altavoz -------------------------

const int red1 = 2;   // Piedra (LED azul)
const int red2 = 4;   // Papel
const int red3 = 5;   // Tijera
const int speaker = 12;

// ------------------------- APAGAR TODOS LOS LEDs -------------------------

void apagarTodos() {
  digitalWrite(red1, HIGH); // LEDs invertidos → HIGH apaga
  digitalWrite(red2, HIGH);
  digitalWrite(red3, HIGH);
}

// ------------------------- ENCENDER LED POR JUGADA -------------------------

void encenderLED(int jugada) {
  apagarTodos();
  switch (jugada) {
    case 1: digitalWrite(red1, LOW); break; // Piedra
    case 2: digitalWrite(red2, LOW); break; // Papel
    case 3: digitalWrite(red3, LOW); break; // Tijera
  }
}

// ------------------------- Setup -------------------------

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print(" Piedra Papel y ");
  lcd.setCursor(0, 1);
  lcd.print(" Tijera ");
  delay(1000);
  lcd.clear();

  // Inicializar aleatoriedad
  randomSeed(analogRead(A5));

  A = 0;

  pinMode(11, OUTPUT);  // Trigger
  pinMode(10, INPUT);   // Echo
  pinMode(speaker, OUTPUT);

  pinMode(red1, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(red3, OUTPUT);

  apagarTodos(); // LEDs apagados al inicio

  servoPiedra.attach(3);
  servoPapel.attach(6);
  servoTijera.attach(9);

  servoPiedra.write(0);
  servoPapel.write(0);
  servoTijera.write(0);
}

// ------------------------- Loop -------------------------

void loop() {
  if (checkDistance() < 100) {
    A = random(1, 4); // 1=Piedra, 2=Papel, 3=Tijera

    tone(speaker, 131);
    delay(100);
    noTone(speaker);

    lcd.setCursor(0, 0);
    lcd.print(" Es....");

    // Mostrar resultado en LCD y encender LED correspondiente
    switch (A) {
      case 1: // Piedra
        lcd.setCursor(0, 1);
        lcd.print("   Piedra!");
        encenderLED(1);
        servoPiedra.write(120);
        delay(3000);
        servoPiedra.write(179);
        break;

      case 2: // Papel
        lcd.setCursor(0, 1);
        lcd.print("   Papel!");
        encenderLED(2);
        servoPapel.write(120);
        delay(3000);
        servoPapel.write(179);
        break;

      case 3: // Tijera
        lcd.setCursor(0, 1);
        lcd.print("   Tijera!");
        encenderLED(3);
        servoTijera.write(120);
        delay(3000);
        servoTijera.write(179);
        break;
    }

    delay(500);
    lcd.clear();
  }
}
