#include <WiFiNINA.h>
#include "arduino_secrets.h"
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASSWORD;
int b = 1;
WiFiClient client;
int sensorPin = A0;        // select the input pin for the potentiometer
int ledPin = LED_BUILTIN;  // select the pin for the LED
int sensorValue = 0;       // variable to store the value coming from the sensor
int a = 0;

char HOST_NAME[] = "maker.ifttt.com";
String PATH_NAME = "https://maker.ifttt.com/trigger/LDR/with/key/fvmrAhgO6IKkTDwylrtnxNYt4otKuAEi2UoirIZdMAK";  // change your EVENT-NAME and YOUR-KEY
String queryString = "?value1=57&value2=25";

void setup() {
  // initialize WiFi connection
  WiFi.begin(ssid, pass);

  Serial.begin(9600);
  while (!Serial)
    ;

  // connect to web server on port 80:
  if (client.connect(HOST_NAME, 80)) {
    // if connected:
    Serial.println("Connected to server");
  } else {  // if not connected:
    Serial.println("connection failed");
  }
}

void loop() {
  while (b < 10) {
    if (sensorValue >= 400) {
      sensorValue = analogRead(sensorPin);
      Serial.println(sensorValue);
      Serial.println("Sunlight detected");
      digitalWrite(ledPin, HIGH);
      a = a + 1;

    } else {
      sensorValue = analogRead(sensorPin);
      Serial.println(sensorValue);
      Serial.println("Sunlight not detected");
      digitalWrite(ledPin, LOW);
    }
    b = b + 1;
    delay(1000);
  }

  if (a < 20) {
    client.println("GET " + PATH_NAME + queryString + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: close");
    client.println();  // end HTTP header
    // read an incoming byte from the server and print it to serial monitor:
    char c = client.read();
    Serial.print(c);
  }
}

