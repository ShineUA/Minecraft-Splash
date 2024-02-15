#include "main.h"

#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <random>
#include <string>
#include <cstring>
#include "settings/CustomSettings.h"
#include "tools/Easings.h"


std::vector<std::vector<std::string>> default_splashes = {
	{"Also try minecraft...", "0.6"},
	{"Also try terraria...", "0.6"},
	{"Go touch some grass...", "0.6"},
	{"FIRE IN THE HOLE!!!!", "0.6"},
	{"I'm verified THE GOLDEN LETS GO!", "0.35"},
	{"Also try the impossible game...", "0.45"},
	{"WATER ON THE HILL!!!", "0.6"},
	{"Korivka top!","0.6"},
	{"Chomu ne na fronti?", "0.6"},
	{"jump on the spike to win...", "0.5"},
	{"try Tidal wave if you're new...", "0.45"},
	{"try Bloodbath if you're new...", "0.45"},
	{"don't crash on 99%...", "0.6"},
	{"lobotomy dash...", "0.6"},
	{"also try star echo...", "0.6"},
	{"RubRubRubRubRub", "0.6"},
	{"There's nothing we can do...", "0.45"},
	{"Vinovat neiron...", "0.6"},
	{"We are from Geometry Dash Ukraine...", "0.35"},
	{"muplan challenge...", "0.6"},
	{"Ho hey!", "0.6"},
	{"Again? Really?", "0.6"},
	{"Continue?", "0.6"},
	{"GGWP", "0.6"},
	{"LOL", "0.6"},
	{"Take a break...", "0.6"},
	{"Not ok...", "0.6"},
	{"You ok?", "0.6"},
	{"BASED", "0.6"},
	{"el pepe", "0.6"},
	{"Harder than FNF", "0.6"},
	{"I am Batman", "0.6"},
	{"huhu yo", "0.6"},
	{"Kappa", "0.6"},
	{"pogchamp", "0.6"},
	{"Press alt + f4 for secret way", "0.45"},
	{"Take a break!", "0.6"},
	{"Time to go outside...", "0.6"},
	{"To be continued...", "0.6"},
	{"youre going to brazil", "0.6"}
};

int random_splash;

bool onOpenRandom = false;

using namespace geode::prelude;

$on_mod(Loaded) {
    Mod::get()->addCustomSetting<ArrayListValue>("splashes-vector", default_splashes);
}

class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;

		auto main_title = this->getChildByID("main-title");

		if(!Mod::get()->setSavedValue<bool>("not-first-boot-after-1.2.2", true)) {
			Mod::get()->setSavedValue<std::vector<std::vector<std::string>>>("splashes-vector", default_splashes);
		}

		if(!onOpenRandom) {
			auto am_of_spl = Mod::get()->getSavedValue<std::vector<std::vector<std::string>>>("splashes-vector").size();
			if(am_of_spl == 1) {
				random_splash = 0;
			} else {
				std::random_device rd; 
				std::mt19937 gen(rd()); 
				std::uniform_int_distribution<std::mt19937::result_type> distr(0, am_of_spl - 1); 
				random_splash = distr(gen);
			}
			onOpenRandom = true;
		}

		auto appearence_setting = Mod::get()->getSettingValue<bool>("new-appearance");

		auto splash = CCLabelBMFont::create("", "goldFont.fnt");
		auto winSize = CCDirector::get()->getWinSize();
		auto density = winSize.width / winSize.height;
		float posX;
		float posY;

		if(appearence_setting){
			posX = main_title->getPositionX() + 167.f;
			posY = main_title->getPositionY() - 11.f;
			splash->setRotation(-15.f);
		} else {
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
			splash->setRotation(-9.f);
		}
		
		auto label_text = Mod::get()->getSavedValue<std::vector<std::vector<std::string>>>("splashes-vector")[random_splash][0];

		char* text = new char[Mod::get()->getSavedValue<std::vector<std::vector<std::string>>>("splashes-vector")[random_splash][0].size() + 1];

		std::strcpy(text, label_text.c_str());

		splash->setString(text);

		delete[] text;
		
		auto size = Mod::get()->getSavedValue<std::vector<std::vector<std::string>>>("splashes-vector")[random_splash][1];

		CCActionInterval* inEasing;
		CCActionInterval* outEasing;
		inEasing = Easings::returnEasingIn(Mod::get()->getSettingValue<int64_t>("easing-in"));
		outEasing = Easings::returnEasingOut(Mod::get()->getSettingValue<int64_t>("easing-out"));

		splash->setScale(std::stof((size)));

		auto animation_length = Mod::get()->getSettingValue<double>("animation-length");

		if(!Mod::get()->getSettingValue<bool>("dis-anim")) {
			splash->runAction(CCRepeatForever::create(CCSequence::create(
				inEasing,
				outEasing,
				nullptr
			)));
		}
		
		splash->setZOrder(15);
		splash->setID("minecraft-splash");
		splash->setPosition(posX, posY);
		addChild(splash);
		return true;
	}
};

class $modify(PauseLayer) {
	void onQuit(CCObject* sender) {
		auto am_of_spl = Mod::get()->getSavedValue<std::vector<std::vector<std::string>>>("splashes-vector").size();
		if(am_of_spl == 1) {
			random_splash = 0;
		} else {
			std::random_device rd; 
			std::mt19937 gen(rd()); 
			std::uniform_int_distribution<std::mt19937::result_type> distr(0, am_of_spl - 1); 
			random_splash = distr(gen);
		}
		
		PauseLayer::onQuit(sender);
	}
};