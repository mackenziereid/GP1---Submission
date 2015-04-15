
#ifndef _CENEMY2_H
#define _CENEMY2_H
#include "cSprite.h"

class cEnemy2 : public cSprite
{
private:
	glm::vec2 asteroidVelocity = glm::vec2(0.0f, 0.0f);

public:
	void render();		// Default render function
	void update(float deltaTime);		// Rocket update method
	void setAsteroidVelocity(glm::vec2 asteroidVel);   // Sets the velocity for the rocket
	glm::vec2 getAsteroidVelocity();				 // Gets the rocket velocity
	void renderCollisionBox();				// Use this function to show the collision box
};
#endif