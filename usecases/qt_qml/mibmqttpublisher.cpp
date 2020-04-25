/***
 * Copyright (C) 2020 Mustafa Ozcelikors <mozcelikors@gmail.com>
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU General Public License
 * which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/
 *
 * Description:
 *     Media In the Box project Generic MQTT Publisher API for Qt/QML
 *     http://www.mozcelikors.com
 *
 **/

#include "mibmqttpublisher.h"
#include <QDebug>
#include <unistd.h>

MibMQTTPublisher::MibMQTTPublisher(QObject *parent) : QObject(parent),
    f_connected(0),
    publisher(nullptr)
{
    if (this->publisher == nullptr)
    {
        publisher = new QMqttClient();

	connect (this->publisher, &QMqttClient::errorChanged ,this, &MibMQTTPublisher::errorChanged);
	connect (this->publisher, &QMqttClient::connected ,this, &MibMQTTPublisher::connectedCallback);
    }
}

void MibMQTTPublisher::connectTo (QString hostname, quint16 port)
{
    if (this->publisher != nullptr)
    {
        publisher->setHostname(hostname);
        publisher->setPort(port);
        publisher->connectToHost();
    }
}

void MibMQTTPublisher::publishToTopic (QString topic_name, QString text)
{
    if (this->publisher != nullptr && f_connected == 1)
    {
        QMqttTopicName mqtt_topic_name;
        mqtt_topic_name.setName(topic_name);
        if ( publisher->publish(mqtt_topic_name, text.toUtf8(), QOS_LEVEL)  == -1)
			qDebug() << "MibMQTTPublisher: Could not publish message.";
    }
    else
    {
           if (f_connected == 0)
			   qDebug() << "MibMQTTPublisher: Not connected yet.";
           else
			   qDebug() << "MibMQTTPublisher: published does not exist.";
    }
}


/********** Callbacks ****************/
void MibMQTTPublisher::connectedCallback (void)
{
	qDebug() << "MibMQTTPublisher: Now connected.";
    f_connected = 1;
}

void MibMQTTPublisher::errorChanged(QMqttClient::ClientError error)
{
    qDebug() << error;
}

