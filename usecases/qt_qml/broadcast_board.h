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

#ifndef BROADCASTBOARD_H
#define BROADCASTBOARD_H

#include <QObject>
#include <QtMqtt>

#include "mibmqttpublisher.h"

#define QOS_LEVEL 0

class BroadcastBoard : public QObject
{
	Q_OBJECT
public:
	explicit BroadcastBoard(QObject *parent = nullptr);

	void setRelay1Feedback(const QString relay1);
	void setRelay2Feedback(const QString relay2);
	void setRelay3Feedback(const QString relay3);
	void setMotor1Feedback(const QString m1);
	void setMotor2Feedback(const QString m2);
	void setTemperature(const QString temp);
	void setHumidity(const QString hum);
	void setWatchdogFeedback(const QString watchdog);

public Q_SLOTS:
    void connectTo(QString hostname, quint16 port);

	void setDeviceId(int id);
	QString getFullTopicName(QString topic);

	QString getRelay1Feedback() const;
	QString getRelay2Feedback() const;
	QString getRelay3Feedback() const;
	QString getTemperature() const;
	QString getHumidity() const;
	QString getMotor1Feedback() const;
	QString getMotor2Feedback() const;
	QString getWatchdogFeedback() const;

	void publish_relay1(QString data);
	void publish_relay2(QString data);
	void publish_relay3(QString data);
	void publish_motor1(QString data);
	void publish_motor2(QString data);
	void publish_watchdog(QString data);

signals:
	void relayInfoReceived();
	void temperatureReceived();
	void humidityReceived();
	void motor1InfoReceived();
	void motor2InfoReceived();
	void watchdogInfoReceived();

public slots:
	void connectedCallback (void);
	void errorChanged(QMqttClient::ClientError error);
	void receivedMessage(const QByteArray &message, const QMqttTopicName &topic);

private:
	int DEVICE_ID = 0;

private:
	QMqttClient* subscriber;
	MibMQTTPublisher *publisher;

private:
	QString relay1;
	QString relay2;
	QString relay3;
	QString relay1_feedback;
	QString relay2_feedback;
	QString relay3_feedback;

	QString temperature;
	QString humidity;

	QString motor1;
	QString motor1_feedback;

	QString motor2;
	QString motor2_feedback;

	QString watchdog;
	QString watchdog_feedback;

};

#endif // BROADCASTBOARD_H
