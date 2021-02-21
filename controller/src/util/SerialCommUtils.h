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


#ifndef __CONTROLLER_SERIALCOMMUTILS_H__
#define __CONTROLLER_SERIALCOMMUTILS_H__

#include <HardwareSerial.h>


namespace lichtlein {

	/**
	 * Reads data from the serial port.
	 * @tparam T the type of data to be read
	 * @param data pointer to the target object where to store the data read
	 * @return <c>true</c> if the data was read successfully
	 */
	template<class T>
	bool readSerial(T* data) {
		size_t bytes_expected = sizeof(*data);
		size_t bytes_read     = Serial.readBytes(reinterpret_cast<uint8_t*>(data), bytes_expected);

		return bytes_read == bytes_expected;
	}

}

#endif //__CONTROLLER_SERIALCOMMUTILS_H__
