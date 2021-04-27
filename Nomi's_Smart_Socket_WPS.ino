#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

#define USERNAME "USERNAME"
#define DEVICE_ID "DEVICE_ID"
#define DEVICE_CREDENTIAL "DEVICE_CREDENTIAL"

const int relay1 = 14;
const int relay2 = 4;
const int relay3 = 13;
const int relay4 = 12;

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup(void)
{
    Serial.begin(115200);

    pinMode(relay1, OUTPUT);
    pinMode(relay2, OUTPUT);
    pinMode(relay3, OUTPUT);
    pinMode(relay4, OUTPUT);

    WiFi.mode(WIFI_STA);
    WiFi.begin("", ""); //If the wifi credentials are stored, esp will try to connect

    digitalWrite(relay1, HIGH); // Just an indication that wps is starting

    delay(5000);

    if (WiFi.status() != WL_CONNECTED)
    {

        Serial.println("\nAttempting connection ...");

        WiFi.beginWPSConfig();

        delay(5000);

        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println("Connected!");
            Serial.println(WiFi.localIP());
            Serial.println(WiFi.SSID());
            Serial.println(WiFi.macAddress());

            digitalWrite(relay2, HIGH);
            delay(500);
        }
        else
        {
            Serial.println("Connection failed!");
            digitalWrite(relay3, HIGH);
            delay(500);
        }
    }
    else
    {
        Serial.println("\nConnection already established.");
        digitalWrite(relay4, HIGH);
        delay(500);
    }

    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    digitalWrite(relay3, LOW);
    digitalWrite(relay4, LOW);

    thing.add_wifi(WiFi.SSID().c_str(), WiFi.psk().c_str());

    thing["relay1"] << digitalPin(relay1);
    thing["relay2"] << digitalPin(relay2);
    thing["relay3"] << digitalPin(relay3);
    thing["relay4"] << digitalPin(relay4);
}

void loop()
{
    thing.handle();
}