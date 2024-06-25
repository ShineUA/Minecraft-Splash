#include "./EditSplashAppearanceLayer.h"
#include "Geode/binding/MenuGameLayer.hpp"
#include "Geode/cocos/CCDirector.h"
#include "Geode/cocos/actions/CCActionInstant.h"
#include "Geode/cocos/actions/CCActionInterval.h"
#include "Geode/cocos/cocoa/CCObject.h"
#include "Geode/cocos/menu_nodes/CCMenu.h"
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
    auto bg = CCSprite::create("game_bg_01_001.png");
    bg->setScale(CCDirector::sharedDirector()->getWinSizeInPixels().width / bg->getTexture()->getContentSizeInPixels().width);
    bg->setContentWidth(1024);
    bg->setTextureRect(CCRect(0, 0, 1024, 512));
    bg->setPosition((bg->getContentSize() / 2) * (CCDirector::sharedDirector()->getWinSizeInPixels().width / bg->getTexture()->getContentSizeInPixels().width));
    bg->setColor({0, 255, 255});
    bg->setID("bg-1");
    bg->runAction(CCRepeatForever::create(CCSequence::create(
        CCTintTo::create(2.5, 255, 0, 255),
        CCDelayTime::create(0.5),
        CCTintTo::create(2.5, 255, 255, 0),
        CCDelayTime::create(0.5),
        CCTintTo::create(2.5, 0, 255, 255),
        CCDelayTime::create(0.5),
        nullptr
    )));
    bg->runAction(CCRepeatForever::create(CCSequence::create(
        CCMoveBy::create(15, {-bg->getContentWidth() / 2 * (CCDirector::sharedDirector()->getWinSizeInPixels().width / bg->getTexture()->getContentSizeInPixels().width), 0}),
        CCMoveBy::create(0, {bg->getContentWidth() / 2 * (CCDirector::sharedDirector()->getWinSizeInPixels().width / bg->getTexture()->getContentSizeInPixels().width), 0}),
        nullptr
    )));
    
    this->addChild(bg);
    return true;
}

void EditSplashAppearanceLayer::bgLoop(CCNode* node) {
    node->runAction(CCRepeatForever::create(CCSequence::create(
        CCMoveBy::create(0, {node->getContentWidth() * 3, 0}),
        CCMoveBy::create(15 * 3, {-node->getContentWidth() * 3, 0}),
        nullptr
    )));
}
