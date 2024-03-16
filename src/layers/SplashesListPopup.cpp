#include "SplashesListPopup.h"
#include <fmt/format.h>
#include "EntriesLayer.h"

SplashesListPopup* SplashesListPopup::create(ArrayListValue* save_value) {
    SplashesListPopup* ret = new SplashesListPopup();
    if (ret && ret->init(375.f, 250.f, save_value)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool SplashesListPopup::setup(ArrayListValue* save_value) {
    this->setZOrder(150);
    this->m_local_value = save_value;

    auto item_arr = CCArray::create();

    this->setupSplashesList();

    auto addBtn_spr = CCSprite::createWithSpriteFrameName("GJ_plusBtn_001.png");
    auto addBtn = CCMenuItemSpriteExtra::create(
        addBtn_spr,
        this,
        menu_selector(SplashesListPopup::addEntry)
    );
    
    addBtn->setPositionX(169.f);
    addBtn->setScale(0.525f);
    addBtn->m_baseScale = 0.525f;

    this->m_buttonMenu->addChild(addBtn);
    return true;
}

void SplashesListPopup::addEntry(CCObject* sender) {
    auto node = EntriesLayer::create(this->m_local_value, 0, 0, this);
    CCScene::get()->addChild(node);
}

void SplashesListPopup::editEntry(CCObject* sender) {
    auto node = EntriesLayer::create(this->m_local_value, std::stoi(static_cast<CCMenuItemSpriteExtra*>(sender)->getID()), 1, this);
    CCScene::get()->addChild(node);
}

void SplashesListPopup::deleteEntry(CCObject* sender) {
    if(this->m_local_value->getArray().size() <= 1) {
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
                std::vector<std::vector<std::string>> v = this->m_local_value->getArray();
                v.erase(v.begin() + index);
                this->m_local_value->setArray(v);
                auto am_of_spl = v.size();
                if(am_of_spl == 1) {
                    random_splash = 0;
                } else {
                    std::random_device rd; 
                    std::mt19937 gen(rd()); 
                    std::uniform_int_distribution<std::mt19937::result_type> distr(0, am_of_spl - 1); 
                    random_splash = distr(gen);
                }
                Mod::get()->setSavedValue<std::vector<std::vector<std::string>>>("splashes-vector", v);
                this->updateSplashesList();
            } 
        }
    );
}

void SplashesListPopup::setupSplashesList() {
    auto item_arr = CCArray::create();

    auto splash_array = m_local_value->getArray();

    for(int i = 0;i < splash_array.size();i++) {
        auto item_menu = CCMenu::create();
        item_menu->setPosition({308.f / 2.f + 111.f, 40.f / 2.f});
        item_menu->setContentWidth(73);
        item_menu->setLayout(RowLayout::create()->setAutoScale(false), false);

        auto splash = CCLabelBMFont::create(splash_array.at(i).at(0).c_str(), "bigFont.fnt");
        splash->setScale(0.5f);
        splash->setAnchorPoint({0.f, 0.5f});
        splash->setPosition({5.f, 20.f});
        splash->limitLabelWidth(222.f, 0.5f, 0.2f);

        auto delete_spr = CCSprite::createWithSpriteFrameName("GJ_trashBtn_001.png");
        auto delete_btn = CCMenuItemSpriteExtra::create(
            delete_spr,
            this,
            menu_selector(SplashesListPopup::deleteEntry)
        );

        delete_btn->m_baseScale = 0.8f;
        delete_btn->setID(fmt::format("{}", i).c_str());
        delete_btn->setScale(0.8f);
        // delete_btn->setPosition({offset.x - 273.f, offset.y - 310.f});

        auto edit_spr = CCSprite::create("editBtn_001.png"_spr);
        auto edit_btn = CCMenuItemSpriteExtra::create(
            edit_spr,
            this,
            menu_selector(SplashesListPopup::editEntry)
        );

        edit_btn->m_baseScale = 0.8f;
        edit_btn->setID(fmt::format("{}", i).c_str());
        edit_btn->setScale(0.8f);
        // edit_btn->setPosition({offset.x - 293.f, offset.y -310.f});

        item_menu->addChild(edit_btn);
        item_menu->addChild(delete_btn);

        auto item_node = CCNode::create();

        item_node->addChild(splash);
        item_node->addChild(item_menu);
        item_arr->addObject(item_node);
        item_menu->updateLayout();
    }

    auto splash_list_round_top = CCScale9Sprite::createWithSpriteFrameName("GJ_commentTop_001.png");
    splash_list_round_top->setContentSize(ccp(320.f, 22.f));
    splash_list_round_top->setPosition({offset.x, offset.y + 95.f});
    splash_list_round_top->setID("list-top");

    auto splash_list_round_down = CCScale9Sprite::createWithSpriteFrameName("GJ_commentTop_001.png");
    splash_list_round_down->setContentSize(ccp(320.f, 22.f));
    splash_list_round_down->setPosition({offset.x, offset.y - 95.f});
    splash_list_round_down->setRotation(180);
    splash_list_round_down->setID("list-down");

    auto splash_list_round_left = CCScale9Sprite::createWithSpriteFrameName("GJ_commentSide_001.png");
    splash_list_round_left->setContentSize(ccp(22.f, 170.f));
    splash_list_round_left->setPosition({offset.x - 163.7f, offset.y});
    splash_list_round_left->setID("list-left");

    auto splash_list_round_right = CCScale9Sprite::createWithSpriteFrameName("GJ_commentSide_001.png");
    splash_list_round_right->setContentSize(ccp(22.f, 170.f));
    splash_list_round_right->setPosition({offset.x + 163.7f, offset.y});
    splash_list_round_right->setRotation(180);
    splash_list_round_right->setID("list-right");

    auto list = ListView::create(item_arr, 40.f, 308.f, 200.f);
    list->setPosition({offset.x - 154.f, offset.y - 100.f});
    list->setID("list");

    auto splash_list_bg = CCLayerColor::create();
    splash_list_bg->setOpacity(75);
    splash_list_bg->setContentSize(ccp(308.f, 200.f));
    splash_list_bg->setPosition(list->getPosition());
    splash_list_bg->setID("list-bg");

    this->m_mainLayer->addChild(splash_list_bg);
    this->m_mainLayer->addChild(list);
    this->m_mainLayer->addChild(splash_list_round_top);
    this->m_mainLayer->addChild(splash_list_round_down);
    this->m_mainLayer->addChild(splash_list_round_left);
    this->m_mainLayer->addChild(splash_list_round_right);
}

void SplashesListPopup::updateSplashesList() {
    this->m_mainLayer->getChildByID("list")->removeFromParentAndCleanup(true);
    this->m_mainLayer->getChildByID("list-bg")->removeFromParentAndCleanup(true);
    this->m_mainLayer->getChildByID("list-top")->removeFromParentAndCleanup(true);
    this->m_mainLayer->getChildByID("list-down")->removeFromParentAndCleanup(true);
    this->m_mainLayer->getChildByID("list-left")->removeFromParentAndCleanup(true);
    this->m_mainLayer->getChildByID("list-right")->removeFromParentAndCleanup(true);
    this->setupSplashesList();
}