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

#include "TrayIcon.h"

#include <string>


namespace lichtlein {

	bool TrayIcon::init(HWND hWnd) {
		this->parent_hwnd = hWnd;
		std::string tooltip_text = "Lichtlein";

		// create tray icon menu
		tray_popup_menu = CreatePopupMenu();
		AppendMenu(tray_popup_menu, MF_STRING, MENU_ID_SET_BRIGHTNESS, "Brightness");
		AppendMenu(tray_popup_menu, MF_STRING, MENU_ID_EXIT,           "Exit");

		// set up tray icon
		ZeroMemory(&tray_icon, sizeof(tray_icon));
		tray_icon.cbSize           = sizeof(tray_icon);
		tray_icon.hWnd             = hWnd;
		tray_icon.uID              = TRAY_ICON_ID;
		tray_icon.hIcon            = LoadIcon(nullptr, IDI_APPLICATION);
		tray_icon.uFlags           = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		tray_icon.uVersion         = NOTIFYICON_VERSION;
		tray_icon.uCallbackMessage = TRAY_ICON_MESSAGE_ID;
		strncpy_s(tray_icon.szTip, tooltip_text.data(), tooltip_text.size());

		// add tray icon
		BOOL result = Shell_NotifyIcon(NIM_ADD, &tray_icon);

		return !!result;
	}


	void TrayIcon::dispose() {
		Shell_NotifyIcon(NIM_DELETE, &tray_icon);
	}


	bool TrayIcon::handleMessage(UINT uMsg) {
		switch(uMsg) {
			case WM_RBUTTONUP: {
				displayMenu();

				return true;
			}

			default: {
				return false;
			}
		}
	}


	void TrayIcon::displayMenu() {
		UINT selected = displayMenuAtCursor(tray_popup_menu);

		switch(selected) {
			case MENU_ID_SET_BRIGHTNESS: {
				break;
			}

			case MENU_ID_EXIT: {
				PostQuitMessage(0);
				break;
			}

			default: {
				break;
			}
		}
	}


	UINT TrayIcon::displayMenuAtCursor(HMENU menu) {
		POINT cursor_pos;
		GetCursorPos(&cursor_pos);

		UINT selected = TrackPopupMenu(
				menu,
				TPM_RETURNCMD | TPM_NONOTIFY,
				cursor_pos.x, cursor_pos.y,
				0,
				this->parent_hwnd,
				nullptr
		);

		return selected;
	}

}
