#include <Geode/Bindings.hpp>
#include <matjson/stl_serialize.hpp>

using namespace geode::prelude;

class Easings {
    public:
        static cocos2d::CCActionInterval* returnEasingIn(int num);
        static cocos2d::CCActionInterval* returnEasingOut(int num);
};