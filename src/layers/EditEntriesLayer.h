#include <Geode/Bindings.hpp>
#include <string>

#pragma once

#include "../settings/CustomSettings.h"
#include "SplashesListPopup.h"

using namespace geode::prelude;

class EditEntriesLayer : public geode::Popup<ArrayListNode*, int, int, SplashesListPopup*> {
    protected:
    const CCPoint offset = cocos2d::CCDirector::get()->getWinSize() / 2.f;
        ArrayListNode* m_node;
        SplashesListPopup* m_previousPopup;
        int m_index;
        const std::string m_defaultPreviewPlaceholder = "Preview";
        const float m_defaultPreviewScale = 0.6f;
        CCLabelBMFont* m_previewLabel;
        virtual bool setup(ArrayListNode* node, int index, int mode, SplashesListPopup* prev_popup) override;
        virtual void addSplash(cocos2d::CCObject* sender);
        virtual void editSplash(cocos2d::CCObject* sender);
    public:
        static EditEntriesLayer* create(ArrayListNode* node, int index, int mode, SplashesListPopup* prev_popup);
        class ScaleInputDelegate : public TextInputDelegate {
            public:
                void textChanged(CCTextInputNode* p0) override;
        };
        class SplashInputDelegate : public TextInputDelegate {
            public:
                void textChanged(CCTextInputNode* p0) override;
        };
};