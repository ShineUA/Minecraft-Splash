#include <Geode/Bindings.hpp>
#include <matjson/stl_serialize.hpp>

using namespace geode::prelude;

class EasingsPreview {
    public:
        static cocos2d::CCActionInterval* returnEasingIn(int num, cocos2d::CCLabelBMFont* label);
        static cocos2d::CCActionInterval* returnEasingOut(int num, cocos2d::CCLabelBMFont* label);
};
