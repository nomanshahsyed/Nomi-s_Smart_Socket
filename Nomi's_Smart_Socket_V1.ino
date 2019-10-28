
#include <ThingerESP8266.h>

#define USERNAME "USERNAME"
#define DEVICE_ID "DEVICE_ID"
#define DEVICE_CREDENTIAL "DEVICE_CREDENTIAL"

#define SSID "SSID"
#define SSID_PASSWORD "SSID_PASSWORD"

const int relay1 = 14;
const int relay2 = 4;
const int relay3 = 13;
const int relay4 = 12;

int t = 0;

ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

void setup(void)
{
    Serial.begin(115200);


    pinMode(relay1, OUTPUT);
    pinMode(relay2, OUTPUT);
    pinMode(relay3, OUTPUT);
    pinMode(relay4, OUTPUT);

    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    digitalWrite(relay3, LOW);
    digitalWrite(relay4, LOW);

    thing.add_wifi(SSID, SSID_PASSWORD);

    thing["relay1"] << digitalPin(relay1);
    thing["relay2"] << digitalPin(relay2);
    thing["relay3"] << digitalPin(relay3);
    thing["relay4"] << digitalPin(relay4);
}

void loop()
{
    thing.handle();
}
