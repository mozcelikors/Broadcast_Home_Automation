/***
 * Copyright (C) 2020 Mustafa Ozcelikors <mozcelikors@gmail.com>
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU General Public License
 * which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/
 *
 * Description:
 *     Broadcast_Home_Automation Watchdog Component
 *
 **/

#include <watchdog.h>

Watchdog::Watchdog(char * topic, char * feedback_topic)
{
	WATCHDOG_TOPIC = topic;
	WATCHDOG_FEEDBACK_TOPIC = feedback_topic;
}

Watchdog::~Watchdog()
{

}

void Watchdog::callback(PubSubClient* client, const char* topic, const byte* payload, unsigned int length)
{
	//Loopback
	if (strcmp(topic, WATCHDOG_TOPIC)==0)
	{
		char data[length];
		for (int i = 0; i < length; i++)
		{
			data[i] = (char)payload[i];
		}
		data[length]=0;

		if (client->connected())
			client->publish(WATCHDOG_FEEDBACK_TOPIC, (const char*) data);
	}
}

void Watchdog::setup(void)
{

}

void Watchdog::reset(void)
{

}

void Watchdog::subscribe (PubSubClient* client)
{
	if (client->connected())
		client->subscribe(WATCHDOG_TOPIC);
}

void Watchdog::publish (PubSubClient* client, const char* data)
{
	if (client->connected())
		client->publish(WATCHDOG_FEEDBACK_TOPIC, data);
}

void Watchdog::loop (PubSubClient* client)
{

}
