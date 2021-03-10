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

#include "SerialCommAgent.h"
#include "Win32Error.h"

#include "SerialPortCommands.h"

#include <iostream>


namespace lichtlein {


	SerialCommAgent SerialCommAgent::instance;


	SerialCommAgent& SerialCommAgent::getInstance() {
		return instance;
	}


	SerialCommAgent::~SerialCommAgent() {
		if (isConnected()) {
			disconnect();
		}
	}


	bool SerialCommAgent::ensureConnected() {
		if (!isConnected()) {
			connect();
		}

		return isConnected();
	}


	bool SerialCommAgent::connect() {
		if (isConnected()) {
			return false;
		}

		hCommPort = CreateFile(
				"COM3", // todo: currently hardcoded port
				GENERIC_READ | GENERIC_WRITE,
				0,
				nullptr,
				OPEN_EXISTING,
				0,
				nullptr
		);

		if (hCommPort == INVALID_HANDLE_VALUE) {
			Win32Error::checkLastError();

			return false;
		}

		BOOL ret;
		ret = GetCommState(hCommPort, &commState);
		if (ret == FALSE) {
			return false;
		}

		commState.BaudRate = 9600;
		commState.ByteSize = 8;

		ret = SetCommState(hCommPort, &commState);
		if (ret == FALSE) {
			return false;
		}

		COMMTIMEOUTS commTimeOut;
		commTimeOut.ReadIntervalTimeout         = 3;
		commTimeOut.ReadTotalTimeoutMultiplier  = 3;
		commTimeOut.ReadTotalTimeoutConstant    = 2;
		commTimeOut.WriteTotalTimeoutMultiplier = 3;
		commTimeOut.WriteTotalTimeoutConstant   = 2;
		ret = SetCommTimeouts(hCommPort, &commTimeOut);

		if (ret == FALSE) {
			return false;
		}

		return true;
	}


	void SerialCommAgent::disconnect() {
		if (hCommPort != nullptr) {
			CloseHandle(hCommPort);
			hCommPort = nullptr;
		}
	}


	bool SerialCommAgent::isConnected() const {
		return hCommPort != nullptr;
	}


	bool SerialCommAgent::send(const void* data, size_t size) {
		if (isConnected()) {
			DWORD written = 0;
			BOOL ret = WriteFile(hCommPort, data, size, &written, nullptr);

			if (ret != FALSE) {
				return true;
			}

			checkForError();
		}

		return false;
	}


	bool SerialCommAgent::read(void* data, size_t size) {
		if (isConnected()) {
			DWORD read = 0;
			BOOL ret = ReadFile(hCommPort, data, size, &read, nullptr);

			if (ret != FALSE) {
				return true;
			}

			checkForError();
		}

		return false;
	}


	void SerialCommAgent::setBrightness(uint8_t brightness) {
		runWithConnection(
				[this, brightness] {
					send(SerialPortCommands::SetBrightness);
					send(brightness);
				}
		);
	}


	void SerialCommAgent::sendColorSequence(const std::vector<uint32_t>& colors) {
		runWithConnection(
				[this, &colors] {
					auto count = uint16_t(colors.size());

					send(SerialPortCommands::ColorSequence);
					send(count);

					for(auto& color : colors) {
						uint8_t r = (color >> 16) & 0xff;
						uint8_t g = (color >>  8) & 0xff;
						uint8_t b = (color >>  0) & 0xff;

						send(r);
						send(g);
						send(b);
					}
				}
		);
	}


	void SerialCommAgent::sendColorSequence(uint16_t count, uint32_t color) {
		runWithConnection(
				[this, count, color] {
					uint8_t r = (color >> 16) & 0xff;
					uint8_t g = (color >>  8) & 0xff;
					uint8_t b = (color >>  0) & 0xff;

					send(SerialPortCommands::ColorSequence);
					send(count);

					for(uint16_t i=0; i<count; i++) {
						send(r);
						send(g);
						send(b);
					}
				}
		);
	}


	bool SerialCommAgent::runWithConnection(const std::function<void()>& proc) {
		try {
			// check for any pending error
			checkForError();

			// ensure a connection is established before executing the procedure
			if (ensureConnected()) {
				proc();
			}

			return true;
		}
		catch(std::exception& e) {
			std::cerr << "Serial Communication failed with error: " << e.what();
		}

		return false;
	}


	void SerialCommAgent::checkForError() {
		DWORD err = GetLastError();

		if (err != NO_ERROR) {
			disconnect();

			Win32Error::throwWithErrorCode(err);
		}
	}
}