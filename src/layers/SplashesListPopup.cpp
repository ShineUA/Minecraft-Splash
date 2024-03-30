#include "SplashesListPopup.h"
#include <fmt/format.h>
#include "EditEntriesLayer.h"

SplashesListPopup* SplashesListPopup::create(ArrayListNode* node) {
    SplashesListPopup* ret = new SplashesListPopup();
    if (ret && ret->init(435.f, 300.f, node)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool SplashesListPopup::setup(ArrayListNode* node) {
    this->setZOrder(150);

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
    addBtn->setPositionX(155.f);
    addBtn->setPositionY(-130.f);

    auto deleteAllBtn_spr = ButtonSprite::create("Remove All", 0, false, "goldFont.fnt", "GJ_button_05.png", 30.f, 0.7f);
    deleteAllBtn_spr->setScale(0.7);
    auto deleteAllBtn = CCMenuItemSpriteExtra::create(
        deleteAllBtn_spr,
        this,
        menu_selector(SplashesListPopup::deleteAllSplashes)
    );
    deleteAllBtn->setPositionX(-155.f);
    deleteAllBtn->setPositionY(-130.f);

    this->m_buttonMenu->addChild(addBtn);
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
            } 
        }
    );
}

void SplashesListPopup::setupSplashesList(float pos_x, float pos_y, float scale_x, float scale_y) {
    auto item_arr = CCArray::create();

    auto splash_array = this->m_node->getValue();

    for(int i = 0;i < splash_array.size();i++) {
        auto item_menu = CCMenu::create();
        item_menu->setPosition({scale_x - 40, 40.f / 2.f});
        item_menu->setContentWidth(73);
        item_menu->setLayout(RowLayout::create()->setAutoScale(false), false);

        auto splash = CCLabelBMFont::create(splash_array.at(i).at(0).c_str(), "bigFont.fnt");
        splash->setScale(0.5f);
        splash->setAnchorPoint({0.f, 0.5f});
        splash->setPosition({5.f, 20.f});
        splash->limitLabelWidth(scale_x - 86.f, 0.5f, 0.2f);

        auto delete_spr = CCSprite::createWithSpriteFrameName("GJ_trashBtn_001.png");
        auto delete_btn = CCMenuItemSpriteExtra::create(
            delete_spr,
            this,
            menu_selector(SplashesListPopup::deleteEntry)
        );

        delete_btn->m_baseScale = 0.8f;
        delete_btn->setID(fmt::format("{}", i).c_str());
        delete_btn->setScale(0.8f);

        auto edit_spr = CCSprite::create("editBtn_001.png"_spr);
        auto edit_btn = CCMenuItemSpriteExtra::create(
            edit_spr,
            this,
            menu_selector(SplashesListPopup::editEntry)
        );

        edit_btn->m_baseScale = 0.8f;
        edit_btn->setID(fmt::format("{}", i).c_str());
        edit_btn->setScale(0.8f);

        item_menu->addChild(edit_btn);
        item_menu->addChild(delete_btn);

        auto item_node = CCNode::create();

        item_node->addChild(splash);
        item_node->addChild(item_menu);
        item_arr->addObject(item_node);
        item_menu->updateLayout();
    }

    auto splash_list_bg = CCLayerColor::create();
    splash_list_bg->setOpacity(75);
    splash_list_bg->setZOrder(-1);
    splash_list_bg->setContentSize(ccp(scale_x, scale_y));

    auto list = ListView::create(item_arr, 40.f, scale_x, scale_y);
    list->setPosition({pos_x - (scale_x / 2), pos_y - (scale_y / 2)});
    list->setID("list");

    auto splash_list_round_top = CCScale9Sprite::createWithSpriteFrameName("GJ_commentTop_001.png");
    splash_list_round_top->setContentSize(ccp(scale_x + 12.f, 22.f));
    splash_list_round_top->setPosition({scale_x / 2, scale_y - 5});

    auto splash_list_round_down = CCScale9Sprite::createWithSpriteFrameName("GJ_commentTop_001.png");
    splash_list_round_down->setContentSize(ccp(scale_x + 12.f, 22.f));
    splash_list_round_down->setPosition({scale_x / 2, 5});
    splash_list_round_down->setRotation(180);

    auto splash_list_round_left = CCScale9Sprite::createWithSpriteFrameName("GJ_commentSide_001.png");
    splash_list_round_left->setContentSize(ccp(22.f, scale_y - 30.f));
    splash_list_round_left->setPosition({-9.7f, scale_y / 2});

    auto splash_list_round_right = CCScale9Sprite::createWithSpriteFrameName("GJ_commentSide_001.png");
    splash_list_round_right->setContentSize(ccp(22.f, scale_y - 30.f));
    splash_list_round_right->setPosition({scale_x + 9.7f, scale_y / 2});
    splash_list_round_right->setRotation(180);
    
    list->addChild(splash_list_bg);
    list->addChild(splash_list_round_top);
    list->addChild(splash_list_round_down);
    list->addChild(splash_list_round_left);
    list->addChild(splash_list_round_right);
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
            }
        }
    );
}