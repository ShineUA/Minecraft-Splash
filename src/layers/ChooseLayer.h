#pragma once
#include <Geode/Geode.hpp>
#include "../settings/CustomSettings.h"
#include "./SplashesListPopup.h"

using namespace geode::prelude;

class ChooseLayer : public geode::Popup<ArrayListNode*> {
    protected:
        ArrayListNode* m_node;
        const CCPoint offset = {285.f / 2, 125.f / 2};
        bool setup(ArrayListNode* node) override;
        void onSplashesOptionsBtn(cocos2d::CCObject* sender);
        void onEditAppearanceBtn(cocos2d::CCObject* sender);
    public:
        static ChooseLayer* create(ArrayListNode* node);
};