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

#ifndef __CONTROLLER_LIGHTBARBUILDER_H__
#define __CONTROLLER_LIGHTBARBUILDER_H__

#include "LightBar.h"

#include <memory>


namespace lichtlein {

	/**
	 * A factory class to construct a LightBar object.
	 */
	class LightBarBuilder
	{
	public:
		LightBarBuilder();

		// no copying allowed
		LightBarBuilder(const LightBarBuilder&) = delete;
		LightBarBuilder& operator=(const LightBarBuilder&) = delete;

		// default moving
		LightBarBuilder(LightBarBuilder&&) = default;
		LightBarBuilder& operator=(LightBarBuilder&&) = default;

	public:
		/**
		 * Defines how much lights the LightBar being construction shall handle.
		 * @param light_count The number of lights to be handled by the constructed LightBar
		 * @return
		 */
		LightBarBuilder& setLightCount(unsigned int light_count);

		/**
		 * Finishes creation of the light bar.
		 * @return A fully initialized LightBar object
		 */
		lichtlein::LightBar* finish();

	private:
		unsigned int light_count = 1;

		lichtlein::LightBar* light_bar = nullptr;
	};

}

#endif //__CONTROLLER_LIGHTBARBUILDER_H__
