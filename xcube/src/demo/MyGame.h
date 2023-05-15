#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__

#include "../engine/AbstractGame.h"

struct GameKey {
	Point2 pos;
	bool isAlive;
};

class MyGame : public AbstractGame {
	private:
		Rect box;
		Rect ball;
		Rect box2;
		Rot rot;

		Vector2i velocity;
		Vector2i velocity2;

		std::vector<std::shared_ptr<GameKey>> gameKeys;

		/* GAMEPLAY */
		int points1, points2;
		int previousX;
		int previousY;
		bool gameWon;

		void handleKeyEvents();
		void update();
		void render();
		void renderUI();
	public:
        MyGame();
		~MyGame();
		float ballSpeedX = -4;
		float ballSpeedY = -1;

};

#endif