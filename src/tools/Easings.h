#include <Geode/Bindings.hpp>
#include <matjson/stl_serialize.hpp>

using namespace geode::prelude;

#if !defined GEODE_IS_MAC
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