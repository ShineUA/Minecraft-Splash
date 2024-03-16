#include <Geode/Bindings.hpp>
#include <string>

#pragma once

#include "../settings/CustomSettings.h"

using namespace geode::prelude;

class SplashesListPopup : public geode::Popup<ArrayListValue*> {
    protected:
        const cocos2d::CCPoint offset = cocos2d::CCDirector::sharedDirector()->getWinSize() / 2;
        ArrayListValue* m_local_value;
        virtual bool setup(ArrayListValue* save_value) override;
        virtual void deleteEntry(cocos2d::CCObject* sender);
        virtual void addEntry(cocos2d::CCObject* sender);
        virtual void editEntry(cocos2d::CCObject* sender);
        virtual void setupSplashesList();
    public:
        virtual void updateSplashesList();
        static SplashesListPopup* create(ArrayListValue* save_value);
};

