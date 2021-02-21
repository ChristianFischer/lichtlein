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


#include "Win32Error.h"

#include <sstream>


namespace lichtlein {

	Win32Error::Win32Error(DWORD error_code) : error_code(error_code) {
	}


	void Win32Error::checkLastError() {
		DWORD err = GetLastError();

		if (err != ERROR_SUCCESS) {
			throwWithErrorCode(0);
		}
	}


	void Win32Error::throwWithErrorCode(DWORD error_code) {
		throw Win32Error(error_code);
	}


	const char* lichtlein::Win32Error::what() const {
		if (msg.empty()) {
			std::stringstream ss;
			ss << "Windows Error code #";
			ss << error_code;

			msg = ss.str();
		}

		return msg.c_str();
	}

}