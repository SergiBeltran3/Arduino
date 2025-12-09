# Proyecto Arduino

**Objetivo: Hacer un minijuego que sea igual al piedra, papel o tijera**

**Equipo: Sergi Beltran y Arturo Shagoyan**

**Roles: *Sergi Beltran* (Montaje en Tinkercad / Programación) *Arturo Shagoyan* (Montaje en físico / Ayudante de programación)**

**Plan de Sprints:** 

_- Sprint 1:_ **Definir el objetivo del proyecto, hacer un boceto en Tinkercad y subir las primeras versiones del código.**

_- Sprint 2:_ **Prototipo mas avanzado (Circuito completo en Tinkercad, código mejorado) y lista de sensores.**

_- LiveDemo:_ **Funcionamiento del prototipo (en físico), explicar el proyecto y responder a las preguntas.**

# 🏁 **SPRINT 1 - PROGRESO DEL PROYECTO** 

## 🎯 _Objetivo del Proyecto:_

El objetivo de este proyecto es construir un prototipo físico con Arduino que reaccione mediante sensores y actuadores para crear una experiencia interactiva.

El sistema combinará:

  - (x1) Sensor ultrasónico (HC-SR04)

  - (x3) LEDs

  - (x1) Buzzer

  - (x3) Servo SG90

  - (x1) Potenciómetro

  - (x1) Pantalla LCD 16x2

  - (x4) Resistencias

El propósito es que el prototipo responda de forma dinámica a la distancia, a la interacción del usuario y a valores analógicos.

## 🛠️ _Boceto en Tinkercad_

Se ha creado un primer diseño del circuito en Tinkercad, donde se incluyen los principales sensores y actuadores del proyecto.

<img width="925" height="701" alt="Captura de pantalla 2025-11-21 165456" src="https://github.com/user-attachments/assets/b8fd5d4f-8bc9-4498-bd7d-f6d0e8eb785a" />

## 💻 _Primeras versiones del código_

## ✔️ _Objetivo:_ asegurar que el sensor funciona y da valores estables.

```cpp
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
```
## ✔️ _Objetivo:_ comprobar que no vibran y que responden bien.

```cpp
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
```
# 🚀 **SPRINT 2 - PROGRESO DEL PROYECTO**

## 🔧 _Mejoras realizadas desde el Sprint 1_

Durante este sprint se ha avanzado significativamente en el desarrollo del prototipo.  

El circuito se ha completado, el código principal ya integra todos los componentes, y se ha mejorado la documentación del proyecto.

Hemos aplicado también el feedback que nos dieron en el anterior sprint y hemos añadido algunas mejoras.

---

## 🛠️ _Circuito en Tinkercad (versión avanzada)_

Se ha actualizado el diseño anterior añadiendo:

- Pantalla LCD 16x2 completamente conectada  
- Sistema de 3 servomotores (piedra, papel y tijera)  
- LED para cada resultado  
- Sensor ultrasónico configurado correctamente  
- Buzzer para el sonido del evento  
- Ajuste del cableado para evitar interferencias  
- Añadido potenciómetro para contraste del LCD

## 📌 _Imagen del circuito actualizado:_

Hemos realizado otro proyecto de Tinkercad con el circuito que vamos a usar en el proyecto (ya que encontramos un problema con el anterior), en este circuito hemos realizado un circuito inverso para los LED's de colores ya que nos hemos dado cuenta de que usando la otra técnica iba a ser un engorro a la hora de montar el proyecto, el circuito funciona de la siguiente manera: lo hace inverso, todo aquello que este en LOW (estará encendido) y todo aquello que este en HIGH (estatá apagado), a continuación os muestro el circuito:

<img width="1008" height="748" alt="Captura de pantalla 2025-12-02 125210" src="https://github.com/user-attachments/assets/3a11ef72-e71c-4f78-95c8-e96d1a234fb6" />

Para compensar las resistencias individuales de cada LED (220 Ω), hemos usado una resistencia de (330 Ω) para todos los LED's a la vez:

<img width="316" height="143" alt="Captura de pantalla 2025-12-02 115959" src="https://github.com/user-attachments/assets/ca111e90-e4f0-4a78-b037-09052ce09f95" />

## 📦 _Lista de sensores y componentes (actualizada)_

La lista requerida ya está completada en el archivo `hardware.md`.

Incluye:

- HC-SR04  
- 3 servos SG90  
- Pantalla LCD 16x2  
- Buzzer  
- LEDs + resistencias  
- Potenciómetro  
- Protoboard  
- Cables Dupont

---

## 💻 _Código funcional implementado en el Sprint 2_

A continuación se muestra la versión del código que ya integra:

✔ Lectura del sensor ultrasónico  
✔ Control de 3 servos  
✔ Mensajes en la pantalla LCD 16x2  
✔ LEDs correspondientes a cada opción  
✔ Sonido con el buzzer  
✔ Lógica completa de Piedra – Papel – Tijera 
✔ Lógica avanzada para que salga "random" en Piedra, Papel, Tijera

### 💻 _Versión 3 – Integración completa del sistema_

```cpp
*//En este código se puede observar el uso del circuito inverso en los LED's (LOW/apagado, HIGH/encendido)*
```

```cpp
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
int ultimaJugada = 0; // Nueva variable para guardar la última jugada

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

// ------------------------- FUNCION PARA ELEGIR JUGADA SIN REPETIR -------------------------

int elegirJugadaNoRepetida() {
  int nueva;
  do {
    nueva = random(1, 4); // 1=Piedra, 2=Papel, 3=Tijera
  } while (nueva == ultimaJugada);
  ultimaJugada = nueva;
  return nueva;
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
    A = elegirJugadaNoRepetida(); // Ahora usamos la función que evita repeticiones

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
```

----------

💼 **REGISTRO DE TRABAJO** 💼

**13/11/2025**

Hoy hemos montado la maqueta de nuestro juego (Piedra, Papel y Tijera) en Tinkercad, aquí muestro la imagen:

<img width="932" height="707" alt="Captura de pantalla 2025-11-13 100617" src="https://github.com/user-attachments/assets/1ee2d610-7e6a-458b-aeb8-52ec74db5a66" />


**18/11/2025**

Estamos montando en fisico nuestro proyecto (piedra,papel,tijera), estamos haciendo pruebas para solucionar los errores que nos van apareciendo

![Proyecto_fisico](https://github.com/user-attachments/assets/ef3744e7-b4dc-4b85-ace7-7198b94f9a36)

**20/11/2025**

Hemos hecho una prueba en formato fisico de como funciona nuestro proyecto y es bastante funcional, pero añadiremos mejoras:

https://github.com/user-attachments/assets/f2f93b62-7ad6-47eb-999d-e23f4c74a813

**25/11/2025**

Hoy hemos hecho mas pruebas del minijuego (en físico) y hemos estado cambiando cosas y añadido otras (algunas nos han dado problemas y las hemos tenido que suprimir) por ejemplo queriamos aumentar el sonido del *Buzzer* (pero eso ha hecho que gaste mas energia y por ende causaba que la pantalla y los servos dejasen de funcionar), también hemos querido aumentar la velocidad de los servos (pero al tener mas velocidad, causaba que todos se moviesen por igual [Puede que en un futuro sigamos probando cosas] pero hasta ahora hemos decidido suprimir esa opción.

Al final, nos hemos dado cuenta que la logica *"Random"* de nuestro juego "fallaba", ya que a veces salían opciones repetidas y eso no daba juego al jugador a la hora de jugar, así que hemos decidido cambiar la logica del juego para que las opciones no se repitan, aquí subo el código con los cambios añadidos:

# Código Arduino

```cpp
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
int ultimaJugada = 0; *// Nueva variable para guardar la última jugada**

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

*// ------------------------- FUNCION PARA ELEGIR JUGADA SIN REPETIR -------------------------**

int elegirJugadaNoRepetida() {
  int nueva;
  do {
    nueva = random(1, 4); // 1=Piedra, 2=Papel, 3=Tijera
  } while (nueva == ultimaJugada);
  ultimaJugada = nueva;
  return nueva;
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

  *// Inicializar aleatoriedad**
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
    A = elegirJugadaNoRepetida(); *// Ahora usamos la función que evita repeticiones**

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
```
He marcado en rojo los comentarios donde se han implementado los diferentes cambios de aleatoriedad *("Random")* del proyecto.

**02/12/2025**

Hoy he montado el segundo prototipo de Tinkercad (el que usaremos para la LiveDemo), este prototipo también es el que hemos usado para explicar el _Sprint 2_ donde hemos invertido el circuito de los LED's y hemos realizado un circuito inverso (a petición del profe, para que sea menos engorroso), gracias a esto hemos conseguido que los LED's funcionen dependiendo de lo que salga (Piedra, Papel o Tijera)

<img width="1008" height="748" alt="Captura de pantalla 2025-12-02 125210" src="https://github.com/user-attachments/assets/403ced24-868c-4293-883d-cfd0e466874e" />

Así queda el montaje en físico:

![WhatsApp Image 2025-12-02 at 12 55 26](https://github.com/user-attachments/assets/59e28b8d-f078-406c-b2f6-163e7165216c)

**04/12/2025**

Hemos solucionado errores que nos causanban los servos (distancia a la que giraban) y hemos solucionado pequeños detalles como por ejemplo la distancia a la que el ultrasonido detecta tu mano cuando te acercas, también hemos añadido que cuando no haya nadie jugando los LED's se apaguen, a continuación, os mostramos los cambios:

```cpp
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
int ultimaJugada = 0; // Nueva variable para guardar la última jugada

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

// ------------------------- FUNCION PARA ELEGIR JUGADA SIN REPETIR -------------------------

int elegirJugadaNoRepetida() {
  int nueva;
  do {
    nueva = random(1, 4); // 1=Piedra, 2=Papel, 3=Tijera
  } while (nueva == ultimaJugada);
  ultimaJugada = nueva;
  return nueva;
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
  float distancia = checkDistance();

  if (distancia < 10) { *//DISTANCIA DETECTADA**
    A = elegirJugadaNoRepetida();

    tone(speaker, 131);
    delay(100);
    noTone(speaker);

    lcd.setCursor(0, 0);
    lcd.print(" Es....");

    switch (A) {
      case 1:
        lcd.setCursor(0, 1);
        lcd.print("   Piedra!");
        encenderLED(1);
        servoPiedra.write(90); *//HEMOS REDUCIDO EL GIRO DE LOS SERVOS (DABA ERROR)**
        delay(3000);
        servoPiedra.write(0); *//HEMOS REDUCIDO EL GIRO DE LOS SERVOS (DABA ERROR)**
        break;

      case 2:
        lcd.setCursor(0, 1);
        lcd.print("   Papel!");
        encenderLED(2);
        servoPapel.write(90); *//HEMOS REDUCIDO EL GIRO DE LOS SERVOS (DABA ERROR)**
        delay(3000);
        servoPapel.write(0); *//HEMOS REDUCIDO EL GIRO DE LOS SERVOS (DABA ERROR)**
        break;

      case 3:
        lcd.setCursor(0, 1);
        lcd.print("   Tijera!");
        encenderLED(3);
        servoTijera.write(90); *//HEMOS REDUCIDO EL GIRO DE LOS SERVOS (DABA ERROR)**
        delay(3000);
        servoTijera.write(0); *//HEMOS REDUCIDO EL GIRO DE LOS SERVOS (DABA ERROR)**
        break;
    }

    delay(500);
    lcd.clear();
  }
  else {
    apagarTodos();  *// 👈 SE APAGAN LOS LEDS CUANDO NO HAY NADIE *//HEMOS AÑADIDO QUE CUANDO NO ESTÉ DETECTANDO NADA LOS LED'S SE APAGUEN**
  }
}
```

**09/12/2025**

Hoy hemos encontrado un problema con el circuito, y nos hemos dado cuenta de que los servos se estaban consumiendo gran parte del circuito electrico de nuestro mininjuego, entonces lo que hemos hecho para solucionarlo es añadir una bateria (5v) para que gran parte de esa energia vaya hacia el circuito y no tengamos problemas con algunos componentes del circuito como la pantalla, los LED's y sobre todo los servos, con esto conseguimos solucionar algunos problemas.

Esta es la bateria:

![WhatsApp Image 2025-12-09 at 12 44 30](https://github.com/user-attachments/assets/e8448c38-3e2e-48fb-b3f0-d9d2ede3c4e4)

Y este es el circuito con la bateria incorporada:

![WhatsApp Image 2025-12-09 at 12 44 31](https://github.com/user-attachments/assets/d651d8a3-6cdb-4bfa-984f-533b8af05f44)
