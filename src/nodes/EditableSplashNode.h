#pragma once

#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include <Geode/Geode.hpp>

extern int splashIndex;

using namespace geode::prelude;

class EditableSplashNode : public cocos2d::CCNode {
    protected:
        cocos2d::CCLabelBMFont* m_label;
        bool init() override;
    public:
        static EditableSplashNode* create();
};