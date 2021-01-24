# Subscriber

import paho.mqtt.client as mqtt


broker 	= "test.mosquitto.org"
port 	= 1883
topic	= "DIUEIL/JMPQ/Temperature"

client = mqtt.Client("Subdevice")
client.connect(broker, port)

def on_connect(client, userdata, flags, rc):
	print("Connected to a broker !")
	client.subscribe(topic)


def on_message(client, userdata, message):
    print(message.payload.decode("utf-8"))

while True:
	client.on_connect = on_connect
	client.on_message = on_message
	client.loop_forever()

    