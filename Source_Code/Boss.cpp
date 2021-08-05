'#include "Boss.h"

Boss::Boss(std::string n)
{
	filename = n;
	if (filename == "GOD1Aura.png")
	{
		hurtFilename = "God1Hurt.png";
		totalHealth = 1000;
		health = 1000;
		speed = 20;
		attack = 30;
		defence = 25;

		clawAnim.reserve(6);
		clawAnim.pushBack(cocos2d::SpriteFrame::create("GOD1Att1.png", cocos2d::Rect(-130/4, -25, 130, 100)));
		clawAnim.pushBack(cocos2d::SpriteFrame::create("GOD1Att2.png", cocos2d::Rect(-130/4, -25, 130, 100)));
		clawAnim.pushBack(cocos2d::SpriteFrame::create("GOD1Att3.png", cocos2d::Rect(-130 / 4, -25, 130, 100)));
		clawAnim.pushBack(cocos2d::SpriteFrame::create("GOD1Att2.png", cocos2d::Rect(-130 / 4, -25, 130, 100)));
		clawAnim.pushBack(cocos2d::SpriteFrame::create("GOD1Att1.png", cocos2d::Rect(-130 / 4, -25, 130, 100)));
		clawAnim.pushBack(cocos2d::SpriteFrame::create("GOD1Aura.png", cocos2d::Rect(-130 / 4, -25, 130, 100)));
		
		laserAnim.reserve(4);
		laserAnim.pushBack(cocos2d::SpriteFrame::create("Laser1.png", cocos2d::Rect(-20, 18.5, 150, 74)));
		laserAnim.pushBack(cocos2d::SpriteFrame::create("Laser2.png", cocos2d::Rect(-20, 18.5, 150, 74)));
		laserAnim.pushBack(cocos2d::SpriteFrame::create("Laser3.png", cocos2d::Rect(-20, 18.5, 150, 74)));
		laserAnim.pushBack(cocos2d::SpriteFrame::create("Laser4.png", cocos2d::Rect(-20, 18.5, 150, 74)));

	}
	else if(filename == "GOD2Aura.png")
	{
		hurtFilename = "God2Hurt.png";
		totalHealth = 2500;
		health = 2500;
		speed = 30;
		attack = 50;
		defence = 35;	
		
		clawAnim.reserve(6);
		clawAnim.pushBack(cocos2d::SpriteFrame::create("GOD2Att1.png", cocos2d::Rect(-130 / 4, -25, 130, 100)));
		clawAnim.pushBack(cocos2d::SpriteFrame::create("GOD2Att2.png", cocos2d::Rect(-130 / 4, -25, 130, 100)));
		clawAnim.pushBack(cocos2d::SpriteFrame::create("GOD2Att3.png", cocos2d::Rect(-130 / 4, -25, 130, 100)));
		clawAnim.pushBack(cocos2d::SpriteFrame::create("GOD2Att2.png", cocos2d::Rect(-130 / 4, -25, 130, 100)));
		clawAnim.pushBack(cocos2d::SpriteFrame::create("GOD2Att1.png", cocos2d::Rect(-130 / 4, -25, 130, 100)));
		clawAnim.pushBack(cocos2d::SpriteFrame::create("GOD2Aura.png", cocos2d::Rect(-130 / 4, -25, 130, 100)));

		laserAnim.reserve(4);
		laserAnim.pushBack(cocos2d::SpriteFrame::create("Laser1.png", cocos2d::Rect(-20, 18.5, 150, 74)));
		laserAnim.pushBack(cocos2d::SpriteFrame::create("Laser2.png", cocos2d::Rect(-20, 18.5, 150, 74)));
		laserAnim.pushBack(cocos2d::SpriteFrame::create("Laser3.png", cocos2d::Rect(-20, 18.5, 150, 74)));
		laserAnim.pushBack(cocos2d::SpriteFrame::create("Laser4.png", cocos2d::Rect(-20, 18.5, 150, 74)));

	}

	else
	{
		hurtFilename = "FinalBoss.png";
		totalHealth = 3000;
		health = 3000;
		speed = 50;
		attack = 50;
		defence = 25;

		clawAnim.reserve(8);
		clawAnim.pushBack(cocos2d::SpriteFrame::create("FinalBoss1.png", cocos2d::Rect(-130 / 4, -25, 130, 100)));
		clawAnim.pushBack(cocos2d::SpriteFrame::create("FinalBoss2.png", cocos2d::Rect(-130 / 4, -25, 130, 100)));
		clawAnim.pushBack(cocos2d::SpriteFrame::create("FinalBoss3.png", cocos2d::Rect(-130 / 4, -25, 130, 100)));
		clawAnim.pushBack(cocos2d::SpriteFrame::create("FinalBoss4.png", cocos2d::Rect(-130 / 4, -25, 130, 100)));
		clawAnim.pushBack(cocos2d::SpriteFrame::create("FinalBoss3.png", cocos2d::Rect(-130 / 4, -25, 130, 100)));
		clawAnim.pushBack(cocos2d::SpriteFrame::create("FinalBoss2.png", cocos2d::Rect(-130 / 4, -25, 130, 100)));
		clawAnim.pushBack(cocos2d::SpriteFrame::create("FinalBoss1.png", cocos2d::Rect(-130 / 4, -25, 130, 100)));
		clawAnim.pushBack(cocos2d::SpriteFrame::create("FinalBoss.png", cocos2d::Rect(-130 / 4, -25, 130, 100)));

		laserAnim.reserve(4);
		laserAnim.pushBack(cocos2d::SpriteFrame::create("Laser1.png", cocos2d::Rect(-20, 18.5, 150, 74)));
		laserAnim.pushBack(cocos2d::SpriteFrame::create("Laser2.png", cocos2d::Rect(-20, 18.5, 150, 74)));
		laserAnim.pushBack(cocos2d::SpriteFrame::create("Laser3.png", cocos2d::Rect(-20, 18.5, 150, 74)));
		laserAnim.pushBack(cocos2d::SpriteFrame::create("Laser4.png", cocos2d::Rect(-20, 18.5, 150, 74)));

	}
}
