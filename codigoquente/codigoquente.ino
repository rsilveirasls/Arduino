/*
TCC RAFAEL SILVEIRA 2015
2, 3 ----- GARABEE
9,10 ----- LEITOR RFID
A0,A1,A2,A3,A4 ---- DISPLAY
4 ---- BUZZER
6 ---- LED 
7 ---- LED

SOBRANDO 5,0,1,8,11,12,13

*/
#include <SPI.h>
#include <MFRC522.h>  
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
SoftwareSerial mySerial(2, 3);
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   

Adafruit_PCD8544 display = Adafruit_PCD8544(A4, A3, A2, A1, A0);  //pinos referente ao display
//Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 11, 12);
 
int contador1=1;
int contador2=1;
int contador3=1;
int contador4=1;
int val2 = 0;
int buzzer=4;

int ledverde=6;
int ledvermelho=7;
char st[20];
 
void setup() 
{
  Serial.begin(19200);   // Inicia a serial
  SPI.begin();      // Inicia  SPI bus
  pinMode(ledverde, OUTPUT);   
  pinMode(ledvermelho, OUTPUT);  
  pinMode(buzzer, OUTPUT);
  mfrc522.PCD_Init();   // Inicia MFRC522
  Serial.println("SISGE - APROXIME O CARTAO DO LEITOR");
  Serial.println();
  digitalWrite(ledvermelho, HIGH);
 
  mySerial.begin(19200);
  display.begin();
  display.setContrast(60); //Ajusta o contraste do display
  display.clearDisplay();   //Apaga o buffer e o display
  display.setTextSize(1);  //Seta o tamanho do texto
  display.setTextColor(BLACK); //Seta a cor do texto
  display.setCursor(0,0);  //Seta a posição do cursor
  display.println(" SISGE - APROXIME O CARTAO DO LEITOR");  

  //Texto invertido - Branco com fundo preto
  display.setCursor(0,20);  //Seta a posição do cursor
  display.setTextColor(WHITE, BLACK); 
  display.setTextSize(1); 
  display.println("APROXIME O CARTAO!!");

  display.display();
  delay(2000);
  
 
}
 
void loop() {
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Mostra UID na serial
  //Serial.print("ID :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
   
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  //Serial.print("ID DO CARTAO : ");
  conteudo.toUpperCase();
  if (conteudo.substring(1)) 
  {
    mySerial.println(conteudo.substring(1)); 
    Serial.print(conteudo.substring(1));
    display.clearDisplay();   //Apaga o buffer e o display
    display.setTextSize(1);  //Seta o tamanho do texto
    display.setTextColor(BLACK); //Seta a cor do texto
    display.setCursor(0,0);  //Seta a posição do cursor
    display.println(" SISGE - APROXIME O CARTAO DO LEITOR");  
      
        //Texto invertido - Branco com fundo preto
    display.setTextColor(WHITE, BLACK); 
    display.setTextSize(1); 
    display.println("ID:");
    display.setTextSize(2); 
    display.setTextColor(BLACK);
    display.print(conteudo.substring(1));
    display.display();
    digitalWrite(ledverde, HIGH);
    apito();
    digitalWrite(ledvermelho, LOW);
    delay(3000);
    aproxime();

  display.display();
    

  }
  
} 
 
void apito(){

                      digitalWrite(buzzer, HIGH);
                      delay(10);
                      digitalWrite(buzzer, LOW);
  
}

void aproxime(){
  display.clearDisplay();   //Apaga o buffer e o display
  digitalWrite(ledverde, LOW);
  digitalWrite(ledvermelho, HIGH);
  display.setTextSize(1);  //Seta o tamanho do texto
  display.setTextColor(BLACK); //Seta a cor do texto
  display.setCursor(0,0);  //Seta a posição do cursor
  display.println(" SISGE - APROXIME O CARTAO DO LEITOR");  

  //Texto invertido - Branco com fundo preto
  display.setCursor(0,20);  //Seta a posição do cursor
  display.setTextColor(WHITE, BLACK); 
  display.setTextSize(1); 
  display.println("APROXIME O CARTAO!!");
  display.display();
}


  
