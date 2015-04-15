/*
=================
cRocket.cpp
- Header file for class definition - IMPLEMENTATION
=================
*/
#include "cBkGround.h"

void cBkGround::render()
{
	cSprite::render();
}
/*
=================================================================
Update the sprite position
=================================================================
*/

void cBkGround::update(float deltaTime)
{
	if (m_InputMgr->isKeyDown(VK_SPACE))
	{
		spritePos2D.x += 10;
	}
}
