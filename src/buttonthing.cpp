// buttonthing - use an Adafruit Huzzah ESP8266 to read input (buttons) and send light commands to max.
// lots of primitives gleaned here: https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/WiFiClient/WiFiClient.ino

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

// put the WIFI credentials in wificreds.h, in the same directory as buttonthing.cpp (this file) with the lines:
// const char* ssid = "WIFI SSID";
// const char* password = "WIFI SECRET PASSWORD";
// (uncommented, of course)
#include "wificreds.h"

const char* host = "max.kenkl.org";

const unsigned int clienttimeout = 60000;  //ms for client timeout in the doThing* actions
const int led = 13;

const int button1 = 14;
const char* url1 = "/lights/normal.php";
int button1State = 0;

const int button2 = 2;
const char* url2 = "/lights/loft_teevee.php";
int button2State = 0;

const int button3 = 12;
const char* url3 = "/lights/cinema.php";
int button3State = 0;

const int button4 = 5;
const char* url4 = "/lights/alloff.php?id=L";
int button4State = 0;

const int button5 = 0;
const char* url5 = "/lights/brhalf.php";
int button5State = 0;

const int button6 = 4;
const char* url6 = "/lights/alloff.php?id=O";
int button6State = 0;

// bool state = 0;

void doThing(const char* url);

void setup() {
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(button5, INPUT_PULLUP);
  pinMode(button6, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  digitalWrite(led, 1);
  Serial.begin(115200);
  // delay(10);

  // We start by connecting to a WiFi network
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);

/* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
   would try to act as both a client and an access-point and could cause
   network-issues with your other WiFi-devices on your WiFi-network. */
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
  delay(500);
  Serial.print(".");
}

Serial.println("");
Serial.println("WiFi connected");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());

  digitalWrite(led, 0);
}

void loop() {
  button1State = digitalRead(button1);
  button2State = digitalRead(button2);
  button3State = digitalRead(button3);
  button4State = digitalRead(button4);
  button5State = digitalRead(button5);
  button6State = digitalRead(button6);

  if(button1State == LOW) {
    Serial.println("button 1 pressed");
    digitalWrite(led, 1);
    delay(1); //poor man's debounce. we'll assume that the button's been released by now.
    doThing(url1);
  }
  else {
    digitalWrite(led, 0);
  }

  if(button2State == LOW) {
    Serial.println("button 2 pressed");
    digitalWrite(led, 1);
    delay(1); //poor man's debounce. we'll assume that the button's been released by now.
    doThing(url2);
  }
  else {
    digitalWrite(led, 0);
  }

  if(button3State == LOW) {
    Serial.println("button 3 pressed");
    digitalWrite(led, 1);
    delay(1); //poor man's debounce. we'll assume that the button's been released by now.
    doThing(url3);
  }
  else {
    digitalWrite(led, 0);
  }

  if(button4State == LOW) {
    Serial.println("button 4 pressed");
    digitalWrite(led, 1);
    delay(1); //poor man's debounce. we'll assume that the button's been released by now.
    doThing(url4);
  }
  else {
    digitalWrite(led, 0);
  }

  if(button5State == LOW) {
    Serial.println("button 5 pressed");
    digitalWrite(led, 1);
    delay(1); //poor man's debounce. we'll assume that the button's been released by now.
    doThing(url5);
  }
  else {
    digitalWrite(led, 0);
  }

  if(button6State == LOW) {
    Serial.println("button 6 pressed");
    digitalWrite(led, 1);
    delay(1); //poor man's debounce. we'll assume that the button's been released by now.
    doThing(url6);
  }
  else {
    digitalWrite(led, 0);
  }

}

void doThing(const char* url) {

  digitalWrite(led, 1); // light up a pilot while we connect, send, and get a response.

  Serial.println("Got to doThing...");
  Serial.print("connecting to ");
  Serial.println(host);

  // Use WiFiClient class to create TCP connections
WiFiClient client;
const int httpPort = 80;
if (!client.connect(host, httpPort)) {
  Serial.println("connection failed");
  return;
}

// We now create a URI for the request
//String url = "/lights/cinema.php";

Serial.print("Requesting URL: ");
Serial.println(url);

// This will send the request to the server
client.print(String("GET ") + url + " HTTP/1.1\r\n" +
             "Host: " + host + "\r\n" +
             "Connection: close\r\n\r\n");
unsigned long timeout = millis();
while (client.available() == 0) {
  if (millis() - timeout > clienttimeout) {
    Serial.println(">>> Client Timeout !");
    client.stop();
    return;
  }
}

  Serial.println("closing connection");
  Serial.println();

  digitalWrite(led, 0); // turn off the pilot

}
