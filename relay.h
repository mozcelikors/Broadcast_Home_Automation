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

#ifndef RELAY_H
#define RELAY_H

#include <broadcast.h>
#include <broadcast_interface.h>

class Relay : public BroadcastInterface {
public:
	Relay(int pin, char * topic, char * feedback_topic);
	~Relay();
	void callback(PubSubClient* client, const char* topic, const byte* payload, unsigned int length);
	void setup(void);
	void reset(void);
	void subscribe (PubSubClient* client);
	void publish (PubSubClient* client, const char* data);
	void loop (PubSubClient* client, long* now);

	// New methods
	void on(void);
	void off(void);

private:
	int RELAY_STATE;
	int PREV_RELAY_STATE;
	int RELAY_PIN;
	char* RELAY_TOPIC;
	char* RELAY_FEEDBACK_TOPIC;
};

#endif
