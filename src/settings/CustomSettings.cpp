#include "CustomSettings.h"

#include <Geode/Bindings.hpp>
#include <string>
#include <cstring>
#include "../main.h"
#include "../layers/SplashesListPopup.h"

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

    m_currentArray = value->getArray();

    auto items = CCArray::create();
    std::stringstream ss;

    for(int i = 0; i < m_currentArray.size(); i++) {
        ss << m_currentArray.at(i).at(0);
        auto label_holder = CCLabelBMFont::create(ss.str().c_str(), "bigFont.fnt");
        label_holder->setScale(0.4f);
        items->addObjectNew(label_holder);
        ss.str("");
    }

    auto ccmenu = CCMenu::create();

    auto spr = ButtonSprite::create("Edit Splashes");

    auto btn = CCMenuItemSpriteExtra::create(
        spr, this, menu_selector(ArrayListNode::createPopup)
    );

    ccmenu->setPosition({width / 2, 20.f});
    btn->setScale(0.7f);
    btn->m_baseScale = 0.7f;

    // auto splashes_view_list = ListView::create(items, 40.f, width - 20.f, 200.f - 50.f);
    // splashes_view_list->setPosition(width / 2, 100.f);

    // this->addChild(splashes_view_list);

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
    // auto input = static_cast<InputNode*>(this->getChildByID("menu")->getChildByID("test-input"));
    // input->setString("test");
    static_cast<ArrayListValue*>(m_value)->setArray(default_splashes);
}

void ArrayListNode::createPopup(cocos2d::CCObject* sender) {
    auto value = static_cast<ArrayListValue*>(m_value);
    auto popup = SplashesListPopup::create(value);
    auto scene = CCScene::get();
    scene->addChild(popup);
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