#include "./EditSplashAppearanceLayer.h"
#include "Geode/binding/GameManager.hpp"
#include "Geode/binding/MenuGameLayer.hpp"
#include "Geode/cocos/CCDirector.h"
#include "Geode/cocos/actions/CCActionInstant.h"
#include "Geode/cocos/actions/CCActionInterval.h"
#include "Geode/cocos/cocoa/CCObject.h"
#include "Geode/cocos/menu_nodes/CCMenu.h"
#include "Geode/cocos/sprite_nodes/CCSpriteBatchNode.h"
#include "Geode/cocos/sprite_nodes/CCSpriteFrameCache.h"
#include "ccTypes.h"

void EditSplashAppearanceLayer::keyBackClicked() {
    CCDirector::sharedDirector()->popSceneWithTransition(0.5, PopTransition::kPopTransitionFade);
}

EditSplashAppearanceLayer* EditSplashAppearanceLayer::scene() {
    auto ret = new EditSplashAppearanceLayer();
    if(ret && ret->init()) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
        ret = nullptr;
    }
    return ret;
}

bool EditSplashAppearanceLayer::init() {
    if(!CCLayer::init()) return false;
    this->setContentSize(CCDirector::sharedDirector()->getWinSize());
    this->setKeypadEnabled(true);
    this->setTouchEnabled(true);
    auto bg = CCSpriteBatchNode::create((GameManager::get()->m_loadedBgID < 10) ? fmt::format("game_bg_0{}_001.png", GameManager::get()->m_loadedBgID).c_str() : fmt::format("game_bg_{}_001.png", GameManager::get()->m_loadedBgID).c_str());
    auto bg_1 = CCSprite::create((GameManager::get()->m_loadedBgID < 10) ? fmt::format("game_bg_0{}_001.png", GameManager::get()->m_loadedBgID).c_str() : fmt::format("game_bg_{}_001.png", GameManager::get()->m_loadedBgID).c_str());
    bg_1->setScale(CCDirector::sharedDirector()->getWinSizeInPixels().width / bg_1->getTexture()->getContentSizeInPixels().width);
    bg_1->setPosition((bg_1->getContentSize() / 2) * (CCDirector::sharedDirector()->getWinSizeInPixels().width / bg_1->getTexture()->getContentSizeInPixels().width));
    bg_1->setColor({0, 255, 255});
    bg_1->setID("bg-1");
    bg_1->runAction(CCRepeatForever::create(CCSequence::create(
        CCTintTo::create(2.5, 255, 0, 255),
        CCDelayTime::create(0.5),
        CCTintTo::create(2.5, 255, 255, 0),
        CCDelayTime::create(0.5),
        CCTintTo::create(2.5, 0, 255, 255),
        CCDelayTime::create(0.5),
        nullptr
    )));
    bg->addChild(bg_1);
    auto bg_2 = CCSprite::create((GameManager::get()->m_loadedBgID < 10) ? fmt::format("game_bg_0{}_001.png", GameManager::get()->m_loadedBgID).c_str() : fmt::format("game_bg_{}_001.png", GameManager::get()->m_loadedBgID).c_str());
    bg_2->setScale(CCDirector::sharedDirector()->getWinSizeInPixels().width / bg_2->getTexture()->getContentSizeInPixels().width);
    bg_2->setPositionX((bg_2->getContentWidth() / 2) * (CCDirector::sharedDirector()->getWinSizeInPixels().width / bg_2->getTexture()->getContentSizeInPixels().width) * 3);
    bg_2->setPositionY((bg_2->getContentHeight() / 2) * (CCDirector::sharedDirector()->getWinSizeInPixels().width / bg_2->getTexture()->getContentSizeInPixels().width));
    bg_2->setColor({0, 255, 255});
    bg_2->setID("bg-2");
    bg_2->runAction(CCRepeatForever::create(CCSequence::create(
        CCTintTo::create(2.5, 255, 0, 255),
        CCDelayTime::create(0.5),
        CCTintTo::create(2.5, 255, 255, 0),
        CCDelayTime::create(0.5),
        CCTintTo::create(2.5, 0, 255, 255),
        CCDelayTime::create(0.5),
        nullptr
    )));
    bg->addChild(bg_2);
    bg->runAction(CCRepeatForever::create(CCSequence::create(
        CCMoveBy::create(15, {-bg_1->getContentWidth() * (CCDirector::sharedDirector()->getWinSizeInPixels().width / bg_1->getTexture()->getContentSizeInPixels().width), 0}),
        CCMoveBy::create(0, {bg_1->getContentWidth() * (CCDirector::sharedDirector()->getWinSizeInPixels().width / bg_1->getTexture()->getContentSizeInPixels().width), 0}),
        nullptr
    )));
    auto ground = CCSpriteBatchNode::create((GameManager::get()->m_loadedGroundID < 10) ? fmt::format("groundSquare_0{}_001.png", GameManager::get()->m_loadedGroundID).c_str() : fmt::format("groundSquare_{}_001.png", GameManager::get()->m_loadedGroundID).c_str());
    for(int i = 0; i < std::ceil(CCDirector::sharedDirector()->getWinSize().width / 128.f) + 1; i++) {
        auto sprite = CCSprite::create((GameManager::get()->m_loadedGroundID < 10) ? fmt::format("groundSquare_0{}_001.png", GameManager::get()->m_loadedGroundID).c_str() : fmt::format("groundSquare_{}_001.png", GameManager::get()->m_loadedGroundID).c_str());
        sprite->setPosition({(sprite->getContentWidth() / 2) + sprite->getContentWidth() * i, sprite->getContentHeight() / 6});
        sprite->setColor({0, 255, 255});
        sprite->runAction(CCRepeatForever::create(CCSequence::create(
        CCTintTo::create(2.5, 255, 0, 255),
        CCDelayTime::create(0.5),
        CCTintTo::create(2.5, 255, 255, 0),
        CCDelayTime::create(0.5),
        CCTintTo::create(2.5, 0, 255, 255),
        CCDelayTime::create(0.5),
        nullptr
        )));
        ground->addChild(sprite);
    }
    
    ground->runAction(CCRepeatForever::create(CCSequence::create(
        CCMoveBy::create(0.35, {-128, 0}),
        CCMoveBy::create(0, {128, 0}),
        nullptr
    )));
    this->addChild(bg);
    this->addChild(ground);
    return true;
}

void EditSplashAppearanceLayer::bgLoop(CCNode* node) {
    node->runAction(CCRepeatForever::create(CCSequence::create(
        CCMoveBy::create(0, {node->getContentWidth() * 3, 0}),
        CCMoveBy::create(15 * 3, {-node->getContentWidth() * 3, 0}),
        nullptr
    )));
}
