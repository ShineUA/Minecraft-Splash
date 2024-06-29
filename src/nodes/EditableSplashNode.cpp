#include "./EditableSplashNode.h"
#include "EditableSplashNode.h"
#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include "Geode/cocos/platform/CCPlatformMacros.h"

bool EditableSplashNode::init() {
    if(!CCNode::init()) return false;
    auto savedSplashes = Mod::get()->getSavedValue<std::vector<std::vector<std::string>>>("splashes-vector");

    this->m_label = cocos2d::CCLabelBMFont::create(savedSplashes.at(splashIndex).at(0).c_str(), "goldFont.fnt");
    this->m_label->setPosition(this->m_label->getContentSize() / 2);
    this->setContentSize(this->m_label->getContentSize());
    this->addChild(this->m_label);
    
    this->setPosition({Mod::get()->getSavedValue<float>("pos-x"), Mod::get()->getSavedValue<float>("pos-y")});
    this->setRotationX(Mod::get()->getSavedValue<float>("rot-x"));
    this->setRotationY(Mod::get()->getSavedValue<float>("rot-y"));
    this->setScaleX(Mod::get()->getSavedValue<float>("scale-x"));
    this->setScaleY(Mod::get()->getSavedValue<float>("scale-y"));

    return true;
}

EditableSplashNode* EditableSplashNode::create() {
    auto ret = new EditableSplashNode();
    if(ret && ret->init()) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
        ret = nullptr;
    }
    return ret;
}