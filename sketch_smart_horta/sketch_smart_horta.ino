// Projeto Smart Irrigation - IOT
//Definição das portas e dos leds  e dos sensores analogicos
#include "DHT.h"

#define DHTPIN A1 // pino que estamos conectado
#define DHTTYPE DHT11 // DHT 11

#define pino_sinal_analogico A0
#define pino_led_vermelho 12
#define pino_led_amarelo 11
#define pino_led_verde 10

int pino_rele1 = 3;
int pino_rele2 = 4;


#define tempoDelay 2000

// Conecte pino 1 do sensor (esquerda) ao +5V
// Conecte pino 2 do sensor ao pino de dados definido em seu Arduino
// Conecte pino 4 do sensor ao GND
// Conecte o resistor de 10K entre pin 2 (dados) 
// e ao pino 1 (VCC) do sensor
DHT dht(DHTPIN, DHTTYPE);
 
int valor_analogico;
 
void setup()
{
  Serial.begin(9600);
  pinMode(pino_sinal_analogico, INPUT);
  pinMode(pino_led_vermelho, OUTPUT);
  pinMode(pino_led_amarelo, OUTPUT);
  pinMode(pino_led_verde, OUTPUT);

  pinMode(pino_rele1, OUTPUT);
  pinMode(pino_rele2, OUTPUT);

  Serial.println("DHT 11 Sensor de Temperatura !");
  dht.begin();

  //Desliga os dois reles
  digitalWrite(pino_rele1, HIGH);
  digitalWrite(pino_rele2, HIGH);
}
 
void loop()
{

  Serial.println("");  
  Serial.println("#####################################################");  
  Serial.println("#1 -- Dados Sensor Higrometro Umidade do Solo ");  
  lerSensorHigrometro();
  delay(tempoDelay); // Delay para facilitar visualização dos dados do monitor

  Serial.println("");  
  Serial.println("#####################################################");  
  Serial.println("#2 -- Dados Sensor Temperatura e Umidade do AR DHT11 ");  
  lerSensorTemperatura();
  delay(tempoDelay); // Delay para facilitar visualização dos dados do monitor
    
  
}
 
void apagaleds()
{
  digitalWrite(pino_led_vermelho, LOW);
  digitalWrite(pino_led_amarelo, LOW);
  digitalWrite(pino_led_verde, LOW);
}


void lerSensorHigrometro()
{
  //Le o valor do pino A0 do sensor
  valor_analogico = analogRead(pino_sinal_analogico);
 
  //Mostra o valor da porta analogica no serial monitor
  Serial.print("Porta analogica: ");
  Serial.print(valor_analogico);
 
  //Solo umido, acende o led verde
  if (valor_analogico > 0 && valor_analogico < 400)
  {
    Serial.println(" Status: Solo umido  : "  + valor_analogico);
    apagaleds();
    digitalWrite(pino_led_verde, HIGH);
    //desliga o rele
    digitalWrite(pino_rele1, HIGH);    
  }
 
  //Solo com umidade moderada, acende led amarelo
  if (valor_analogico > 400 && valor_analogico < 800)
  {
    Serial.println(" Status: Umidade moderada : " + valor_analogico );
    apagaleds();
    digitalWrite(pino_led_amarelo, HIGH);
  }
 
  //Solo seco, acende led vermelho
  if (valor_analogico > 800 && valor_analogico < 1024)
  {
    Serial.println(" Status: Solo seco " + valor_analogico);
    apagaleds();
    digitalWrite(pino_led_vermelho, HIGH);
    //liga o rele
    digitalWrite(pino_rele1, LOW);    
    Serial.println("Rele 1 Ligado");
    Serial.println("Rele 2 Ligado");
    
    
  }
  delay(100);

}


void lerSensorTemperatura(){
  
  // Codigo para pegar informação do dht11
  // A leitura da temperatura e umidade pode levar 250ms!
  // O atraso do sensor pode chegar a 2 segundos.
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t) || isnan(h)) 
  {
    Serial.println("Falha lendo dados DHT");
  } 
  else 
  {
    Serial.print("Umidade: ");
    Serial.print(h);
    Serial.print(" %t");
    Serial.print("Temperatura: ");
    Serial.print(t);
    Serial.println(" *C");
  }
    
}

