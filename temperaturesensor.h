/***
 * Copyright (C) 2020 Mustafa Ozcelikors <mozcelikors@gmail.com>
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU General Public License
 * which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/
 *
 * Description:
 *     Broadcast_Home_Automation Temperature Sensor Component
 *
 **/

#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include <broadcast.h>
#include <broadcast_interface.h>
#include <DHT.h>

#define DHT_TYPE DHT22

class TemperatureSensor : public BroadcastInterface {
public:
	TemperatureSensor(int pin, char * temp_topic, char * hum_topic);
	~TemperatureSensor();
	void callback(PubSubClient* client, const char* topic, const byte* payload, unsigned int length);
	void setup(void);
	void reset(void);
	void subscribe (PubSubClient* client);
	void publish (PubSubClient* client, const char* data);
	void loop (PubSubClient* client, long* now);

private:
	DHT* dht = nullptr;
	float TEMPERATURE = 0.0;
	float HUMIDITY = 0.0;
	float PREV_TEMPERATURE = 0.0;
	float PREV_HUMIDITY = 0.0;
	int TEMPERATURESENSOR_PIN;
	char* TEMPERATURE_TOPIC;
	char* HUMIDITY_TOPIC;
};

#endif
