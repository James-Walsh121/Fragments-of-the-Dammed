#ifndef _GAME_H_
#define _GAME_H_

#include "cocos2d.h"
#include "GameManager.h"

class Game :public cocos2d::Layer
{
private:
	int time;
	int level;
	bool buttonPushed = false, moveButton = false, transform = false, transformBack = false;
	bool headbuttStart = false, headbuttEnd = false;
	int buttonLayer = 0, buttonClicked = 0, attMagSpe = 0;
	float startPosOfBoss;
	float percentDamageToBoss = 0;
	float startPosOfBossHealth;
	cocos2d::Label* timerLabel;
	cocos2d::Label* healthLabel;
	cocos2d::Sprite* bossSprite;

	cocos2d::Director* director = cocos2d::Director::getInstance();
	cocos2d::Size visibleSize = director->getVisibleSize();
	cocos2d::Vec2 origin = director->getVisibleOrigin();

	GameManager* gm;
	void damageBoss(int damage);
	int calculateDamage(int atttack);
	int damage = 0;

public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(Game);
	void update(float delta) override;

	void changeTimer(int d);
	void changeHealth(int d);
	int bossAI();
	void goToNext(cocos2d::Ref*);
	void calculateScore();


};

#endif