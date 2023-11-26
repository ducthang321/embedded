#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"
#define DHTTYPE DHT11
#define RELAY_PIN D1
/* Set these to your desired credentials. */
const char *ssid = "COFFEE 24 HOURS";  //ENTER YOUR WIFI SETTINGS
const char *password = "66668888";
const int DHTPin = 5;
WiFiServer server(80);
DHT dht(DHTPin, DHTTYPE);
int value, real_value, percent;
//Web/Server address to read/write from 

//=======================================================================
//                    Power on setup
//=======================================================================

void setup() {
  delay(10);
  pinMode(13, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);
  dht.begin();
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
}

//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
  //-------------------DOAMDAT-----------------------
  for(int i = 0; i<=9; i++){
    real_value += analogRead(A0);
  };
  value = real_value/10;
  real_value = 0;
  percent = map(value, 340, 1024, 0, 100); // 340 khi nhung nuoc, nen do am se la 100% 
  percent = 100 - percent ;
  if (percent < 40 ){
    digitalWrite(RELAY_PIN, LOW);
  }
  else {
    digitalWrite(RELAY_PIN, HIGH);
  }

  HTTPClient http;    //Declare object of class HTTPClient

  float humidity = dht.readHumidity();
  float temperatureC = dht.readTemperature();
  //float temperatureF = dht.toFahrenheit(temperatureC);

  //POST Data
  //getData = "nhietdoc=" + String(temperatureC) + "nhietdof=" + String(temperatureF) + "doam=" + String(humidity) ;  //Note "?" added at front
 String postData = "?nhietdo=" + String(temperatureC) + "&doam=" + String(humidity) + "&doamdat=" + String(percent);

  String link = "http://192.168.1.42/getdemo.php";

  //http.begin(WiFiClient(),link);     //Specify request destination
  WiFiClient client;
  http.begin(client, link);
  int httpCode = http.POST(postData);            //Send the request
  String payload = http.getString();    //Get the response payload

  Serial.println(httpCode);   //Print HTTP return code
  Serial.println(payload);    //Print request response payload
   
  http.end();  //Close connection
  
  delay(180000);  //GET Data at every 60 seconds
}
