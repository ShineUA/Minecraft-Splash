#pragma once
#include "../settings/CustomSettings.h"

using namespace geode::prelude;

class SplashesListPopup : public geode::Popup<ArrayListNode*> {
    protected:
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
        const cocos2d::CCPoint offset = {435.f / 2, 300.f / 2};
        virtual void checkForChanges();
        virtual void updateSplashesList(float pos_x, float pos_y, float scale_x, float scale_y);
        static SplashesListPopup* create(ArrayListNode* node);
};

