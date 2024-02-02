#include "SettingsLayer.h"

#include <Geode/Geode.hpp>
#include <Geode/Bindings.hpp>
#include <string>
#include <cstring>
#include "../main.h"

using namespace geode::prelude;

int page = 0;

SettingsLayer* SettingsLayer::create() {
	auto ret = new SettingsLayer();
    if (ret && ret->init()) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool SettingsLayer::init() {
    if(!CCLayer::init()) return false;

    this->setTouchEnabled(true);
    this->setTouchMode(kCCTouchesOneByOne);
    this->setMouseEnabled(true);
    this->setKeypadEnabled(true);

    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -129, true);

    this->setID("ms-settings");

	geode::cocos::handleTouchPriority(this);
    auto winSize = CCDirector::sharedDirector()->getWinSize();

    this->setContentSize(ccp(winSize.width, winSize.height));

    auto bg = CCScale9Sprite::create("GJ_square01-uhd.png");
    bg->setContentSize(ccp(475, 280));
    bg->setID("panel");
    bg->setPosition({winSize.width + 10.f, winSize.height / 2});
    bg->setZOrder(-3);

    auto backBtn = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"),
        this,
        menu_selector(SettingsLayer::onBack)
    );
    backBtn->setID("exit-button");
    backBtn->setPosition({winSize.width + 10.f - 228.f, winSize.height / 2 + 137.f});

    auto title = CCLabelBMFont::create("Splash's Settings", "bigFont.fnt");
    title->setPosition({winSize.width + 10.f, winSize.height / 2 + 120.f});
    title->setScale(0.550f);

    auto appearanceInfo = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"),
        this,
        menu_selector(SettingsLayer::onAppearanceInfo)
    );
    appearanceInfo->setScale(0.5f);
    appearanceInfo->setPosition({winSize.width + 10.f - 212.f, winSize.height / 2 + 96.f});
    appearanceInfo->m_baseScale = 0.5f;
    appearanceInfo->setID("appearance-info-btn");

    auto appearanceLabel = CCLabelBMFont::create("Enable new appearance", "bigFont.fnt");
    appearanceLabel->setPosition({winSize.width + 10.f - 91.f, winSize.height / 2 + 80.f});
    appearanceLabel->setScale(0.4f);
    appearanceLabel->setID("appearance-label-text");

    auto appearanceCheckBoxSprite = CCSprite::createWithSpriteFrameName(Mod::get()->getSettingValue<bool>("new-appearance") ? "GJ_checkOn_001.png" : "GJ_checkOff_001.png");
    auto appearanceCheckBoxSprite2 = CCSprite::createWithSpriteFrameName(!Mod::get()->getSettingValue<bool>("new-appearance") ? "GJ_checkOn_001.png" : "GJ_checkOff_001.png");

    auto appearanceCheckBox = CCMenuItemToggler::create(
        appearanceCheckBoxSprite,
        appearanceCheckBoxSprite2,
        this,
        menu_selector(SettingsLayer::onAppearanceChecked)
    );
    appearanceCheckBox->setPosition({winSize.width + 10.f - 192.f, winSize.height / 2 + 80.f});
    appearanceCheckBox->setScale(0.78f);
    appearanceCheckBox->setID("appearance-checkbox");

    auto disAnimInfo = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"),
        this,
        menu_selector(SettingsLayer::onDisAnimInfo)
    );
    disAnimInfo->setScale(0.5f);
    disAnimInfo->setPosition({winSize.width + 10.f - 4.f, winSize.height / 2 + 96.f});
    disAnimInfo->m_baseScale = 0.5f;
    disAnimInfo->setID("dis-anim-info-btn");

    auto disAnimLabel = CCLabelBMFont::create("Disable animation", "bigFont.fnt");
    disAnimLabel->setPosition({winSize.width + 10.f + 97.f, winSize.height / 2 + 80.f});
    disAnimLabel->setScale(0.4f);
    disAnimLabel->setID("dis-anim-text");

    auto disAnimCheckBoxSprite = CCSprite::createWithSpriteFrameName(Mod::get()->getSettingValue<bool>("dis-anim") ? "GJ_checkOn_001.png" : "GJ_checkOff_001.png");
    auto disAnimCheckBoxSprite2 = CCSprite::createWithSpriteFrameName(!Mod::get()->getSettingValue<bool>("dis-anim") ? "GJ_checkOn_001.png" : "GJ_checkOff_001.png");

    auto disAnimCheckBox = CCMenuItemToggler::create(
        disAnimCheckBoxSprite,
        disAnimCheckBoxSprite2,
        this,
        menu_selector(SettingsLayer::onDisAnimChecked)
    );
    disAnimCheckBox->setPosition({winSize.width + 10.f + 16.f, winSize.height / 2 + 80.f});
    disAnimCheckBox->setScale(0.78f);
    disAnimCheckBox->setID("dis-anim-checkbox");


    auto animationLengthInfo = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"),
        this,
        menu_selector(SettingsLayer::onAnimationLengthInfo)
    );
    animationLengthInfo->setScale(0.5f);
    animationLengthInfo->setPosition({winSize.width + 10.f - 191.f, winSize.height / 2 - 72.f});
    animationLengthInfo->m_baseScale = 0.5f;
    animationLengthInfo->setID("animation-length-info-btn");

    auto animationSpeedBG = CCScale9Sprite::create("square02_small-uhd.png");
    animationSpeedBG->setContentSize(ccp(70, 30));
    animationSpeedBG->setPosition({winSize.width + 10.f - 128.f, winSize.height / 2 - 107.f});
    animationSpeedBG->setOpacity(100);
    animationSpeedBG->setScale(0.7f);
    animationSpeedBG->setID("animation-length-text-bg");

    auto animationLengthLabel = CCLabelBMFont::create("Animation Length:", "bigFont.fnt");
    animationLengthLabel->setPosition({winSize.width + 10.f - 128.f, winSize.height / 2 - 81.f});
    animationLengthLabel->setScale(0.4f);
    animationLengthLabel->setID("animation-length-label-text");

    std::stringstream ss;
    ss << Mod::get()->getSettingValue<float>("animation-length");
    auto animationLengthInput = CCTextInputNode::create(
        70.f,
        30.f,
        ss.str().c_str(),
        "bigFont.fnt"
    );
    animationLengthInput->setPosition({winSize.width + 10.f - 149.f, winSize.height / 2 - 114.f});
    animationLengthInput->setScale(0.420f);
    animationLengthInput->m_allowedChars = "0123456789.";
    animationLengthInput->setID("animation-length");

    auto animationScaleInfo = CCMenuItemSpriteExtra::create(
        CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png"),
        this,
        menu_selector(SettingsLayer::onAnimationScaleInfo)
    );
    animationScaleInfo->setScale(0.5f);
    animationScaleInfo->setPosition({winSize.width + 10.f - 60.f, winSize.height / 2 - 90.f});
    animationScaleInfo->m_baseScale = 0.5f;
    animationScaleInfo->setID("animation-scale-info-btn");

    auto animationScaleBG = CCScale9Sprite::create("square02_small-uhd.png");
    animationScaleBG->setContentSize(ccp(70, 30));
    animationScaleBG->setPosition({winSize.width + 10.f, winSize.height / 2 - 107.f});
    animationScaleBG->setOpacity(100);
    animationScaleBG->setScale(0.7f);
    animationScaleBG->setID("animation-scale-text-bg");

    auto animationScaleLabel = CCLabelBMFont::create("Animation Scale:", "bigFont.fnt");
    animationScaleLabel->setPosition({winSize.width + 10.f, winSize.height / 2 - 81.f});
    animationScaleLabel->setScale(0.4f);
    animationScaleLabel->setID("animation-scale-label-text");

    ss.str("");
    ss << Mod::get()->getSettingValue<float>("animation-scale");
    auto animationScaleInput = CCTextInputNode::create(
        70.f,
        30.f,
        ss.str().c_str(),
        "bigFont.fnt"
    );
    animationScaleInput->setPosition({winSize.width + 10.f - 21.f, winSize.height / 2 - 114.f});
    animationScaleInput->setScale(0.420f);
    animationScaleInput->m_allowedChars = "0123456789.";
    animationScaleInput->setID("animation-scale");

    auto test1 = CCLabelBMFont::create("Test1", "bigFont.fnt");

    auto splashArray = CCArray::create(test1, nullptr);

    auto splashAmount = Mod::get()->getSettingValue<int>("amount-of-splashes");
    std::stringstream ss_text;

    for(int i = 0; i < splashAmount; i++) {
        ss.str("");
        ss << "splash-" << i;
        auto splash = Mod::get()->getSettingValue<std::string>(ss.str().c_str());
        ss << "-size";
        auto splash_size = Mod::get()->getSettingValue<std::string>(ss.str().c_str());
        ss.str("");
        ss << splash << " Size: " << splash_size;
        auto textHolder = CCLabelBMFont::create(ss.str().c_str(), "bigFont.fnt");
        textHolder->setScale(0.4f);
        if(i == 0) {
            splashArray->replaceObjectAtIndex(0, textHolder);
        } else {
            splashArray->addObject(textHolder);
        }
        
    }

    auto splashList = ListView::create(splashArray, 25.f);
    splashList->setPosition({winSize.width / 2 - 178.f, winSize.height / 2 - 120.f});
    splashList->setVisible(false); // for pages
    splashList->setID("splash-list");

    auto menuBtns = CCMenu::create();
    menuBtns->setPosition({0.f, 0.f});
    menuBtns->addChild(backBtn);
    menuBtns->addChild(appearanceInfo);
    menuBtns->addChild(appearanceCheckBox);
    menuBtns->addChild(disAnimInfo);
    menuBtns->addChild(disAnimCheckBox);
    menuBtns->addChild(animationLengthInfo);
    menuBtns->addChild(animationLengthInput);
    menuBtns->addChild(animationScaleInfo);
    menuBtns->addChild(animationScaleInput);
    menuBtns->setID("buttons");

    bg->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(1.0f, CCDirector::get()->getWinSize() / 2)), nullptr));
    backBtn->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(1.0f, {winSize.width / 2 - 228.f, winSize.height / 2 + 130.f})), nullptr));
    title->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(1.0f, {winSize.width / 2, winSize.height / 2 + 120.f})), nullptr));
    appearanceLabel->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(1.0f, {winSize.width / 2 - 91.f, winSize.height / 2 + 80.f})), nullptr));
    appearanceCheckBox->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(1.0f, {winSize.width / 2 - 192.f, winSize.height / 2 + 80.f})), nullptr));
    appearanceInfo->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(1.0f, {winSize.width / 2 - 212.f, winSize.height / 2 + 96.f})), nullptr));
    animationSpeedBG->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(1.0f, {winSize.width / 2 - 128.f, winSize.height / 2 - 107.f})), nullptr));
    animationLengthLabel->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(1.0f, {winSize.width / 2 - 128.f, winSize.height / 2 - 81.f})), nullptr));
    animationLengthInput->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(1.0f, {winSize.width / 2 - 149.f, winSize.height / 2 - 114.f})), nullptr));
    animationLengthInfo->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(1.0f, {winSize.width / 2 - 191.f, winSize.height / 2 - 72.f})), nullptr));
    animationScaleBG->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(1.0f, {winSize.width / 2, winSize.height / 2 - 107.f})), nullptr));
    animationScaleLabel->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(1.0f, {winSize.width / 2, winSize.height / 2 - 81.f})), nullptr));
    animationScaleInput->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(1.0f, {winSize.width / 2 - 21.f, winSize.height / 2 - 114.f})), nullptr));
    animationScaleInfo->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(1.0f, {winSize.width / 2 - 60.f, winSize.height / 2 - 72.f})), nullptr));
    disAnimLabel->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(1.0f, {winSize.width / 2 + 97.f, winSize.height / 2 + 80.f})), nullptr));
    disAnimCheckBox->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(1.0f, {winSize.width / 2 + 16.f, winSize.height / 2 + 80.f})), nullptr));
    disAnimInfo->runAction(CCSequence::create(CCEaseElasticOut::create(CCMoveTo::create(1.0f, {winSize.width / 2 - 4.f, winSize.height / 2 + 96.f})), nullptr));

    addChild(bg);
    addChild(animationSpeedBG);
    addChild(animationScaleBG);
    addChild(menuBtns);
    addChild(title);
    addChild(appearanceLabel);
    addChild(disAnimLabel);
    addChild(animationLengthLabel);
    addChild(animationScaleLabel);
    addChild(splashList);
	return true;
};

void SettingsLayer::keyBackClicked() {
    SettingsLayer::onBack(nullptr);
}

void SettingsLayer::onBack(CCObject* sender) {
    auto splash = this->getParent()->getParent()->getChildByID("MenuLayer")->getChildByID("minecraft-splash");
    auto animation_speed_input = static_cast<CCTextInputNode*>(this->getChildByID("buttons")->getChildByID("animation-length"));
    auto animation_speed = animation_speed_input->getString();
    auto animation_scale_input = static_cast<CCTextInputNode*>(this->getChildByID("buttons")->getChildByID("animation-scale"));
    auto animation_scale = animation_scale_input->getString();
    std::stringstream ss;
    ss << "splash-" << random_splash << "-size";
    
    if(!Mod::get()->getSettingValue<bool>("dis-anim")) {
        if(!animation_speed.empty()) {
            splash->stopActionByTag(1);
            splash->setScale(std::stof(Mod::get()->getSettingValue<std::string>(ss.str().c_str())));
            splash->runAction(CCRepeatForever::create(CCSequence::create(
                CCEaseOut::create(CCScaleTo::create(std::stof(animation_speed), splash->getScale() + Mod::get()->getSettingValue<float>("animation-scale")), std::stof(animation_speed)),
                CCEaseOut::create(CCScaleTo::create(std::stof(animation_speed), splash->getScale()), std::stof(animation_speed)),
                nullptr
            )))->setTag(1);
            Mod::get()->setSettingValue<float>("animation-length", std::stof(animation_speed));
        }

        if(!animation_scale.empty()) {
            splash->stopActionByTag(1);
            splash->setScale(std::stof(Mod::get()->getSettingValue<std::string>(ss.str().c_str())));
            splash->runAction(CCRepeatForever::create(CCSequence::create(
                CCEaseOut::create(CCScaleTo::create(Mod::get()->getSettingValue<float>("animation-length"), splash->getScale() + std::stof(animation_scale)), Mod::get()->getSettingValue<float>("animation-length")),
                CCEaseOut::create(CCScaleTo::create(Mod::get()->getSettingValue<float>("animation-length"), splash->getScale()), Mod::get()->getSettingValue<float>("animation-length")),
                nullptr
            )))->setTag(1);
            Mod::get()->setSettingValue<float>("animation-scale", std::stof(animation_scale));
        }
    } else {
        if(!animation_speed.empty()) {
            Mod::get()->setSettingValue<float>("animation-length", std::stof(animation_speed));
        }

        if(!animation_scale.empty()) {
            Mod::get()->setSettingValue<float>("animation-scale", std::stof(animation_scale));
        }
    }

    auto parent = this->getParent();
    parent->removeAllChildren();
    parent->removeFromParent();
    page = 0;
}

void SettingsLayer::onAppearanceChecked(CCObject* sender) {
    auto splash = this->getParent()->getParent()->getChildByID("MenuLayer")->getChildByID("minecraft-splash");
    auto main_title = this->getParent()->getParent()->getChildByID("MenuLayer")->getChildByID("main-title");
    auto winSize = CCDirector::get()->getWinSize();
    auto density = winSize.width / winSize.height;

    float posX, posY, rotation;

    if(!Mod::get()->getSavedValue<bool>("new-appearance", true)) {
        Mod::get()->setSettingValue<bool>("new-appearance", true);
        posX = main_title->getPositionX() + 167.f;
        posY = main_title->getPositionY() - 11.f;
        rotation = -15.f;
    } else {
        Mod::get()->setSettingValue<bool>("new-appearance", false);
        if(density < 1.7f && density >= 1.5f) {
            posX = winSize.width / 2 + 154.f;
            posY = winSize.height / 2 + 73.f;
        } else if(density < 1.5f) {
            posX = winSize.width / 2 + 132.f;
            posY = winSize.height / 2 + 86.f;
        } else {
            posX = winSize.width / 2 + 183.f;
            posY = winSize.height / 2 + 71.f;
        }
        rotation = -9.f;
    }

    splash->runAction(CCSequence::create(
        CCEaseExponentialOut::create(CCMoveTo::create(0.3f, {posX, posY})),
        nullptr
    ));
    splash->runAction(CCSequence::create(
        CCEaseExponentialOut::create(CCRotateTo::create(0.3f, rotation)),
        nullptr
    ));
}

void SettingsLayer::onDisAnimChecked(CCObject* sender) {
    auto splash = static_cast<CCLabelBMFont*>(this->getParent()->getParent()->getChildByID("MenuLayer")->getChildByID("minecraft-splash"));
    std::stringstream ss;
    ss << "splash-" << random_splash << "-size";

    if(!Mod::get()->getSettingValue<bool>("dis-anim")) {
        splash->stopActionByTag(1);
        splash->runAction(CCSequence::create(
            CCEaseOut::create(CCScaleTo::create(Mod::get()->getSettingValue<float>("animation-length"), std::stof(Mod::get()->getSettingValue<std::string>(ss.str().c_str()))), Mod::get()->getSettingValue<float>("animation-length")),
            nullptr
        ));
        Mod::get()->setSettingValue<bool>("dis-anim", true);
    } else {
        splash->runAction(CCRepeatForever::create(CCSequence::create(
            CCEaseOut::create(CCScaleTo::create(Mod::get()->getSettingValue<float>("animation-length"), std::stof(Mod::get()->getSettingValue<std::string>(ss.str().c_str())) + Mod::get()->getSettingValue<float>("animation-scale")), Mod::get()->getSettingValue<float>("animation-speed")),
            CCEaseOut::create(CCScaleTo::create(Mod::get()->getSettingValue<float>("animation-length"), std::stof(Mod::get()->getSettingValue<std::string>(ss.str().c_str()))), Mod::get()->getSettingValue<float>("animation-length")),
            nullptr
        )))->setTag(1);
        Mod::get()->setSettingValue<bool>("dis-anim", false);
    }
}

void SettingsLayer::onAppearanceInfo(CCObject* sender) {
    FLAlertLayer::create(
        "Info",
        "Enables new appearance which is more familiar to Minecraft original.",
        "OK"
    )->show();
}

void SettingsLayer::onDisAnimInfo(CCObject* sender) {
    FLAlertLayer::create(
        "Info",
        "Disables splash's animation.",
        "OK"
    )->show();
}

void SettingsLayer::onAnimationLengthInfo(CCObject* sender) {
    FLAlertLayer::create(
        "Info",
        "Changes length <cg>(in seconds)</c> of splash's animation.",
        "OK"
    )->show();
}

void SettingsLayer::onAnimationScaleInfo(CCObject* sender) {
    FLAlertLayer::create(
        "Info",
        "Changes scale of splash's animation.",
        "OK"
    )->show();
}

SettingsLayerBG* SettingsLayerBG::create() {
    auto ret = new SettingsLayerBG();
    if (ret && ret->init()) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool SettingsLayerBG::init() {
    if(!CCLayerColor::init()) return false;
    this->runAction(CCFadeTo::create(0.3f, 150));
    return true;
}
