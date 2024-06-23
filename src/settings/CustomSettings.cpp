#include "CustomSettings.h"

#include "../layers/ChooseLayer.h"

extern int splashIndex;
extern std::vector<std::vector<std::string>> default_splashes;

SettingNode* ArrayListValue::createNode(float width) {
    return ArrayListNode::create(this, width);
}

bool ArrayListNode::init(ArrayListValue* value, float width) {
    if (!SettingNode::init(value))
        return false;
    geode::cocos::handleTouchPriority(this);
    this->setValue(value->getArray());
    this->setContentSize({ width, 40.f });
    auto ccmenu = CCMenu::create();
    ButtonSprite* spr;
    spr = ButtonSprite::create("Misc. Options", "goldFont.fnt", Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? "geode.loader/GE_button_05.png" : "GJ_button_01.png");
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
    static_cast<ArrayListValue*>(m_value)->setArray(this->getValue());
    Mod::get()->setSavedValue<std::vector<std::vector<std::string>>>("splashes-vector", static_cast<ArrayListValue*>(m_value)->getArray());
    if(static_cast<ArrayListValue*>(m_value)->getArray().size() == 1) {
        splashIndex = 0;
    } else {
        std::random_device rd; 
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<std::mt19937::result_type> distr(0, static_cast<ArrayListValue*>(m_value)->getArray().size() - 1); 
        splashIndex = distr(gen);
    }
    this->dispatchCommitted();
}

bool ArrayListNode::hasUncommittedChanges() {
    return m_unsavedArray != static_cast<ArrayListValue*>(m_value)->getArray();
}

bool ArrayListNode::hasNonDefaultValue() {
    return m_unsavedArray != default_splashes;
}

std::vector<std::vector<std::string>> ArrayListNode::getValue() {
    return this->m_unsavedArray;
}

void ArrayListNode::setValue(std::vector<std::vector<std::string>> value) {
    this->m_unsavedArray.clear();
    this->m_unsavedArray.assign(value.begin(), value.end());
}

void ArrayListNode::resetToDefault() {
    this->setValue(default_splashes);
    this->dispatchChangedPublic();
}

void ArrayListNode::createPopup(cocos2d::CCObject* sender) {
    auto popup = ChooseLayer::create(this);
    CCScene::get()->addChild(popup);
}

void ArrayListNode::dispatchChangedPublic() {
    this->dispatchChanged();
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


