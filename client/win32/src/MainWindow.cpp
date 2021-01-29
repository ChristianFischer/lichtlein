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

#include "MainWindow.h"

namespace lichtlein {

	LPCSTR MainWindow::WND_CLASS_NAME = "LichtleinClient";


	bool MainWindow::init(HINSTANCE hInstance) {
		this->hInstance = hInstance;

		// set up window class
		ZeroMemory(&wcls, sizeof(wcls));
		wcls.cbSize        = sizeof(wcls);
		wcls.style         = 0;
		wcls.lpfnWndProc   = MainWindow::WndProc;
		wcls.cbClsExtra    = 0;
		wcls.cbWndExtra    = 0;
		wcls.hInstance     = hInstance;
		wcls.hIcon         = LoadIcon(nullptr, IDI_APPLICATION);
		wcls.hCursor       = LoadCursor(nullptr, IDC_ARROW);
		wcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		wcls.lpszMenuName  = nullptr;
		wcls.lpszClassName = WND_CLASS_NAME;

		if (!RegisterClassEx(&wcls)) {
			FatalAppExit(0, TEXT("Failed to register window class"));
		}

		// create window
		hWnd = CreateWindow(
				WND_CLASS_NAME,
				TEXT("Lichtlein"),
				WS_OVERLAPPEDWINDOW, // invisible window
				CW_USEDEFAULT, CW_USEDEFAULT, 480, 320,
				nullptr,
				nullptr,
				hInstance,
				this
		);

		// check for success
		if (!hWnd) {
			MessageBox(
					nullptr,
					"Failed to create Window",
					TEXT("Error"),
					MB_ICONERROR | MB_OK | MB_TOPMOST
			);

			return false;
		}

		// store the pointer to 'this' for the window in order to
		// gain access to the window object during message handling
		SetWindowLongPtr(this->hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

		// initialize tray icon, after the window was created successfully
		tray_icon.init(this->hWnd);

		return true;
	}


	void MainWindow::dispose() {
		tray_icon.dispose();

		UnregisterClass(WND_CLASS_NAME, hInstance);
	}


	bool MainWindow::isOpen() const {
		return hWnd != nullptr;
	}


	LRESULT MainWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		MainWindow* window = nullptr;
		LRESULT     result = 0;

		// on create take the window pointer from lParam
		if (uMsg == WM_NCCREATE) {
			// get the create struct
			auto* lpCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);

			// the CreateParams contains the user object submitted to CreateWindow
			window = reinterpret_cast<MainWindow*>(lpCreateStruct->lpCreateParams);

			// store the window pointer as the user object of WIN32 window
			SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		}
		else {
			// ... otherwise try to get the window pointer from GWLP_USERDATA
			LONG_PTR user_data = GetWindowLongPtr(hWnd, GWLP_USERDATA);
			window = reinterpret_cast<MainWindow*>(user_data);
		}

		if (!window || !window->handleMessage(uMsg, wParam, lParam)) {
			result = DefWindowProc(hWnd, uMsg, wParam, lParam);
		}

		return result;
	}


	bool MainWindow::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
		switch(uMsg) {
			case WM_CLOSE: {
				PostQuitMessage(0);

				// need to invoke DefWindowProc to destroy the window
				return false;
			}

			case TrayIcon::TRAY_ICON_MESSAGE_ID: {
				if (wParam == TrayIcon::TRAY_ICON_ID) {
					tray_icon.handleMessage(lParam);

					return true;
				}

				return false;
			}

			default: {
				return false;
			}
		}
	}
}

