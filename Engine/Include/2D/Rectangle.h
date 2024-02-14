#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Object.h"

namespace E2D {
	class Rectangle : public Object {
	public:
		Rectangle(float width, float height);

		void draw() override;
	};
}