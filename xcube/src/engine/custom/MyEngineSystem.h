#ifndef __MY_ENGINE_H__
#define __MY_ENGINE_H__

#include <vector>

#include "../EngineCommon.h"


class MyEngineSystem {
	friend class XCube2Engine;
	private:

	public:
		bool collision;
		struct vector2D {
			int x;
			int y;
		};
		struct AABB {
			vector2D min;
			vector2D max;
		};
		void checkAABBOverlap( AABB& a,  AABB& b, bool & AABBcol);

		struct SAT
		{
			vector2D center;
			vector2D C1;
			vector2D C2;
			vector2D C3;
			vector2D C4;
		};
		void checkSATOverlap( SAT& a, SAT& b, vector2D& c, bool & SATcol);
		void getCenter(AABB& a, int& centerX, int& centerY);
		void closest(AABB& a, vector2D& b, int& closeX, int& closeY);
		void check(AABB& a, int& out);
};



#endif