#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one

using namespace std;
#include <sstream>
#include <windows.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSoundMgr.h"
#include "cFontMgr.h"
#include "cSprite.h"
#include "asteroidsGame.h"

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR cmdLine,
	int cmdShow)
{

	//Set our window settings
	const int windowWidth = 1024;
	const int windowHeight = 768;
	const int windowBPP = 16;

	//This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	// This is the sound manager
	static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();

	// This is the Font manager
	static cFontMgr* theFontMgr = cFontMgr::getInstance();

	//The example OpenGL code
	windowOGL theOGLWnd;

	//Attach our the OpenGL window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);

	//Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
	{
		//If it fails

		MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
		return 1;
	}

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
	{
		MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
		return 1;
	}

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	/* initialize random seed: */
	srand((unsigned int)time(NULL));

	// Create vector array of textures
	LPCSTR texturesToUse[] = { "Images\\GP_Enemy1.png", "Images\\GP_Enemy2.png", "Images\\GP_Bullet1.png", "Images\\GP_Bullet2.png", "Images\\ship.png" };
	for (int tCount = 0; tCount < 5; tCount++)
	{
		theGameTextures.push_back(new cTexture());
		theGameTextures[tCount]->createTexture(texturesToUse[tCount]);
	}

	// load game sounds
	// Load Sound
	LPCSTR gameSounds[3] = { "Audio/who10Edit.wav", "Audio/shot007.wav", "Audio/explosion2.wav" };

	//theSoundMgr->add("Theme", gameSounds[0]);
	theSoundMgr->add("Shot", gameSounds[1]);
	theSoundMgr->add("Explosion", gameSounds[2]);

	// load game fontss
	// Load Fonts
	LPCSTR gameFonts[2] = { "Fonts/digital-7.ttf", "Fonts/space age.ttf" };
	theFontMgr->addFont("SevenSeg", gameFonts[0], 24);
	theFontMgr->addFont("Space", gameFonts[1], 24);

	float ai_posX = 100.0f;
	float ai_posY = 50.0f;


	for (int astro = 0; astro < 27; astro++)
	{
		theAsteroids.push_back(new cAsteroid);
		theAsteroids[astro]->setSpritePos(glm::vec2(ai_posX, ai_posY));
		int randAsteroid = rand() % 2;
		theAsteroids[astro]->setTexture(theGameTextures[randAsteroid]->getTexture());
		theAsteroids[astro]->setTextureDimensions(theGameTextures[randAsteroid]->getTWidth(), theGameTextures[randAsteroid]->getTHeight());
		theAsteroids[astro]->setSpriteCentre();
		theAsteroids[astro]->setAsteroidVelocity(glm::vec2(glm::vec2(0.0f, 0.0f)));
		theAsteroids[astro]->setActive(true);
		theAsteroids[astro]->setMdlRadius();
		ai_posX += 75.0f;
		if (astro == 8)
		{
			ai_posX = 100.0f;
			ai_posY += 75.0f;
		}
		else
		if (astro == 17)
		{
			ai_posX = 100.0f;
			ai_posY += 75.0f;
		}
	}

		for (int ships = 0; ships < 5; ships++)
		{
			theShips.push_back(new cEnemy2);
			theShips[ships]->setSpritePos(glm::vec2(75.0f + (200 * ships), 500.0f));
			theShips[ships]->setTexture(theGameTextures[4]->getTexture());
			theShips[ships]->setTextureDimensions(theGameTextures[4]->getTWidth(), theGameTextures[4]->getTHeight());
			theShips[ships]->setSpriteCentre();
			theShips[ships]->setAsteroidVelocity(glm::vec2(glm::vec2(0.0f, 0.0f)));
			theShips[ships]->setActive(true);
			theShips[ships]->setMdlRadius();
		}

		cTexture rocketTxt;
		rocketTxt.createTexture("Images\\GP_Player.png");
		cRocket rocketSprite;
		rocketSprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
		rocketSprite.setSpritePos(glm::vec2(512.0f, 700.0f));
		rocketSprite.setTexture(rocketTxt.getTexture());
		rocketSprite.setTextureDimensions(rocketTxt.getTWidth(), rocketTxt.getTHeight());
		rocketSprite.setSpriteCentre();
		rocketSprite.setRocketVelocity(glm::vec2(0.0f, 0.0f));
		
		cTexture textureBkgd;
		textureBkgd.createTexture("Images\\GP_BG.png");  //Background image
		cBkGround spriteBkgd;
		spriteBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
		spriteBkgd.setTexture(textureBkgd.getTexture());
		spriteBkgd.setTextureDimensions(textureBkgd.getTWidth(), textureBkgd.getTHeight());

		cTexture textureMenuBkgd;
		textureMenuBkgd.createTexture("Images\\intro.png");  //Background image
		cBkGround spriteMenuBkgd;
		spriteMenuBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
		spriteMenuBkgd.setTexture(textureMenuBkgd.getTexture());
		spriteMenuBkgd.setTextureDimensions(textureMenuBkgd.getTWidth(), textureMenuBkgd.getTHeight());

		cTexture textureEndBkgd;
		textureEndBkgd.createTexture("Images\\endScene.png");  //Background image
		cBkGround spriteEndBkgd;
		spriteEndBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
		spriteEndBkgd.setTexture(textureEndBkgd.getTexture());
		spriteEndBkgd.setTextureDimensions(textureEndBkgd.getTWidth(), textureEndBkgd.getTHeight());

		// Attach sound manager to rocket sprite
		rocketSprite.attachSoundMgr(theSoundMgr);

		//This is the mainloop, we render frames until isRunning returns false
		while (pgmWNDMgr->isWNDRunning())
		{
			pgmWNDMgr->processWNDEvents(); //Process any window events

			//We get the time that passed since the last frame
			float elapsedTime = pgmWNDMgr->getElapsedSeconds();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			static bool menuOn = true;
			static bool scoreOn = false;
			int score = rocketSprite.getScore();
			if (score > 545)
			{
				scoreOn = true;
			}
			if (theInputMgr->wasKeyPressed(VK_SPACE) && menuOn)
			{
				menuOn = false;
			}
			if (theInputMgr->wasKeyPressed(VK_SPACE) && scoreOn)
			{
				rocketSprite.Score = 0;
				scoreOn = false;
			}

			if (scoreOn)
			{
				spriteEndBkgd.render();
			}
			if (menuOn && !scoreOn)
			{
				spriteMenuBkgd.render();
			}
			if (!menuOn && !scoreOn)
			{
				spriteBkgd.render();

				rocketSprite.update(elapsedTime);

				vector<cAsteroid*>::iterator asteroidIterator = theAsteroids.begin();
				while (asteroidIterator != theAsteroids.end())
				{
					if ((*asteroidIterator)->isActive() == false)
					{
						asteroidIterator = theAsteroids.erase(asteroidIterator);
					}
					else
					{
						(*asteroidIterator)->update(elapsedTime);
						(*asteroidIterator)->render();
						++asteroidIterator;
					}
				}

				vector<cEnemy2*>::iterator shipIterator = theShips.begin();
				while (shipIterator != theShips.end())
				{
					if ((*shipIterator)->isActive() == false)
					{
						shipIterator = theShips.erase(shipIterator);
					}
					else
					{
						(*shipIterator)->update(elapsedTime);
						(*shipIterator)->render();
						++shipIterator;
					}
				}

				rocketSprite.render();
				int score = rocketSprite.getScore();
				string scoreRes;
				stringstream convertion;
				convertion << score;
				scoreRes = convertion.str();
				LPSTR print_s = const_cast<char *>(scoreRes.c_str());
				theFontMgr->getFont("Space")->printText("Score: ", FTPoint(0.0f, -1.0f, 0.0f));
				theFontMgr->getFont("Space")->printScore(print_s, FTPoint(0.0f, -1.0f, 0.0f));
			}
			pgmWNDMgr->swapBuffers();
			theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);
		}

		theOGLWnd.shutdown(); //Free any resources
		pgmWNDMgr->destroyWND(); //Destroy the program window

		return 0; //Return success
}