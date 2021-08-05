#ifndef _BOSS_H_
#define _BOSS_H_

#include "cocos2d.h"

class Boss
{

public:

	std::string filename;
	std::string hurtFilename;
	int totalHealth;
	int health;
	int speed;
	int attack;
	int defence;

	cocos2d::Vector<cocos2d::SpriteFrame*> clawAnim;
	cocos2d::Vector<cocos2d::SpriteFrame*> laserAnim;

	Boss(std::string n);

};

#endif