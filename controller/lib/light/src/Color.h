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

#ifndef __LICHTLEIN_CONTROLLER_COLOR_H__
#define __LICHTLEIN_CONTROLLER_COLOR_H__

#include <stdint.h>


namespace lichtlein {

	/**
	 * The Color class stores the information of a displayable color value.
	 * Each color contains a 8 bit value for the red, green and blue light
	 * with an additional white-value, which can be used for LED stripes
	 * containing an additional white light.
	 */
	class Color
	{
	public:
		/**
		 * Creates a Color object with all values on zero, which represents a black color.
		 */
		explicit Color();

		/**
		 * Creates a color object with a 32 bit WRGB value, where each byte
		 * stores the information of a single color channel in the format
		 * <c>0xWWRRGGBB</c>.
		 */
		explicit Color(uint32_t wrgb);

		/**
		 * Creates a Color object with a single value for each color channel.
		 * @param r the red color value
		 * @param g the green color value
		 * @param b the blue color value
		 * @param w the white value
		 */
		Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w = 0x00);

		~Color() = default;

		Color(const Color&) = default;
		Color(Color&&) = default;

		Color& operator=(const Color&) = default;
		Color& operator=(Color&&) = default;

		explicit operator uint32_t() const;

	public:
		using iterator = uint8_t*;
		using const_iterator = const uint8_t*;

		iterator begin() { return components + 0; }
		iterator end()   { return components + 4; }
		const_iterator begin() const { return components + 0; }
		const_iterator end() const   { return components + 4; }

	public:
		union {
			struct {
				/**
				 * The blue color value.
				 */
				uint8_t b;

				/**
				 * The green color value.
				 */
				uint8_t g;

				/**
				 * The red color value.
				 */
				uint8_t r;

				/**
				 * The additional white value of the color.
				 */
				uint8_t w;
			};

			/**
			 * A vector containing all single color channels.
			 */
			uint8_t components[4];

			/**
			 * A combined 32bit value containing all four color channels.
			 */
			uint32_t wrgb;
		};
	};



	/**
	 * Blend between two different colors creating a mixture between them.
	 * @param a The first color to blend from
	 * @param b The second color to blend to
	 * @param p The progress value which represents the progress to blend between a and b
	 * @param t The maximum progress which means the blending will result in 100% of color b
	 * @return The blending result color between a and b
	 */
	Color blend(const Color& a, const Color& b, uint32_t p, uint32_t t);


	/**
	 * Blend between two different colors creating a mixture between them.
	 * @param a The first color to blend from
	 * @param b The second color to blend to
	 * @param f The progress of blending between a and b where 0 means 100% of color a and 1 means 100% of color b
	 * @return The blending result color between a and b
	 */
	Color blend(const Color& a, const Color& b, float f);

}


#endif //__LICHTLEIN_CONTROLLER_COLOR_H__
