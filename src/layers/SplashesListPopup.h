#include <Geode/Bindings.hpp>
#include <string>


using namespace geode::prelude;

class SplashesListPopup : public FLAlertLayer, TextInputDelegate, FLAlertLayerProtocol {
    protected:
        virtual bool init(std::vector<std::vector<std::string>> objects);
        virtual void deleteEntry(cocos2d::CCObject* sender);
        virtual void addEntry(cocos2d::CCObject* sender);
        virtual void editEntry(cocos2d::CCObject* sender);
        virtual void keyBackClicked() override;
        virtual void onCloseBtn(cocos2d::CCObject* sender);
    public:
        static SplashesListPopup* create(std::vector<std::vector<std::string>> objects);
};

