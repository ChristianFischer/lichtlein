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

#ifndef __LICHTLEIN_WIN32_TRAYICON_H__
#define __LICHTLEIN_WIN32_TRAYICON_H__

#include "windows.h"


namespace lichtlein {

	/**
	 * Manages the icon in the system tray.
	 */
	class TrayIcon
	{
	public:
		TrayIcon() = default;
		~TrayIcon() = default;

		TrayIcon(const TrayIcon&) = delete;
		TrayIcon(TrayIcon&&) = delete;

		TrayIcon& operator=(const TrayIcon&) = delete;
		TrayIcon& operator=(TrayIcon&&) = delete;

	public:
		/// The icon's ID.
		static constexpr int TRAY_ICON_ID                 = 1000;

		/// The ID of the message received by WndProc
		static constexpr int TRAY_ICON_MESSAGE_ID         = WM_USER + 1000;

		/// The ID of the Brightness submenu
		static constexpr int MENU_ID_BRIGHTNESS           = WM_USER + 1010;

		/// The first ID to set the brightness value
		static constexpr int MENU_ID_BRIGHTNESS_SET_BEGIN = WM_USER + 1020;

		/// The ID of the exist button
		static constexpr int MENU_ID_EXIT                 = WM_USER + 1090;

	public:
		/**
		 * Initializes the tray icon and brings it into the system tray.
		 * @param hWnd The owner window HWND
		 * @return \c true on success
		 */
		bool init(HWND hWnd);

		/**
		 * Disposes the tray icon and removes it from the system tray.
		 */
		void dispose();

		/**
		 * Handles a message received in WndProc which was addressed to the system tray.
		 */
		bool handleMessage(UINT uMsg);

		/**
		 * Displays the tray icon's context menu.
		 */
		void displayMenu();

	private:
		/**
		 * Displays a HMENU on the cursor's current location.
		 * @param menu The HMENU to be displayed
		 * @return the ID of the menu item selected by the user
		 */
		UINT displayMenuAtCursor(HMENU menu);

	private:
		BOOL           tray_icon_open        = FALSE;
		HWND           parent_hwnd           = nullptr;
		HMENU          tray_popup_menu       = nullptr;
		HMENU          tray_popup_brightness = nullptr;
		NOTIFYICONDATA tray_icon             = { };
	};

}

#endif //__LICHTLEIN_WIN32_TRAYICON_H__
