/***
 * Copyright (C) 2020 Mustafa Ozcelikors <mozcelikors@gmail.com>
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU General Public License
 * which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/
 *
 * Description:
 *     Broadcast_Home_Automation Relay Component
 *
 **/

#include <relay.h>

Relay::Relay(int pin, char * topic, char * feedback_topic)
{
	RELAY_STATE = 0;
	PREV_RELAY_STATE = 0;
	RELAY_PIN = BroadcastPin(pin);
	RELAY_TOPIC = topic;
	RELAY_FEEDBACK_TOPIC = feedback_topic;
}

Relay::~Relay()
{

}

void Relay::callback(PubSubClient* client, const char* topic, const byte* payload, unsigned int length)
{
	if (strcmp(topic, RELAY_TOPIC)==0)
	{
		if ((char)payload[0] == '1')
		{
			digitalWrite(RELAY_PIN, HIGH);
			client->publish(RELAY_FEEDBACK_TOPIC,"1");
		}
		else
		{
			digitalWrite(RELAY_PIN, LOW);
			client->publish(RELAY_FEEDBACK_TOPIC,"0");
		}
	}
}

void Relay::setup(void)
{
	pinMode(RELAY_PIN, OUTPUT);
	digitalWrite(RELAY_PIN, LOW);
	RELAY_STATE = 0;
}

void Relay::reset(void)
{
	digitalWrite(RELAY_PIN, LOW);
	RELAY_STATE = 0;
}

void Relay::subscribe (PubSubClient* client)
{
	client->subscribe(RELAY_TOPIC);
}

void Relay::publish (PubSubClient* client, const char* data)
{
	client->publish(RELAY_FEEDBACK_TOPIC, data);
}

void Relay::loop (PubSubClient* client, long* now)
{

}
