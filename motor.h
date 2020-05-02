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

#ifndef MOTOR_H
#define MOTOR_H

#include <broadcast.h>
#include <broadcast_interface.h>

class Motor : public BroadcastInterface {
public:
	Motor(int pin, char * topic, char * feedback_topic);
	~Motor();
	void callback(PubSubClient* client, const char* topic, const byte* payload, unsigned int length);
	void setup(void);
	void reset(void);
	void subscribe (PubSubClient* client);
	void publish (PubSubClient* client, const char* data);
	void loop (PubSubClient* client);

private:
	int MOTOR_VAL;
	int PREV_MOTOR_VAL;
	int MOTOR_PIN;
	char* MOTOR_TOPIC;
	char* MOTOR_FEEDBACK_TOPIC;
};

#endif
