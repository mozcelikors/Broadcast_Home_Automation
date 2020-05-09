/***
 * Copyright (C) 2020 Mustafa Ozcelikors <mozcelikors@gmail.com>
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU General Public License
 * which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/
 *
 * Description:
 *     Broadcast_Home_Automation Motor Component
 *
 **/

#include <motor.h>

Motor::Motor(int pin, char * topic, char * feedback_topic)
{
	MOTOR_VAL = 90;
	PREV_MOTOR_VAL = 90;
	MOTOR_PIN = BroadcastPin(pin);
	MOTOR_TOPIC = topic;
	MOTOR_FEEDBACK_TOPIC = feedback_topic;
}

Motor::~Motor()
{

}

void Motor::callback(PubSubClient* client, const char* topic, const byte* payload, unsigned int length)
{
	//Table heights are loopback for now
	if (strcmp(topic, MOTOR_TOPIC)==0)
	{
		char data[length];
		for (int i = 0; i < length; i++)
		{
			data[i] = (char)payload[i];
		}
		data[length]=0;

		if (client->connected())
			client->publish(MOTOR_FEEDBACK_TOPIC, (const char*) data);
	}
}

void Motor::setup(void)
{

}

void Motor::reset(void)
{
	MOTOR_VAL = 90;
	PREV_MOTOR_VAL = 90;
}

void Motor::subscribe (PubSubClient* client)
{
	if (client->connected())
		client->subscribe(MOTOR_TOPIC);
}

void Motor::publish (PubSubClient* client, const char* data)
{
	if (client->connected())
		client->publish(MOTOR_FEEDBACK_TOPIC, data);
}

void Motor::loop (PubSubClient* client)
{
	if (client->connected())
		client->loop();
}
