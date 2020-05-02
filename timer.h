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

#ifndef TIMER_H
#define TIMER_H

#include <broadcast.h>
#include <broadcast_interface.h>

class Timer {
public:
	Timer();
	~Timer();
	void recordNow(void);
	long getRecordedTime(void);
	long getNow (void);
	void setRecordedTime(long time);

private:
	long* now;
	long now_ = 0;
};

#endif
