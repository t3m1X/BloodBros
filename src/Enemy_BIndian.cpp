#include "Application.h"
#include "Enemy_BIndian.h"
#include "Path.h"
#include "ModuleCollision.h"
#include "p2Point.h"
#include "ModuleParticles.h"

BIndian::BIndian(int x, int y) : Enemy(x, y)
{

	/*FIRST INDIAN : 48 X 90 1147 X 1328
	SECOND : 66 X 93 1147 X 1328
		 THIRD : 48 X 96  1147 X 1328
			 FOURTH : 48 X 93 1147 X 1328
				  FIFTH : 84 X 96 1147 X 1328
					  SIXTH : 48 X 75  1147 X 1328
						  SEVENTH : 75 X 57 1147 X 1328
								EIGHTH : 75 X 15  1147 X 1328
										 */

	walk.speed = 0.1f;

	i_pos.x = x;
	i_pos.y = y;

}