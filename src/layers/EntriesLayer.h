#include <Geode/Bindings.hpp>
#include <string>

#pragma once

#include "../settings/CustomSettings.h"
#include "SplashesListPopup.h"

using namespace geode::prelude;

class EntriesLayer : public geode::Popup<ArrayListValue*, int, int, SplashesListPopup*> {
    protected:
    const CCPoint offset = cocos2d::CCDirector::get()->getWinSize() / 2.f;
        ArrayListValue* m_save;
        SplashesListPopup* m_prev_popup;
        int m_index;
        const std::string m_def_preview_placeholder = "Preview";
        const float m_def_preview_scale = 0.6f;
        CCLabelBMFont* m_preview_label;
        virtual bool setup(ArrayListValue* save, int index, int mode, SplashesListPopup* prev_popup) override;
        virtual void addSplash(cocos2d::CCObject* sender);
        virtual void editSplash(cocos2d::CCObject* sender);
    public:
        static EntriesLayer* create(ArrayListValue* save, int index, int mode, SplashesListPopup* prev_popup);
        class ScaleInputDelegate : public TextInputDelegate {
            public:
                void textChanged(CCTextInputNode* p0) override;
        };
        class SplashInputDelegate : public TextInputDelegate {
            public:
                void textChanged(CCTextInputNode* p0) override;
        };
};