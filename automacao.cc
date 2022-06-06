include <ESP8266WiFi.h>
include <BlynkSimpleEsp8266.h>
 
char auth[] = "Token do Blynk"; // Token de autenticação gerado pelo aplicativo
char ssid[] = "Nome do wifi";
char pass[] = "Senha Wifi";

int sensor = A0; 
int buzzer = D5;
int greenLed = D6; 
int redLed = D7; 
int sensor_limit = 600; //Limite de gás aceitavel 

//Definindo os componentes do prototipo 
void setup() {
pinMode(buzzer, OUTPUT);
pinMode(sensor, INPUT);
pinMode(greenLed, OUTPUT);
pinMode(redLed, OUTPUT);
digitalWrite(greenLed, LOW);
digitalWrite(redLed, LOW);
Serial.begin(9600);
Blynk.begin(auth, ssid, pass); // Função para se conectar ao aplicativo Blynk pela internet
}

//Codigo para verificação de vazamento do gás
void loop() {
int sensor_value = analogRead(sensor);
Blynk.virtualWrite(V1, sensor_value);
if (sensor_value > sensor_limit) {
digitalWrite(greenLed, LOW);
digitalWrite(redLed, HIGH);
digitalWrite(buzzer, HIGH);
delay(500);
digitalWrite(buzzer, LOW);
Blynk.notify("Gas Detected");
}
else {
digitalWrite(buzzer, LOW);
digitalWrite(greenLed, HIGH);
digitalWrite(redLed, LOW);
}
delay(100);
Blynk.run(); //Manda as informações obtidas para o app Blynk
}