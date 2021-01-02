#include <ESP8266WiFi.h>
#include <ThingESP.h>
#include "DHT.h"

DHT dht(2, DHT11);
float t, h;

ThingESP8266 thing("username", "nameproject", "xxxxxxx");

int LED = LED_BUILTIN;

void setup()
{
  Serial.begin(115200);

  dht.begin();

  pinMode(LED, OUTPUT);

  thing.SetWiFi("nama_WiFi", "pass_WiFi");
  thing.initDevice();
}

String HandleResponse(String query)
{
  //  dht11 
  awal:
  t = dht.readTemperature();
  h = dht.readHumidity();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    goto awal;
  }
  
  if (query == "led on") {
    digitalWrite(LED, 0);
    return "Done: LED Turned ON";
  }

  else if (query == "led off") {
    digitalWrite(LED, 1);
    return "Done: LED Turned OFF";
  }

  else if (query == "led status")
    return digitalRead(LED) ? "LED is OFF" : "LED is ON";

  else if (query == "temp") {
    return "Suhu: " + String(t,2) + "°C";
  }

  else if (query == "humd") {
    return "Kelembaban: " + String(h,2) + "%";
  }

  else return "Your query was invalid..";
}


void loop()
{
  thing.Handle();
}
