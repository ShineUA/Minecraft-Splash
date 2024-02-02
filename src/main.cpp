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

//  class MySettingValue;

//  class MySettingValue : public SettingValue {
//      // store the current value in some form.
//      // this may be an enum, a class, or
//      // whatever it is your setting needs -
//      // you are free to do whatever!

//  public:
//      bool load(matjson::Value const& json) override {
//          // load the value of the setting from json,
//          // returning true if loading was succesful
//      }
//      bool save(matjson::Value& json) const override {
//          // save the value of the setting into json,
//          // returning true if saving was succesful
//      }
//      SettingNode* createNode(float width) override {
//          return MySettingNode::create(width);
//      }

//      // getters and setters for the value
//  };

//  class MySettingNode : public SettingNode {
//  protected:
//      bool init(MySettingValue* value, float width) {
//          if (!SettingNode::init(value))
//              return false;
        
//          // You may change the height to anything, but make sure to call
//          // setContentSize!
//          this->setContentSize({ width, 40.f });

//          // Set up the UI. Note that Geode provides a background for the
//          // setting automatically

//          return true;
//      }

//      // Whenever the user interacts with your controls, you should call
//      // this->dispatchChanged()

//  public:
//      // When the user wants to save this setting value, this function is
//      // called - this is where you should actually set the value of your
//      // setting
//      void commit() override {
//          // Set the actual value

//          // Let the UI know you have committed the value
//          this->dispatchCommitted();
//      }

//      // Geode calls this to query if the setting value has been changed,
//      // and those changes haven't been committed
//      bool hasUncommittedChanges() override {
//          // todo
//      }

//      // Geode calls this to query if the setting has a value that is
//      // different from its default value
//      bool hasNonDefaultValue() override {
//          // todo
//      }

//      // Geode calls this to reset the setting's value back to default
//      void resetToDefault() override {
//          // todo
//      }

//      static MySettingNode* create(MySettingValue* value, float width) {
//          auto ret = new MySettingNode();
//          if (ret && ret->init(value, width)) {
//              ret->autorelease();
//              return ret;
//          }
//          CC_SAFE_DELETE(ret);
//          return nullptr;
//      }
//  };

//  $on_mod(Loaded) {
//      Mod::get()->addCustomSetting<MySettingValue>("my-setting", ...);
//  }


class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;

		auto main_title = this->getChildByID("main-title");

		if(!Mod::get()->setSavedValue<bool>("not-first-boot", true)) {
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

		auto appearence_setting = Mod::get()->getSettingValue<bool>("new-appearance");

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

		auto animation_length = Mod::get()->getSettingValue<double>("animation-length");

		if(!Mod::get()->getSettingValue<bool>("dis-anim")) {
			splash->runAction(CCRepeatForever::create(CCSequence::create(
				CCEaseOut::create(CCScaleTo::create(animation_length, splash->getScale() + Mod::get()->getSettingValue<double>("animation-scale")), animation_length),
				CCEaseOut::create(CCScaleTo::create(animation_length, splash->getScale()), animation_length),
				nullptr
			)))->setTag(1);
		}
		
		splash->setZOrder(3);
		splash->setID("minecraft-splash");
		splash->setPosition(posX, posY);
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