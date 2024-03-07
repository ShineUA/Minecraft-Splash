#include "EntriesLayer.h"

#include "../tools/Easings.h"
#include "../main.h"
#include <random>

EntriesLayer* EntriesLayer::create(ArrayListValue* save, int index, int mode) {
    EntriesLayer* ret = new EntriesLayer();
    if (ret && ret->init(save, index, mode)) {
        ret->autorelease();
    } else {
        delete ret;
        ret = nullptr;
    }
    return ret;
}

bool EntriesLayer::init(ArrayListValue* save, int index, int mode) {
    if (!this->initWithColor({0, 0, 0, 75})) return false;
    this->m_save = save;

    const CCPoint offset = CCDirector::get()->getWinSize() / 2.f;

    this->m_noElasticity = true;
    geode::cocos::handleTouchPriority(this);
    this->registerWithTouchDispatcher();
    this->setTouchEnabled(true);
    this->setKeypadEnabled(true);
    this->setZOrder(150);

    auto layer = CCLayer::create();
    auto menu = CCMenu::create();
    this->m_mainLayer = layer;
    this->m_buttonMenu = menu;
    this->m_index = index;

    auto bg = CCScale9Sprite::create("GJ_square01.png");
    bg->setPosition(offset);

    layer->addChild(bg);

    auto closeSpr = CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png");
    auto closeBtn = CCMenuItemSpriteExtra::create(
        closeSpr,
        this,
        menu_selector(EntriesLayer::onExit)
    );
    closeBtn->setScale(0.8f);
    closeBtn->m_baseScale = 0.8f;
    menu->addChild(closeBtn);

    if(mode == 0) {
        bg->setContentSize(ccp(435, 285));
        closeBtn->setPosition({-215, 140});

        auto add_label = CCLabelBMFont::create("Add Splash", "goldFont.fnt");
        add_label->setPosition({offset.x, offset.y + 65 + 60});

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

        layer->addChild(preview_bg);
        layer->addChild(add_label);
        layer->addChild(preview_tip);
        layer->addChild(this->m_preview_label);

        menu->addChild(label_input);
        menu->addChild(scale_input);
        menu->addChild(add_btn);
    } else if(mode == 1) {
        bg->setContentSize(ccp(435, 285));
        closeBtn->setPosition({-215, 140});

        auto edit_label = CCLabelBMFont::create("Edit Splash", "goldFont.fnt");
        edit_label->setPosition({offset.x, offset.y + 65 + 60});

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

        auto edit_spr = ButtonSprite::create("Edit");
        auto edit_btn = CCMenuItemSpriteExtra::create(
            edit_spr,
            this,
            menu_selector(EntriesLayer::editSplash)
        );
        edit_btn->setPositionY(-120);

        layer->addChild(preview_bg);
        layer->addChild(edit_label);
        layer->addChild(preview_tip);
        layer->addChild(this->m_preview_label);

        menu->addChild(label_input);
        menu->addChild(scale_input);
        menu->addChild(edit_btn);
    } else if(mode == 2) {
        closeBtn->setVisible(false);
        bg->setVisible(false);
        this->setOpacity(0);
        // bg->setContentSize(ccp(190, 90));
        // auto label = CCLabelBMFont::create(fmt::format("Are you sure you want\nto delete splash {}?", this->m_index + 1).c_str(), "bigFont.fnt");
        // label->setPosition({offset.x, offset.y + 20});
        // label->setScale(0.425f);

        // auto yesSpr = ButtonSprite::create("Yes");
        // auto yesBtn = CCMenuItemSpriteExtra::create(
        //     yesSpr,
        //     this,
        //     menu_selector(EntriesLayer::removeSplash)
        // );

        // auto noSpr = ButtonSprite::create("No");
        // auto noBtn = CCMenuItemSpriteExtra::create(
        //     noSpr,
        //     this,
        //     menu_selector(EntriesLayer::onExit)
        // );

        // layer->addChild(label);
        
        // menu->addChild(yesBtn);
        // menu->addChild(noBtn);
        geode::createQuickPopup(
            "Info",
            fmt::format("Are you sure you want to delete splash {}?", this->m_index + 1).c_str(),
            "Yes", "No",
            [this](auto, bool btn2) {
                if(!btn2) {
                    this->removeSplash(nullptr);
                } else {
                    this->keyBackClicked();
                }
            }
        );
    } else {
        this->keyBackClicked();
    }

    layer->addChild(menu);
    this->addChild(layer);

    return true;
}

void EntriesLayer::keyBackClicked() {
    this->setTouchEnabled(false);
    this->setKeypadEnabled(false);
    this->removeFromParentAndCleanup(true);
    auto popup = SplashesListPopup::create(this->m_save);
    CCScene::get()->addChild(popup);
}

void EntriesLayer::onExit(CCObject* sender) {
    this->keyBackClicked();
}

void EntriesLayer::addSplash(CCObject* sender) {
    auto splash = static_cast<InputNode*>(this->m_buttonMenu->getChildByID("splash-text"))->getString();
    auto scale = static_cast<InputNode*>(this->m_buttonMenu->getChildByID("scale"))->getString();
    if(scale.empty() || splash.empty() || scale.ends_with(".")) {
        FLAlertLayer::create(
            "Error!",
            "Please fill all input fields <cr>correctly!</c>",
            "OK"
        )->show();
        return;
    }
    std::vector<std::vector<std::string>> v = this->m_save->getArray();
    std::vector<std::string> v_an;
    v_an.push_back(splash);
    v_an.push_back(scale);
    v.push_back(v_an);
    this->m_save->setArray(v);
    Mod::get()->setSavedValue<std::vector<std::vector<std::string>>>("splashes-vector", v);
    this->keyBackClicked();
}

void EntriesLayer::editSplash(CCObject* sender) {
    auto splash = static_cast<InputNode*>(this->m_buttonMenu->getChildByID("splash-text"))->getString();
    auto scale = static_cast<InputNode*>(this->m_buttonMenu->getChildByID("scale"))->getString();
    if(scale.empty() || splash.empty() || scale.ends_with(".")) {
        FLAlertLayer::create(
            "Error!",
            "Please fill all input fields <cr>correctly!</c>",
            "OK"
        )->show();
        return;
    }
    std::vector<std::vector<std::string>> v = this->m_save->getArray();
    std::vector<std::string> v_an;
    v_an.push_back(splash);
    v_an.push_back(scale);
    v.at(this->m_index) = v_an;
    this->m_save->setArray(v);
    Mod::get()->setSavedValue<std::vector<std::vector<std::string>>>("splashes-vector", v);
    this->keyBackClicked();
}

void EntriesLayer::removeSplash(CCObject* sender) {
    std::vector<std::vector<std::string>> v = this->m_save->getArray();
    v.erase(v.begin() + this->m_index);
    this->m_save->setArray(v);
    auto am_of_spl = v.size();
    if(am_of_spl == 1) {
        random_splash = 0;
    } else {
        std::random_device rd; 
        std::mt19937 gen(rd()); 
        std::uniform_int_distribution<std::mt19937::result_type> distr(0, am_of_spl - 1); 
        random_splash = distr(gen);
    }
    Mod::get()->setSavedValue<std::vector<std::vector<std::string>>>("splashes-vector", v);
    this->keyBackClicked();
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