//Projeto arduino pisca led
void setup() {
  pinMode(10, OUTPUT);  
  pinMode(11, OUTPUT);  
  pinMode(12,OUTPUT);  
}

void loop() {
  // Controle do led verde
  digitalWrite(10,HIGH); //acende o led
  delay(4000);          // espera 4 segundos
  digitalWrite(10,LOW);  //apaga o led

  // Controle do led amarelo
  digitalWrite(11,HIGH); 
  delay(2000);
  digitalWrite(11,LOW);

  // Controle do led vermelho
  digitalWrite(12,HIGH);
  delay(4000);
  digitalWrite(12,LOW);
  
}
