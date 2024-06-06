#include "SplashesListPopup.h"
#include "EditEntriesLayer.h"

extern std::vector<std::vector<std::string>> default_splashes;

SplashesListPopup* SplashesListPopup::create(ArrayListNode* node) {
    SplashesListPopup* ret = new SplashesListPopup();
    if (ret && ret->initAnchored(435.f, 300.f, node, Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? "geode.loader/GE_square01.png" : "GJ_square01.png")) {
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
    if(Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme")) this->m_closeBtn->setSprite(CircleButtonSprite::createWithSpriteFrameName("geode.loader/close.png", 0.85f, CircleBaseColor::DarkPurple));
    else this->m_closeBtn->setSprite(CircleButtonSprite::createWithSpriteFrameName("geode.loader/close.png", 0.85f, CircleBaseColor::Green));
    auto item_arr = CCArray::create();
    this->setupSplashesList(offset.x, offset.y, 320, 225);
    auto addBtn_spr = ButtonSprite::create("Add Splash", 0, false, "goldFont.fnt", Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? "geode.loader/GE_button_05.png" : "GJ_button_01.png", 30.f, 0.7f);
    addBtn_spr->setScale(0.7);
    auto addBtn = CCMenuItemSpriteExtra::create(
        addBtn_spr,
        this,
        menu_selector(SplashesListPopup::addEntry)
    );
    addBtn->setPosition({offset.x + 165.f, offset.y + -130.f});
    auto deleteAllBtn_spr = ButtonSprite::create("Remove All", 0, false, "goldFont.fnt", Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? "geode.loader/GE_button_05.png" : "GJ_button_01.png", 30.f, 0.7f);
    deleteAllBtn_spr->setScale(0.7);
    auto deleteAllBtn = CCMenuItemSpriteExtra::create(
        deleteAllBtn_spr,
        this,
        menu_selector(SplashesListPopup::deleteAllSplashes)
    );
    deleteAllBtn->setPosition({offset.x + -165.f, offset.y + -130.f});
    auto resetBtn_spr = ButtonSprite::create("Reset", 0, false, "goldFont.fnt", Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? "geode.loader/GE_button_05.png" : "GJ_button_01.png", 30.f, 0.7f);
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
    auto splash_array = this->m_node->getValue();
    auto scrollLayer = ScrollLayer::create({scale_x, scale_y});
    scrollLayer->m_contentLayer->changeHeight(40.f * splash_array.size());
    scrollLayer->scrollToTop();
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
        auto itemNode = CCNode::create();
        itemNode->setContentSize(ccp(scale_x, 40));
        if(i % 2 == 0) {
            auto bg = CCLayerColor::create();
            bg->setOpacity(50);
            bg->setContentSize(ccp(scale_x, 40));
            itemNode->addChild(bg);
        }
        itemNode->addChild(splash);
        itemNode->addChild(itemMenu);
        itemNode->setPositionY((splash_array.size() - i) * 40.f - 40.f);
        itemMenu->updateLayout();
        scrollLayer->m_contentLayer->addChild(itemNode);
    }
    auto splashListBg = CCLayerColor::create();
    splashListBg->setOpacity(75);
    splashListBg->setID("list");
    splashListBg->setContentSize(ccp(scale_x, scale_y));
    splashListBg->setPosition({pos_x - scale_x / 2, pos_y - scale_y / 2});
    auto splashListBorderTop = CCScale9Sprite::createWithSpriteFrameName(Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? "geode.loader/geode-list-top.png" : "GJ_commentTop_001.png");
    splashListBorderTop->setContentSize(ccp(Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? scale_x + 1.f : scale_x + 12.f, Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? 17.f : 22.f));
    splashListBorderTop->setPosition({scale_x / 2, scale_y - 7});
    auto splashListBorderDown = CCScale9Sprite::createWithSpriteFrameName(Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? "geode.loader/geode-list-top.png" : "GJ_commentTop_001.png");
    splashListBorderDown->setContentSize(ccp(Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? scale_x + 1.f : scale_x + 12.f, Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? 18.f : 22.f));
    splashListBorderDown->setPosition({scale_x / 2, 7});
    splashListBorderDown->setRotation(180);
    auto splashListBorderLeft = CCScale9Sprite::createWithSpriteFrameName(Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? "geode.loader/geode-list-side.png" : "GJ_commentSide_001.png");
    splashListBorderLeft->setContentSize(ccp(Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? 1.985f : 22.f, scale_y - 30.f));
    splashListBorderLeft->setPosition({Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? 0.385f : -9.7f, scale_y / 2});
    auto splashListBorderRight = CCScale9Sprite::createWithSpriteFrameName(Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? "geode.loader/geode-list-side.png" : "GJ_commentSide_001.png");
    splashListBorderRight->setContentSize(ccp(Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? 1.985f : 22.f, scale_y - 30.f));
    splashListBorderRight->setPosition({Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? scale_x + -0.385f : scale_x + 9.7f, scale_y / 2});
    splashListBorderRight->setRotation(180);
    splashListBg->addChild(scrollLayer);
    splashListBg->addChild(splashListBorderTop);
    splashListBg->addChild(splashListBorderDown);
    splashListBg->addChild(splashListBorderLeft);
    splashListBg->addChild(splashListBorderRight);
    this->m_mainLayer->addChild(splashListBg);
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
                std::vector<std::vector<std::string>> v = {{"Splash", "0.6"}};
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