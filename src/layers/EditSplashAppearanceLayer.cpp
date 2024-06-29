#include "./EditSplashAppearanceLayer.h"

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
    this->m_menu->setPosition({0, 0});
    auto bg = CCSpriteBatchNode::create((GameManager::get()->m_loadedBgID < 10) ? fmt::format("game_bg_0{}_001.png", GameManager::get()->m_loadedBgID).c_str() : fmt::format("game_bg_{}_001.png", GameManager::get()->m_loadedBgID).c_str());
    auto bg_1 = CCSprite::create((GameManager::get()->m_loadedBgID < 10) ? fmt::format("game_bg_0{}_001.png", GameManager::get()->m_loadedBgID).c_str() : fmt::format("game_bg_{}_001.png", GameManager::get()->m_loadedBgID).c_str());
    bg_1->setScale(CCDirector::sharedDirector()->getWinSizeInPixels().width / bg_1->getTexture()->getContentSizeInPixels().width);
    bg_1->setPosition((bg_1->getContentSize() / 2) * (CCDirector::sharedDirector()->getWinSizeInPixels().width / bg_1->getTexture()->getContentSizeInPixels().width));
    bg_1->setColor({0, 255, 255});
    bg_1->setID("bg-1"_spr);
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
    bg_2->setID("bg-2"_spr);
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
    auto ground = GJGroundLayer::create(GameManager::get()->m_loadedGroundID, 0);
    ground->setPositionY(90);
    ground->getChildByID("ground-sprites")->runAction(CCRepeatForever::create(CCSequence::create(
        CCMoveBy::create(0.35, {-128, 0}),
        CCMoveBy::create(0, {128, 0}),
        nullptr
    )));
    auto groundSpritesArr = static_cast<CCSprite*>(ground->getChildByID("ground-sprites")->getChildren()->objectAtIndex(0))->getChildren();
    for(int i = 0; i < groundSpritesArr->count(); i++) {
        static_cast<CCSprite*>(groundSpritesArr->objectAtIndex(i))->setColor({0, 255, 255});
        static_cast<CCSprite*>(groundSpritesArr->objectAtIndex(i))->runAction(CCRepeatForever::create(CCSequence::create(
        CCTintTo::create(2.5, 255, 0, 255),
        CCDelayTime::create(0.5),
        CCTintTo::create(2.5, 255, 255, 0),
        CCDelayTime::create(0.5),
        CCTintTo::create(2.5, 0, 255, 255),
        CCDelayTime::create(0.5),
        nullptr
        )));
    }
    if(ground->getChildByID("ground-sprites-2")) {
        ground->getChildByID("ground-sprites-2")->runAction(CCRepeatForever::create(CCSequence::create(
            CCMoveBy::create(0.35, {-128, 0}),
            CCMoveBy::create(0, {128, 0}),
            nullptr
        )));
        auto ground2SpritesArr = static_cast<CCSprite*>(ground->getChildByID("ground-sprites-2")->getChildren()->objectAtIndex(0))->getChildren();
        for(int i = 0; i < ground2SpritesArr->count(); i++) {
            static_cast<CCSprite*>(ground2SpritesArr->objectAtIndex(i))->setColor({0, 255, 255});
            static_cast<CCSprite*>(ground2SpritesArr->objectAtIndex(i))->runAction(CCRepeatForever::create(CCSequence::create(
            CCTintTo::create(2.5, 255, 0, 255),
            CCDelayTime::create(0.5),
            CCTintTo::create(2.5, 255, 255, 0),
            CCDelayTime::create(0.5),
            CCTintTo::create(2.5, 0, 255, 255),
            CCDelayTime::create(0.5),
            nullptr
            )));
        }
    }
    this->addChild(bg);
    this->addChild(ground);

    auto exitBtnSpr = ButtonSprite::create("Return", "goldFont.fnt", "GJ_button_05.png");
    auto exitBtn = CCMenuItemSpriteExtra::create(
        exitBtnSpr,
        this,
        menu_selector(EditSplashAppearanceLayer::onReturn)
    );
    exitBtn->setPosition({offset.x + 57, offset.y + 135});
    this->m_menu->addChild(exitBtn);
    auto saveBtnSpr = ButtonSprite::create("Save");
    auto saveBtn = CCMenuItemSpriteExtra::create(
        saveBtnSpr,
        this,
        nullptr
    );
    saveBtn->setPosition({offset.x - 57, offset.y + 135});
    this->m_menu->addChild(saveBtn);
    auto editableNode = EditableSplashNode::create();

    this->addChild(editableNode);
    this->addChild(this->m_menu);
    return true;
}

void EditSplashAppearanceLayer::onReturn(CCObject* sender) {
    this->keyBackClicked();
}
