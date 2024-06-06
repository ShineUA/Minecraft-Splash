#include "main.h"

$on_mod(Loaded) {
    Mod::get()->addCustomSetting<ArrayListValue>("splashes", default_splashes);
	Mod::get()->addCustomSetting<SectionSettingValue>("main-label", "none");
	Mod::get()->addCustomSetting<SectionSettingValue>("splashes-label", "none");
}

$execute {
	if(!Mod::get()->setSavedValue<bool>("not-first-boot-after-1.2.2", true)) {
		Mod::get()->setSavedValue<std::vector<std::vector<std::string>>>("splashes-vector", default_splashes);
	}
}

class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;
		if(!onOpenRandom) {
			if(Mod::get()->getSavedValue<std::vector<std::vector<std::string>>>("splashes-vector").size() == (size_t)1) {
				splashIndex = 0;
			} else {
				std::random_device rd; 
				std::mt19937 gen(rd()); 
				std::uniform_int_distribution<std::mt19937::result_type> distr(0, Mod::get()->getSavedValue<std::vector<std::vector<std::string>>>("splashes-vector").size() - 1); 
				splashIndex = distr(gen);
			}
			onOpenRandom = true;
		}
		auto splash = CCLabelBMFont::create(Mod::get()->getSavedValue<std::vector<std::vector<std::string>>>("splashes-vector")[splashIndex][0].c_str(), "goldFont.fnt");
		splash->setScale(std::stof(Mod::get()->getSavedValue<std::vector<std::vector<std::string>>>("splashes-vector")[splashIndex][1]));
		if(Mod::get()->getSettingValue<bool>("new-appearance")){
			splash->setPosition({this->getChildByID("main-title")->getPositionX() + 167.f, this->getChildByID("main-title")->getPositionY() - 11.f});
			splash->setRotation(-15.f);
		} else {
			if(CCDirector::get()->getWinSize().width / CCDirector::get()->getWinSize().height < 1.7f && CCDirector::get()->getWinSize().width / CCDirector::get()->getWinSize().height >= 1.5f) {
				splash->setPosition({CCDirector::get()->getWinSize().width / 2 + 154.f, CCDirector::get()->getWinSize().height / 2 + 73.f});
			} else if(CCDirector::get()->getWinSize().width / CCDirector::get()->getWinSize().height < 1.5f) {
				splash->setPosition({CCDirector::get()->getWinSize().width / 2 + 132.f, CCDirector::get()->getWinSize().height / 2 + 86.f});
			} else {
				splash->setPosition({CCDirector::get()->getWinSize().width / 2 + 183.f, CCDirector::get()->getWinSize().height / 2 + 71.f});
			}
			splash->setRotation(-9.f);
		}
#ifdef GEODE_IS_MACOS
		if(!Mod::get()->getSettingValue<bool>("dis-anim")) {
			splash->runAction(CCRepeatForever::create(CCSequence::create(
				cocos2d::CCScaleTo::create(Mod::get()->getSettingValue<double>("animation-length"), std::stof(Mod::get()->getSavedValue<std::vector<std::vector<std::string>>>("splashes-vector").at(splashIndex).at(1)) + Mod::get()->getSettingValue<double>("animation-scale")),
				cocos2d::CCScaleTo::create(Mod::get()->getSettingValue<double>("animation-length"), std::stof(Mod::get()->getSavedValue<std::vector<std::vector<std::string>>>("splashes-vector").at(splashIndex).at(1))),
				nullptr
			)));
		}
#else
		CCActionInterval* inEasing = Easings::returnEasingIn(Mod::get()->getSettingValue<int64_t>("easing-in"));
		CCActionInterval* outEasing = Easings::returnEasingOut(Mod::get()->getSettingValue<int64_t>("easing-out"));
		if(!Mod::get()->getSettingValue<bool>("dis-anim")) {
			splash->runAction(CCRepeatForever::create(CCSequence::create(
				inEasing,
				outEasing,
				nullptr
			)));
		}
#endif
		splash->setZOrder(15);
		splash->setID("minecraft-splash");
		addChild(splash);
		return true;
	}
};
class $modify(PauseLayer) {
	void onQuit(CCObject* sender) {
		if(Mod::get()->getSavedValue<std::vector<std::vector<std::string>>>("splashes-vector").size() == (size_t)1) {
			splashIndex = 0;
		} else {
			std::random_device rd; 
			std::mt19937 gen(rd()); 
			std::uniform_int_distribution<std::mt19937::result_type> distr(0, Mod::get()->getSavedValue<std::vector<std::vector<std::string>>>("splashes-vector").size() - 1); 
			splashIndex = distr(gen);
		}
		PauseLayer::onQuit(sender);
	}
};