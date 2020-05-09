/***
 * Copyright (C) 2020 Mustafa Ozcelikors <mozcelikors@gmail.com>
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU General Public License
 * which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/
 *
 * Description:
 *     Broadcast_Home_Automation
 *
 **/

// For WiFi + MQTT
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <string.h>

#include <broadcast.h>
#include <relay.h>
#include <temperaturesensor.h>
#include <motor.h>
#include <watchdog.h>

#define DEVICE_ID 1
#define DEBUG 1

// For power mgmt
extern "C" {
#include "user_interface.h"
}

Watchdog* watchdog1;
Relay* relay1;
Relay* relay2;
Relay* relay3;
TemperatureSensor* temperaturesensor1;
Motor* motor1;
Motor* motor2;

// Update these with values suitable for your network.
const char* ssid = "SUPERONLINE_WiFi_5089";
const char* password = "UTNJ47YFTFU3";
const char* mqtt_server = "192.168.1.35"; // This is the static IP for media in the box on home network

WiFiClient espClient;
PubSubClient client(espClient);
PubSubClient* client_ptr;

void setup_wifi()
{
	delay(10);

#ifdef DEBUG
	// We start by connecting to a WiFi network
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(ssid);
#endif

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
#ifdef DEBUG
		Serial.print(".");
#endif
	}

	randomSeed(micros());

#ifdef DEBUG
	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());
#endif
}

void callback(char* topic, byte* payload, unsigned int length) {
#ifdef DEBUG
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	for (int i = 0; i < length; i++)
	{
		Serial.print((char)payload[i]);
	}
	Serial.println();
#endif

	watchdog1->callback(client_ptr, topic, payload, length);
	motor1->callback(client_ptr, topic, payload, length);
	motor2->callback(client_ptr, topic, payload, length);
	relay1->callback(client_ptr, topic, payload, length);
	relay2->callback(client_ptr, topic, payload, length);
	relay3->callback(client_ptr, topic, payload, length);
	temperaturesensor1->callback(client_ptr, topic, payload, length);
}

void publish()
{
	watchdog1->publish(client_ptr, "1");
	relay1->publish(client_ptr, "1");
	relay2->publish(client_ptr, "1");
	relay3->publish(client_ptr, "1");
	motor1->publish(client_ptr, "90");
	motor2->publish(client_ptr, "90");
}

void subscribe()
{
	watchdog1->subscribe(client_ptr);
	relay1->subscribe(client_ptr);
	relay2->subscribe(client_ptr);
	relay3->subscribe(client_ptr);
	motor1->subscribe(client_ptr);
	motor2->subscribe(client_ptr);
}

void reconnect() {
	// Loop until we're reconnected
	while (!client_ptr->connected())
	{
#ifdef DEBUG
		Serial.print("Attempting MQTT connection...");
#endif
		// Attempt to connect
		if (client_ptr->connect(String("BroadcastNode-"+DEVICE_ID).c_str()))
		{
#ifdef DEBUG
			Serial.println("connected");
#endif
			//Publish initial values
			publish();
			//Resubscribe
			subscribe();
		}
		else
		{
#ifdef DEBUG
			Serial.print("failed, rc=");
			Serial.print(client_ptr->state());
			Serial.println(" try again in 1000 milliseconds");
#endif
			// Wait 300ms before retrying
			delay(1000);
		}
	}
}

char* constructTopic(char* topicEnd)
{
	// Surely leaks memory, do not overuse this.
	char* topic;
	topic = (char*) malloc(sizeof (char) * (40));
	sprintf(topic,"broadcast/%i/%s",DEVICE_ID,topicEnd);
	return topic;
}

void setup()
{
#ifdef DEBUG
	Serial.begin(115200);
#endif

	client_ptr = &client;

	watchdog1 = new Watchdog(constructTopic("watchdog"), constructTopic("watchdog_feedback"));
	relay1 = new Relay(0, constructTopic("relay1"), constructTopic("relay1_feedback"));
	relay2 = new Relay(1, constructTopic("relay2"), constructTopic("relay2_feedback"));
	relay3 = new Relay(2, constructTopic("relay3"), constructTopic("relay3_feedback"));
	temperaturesensor1 = new TemperatureSensor(7, constructTopic("temperature"), constructTopic("humidity"));
	motor1 = new Motor(3, constructTopic("motor1"), constructTopic("motor1_feedback"));
	motor2 = new Motor(3, constructTopic("motor2"), constructTopic("motor2_feedback"));

	watchdog1->setup();
	relay1->setup();
	relay2->setup();
	relay3->setup();
	temperaturesensor1->setup();
	motor1->setup();
	motor2->setup();

	setup_wifi();

	client_ptr->setServer(mqtt_server, 1883);
	client_ptr->setCallback(callback);

	/* Attempt MQTT connection */
	reconnect();
}

void reset()
{
	watchdog1->reset();
	relay1->reset();
	relay2->reset();
	relay3->reset();
	motor1->reset();
	motor2->reset();
	temperaturesensor1->reset();
}

void relays_on()
{
	relay1->on();
	relay2->on();
	relay3->on();
}

void loop()
{
	if(WiFi.status() != WL_CONNECTED)
	{
		// For safety, if WiFi is lost, keep relays on
		relays_on();

		// Try reconnecting to wifi
		WiFi.mode(WIFI_STA);
		WiFi.begin(ssid,password);
		delay(2000);
		reset();
	}
	else if (!client_ptr->connected())
	{
		// For safety, if MQTT server is lost, keep relays on
		relays_on();

		// Try reconnecting to MQTT server
		reconnect();
		delay(2000);
		reset();
	}
	else
	{
		watchdog1->loop(client_ptr);
		relay1->loop(client_ptr);
		relay2->loop(client_ptr);
		relay3->loop(client_ptr);
		temperaturesensor1->loop(client_ptr);
		motor1->loop(client_ptr);
		motor2->loop(client_ptr);

		client_ptr->loop();
	}

	// Provide liveness, avoid starvation of tasks
	delay(20);
}

