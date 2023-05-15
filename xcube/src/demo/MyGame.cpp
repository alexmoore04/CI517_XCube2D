#include "MyGame.h"

MyGame::MyGame() : AbstractGame(), points1(0), points2(0), gameWon(false), box(5, 250, 20, 100), ball(395, 295, 10, 10), box2(775, 250, 20, 100), rot(Point2{300,300}, Point2{ 350,350 }, Point2{300, 400}, Point2{ 250, 350 }, 5) {
	TTF_Font * font = ResourceManager::loadFont("res/fonts/arial.ttf", 72);
	gfx->useFont(font);
	gfx->setVerticalSync(true);

}

MyGame::~MyGame() {

}

void MyGame::handleKeyEvents() {
	int speed = 6;

	if (eventSystem->isPressed(Key::W)) {
		velocity.y = -speed;
	}

	if (eventSystem->isPressed(Key::S)) {
		velocity.y = speed;
	}
	if (eventSystem->isPressed(Key::UP)) {
		velocity2.y = -speed;
	}
	if (eventSystem->isPressed(Key::DOWN)) {
		velocity2.y = speed;
	}

}

void MyGame::update() {

	previousX = ball.x - ballSpeedX;
	previousY = ball.y - ballSpeedY;
	bool collision = false;
	mySystem->checkAABBOverlap(MyEngineSystem::AABB{ MyEngineSystem::vector2D{ box.x, box.y }, MyEngineSystem::vector2D{box.x + box.w, box.y + box.h} }, MyEngineSystem::AABB{ MyEngineSystem::vector2D{ ball.x, ball.y }, MyEngineSystem::vector2D{ball.x + ball.w, ball.y + ball.h} }, collision);
	if (collision == true) {
		ballSpeedX = -1 * (ballSpeedX * 1.1);
		if (velocity.y > 0) {
			ballSpeedY = ballSpeedY * velocity.y / 2;
		}
		ball.x = 26;
		collision = false;
	}
	mySystem->checkAABBOverlap(MyEngineSystem::AABB{ MyEngineSystem::vector2D{ box2.x, box2.y }, MyEngineSystem::vector2D{box2.x + box2.w, box2.y + box2.h} }, MyEngineSystem::AABB{ MyEngineSystem::vector2D{ ball.x, ball.y }, MyEngineSystem::vector2D{ball.x + ball.w, ball.y + ball.h} }, collision);
	if (collision == true) {
		ballSpeedX = -1 * (ballSpeedX * 1.1);
		if (velocity.y > 0) {
			ballSpeedY = ballSpeedY * velocity.y / 2;
		}
		ball.x = 764;
		collision = false;
	}
	int ballCenterX = ball.x + ball.w/2;
	int ballCenterY = ball.y + ball.h/2;
	int rotCenterX = 300;
	int rotCenterY = 350;
	int midPointX = 0;
	int midPointY = 0;
	int holder = 0;
	mySystem->getCenter(MyEngineSystem::AABB{ MyEngineSystem::vector2D{ ballCenterX, ballCenterY } , MyEngineSystem::vector2D{rotCenterX, rotCenterY } },  midPointX,  midPointY );
	mySystem->checkSATOverlap(MyEngineSystem::SAT{ MyEngineSystem::vector2D{ ballCenterX, ballCenterY },MyEngineSystem::vector2D{ ball.x, ball.y },MyEngineSystem::vector2D{ ball.x + ball.w, ball.y },MyEngineSystem::vector2D{ ball.x, ball.y + ball.h},MyEngineSystem::vector2D{ ball.x + ball.w, ball.y + ball.h} }, MyEngineSystem::SAT{ MyEngineSystem::vector2D{ rotCenterX, rotCenterY },MyEngineSystem::vector2D{ rot.TL.x, rot.TL.y },MyEngineSystem::vector2D{ rot.TR.x, rot.TR.y },MyEngineSystem::vector2D{ rot.BL.x , rot.BL.y},MyEngineSystem::vector2D{ rot.BR.x, rot.BR.y} }, MyEngineSystem::vector2D{ midPointX, midPointY }, collision);
	if (collision == true) {
		ball.x = previousX;
		ball.y = previousY;
		if (ballSpeedX > 0 && ballSpeedY > 0) {
			holder = ballSpeedX * -1;
			ballSpeedX = ballSpeedY * -1;
			ballSpeedY = holder;
		}
		else if (ballSpeedX < 0 && ballSpeedY > 0) {
			holder = ballSpeedX * -1;
			ballSpeedX = ballSpeedY ;
			ballSpeedY = holder;
		}
		else
		{
			holder = ballSpeedX;
			ballSpeedX = ballSpeedY;
			ballSpeedY = holder;
		}
		std::cout << "ALEX_MOORE-CI517-2022";
	}

	if (box.y + box.h + velocity.y <= 600 && box.y + velocity.y >= 0) {
		box.y += velocity.y;
	}

	if (box2.y + box2.h + velocity2.y <= 600 && box2.y + velocity2.y >= 0) {
		box2.y += velocity2.y;
	}

	if (ball.y + ballSpeedY < 0 || ball.y + ball.h + ballSpeedY > 600) {
		ballSpeedY = ballSpeedY * -1;
	}
	if (ball.x < 0) {
		ball.x = 395;
		ball.y = 295;
		ballSpeedX = -4;
		ballSpeedY = -1;
		points2 += 1;
	}
	if (ball.x > 800) {
		ball.x = 395;
		ball.y = 295;
		ballSpeedX = 4;
		ballSpeedY = 1;
		points1 += 1;
	}

	

	ball.x += ballSpeedX;
	ball.y += ballSpeedY;


    velocity.y = 0;
	velocity2.y = 0;
}

void MyGame::render() {
	gfx->setDrawColor(SDL_COLOR_GREEN);
	gfx->drawRect(box);

	gfx->setDrawColor(SDL_COLOR_YELLOW);
	gfx->drawRect(ball);

	gfx->setDrawColor(SDL_COLOR_RED);
	gfx->drawRect(box2);

	gfx->setDrawColor(SDL_COLOR_WHITE);
	gfx->drawLines(rot, rot.count);
}

void MyGame::renderUI() {
	gfx->setDrawColor(SDL_COLOR_AQUA);
	std::string points1Str = std::to_string(points1);
	std::string points2Str = std::to_string(points2);
	std::string colon = ":";
	gfx->drawText(points1Str, 390 - points1Str.length() * 50, 25);
	gfx->drawText(points2Str, 440, 25);
	gfx->drawText(colon, 400, 25);

	if (gameWon)
		gfx->drawText("YOU WON", 250, 500);
} 