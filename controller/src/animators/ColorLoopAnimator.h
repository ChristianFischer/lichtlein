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

#ifndef __CONTROLLER_COLORLOOPANIMATOR_H__
#define __CONTROLLER_COLORLOOPANIMATOR_H__

#include "Animator.h"
#include "Color.h"

#include <vector>


namespace lichtlein {

	/**
	 * An animation wich displays a color gradient cycling through the light bar.
	 */
	class ColorLoopAnimator : public Animator
	{
	public:
		static ColorLoopAnimator* makeRainbowLoopAnimator();

		/**
		 * Set the color sequence to be displayed.
		 */
		void setColors(const std::vector<Color>& colors);

		/**
		 * Set the time in milliseconds for a full loop.
		 */
		void setFullLoopTime(uint32_t time);

	protected:
		void onUpdate(Layer* layer, uint32_t ms) override;

	private:
		uint32_t offset;
		uint32_t full_loop_time = 5000;

		std::vector<Color> color_table;
	};

}

#endif //__CONTROLLER_COLORLOOPANIMATOR_H__
