#pragma once

#include <string>
#include <vector>
#include <map>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Object.h"
#include "../Engine.h"
#include "../Texture.h"

namespace E2D {
	class SpriteAnimated : public Object {
	private:
		std::map<std::string, std::vector<Texture>> animations;
		float currentTime;

	public:
		std::string currentAnimation;
		int indexTexture;
		float timeChangeTexture;
		bool pauseAnimation;

		SpriteAnimated(std::string name, std::vector<Texture> textures);

		void load(std::string name, std::vector<Texture> textures);
		void play(std::string name);
		void draw() override;
	};
}