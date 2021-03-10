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

#ifndef __CONTROLLER_STREAMCONTROLLER_H__
#define __CONTROLLER_STREAMCONTROLLER_H__

#include "Layer.h"

namespace lichtlein {

	class LightBar;


	/**
	 * Controller class to handle a color stream received via serial port.
	 * The StreamController will hold a layer of the displayed light bar
	 * to forward all received color information onto that layer.
	 */
	class StreamController
	{
	public:
		StreamController() = default;
		~StreamController() = default;

	public:
		/**
		 * Initialize the controller with the LightBar being used.
		 * @param light_bar the LightBar the controller will attach to
		 */
		void init(LightBar* light_bar);

		/**
		 * Updates the controller.
		 * @param dt The time passed in milliseconds
		 */
		void update(uint32_t dt);

		/**
		 * Reads color information from the serial port.
		 * This will expect the information in a format as described
		 * for the SerialPortCommands::ColorSequence command.
		 */
		void readColorStreamFromSerial();

	private:
		/**
		 * Get the pointer to the layer the controller is sending the color information to.
		 * If there is currently no layer reserved, it will acquire a new layer.
		 */
		Layer* getOrCreateLayer();

		/**
		 * Disable the controller and frees it's layer, if any.
		 */
		void disable();

		/**
		 * Reset the timer for the last signal received.
		 */
		void resetLastSignal();

	private:
		LightBar* light_bar    = nullptr;
		Layer*    stream_layer = nullptr;
		uint32_t  last_signal  = 0;
	};

}

#endif //__CONTROLLER_STREAMCONTROLLER_H__
