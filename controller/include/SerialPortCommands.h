/**
 * Copyright (C) 2021
 * Christian Fischer
 *
 * https://github.com/ChristianFischer/lichtlein
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef __CONTROLLER_SERIALPORTCOMMANDS_H__
#define __CONTROLLER_SERIALPORTCOMMANDS_H__

#include "stdint.h"


namespace lichtlein {

	enum class SerialPortCommands : uint16_t {

		/**
		 * Unused
		 */
		None,

		/**
		 * Request the number of lights present for the light bar.
		 *
		 * Parameter:
		 * None
		 *
		 * Reply:
		 * 32bit integer containing the number of lights
		 */
		GetLightCount,

		/**
		 * Set the led_brightness for the light bar's LEDs
		 *
		 * Parameter:
		 * 8 bit integer containing the desired led_brightness
		 */
		SetBrightness,

		/**
		 * Send a sequence of colors to the controller.
		 *
		 * Parameter:
		 * 16 bit integer for the number if colors to follow
		 * 24 bit RGB value per color
		 */
		ColorSequence,

	};

}

#endif //__CONTROLLER_SERIALPORTCOMMANDS_H__
