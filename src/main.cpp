#include "main.h"

#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/cocos/actions/CCActionInterval.h>
#include <random>
#include <string>
#include <cstring>
#include <Geode/cocos/base_nodes/Layout.hpp>
#include <Geode/binding/FLAlertLayerProtocol.hpp>
#include "layers/SettingsLayer.h"



std::array<std::array<std::string, 2>, 40> default_splashes = {{
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
}};

int random_splash;

bool onOpenRandom = false;

using namespace geode::prelude;


class $modify(MSMenuLayer, MenuLayer) {

	void onSettingsLayer(CCObject* sender){
		auto settingsLayer = SettingsLayer::create();
		auto settingsLayerBG = SettingsLayerBG::create();
		settingsLayerBG->addChild(settingsLayer);
		CCScene::get()->addChild(settingsLayerBG);
	}

	bool init() {
		if (!MenuLayer::init()) return false;

		auto main_title = this->getChildByID("main-title");

		if(!Mod::get()->setSavedValue<bool>("not-first-boot", true)) {
			Mod::get()->setSavedValue<bool>("new-appearance", false);
			Mod::get()->setSavedValue<bool>("dis-anim", false);
			Mod::get()->setSavedValue<float>("animation-length", 0.6f);
			Mod::get()->setSavedValue<float>("animation-scale", 0.05f);
			std::stringstream ss;
			for(int i = 0; i < default_splashes.size(); i++) {
				ss << "splash-" << i;
				Mod::get()->setSavedValue<std::string>(ss.str().c_str(), default_splashes[i][0]);
				ss << "-size";
				Mod::get()->setSavedValue<std::string>(ss.str().c_str(), default_splashes[i][1]);
				ss.str("");
			}
			Mod::get()->setSavedValue<int>("amount-of-splashes", default_splashes.size());
		}

		if(!onOpenRandom) {
			std::random_device rd; 
			std::mt19937 gen(rd()); 
			std::uniform_int_distribution<> distr(0, Mod::get()->getSavedValue<int>("amount-of-splashes") - 1); 
			random_splash = distr(gen);
			onOpenRandom = true;
		}

		auto appearence_setting = Mod::get()->getSavedValue<bool>("new-appearance");

		auto splash = CCLabelBMFont::create("", "goldFont.fnt");
		auto winSize = CCDirector::get()->getWinSize();
		auto density = winSize.width / winSize.height;
		float posX, posY;

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
		
		char* text = new char[Mod::get()->getSavedValue<int>("amount-of-splashes") + 1];

		std::stringstream sss;

		sss << "splash-" << random_splash;
		
		auto label_text = Mod::get()->getSavedValue<std::string>(sss.str().c_str());

		std::strcpy(text, label_text.c_str());

		splash->setString(text);

		sss << "-size";

		delete[] text;
		
		auto size = Mod::get()->getSavedValue<std::string>(sss.str().c_str());

		splash->setScale(std::stof((size)));

		auto animation_length = Mod::get()->getSavedValue<float>("animation-length");

		if(!Mod::get()->getSavedValue<bool>("dis-anim")) {
			splash->runAction(CCRepeatForever::create(CCSequence::create(
				CCEaseOut::create(CCScaleTo::create(animation_length, splash->getScale() + Mod::get()->getSavedValue<float>("animation-scale")), animation_length),
				CCEaseOut::create(CCScaleTo::create(animation_length, splash->getScale()), animation_length),
				nullptr
			)))->setTag(1);
		}
		
		splash->setZOrder(3);
		splash->setID("minecraft-splash");
		splash->setPosition(posX, posY);

		auto spr = CCSprite::create("Cust_setBtn_001.png"_spr);
		auto btn = CCMenuItemSpriteExtra::create(
        	spr, this, menu_selector(MSMenuLayer::onSettingsLayer)
		);

		auto dailyChestButton = this->getChildByID("right-side-menu")->getChildByID("daily-chest-button");
		btn->setPositionX(dailyChestButton->getPositionX());
		btn->setPositionY(dailyChestButton->getPositionY() - 55.f);
		btn->setAnchorPoint(dailyChestButton->getAnchorPoint());

		getChildByID("right-side-menu")->addChild(btn);
		addChild(splash);
		return true;
	}
};

class $modify(PauseLayer) {
	void onQuit(CCObject* sender) {
		std::random_device rd; 
		std::mt19937 gen(rd()); 
		std::uniform_int_distribution<> distr(0, Mod::get()->getSavedValue<int>("amount-of-splashes") - 1); 
		random_splash = distr(gen);
		PauseLayer::onQuit(sender);
	}
};