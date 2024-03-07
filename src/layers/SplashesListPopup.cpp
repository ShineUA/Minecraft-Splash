#include "SplashesListPopup.h"
#include <fmt/format.h>
#include "EntriesLayer.h"

SplashesListPopup* SplashesListPopup::create(ArrayListValue* save_value) {
    SplashesListPopup* ret = new SplashesListPopup();
    if (ret && ret->init(save_value)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool SplashesListPopup::init(ArrayListValue* save_value) {
    if (!this->initWithColor({0, 0, 0, 75})) return false;

    this->m_local_value = save_value;

    this->m_noElasticity = true;
    geode::cocos::handleTouchPriority(this);
    this->registerWithTouchDispatcher();
    this->setTouchEnabled(true);
    this->setKeypadEnabled(true);
    this->setZOrder(125);

    auto layer = CCLayer::create();
    auto menu = CCMenu::create();
    this->m_mainLayer = layer;
    this->m_buttonMenu = menu;
    
    this->addChild(layer);

    const float width = 375, height = 250;

    auto* director = CCDirector::sharedDirector();

    const CCPoint offset = director->getWinSize() / 2.f;

    auto bg = extension::CCScale9Sprite::create("GJ_square01.png");
    bg->setContentSize({width, height});
    bg->setPosition(offset);
    menu->setPosition(offset);
    bg->setZOrder(-2);
    layer->addChild(bg);

    auto closeBtn_spr = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
    auto closeBtn = CCMenuItemSpriteExtra::create(
        closeBtn_spr,
        this,
        menu_selector(SplashesListPopup::onCloseBtn)
    );

    closeBtn->setPosition({-186.f, 124.f});

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

    auto splash_list_round_down = CCScale9Sprite::createWithSpriteFrameName("GJ_commentTop_001.png");
    splash_list_round_down->setContentSize(ccp(320.f, 22.f));
    splash_list_round_down->setPosition({offset.x, offset.y - 95.f});
    splash_list_round_down->setRotation(180);

    auto splash_list_round_left = CCScale9Sprite::createWithSpriteFrameName("GJ_commentSide_001.png");
    splash_list_round_left->setContentSize(ccp(22.f, 170.f));
    splash_list_round_left->setPosition({offset.x - 163.7f, offset.y});

    auto splash_list_round_right = CCScale9Sprite::createWithSpriteFrameName("GJ_commentSide_001.png");
    splash_list_round_right->setContentSize(ccp(22.f, 170.f));
    splash_list_round_right->setPosition({offset.x + 163.7f, offset.y});
    splash_list_round_right->setRotation(180);

    this->m_local_list = ListView::create(item_arr, 40.f, 308.f, 200.f);
    this->m_local_list->setPosition({offset.x - 154.f, offset.y - 100.f});

    auto splash_list_bg = CCLayerColor::create();
    splash_list_bg->setOpacity(75);
    splash_list_bg->setContentSize(ccp(308.f, 200.f));
    splash_list_bg->setPosition(this->m_local_list->getPosition());

    auto addBtn_spr = CCSprite::createWithSpriteFrameName("GJ_plusBtn_001.png");
    auto addBtn = CCMenuItemSpriteExtra::create(
        addBtn_spr,
        this,
        menu_selector(SplashesListPopup::addEntry)
    );
    
    addBtn->setPositionX(169.f);
    addBtn->setScale(0.525f);
    addBtn->m_baseScale = 0.525f;

    layer->addChild(splash_list_bg);
    layer->addChild(m_local_list);
    layer->addChild(splash_list_round_top);
    layer->addChild(splash_list_round_down);
    layer->addChild(splash_list_round_left);
    layer->addChild(splash_list_round_right);

    menu->addChild(closeBtn);
    menu->addChild(addBtn);

    layer->addChild(menu);

    return true;
}

void SplashesListPopup::addEntry(CCObject* sender) {
    auto node = EntriesLayer::create(this->m_local_value, 0);
    CCScene::get()->addChild(node);
    this->keyBackClicked();
}

void SplashesListPopup::editEntry(CCObject* sender) {
    auto node = EntriesLayer::create(this->m_local_value, std::stoi(static_cast<CCMenuItemSpriteExtra*>(sender)->getID()), 1);
    CCScene::get()->addChild(node);
    this->keyBackClicked();
}

void SplashesListPopup::deleteEntry(CCObject* sender) {
    if(this->m_local_value->getArray().size() <= 1) {
        FLAlertLayer::create(
            "Error",
            "There's must be at least one splash!",
            "OK"
        )->show();
        return;
    }
    auto node = EntriesLayer::create(this->m_local_value, std::stoi(static_cast<CCMenuItemSpriteExtra*>(sender)->getID()), 2);
    CCScene::get()->addChild(node);
    this->keyBackClicked();
}

void SplashesListPopup::keyBackClicked() {
    this->setTouchEnabled(false);
    this->setKeypadEnabled(false);
    this->removeFromParentAndCleanup(true);
}

void SplashesListPopup::onCloseBtn(CCObject* sender) {
    this->keyBackClicked();
}