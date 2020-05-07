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

#ifndef BROADCASTTOPICS_H
#define BROADCASTTOPICS_H

#include <QObject>

namespace
{
	static const QString BROADCAST_TOPIC_START = "broadcast/";

	static const QString RELAY1_TOPIC = "/relay1";
	static const QString RELAY1_FEEDBACK_TOPIC = "/relay1_feedback";

	static const QString RELAY2_TOPIC = "/relay2";
	static const QString RELAY2_FEEDBACK_TOPIC = "/relay2_feedback";

	static const QString RELAY3_TOPIC = "/relay3";
	static const QString RELAY3_FEEDBACK_TOPIC = "/relay3_feedback";

	static const QString TEMPERATURE_TOPIC = "/temperature";
	static const QString HUMIDITY_TOPIC = "/humidity";

	static const QString MOTOR1_TOPIC = "/motor1";
	static const QString MOTOR2_TOPIC = "/motor2";

	static const QString MOTOR1_FEEDBACK_TOPIC = "/motor1_feedback";
	static const QString MOTOR2_FEEDBACK_TOPIC = "/motor2_feedback";

	static const QString WATCHDOG_TOPIC = "/watchdog";
	static const QString WATCHDOG_FEEDBACK_TOPIC = "/watchdog_feedback";
}

#endif // BROADCASTTOPICS_H
