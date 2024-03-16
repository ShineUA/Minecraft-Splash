#include "EntriesLayer.h"

#include "../tools/Easings.h"
#include "../main.h"
#include <random>

EntriesLayer* EntriesLayer::create(ArrayListValue* save, int index, int mode, SplashesListPopup* prev_popup) {
    EntriesLayer* ret = new EntriesLayer();
    if (ret && ret->init(435.f, 285.f, save, index, mode, prev_popup)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool EntriesLayer::setup(ArrayListValue* save, int index, int mode, SplashesListPopup* prev_popup) {
    this->m_save = save;

    this->m_prev_popup = prev_popup;

    this->setZOrder(160);
    this->m_index = index;
    if(mode == 0) {
        this->setTitle("Add Splash", "goldFont.fnt", 1);

        auto splash_delegate = new EntriesLayer::SplashInputDelegate();

        auto label_input = InputNode::create(300, "Splash Text", "bigFont.fnt", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz,'.!?0123456789 ", 40);
        label_input->setPositionY(85);
        label_input->setID("splash-text");
        label_input->getInput()->setDelegate(splash_delegate);
        
        auto scale_delegate = new EntriesLayer::ScaleInputDelegate();

        auto scale_input = InputNode::create(50, "Scale", "bigFont.fnt", "0123456789.", 4);
        scale_input->getInput()->setLabelPlaceholderScale(0.4);
        scale_input->getInput()->setMaxLabelScale(0.5);
        scale_input->getInput()->setDelegate(scale_delegate);
        scale_input->setPositionY(50);
        scale_input->setScale(0.8);
        scale_input->setID("scale");

        auto preview_bg = CCScale9Sprite::create("GJ_square05.png");
        preview_bg->setPosition({offset.x, offset.y - 50.f});
        preview_bg->setContentSize(ccp(205, 100));

        auto preview_tip = CCLabelBMFont::create("Tip: The text shouldn't extend\nbeyond the edges of the square", "bigFont.fnt");
        preview_tip->setScale(0.35f);
        preview_tip->setOpacity(150);
        preview_tip->setPosition({offset.x, offset.y + 15.f});

        this->m_preview_label = CCLabelBMFont::create(fmt::format("{}", this->m_def_preview_placeholder).c_str(), "goldFont.fnt");
        this->m_preview_label->setPosition(preview_bg->getPosition());
        this->m_preview_label->setScale(this->m_def_preview_scale);

        if(Mod::get()->getSettingValue<bool>("new-appearance")) {
            this->m_preview_label->setRotation(-15.f);
        } else {
            this->m_preview_label->setRotation(-9.f);
        }

        CCActionInterval* inEasing = EasingsPreview::returnEasingIn(Mod::get()->getSettingValue<int64_t>("easing-in"), this->m_preview_label);
		CCActionInterval* outEasing = EasingsPreview::returnEasingOut(Mod::get()->getSettingValue<int64_t>("easing-out"), this->m_preview_label);

		if(!Mod::get()->getSettingValue<bool>("dis-anim")) {
			this->m_preview_label->runAction(CCRepeatForever::create(CCSequence::create(
				inEasing,
				outEasing,
				nullptr
			)))->setTag(1);
		}

        auto add_spr = ButtonSprite::create("Add");
        auto add_btn = CCMenuItemSpriteExtra::create(
            add_spr,
            this,
            menu_selector(EntriesLayer::addSplash)
        );
        add_btn->setPositionY(-120);

        this->m_mainLayer->addChild(preview_bg);
        this->m_mainLayer->addChild(preview_tip);
        this->m_mainLayer->addChild(this->m_preview_label);

        this->m_buttonMenu->addChild(label_input);
        this->m_buttonMenu->addChild(scale_input);
        this->m_buttonMenu->addChild(add_btn);
    } else if(mode == 1) {
        // auto edit_label = CCLabelBMFont::create("Edit Splash", "goldFont.fnt");
        // edit_label->setPosition({offset.x, offset.y + 65 + 60});
        this->setTitle("Edit Splash", "goldFont.fnt", 1);

        auto splash_delegate = new EntriesLayer::SplashInputDelegate();

        auto label_input = InputNode::create(300, "Splash Text", "bigFont.fnt", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz,.!@%{}()[]$|\\/&;:+<>№=*^~\"'-_`0123456789 ", 40);
        label_input->setPositionY(85);
        label_input->setID("splash-text");
        label_input->setString(this->m_save->getArray().at(this->m_index).at(0).c_str());
        label_input->getInput()->setDelegate(splash_delegate);
        
        auto scale_delegate = new EntriesLayer::ScaleInputDelegate();

        auto scale_input = InputNode::create(50, "Scale", "bigFont.fnt", "0123456789.", 4);
        scale_input->getInput()->setLabelPlaceholderScale(0.4);
        scale_input->getInput()->setMaxLabelScale(0.5);
        scale_input->setString(this->m_save->getArray().at(this->m_index).at(1).c_str());
        scale_input->getInput()->setDelegate(scale_delegate);
        scale_input->setPositionY(50);
        scale_input->setScale(0.8);
        scale_input->setID("scale");

        auto preview_bg = CCScale9Sprite::create("GJ_square05.png");
        preview_bg->setPosition({offset.x, offset.y - 50.f});
        preview_bg->setContentSize(ccp(205, 100));

        auto preview_tip = CCLabelBMFont::create("Tip: The text shouldn't extend\nbeyond the edges of the square", "bigFont.fnt");
        preview_tip->setScale(0.35f);
        preview_tip->setOpacity(150);
        preview_tip->setPosition({offset.x, offset.y + 15.f});

        this->m_preview_label = CCLabelBMFont::create(this->m_save->getArray().at(this->m_index).at(0).c_str(), "goldFont.fnt");
        this->m_preview_label->setPosition(preview_bg->getPosition());
        this->m_preview_label->setScale(std::stof(this->m_save->getArray().at(this->m_index).at(1).c_str()));

        if(Mod::get()->getSettingValue<bool>("new-appearance")) {
            this->m_preview_label->setRotation(-15.f);
        } else {
            this->m_preview_label->setRotation(-9.f);
        }

        CCActionInterval* inEasing = EasingsPreview::returnEasingIn(Mod::get()->getSettingValue<int64_t>("easing-in"), this->m_preview_label);
		CCActionInterval* outEasing = EasingsPreview::returnEasingOut(Mod::get()->getSettingValue<int64_t>("easing-out"), this->m_preview_label);

		if(!Mod::get()->getSettingValue<bool>("dis-anim")) {
			this->m_preview_label->runAction(CCRepeatForever::create(CCSequence::create(
				inEasing,
				outEasing,
				nullptr
			)))->setTag(1);
		}

        auto edit_spr = ButtonSprite::create("Edit");
        auto edit_btn = CCMenuItemSpriteExtra::create(
            edit_spr,
            this,
            menu_selector(EntriesLayer::editSplash)
        );
        edit_btn->setPositionY(-120);

        this->m_mainLayer->addChild(preview_bg);
        this->m_mainLayer->addChild(preview_tip);
        this->m_mainLayer->addChild(this->m_preview_label);

        this->m_buttonMenu->addChild(label_input);
        this->m_buttonMenu->addChild(scale_input);
        this->m_buttonMenu->addChild(edit_btn);
    } else {
        this->keyBackClicked();
    }
    return true;
}

void EntriesLayer::addSplash(CCObject* sender) {
    auto splash = static_cast<InputNode*>(this->m_buttonMenu->getChildByID("splash-text"))->getString();
    auto scale = static_cast<InputNode*>(this->m_buttonMenu->getChildByID("scale"))->getString();
    if(scale.empty() || splash.empty() || scale.ends_with(".") || std::stof(scale) <= 0) {
        return FLAlertLayer::create(
            "Error!",
            "Please fill all input fields <cr>correctly!</c>",
            "OK"
        )->show();
    }
    std::vector<std::vector<std::string>> v = this->m_save->getArray();
    std::vector<std::string> v_an;
    v_an.push_back(splash);
    v_an.push_back(scale);
    v.push_back(v_an);
    this->m_save->setArray(v);
    Mod::get()->setSavedValue<std::vector<std::vector<std::string>>>("splashes-vector", v);
    this->m_prev_popup->updateSplashesList();
    this->onClose(nullptr);
}

void EntriesLayer::editSplash(CCObject* sender) {
    auto splash = static_cast<InputNode*>(this->m_buttonMenu->getChildByID("splash-text"))->getString();
    auto scale = static_cast<InputNode*>(this->m_buttonMenu->getChildByID("scale"))->getString();
    if(scale.empty() || splash.empty() || scale.ends_with(".") || std::stof(scale) <= 0) {
        return FLAlertLayer::create(
            "Error!",
            "Please fill all input fields <cr>correctly!</c>",
            "OK"
        )->show();
    }
    std::vector<std::vector<std::string>> v = this->m_save->getArray();
    std::vector<std::string> v_an;
    v_an.push_back(splash);
    v_an.push_back(scale);
    v.at(this->m_index) = v_an;
    this->m_save->setArray(v);
    Mod::get()->setSavedValue<std::vector<std::vector<std::string>>>("splashes-vector", v);
    this->m_prev_popup->updateSplashesList();
    this->onClose(nullptr);
}

void EntriesLayer::SplashInputDelegate::textChanged(CCTextInputNode* p0) {
    std::string string = p0->getString();
    if(string.empty()) {
        static_cast<EntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_preview_label->setString(fmt::format("{}", static_cast<EntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_def_preview_placeholder).c_str());
    } else {
        static_cast<EntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_preview_label->setString(fmt::format("{}", string).c_str());
    }
}

void EntriesLayer::ScaleInputDelegate::textChanged(CCTextInputNode* p0) {
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
            static_cast<EntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_preview_label->setScale(scale);
            if(!dis_anim) {
                static_cast<EntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_preview_label->stopActionByTag(1);
                CCActionInterval* inEasing = EasingsPreview::returnEasingIn(Mod::get()->getSettingValue<int64_t>("easing-in"), static_cast<EntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_preview_label);
		        CCActionInterval* outEasing = EasingsPreview::returnEasingOut(Mod::get()->getSettingValue<int64_t>("easing-out"), static_cast<EntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_preview_label);
                static_cast<EntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_preview_label->runAction(CCRepeatForever::create(CCSequence::create(
                    inEasing,
                    outEasing,
                    nullptr
                )))->setTag(1);
            }
        } else {
            static_cast<EntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_preview_label->setScale(static_cast<EntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_def_preview_scale);
            if(!dis_anim) {
                static_cast<EntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_preview_label->stopActionByTag(1);
                CCActionInterval* inEasing = EasingsPreview::returnEasingIn(Mod::get()->getSettingValue<int64_t>("easing-in"), static_cast<EntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_preview_label);
                CCActionInterval* outEasing = EasingsPreview::returnEasingOut(Mod::get()->getSettingValue<int64_t>("easing-out"), static_cast<EntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_preview_label);
                static_cast<EntriesLayer*>(p0->getParent()->getParent()->getParent()->getParent())->m_preview_label->runAction(CCRepeatForever::create(CCSequence::create(
                    inEasing,
                    outEasing,
                    nullptr
                )))->setTag(1);
            }
        }
    }
}