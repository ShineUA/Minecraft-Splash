#include "EditEntriesLayer.h"

#include "../tools/Easings.h"
#include "Geode/cocos/platform/CCPlatformMacros.h"
#include "SplashesListPopup.h"

EditEntriesLayer* EditEntriesLayer::create(ArrayListNode* node, int index, int mode, SplashesListPopup* prev_popup) {
    EditEntriesLayer* ret = new EditEntriesLayer();
    if (ret && ret->initAnchored(435.f, 285.f, node, index, mode, prev_popup, Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? "geode.loader/GE_square01.png" : "GJ_square01.png")) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
        ret = nullptr;
    }
    return ret;
}

bool EditEntriesLayer::setup(ArrayListNode* node, int index, int mode, SplashesListPopup* prev_popup) {
    this->m_node = node;
    this->m_previousPopup = prev_popup;
    this->setZOrder(300);
    this->m_index = index;
    if(Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme")) this->m_closeBtn->setSprite(CircleButtonSprite::createWithSpriteFrameName("geode.loader/close.png", 0.85f, CircleBaseColor::DarkPurple));
    else this->m_closeBtn->setSprite(CircleButtonSprite::createWithSpriteFrameName("geode.loader/close.png", 0.85f, CircleBaseColor::Green));
    auto labelInput = TextInput::create(300, "Splash Text", "bigFont.fnt");
    labelInput->setFilter("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz,'.!?0123456789 ");
    labelInput->setMaxCharCount(40);
    labelInput->setPosition({offset.x, offset.y + 85});
    labelInput->setID("splash-text");
    auto scaleInput = TextInput::create(50, "Scale", "bigFont.fnt");
    scaleInput->setFilter("0123456789.");
    scaleInput->setMaxCharCount(4);
    scaleInput->getInputNode()->setLabelPlaceholderScale(0.4);
    scaleInput->getInputNode()->setMaxLabelScale(0.5);
    scaleInput->setPosition({offset.x, offset.y + 50});
    scaleInput->setScale(0.8);
    scaleInput->setID("scale");
    auto previewBg = CCScale9Sprite::create("GJ_square05.png");
    previewBg->setPosition({offset.x, offset.y - 50.f});
    previewBg->setContentSize(ccp(205, 100));
    auto previewTip = CCLabelBMFont::create("Tip: The text shouldn't extend\nbeyond the edges of the square", "bigFont.fnt");
    previewTip->setScale(0.35f);
    previewTip->setOpacity(150);
    previewTip->setPosition({offset.x, offset.y + 15.f});
    this->m_previewLabel = CCLabelBMFont::create(this->m_defaultPreviewPlaceholder.c_str(), "goldFont.fnt");
    this->m_previewLabel->setPosition(previewBg->getPosition());
    this->m_previewLabel->setScale(this->m_defaultPreviewScale);
    if(Mod::get()->getSettingValue<bool>("new-appearance")) this->m_previewLabel->setRotation(-15.f);
    else this->m_previewLabel->setRotation(-9.f);
    this->m_mainLayer->addChild(previewBg);
    this->m_mainLayer->addChild(previewTip);
    this->m_mainLayer->addChild(this->m_previewLabel);
    this->m_buttonMenu->addChild(labelInput);
    this->m_buttonMenu->addChild(scaleInput);
    if(mode == 0) {
        this->setTitle("Add Splash", "goldFont.fnt", 1);
        auto addSpr = ButtonSprite::create("Add", "goldFont.fnt", Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? "geode.loader/GE_button_05.png" : "GJ_button_01.png");
        auto addBtn = CCMenuItemSpriteExtra::create(
            addSpr,
            this,
            menu_selector(EditEntriesLayer::addSplash)
        );
        addBtn->setPosition({offset.x, offset.y + -120});
        this->m_buttonMenu->addChild(addBtn);
    } else if(mode == 1) {
        this->setTitle("Edit Splash", "goldFont.fnt", 1);
        labelInput->setString(this->m_node->getValue().at(this->m_index).c_str());
        //scaleInput->setString(this->m_node->getValue().at(this->m_index).at(1).c_str());
        this->m_previewLabel->setString(this->m_node->getValue().at(this->m_index).c_str());
        //this->m_previewLabel->setScale(std::stof(this->m_node->getValue().at(this->m_index).at(1).c_str()));
        auto editSpr = ButtonSprite::create("Edit", "goldFont.fnt", Loader::get()->getLoadedMod("geode.loader")->getSettingValue<bool>("enable-geode-theme") ? "geode.loader/GE_button_05.png" : "GJ_button_01.png");
        auto editBtn = CCMenuItemSpriteExtra::create(
            editSpr,
            this,
            menu_selector(EditEntriesLayer::editSplash)
        );
        editBtn->setPosition({offset.x, offset.y + -120});
        this->m_buttonMenu->addChild(editBtn);
    } else this->keyBackClicked();
    auto splashDelegate = new EditEntriesLayer::SplashInputDelegate();
    labelInput->getInputNode()->setDelegate(splashDelegate);
    auto scaleDelegate = new EditEntriesLayer::ScaleInputDelegate();
    scaleInput->getInputNode()->setDelegate(scaleDelegate);
    CCActionInterval* inEasing = EasingsPreview::returnEasingIn(Mod::get()->getSettingValue<int64_t>("easing-in"), this->m_previewLabel);
    CCActionInterval* outEasing = EasingsPreview::returnEasingOut(Mod::get()->getSettingValue<int64_t>("easing-out"), this->m_previewLabel);
    if(!Mod::get()->getSettingValue<bool>("dis-anim")) {
        this->m_previewLabel->runAction(CCRepeatForever::create(CCSequence::create(
            inEasing,
            outEasing,
            nullptr
        )))->setTag(1);
    }
    return true;
}

void EditEntriesLayer::addSplash(CCObject* sender) {
    auto splash = static_cast<TextInput*>(this->m_buttonMenu->getChildByID("splash-text"))->getString();
    auto scale = static_cast<TextInput*>(this->m_buttonMenu->getChildByID("scale"))->getString();
    if(scale.empty() || splash.empty() || scale.ends_with(".") || std::stof(scale) <= 0) {
        return FLAlertLayer::create(
            "Error!",
            "Please fill all input fields <cr>correctly!</c>",
            "OK"
        )->show();
    }
    std::vector<std::string> v = this->m_node->getValue();
    v.push_back(splash);
    this->m_node->setValue(v);
    auto itemMenu = CCMenu::create();
    itemMenu->setPosition({this->m_previousPopup->m_scrollLayer->getContentWidth() - 40, 40.f / 2.f});
    itemMenu->setContentWidth(73);
    itemMenu->setLayout(RowLayout::create()->setAutoScale(false), false);
    auto splashText = CCLabelBMFont::create(splash.c_str(), "bigFont.fnt");
    splashText->setScale(0.5f);
    splashText->setAnchorPoint({0.f, 0.5f});
    splashText->setPosition({5.f, 20.f});
    splashText->limitLabelWidth(this->m_previousPopup->m_scrollLayer->getContentWidth() - 86.f, 0.5f, 0.2f);
    auto deleteSpr = CCSprite::createWithSpriteFrameName("GJ_trashBtn_001.png");
    deleteSpr->setScale(0.8f);
    auto deleteBtn = CCMenuItemSpriteExtra::create(
        deleteSpr,
        this->m_previousPopup,
        menu_selector(SplashesListPopup::deleteEntry)
    );
    deleteBtn->setID(std::to_string(v.size()- 1).c_str());
    auto editSprText = CCLabelBMFont::create("Edit", "bigFont.fnt");
    auto editSpr = CircleButtonSprite::create(editSprText, CircleBaseColor::Pink);
    editSpr->setScale(0.7f);
    auto editBtn = CCMenuItemSpriteExtra::create(
        editSpr,
        this->m_previousPopup,
        menu_selector(SplashesListPopup::editEntry)
    );
    editBtn->setID(std::to_string(v.size() - 1).c_str());
    itemMenu->addChild(editBtn);
    itemMenu->addChild(deleteBtn);
    auto itemNode = CCNode::create();
    itemNode->setContentSize(ccp(this->m_previousPopup->m_scrollLayer->getContentWidth(), 40));
    itemNode->setID(std::to_string(v.size() - 1).c_str());
    itemNode->setZOrder(1);
    
    itemNode->addChild(splashText);
    itemNode->addChild(itemMenu);
    itemMenu->updateLayout();
    if((v.size() - 1) * 40.f > this->m_previousPopup->m_scrollLayer->getContentHeight()) {
        this->m_previousPopup->m_scrollLayer->m_contentLayer->setContentHeight(this->m_previousPopup->m_scrollLayer->m_contentLayer->getContentHeight() + 40);
        itemNode->setPositionY(-40);
        itemNode->runAction(CCMoveBy::create(0.4, {0, 40}));
        if((v.size() - 1) % 2 == 0 && !this->m_previousPopup->m_isEven && this->m_previousPopup->m_scrollLayer->m_contentLayer->getChildByID("col-" + std::to_string(v.size() - 1)) == nullptr && v.size() - 1 >= this->m_previousPopup->m_startSize) {
            log::info("1");
            auto bg = CCLayerColor::create();
            bg->setOpacity(50);
            bg->setID("col-" + std::to_string(v.size() - 1));
            bg->setContentSize(ccp(this->m_previousPopup->m_scrollLayer->getContentWidth(), 40));
            bg->setPositionY(this->m_previousPopup->m_scrollLayer->m_contentLayer->getContentHeight() - 40);
            this->m_previousPopup->m_scrollLayer->m_contentLayer->addChild(bg);
        } else if ((v.size() - 1) % 2 != 0 && this->m_previousPopup->m_isEven && this->m_previousPopup->m_scrollLayer->m_contentLayer->getChildByID("col-" + std::to_string(v.size() - 1)) == nullptr && v.size() - 1 >= this->m_previousPopup->m_startSize){
            log::info("2");
            auto bg = CCLayerColor::create();
            bg->setOpacity(50);
            bg->setID("col-" + std::to_string(v.size() - 1));
            bg->setContentSize(ccp(this->m_previousPopup->m_scrollLayer->getContentWidth(), 40));
            bg->setPositionY(this->m_previousPopup->m_scrollLayer->m_contentLayer->getContentHeight() - 40);
            this->m_previousPopup->m_scrollLayer->m_contentLayer->addChild(bg);
        }
        for(int i = v.size() - 2; i >= 0; i--) {
            auto node = this->m_previousPopup->m_scrollLayer->m_contentLayer->getChildByID(std::to_string(i));
            node->runAction(CCMoveBy::create(0.4, {0, 40}));
        }
        this->m_previousPopup->m_scrollLayer->m_contentLayer->addChild(itemNode);
    } else {
        itemNode->setPositionY(this->m_previousPopup->m_scrollLayer->m_contentLayer->getChildByID(std::to_string(v.size() - 2))->getPositionY() - 40);
        splashText->setOpacity(0);
        editSprText->setOpacity(0);
        editSpr->setOpacity(0);
        deleteSpr->setOpacity(0);
        if((v.size() - 1) % 2 == 0) {
            log::info("3");
            auto bg = CCLayerColor::create();
            bg->setOpacity(50);
            bg->setID("col-" + std::to_string(v.size() - 1));
            bg->setContentSize(ccp(this->m_previousPopup->m_scrollLayer->m_contentLayer->getContentWidth(), 40));
            bg->setPositionY(this->m_previousPopup->m_scrollLayer->m_contentLayer->getContentHeight() - (40 * (v.size())));
            this->m_previousPopup->m_scrollLayer->m_contentLayer->addChild(bg);
        }
        splashText->runAction(CCFadeIn::create(0.4));
        editSprText->runAction(CCFadeIn::create(0.4));
        editSpr->runAction(CCFadeIn::create(0.4));
        deleteSpr->runAction(CCFadeIn::create(0.4));
        this->m_previousPopup->m_scrollLayer->m_contentLayer->addChild(itemNode);
    }
    //this->m_previousPopup->updateSplashesList(this->m_previousPopup->offset.x, this->m_previousPopup->offset.y, 320, 225);
    this->m_node->dispatchChangedPublic();
    this->m_previousPopup->checkForChanges();
    this->onClose(nullptr);
}

void EditEntriesLayer::editSplash(CCObject* sender) {
    auto splash = static_cast<TextInput*>(this->m_buttonMenu->getChildByID("splash-text"))->getString();
    auto scale = static_cast<TextInput*>(this->m_buttonMenu->getChildByID("scale"))->getString();
    if(scale.empty() || splash.empty() || scale.ends_with(".") || std::stof(scale) <= 0) {
        return FLAlertLayer::create(
            "Error!",
            "Please fill all input fields <cr>correctly!</c>",
            "OK"
        )->show();
    }
    std::vector<std::string> v = this->m_node->getValue();
    v.at(this->m_index) = splash;
    this->m_node->setValue(v);
    auto oldVisSplash = getChildOfType<CCLabelBMFont>(this->m_previousPopup->m_scrollLayer->m_contentLayer->getChildByID(std::to_string(this->m_index)), 0);
    auto newVisSplash = CCLabelBMFont::create(splash.c_str(), "bigFont.fnt");
    newVisSplash->setScale(0.5f);
    newVisSplash->setAnchorPoint({0.f, 0.5f});
    newVisSplash->setPosition({5.f, 20.f});
    newVisSplash->limitLabelWidth(this->m_previousPopup->m_scrollLayer->getContentWidth() - 86.f, 0.5f, 0.2f);
    newVisSplash->setOpacity(0);
    this->m_previousPopup->m_scrollLayer->m_contentLayer->getChildByID(std::to_string(this->m_index))->addChild(newVisSplash);
    oldVisSplash->runAction(CCSequence::create(
        CCFadeOut::create(0.3),
        CCCallFuncN::create(oldVisSplash, callfuncN_selector(SplashesListPopup::destroyNode)),
        nullptr
    ));
    newVisSplash->runAction(CCSequence::create(
        CCDelayTime::create(0.4),
        CCFadeIn::create(0.3),
        nullptr
    ));
    this->m_node->dispatchChangedPublic();
    this->m_previousPopup->checkForChanges();
    this->onClose(nullptr);
}

void EditEntriesLayer::SplashInputDelegate::textChanged(CCTextInputNode* p0) {
    std::string string = p0->getString();
    if(string.empty()) static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_previewLabel->setString(static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_defaultPreviewPlaceholder.c_str());
    else static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_previewLabel->setString(string.c_str());
}

void EditEntriesLayer::ScaleInputDelegate::textChanged(CCTextInputNode* p0) {
    auto dis_anim = Mod::get()->getSettingValue<bool>("dis-anim");
    float scale;
    if(p0->getString().empty() || p0->getString() == "0.") return;
    else if(p0->getString() == "1.") return;
    else if(p0->getString() == ".") {
        p0->setString("");
        return;
    } else scale = std::stof(p0->getString());

    if(scale > 1.0f) p0->setString("1.0");
    else {
        if(scale > 0.f) {
            static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_previewLabel->setScale(scale);
#ifdef GEODE_IS_MACOS
        if(!dis_anim) {
            static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_previewLabel->stopActionByTag(1);
			static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_previewLabel->runAction(CCRepeatForever::create(CCSequence::create(
				cocos2d::CCScaleTo::create(Mod::get()->getSettingValue<double>("animation-length"), static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_previewLabel->getScale() + Mod::get()->getSettingValue<double>("animation-scale")),
				cocos2d::CCScaleTo::create(Mod::get()->getSettingValue<double>("animation-length"), static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_previewLabel->getScale()),
				nullptr
			)))->setTag(1);
		}
#else
            if(!dis_anim) {
                static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_previewLabel->stopActionByTag(1);
                CCActionInterval* inEasing = EasingsPreview::returnEasingIn(Mod::get()->getSettingValue<int64_t>("easing-in"), static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_previewLabel);
		        CCActionInterval* outEasing = EasingsPreview::returnEasingOut(Mod::get()->getSettingValue<int64_t>("easing-out"), static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_previewLabel);
                static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_previewLabel->runAction(CCRepeatForever::create(CCSequence::create(
                    inEasing,
                    outEasing,
                    nullptr
                )))->setTag(1);
            }
#endif
        } else {
            static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_previewLabel->setScale(static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_defaultPreviewScale);
#ifdef GEODE_IS_MACOS
        if(!dis_anim) {
            static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_previewLabel->stopActionByTag(1);
			static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_previewLabel->runAction(CCRepeatForever::create(CCSequence::create(
				cocos2d::CCScaleTo::create(Mod::get()->getSettingValue<double>("animation-length"), static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_previewLabel->getScale() + Mod::get()->getSettingValue<double>("animation-scale")),
				cocos2d::CCScaleTo::create(Mod::get()->getSettingValue<double>("animation-length"), static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_previewLabel->getScale()),
				nullptr
			)))->setTag(1);
		}
#else
            if(!dis_anim) {
                static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_previewLabel->stopActionByTag(1);
                CCActionInterval* inEasing = EasingsPreview::returnEasingIn(Mod::get()->getSettingValue<int64_t>("easing-in"), static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_previewLabel);
                CCActionInterval* outEasing = EasingsPreview::returnEasingOut(Mod::get()->getSettingValue<int64_t>("easing-out"), static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_previewLabel);
                static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_previewLabel->runAction(CCRepeatForever::create(CCSequence::create(
                    inEasing,
                    outEasing,
                    nullptr
                )))->setTag(1);
            }
#endif
        }
    }
}