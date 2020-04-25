/***
 * Copyright (C) 2020 Mustafa Ozcelikors <mozcelikors@gmail.com>
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU General Public License
 * which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/
 *
 * Description:
 *     Broadcast_Home_Automation Virtual Interface
 *
 **/

#ifndef BROADCASTINTERFACE_H
#define BROADCASTINTERFACE_H

#include <broadcast.h>

class BroadcastInterface {
public:
	virtual void callback(PubSubClient* client, const char* topic, const byte* payload, unsigned int length) = 0;
	virtual void setup(void) = 0;
	virtual void reset(void) = 0;
	virtual void subscribe (PubSubClient* client) = 0;
	virtual void publish (PubSubClient* client, const char* data) = 0;
	virtual void loop (PubSubClient* client, long* now) = 0;
};

#endif
