#pragma once

#include <Geode/Geode.hpp>
#include "../nodes/EditableSplashNode.h"

using namespace geode::prelude;

class EditSplashAppearanceLayer : public CCLayer {
    protected:
        cocos2d::CCPoint offset = CCDirector::get()->getWinSize() / 2;
        CCMenu* m_menu = CCMenu::create();
        bool init() override;
        void onReturn(CCObject* sender);
    public:
        void keyBackClicked() override;
        static EditSplashAppearanceLayer* scene();
};