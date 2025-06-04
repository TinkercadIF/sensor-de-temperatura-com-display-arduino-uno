#include <LiquidCrystal.h>

// Definimos os valores dos pinos utilizados para ligar o LCD 16x2
int rs = 6;
int e = 7;
int d4 = 2;
int d5 = 3;
int d6 = 4;
int d7 = 5;

// Definidos os Pinos Digitais do Led
int led = 8;   // LED normal
int ledv = 9;   // LED de perigo
int buzzerPin = 13; // Pino do buzzer

// Pino analógico do sensor de temperatura
int tempPin = A0;  // Supondo que o sensor esteja no pino A0

// Inicializar o LCD chamando suas variáveis já definidas
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

void setup() {
  pinMode(led, OUTPUT);  // O LED normal como saída
  pinMode(ledv, OUTPUT); // O LED de perigo como saída
  pinMode(buzzerPin, OUTPUT); // O buzzer como saída
  lcd.begin(16, 2);      // Iniciar LCD com 16 colunas e 2 linhas
}

void loop() {
  // Lê o valor do sensor de temperatura
  int sensorValue = analogRead(tempPin);
  
  // Converte o valor lido para uma temperatura em graus Celsius
  float temp = sensorValue * (5.0 / 1023.0) * 100.0; // Converte para Celsius
  
  // Exibe a temperatura na primeira linha do LCD
  lcd.setCursor(0, 0);
  lcd.print(temp);      // Imprime a temperatura no LCD
  lcd.print(" graus C"); // Imprime a unidade "graus C"
  
  // Condicional para verificar se a temperatura está fora do normal
  if (temp > 40) {
    digitalWrite(led, HIGH);  // Liga o LED normal
    digitalWrite(ledv, LOW);  // Desliga o LED de perigo
    digitalWrite(buzzerPin, HIGH); // Aciona o buzzer (perigo)
    lcd.setCursor(0, 1);      // Linha 2 do LCD
    lcd.print("Perigo!!!");   // Alerta de perigo
  } else if (temp < 0) {
    digitalWrite(led, HIGH);  // Liga o LED normal
    digitalWrite(ledv, LOW);  // Desliga o LED de perigo
    digitalWrite(buzzerPin, HIGH); // Aciona o buzzer (perigo)
    lcd.setCursor(0, 1);      // Linha 2 do LCD
    lcd.print("Perigo!!!");   // Alerta de perigo
  } else {
    // Se a temperatura estiver no intervalo normal, limpa a segunda linha do LCD
    digitalWrite(ledv, HIGH); // Liga o LED de perigo (normal)
    digitalWrite(led, LOW);   // Desliga o LED normal
    digitalWrite(buzzerPin, LOW); // Desliga o buzzer
    lcd.setCursor(0, 1);
    lcd.print("               ");  // Apaga a mensagem anterior
  }
  
  delay(1000);  // Atraso de 1 segundo antes de atualizar o display
}
