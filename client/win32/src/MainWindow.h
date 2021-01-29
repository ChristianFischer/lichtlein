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

#ifndef __LICHTLEIN_WIN32_MAINWINDOW_H__
#define __LICHTLEIN_WIN32_MAINWINDOW_H__

#include "TrayIcon.h"

#include "windows.h"


namespace lichtlein {

	/**
	 * The main window, which purpose is basically just to hold the tray icon
	 * and receive window messages for the whole application.
	 */
	class MainWindow
	{
	public:
		MainWindow() = default;
		~MainWindow() = default;

		MainWindow(const MainWindow&) = delete;
		MainWindow(MainWindow&&) = delete;

		MainWindow& operator=(const MainWindow&) = delete;
		MainWindow& operator=(MainWindow&&) = delete;

	public:
		/**
		 * Initialize the window. This makes the window available and active,
		 * but stays invisible.
		 * @param hInstance The applications HINSTANCE
		 * @return \c true on success
		 */
		bool init(HINSTANCE hInstance);

		/**
		 * Closes and dispose the window.
		 */
		void dispose();

		/**
		 * Checks if the window is still open and active.
		 */
		[[nodiscard]]
		bool isOpen() const;

	private:
		/**
		 * Callback function to receive window messages.
		 * This will be bound to the window class and
		 * forwards it to handleMessage().
		 */
		static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

		/**
		 * Handles window messages received by WndProc.
		 */
		bool handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	private:
		/// The window's class name, used to identify the window class
		static LPCSTR WND_CLASS_NAME;

		TrayIcon tray_icon;

		HINSTANCE  hInstance = nullptr;
		WNDCLASSEX wcls      = { };
		HWND       hWnd      = nullptr;
	};

}

#endif //__LICHTLEIN_WIN32_MAINWINDOW_H__
