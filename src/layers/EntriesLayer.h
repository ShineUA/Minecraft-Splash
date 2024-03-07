#include <Geode/Bindings.hpp>
#include <string>

#pragma once

#include "../settings/CustomSettings.h"
#include "SplashesListPopup.h"

using namespace geode::prelude;

class EntriesLayer : public FLAlertLayer, TextInputDelegate, FLAlertLayerProtocol {
    protected:
        ArrayListValue* m_save;
        int m_index;
        const std::string m_def_preview_placeholder = "Preview";
        const float m_def_preview_scale = 0.6f;
        CCLabelBMFont* m_preview_label;
        virtual bool init(ArrayListValue* save, int index, int mode);
        virtual void keyBackClicked() override;
        virtual void onExit(cocos2d::CCObject* sender);
        virtual void addSplash(cocos2d::CCObject* sender);
        virtual void editSplash(cocos2d::CCObject* sender);
        virtual void removeSplash(cocos2d::CCObject* sender);
    public:
        static EntriesLayer* create(ArrayListValue* save, int index, int mode = 0);
        class ScaleInputDelegate : public TextInputDelegate {
            public:
                void textChanged(CCTextInputNode* p0) override;
        };
        class SplashInputDelegate : public TextInputDelegate {
            public:
                void textChanged(CCTextInputNode* p0) override;
        };
};