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

#include <Arduino.h>
#include <unity.h>

#include "../../lib/light/src/Color.h"


using namespace lichtlein;


void test_init_default() {
	Color color;

	TEST_ASSERT_EQUAL_UINT32(0x00000000, color);
	TEST_ASSERT_EQUAL_UINT(0x00, color.w);
	TEST_ASSERT_EQUAL_UINT(0x00, color.r);
	TEST_ASSERT_EQUAL_UINT(0x00, color.g);
	TEST_ASSERT_EQUAL_UINT(0x00, color.b);
}


void test_init_4uint8() {
	Color color(0x11223344);

	TEST_ASSERT_EQUAL_UINT32(0x11223344, color);
	TEST_ASSERT_EQUAL_UINT(0x11, color.w);
	TEST_ASSERT_EQUAL_UINT(0x22, color.r);
	TEST_ASSERT_EQUAL_UINT(0x33, color.g);
	TEST_ASSERT_EQUAL_UINT(0x44, color.b);
}


void test_init_uint32() {
	Color color(0x22, 0x33, 0x44, 0x11);

	TEST_ASSERT_EQUAL_UINT32(0x11223344, color);
	TEST_ASSERT_EQUAL_UINT(0x11, color.w);
	TEST_ASSERT_EQUAL_UINT(0x22, color.r);
	TEST_ASSERT_EQUAL_UINT(0x33, color.g);
	TEST_ASSERT_EQUAL_UINT(0x44, color.b);
}


void test_iterator() {
	Color color(0x22, 0x33, 0x44, 0x11);

	TEST_ASSERT_EQUAL_UINT32(0x11223344, color);
	TEST_ASSERT_EQUAL_UINT(0x11, color.w);
	TEST_ASSERT_EQUAL_UINT(0x22, color.r);
	TEST_ASSERT_EQUAL_UINT(0x33, color.g);
	TEST_ASSERT_EQUAL_UINT(0x44, color.b);

	// iterate over each component and multiply by 2
	for(auto& c : color) {
		c *= 2;
	}

	TEST_ASSERT_EQUAL_UINT32(0x22446688, color);
	TEST_ASSERT_EQUAL_UINT(0x22, color.w);
	TEST_ASSERT_EQUAL_UINT(0x44, color.r);
	TEST_ASSERT_EQUAL_UINT(0x66, color.g);
	TEST_ASSERT_EQUAL_UINT(0x88, color.b);
}



void setup() {
}



void loop() {
	// wait for 2 seconds if the board doesn't support software reset via Serial.DTR/RTS
	delay(2000);

	UNITY_BEGIN();

	RUN_TEST(test_init_default);
	RUN_TEST(test_init_4uint8);
	RUN_TEST(test_init_uint32);
	RUN_TEST(test_iterator);

	UNITY_END();
}