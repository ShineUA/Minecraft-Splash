#pragma once
#include <matjson/stl_serialize.hpp>

using namespace geode::prelude;

extern int splashIndex;

#if !defined GEODE_IS_MACOS
class Easings {
    public:
        static cocos2d::CCActionInterval* returnEasingIn(int num);
        static cocos2d::CCActionInterval* returnEasingOut(int num);
};

class EasingsPreview {
    public:
        static cocos2d::CCActionInterval* returnEasingIn(int num, cocos2d::CCLabelBMFont* label);
        static cocos2d::CCActionInterval* returnEasingOut(int num, cocos2d::CCLabelBMFont* label);
};
#endif