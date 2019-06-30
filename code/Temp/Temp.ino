#include "DHT.h"
#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#define DHTPIN 4 // IMPORTANT D2 on NodeMCU is GPIO 4
int led=5;
int led_red=2;

#define DHTTYPE DHT22 // DHT 22 

const char *ssid = "wifi name"; // Your wifi ssid
const char *password = "wifi  passowrd"; //Your wifi password

unsigned long myChannelNumber = 704427;
const char * myWriteAPIKey = "THINK_SPEAK WRITE API KEY";

const char* server = "api.thingspeak.com";

WiFiClient client;

DHT dht(DHTPIN, DHTTYPE);    //set the dht sensor

void updateThingSpeak(float t, float h){     //function to send data to thinkspeak
    ThingSpeak.setField(1,t);
    ThingSpeak.setField(2,h);
    ThingSpeak.writeFields(myChannelNumber,myWriteAPIKey);
    delay(1000);
}

void setup()
{
    // put your setup code here, to run once:
    pinMode(led,OUTPUT);
    pinMode(led_red,OUTPUT);
    digitalWrite(led,LOW);
    digitalWrite(led_red,HIGH);
    Serial.begin(115200);
    dht.begin();
    ThingSpeak.begin(client);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)    //check the wifi status
    {
        delay(500);
        digitalWrite(led_red,HIGH);
        Serial.print("waiting for wifi to be connected");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    digitalWrite(led_red,LOW);
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void loop()
{
    // put your main code here, to run repeatedly:
    float h = dht.readHumidity();
    //celcius
    float t = dht.readTemperature();
    //fahrenheit
    float f = dht.readTemperature(true);

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t) || isnan(f))
    {
        Serial.println("Failed to read from DHT sensor!");
        digitalWrite(led,LOW);
        digitalWrite(led_red,HIGH);
        return;
    }
    digitalWrite(led,HIGH);
    digitalWrite(led_red,LOW);
    // Compute heat index in Fahrenheit (the default)
    float hif = dht.computeHeatIndex(f, h);
    // Compute heat index in Celcius
    float hic = dht.computeHeatIndex(t, h, false);

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.print(f);
    Serial.print(" *F\t");
    Serial.print("Heat index: ");
    Serial.print(hic);
    Serial.print(" *C ");
    Serial.print(hif);
    Serial.println(" *F");

    if(client.connect(server,80)){
        updateThingSpeak(t,h);
    }
}
