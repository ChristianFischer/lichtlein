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


#ifndef __LICHTLEIN_WIN32ERROR_H__
#define __LICHTLEIN_WIN32ERROR_H__

#include <exception>
#include <string>
#include <windows.h>


namespace lichtlein {

	/**
	 * Exception class for any Win32 Error received by GetLastError().
	 */
	class Win32Error : public std::exception
	{
	public:
		explicit Win32Error(DWORD error_code);

		Win32Error() = delete;

		Win32Error(const Win32Error&) = delete;
		Win32Error(Win32Error&&) = delete;

		Win32Error& operator=(const Win32Error&) = delete;
		Win32Error& operator=(Win32Error&&) = delete;

	public:
		/**
		 * Checks GetLastError() and throws an exception, if an error code was found.
		 */
		static void checkLastError();

		/**
		 * Throws a Win32Error with the given error code.
		 * @param error_code a Win32 error code
		 */
		static void throwWithErrorCode(DWORD error_code);

		[[nodiscard]]
		const char* what() const override;

	private:
		DWORD error_code = 0;

		mutable std::string msg;
	};

}

#endif //__LICHTLEIN_WIN32ERROR_H__
