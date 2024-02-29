#pragma once

#include <Engine.h>
#include <2D/Sprite.h>
#include <2D/SpriteAnimated.h>
#include <2D/Rectangle.h>
#include <UI/Label.h>
#include <UI/Test.h>

#include "FlappyBirdPlayer.h"
#include "FlappyBirdObstacles.h"

enum class FlappyBirdState {
	MENU,
	GAME,
	PAUSE,
	RESULT
};

void flappyBird();