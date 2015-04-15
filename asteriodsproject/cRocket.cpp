/*
=================
cRocket.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cRocket.h"

void cRocket::render()
{
	glPushMatrix();

	glTranslatef(spritePos2D.x, spritePos2D.y, 0.0f);
	glRotatef(spriteRotation, 0.0f, 0.0f, 1.0f);
	glScalef(spriteScaling.x, spriteScaling.y, 1.0f);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GLTextureID); // Binding of GLtexture name 

	glBegin(GL_QUADS);
	glColor3f(255.0f, 255.0f, 255.0f);
	glTexCoord2f(spriteTexCoordData[0].x, spriteTexCoordData[0].y);
	glVertex2f(-(textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[1].x, spriteTexCoordData[1].y);
	glVertex2f((textureWidth / 2), -(textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[2].x, spriteTexCoordData[2].y);
	glVertex2f((textureWidth / 2), (textureHeight / 2));
	glTexCoord2f(spriteTexCoordData[3].x, spriteTexCoordData[3].y);
	glVertex2f(-(textureWidth / 2), (textureHeight / 2));

	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
/*
=================================================================
Update the sprite position
=================================================================
*/


void cRocket::update(float deltaTime)
{
	if (m_InputMgr->isKeyDown(VK_RIGHT))
	{
		spritePos2D.x += 5.0f;
	}
	if (m_InputMgr->isKeyDown(VK_LEFT))
	{
		spritePos2D.x -= 5.0f;
	}
	if (m_InputMgr->isKeyDown(int('Z')))
	{
		if (bigBullet)
		{
			bigBullet = false;
		} else
		if (!bigBullet)
		{
			bigBullet = true;
		}
	}

	if (m_InputMgr->isKeyDown(VK_UP))
	{
		
	}

	if (m_InputMgr->isKeyDown(VK_SPACE))
	{
		if (!bigBullet)
		{
			// Add new bullet sprite to the vector array
			theRocketBullets.push_back(new cBullet);
			int numBullets = theRocketBullets.size() - 1;
			theRocketBullets[numBullets]->setSpritePos(glm::vec2(spritePos2D.x, spritePos2D.y));
			theRocketBullets[numBullets]->setSpriteTranslation(glm::vec2(12.0f, 12.0f));
			theRocketBullets[numBullets]->setTexture(theGameTextures[3]->getTexture());
			theRocketBullets[numBullets]->setTextureDimensions(theGameTextures[3]->getTWidth(), theGameTextures[3]->getTHeight());
			theRocketBullets[numBullets]->setSpriteCentre();
			theRocketBullets[numBullets]->setBulletVelocity(glm::vec2(0.0f, 0.0f));
			theRocketBullets[numBullets]->setSpriteRotation(getSpriteRotation());
			theRocketBullets[numBullets]->setActive(true);
			theRocketBullets[numBullets]->setMdlRadius();
			// play the firing sound
			m_SoundMgr->getSnd("Shot")->playAudio(AL_TRUE);
		}
		if (bigBullet)
		{
			theBigBullets.push_back(new cBullet2);
			int numBullets = theBigBullets.size() - 1;
			theBigBullets[numBullets]->setSpritePos(glm::vec2(spritePos2D.x, spritePos2D.y));
			theBigBullets[numBullets]->setSpriteTranslation(glm::vec2(3.0f, 3.0f));
			theBigBullets[numBullets]->setTexture(theGameTextures[2]->getTexture());
			theBigBullets[numBullets]->setTextureDimensions(theGameTextures[2]->getTWidth(), theGameTextures[2]->getTHeight());
			theBigBullets[numBullets]->setSpriteCentre();
			theBigBullets[numBullets]->setBulletVelocity(glm::vec2(0.0f, 0.0f));
			theBigBullets[numBullets]->setSpriteRotation(getSpriteRotation());
			theBigBullets[numBullets]->setActive(true);
			theBigBullets[numBullets]->setMdlRadius();
		}
	}

	if (spritePos2D.x + (textureWidth / 2) > 1024)
	{
		spritePos2D.x -= 5.0f;
	}
	if (spritePos2D.x - (textureWidth / 2) < 0)
	{
		spritePos2D.x += 5.0f;
	}

	if (spriteRotation > 360)
	{
		spriteRotation -= 360.0f;
	}

	glm::vec2 spriteVelocityAdd = glm::vec2(0.0f, 0.0f);
	spriteVelocityAdd.x = (glm::sin(glm::radians(spriteRotation)));
	spriteVelocityAdd.y = -(glm::cos(glm::radians(spriteRotation)));

	spriteVelocityAdd *= spriteTranslation;

	rocketVelocity += spriteVelocityAdd;

	spritePos2D += rocketVelocity * deltaTime;

	rocketVelocity *= 0.95;

	/*
	==============================================================
	| Check for collisions
	==============================================================
	*/
	for (vector<cBullet*>::iterator bulletIterartor = theRocketBullets.begin(); bulletIterartor != theRocketBullets.end(); ++bulletIterartor)
	{
		(*bulletIterartor)->update(deltaTime);
		for (vector<cAsteroid*>::iterator asteroidIterator = theAsteroids.begin(); asteroidIterator != theAsteroids.end(); ++asteroidIterator)
		{
			if ((*asteroidIterator)->collidedWith((*asteroidIterator)->getBoundingRect(), (*bulletIterartor)->getBoundingRect()))
			{
				// if a collision set the bullet and asteroid to false
				(*asteroidIterator)->setActive(false);
				(*bulletIterartor)->setActive(false);
				Score += 10;
			}
		}
		for (vector<cEnemy2*>::iterator shipIterator = theShips.begin(); shipIterator != theShips.end(); ++shipIterator)
		{
			if ((*shipIterator)->collidedWith((*shipIterator)->getBoundingRect(), (*bulletIterartor)->getBoundingRect()))
			{
				// if a collision set the bullet and asteroid to false
				(*bulletIterartor)->setActive(false);
			}
		}
	}

	for (vector<cBullet2*>::iterator bbulletIterartor = theBigBullets.begin(); bbulletIterartor != theBigBullets.end(); ++bbulletIterartor)
	{
		(*bbulletIterartor)->update(deltaTime);
		for (vector<cAsteroid*>::iterator asteroidIterator = theAsteroids.begin(); asteroidIterator != theAsteroids.end(); ++asteroidIterator)
		{
			if ((*asteroidIterator)->collidedWith((*asteroidIterator)->getBoundingRect(), (*bbulletIterartor)->getBoundingRect()))
			{
				// if a collision set the bullet and asteroid to false
				(*asteroidIterator)->setActive(false);
				(*bbulletIterartor)->setActive(false);
			}
		}
		for (vector<cEnemy2*>::iterator shipIterator = theShips.begin(); shipIterator != theShips.end(); ++shipIterator)
		{
			if ((*shipIterator)->collidedWith((*shipIterator)->getBoundingRect(), (*bbulletIterartor)->getBoundingRect()))
			{
				// if a collision set the bullet and asteroid to false
				(*shipIterator)->setActive(false);
				(*bbulletIterartor)->setActive(false);
				Score += 50;
			}
		}
	}

	vector<cBullet*>::iterator bulletIterartor = theRocketBullets.begin();
	while (bulletIterartor != theRocketBullets.end())
	{
		if ((*bulletIterartor)->isActive() == false)
		{
			bulletIterartor = theRocketBullets.erase(bulletIterartor);
			// play the explosion sound.
			m_SoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
		}
		else
		{
			//(*bulletIterartor)->update(deltaTime);
			(*bulletIterartor)->render();
			++bulletIterartor;
		}
	}

	vector<cBullet2*>::iterator bbulletIterartor = theBigBullets.begin();
	while (bbulletIterartor != theBigBullets.end())
	{
		if ((*bbulletIterartor)->isActive() == false)
		{
			bbulletIterartor = theBigBullets.erase(bbulletIterartor);
			// play the explosion sound.
			m_SoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
		}
		else
		{
			//(*bulletIterartor)->update(deltaTime);
			(*bbulletIterartor)->render();
			++bbulletIterartor;
		}
	}


}
/*
=================================================================
  Sets the velocity for the rocket
=================================================================
*/
void cRocket::setRocketVelocity(glm::vec2 rocketVel)
{
	rocketVelocity = rocketVel;
}
/*
=================================================================
  Gets the rocket velocity
=================================================================
*/
glm::vec2 cRocket::getRocketVelocity()
{
	return rocketVelocity;
}


int cRocket::getScore()
{
	return Score;
}

bool cRocket::isMenu()
{
	return menuScene;
}