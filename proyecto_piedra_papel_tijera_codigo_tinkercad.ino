// =======================================================
//  Proyecto: Piedra, Papel o Tijera automático
//  Autor: [Sergi Beltran y Arturo Shagoyan]
//  Descripción: Usa un sensor ultrasónico y servos para
//               mostrar piedra, papel o tijera al azar.
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

  float distance = pulseIn(10, HIGH) / 58.00; // Conversión a cm
  delay(10);
  return distance;
}

// ------------------------- Servos -------------------------

Servo servoPiedra;   // Pin 3
Servo servoPapel;    // Pin 6
Servo servoTijera;   // Pin 9

// ------------------------- LEDs y Altavoz -------------------------

const int red1 = 2;
const int red2 = 4;
const int red3 = 5;
const int speaker = 12;

// ------------------------- Setup -------------------------

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print(" Piedra Papel y ");
  lcd.setCursor(0, 1);
  lcd.print(" Tijera ");
  delay(1000);
  lcd.clear();

  A = 0;

  pinMode(11, OUTPUT);  // Trigger sensor
  pinMode(10, INPUT);   // Echo sensor
  pinMode(speaker, OUTPUT);

  pinMode(red1, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(red3, OUTPUT);

  servoPiedra.attach(3);
  servoPapel.attach(6);
  servoTijera.attach(9);

  // Posición inicial de los servos
  servoPiedra.write(0);
  servoPapel.write(0);
  servoTijera.write(0);
}

// ------------------------- Loop -------------------------

void loop() {
  if (checkDistance() < 100) { // Si hay algo cerca (menos de 100 cm)
    A = random(1, 4); // Genera número entre 1 y 3

    tone(speaker, 131);
    delay(100);
    noTone(speaker);

    lcd.setCursor(0, 0);
    lcd.print(" Es....");

    switch (A) {
      case 1: // Piedra
        lcd.setCursor(0, 1);
        lcd.print("   Piedra!");
        digitalWrite(red1, HIGH);
        servoPiedra.write(120);
        delay(3000);
        servoPiedra.write(179);
        digitalWrite(red1, LOW);
        break;

      case 2: // Papel
        lcd.setCursor(0, 1);
        lcd.print("   Papel!");
        digitalWrite(red2, HIGH);
        servoPapel.write(120);
        delay(3000);
        servoPapel.write(179);
        digitalWrite(red2, LOW);
        break;

      case 3: // Tijera
        lcd.setCursor(0, 1);
        lcd.print("   Tijera!");
        digitalWrite(red3, HIGH);
        servoTijera.write(120);
        delay(3000);
        servoTijera.write(179);
        digitalWrite(red3, LOW);
        break;
    }

    delay(500);
    lcd.clear();
  }
}
