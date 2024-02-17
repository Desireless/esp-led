#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#define SDA_PIN 12
#define SCL_PIN 14
#define OLED_RESET -1
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

const char* wifiSsid = "TTTT";
const char* wifiPassword = "holahola";

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
    Serial.begin(115200); // Set serial communication speed

    /*
    DISPLAY
    */
    Wire.begin(SDA_PIN, SCL_PIN);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
      Serial.println("SSD1306 initialization failed");
      while (true)
        ;
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Hello, ESP8266!");
    display.display();
    delay(1000);
    /*
    WIFI
    */
  //   connectToWiFi();
  scanAndDisplayNetworks();
}


void loop() {}

void connectToWiFi() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Configura un WiFi con los siguientes datos:");
  display.setCursor(0, 10);
  display.print("Nombre: ");
  display.println(wifiSsid);
  display.setCursor(0, 20);
  display.print("Clave: ");
  display.println(wifiPassword);
  display.display();

  Serial.println("Esperando a que el usuario configure el WiFi...");

  // Espera a que el usuario configure el WiFi
  while (WiFi.status() != WL_CONNECTED) {
    // Intenta conectarse al WiFi creado por el usuario
    WiFi.begin(wifiSsid, wifiPassword);
    delay(5000);
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.println("RED: OK"); 
  display.display();

}

void scanAndDisplayNetworks() {
  int numNetworks = WiFi.scanNetworks();

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Redes WiFi disponibles");

  int networksDisplayed = 0;
  int cursor = 2;

  for (int i = 0; i < numNetworks; i++) {
    String ssid = WiFi.SSID(i);
    int rssi = WiFi.RSSI(i);

    display.setCursor(0, cursor * 10);
    display.print(ssid);
    display.print(" (");
    display.print(rssi);
    display.println(" dBm)");
    networksDisplayed++;
    cursor++;

    if(networksDisplayed == 4){
      break;
    }
  }

  display.display();
}
