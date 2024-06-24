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
    bg->setPosition(bg->getContentSize() / 2);
    bg->setColor({0, 255, 255});
    bg->setID("bg-1");
    bg->runAction(CCRepeatForever::create(CCSequence::create(
        CCTintTo::create(2.5, 255, 0, 255),
        CCTintTo::create(2.5, 255, 255, 0),
        CCTintTo::create(2.5, 0, 255, 255),
        nullptr
    )));
    auto bg2 = CCSprite::create("game_bg_01_001.png");
    bg2->setPosition({(bg->getContentWidth() / 2) + bg->getContentWidth(), bg->getContentHeight() / 2});
    bg2->setColor({0, 255, 255});
    bg2->setID("bg-2");
    bg2->runAction(CCRepeatForever::create(CCSequence::create(
        CCTintTo::create(2.5, 255, 0, 255),
        CCTintTo::create(2.5, 255, 255, 0),
        CCTintTo::create(2.5, 0, 255, 255),
        nullptr
    )));
    auto bg3 = CCSprite::create("game_bg_01_001.png");
    bg3->setPosition({(bg->getContentWidth() / 2) + bg->getContentWidth() * 2, bg->getContentHeight() / 2});
    bg3->setColor({0, 255, 255});
    bg3->setID("bg-3");
    bg3->runAction(CCRepeatForever::create(CCSequence::create(
        CCTintTo::create(2.5, 255, 0, 255),
        CCTintTo::create(2.5, 255, 255, 0),
        CCTintTo::create(2.5, 0, 255, 255),
        nullptr
    )));
    bg->runAction(CCSequence::create(
        CCMoveBy::create(15, {-bg->getContentWidth(), 0}),
        CCCallFuncN::create(bg, callfuncN_selector(EditSplashAppearanceLayer::bgLoop)),
        nullptr
    ));
    bg2->runAction(CCSequence::create(
        CCMoveBy::create(15 * 2, {-bg2->getContentWidth() * 2, 0}),
        CCCallFuncN::create(bg2, callfuncN_selector(EditSplashAppearanceLayer::bgLoop)),
        nullptr
    ));
    bg3->runAction(CCSequence::create(
        CCMoveBy::create(15 * 3, {-bg2->getContentWidth() * 3, 0}),
        CCCallFuncN::create(bg3, callfuncN_selector(EditSplashAppearanceLayer::bgLoop)),
        nullptr
    ));
    
    
    this->addChild(bg);
    this->addChild(bg2);
    this->addChild(bg3);
    return true;
}

void EditSplashAppearanceLayer::bgLoop(CCNode* node) {
    node->runAction(CCRepeatForever::create(CCSequence::create(
        CCMoveBy::create(0, {node->getContentWidth() * 3, 0}),
        CCMoveBy::create(15 * 3, {-node->getContentWidth() * 3, 0}),
        nullptr
    )));
}