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

#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <broadcast.h>
#include <broadcast_interface.h>

class Watchdog : public BroadcastInterface {
public:
	Watchdog(char * topic, char * feedback_topic);
	~Watchdog();
	void callback(PubSubClient* client, const char* topic, const byte* payload, unsigned int length);
	void setup(void);
	void reset(void);
	void subscribe (PubSubClient* client);
	void publish (PubSubClient* client, const char* data);
	void loop (PubSubClient* client);

private:
	char* WATCHDOG_TOPIC;
	char* WATCHDOG_FEEDBACK_TOPIC;
};

#endif
