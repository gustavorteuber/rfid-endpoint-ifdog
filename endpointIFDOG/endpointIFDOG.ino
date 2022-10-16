//ARDUINO DO (SELECIONAR NOME DE ACORDO COM O LOCAL)
//rfid
#include <MFRC522.h>
#include <SPI.h>
#define PINO_RST 9
#define PINO_SDA 10
//wifi
#include "esp_wifi.h"
#include "esp_wpa2.h"
#include "esp_event_loop.h"
//data e hora
#include <WiFi.h>
#include "time.h"

const char* ssid       = "SEU_SSID";
const char* password   = "SUA_SENHA";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;

//nao esqueca de ajustar o fuso
const int   daylightOffset_sec = -3600*3;

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Falha ao obter a hora");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void setup()
{
  Serial.begin(115200);
  
  //connect to WiFi
  Serial.printf("Conectando em %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" Feito");
  
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop()
{
  delay(5000);
  printLocalTime();
}
//checando erros (Wifi)
static void initialise_wifi(void){
    tcpip_adapter_init();
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK( esp_wifi_start() );
    uart_write_bytes(UART_NUM_0, (const char *) "WiFi configurado\n", 20);
}

MFRC522 rfid(PINO_SDA, PINO_RST);

void setup() 
{
  Serial.begin(9600);

  SPI.begin();      // Inicia  SPI bus
  rfid.PCD_Init();
  
  Serial.println("Esperando Cão...");
  Serial.println();
}

void loop() 
{
   //Procura nova tag
  if (!rfid.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  // Seleciona uma tag
  if (!rfid.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  //Mostra UID na serial
//  Serial.print("UID da tag :");
  String conteudo= "";

  for (byte i = 0; i < rfid.uid.size; i++) 
  {
     conteudo.concat(String(rfid.uid.uidByte[i] < HEX ? " 0" : " ")); 
     conteudo.concat(String(rfid.uid.uidByte[i], HEX)); 
  }

//  Serial.println(mensagem);

  Serial.print("UID RFID: ");
  if (conteudo.substring(1) == "f2 b1 ae 20") //UID 1 - Tag do Maicon (o codigo da tag (exemplo))
  {
    Serial.println("Maicon está aqui!");
    PrintLocalTime();
  }
    Serial.print("UID RFID: ");
  if (conteudo.substring(1) == "f3 b1 ae 20") //UID 2 - Tag do Formiga (o codigo da tag (exemplo))
  {
    Serial.println("Formiga está aqui!");
    PrintLocalTime();
  }
    Serial.print("UID RFID: ");
  if (conteudo.substring(1) == "f4 b1 ae 20") //UID 3 - Tag do Churras (o codigo da tag (exemplo))
  {
    Serial.println("Churras está aqui !");
    PrintLocalTime();
  }
    Serial.print("UID RFID: ");
  if (conteudo.substring(1) == "f5 b1 ae 20") //UID 4 - Tag do Maicon (o codigo da tag (exemplo))
  {
    Serial.println("Formiga está aqui!");
    SPrintLocalTime();
  }
  else
  {
    Serial.println("Não registrada"); //Caso o cachorro não esteja no sistema de tagueamento.
  }
}











