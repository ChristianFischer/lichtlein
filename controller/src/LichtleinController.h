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

#ifndef __CONTROLLER_LICHTLEINCONTROLLER_H__
#define __CONTROLLER_LICHTLEINCONTROLLER_H__

#include "LightBar.h"
#include "StreamController.h"

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>


namespace lichtlein {

	class LichtleinController
	{
	public:
		LichtleinController();
		~LichtleinController();

		LichtleinController(const LichtleinController&) = delete;
		LichtleinController(LichtleinController&&) = delete;

		LichtleinController& operator=(const LichtleinController&) = delete;
		LichtleinController& operator=(LichtleinController&&) = delete;

	public:
		/// The time in milliseconds which should pass between each update
		static constexpr uint32_t UPDATE_TICK_TIME    = 50;

		/// The number of LEDs on the attached light bar
		static constexpr uint16_t LIGHT_BAR_LED_COUNT = 60;

		/// The Arduino's pin, where the light bar is attached on
		static constexpr uint16_t LIGHT_BAR_PIN       = 2;

		/// Baud rate for communication via serial port
		static constexpr uint32_t SERIAL_BAUD_RATE    = 9600;

	public:
		/**
		 * Initializes the controller and all of it's components.
		 */
		void init();

		/**
		 * Dispose and cleanup all of the controller's components.
		 */
		void dispose();

		/**
		 * Periodically updates the controller and all of it's components.
		 */
		void update();

	public:
		/**
		 * Checks whether the controller is still alive.
		 */
		bool isAlive() const;

		/**
		 * Set the light bar's led_brightness.
		 */
		void setBrightness(uint8_t brightness);

		/**
		 * Get the light bar's led_brightness.
		 */
		uint8_t getBrightness() const;

	private:
		void pollSerialMessages();

	private:
		bool alive     = false;
		bool listening = true;

		uint8_t led_brightness = 16;

		Adafruit_NeoPixel* pixels    = nullptr;
		LightBar*          light_bar = nullptr;
		Animator*          animator  = nullptr;
		StreamController   stream_controller;
	};

}

#endif //__CONTROLLER_LICHTLEINCONTROLLER_H__
