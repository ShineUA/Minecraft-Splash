#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/cocos/actions/CCActionInterval.h>
#include <random>
#include <string>
#include <cstring>



// std::array<std::array<std::string, 2>, 2> default_splashes = {{
// 	{"Also try minecraft...", "0.6"},
// 	{"Also try terraria...", "0.6"}
// }};

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
			// std::uniform_int_distribution<> distr(0, default_splashes.size() - 1); 
			std::uniform_int_distribution<> distr(0, 39);
			random_label = distr(gen);
			onOpenRandom = true;
		}

		// random_label = 1;

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
		
		// label->setScale(std::stof((default_splashes[0][1])));

		// char* text = new char[default_splashes[random_label][0].size() + 1];

		// std::strcpy(text, default_splashes[random_label][0].c_str());

		// label->setString(text);

		// delete[] text;

		label->setScale(0.6);

		switch (random_label)
		{
		case 0:
			label->setString("Also try minecraft...");
			break;
		case 1:
			label->setString("Also try terraria...");
			break;
		case 2:
			label->setString("Go touch some grass...");
			break;
		case 3:
			label->setString("FIRE IN THE HOLE!!!!");
			break;
		case 4:
			label->setString("I'm verified THE GOLDEN LETS GO!");
			label->setScale(0.35f);
			break;
		case 5:
			label->setString("Also try the impossible game...");
			label->setScale(0.45f);
			break;
		case 6:
			label->setString("WATER ON THE HILL!!!");
			break;
		case 7:
			label->setString("Korivka top!");
			break;
		case 8:
			label->setString("Chomu ne na fronti?");
			break;
		case 9:
			label->setString("jump on the spike to win...");
			label->setScale(0.5f);
			break;
		case 10:
			label->setString("try Tidal wave if you're new...");
			label->setScale(0.45f);
			break;
		case 11:
			label->setString("try Bloodbath if you're new...");
			label->setScale(0.45f);
			break;
		case 12:
			label->setString("don't crash on 99%...");
			break;
		case 13:
			label->setString("lobotomy dash...");
			break;
		case 14:
			label->setString("also try star echo...");
			break;
		case 15:
			label->setString("RubRubRubRubRub");
			break;
		case 16:
			label->setString("There's nothing we can do...");
			label->setScale(0.45f);
			break;
		case 17:
			label->setString("Vinovat neiron...");
			break;
		case 18:
			label->setString("We are from Geometry Dash Ukraine...");
			label->setScale(0.35f);
			break;
		case 19:
			label->setString("muplan challenge...");
			break;
		case 20:
			label->setString("Ho hey!");
			break;
		case 21:
			label->setString("Again? Really?");
			break;
		case 22:
			label->setString("Continue?");
			break;
		case 23:
			label->setString("GGWP");
			break;
		case 24:
			label->setString("LOL");
			break;
		case 25:
			label->setString("Take a break...");
			break;
		case 26:
			label->setString("Not ok...");
			break;
		case 27:
			label->setString("You ok?");
			break;
		case 28:
			label->setString("BASED");
			break;
		case 29:
			label->setString("el pepe");
			break;
		case 30:
			label->setString("Harder than FNF");
			break;
		case 31:
			label->setString("I am Batman");
			break;
		case 32:
			label->setString("huhu yo");
			break;
		case 33:
			label->setString("Kappa");
			break;
		case 34:
			label->setString("pogchamp");
			break;
		case 35:
			label->setString("Press alt + f4 for secret way");
			label->setScale(0.45f);
			break;
		case 36:
			label->setString("Take a break!");
			break;
		case 37:
			label->setString("Time to go outside...");
			break;
		case 38:
			label->setString("To be continued...");
			break;
		case 39:
			label->setString("youre going to brazil");
			break;
		}

		label->runAction(CCRepeatForever::create(CCSequence::create(
			CCEaseOut::create(CCScaleTo::create(0.6f, label->getScale() + 0.05f), 0.6f),
			CCEaseOut::create(CCScaleTo::create(0.6f, label->getScale()), 0.6f),
			nullptr
		)));

		label->setZOrder(3);
		label->setID("minecraft-label");
		label->setPosition(posX, posY);
		
		this->addChild(label);
		return true;
	}
};

class $modify(PauseLayer) {
	void onQuit(CCObject* sender) {
		std::random_device rd; 
		std::mt19937 gen(rd()); 
		// std::uniform_int_distribution<> distr(0, default_splashes.size() - 1); 
		std::uniform_int_distribution<> distr(0, 39); 
		random_label = distr(gen);
		PauseLayer::onQuit(sender);
	}
};