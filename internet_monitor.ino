#include <WiFiNINA.h>

#define googleOnlineLED 10
#define googleOfflineLED 9


char ssid[] = "network name";
char pass[] = "password";

int status = WL_IDLE_STATUS;

char google[] = "google.com";

WiFiClient client;

void setup() {
  pinMode(googleOnlineLED, OUTPUT);
  pinMode(googleOfflineLED, OUTPUT);
  digitalWrite(googleOnlineLED, LOW);
  digitalWrite(googleOfflineLED, LOW);

  Serial.begin(9600);

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  IPAddress gateway = WiFi.gatewayIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.print("Default Gateway: ");
  Serial.println(gateway);
}

void loop() {
  Serial.print("status before client.stop(): ");
  Serial.println(client.status());

  client.stop();

  Serial.print("status after client.stop(): ");
  Serial.println(client.status());

  if (client.connect(google, 80)) {
    Serial.print("status inside if client.connect(): ");
    Serial.println(client.status());
    Serial.print("Google is ONLINE at:  ");
    Serial.println(client.remoteIP());
    digitalWrite(googleOnlineLED, LOW);
    digitalWrite(googleOfflineLED, HIGH);
  }
  else {
    Serial.print("status inside else client.connect(): ");
    Serial.println(client.status());
    Serial.println("Google is OFFLINE");
    digitalWrite(googleOnlineLED, HIGH);
    digitalWrite(googleOfflineLED, LOW);
  }
  
  delay(2000);
}
