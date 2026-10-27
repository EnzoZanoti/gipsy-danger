// Programação incial
#define TRIGGER 9
#define ECHO 8

// Motor Esquerdo
#define IN1 2  // OUT1 = negativo
#define IN2 3  // OUT2 = positivo

// Motor Direito
#define IN3 10 // OUT3 = negativo
#define IN4 11 // OUT4 = positivo

long distancia;

void setup() {
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  // Pulso do sensor ultrassônico
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIGGER, LOW);

  // Lê o eco
  long tempo = pulseIn(ECHO, HIGH);

  // Calcula distância
  distancia = tempo * 0.0343 / 2;

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Se detectar algo a menos de 20 cm
  if (distancia > 0 && distancia < 20) {

    // MOTOR ESQUERDO -> FRENTE
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    // MOTOR DIREITO -> FRENTE
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

  } else {

    // PARA MOTOR ESQUERDO
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);

    // PARA MOTOR DIREITO
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }

  delay(50);
}
