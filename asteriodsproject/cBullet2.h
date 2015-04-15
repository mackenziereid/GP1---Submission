
#ifndef _CBULLET2_H
#define _CBULLET2_H
#include "cSprite.h"


class cBullet2 : public cSprite
{
private:
	glm::vec2 bulletVelocity = glm::vec2(0.0f, 0.0f);

public:
	//cBullet(vector<cTexture*> tileTextList)

	void render();		// Default render function
	void update(float deltaTime);		// Bullet update method
	void setBulletVelocity(glm::vec2 bulletVel);   // Sets the velocity for the Bullet
	glm::vec2 getBulletVelocity();				 // Gets the Bullet velocity
	void renderCollisionBox();				// Use this function to show the collision box
};
#endif