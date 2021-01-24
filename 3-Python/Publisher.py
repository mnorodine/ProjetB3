# Publisher

import paho.mqtt.client as mqtt


host 	= "test.mosquitto.org"
port 	= 1883
topic	= "DIUEIL/JMPQ/Temperature"

client = mqtt.Client("Subdevice")
client.connect(host, port)


Msg = "Hello DIUEIL JMPQ"
client.publish(topic, Msg )

"""
Msg = input("Message : ")
print("Message is "+ Msg)
while Msg != "Q" and Msg > "" :
	client.publish(topic, Msg )
	Msg = input("Message : ")
"""