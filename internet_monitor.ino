/*This project requires an Arduino Nano 33 IoT.
Arduino sells other Wi-Fi enabled Arduinos that 
may work, but I've not tested them with this code.

It was pieced together from some other bits of code, 
mostly by Aucoeur Ngo, who was helpfully helping me
troubleshoot why my code wasn't working*/

#include <WiFiNINA.h>

/*wire LEDs to pins 9 and 10 with appropriate resistors.
This should be about 40-50 ohms for an Arduino with
3.3V output on its IO pins*/
#define googleOnlineLED 10
#define googleOfflineLED 9

//your wifi credentials go here
char ssid[] = "network name";
char pass[] = "password";

int status = WL_IDLE_STATUS;

//put whichever reliable website you want right here
char google[] = "google.com";

WiFiClient client;

void setup() {
  pinMode(googleOnlineLED, OUTPUT);
  pinMode(googleOfflineLED, OUTPUT);
  digitalWrite(googleOnlineLED, LOW);
  digitalWrite(googleOfflineLED, LOW);

 /*all the serial comms stuff can be removed, but it's 
  helpful for troubleshooting*/
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
