#include "SplashesListPopup.h"
#include <fmt/format.h>
#include "EditEntriesLayer.h"
#include "Geode/binding/ButtonSprite.hpp"
#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include "Geode/cocos/layers_scenes_transitions_nodes/CCLayer.h"
#include "Geode/ui/BasedButtonSprite.hpp"

extern std::vector<std::vector<std::string>> default_splashes;

SplashesListPopup* SplashesListPopup::create(ArrayListNode* node) {
    SplashesListPopup* ret = new SplashesListPopup();
    if (ret && ret->initAnchored(435.f, 300.f, node)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool SplashesListPopup::setup(ArrayListNode* node) {
    this->setZOrder(250);
    this->setTitle("Splashes");
    this->m_node = node;
    auto item_arr = CCArray::create();
    this->setupSplashesList(offset.x, offset.y, 320, 225);
    auto addBtn_spr = ButtonSprite::create("Add Splash", 0, false, "goldFont.fnt", "GJ_button_05.png", 30.f, 0.7f);
    addBtn_spr->setScale(0.7);
    auto addBtn = CCMenuItemSpriteExtra::create(
        addBtn_spr,
        this,
        menu_selector(SplashesListPopup::addEntry)
    );
    addBtn->setPosition({offset.x + 155.f, offset.y + -130.f});
    auto deleteAllBtn_spr = ButtonSprite::create("Remove All", 0, false, "goldFont.fnt", "GJ_button_05.png", 30.f, 0.7f);
    deleteAllBtn_spr->setScale(0.7);
    auto deleteAllBtn = CCMenuItemSpriteExtra::create(
        deleteAllBtn_spr,
        this,
        menu_selector(SplashesListPopup::deleteAllSplashes)
    );
    deleteAllBtn->setPosition({offset.x + -155.f, offset.y + -130.f});
    auto resetBtn_spr = ButtonSprite::create("Reset", 0, false, "goldFont.fnt", "GJ_button_05.png", 30.f, 0.7f);
    resetBtn_spr->setScale(0.7);
    this->m_resetBtn = CCMenuItemSpriteExtra::create(
        resetBtn_spr,
        this,
        menu_selector(SplashesListPopup::resetSplashes)
    );
    this->m_resetBtn->setPosition({offset.x, offset.y + -130.f});
    this->checkForChanges();
    this->m_buttonMenu->addChild(addBtn);
    this->m_buttonMenu->addChild(this->m_resetBtn);
    this->m_buttonMenu->addChild(deleteAllBtn);
    return true;
}

void SplashesListPopup::addEntry(CCObject* sender) {
    auto node = EditEntriesLayer::create(this->m_node, 0, 0, this);
    CCScene::get()->addChild(node);
}

void SplashesListPopup::editEntry(CCObject* sender) {
    auto node = EditEntriesLayer::create(this->m_node, std::stoi(static_cast<CCMenuItemSpriteExtra*>(sender)->getID()), 1, this);
    CCScene::get()->addChild(node);
}

void SplashesListPopup::deleteEntry(CCObject* sender) {
    if(this->m_node->getValue().size() <= 1) {
        return FLAlertLayer::create(
            "Error",
            "There's must be at least one splash!",
            "OK"
        )->show();
    }
    auto index = std::stoi(static_cast<CCMenuItemSpriteExtra*>(sender)->getID());
    geode::createQuickPopup(
        "Info",
        fmt::format("Are you sure you want to delete splash {}?", index + 1).c_str(),
        "Yes", "No",
        [this, index](auto, bool btn2) {
            if(!btn2) {
                std::vector<std::vector<std::string>> v = this->m_node->getValue();
                v.erase(v.begin() + index);
                this->m_node->setValue(v);
                this->updateSplashesList(offset.x, offset.y, 320, 225);
                this->m_node->dispatchChangedPublic();
                this->checkForChanges();
            } 
        }
    );
}

void SplashesListPopup::setupSplashesList(float pos_x, float pos_y, float scale_x, float scale_y) {
    auto item_arr = CCArray::create();
    auto splash_array = this->m_node->getValue();
    for(int i = 0;i < splash_array.size();i++) {
        auto itemMenu = CCMenu::create();
        itemMenu->setPosition({scale_x - 40, 40.f / 2.f});
        itemMenu->setContentWidth(73);
        itemMenu->setLayout(RowLayout::create()->setAutoScale(false), false);
        auto splash = CCLabelBMFont::create(splash_array.at(i).at(0).c_str(), "bigFont.fnt");
        splash->setScale(0.5f);
        splash->setAnchorPoint({0.f, 0.5f});
        splash->setPosition({5.f, 20.f});
        splash->limitLabelWidth(scale_x - 86.f, 0.5f, 0.2f);
        auto deleteSpr = CCSprite::createWithSpriteFrameName("GJ_trashBtn_001.png");
        deleteSpr->setScale(0.8f);
        auto deleteBtn = CCMenuItemSpriteExtra::create(
            deleteSpr,
            this,
            menu_selector(SplashesListPopup::deleteEntry)
        );
        deleteBtn->setID(fmt::format("{}", i).c_str());
        auto editSprText = CCLabelBMFont::create("Edit", "bigFont.fnt");
        auto editSpr = CircleButtonSprite::create(editSprText, CircleBaseColor::Pink);
        editSpr->setScale(0.7f);
        auto editBtn = CCMenuItemSpriteExtra::create(
            editSpr,
            this,
            menu_selector(SplashesListPopup::editEntry)
        );
        editBtn->setID(fmt::format("{}", i).c_str());
        itemMenu->addChild(editBtn);
        itemMenu->addChild(deleteBtn);
        auto item_node = CCNode::create();
        item_node->addChild(splash);
        item_node->addChild(itemMenu);
        item_arr->addObject(item_node);
        itemMenu->updateLayout();
    }
#if !defined GEODE_IS_MACOS
    auto splashListBg = CCLayerColor::create();
    splashListBg->setOpacity(75);
    splashListBg->setZOrder(-1);
    splashListBg->setContentSize(ccp(scale_x, scale_y));
#endif
    auto list = ListView::create(item_arr, 40.f, scale_x, scale_y);
    list->setPosition({pos_x - (scale_x / 2), pos_y - (scale_y / 2)});
    list->setID("list");
    auto splashListBorderTop = CCScale9Sprite::createWithSpriteFrameName("GJ_commentTop_001.png");
    splashListBorderTop->setContentSize(ccp(scale_x + 12.f, 22.f));
    splashListBorderTop->setPosition({scale_x / 2, scale_y - 5});
    auto splashListBorderDown = CCScale9Sprite::createWithSpriteFrameName("GJ_commentTop_001.png");
    splashListBorderDown->setContentSize(ccp(scale_x + 12.f, 22.f));
    splashListBorderDown->setPosition({scale_x / 2, 5});
    splashListBorderDown->setRotation(180);
    auto splashListBorderLeft = CCScale9Sprite::createWithSpriteFrameName("GJ_commentSide_001.png");
    splashListBorderLeft->setContentSize(ccp(22.f, scale_y - 30.f));
    splashListBorderLeft->setPosition({-9.7f, scale_y / 2});
    auto splashListBorderRight = CCScale9Sprite::createWithSpriteFrameName("GJ_commentSide_001.png");
    splashListBorderRight->setContentSize(ccp(22.f, scale_y - 30.f));
    splashListBorderRight->setPosition({scale_x + 9.7f, scale_y / 2});
    splashListBorderRight->setRotation(180);
#if !defined GEODE_IS_MACOS
    list->addChild(splashListBg);
#endif
    list->addChild(splashListBorderTop);
    list->addChild(splashListBorderDown);
    list->addChild(splashListBorderLeft);
    list->addChild(splashListBorderRight);
    this->m_mainLayer->addChild(list);
}

void SplashesListPopup::updateSplashesList(float pos_x, float pos_y, float scale_x, float scale_y) {
    this->m_mainLayer->getChildByID("list")->removeFromParentAndCleanup(true);
    this->setupSplashesList(pos_x, pos_y, scale_x, scale_y);
}

void SplashesListPopup::deleteAllSplashes(CCObject* sender) {
    geode::createQuickPopup(
        "Info",
        "Are you sure you want to delete all splashes at once?",
        "Yes", "No",
        [this](auto, bool btn2) {
            if(!btn2) {
                std::vector<std::vector<std::string>> v = {
                    {"Splash", "0.6"}
                };
                this->m_node->setValue(v);
                this->m_node->dispatchChangedPublic();
                this->updateSplashesList(offset.x, offset.y, 320, 225);
                this->checkForChanges();
            }
        }
    );
}

void SplashesListPopup::resetSplashes(CCObject* sender) {
    geode::createQuickPopup(
        "Info",
        "Are you sure?",
        "Yes", "No",
        [this, sender](auto, bool btn2) {
            if(!btn2) {
                this->m_node->setValue(default_splashes);
                this->m_node->dispatchChangedPublic();
                this->updateSplashesList(offset.x, offset.y, 320, 225);
                this->checkForChanges();
            }
        }
    );
}

void SplashesListPopup::checkForChanges() {
    if(this->m_node->hasNonDefaultValue()) {
        this->m_resetBtn->setVisible(true);
    } else {
        this->m_resetBtn->setVisible(false);
    }
}