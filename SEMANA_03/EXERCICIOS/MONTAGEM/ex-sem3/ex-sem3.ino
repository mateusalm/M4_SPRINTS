#define LED0 17 
#define LED1 3
#define LED2 10
#define LED3 12
#define LDR 2
#define BUZZER 1
#define ESCOLHER 39
#define TOCAR 35

//int anterior = 0;

int notaAtual = 0;

double notas[15] = {264, 296.2, 332.6, 352.4, 
                    395.5, 444, 498.4, 528, 
                    592.42, 665.28, 704.88, 790.94,
                    888.1, 996.86, 1056};


int escolhidas[50] = {};

int ultima = 0;

void setup() {

  Serial.begin(115200);


  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  pinMode(LDR, INPUT);

  pinMode(BUZZER, OUTPUT);

  pinMode(ESCOLHER, INPUT_PULLUP);

  pinMode(TOCAR, INPUT_PULLUP);

}

void sequencia(int numero) {
  
  digitalWrite(LED0, numero & 0b0001);
  digitalWrite(LED1, numero & 0b0010);
  digitalWrite(LED2, numero & 0b0100);
  digitalWrite(LED3, numero & 0b1000);

  tone(BUZZER, notas[numero], 500);

  delay(500);

}

void loop() {

  int leitura = analogRead(LDR);

  int escala = map(leitura, 32, 4063, 0, 15); 
  //Serial.println(escala);

  if (notaAtual != escala){
    Serial.println(escala);

    sequencia(escala);
    //anterior = escala;
    notaAtual = escala;
  }

  if (digitalRead(ESCOLHER) == LOW) {
    escolhidas[ultima] = notaAtual;
    ultima++;

    sequencia(notaAtual);

    Serial.println("escolhida: ");
    Serial.println(escolhidas[ultima]);
  }

  if (digitalRead(TOCAR) == LOW) {
    for (int i =0; i <= ultima; i++){
      //tone(BUZZER, escolhidas[i], 500);

      sequencia(escolhidas[i]);

      Serial.println("tocar :");
      Serial.println(escolhidas[i]);
    }

    escolhidas[50] = {};
    
    ultima = 0;
  }

  delay(500);
}
