// ===== Pinos da Ponte H =====
// Motor esquerdo: Out1 (+) / Out2 (-)
const int IN1 = 2;   // Out1 - positivo motor esquerdo
const int IN2 = 3;   // Out2 - negativo motor esquerdo

// Motor direito: Out3 (-) / Out4 (+)
const int IN3 = 10;  // Out3 - negativo motor direito
const int IN4 = 11;  // Out4 - positivo motor direito

// ===== Pinos do sensor ultrassônico =====
const int TRIG = 9;
const int ECHO = 8;

// ===== Configuração =====
const float DISTANCIA_LIMITE = 20.0;  // cm

// Mede a distância em cm (retorna -1 se não houver leitura válida)
float medirDistancia() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  // Timeout de 30 ms (~5 m) para não travar o programa
  long duracao = pulseIn(ECHO, HIGH, 30000);

  if (duracao == 0) {
    return -1;
  }
  return (duracao * 0.0343) / 2.0;
}

// Gira os dois motores no mesmo sentido
// (o motor direito tem polaridade invertida na ponte H: + em Out4, - em Out3)
void ligarMotores() {
  digitalWrite(IN1, HIGH);  // esquerdo: positivo
  digitalWrite(IN2, LOW);   // esquerdo: negativo
  digitalWrite(IN3, LOW);   // direito: negativo
  digitalWrite(IN4, HIGH);  // direito: positivo
}

void pararMotores() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pararMotores();
  Serial.begin(9600);
}

void loop() {
  float distancia = medirDistancia();

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  // Objeto detectado a 20 cm ou menos -> motores ligados
  if (distancia > 0 && distancia <= DISTANCIA_LIMITE) {
    ligarMotores();
  } else {
    pararMotores();
  }

  delay(60);  // intervalo entre medições
}
