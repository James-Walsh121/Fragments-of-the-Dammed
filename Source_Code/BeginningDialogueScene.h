#ifndef _BEGINNING_DIALOGUE_H_
#define _BEGINNING_DIALOGUE_H_

#include "cocos2d.h"
#include "GameManager.h"

class BeginningDialogueScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void goToCustomize(cocos2d::Ref* pSender);

	CREATE_FUNC(BeginningDialogueScene);
};

#endif