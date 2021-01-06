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

#include "Color.h"


namespace lichtlein {

	Color::Color()
		: Color(0x000000)
	{
	}


	Color::Color(uint32_t wrgb) // NOLINT(cppcoreguidelines-pro-type-member-init)
		: wrgb(wrgb)
	{
	}


	Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w) // NOLINT(cppcoreguidelines-pro-type-member-init)
		: b(b), g(g), r(r), w(w)
	{
	}


	Color::operator uint32_t() const {
		return wrgb;
	}

}
