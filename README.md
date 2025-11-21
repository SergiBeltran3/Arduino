# Arduino

**Objetivo: Hacer un minijuego que sea igual al piedra, papel o tijera**

**Equipo: Sergi Beltran y Arturo Shagoyan**

**Plan de Sprints:** 

_- Sprint 1:_ **Definir el objetivo del proyecto, hacer un boceto en Tinkercad y subir las primeras versiones del código.**

_- Sprint 2:_ **Prototipo mas avanzado (Circuito completo en Tinkercad, código mejorado) y lista de sensores.**

_- LiveDemo:_ **Funcionamiento del prototipo (en físico), explicar el proyecto y responder a las preguntas.**

# 🏁 **SPRINT 1 - PROGRESO DEL PROYECTO** 

## 🎯 _Objetivo del Proyecto:_

El objetivo de este proyecto es construir un prototipo físico con Arduino que reaccione mediante sensores y actuadores para crear una experiencia interactiva.

El sistema combinará:

Sensor ultrasónico (HC-SR04)

LEDs

Buzzer

Servo SG90

Botón / Potenciómetro

El propósito es que el prototipo responda de forma dinámica a la distancia, a la interacción del usuario y a valores analógicos.

## 🛠️ _Boceto en Tinkercad_

Se ha creado un primer diseño del circuito en Tinkercad, donde se incluyen los principales sensores y actuadores del proyecto.

<img width="925" height="701" alt="Captura de pantalla 2025-11-21 165456" src="https://github.com/user-attachments/assets/b8fd5d4f-8bc9-4498-bd7d-f6d0e8eb785a" />

## 💻 _Primeras versiones del código_

### // Versión 1: Prueba del sensor HC-SR04

const int trig = 11;
const int echo = 10;

void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

float getDistance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  float d = pulseIn(echo, HIGH) / 58.0;
  return d;
}

void loop() {
  float dist = getDistance();
  Serial.println(dist);
  delay(200);
}

## ✔️ _Objetivo:_ asegurar que el sensor funciona y da valores estables.

### // Versión 2: Control simple de servos

#include <Servo.h>

Servo sPiedra;
Servo sPapel;
Servo sTijera;

void setup() {
  sPiedra.attach(3);
  sPapel.attach(6);
  sTijera.attach(9);

  sPiedra.write(0);
  sPapel.write(0);
  sTijera.write(0);
}

void loop() {
  sPiedra.write(120);
  delay(1000);
  sPiedra.write(0);
  delay(1000);
}

## ✔️ _Objetivo:_ comprobar que no vibran y que responden bien.

💼 **REGISTRO DE TRABAJO** 💼

13/11/2025

Hoy hemos montado la maqueta de nuestro juego (Piedra, Papel y Tijera) en Tinkercad, aquí muestro la imagen:

<img width="932" height="707" alt="Captura de pantalla 2025-11-13 100617" src="https://github.com/user-attachments/assets/1ee2d610-7e6a-458b-aeb8-52ec74db5a66" />


18/11/2025

Estamos montando en fisico nuestro proyecto (piedra,papel,tijera), estamos haciendo pruebas para solucionar los errores que nos van apareciendo

![Proyecto_fisico](https://github.com/user-attachments/assets/ef3744e7-b4dc-4b85-ace7-7198b94f9a36)

20/11/2025

Hemos hecho una prueba en formato fisico de como funciona nuestro proyecto y es bastante funcional, pero añadiremos mejoras:

https://github.com/user-attachments/assets/f2f93b62-7ad6-47eb-999d-e23f4c74a813



