#include <ESP8266WiFi.h>

#include "DHT.h"
#include <ESP8266HTTPClient.h>

#define DHTTYPE DHT11
const char* serverUrl = "192.168.1.42/getdemo.php";
const char* ssid = "COFFEE 24 HOURS";

const char* password = "66668888";

WiFiServer server(80);

const int DHTPin = 5;

DHT dht(DHTPin, DHTTYPE);

static char celsiusTemp[7];

static char fahrenheitTemp[7];

static char humidityTemp[7];

void setup()

{

  Serial.begin(115200);

  delay(10);

  dht.begin();

  Serial.println();

  Serial.print("Dang ket noi den mang… ");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)

  {

    delay(500);

    Serial.print(".");

  }

  Serial.println("");

  Serial.println("Da ket noi WiFi");

  server.begin();

  Serial.println("Web server dang khoi dong. Vui long doi dia chi IP…");

  delay(1000);

  Serial.println(WiFi.localIP());

}

void loop()

{

  WiFiClient client = server.available();

  if (client)

  {

    Serial.println("Co client moi");

    boolean blank_line = true;

    while (client.connected())

    {

      if (client.available())

      {

        char c = client.read();

        if (c == '\n' && blank_line)

        {

          float h = dht.readHumidity();

          float t = dht.readTemperature();

          float f = dht.readTemperature(true);

          if (isnan(h) || isnan(t) || isnan(f))

          {

            Serial.println("Khong the doc du lieu tu cam bien DHT!");

            strcpy(celsiusTemp, "Failed");

            strcpy(fahrenheitTemp, "Failed");

            strcpy(humidityTemp, "Failed");

          }

          else

          {

            float hic = dht.computeHeatIndex(t, h, false);

            dtostrf(hic, 6, 2, celsiusTemp);

            float hif = dht.computeHeatIndex(f, h);

            dtostrf(hif, 6, 2, fahrenheitTemp);

            dtostrf(h, 6, 2, humidityTemp);

          }

  HTTPClient http;
  http.begin(client, serverUrl);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  String data = "temperature_C=" + String(celsiusTemp) +
                "&temperature_F=" + String(fahrenheitTemp) +
                "&humidity=" + String(humidityTemp);
  int httpResponseCode = http.POST(data);
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("Error during HTTP request: ");
    Serial.println(httpResponseCode);
  }
  http.end();

  delay(5000); // Delay for 5 seconds before sending the next data
        }
      }
    }
  }
}
