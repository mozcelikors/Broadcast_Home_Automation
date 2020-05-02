/***
 * Copyright (C) 2020 Mustafa Ozcelikors <mozcelikors@gmail.com>
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the GNU General Public License
 * which accompanies this distribution, and is available at
 * http://www.gnu.org/licenses/
 *
 * Description:
 *     Broadcast_Home_Automation Timer Component
 *
 **/

#include <timer.h>

Timer::Timer()
{
	now = &now_;
}

void Timer::recordNow(void)
{
	*now = getNow();
}

long Timer::getRecordedTime(void)
{
	return *now;
}

long Timer::getNow(void)
{
	return millis();
}

void Timer::setRecordedTime(long time)
{
	*now = time;
}
