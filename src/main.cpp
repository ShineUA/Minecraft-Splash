#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/cocos/actions/CCActionInterval.h>
#include <random>
#include <string>
#include <cstring>



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

bool onOpenRandom = false;
int random_label;

using namespace geode::prelude;


class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;

		auto main_title = this->getChildByID("main-title");

		if(!onOpenRandom) {
			std::random_device rd; 
			std::mt19937 gen(rd()); 
			std::uniform_int_distribution<> distr(0, default_splashes.size() - 1); 
			random_label = distr(gen);
			onOpenRandom = true;
		}

		auto appearence_setting = Mod::get()->getSettingValue<bool>("appearance");

		auto label = CCLabelBMFont::create("", "goldFont.fnt");
		auto winSize = CCDirector::get()->getWinSize();
		auto density = winSize.width / winSize.height;
		float posX, posY;

		if(appearence_setting){
			posX = main_title->getPositionX() + 167.f;
			posY = main_title->getPositionY() - 11.f;
			label->setRotation(-15.f);
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
			label->setRotation(-9.f);
		}
		
		label->setScale(std::stof((default_splashes[random_label][1])));

		char* text = new char[default_splashes[random_label][0].size() + 1];

		std::strcpy(text, default_splashes[random_label][0].c_str());

		label->setString(text);

		delete[] text;

		// label->setScale(0.6f);

		auto animation_speed = Mod::get()->getSettingValue<double>("animation-speed");

		label->runAction(CCRepeatForever::create(CCSequence::create(
			CCEaseOut::create(CCScaleTo::create(animation_speed, label->getScale() + 0.05f), animation_speed),
			CCEaseOut::create(CCScaleTo::create(animation_speed, label->getScale()), animation_speed),
			nullptr
		)));

		label->setZOrder(3);
		label->setID("minecraft-label");
		label->setPosition(posX, posY);

		// Button & menu

		this->addChild(label);
		return true;
	}
};

class $modify(PauseLayer) {
	void onQuit(CCObject* sender) {
		std::random_device rd; 
		std::mt19937 gen(rd()); 
		std::uniform_int_distribution<> distr(0, default_splashes.size() - 1); 
		random_label = distr(gen);
		PauseLayer::onQuit(sender);
	}
};