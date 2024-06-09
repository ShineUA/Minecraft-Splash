#pragma once
#include "../settings/CustomSettings.h"
#include "Geode/ui/ScrollLayer.hpp"

using namespace geode::prelude;

class SplashesListPopup : public geode::Popup<ArrayListNode*> {
    protected:
        ArrayListNode* m_node;
        CCMenuItemSpriteExtra* m_resetBtn;
        bool setup(ArrayListNode* node) override;
        void setupSplashesList(float pos_x, float pos_y, float scale_x, float scale_y);
        void deleteAllSplashes(cocos2d::CCObject* sender);
        void resetSplashes(cocos2d::CCObject* sender);
    public:
        bool m_isEven;
        size_t m_startSize;
        ScrollLayer* m_scrollLayer;
        const cocos2d::CCPoint offset = {435.f / 2, 300.f / 2};
        void addEntry(cocos2d::CCObject* sender);
        void editEntry(cocos2d::CCObject* sender);
        void deleteEntry(cocos2d::CCObject* sender);
        void destroyNode(cocos2d::CCNode* node);
        void checkForChanges();
        void updateSplashesList(float pos_x, float pos_y, float scale_x, float scale_y);
        static SplashesListPopup* create(ArrayListNode* node);
};

