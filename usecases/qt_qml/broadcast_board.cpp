/***
 * Copyright (C) 2020 Mustafa Ozcelikors <mozcelikors@gmail.com>
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU General Public License
 * which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/
 *
 * Description:
 *     Broadcast_Home_Automation Qt API
 *     http://www.mozcelikors.com
 *
 **/

#include "broadcast_board.h"
#include "broadcast_topics.h"
#include <QDebug>

BroadcastBoard::BroadcastBoard(QObject *parent) : QObject(parent),
	publisher(nullptr),
	subscriber(nullptr),
	DEVICE_ID(0)
{
	if (this->publisher == nullptr)
	{
		publisher = new MibMQTTPublisher();
	}
	if (this->subscriber == nullptr)
	{
		subscriber = new QMqttClient();
		connect (this->subscriber, &QMqttClient::errorChanged ,this, &BroadcastBoard::errorChanged);
		connect (this->subscriber, &QMqttClient::connected ,this, &BroadcastBoard::connectedCallback);
	}
}

void BroadcastBoard::connectTo (QString hostname, quint16 port)
{
	if (this->publisher != nullptr)
	{
		publisher->connectTo(hostname, port);
	}

	if (this->subscriber != nullptr)
	{
		subscriber->setHostname(hostname);
		subscriber->setPort(port);
		subscriber->connectToHost();
	}
}

void BroadcastBoard::setDeviceId(int id)
{
	qDebug() << "BroadcastBoard: Device ID is "+QString::number(id);
	this->DEVICE_ID = id;
}

QString BroadcastBoard::getFullTopicName(QString topic)
{
	//qDebug() << BROADCAST_TOPIC_START+QString::number(this->DEVICE_ID)+topic;
	return BROADCAST_TOPIC_START+QString::number(this->DEVICE_ID)+topic;
}

/********** Callbacks ****************/
void BroadcastBoard::connectedCallback (void)
{
	qDebug() << "BroadcastBoard: Now connected.";

    if (this->subscriber != nullptr)
    {
        QMqttTopicFilter t_f;
	// !!! BEWARE !!!
	//Set to t_f.setFilter("#"); for all topics
	t_f.setFilter(BROADCAST_TOPIC_START+QString::number(this->DEVICE_ID)+"/#");
        subscriber->subscribe(t_f, QOS_LEVEL);

	connect(subscriber, &QMqttClient::messageReceived, this, &BroadcastBoard::receivedMessage);
    }
}

void BroadcastBoard::receivedMessage(const QByteArray &message, const QMqttTopicName &topic)
{
	/*const QString content = QDateTime::currentDateTime().toString()
                + QLatin1String(" Received Topic: ")
                + topic.name()
                + QLatin1String(" Message: ")
                + message
                + QLatin1Char('\n');
	qDebug() << content;*/


	if(topic.name() == getFullTopicName(RELAY1_FEEDBACK_TOPIC))
	{
		setRelay1Feedback(QString(message));
		emit relayInfoReceived();
	}
	else if(topic.name() == getFullTopicName(RELAY2_FEEDBACK_TOPIC))
	{
		setRelay2Feedback(QString(message));
		emit relayInfoReceived();
	}
	else if(topic.name() == getFullTopicName(RELAY3_FEEDBACK_TOPIC))
	{
		setRelay3Feedback(QString(message));
		emit relayInfoReceived();
	}
	else if(topic.name() == getFullTopicName(TEMPERATURE_TOPIC))
	{
		setTemperature(QString(message));
		emit temperatureReceived();
	}
	else if(topic.name() == getFullTopicName(HUMIDITY_TOPIC))
	{
		setHumidity(QString(message));
		emit humidityReceived();
	}
	else if(topic.name() == getFullTopicName(MOTOR1_FEEDBACK_TOPIC))
	{
		setMotor1Feedback(QString(message));
		emit motor1InfoReceived();
	}
	else if(topic.name() == getFullTopicName(MOTOR2_FEEDBACK_TOPIC))
	{
		setMotor2Feedback(QString(message));
		emit motor2InfoReceived();
	}
	else if(topic.name() == getFullTopicName(WATCHDOG_FEEDBACK_TOPIC))
	{
		setWatchdogFeedback(QString(message));
		emit watchdogInfoReceived();
	}
}

void BroadcastBoard::errorChanged(QMqttClient::ClientError error)
{
    qDebug() << error;
}

/****************** Get methods of private objects ********************/
QString BroadcastBoard::getRelay1Feedback() const
{
	return relay1_feedback;
}
QString BroadcastBoard::getRelay2Feedback() const
{
	return relay2_feedback;
}
QString BroadcastBoard::getRelay3Feedback() const
{
	return relay3_feedback;
}
QString BroadcastBoard::getHumidity() const
{
	return humidity;
}
QString BroadcastBoard::getTemperature() const
{
	return temperature;
}
QString BroadcastBoard::getMotor1Feedback() const
{
	return motor1;
}
QString BroadcastBoard::getMotor2Feedback() const
{
	return motor2;
}
QString BroadcastBoard::getWatchdogFeedback() const
{
	return watchdog_feedback;
}

/*********************** Set methods of private objects *********************/
void BroadcastBoard::setRelay1Feedback(const QString relay1_fb)
{
	relay1_feedback = relay1_fb;
}
void BroadcastBoard::setRelay2Feedback(const QString relay2_fb)
{
	relay2_feedback = relay2_fb;
}
void BroadcastBoard::setRelay3Feedback(const QString relay3_fb)
{
	relay3_feedback = relay3_fb;
}
void BroadcastBoard::setTemperature(const QString temp)
{
	temperature = temp;
}
void BroadcastBoard::setHumidity(const QString hum)
{
	humidity = hum;
}
void BroadcastBoard::setMotor1Feedback(const QString m1)
{
	motor1 = m1;
}
void BroadcastBoard::setMotor2Feedback(const QString m2)
{
	motor2 = m2;
}
void BroadcastBoard::setWatchdogFeedback(const QString watchdog)
{
	watchdog_feedback = watchdog;
}

/****************************** Publisher functions ******************************/
void BroadcastBoard::publish_relay1(QString data)
{
	publisher->publishToTopic(getFullTopicName(RELAY1_TOPIC), data);
}

void BroadcastBoard::publish_relay2(QString data)
{
	publisher->publishToTopic(getFullTopicName(RELAY2_TOPIC), data);
}

void BroadcastBoard::publish_relay3(QString data)
{
	publisher->publishToTopic(getFullTopicName(RELAY3_TOPIC), data);
}

void BroadcastBoard::publish_motor1(QString data)
{
	publisher->publishToTopic(getFullTopicName(MOTOR1_TOPIC), data);
}

void BroadcastBoard::publish_motor2(QString data)
{
	publisher->publishToTopic(getFullTopicName(MOTOR2_TOPIC), data);
}

void BroadcastBoard::publish_watchdog(QString data)
{
	publisher->publishToTopic(getFullTopicName(WATCHDOG_TOPIC), data);
}
