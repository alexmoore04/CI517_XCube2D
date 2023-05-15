#include "MyEngineSystem.h"


void MyEngineSystem::checkAABBOverlap( AABB& a, AABB& b, bool & AABBcol) {
	if (a.max.x < b.min.x || a.min.x > b.max.x) {
		AABBcol = false;
	}
	else {
		if (a.max.y < b.min.y || a.min.y > b.max.y) {
			AABBcol = false;
		}
		else
		{
			AABBcol = true;
		}
	};
}

void MyEngineSystem::closest(AABB& a,vector2D& b, int& closeX, int& closeY) {
	int x = a.max.x - b.x;
	int y = a.max.y - b.y;
	if (x < 0) {
		x = x * -1;
	}
	if (y < 0) {
		y = y * -1;
	}
	int close1 = x + y;
	x = a.min.x - b.x;
	y = a.min.y - b.y;
	if (x < 0) {
		x = x * -1;
	}
	if (y < 0) {
		y = y * -1;
	}
	int close2 = x + y;
	if (close1 > close2) {
		closeX = a.max.x;
		closeY = a.max.y;
	}
	else {
		closeX = a.min.x;
		closeY = a.min.y;
	}
}

void MyEngineSystem::check(AABB& a, int& out) {
	int x = 0;
	int y = 0;
	if (a.max.x > a.min.x) {
		x = a.max.x - a.min.x;
		if (a.max.y > a.min.y) {
			y = a.max.y - a.min.y;
		}
		else
		{
			y = a.min.y - a.max.y;
		}
	}
	else {
		x = a.min.x - a.max.x;
		if (a.max.y > a.min.y) {
			y = a.max.y - a.min.y;
		}
		else
		{
			y = a.min.y - a.max.y;
		}
	}
	out = x + y ;
}

void MyEngineSystem::checkSATOverlap(SAT& a, SAT& b, vector2D& c, bool& SATcol) {
	int closeXa = 0;
	int closeYa = 0;
	int closeXb = 0;
	int closeYb = 0;
	int dist = 0;
	int distA = 0;
	int distB = 0;
	MyEngineSystem::closest(MyEngineSystem::AABB{ MyEngineSystem::vector2D{a.C1.x,a.C1.y},MyEngineSystem::vector2D{a.C2.x,a.C2.y} }, MyEngineSystem::vector2D{ c.x, c.y }, closeXa, closeYa );
	MyEngineSystem::closest(MyEngineSystem::AABB{ MyEngineSystem::vector2D{closeXa,closeYa},MyEngineSystem::vector2D{a.C3.x,a.C3.y} }, MyEngineSystem::vector2D{ c.x, c.y },  closeXa, closeYa );
	MyEngineSystem::closest(MyEngineSystem::AABB{ MyEngineSystem::vector2D{closeXa,closeYa},MyEngineSystem::vector2D{a.C4.x,a.C4.y} }, MyEngineSystem::vector2D{ c.x, c.y },  closeXa, closeYa );
	MyEngineSystem::closest(MyEngineSystem::AABB{ MyEngineSystem::vector2D{b.C1.x,b.C1.y},MyEngineSystem::vector2D{b.C2.x,b.C2.y} }, MyEngineSystem::vector2D{ c.x, c.y },  closeXb, closeYb );
	MyEngineSystem::closest(MyEngineSystem::AABB{ MyEngineSystem::vector2D{closeXb,closeYb},MyEngineSystem::vector2D{b.C3.x,b.C3.y} }, MyEngineSystem::vector2D{ c.x, c.y },  closeXb, closeYb );
	MyEngineSystem::closest(MyEngineSystem::AABB{ MyEngineSystem::vector2D{closeXb,closeYb},MyEngineSystem::vector2D{b.C4.x,b.C4.y} }, MyEngineSystem::vector2D{ c.x, c.y },  closeXb, closeYb );
	MyEngineSystem::check(MyEngineSystem::AABB{ MyEngineSystem::vector2D{closeXa ,closeYa},MyEngineSystem::vector2D{closeXb,closeYb} }, dist);
	MyEngineSystem::check(MyEngineSystem::AABB{ MyEngineSystem::vector2D{a.center.x,a.center.y},MyEngineSystem::vector2D{closeXa,closeYa} }, distA);
	MyEngineSystem::check(MyEngineSystem::AABB{ MyEngineSystem::vector2D{b.center.x,b.center.y},MyEngineSystem::vector2D{closeXb,closeYb} }, distB);
	
	if (dist - (distA + distB)*2 > 0) {
		SATcol = false;
	}
	else
	{
		SATcol = true;
	}
}

void MyEngineSystem::getCenter(AABB& a, int& centerX, int& centerY) {
	bool flipx = false;
	bool flipy = false;
	int x = a.max.x - a.min.x;
	int y = a.max.y - a.min.y;
	if (x < 0) {
		x = x * -1;
		flipx = true;
	};
	if (y < 0) {
		y = y * -1;
		flipy = true;
	}
	if (flipx == true) {
		centerX = a.min.x - x/2;
		if (flipy == true) {
			centerY = a.min.y - y/2;
		}
		else
		{
			centerY = a.min.y + y/2;
		}
	}
	else
	{
		centerX = a.min.x + x/2;
		if (flipy == true) {
			centerY = a.min.y - y/2;
		}
		else
		{
			centerY = a.min.y + y/2;
		}
	}
}