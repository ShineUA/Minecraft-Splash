#include "EditEntriesLayer.h"

#include "../tools/Easings.h"
#include <Geode/ui/TextInput.hpp>

EditEntriesLayer* EditEntriesLayer::create(ArrayListNode* node, int index, int mode, SplashesListPopup* prev_popup) {
    EditEntriesLayer* ret = new EditEntriesLayer();
    if (ret && ret->initAnchored(435.f, 285.f, node, index, mode, prev_popup)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool EditEntriesLayer::setup(ArrayListNode* node, int index, int mode, SplashesListPopup* prev_popup) {
    this->m_node = node;
    this->m_previousPopup = prev_popup;
    this->setZOrder(300);
    this->m_index = index;
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
    this->m_previewLabel = CCLabelBMFont::create(fmt::format("{}", this->m_defaultPreviewPlaceholder).c_str(), "goldFont.fnt");
    this->m_previewLabel->setPosition(previewBg->getPosition());
    this->m_previewLabel->setScale(this->m_defaultPreviewScale);
    if(Mod::get()->getSettingValue<bool>("new-appearance")) {
        this->m_previewLabel->setRotation(-15.f);
    } else {
        this->m_previewLabel->setRotation(-9.f);
    }
    this->m_mainLayer->addChild(previewBg);
    this->m_mainLayer->addChild(previewTip);
    this->m_mainLayer->addChild(this->m_previewLabel);
    this->m_buttonMenu->addChild(labelInput);
    this->m_buttonMenu->addChild(scaleInput);
    if(mode == 0) {
        this->setTitle("Add Splash", "goldFont.fnt", 1);
        auto addSpr = ButtonSprite::create("Add");
        auto addBtn = CCMenuItemSpriteExtra::create(
            addSpr,
            this,
            menu_selector(EditEntriesLayer::addSplash)
        );
        addBtn->setPosition({offset.x, offset.y + -120});
        this->m_buttonMenu->addChild(addBtn);
    } else if(mode == 1) {
        // auto edit_label = CCLabelBMFont::create("Edit Splash", "goldFont.fnt");
        // edit_label->setPosition({offset.x, offset.y + 65 + 60});
        this->setTitle("Edit Splash", "goldFont.fnt", 1);
        labelInput->setString(this->m_node->getValue().at(this->m_index).at(0).c_str());
        scaleInput->setString(this->m_node->getValue().at(this->m_index).at(1).c_str());
        this->m_previewLabel->setString(this->m_node->getValue().at(this->m_index).at(0).c_str());
        this->m_previewLabel->setScale(std::stof(this->m_node->getValue().at(this->m_index).at(1).c_str()));
        auto editSpr = ButtonSprite::create("Edit");
        auto editBtn = CCMenuItemSpriteExtra::create(
            editSpr,
            this,
            menu_selector(EditEntriesLayer::editSplash)
        );
        editBtn->setPosition({offset.x, offset.y + -120});
        this->m_buttonMenu->addChild(editBtn);
    } else {
        this->keyBackClicked();
    }
    auto splashDelegate = new EditEntriesLayer::SplashInputDelegate();
    labelInput->getInputNode()->setDelegate(splashDelegate);
    auto scaleDelegate = new EditEntriesLayer::ScaleInputDelegate();
    scaleInput->getInputNode()->setDelegate(scaleDelegate);
#ifdef GEODE_IS_MACOS
    if(!Mod::get()->getSettingValue<bool>("dis-anim")) {
        this->m_previewLabel->runAction(CCRepeatForever::create(CCSequence::create(
            cocos2d::CCScaleTo::create(Mod::get()->getSettingValue<double>("animation-length"), std::stof(Mod::get()->getSavedValue<std::vector<std::vector<std::string>>>("splashes-vector").at(splashIndex).at(1)) + Mod::get()->getSettingValue<double>("animation-scale")),
            cocos2d::CCScaleTo::create(Mod::get()->getSettingValue<double>("animation-length"), std::stof(Mod::get()->getSavedValue<std::vector<std::vector<std::string>>>("splashes-vector").at(splashIndex).at(1))),
            nullptr
        )))->setTag(1);
    }
#else
    CCActionInterval* inEasing = EasingsPreview::returnEasingIn(Mod::get()->getSettingValue<int64_t>("easing-in"), this->m_previewLabel);
    CCActionInterval* outEasing = EasingsPreview::returnEasingOut(Mod::get()->getSettingValue<int64_t>("easing-out"), this->m_previewLabel);
    if(!Mod::get()->getSettingValue<bool>("dis-anim")) {
        this->m_previewLabel->runAction(CCRepeatForever::create(CCSequence::create(
            inEasing,
            outEasing,
            nullptr
        )))->setTag(1);
    }
#endif
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

    std::vector<std::vector<std::string>> v = this->m_node->getValue();
    std::vector<std::string> v_an;
    v_an.push_back(splash);
    v_an.push_back(scale);
    v.push_back(v_an);
    this->m_node->setValue(v);
    this->m_previousPopup->updateSplashesList(offset.x, offset.y, 320, 225);
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
    std::vector<std::vector<std::string>> v = this->m_node->getValue();
    std::vector<std::string> v_an;
    v_an.push_back(splash);
    v_an.push_back(scale);
    v.at(this->m_index) = v_an;
    this->m_node->setValue(v);
    this->m_previousPopup->updateSplashesList(offset.x, offset.y, 320, 225);
    this->m_node->dispatchChangedPublic();
    this->m_previousPopup->checkForChanges();
    this->onClose(nullptr);
}

void EditEntriesLayer::SplashInputDelegate::textChanged(CCTextInputNode* p0) {
    std::string string = p0->getString();
    if(string.empty()) {
        static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_previewLabel->setString(fmt::format("{}", static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_defaultPreviewPlaceholder).c_str());
    } else {
        static_cast<EditEntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_previewLabel->setString(fmt::format("{}", string).c_str());
    }
}

void EditEntriesLayer::ScaleInputDelegate::textChanged(CCTextInputNode* p0) {
    auto dis_anim = Mod::get()->getSettingValue<bool>("dis-anim");
    float scale;
    if(p0->getString().empty() || p0->getString() == "0.") {
        return;
    } else if(p0->getString() == "1.") {
        return;
    } else if(p0->getString() == ".") {
        p0->setString("");
        return;
    } else {
        scale = std::stof(p0->getString());
    }

    if(scale > 1.0f) {
        p0->setString("1.0");
    } else {
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