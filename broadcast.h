/***
 * Copyright (C) 2020 Mustafa Ozcelikors <mozcelikors@gmail.com>
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU General Public License
 * which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/
 *
 * Description:
 *     Broadcast_Home_Automation Pins
 *
 **/

#ifndef BROADCAST_H
#define BROADCAST_H

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <string.h>

int BroadcastPin(const int pinOnBoard);

#endif
