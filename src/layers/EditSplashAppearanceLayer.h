#pragma once

#include <Geode/Geode.hpp>

using namespace geode::prelude;

class EditSplashAppearanceLayer : public CCLayer {
    protected:
        bool init() override;
    public:
        void keyBackClicked() override;
        static EditSplashAppearanceLayer* scene();
};