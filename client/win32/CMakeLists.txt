cmake_minimum_required(VERSION 3.0)
project(lichtlein)

set(CMAKE_CXX_STANDARD 17)

add_executable(
		lichtlein
		WIN32
		src/main.cpp
		src/MainWindow.h
		src/MainWindow.cpp
		src/SerialCommAgent.h
		src/SerialCommAgent.cpp
		src/TrayIcon.h
		src/TrayIcon.cpp
		src/Win32Error.h
		src/Win32Error.cpp
)

target_include_directories(
		lichtlein
		PRIVATE ../../controller/include
)
