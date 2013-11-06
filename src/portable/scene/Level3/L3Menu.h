#ifndef LEVEL3_H
#define L3MENULAYER

#include "../Levels.h"
#include "L3GameLayer.h"

namespace Level3 {

#include "../../AppMacros.h"


USING_NS_CC;

class L3Menu : public Levels{
public:
	~L3Menu();
	static cocos2d::CCScene *scene();

private:
	virtual bool init();
	
private:
    L3Menu();
	
	void initSounds();
	void initScreen();
	void creteMenu();
	
	void playEfectCallback(CCObject *pSender);
	void aboutCallback(CCObject *pSender);
	void setingsCallback(CCObject *pSender);
	
	void flareEffect(CCObject *parent,
					 CCObject *pSelectorTarget,
					 SEL_CallFunc selector);
	void killflareCallback(CCObject* pSender);
	void newGameCallback(CCObject* pSender);
	
	CREATE_FUNC(L3Menu)
	
	
    CCSize _winSize;
	
};

};
#endif // LEVEL3_H