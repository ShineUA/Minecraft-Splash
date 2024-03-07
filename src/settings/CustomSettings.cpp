#include "CustomSettings.h"

#include <Geode/Bindings.hpp>
#include <string>
#include <cstring>
#include "../layers/SplashesListPopup.h"
#include "../layers/EntriesLayer.h"

using namespace geode::prelude;

SettingNode* ArrayListValue::createNode(float width) {
    return ArrayListNode::create(this, width);
}

bool ArrayListNode::init(ArrayListValue* value, float width) {
    if (!SettingNode::init(value))
        return false;
    geode::cocos::handleTouchPriority(this);
    
    // You may change the height to anything, but make sure to call 
    // setContentSize!
    this->setContentSize({ width, 40.f });

    auto ccmenu = CCMenu::create();

    auto spr = ButtonSprite::create("Edit Splashes");

    auto btn = CCMenuItemSpriteExtra::create(
        spr, this, menu_selector(ArrayListNode::createPopup)
    );

    ccmenu->setPosition({width / 2, 20.f});
    btn->setScale(0.7f);
    btn->m_baseScale = 0.7f;

    ccmenu->addChild(btn);
    this->addChild(ccmenu);
    return true;
}

void ArrayListNode::commit() {
    // Set the actual value
    // auto input = static_cast<InputNode*>(this->getChildByID("menu")->getChildByID("test-input"));
    // static_cast<ArrayListValue*>(m_value)->setArray(input->getString());
    // Let the UI know you have committed the value
    this->dispatchCommitted();
}

// Geode calls this to query if the setting value has been changed, 
// and those changes haven't been committed
bool ArrayListNode::hasUncommittedChanges() {
    // todo
    return true;
}

// Geode calls this to query if the setting has a value that is 
// different from its default value
bool ArrayListNode::hasNonDefaultValue() {
    // todo
    return true;
}

// Geode calls this to reset the setting's value back to default
void ArrayListNode::resetToDefault() {
    static_cast<ArrayListValue*>(m_value)->setArray(default_splashes);
    Mod::get()->setSavedValue<std::vector<std::vector<std::string>>>("splashes-vector", default_splashes);
    if(default_splashes.size() == 1) {
        random_splash = 0;
    } else {
        std::random_device rd; 
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<std::mt19937::result_type> distr(0, default_splashes.size() - 1); 
        random_splash = distr(gen);
    }
}

void ArrayListNode::createPopup(cocos2d::CCObject* sender) {
    auto value = static_cast<ArrayListValue*>(m_value);
    auto popup = SplashesListPopup::create(value);
    CCScene::get()->addChild(popup);
}

ArrayListNode* ArrayListNode::create(ArrayListValue* value, float width) {
    auto ret = new ArrayListNode();
    if (ret && ret->init(value, width)) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}