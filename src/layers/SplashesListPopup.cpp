#include "SplashesListPopup.h"
#include "EditEntriesLayer.h"
#include "Geode/binding/CCMenuItemSpriteExtra.hpp"
#include "Geode/cocos/actions/CCActionInterval.h"
#include "Geode/cocos/cocoa/CCObject.h"
#include "Geode/cocos/label_nodes/CCLabelBMFont.h"
#include "Geode/ui/BasedButtonSprite.hpp"
#include "Geode/utils/cocos.hpp"
#include <string>

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
                size_t   size = v.size();
                v.erase(v.begin() + index);
                this->m_node->setValue(v);
                
                getChildOfType<CCLabelBMFont>(this->m_scrollLayer->m_contentLayer->getChildByID(std::to_string(index).c_str()), 0)->runAction(CCSequence::create(
                    CCFadeOut::create(0.4),
                    nullptr
                ));
                auto menu = getChildOfType<CCMenu>(this->m_scrollLayer->m_contentLayer->getChildByID(std::to_string(index).c_str()), 0);
                auto edit_button = static_cast<CCMenuItemSpriteExtra*>(menu->getChildren()->objectAtIndex(0));
                edit_button->m_bEnabled = false;
                edit_button->runAction(CCFadeOut::create(0.4));
                static_cast<CCLabelBMFont*>(static_cast<CircleButtonSprite*>(edit_button->getChildren()->objectAtIndex(0))->getChildren()->objectAtIndex(0))->runAction(CCFadeOut::create(0.4));
                auto delete_button = static_cast<CCMenuItemSpriteExtra*>(menu->getChildren()->objectAtIndex(1));
                delete_button->m_bEnabled = false;
                delete_button->runAction(CCFadeOut::create(0.4));
                static_cast<CCNode*>(this->m_scrollLayer->m_contentLayer->getChildByID(std::to_string(index).c_str()))->runAction(CCSequence::create(
                    CCDelayTime::create(0.4),
                    CCCallFuncN::create(static_cast<CCNode*>(this->m_scrollLayer->m_contentLayer->getChildByID(std::to_string(index).c_str())), callfuncN_selector(SplashesListPopup::destroyNode)),
                    nullptr
                ));
                if (index == 0) {
                    m_scrollLayer->m_contentLayer->changeHeight((m_scrollLayer->m_contentLayer->getContentHeight() - 40.f < m_scrollLayer->getContentHeight()) ? m_scrollLayer->m_contentLayer->getContentHeight() : m_scrollLayer->m_contentLayer->getContentHeight() - 40);
                    if(m_scrollLayer->m_contentLayer->getPositionY() < -40 && m_scrollLayer->m_contentLayer->getContentHeight() - 40.f > m_scrollLayer->getContentHeight()) {
                        m_scrollLayer->m_contentLayer->runAction(CCSequence::create(
                            CCDelayTime::create(0.4),
                            CCMoveBy::create(0.3, CCPoint(0, 40)),
                            nullptr
                        ));
                    } else {
                        for(int i = index + 1; i < size; i++) {
                            auto node = static_cast<CCNode*>(this->m_scrollLayer->m_contentLayer->getChildByID(std::to_string(i).c_str()));
                            node->runAction(CCSequence::create(
                                CCDelayTime::create(0.4),
                                CCMoveBy::create(0.3, CCPoint(0, 40)),
                                nullptr
                            ));
                        }
                    }
                } else if (index > 0) {
                    if(m_scrollLayer->m_contentLayer->getContentHeight() - 40.f > m_scrollLayer->getContentHeight()) {
                        for(int i = index - 1; i >= 0; i--) {
                            auto node = static_cast<CCNode*>(this->m_scrollLayer->m_contentLayer->getChildByID(std::to_string(i).c_str()));
                            node->runAction(CCSequence::create(
                                CCDelayTime::create(0.4),
                                CCMoveBy::create(0.3, CCPoint(0, -40)),
                                nullptr
                            ));
                        }
                        if(m_scrollLayer->m_contentLayer->getPositionY() < -40) {
                            m_scrollLayer->m_contentLayer->runAction(CCSequence::create(
                                CCDelayTime::create(0.4),
                                CCMoveBy::create(0.3, CCPoint(0, 40)),
                                nullptr
                            ));
                        }
                    } else {
                        for(int i = index + 1; i < size; i++) {
                            auto node = static_cast<CCNode*>(this->m_scrollLayer->m_contentLayer->getChildByID(std::to_string(i).c_str()));
                            node->runAction(CCSequence::create(
                                CCDelayTime::create(0.4),
                                CCMoveBy::create(0.3, CCPoint(0, 40)),
                                nullptr
                            ));
                        }
                    }
                    m_scrollLayer->m_contentLayer->changeHeight((m_scrollLayer->m_contentLayer->getContentHeight() - 40.f < m_scrollLayer->getContentHeight()) ? m_scrollLayer->m_contentLayer->getContentHeight() : m_scrollLayer->m_contentLayer->getContentHeight() - 40);
                }
                
                for(size_t i = index + 1; i < size; i++) {
                    auto node = static_cast<CCNode*>(this->m_scrollLayer->m_contentLayer->getChildByID(std::to_string(i).c_str()));
                    static_cast<CCMenuItemSpriteExtra*>(getChildOfType<CCMenu>(node, 0)->getChildren()->objectAtIndex(0))->setID(std::to_string(std::stoi(static_cast<CCMenuItemSpriteExtra*>(getChildOfType<CCMenu>(node, 0)->getChildren()->objectAtIndex(0))->getID()) - 1).c_str());
                    static_cast<CCMenuItemSpriteExtra*>(getChildOfType<CCMenu>(node, 0)->getChildren()->objectAtIndex(1))->setID(std::to_string(std::stoi(static_cast<CCMenuItemSpriteExtra*>(getChildOfType<CCMenu>(node, 0)->getChildren()->objectAtIndex(1))->getID()) - 1).c_str());
                    node->setID(std::to_string(std::stoi(node->getID()) - 1).c_str());
                }
                //this->updateSplashesList(offset.x, offset.y, 320, 225);
                this->m_node->dispatchChangedPublic();
                this->checkForChanges();
            } 
        }
    );
}

void SplashesListPopup::destroyNode(CCNode* node) {
    node->removeMeAndCleanup();
}

void SplashesListPopup::setupSplashesList(float pos_x, float pos_y, float scale_x, float scale_y) {
    auto splash_array = this->m_node->getValue();
    this->m_startSize = splash_array.size();
    m_scrollLayer = ScrollLayer::create({scale_x, scale_y});
    this->m_isEven = ((splash_array.size() - 1) * 40.f > this->m_scrollLayer->getContentHeight()) ? splash_array.size() % 2 == 0 : true;
    m_scrollLayer->setID("scroll-layer");
    float size = 40.f * splash_array.size();
    m_scrollLayer->m_contentLayer->changeHeight((size >= scale_y) ? size : std::ceil(scale_y / 40.f) * 40);
    m_scrollLayer->scrollToTop();
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
        deleteBtn->setID(std::to_string(i).c_str());
        auto editSprText = CCLabelBMFont::create("Edit", "bigFont.fnt");
        auto editSpr = CircleButtonSprite::create(editSprText, CircleBaseColor::Pink);
        editSpr->setScale(0.7f);
        auto editBtn = CCMenuItemSpriteExtra::create(
            editSpr,
            this,
            menu_selector(SplashesListPopup::editEntry)
        );
        editBtn->setID(std::to_string(i).c_str());
        itemMenu->addChild(editBtn);
        itemMenu->addChild(deleteBtn);
        auto itemNode = CCNode::create();
        itemNode->setContentSize(ccp(scale_x, 40));
        itemNode->setID(std::to_string(i).c_str());
        if(i % 2 == 0) {
            auto bg = CCLayerColor::create();
            bg->setOpacity(50);
            bg->setID("col-" + std::to_string(i));
            bg->setContentSize(ccp(scale_x, 40));
            bg->setPositionY(m_scrollLayer->m_contentLayer->getContentHeight() - (40 * (i + 1)));
            m_scrollLayer->m_contentLayer->addChild(bg);
        }
        itemNode->addChild(splash);
        itemNode->addChild(itemMenu);
        itemNode->setZOrder(1);
        itemNode->setPositionY(m_scrollLayer->m_contentLayer->getContentHeight() - (40 * (i + 1)));
        itemMenu->updateLayout();
        m_scrollLayer->m_contentLayer->addChild(itemNode);
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
    splashListBg->addChild(m_scrollLayer);
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