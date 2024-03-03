#include <Geode/Bindings.hpp>
#include <string>
#include "../settings/CustomSettings.h"

using namespace geode::prelude;

class SplashesListPopup : public FLAlertLayer, TextInputDelegate, FLAlertLayerProtocol {
    protected:
        ArrayListValue* m_local_value;
        virtual bool init(ArrayListValue* save_value);
        virtual void deleteEntry(cocos2d::CCObject* sender);
        virtual void addEntry(cocos2d::CCObject* sender);
        virtual void editEntry(cocos2d::CCObject* sender);
        virtual void keyBackClicked() override;
        virtual void onCloseBtn(cocos2d::CCObject* sender);
    public:
        static SplashesListPopup* create(ArrayListValue* save_value);
};

