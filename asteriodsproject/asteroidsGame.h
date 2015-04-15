#ifndef _ASTEROIDSGAME_H
#define _ASTEROIDSGAME_H

// Card game headers
#include "cAsteroid.h"
#include "cRocket.h"
#include "cBullet.h"
#include "cBkGround.h"
#include "cEnemy2.h"
#include "cBullet2.h"

extern vector<cTexture*> theGameTextures;
extern vector<cAsteroid*> theAsteroids;
extern vector<cEnemy2*> theShips;
extern vector<cBullet*> theRocketBullets;
extern vector<cBullet2*> theBigBullets;

#endif