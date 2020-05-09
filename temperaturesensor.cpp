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

#include <temperaturesensor.h>

TemperatureSensor::TemperatureSensor(int pin, char * temp_topic, char * hum_topic)
{
	TEMPERATURESENSOR_PIN = BroadcastPin(pin);
	TEMPERATURE_TOPIC = temp_topic;
	HUMIDITY_TOPIC = hum_topic;
	dht = new DHT(TEMPERATURESENSOR_PIN, DHT_TYPE);
}

TemperatureSensor::~TemperatureSensor()
{
	if (dht != nullptr)
	{
		delete dht;
	}
}

void TemperatureSensor::callback(PubSubClient* client, const char* topic, const byte* payload, unsigned int length)
{

}

void TemperatureSensor::setup(void)
{
	dht->begin();
}

void TemperatureSensor::reset(void)
{

}

void TemperatureSensor::subscribe (PubSubClient* client)
{

}

void TemperatureSensor::publish (PubSubClient* client, const char* data)
{

}

void TemperatureSensor::loop (PubSubClient* client)
{
	if (client->connected())
	{
		TEMPERATURE = dht->readTemperature();
		//Serial.println(TEMPERATURE);
		HUMIDITY = dht->readHumidity();
		//Serial.println(HUMIDITY);
		if ((PREV_TEMPERATURE != TEMPERATURE || PREV_HUMIDITY != HUMIDITY) || temp_timer.getNow()-temp_timer.getRecordedTime() > 8000)
		{
			char DHT_TEMP_char[8];
			char DHT_HUMIDITY_char[8];

			dtostrf(TEMPERATURE, 6, 2, DHT_TEMP_char);
			dtostrf(HUMIDITY, 6, 2, DHT_HUMIDITY_char);

			if (client->connected())
				client->publish(TEMPERATURE_TOPIC,  DHT_TEMP_char);

			delay(100);

			if (client->connected())
				client->publish(HUMIDITY_TOPIC,     DHT_HUMIDITY_char);

			PREV_TEMPERATURE = TEMPERATURE;
			PREV_HUMIDITY = HUMIDITY;

			temp_timer.recordNow();
		}
		client->loop();
	}
}
