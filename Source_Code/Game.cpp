#include "Game.h"
#include "MidGameDialogueScene.h"
#include "LoseGameDialogueScene.h"
#include "SimpleAudioEngine.h"
#include <sstream>
#include <ctime>

#define attackButtonTag 1010
#define magicButtonTag 1011
#define specialButtonTag 1012

#define BOSSHEALTH 11111
#define PLAYERTAG 22222
#define BOSSTAG 33333

#define SPECIAL 44444
#define LASER 55555


cocos2d::Scene* Game::createScene()
{
	/*
	*	Create a scene from the cocos2d library that will hold the
	*	Main Menu layer, displaying the buttons for moving across the
	*	game's menu system and getting to the game, as well as displays
	*	the title screen
	*/
	auto scene = cocos2d::Scene::create();
	auto layer = Game::create();
	scene->addChild(layer);

	return scene;
}

bool Game::init()
{
	if (!Layer::init())
	{
		return false;
	}
	srand(std::time(NULL));

	CocosDenshion::SimpleAudioEngine* audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->stopBackgroundMusic(true);
	audio->playBackgroundMusic("Audio/Finished_Sounds/Tracks/Boss.mp3", true);

	time = 200;
	level = 0;
	scheduleUpdate();
	gm = GameManager::getInstance();
	gm->addBosses();
	Car* car = gm->car;
//	Boss* boy = gm->levels.at(0);

	auto background = cocos2d::Sprite::create("BattleBackground.png");
	background->setScale(gm->scaler);
	background->setPosition
	(
		cocos2d::Vec2
		(
			origin.x + visibleSize.width/2,// - (background->getContentSize().width / 2),
			origin.y + visibleSize.height/2// - background->getContentSize().height / 2
		)
	);
	this->addChild(background, 1);

	auto attackButton = cocos2d::Sprite::create("Attack.png");
	attackButton->setScale(gm->scaler);
	attackButton->setPosition
	(
		cocos2d::Vec2
		(
			origin.x + visibleSize.width - (attackButton->getContentSize().width/2*gm->scaler),
			origin.y + attackButton->getContentSize().height / 4 + (6 * visibleSize.height / 8)
		)
	);
	this->addChild(attackButton, 1, attackButtonTag);

	auto magicButton = cocos2d::Sprite::create("Magic.png");
	magicButton->setScale(gm->scaler);
	magicButton->setPosition
	(
		cocos2d::Vec2
		(
			origin.x +visibleSize.width - (magicButton->getContentSize().width/2*gm->scaler),
			origin.y + magicButton->getContentSize().height / 4 + (4 * visibleSize.height / 8)
		)
	);
	this->addChild(magicButton, 1, magicButtonTag);
	CCLOG("%f, %f", visibleSize.width, gm->scaler);

	auto specialButton = cocos2d::Sprite::create("Special.png");
	specialButton->setScale(gm->scaler);
	specialButton->setPosition
	(
		cocos2d::Vec2
		(
			origin.x + visibleSize.width - ((specialButton->getContentSize().width/2)*gm->scaler),
			origin.y + specialButton->getContentSize().height / 4 + (2 * visibleSize.height / 8)
		)
	);
	this->addChild(specialButton, 1, specialButtonTag);

	auto player = cocos2d::Sprite::create(gm->car->filename);
	player->setScale(gm->scaler/2);
	player->setPosition
	(
		cocos2d::Vec2
		(
			origin.x + (8 * visibleSize.width / 12),
			origin.y + (3 * visibleSize.height / 8)
		)
	);
	this->addChild(player, 1, PLAYERTAG);

	std::string gh;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	gh = std::to_string(gm->car->gameHealth);

#else CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	std::ostringstream gh1;
	gh1 << gm->car->gameHealth;
	gh = gh1.str();
#endif
	healthLabel = cocos2d::Label::createWithTTF("Player Health: " + gh, "fonts/arial.ttf", 12);
	healthLabel->setScale(gm->scaler);
	healthLabel->setColor(cocos2d::Color3B::GREEN);
	healthLabel->setPosition
	(
		cocos2d::Vec2
		(
			origin.x + (9 * visibleSize.width / 12) - healthLabel->getContentSize().width / 2,
			origin.y + ( visibleSize.height / 8) - healthLabel->getContentSize().height / 2
		)
	);
	this->addChild(healthLabel, 1);

	bossSprite = cocos2d::Sprite::create(gm->levels.at(0)->filename);
	bossSprite->setScale(gm->scaler);
	bossSprite->setPosition
	(
		cocos2d::Vec2
		(
			origin.x + (3 * visibleSize.width / 12) - bossSprite->getContentSize().width / 2,
			origin.y + (4.5 * visibleSize.height / 8) - bossSprite->getContentSize().height / 2
		)
	);
	this->addChild(bossSprite, 1, BOSSTAG);
	startPosOfBoss = bossSprite->getPositionX();
	auto bossLabel = cocos2d::Label::createWithTTF("Boss Health: " ,"fonts/arial.ttf", 12);
	bossLabel->setScale(gm->scaler);
	bossLabel->setPosition
	(
		cocos2d::Vec2
		(
			origin.x + 0.05*visibleSize.width + bossLabel->getContentSize().width * gm->scaler / 2,
			origin.y + (1.75 * visibleSize.height / 8) - bossLabel->getContentSize().height / 2
		)
	);
	this->addChild(bossLabel, 1);

	auto emptyHealth = cocos2d::Sprite::create("HealthNone.png");
	emptyHealth->setScale(gm->scaler);
	emptyHealth->setPosition
	(
		cocos2d::Vec2
		(
			origin.x + emptyHealth->getContentSize().width * gm->scaler / 2,
			origin.y + (visibleSize.height / 8) - emptyHealth->getContentSize().height / 2
		)
	);
	this->addChild(emptyHealth, 1);

	auto bossHealth = cocos2d::Sprite::create("Health2.png");
	bossHealth->setScale(gm->scaler);
	bossHealth->setPosition
	(
		cocos2d::Vec2
		(
			origin.x + bossHealth->getContentSize().width * gm->scaler / 2,
			origin.y + (visibleSize.height / 8) - bossHealth->getContentSize().height / 2
		)
	);
	this->addChild(bossHealth, 1, BOSSHEALTH);
	startPosOfBossHealth = bossHealth->getContentSize().width * gm->scaler;




//	player->setScale(gm->scaler);
	
	auto clock = cocos2d::Sprite::create("Clock.png");//, "fonts/Clock.ttf", 16);
	clock->setScale(gm->scaler);
	clock->setPosition
	(
		cocos2d::Vec2
		(
			origin.x + (6 * visibleSize.width / 12),
			origin.y + (7.5 * visibleSize.height / 8)
		)
	);
	this->addChild(clock, 1);


	std::string timeLeft;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	timeLeft = std::to_string(time);

#else CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	std::ostringstream timeLeft1;
	timeLeft1 << time;
	timeLeft = timeLeft1.str();
#endif
	timerLabel = cocos2d::Label::createWithTTF(timeLeft, "fonts/Clock.ttf", 16);
	timerLabel->setColor(cocos2d::Color3B::BLACK);
	timerLabel->setScale(gm->scaler);
	timerLabel->setPosition
	(
		cocos2d::Vec2
		(
			origin.x + (6 * visibleSize.width / 12),
			origin.y + (7.5 * visibleSize.height / 8)
		)
	);
	this->addChild(timerLabel, 1);

	auto listener1 = cocos2d::EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);

	listener1->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		static int x = 0;

		auto target = static_cast<cocos2d::Sprite*>(event->getCurrentTarget());

		cocos2d::Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
		cocos2d::Size s = target->getContentSize();
		cocos2d::Rect rect = cocos2d::Rect(0, 0, s.width, s.height);
		float originalXPos = target->getPosition().x;
		float originalYPos = target->getPosition().y;

		if (rect.containsPoint(locationInNode))
		{
			if (target->getTag() == 1010)
			{
				buttonPushed = true;
				buttonClicked = 0;
				moveButton = true;
			}
			else if (target->getTag() == 1011)
			{
				buttonPushed = true;
				buttonClicked = 1;
				moveButton = true;
			}
			else if (target->getTag() == 1012)
			{
				buttonPushed = true;
				buttonClicked = 2;
				moveButton = true;
			}
			return true;
		}
		return false;

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, attackButton);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), magicButton);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), specialButton);

	return true;
}

void Game::changeHealth(int d)
{
	if (d <= 0)
	{
		changeTimer(200 / gm->car->currentSpeed);
	}
	gm->car->currentHealth -= d;

	if (gm->car->currentHealth >= gm->car->gameHealth)
	{
		gm->car->currentHealth = gm->car->gameHealth;
	}
	std::string healthLeft;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	healthLeft = std::to_string(gm->car->currentHealth);

#else CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	std::ostringstream healthLeft1;
	healthLeft1 << gm->car->currentHealth;
	healthLeft = healthLeft1.str();
#endif

	healthLabel->setString("Health: " + healthLeft);
	if (gm->car->currentHealth <= 0)
	{
		//fade out to bad end // lost all health
		auto action = cocos2d::Sequence::create
		(
			cocos2d::DelayTime::create(2),
			cocos2d::CallFunc::create
			(
				[&]()
				{
					
					auto StoryScene = LoseGameDialogueScene::createScene();
					cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionRotoZoom::create(2, StoryScene));
				}
			),
			NULL
		);

		this->runAction(action);
	}
}

void Game::changeTimer(int d)
{
	time -= d;
	std::string timeLeft;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	timeLeft = std::to_string(time);

#else CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	std::ostringstream timeLeft1;
	timeLeft1 << time;
	timeLeft = timeLeft1.str();
#endif

	timerLabel->setString(timeLeft);

	if (time <= 0)
	{
		auto action = cocos2d::Sequence::create
		(
			cocos2d::DelayTime::create(2),
			cocos2d::CallFunc::create
			(
				[&]()
				{
					
					auto StoryScene = LoseGameDialogueScene::createScene();
					cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionRotoZoom::create(2, StoryScene));
				}
			),
			NULL
		);
		runAction(action);
	}
}

void Game::update(float delta)
{
	cocos2d::Sprite* attack = (cocos2d::Sprite*)getChildByTag(attackButtonTag);
	cocos2d::Sprite* magic = (cocos2d::Sprite*)getChildByTag(magicButtonTag);
	cocos2d::Sprite* special = (cocos2d::Sprite*)getChildByTag(specialButtonTag);

	if (moveButton)
	{
		if (buttonPushed)
		{
			attack->setPositionX(attack->getPositionX() + 100 * delta);
			magic->setPositionX(magic->getPositionX() + 100 * delta);
			special->setPositionX(special->getPositionX() + 100 * delta);
			if (attack->getPositionX() > director->getVisibleSize().width + (gm->scaler * attack->getContentSize().width)/2 )
			{
				buttonPushed = false;
				if (buttonLayer == 0)
				{
					if (buttonClicked == 0)
					{
						attack->setTexture("Slash.png");
						magic->setTexture("Strike.png");
						special->setTexture("Back.png");
						attMagSpe = 0;
						buttonLayer++;
					}
					else if (buttonClicked == 1)
					{
						attack->setTexture(gm->car->magic);
						magic->setTexture("Cure.png");
						special->setTexture("Back.png");
						attMagSpe = 1;
						buttonLayer++;
					}
					else if (buttonClicked == 2)
					{
						attack->setTexture(gm->car->special1);
						magic->setTexture(gm->car->special2);
						special->setTexture("Back.png");
						attMagSpe = 2;
						buttonLayer++;
					}
				}
				else
				{
					if (buttonClicked == 0)
					{
						attack->setTexture("Attack.png");
						magic->setTexture("Magic.png");
						special->setTexture("Special.png");
						if (attMagSpe == 0) // first attack
						{
							//slash
							cocos2d::Animation* a = cocos2d::Animation::createWithSpriteFrames(gm->car->physicalAnim, 0.2f, 1);
							cocos2d::Animate* an = cocos2d::Animate::create(a);
							getChildByTag(PLAYERTAG)->runAction(an);
							calculateDamage(1);
							CocosDenshion::SimpleAudioEngine* audio = CocosDenshion::SimpleAudioEngine::getInstance();
							audio->playEffect("Audio/Finished_Sounds/Attacks/Sword.mp3");
						}
						else if (attMagSpe == 1)//elemental attack
						{
							//ice
							cocos2d::Animation* a = cocos2d::Animation::createWithSpriteFrames(gm->car->magicAnim, 0.2f, 1);
							cocos2d::Animate* an = cocos2d::Animate::create(a);
							getChildByTag(PLAYERTAG)->runAction(an);
							calculateDamage(2);

							CocosDenshion::SimpleAudioEngine* audio = CocosDenshion::SimpleAudioEngine::getInstance();
							audio->playEffect(gm->car->magicSound);
						}
						else // special 1
						{
							calculateDamage(3);

							CocosDenshion::SimpleAudioEngine* audio = CocosDenshion::SimpleAudioEngine::getInstance();
							audio->playEffect(gm->car->specialSound1);
						}
						buttonLayer--;
					}
					else if (buttonClicked == 1)
					{
						attack->setTexture("Attack.png");
						magic->setTexture("Magic.png");
						special->setTexture("Special.png");
						if (attMagSpe == 0) // second attack
						{
							//strike
							cocos2d::Animation* a = cocos2d::Animation::createWithSpriteFrames(gm->car->physicalAnim, 0.2f, 1);
							cocos2d::Animate* an = cocos2d::Animate::create(a);
							getChildByTag(PLAYERTAG)->runAction(an);
							calculateDamage(4);

							CocosDenshion::SimpleAudioEngine* audio = CocosDenshion::SimpleAudioEngine::getInstance();
							audio->playEffect("Audio/Finished_Sounds/Attacks/Strike.mp3");
						}
						else if (attMagSpe == 1)//heal
						{
							cocos2d::Animation* a = cocos2d::Animation::createWithSpriteFrames(gm->car->healingAnim, 0.2f, 1);
							cocos2d::Animate* an = cocos2d::Animate::create(a);
							getChildByTag(PLAYERTAG)->runAction(an);
							changeHealth(-gm->car->gameHealth);

							CocosDenshion::SimpleAudioEngine* audio = CocosDenshion::SimpleAudioEngine::getInstance();
							audio->playEffect("Audio/Finished_Sounds/Magic/Cure.mp3");
						}
						else // special 2
						{
							calculateDamage(6);

							CocosDenshion::SimpleAudioEngine* audio = CocosDenshion::SimpleAudioEngine::getInstance();
							audio->playEffect(gm->car->specialSound1);
						}
						buttonLayer--;
					}
					else if (buttonClicked == 2)
					{
						attack->setTexture("Attack.png");
						magic->setTexture("Magic.png");
						special->setTexture("Special.png");
						buttonLayer--;

					}
				}
			}
		}
		if (!buttonPushed && moveButton)
		{
			attack->setPositionX(attack->getPositionX() - 100 * delta);
			magic->setPositionX(magic->getPositionX() - 100 * delta);
			special->setPositionX(special->getPositionX() - 100 * delta);
			if (attack->getPositionX() < origin.x + visibleSize.width - (attack->getContentSize().width/2*gm->scaler))
			{
				moveButton = false;
			}
		}	
	}

	float percentageMoved = 100 - (100 * ((getChildByTag(BOSSHEALTH)->getPositionX() + startPosOfBossHealth/2) / startPosOfBossHealth));
	
	if (percentDamageToBoss > percentageMoved)
	{
		getChildByTag(BOSSHEALTH)->setPositionX
		(
			getChildByTag(BOSSHEALTH)->getPositionX() - 100 * delta
		);
	}

	if (transform)
	{
		getChildByTag(BOSSHEALTH)->setOpacity(bossSprite->getOpacity() - 128 * delta);
		bossSprite->setOpacity(bossSprite->getOpacity() - 128 * delta);

		if (bossSprite->getOpacity() < 2)
		{
			transform = false;
		}
		if (!transform)
		{
			bossSprite->setTexture(gm->levels.at(level)->filename);
			percentDamageToBoss = 0;
			getChildByTag(BOSSHEALTH)->setPosition
			(
				cocos2d::Vec2
				(
					origin.x + getChildByTag(BOSSHEALTH)->getContentSize().width * gm->scaler / 2,
					origin.y + (visibleSize.height / 8) - getChildByTag(BOSSHEALTH)->getContentSize().height / 2
				)
			);
			transformBack = true;
		}
	}
	if (transformBack)
	{
		getChildByTag(BOSSHEALTH)->setOpacity(bossSprite->getOpacity() + 128 * delta);
		bossSprite->setOpacity(bossSprite->getOpacity() + 128 * delta);
		if (bossSprite->getOpacity() > 253)
		{
			transformBack = false;
			bossSprite->setOpacity(255);
		}
	}

	if(headbuttStart)
	{
		getChildByTag(BOSSTAG)->setPositionX(getChildByTag(BOSSTAG)->getPositionX() + 250 * delta);
		if (getChildByTag(BOSSTAG)->getPositionX() > visibleSize.width / 2)
		{
			headbuttStart = false;
			headbuttEnd = true;
		}
	}
	if (headbuttEnd)
	{
		getChildByTag(BOSSTAG)->setPositionX(getChildByTag(BOSSTAG)->getPositionX() - 250 * delta);
		if (getChildByTag(BOSSTAG)->getPositionX() < startPosOfBoss)
		{
			headbuttEnd = false;
		}
	}

}

void Game::damageBoss(int damage)
{
	gm->levels.at(level)->health -= damage;
	percentDamageToBoss += 100 * damage / gm->levels.at(level)->totalHealth;
	if (gm->levels.at(level)->health <= 0)
	{
		calculateScore();
		bool ready = false;
		if (level == 0)
		{
			transform = true;
			level++;
			
		}
		else if (level == 1)
		{
			auto action = cocos2d::Sequence::create
			(
				cocos2d::DelayTime::create(2),
				cocos2d::CallFunc::create
				(
					[&]()
					{
						
						auto StoryScene = MidGameDialogueScene::createScene();
						cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionRotoZoom::create(2, StoryScene));
					}
				),
			NULL
		);

			this->runAction(action);
		}
	}
	else
	{
		int returnDamage = bossAI();
		changeHealth(returnDamage);
	}
}

int Game::calculateDamage(int attack)
{
	Boss* b = gm->levels.at(level);
	Car* c = gm->car;
	cocos2d::Sprite* boss = (cocos2d::Sprite*)getChildByTag(BOSSTAG);
	boss->setTexture(b->hurtFilename);
	if (attack == 1)
	{
		damage = 300 - (5*b->defence) + c->currentAttack;
		changeTimer(10 - c->currentSpeed/10);
	}
	else if (attack == 2)
	{
		damage = (500 + c->currentAttack) - (3*b->defence);
		changeTimer(20 - 2*(c->currentSpeed/10));
	}
	else if (attack == 3)
	{
		int damage1 = 0;
		cocos2d::Animation* a = cocos2d::Animation::createWithSpriteFrames(gm->car->special1Anim, 0.3f, 1);
		cocos2d::Animate* an = cocos2d::Animate::create(a);

		auto specialSprite = cocos2d::Sprite::createWithSpriteFrame(a->getFrames().at(0)->getSpriteFrame());
		specialSprite->setScale(gm->scaler/2);
		specialSprite->setPosition
		(
			cocos2d::Vec2
			(
				getChildByTag(PLAYERTAG)->getPositionX() - gm->scaler * getChildByTag(PLAYERTAG)->getContentSize().width,
				getChildByTag(PLAYERTAG)->getPositionY()// - gm->scaler * getChildByTag(PLAYERTAG)->getContentSize().height
			)
		);
		this->addChild(specialSprite, 1, SPECIAL);
		specialSprite->runAction(an);
		auto action = cocos2d::Sequence::create
		(
			cocos2d::DelayTime::create(0.9f),
			cocos2d::CallFunc::create
			(
				[&]()
				{

					int damage1 = 0; 
					damage1 = (800 + gm->car->currentAttack * 3) - (gm->levels.at(level)->defence * 10);
					changeTimer(250 / gm->car->currentSpeed);
					removeChild(getChildByTag(SPECIAL));
					cocos2d::Sprite* boss1 = (cocos2d::Sprite*)getChildByTag(BOSSTAG);
					boss1->setTexture(gm->levels.at(level)->filename);
					if (damage1 < 0)
					{
						damage1 *= -1;
					}
					Game::damageBoss(damage1);
					return 0;
				}
			),
			NULL
		);
		runAction(action);
	}
	else if (attack == 4)
	{
		damage = 300 - (5 * b->defence) + c->currentAttack;
		changeTimer(10 - (7 - c->currentSpeed/10));
	}
	else if (attack == 6)
	{
		cocos2d::Animation* a = cocos2d::Animation::createWithSpriteFrames(gm->car->special2Anim, 0.3f, 1);
		cocos2d::Animate* an = cocos2d::Animate::create(a);
		auto specialSprite = cocos2d::Sprite::createWithSpriteFrame(a->getFrames().at(0)->getSpriteFrame());
		specialSprite->setScale(gm->scaler/2);
		specialSprite->setPosition
		(
			cocos2d::Vec2
			(
				getChildByTag(PLAYERTAG)->getPositionX() - gm->scaler * getChildByTag(PLAYERTAG)->getContentSize().width,
				getChildByTag(PLAYERTAG)->getPositionY()// - gm->scaler * getChildByTag(PLAYERTAG)->getContentSize().height
			)
		);
		this->addChild(specialSprite, 1, SPECIAL);
		specialSprite->runAction(an);
		auto action = cocos2d::Sequence::create
		(

			cocos2d::DelayTime::create(0.9f),
			cocos2d::CallFunc::create
			(
				[&]()
				{

					int damage1 = 0;
					damage1 = (300 + gm->car->currentAttack) - (3 * gm->levels.at(level)->defence);

					gm->car->currentAttack += 10;
					if (gm->car->currentSpeed < 100)
					{
						gm->car->currentSpeed += 10;
					}
					changeTimer(35 - 3 * (gm->car->currentSpeed / 10));

					removeChild(getChildByTag(SPECIAL));
					cocos2d::Sprite* boss1 = (cocos2d::Sprite*)getChildByTag(BOSSTAG);
					boss1->setTexture(gm->levels.at(level)->filename);
					if (damage1 < 0)
					{
						damage1 *= -1;
					}
					Game::damageBoss(damage1);
					return 0;
				}
			),
			NULL
		);
		runAction(action);		
	}
	if (damage < 0)
	{
		damage *= -1;
	}
	auto action = cocos2d::Sequence::create
	(
		cocos2d::DelayTime::create(1),
		cocos2d::CallFunc::create
		(
			[&]()
			{
				
				cocos2d::Sprite* boss = (cocos2d::Sprite*)getChildByTag(BOSSTAG);
				boss->setTexture(gm->levels.at(level)->filename);
				Game::damageBoss(damage);
			}
		),
		NULL
	);
	runAction(action);
	
	return damage;
}

int Game::bossAI()
{
	Boss* b = gm->levels.at(level);
	Car* c = gm->car;

	int returnDamage;
	int randomNoise;
	int random = rand() % 100;
	if ( 1 - (b->health / b->totalHealth) > .3)
	{
		randomNoise = 10 - rand() % 70;
		
		if (random > 95)
		{
			//special attack
			returnDamage = (b->attack * 4) - c->currentDefence/2;
			cocos2d::Animation* a = cocos2d::Animation::createWithSpriteFrames(b->laserAnim, 0.3f, 1);
			cocos2d::Animate* an = cocos2d::Animate::create(a);

			auto specialSprite = cocos2d::Sprite::createWithSpriteFrame(a->getFrames().at(0)->getSpriteFrame());
			specialSprite->setScale(gm->scaler / 2);
			specialSprite->setPosition
			(
				cocos2d::Vec2
				(
					getChildByTag(BOSSTAG)->getPositionX() + gm->scaler * getChildByTag(BOSSTAG)->getContentSize().width,
					getChildByTag(BOSSTAG)->getPositionY() - gm->scaler * getChildByTag(BOSSTAG)->getContentSize().height/2
				)
			);
			this->addChild(specialSprite, 1, LASER);
			specialSprite->runAction(an);
			auto action = cocos2d::Sequence::create
			(

				cocos2d::DelayTime::create(0.9f),
				cocos2d::CallFunc::create
				(
					[&]()
					{
						Game::removeChildByTag(LASER);
					}
				),
				NULL
			);
			runAction(action);
		}
		else if (random > 70)
		{
			//headbutt
			returnDamage = (b->attack * 3) - c->currentDefence;
			headbuttStart = true;
		}
		else
		{
			//claw
			returnDamage = (b->attack * 2) - c->currentDefence;
			cocos2d::Animation* a = cocos2d::Animation::createWithSpriteFrames(b->clawAnim, 0.3f, 1);
			cocos2d::Animate* an = cocos2d::Animate::create(a);

			getChildByTag(BOSSTAG)->runAction(an);
		}
	}
	else if (1 - (b->health / b->totalHealth) > .6)
	{
		randomNoise = 10 - rand() % 60;

		if (random > 85)
		{
			//special attack
			returnDamage = (b->attack * 4) - c->currentDefence / 2;
			cocos2d::Animation* a = cocos2d::Animation::createWithSpriteFrames(b->laserAnim, 0.3f, 1);
			cocos2d::Animate* an = cocos2d::Animate::create(a);

			auto specialSprite = cocos2d::Sprite::createWithSpriteFrame(a->getFrames().at(0)->getSpriteFrame());
			specialSprite->setScale(gm->scaler / 2);
			specialSprite->setPosition
			(
				cocos2d::Vec2
				(
					getChildByTag(BOSSTAG)->getPositionX() - gm->scaler * getChildByTag(BOSSTAG)->getContentSize().width,
					getChildByTag(BOSSTAG)->getPositionY()// - gm->scaler * getChildByTag(PLAYERTAG)->getContentSize().height
				)
			);
			this->addChild(specialSprite, 1, LASER);
			specialSprite->runAction(an);
			auto action = cocos2d::Sequence::create
			(

				cocos2d::DelayTime::create(0.9f),
				cocos2d::CallFunc::create
				(
					[&]()
					{
						Game::removeChildByTag(LASER);
					}
				),
				NULL
			);
			runAction(action);
		}
		else if (random > 55)
		{
			//headbutt
			returnDamage = (b->attack * 3) - c->currentDefence;
			headbuttStart = true;
		}
		else
		{
			//claw
			returnDamage = (b->attack * 2) - c->currentDefence;
			cocos2d::Animation* a = cocos2d::Animation::createWithSpriteFrames(b->clawAnim, 0.3f, 1);
			cocos2d::Animate* an = cocos2d::Animate::create(a);

			getChildByTag(BOSSTAG)->runAction(an);
		}
	}
	else if (1 - (b->health / b->totalHealth) > .8)
	{
		randomNoise = 10 - rand() % 50;

		if (random > 60)
		{
			//special attack
			returnDamage = (b->attack * 4) - c->currentDefence / 2;
			cocos2d::Animation* a = cocos2d::Animation::createWithSpriteFrames(b->laserAnim, 0.3f, 1);
			cocos2d::Animate* an = cocos2d::Animate::create(a);

			auto specialSprite = cocos2d::Sprite::createWithSpriteFrame(a->getFrames().at(0)->getSpriteFrame());
			specialSprite->setScale(gm->scaler / 2);
			specialSprite->setPosition
			(
				cocos2d::Vec2
				(
					getChildByTag(BOSSTAG)->getPositionX() - gm->scaler * getChildByTag(BOSSTAG)->getContentSize().width,
					getChildByTag(BOSSTAG)->getPositionY()// - gm->scaler * getChildByTag(PLAYERTAG)->getContentSize().height
				)
			);
			this->addChild(specialSprite, 1, LASER);
			specialSprite->runAction(an);
			auto action = cocos2d::Sequence::create
			(

				cocos2d::DelayTime::create(0.9f),
				cocos2d::CallFunc::create
				(
					[&]()
					{
						Game::removeChildByTag(LASER);
					}
				),
				NULL
			);
			runAction(action);
		}
		else if (random > 30)
		{
			//headbutt
			returnDamage = (b->attack * 3) - c->currentDefence;
			headbuttStart = true;
		}
		else
		{
			//claw
			returnDamage = (b->attack * 2) - c->currentDefence;
			cocos2d::Animation* a = cocos2d::Animation::createWithSpriteFrames(b->clawAnim, 0.3f, 1);
			cocos2d::Animate* an = cocos2d::Animate::create(a);

			getChildByTag(BOSSTAG)->runAction(an);
		}
	}
	else
	{
		randomNoise = 10 - rand() % 30;

		if (random > 40)
		{
			//special attack
			returnDamage = (b->attack * 4) - c->currentDefence / 2;
			cocos2d::Animation* a = cocos2d::Animation::createWithSpriteFrames(b->laserAnim, 0.3f, 1);
			cocos2d::Animate* an = cocos2d::Animate::create(a);

			auto specialSprite = cocos2d::Sprite::createWithSpriteFrame(a->getFrames().at(0)->getSpriteFrame());
			specialSprite->setScale(gm->scaler / 2);
			specialSprite->setPosition
			(
				cocos2d::Vec2
				(
					getChildByTag(BOSSTAG)->getPositionX() - gm->scaler * getChildByTag(BOSSTAG)->getContentSize().width,
					getChildByTag(BOSSTAG)->getPositionY()// - gm->scaler * getChildByTag(PLAYERTAG)->getContentSize().height
				)
			);
			this->addChild(specialSprite, 1, LASER);
			specialSprite->runAction(an);
			auto action = cocos2d::Sequence::create
			(

				cocos2d::DelayTime::create(0.9f),
				cocos2d::CallFunc::create
				(
					[&]()
					{
						Game::removeChildByTag(LASER);
					}
				),
				NULL
			);
			runAction(action);
		}
		else if (random > 15)
		{
			//headbutt
			returnDamage = (b->attack * 3) - c->currentDefence;
		}
		else
		{
			//claw
			returnDamage = (b->attack * 2) - c->currentDefence;
			cocos2d::Animation* a = cocos2d::Animation::createWithSpriteFrames(b->clawAnim, 0.3f, 1);
			cocos2d::Animate* an = cocos2d::Animate::create(a);

			getChildByTag(BOSSTAG)->runAction(an);
		}
	}
	returnDamage += randomNoise;
	if (returnDamage < 0)
	{
		returnDamage *= -1;
	}

	return returnDamage;
}

void Game::calculateScore()
{
	if (time <= 0)
	{
		time = 1;
	}
	gm->score += gm->car->currentHealth * time;
}
