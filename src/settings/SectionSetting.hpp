#pragma once
#include <Geode/Geode.hpp>
#include <Geode/loader/SettingNode.hpp>
using namespace geode::prelude;


// SECTIONS
// Copied from Beat's CLick Sounds mod (get it now!)

class SectionSettingValue;

class SectionSettingValue : public SettingValue {
protected:
    std::string m_placeholder;
public:
    // lines 5, 8, 11, and 12 are copied from GDUtils
    SectionSettingValue(std::string const& key, std::string const& modID, std::string const& placeholder)
      : SettingValue(key, modID), m_placeholder(placeholder) {}
    bool load(matjson::Value const& json) override {return true;}
    bool save(matjson::Value& json) const override {return true;}
    SettingNode* createNode(float width) override;
};

class SectionSettingNode : public SettingNode {
protected:
    std::string m_description;
    bool init(SectionSettingValue* value, float width) {
        if (!SettingNode::init(value))
            return false;
        this->setContentSize({ width, 40.f });
        std::string name = Mod::get()->getSettingDefinition(value->getKey())->get<CustomSetting>()->json->get<std::string>("name");
        this->m_description = Mod::get()->getSettingDefinition(value->getKey())->get<CustomSetting>()->json->get<std::string>("description");
        auto theMenu = CCMenu::create();
        auto theLabel = CCLabelBMFont::create(name.c_str(),"goldFont.fnt");
        auto infoBtn_spr = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
        infoBtn_spr->setScale(0.6);
        auto infoBtn = CCMenuItemSpriteExtra::create(
            infoBtn_spr,
            this,
            menu_selector(SectionSettingNode::onInfoBtn)
        );
        infoBtn->setPositionX(theLabel->getContentWidth() / 4 + 10);
        theLabel->setScale(.5);
        theLabel->setPositionX(0);
        if(!m_description.empty()) {
            theMenu->addChild(infoBtn);
        }
        theMenu->addChild(theLabel);
        theMenu->setPosition(width / 2, 20.f);
        this->addChild(theMenu);
        return true;
    }
    void onInfoBtn(cocos2d::CCObject* sender) {
        FLAlertLayer::create("Info", m_description.c_str(), "OK")->show();
    }

public:
    void commit() override {
        this->dispatchCommitted();
    }
    bool hasUncommittedChanges() override {
        return false;
    }
    bool hasNonDefaultValue() override {
        return true;
    }
    void resetToDefault() override {}
    static SectionSettingNode* create(SectionSettingValue* value, float width) {
        auto ret = new SectionSettingNode();
        if (ret && ret->init(value, width)) {
            ret->autorelease();
            return ret;
        }
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
};

SettingNode* SectionSettingValue::createNode(float width) {
    return SectionSettingNode::create(this, width);
}