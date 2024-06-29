#include "main.h"
#include "settings/CustomSettings.h"

$on_mod(Loaded) {
	if(!Mod::get()->setSavedValue<bool>("1.5.0", true)) {
		Mod::get()->setSavedValue<std::vector<std::string>>("splashes-vector", default_splashes);
	}
    Mod::get()->addCustomSetting<ArrayListValue>("splashes", default_splashes);
	Mod::get()->addCustomSetting<SectionSettingValue>("main-label", "none");
	Mod::get()->addCustomSetting<SectionSettingValue>("splashes-label", "none");
}

$execute {
	if(!Mod::get()->setSavedValue<bool>("1.5.0-2", true)) {
		if(CCDirector::get()->getWinSize().width / CCDirector::get()->getWinSize().height < 1.7f && CCDirector::get()->getWinSize().width / CCDirector::get()->getWinSize().height >= 1.5f) {
			Mod::get()->setSavedValue<float>("pos-x", CCDirector::get()->getWinSize().width / 2 + 154.f);
			Mod::get()->setSavedValue<float>("pos-y", CCDirector::get()->getWinSize().height / 2 + 73.f);
		} else if(CCDirector::get()->getWinSize().width / CCDirector::get()->getWinSize().height < 1.5f) {
			Mod::get()->setSavedValue<float>("pos-x", CCDirector::get()->getWinSize().width / 2 + 132.f);
			Mod::get()->setSavedValue<float>("pos-y", CCDirector::get()->getWinSize().height / 2 + 86.f);
		} else {
			Mod::get()->setSavedValue<float>("pos-x", CCDirector::get()->getWinSize().width / 2 + 183.f);
			Mod::get()->setSavedValue<float>("pos-y", CCDirector::get()->getWinSize().height / 2 + 71.f);
		}
		Mod::get()->setSavedValue<float>("rot-x", -9.f);
		Mod::get()->setSavedValue<float>("rot-y", -9.f);
		Mod::get()->setSavedValue<float>("scale-x", 0.6f);
		Mod::get()->setSavedValue<float>("scale-y", 0.6f);
	}
	if(Mod::get()->getSavedValue<std::vector<std::string>>("splashes-vector").size() == (size_t)1) {
		splashIndex = 0;
	} else {
		std::random_device rd;
		std::mt19937 gen(rd()); 
		std::uniform_int_distribution<std::mt19937::result_type> distr(0, Mod::get()->getSavedValue<std::vector<std::string>>("splashes-vector").size() - 1); 
		splashIndex = distr(gen);
	}
}

class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;
		auto splash = CCLabelBMFont::create(Mod::get()->getSavedValue<std::vector<std::string>>("splashes-vector")[splashIndex].c_str(), "goldFont.fnt");
		splash->setScaleX(Mod::get()->getSavedValue<float>("scale-x"));
		splash->setScaleY(Mod::get()->getSavedValue<float>("scale-y"));
		splash->setPosition({Mod::get()->getSavedValue<float>("pos-x"), Mod::get()->getSavedValue<float>("pos-y")});
		splash->setRotationX(Mod::get()->getSavedValue<float>("rot-x"));
		splash->setRotationY(Mod::get()->getSavedValue<float>("rot-y"));
		// if(Mod::get()->getSettingValue<bool>("new-appearance")){
		// 	splash->setPosition({this->getChildByID("main-title")->getPositionX() + 167.f, this->getChildByID("main-title")->getPositionY() - 11.f});
		// 	splash->setRotation(-15.f);
		// } else {
		// 	if(CCDirector::get()->getWinSize().width / CCDirector::get()->getWinSize().height < 1.7f && CCDirector::get()->getWinSize().width / CCDirector::get()->getWinSize().height >= 1.5f) {
		// 		splash->setPosition({CCDirector::get()->getWinSize().width / 2 + 154.f, CCDirector::get()->getWinSize().height / 2 + 73.f});
		// 	} else if(CCDirector::get()->getWinSize().width / CCDirector::get()->getWinSize().height < 1.5f) {
		// 		splash->setPosition({CCDirector::get()->getWinSize().width / 2 + 132.f, CCDirector::get()->getWinSize().height / 2 + 86.f});
		// 	} else {
		// 		splash->setPosition({CCDirector::get()->getWinSize().width / 2 + 183.f, CCDirector::get()->getWinSize().height / 2 + 71.f});
		// 	}
		// 	splash->setRotation(-9.f);
		// }
// #ifdef GEODE_IS_MACOS
// 		if(!Mod::get()->getSettingValue<bool>("dis-anim")) {
// 			splash->runAction(CCRepeatForever::create(CCSequence::create(
// 				cocos2d::CCScaleTo::create(Mod::get()->getSettingValue<double>("animation-length"), std::stof(Mod::get()->getSavedValue<std::vector<std::vector<std::string>>>("splashes-vector").at(splashIndex).at(1)) + Mod::get()->getSettingValue<double>("animation-scale")),
// 				cocos2d::CCScaleTo::create(Mod::get()->getSettingValue<double>("animation-length"), std::stof(Mod::get()->getSavedValue<std::vector<std::vector<std::string>>>("splashes-vector").at(splashIndex).at(1))),
// 				nullptr
// 			)));
// 		}
// #else
// 		CCActionInterval* inEasing = Easings::returnEasingIn(Mod::get()->getSettingValue<int64_t>("easing-in"));
// 		CCActionInterval* outEasing = Easings::returnEasingOut(Mod::get()->getSettingValue<int64_t>("easing-out"));
// 		if(!Mod::get()->getSettingValue<bool>("dis-anim")) {
// 			splash->runAction(CCRepeatForever::create(CCSequence::create(
// 				inEasing,
// 				outEasing,
// 				nullptr
// 			)));
// 		}
// J#endif
		splash->setZOrder(15);
		splash->setID("minecraft-splash"_spr);
		addChild(splash);
		return true;
	}
};
class $modify(PauseLayer) {
	void onQuit(CCObject* sender) {
		if(Mod::get()->getSavedValue<std::vector<std::string>>("splashes-vector").size() == (size_t)1) {
			splashIndex = 0;
		} else {
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<std::mt19937::result_type> distr(0, Mod::get()->getSavedValue<std::vector<std::string>>("splashes-vector").size() - 1); 
			splashIndex = distr(gen);
		}
		PauseLayer::onQuit(sender);
	}
};