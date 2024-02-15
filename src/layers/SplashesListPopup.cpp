#include "SplashesListPopup.h"

SplashesListPopup* SplashesListPopup::create(std::vector<std::vector<std::string>> objects) {
    SplashesListPopup* ret = new SplashesListPopup();
    if (ret && ret->init(objects)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool SplashesListPopup::init(std::vector<std::vector<std::string>> objects) {
    if (!this->initWithColor({0, 0, 0, 75})) return false;

    this->m_noElasticity = true;
    geode::cocos::handleTouchPriority(this);
    this->registerWithTouchDispatcher();
    this->setTouchEnabled(true);
    this->setKeypadEnabled(true);
    this->setZOrder(150);

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

    auto last_arr = CCArray::create();

    std::stringstream ss;

    for(int i = 0;i < objects.size();i++) {
        auto item_menu = CCMenu::create();

        auto splash = CCLabelBMFont::create(objects.at(i).at(0).c_str(), "bigFont.fnt");
        splash->setScale(0.4f);
        splash->setAnchorPoint({0.f, 0.5f});
        splash->setPosition({5.f, 10.f});

        auto delete_spr = CCSprite::createWithSpriteFrameName("GJ_trashBtn_001.png");
        auto delete_btn = CCMenuItemSpriteExtra::create(
            delete_spr,
            this,
            nullptr
        );

        ss << i;

        delete_btn->m_baseScale = 0.4f;
        delete_btn->setID(ss.str());
        delete_btn->setScale(0.4f);
        delete_btn->setPosition({11.f, -150.f});

        auto edit_spr = CCSprite::create("editBtn_001.png"_spr);
        auto edit_btn = CCMenuItemSpriteExtra::create(
            edit_spr,
            this,
            nullptr
        );

        edit_btn->m_baseScale = 0.4f;
        edit_btn->setID(ss.str());
        edit_btn->setScale(0.4f);
        edit_btn->setPosition({-9.f, -150.f});

        item_menu->addChild(edit_btn);
        item_menu->addChild(delete_btn);

        auto item_node = CCNode::create();

        item_node->addChild(splash);
        item_node->addChild(item_menu);
        last_arr->addObject(item_node);
        ss.str("");
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

    auto splash_list = ListView::create(last_arr, 20.f, 308.f, 200.f);
    splash_list->setPosition({130.5f, 60.f});

    auto splash_list_bg = CCLayerColor::create();
    splash_list_bg->setOpacity(75);
    splash_list_bg->setContentSize(ccp(308.f, 200.f));
    splash_list_bg->setPosition(splash_list->getPosition());

    auto addBtn_spr = CCSprite::createWithSpriteFrameName("GJ_plusBtn_001.png");
    auto addBtn = CCMenuItemSpriteExtra::create(
        addBtn_spr,
        this,
        nullptr
    );
    
    addBtn->setPositionX(169.f);
    addBtn->setScale(0.5f);
    addBtn->m_baseScale = 0.5f;

    layer->addChild(splash_list_bg);
    layer->addChild(splash_list);
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

}

void SplashesListPopup::editEntry(CCObject* sender) {

}

void SplashesListPopup::deleteEntry(CCObject* sender) {

}

void SplashesListPopup::keyBackClicked() {
    this->setTouchEnabled(false);
    this->setKeypadEnabled(false);
    this->removeFromParentAndCleanup(true);
}

void SplashesListPopup::onCloseBtn(CCObject* sender) {
    this->keyBackClicked();
}