#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <string>

// WiFi
const char *ssid = "Agartha";      // Enter your WiFi name
const char *password = "12345678"; // Enter WiFi password
// MQTT Broker
const char *mqtt_broker = "172.20.10.2"; // Enter your WiFi or Ethernet IP
const char *topic = "neutrongate/wifi";
const int mqtt_port = 1883;
WiFiClient espClient;
PubSubClient client(espClient);
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  // Set software serial baud to 115200;
  Serial.begin(115200);

  // connecting to a WiFi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");

  // connecting to a mqtt broker
  client.setServer(mqtt_broker, mqtt_port);

  while (!client.connected())
  {
    String client_id = "esp8266-client-";
    client_id += String(WiFi.macAddress());

    Serial.printf("The client %s connects to mosquitto mqtt broker\n", client_id.c_str());

    if (client.connect(client_id.c_str()))
    {
      Serial.println("Public emqx mqtt broker connected");
      digitalWrite(LED_BUILTIN, LOW);
    }
    else
    {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  // publish and subscribe
  //client.publish(topic, "Hello From ESP8266!");
  client.subscribe(topic);
}

int count = 1;

void loop()
{
  while (count <= 1000) {
    client.publish(topic, String(count).c_str());
    delay(500);
    count++;
    client.loop();
  }
  
}