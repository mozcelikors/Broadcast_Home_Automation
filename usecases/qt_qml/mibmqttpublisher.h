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

#ifndef MIBMQTTPUBLISHER_H
#define MIBMQTTPUBLISHER_H

#include <QObject>
#include <QtMqtt>

#define QOS_LEVEL 0

class MibMQTTPublisher : public QObject
{
	Q_OBJECT
public:
	explicit MibMQTTPublisher(QObject *parent = nullptr);

public Q_SLOTS:
	void connectTo (QString hostname, quint16 port);
	void publishToTopic (QString topic_name, QString text);

signals:

public slots:
	void connectedCallback (void);
	void errorChanged(QMqttClient::ClientError error);

private:
	QMqttClient* publisher;
	int f_connected;
};

#endif // MIBMQTTPUBLISHER_H
