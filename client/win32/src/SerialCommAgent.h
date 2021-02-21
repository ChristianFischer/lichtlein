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


#ifndef __LICHTLEIN_SERIALCOMMAGENT_H__
#define __LICHTLEIN_SERIALCOMMAGENT_H__

#include <cstdint>
#include <functional>
#include <windows.h>


namespace lichtlein {

	/**
	 * Singleton class to handle the communication via serial port to the
	 * controller module.
	 * This class provides low level read and write functionality as well
	 * as high level commands like <c>setBrightness</c>.
	 */
	class SerialCommAgent
	{
	private:
		SerialCommAgent() = default;

	public:
		~SerialCommAgent();

		SerialCommAgent(const SerialCommAgent&) = delete;
		SerialCommAgent(SerialCommAgent&&) = delete;

		SerialCommAgent& operator=(const SerialCommAgent&) = delete;
		SerialCommAgent& operator=(SerialCommAgent&&) = delete;

		/**
		 * Get the singleton instance of this class.
		 */
		static SerialCommAgent& getInstance();

	public:
		/**
		 * Checks if the serial connection is established. If not
		 * it tries to open the connection.
		 * @return <c>true</c> if the connection with the controller is established
		 */
		bool ensureConnected();

		/**
		 * Connects to the controller module via serial port.
		 * @return <c>true</c> if the connection was successful,
		 *         <c>false</c> if an error occurred or a connection was already present
		 */
		bool connect();

		/**
		 * Close the current connection, if any.
		 */
		void disconnect();

		/**
		 * Checks if there's a valid connection to the controller module.
		 */
		[[nodiscard]]
		bool isConnected() const;

		/**
		 * Sends the content of a data buffer to the controller.
		 * @param data pointer to a buffer containing the data to be sent
		 * @param size the number of bytes from the given data to be sent
		 * @return <c>true</c> if the data was sent successfully
		 */
		bool send(const void* data, size_t size);

		/**
		 * Reads pending data from the serial port.
		 * @param data pointer to a data buffer to store the data received
		 * @param size size of the data buffer in bytes
		 * @return <c>true</c> if the data was successfully read
		 */
		bool read(void* data, size_t size);

		/**
		 * Sends data to the controller via serial port.
		 * @tparam T the type of data to be sent
		 * @param data the data to be sent
		 * @return <c>true</c> if the data was sent successfully
		 */
		template<class T>
		bool send(const T& data) {
			return send(reinterpret_cast<const void*>(&data), sizeof(T));
		}

		/**
		 * Reads pending data from the serial port.
		 * @tparam T the type of data to be read
		 * @param data pointer to the data object, where the data received should be stored
		 * @return <c>true</c> if the data was successfully read
		 */
		template<class T>
		bool read(T* data) {
			return read(reinterpret_cast<void*>(&data), sizeof(T));
		}

	public:
		/**
		 * Send the command to the controller to change the light's brightness.
		 * @param brightness the new brightness value to be set
		 */
		void setBrightness(uint8_t brightness);

	private:
		/**
		 * Executes the given procedure after establishing a connection to the
		 * controller module.
		 * If no connection could be established or an error occurred, the
		 * procedure won't be executed.
		 * @param proc the procedure to be executed with a valid connection
		 * @return <c>true</c> if the procedure was executed successfully
		 */
		bool runWithConnection(const std::function<void()>& proc);

		/**
		 * Checks for any pending error.
		 * If an error code was found, it will throw a Win32Error.
		 */
		void checkForError();

	private:
		static SerialCommAgent instance;

		HANDLE hCommPort = nullptr;
		DCB    commState = { };
	};

}

#endif //__LICHTLEIN_SERIALCOMMAGENT_H__
