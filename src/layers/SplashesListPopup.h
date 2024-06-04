#pragma once
#include "../settings/CustomSettings.h"

using namespace geode::prelude;

class SplashesListPopup : public geode::Popup<ArrayListNode*> {
    protected:
        const cocos2d::CCPoint offset = cocos2d::CCDirector::sharedDirector()->getWinSize() / 2;
        ArrayListNode* m_node;
        CCMenuItemSpriteExtra* m_resetBtn;
        virtual bool setup(ArrayListNode* node) override;
        virtual void deleteEntry(cocos2d::CCObject* sender);
        virtual void addEntry(cocos2d::CCObject* sender);
        virtual void editEntry(cocos2d::CCObject* sender);
        virtual void setupSplashesList(float pos_x, float pos_y, float scale_x, float scale_y);
        virtual void deleteAllSplashes(cocos2d::CCObject* sender);
        virtual void resetSplashes(cocos2d::CCObject* sender);
    public:
        virtual void checkForChanges();
        virtual void updateSplashesList(float pos_x, float pos_y, float scale_x, float scale_y);
        static SplashesListPopup* create(ArrayListNode* node);
};

