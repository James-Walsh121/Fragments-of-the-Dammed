#include "MainMenuScene.h"
#include "BeginningDialogueScene.h"
#include "HowtoPlay.h"
#include "SimpleAudioEngine.h"

cocos2d::Scene* MainMenuScene::createScene()
{
	/*
	*	Create a scene from the cocos2d library that will hold the
	*	Main Menu layer, displaying the buttons for moving across the
	*	game's menu system and getting to the game, as well as displays
	*	the title screen
	*/
	auto scene = cocos2d::Scene::create();
	auto layer = MainMenuScene::create();
	scene->addChild(layer);

	return scene;
}

bool MainMenuScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	/*
	*	The cocos2d::Director functions as a scene manager, navigating
	*	the code through the scenes that make up the game. It also holds
	*	the renderer and other information on the various components that
	*	keep the game running.
	*/

	GameManager* gm = GameManager::getInstance();

	CocosDenshion::SimpleAudioEngine* audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("Audio/Track-1.mp3", true);

	cocos2d::Director* director = cocos2d::Director::getInstance();

	auto visibleSize = director->getVisibleSize();
	cocos2d::Vec2 origin = director->getVisibleOrigin();

	auto bg = cocos2d::Sprite::create("MainMenu.png");
	bg->setScale(gm->scaler);
	CCLOG("VIS SIZE:\t%f", visibleSize.width);
	bg->setPosition
	(
		cocos2d::Vec2
		(
			origin.x + (6 * visibleSize.width / 12),
			origin.y + (4 * visibleSize.height / 8)
		)
	);
	this->addChild(bg, 1);


	auto playGameButton = cocos2d::MenuItemImage::create
	(
		"PlayGameButton.png",
		"PlayGameButton.png",
		CC_CALLBACK_1(MainMenuScene::goToStory, this)
	);
	
	/*
		Set the position of the button using a 2d Vector variable
	*/
	playGameButton->setScale(gm->scaler);
	playGameButton->setPosition
	(
		cocos2d::Vec2
		(
			origin.x + (3 * visibleSize.width / 12),
			origin.y + (2 * visibleSize.height / 8)
		)
	);

	auto menu = cocos2d::Menu::create(playGameButton, NULL);
	menu->setPosition(cocos2d::Vec2::ZERO);
	this->addChild(menu, 1);

	auto HowtoPlay = cocos2d::MenuItemImage::create
	(
		"HowToPlayButton.png",
		"HowToPlayButton.png",
		CC_CALLBACK_1(MainMenuScene::goToControls, this)
	);

	/*
	Set the position of the button using a 2d Vector variable
	*/
	HowtoPlay->setScale(gm->scaler);
	HowtoPlay->setPosition
	(
		cocos2d::Vec2
		(
			origin.x + (6 * visibleSize.width / 12),
			origin.y + (2 * visibleSize.height / 8)
		)
	);

	auto howtomenu = cocos2d::Menu::create(HowtoPlay, NULL);
	howtomenu->setPosition(cocos2d::Vec2::ZERO);
	this->addChild(howtomenu, 1);
/*
	auto optionsButton = cocos2d::MenuItemImage::create
	(
		"Options.png",
		"Options.png",
		CC_CALLBACK_1(MainMenuScene::goToOptions, this)
	);

	/*
	Set the position of the button using a 2d Vector variable
	*/
/*
	optionsButton->setScale(gm->scaler);

	optionsButton->setPosition
	(
		cocos2d::Vec2
		(
			origin.x + visibleSize.width / 2,
			origin.y + (visibleSize.height / 2) - visibleSize.height / 10
		)
	);

	auto optionsMenu = cocos2d::Menu::create(optionsButton, NULL);
	optionsMenu->setPosition(cocos2d::Vec2::ZERO);
	this->addChild(optionsMenu, 1);
	*/
	auto exitButton = cocos2d::MenuItemImage::create
	(
		"Exit.png",
		"Exit.png",
		CC_CALLBACK_1(MainMenuScene::goToExit, this)
	);


	/*
	*	Use the GameManager to scale the image according to the screensize
	*/
	exitButton->setScale(gm->scaler);
	
	/*
	Set the position of the button using a 2d Vector variable
	*/
	exitButton->setPosition
	(
		cocos2d::Vec2
		(
			origin.x + (9 * visibleSize.width / 12),
			origin.y + (2 * visibleSize.height / 8)
		)
	);

	auto exitMenu = cocos2d::Menu::create(exitButton, NULL);
	exitMenu->setPosition(cocos2d::Vec2::ZERO);
	this->addChild(exitMenu, 1);

	return true;
}

void MainMenuScene::goToStory(cocos2d::Ref* pSender)
{
	auto StoryScene = BeginningDialogueScene::createScene();
	cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFlipX::create(2, StoryScene));
}

void MainMenuScene::goToControls(cocos2d::Ref* pSender)
{
	auto StoryScene = HowToPlay::createScene();
	cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFlipX::create(2, StoryScene));
}

void MainMenuScene::goToExit(cocos2d::Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application

	CocosDenshion::SimpleAudioEngine::end();

	cocos2d::Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);
}