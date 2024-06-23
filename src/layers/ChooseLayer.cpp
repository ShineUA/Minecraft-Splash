#include "./ChooseLayer.h"

ChooseLayer* ChooseLayer::create(ArrayListNode* node) {
    auto ret = new ChooseLayer();
    if(ret && ret->initAnchored(285.f, 125.f, node, Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? "geode.loader/GE_square01.png" : "GJ_square01.png")) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
        ret = nullptr;
    }
    return ret;
}

bool ChooseLayer::setup(ArrayListNode* node) {
    this->m_node = node;
    this->setZOrder(200);
    if(Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme")) this->m_closeBtn->setSprite(CircleButtonSprite::createWithSpriteFrameName("geode.loader/close.png", 0.85f, CircleBaseColor::DarkPurple));
    else this->m_closeBtn->setSprite(CircleButtonSprite::createWithSpriteFrameName("geode.loader/close.png", 0.85f, CircleBaseColor::Green));
    auto splashesOptionsSpr = ButtonSprite::create("Edit Splashes", "goldFont.fnt", Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? "geode.loader/GE_button_05.png" : "GJ_button_01.png");
    auto splashesOptionsBtn = CCMenuItemSpriteExtra::create(
        splashesOptionsSpr, this, menu_selector(ChooseLayer::onSplashesOptionsBtn)
    );
    splashesOptionsBtn->setPosition({this->offset.x, this->offset.y + 21.f});
    auto splashPositionSpr = ButtonSprite::create("Edit Appearance", "goldFont.fnt", Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? "geode.loader/GE_button_05.png" : "GJ_button_01.png");
    auto splashPositionBtn = CCMenuItemSpriteExtra::create(
        splashPositionSpr, this, menu_selector(ChooseLayer::onEditAppearanceBtn)
    );
    splashPositionBtn->setPosition({this->offset.x, this->offset.y - 21.f});
    this->m_buttonMenu->addChild(splashesOptionsBtn);
    this->m_buttonMenu->addChild(splashPositionBtn);
    return true;
}

void ChooseLayer::onSplashesOptionsBtn(CCObject* sender) {
    CCScene::get()->addChild(SplashesListPopup::create(this->m_node));
}

void ChooseLayer::onEditAppearanceBtn(CCObject* sender) {

}