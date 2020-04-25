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

#include <broadcast.h>

int BroadcastPin(const int pinOnBoard)
{
	switch (pinOnBoard)
	{
		case 4: return 2;
		case 2: return 4;
		case 1: return 5;
		case 8: return 15;
		case 7: return 13;
		case 6: return 12;
		case 5: return 14;
		case 0: return 16;
	}
}
