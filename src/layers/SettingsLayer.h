#include <Geode/Bindings.hpp>

using namespace geode::prelude;

class SettingsLayer : public cocos2d::CCLayer {
protected:
    virtual bool init();
    virtual void keyBackClicked();
    virtual void onBack(cocos2d::CCObject*);
    virtual void onAppearanceChecked(cocos2d::CCObject*);
    virtual void onDisAnimChecked(cocos2d::CCObject*);
    virtual void onAppearanceInfo(cocos2d::CCObject*);
    virtual void onDisAnimInfo(cocos2d::CCObject*);
    virtual void onAnimationLengthInfo(cocos2d::CCObject*);
    virtual void onAnimationScaleInfo(cocos2d::CCObject*);
public:
    static SettingsLayer* create();
};

class SettingsLayerBG : public cocos2d::CCLayerColor {
protected:
    virtual bool init();
public:
    static SettingsLayerBG* create();
};

