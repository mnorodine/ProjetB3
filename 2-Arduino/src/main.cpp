/////////////////////////////////
// Generated with a lot of love//
// with TUNIOT FOR ESP8266     //
// Website: Easycoding.tn      //
/////////////////////////////////
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char *WiFi_Name       = "Galaxy A10s1304";
const char *WiFi_Password   = "Junior@976";


const char *MQTT_HOST       ="test.mosquitto.org";
unsigned int MQTT_PORT      = 1883;

const char *MQTT_TOPIC      ="DIUEIL/JMPQ/Temperature";

unsigned long  tps= 0;
unsigned long  MessageID = 0;


WiFiClient espClient;
PubSubClient MQTTclient(espClient);


void ReconnectMQTTBroker() 
{
  while (!MQTTclient.connected()) 
  {
    Serial.print("\nConnexion au Broker MQTT:");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (MQTTclient.connect(clientId.c_str())) 
    {
      Serial.println("\nConnexion au Broker MQTT '" +String(MQTT_HOST)+ "' établie !" );
    } 
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(MQTTclient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) 
{
  String MQTT_DATA = "";
  for (unsigned int i=0;i<length;i++) 
  {
    MQTT_DATA += (char)payload[i];
  }
  Serial.print(MQTT_DATA);
}

void WiFiConnect()
{
  WiFi.disconnect();
  delay(3000);
  Serial.println("\n\n\nConnexion au réseau WiFi:");
  WiFi.begin(WiFi_Name,WiFi_Password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print(".");

  }
  Serial.println("\nConnexion au réseau WiFi établie");
  Serial.print("\nAdresse IP: ");
  Serial.println((WiFi.localIP().toString()));
}

void MQTTConnect()
{
  MQTTclient.setServer(MQTT_HOST, MQTT_PORT);
  MQTTclient.subscribe(MQTT_TOPIC,0);
  MQTTclient.setCallback(callback);
} 

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  WiFiConnect();
  MQTTConnect();
}


void MQTTReconnect()
{
  while (!MQTTclient.connected()) 
  {
    if (!MQTTclient.connect("ESP32Client")) 
    {
      Serial.print("echec, code erreur= ");
      Serial.println(MQTTclient.state());
      Serial.println("nouvel essai dans 2s");
      delay(2000);
    }
  }
  MQTTclient.subscribe("DIUEIL/JMPQ/Config/#");//souscription aux topics de configuration
}

//Fonction pour publier un float sur un topic 
void MQTTPublish(String topic, float t)
{
  char top[topic.length()+1];
  topic.toCharArray(top,topic.length()+1);
  char t_char[64];

  MessageID ++;
  String t_str = "{{'ID':"+String(MessageID)+"},{'Temperature':"+ String(t)+ "}}";
  t_str.toCharArray(t_char, t_str.length() + 1);
  MQTTclient.publish(top,t_char);
  Serial.println();
  Serial.print(t_str);
  if (digitalRead(LED_BUILTIN)) digitalWrite(LED_BUILTIN, LOW);
  else digitalWrite(LED_BUILTIN, HIGH);
}


void loop()
{
  MQTTReconnect();
  MQTTclient.loop(); 
  
  //On utilise pas un delay pour ne pas bloquer la réception de messages 
  if (millis()-tps>10000)
  {
     tps=millis();
     float temp = 25 + random(8);
     MQTTPublish("DIUEIL/JMPQ/Temperature",temp);
   }
}
