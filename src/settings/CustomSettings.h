#include <Geode/loader/SettingNode.hpp>
#include <vector>
#include <matjson/stl_serialize.hpp>

using namespace geode::prelude;

class ArrayListValue;

class ArrayListValue : public SettingValue {
    protected:
        std::vector<std::vector<std::string>> m_splashArray;
    // store the current value in some form. 
    // this may be an enum, a class, or 
    // whatever it is your setting needs - 
    // you are free to do whatever!

    public:
        ArrayListValue(std::string const& key, std::string const& modID, std::vector<std::vector<std::string>> const& splashArray) : SettingValue(key, modID), m_splashArray(splashArray) {}


        bool load(matjson::Value const& json) override {
            try {
                m_splashArray = Mod::get()->getSavedValue<std::vector<std::vector<std::string>>>("splashes-vector");
                return true;
            } catch(...) {
                return false;
            }
            // load the value of the setting from json, 
            // returning true if loading was succesful
            return true;
        }
        bool save(matjson::Value& json) const override {
            Mod::get()->setSavedValue<std::vector<std::vector<std::string>>>("splashes-vector", m_splashArray);
            // save the value of the setting into json,
            // returning true if saving was succesful
            return true;
        }
        SettingNode* createNode(float width) override;

        void setArray(std::vector<std::vector<std::string>> splashArray) {
            m_splashArray = splashArray;
        }

        std::vector<std::vector<std::string>> getArray() {
            return m_splashArray;
        }

    // getters and setters for the value
};

class ArrayListNode : public SettingNode {
    protected:
        std::vector<std::vector<std::string>> m_currentArray;
        virtual bool init(ArrayListValue* value, float width);
        virtual void createPopup(cocos2d::CCObject* sender);
        // Whenever the user interacts with your controls, you should call 
        // this->dispatchChanged()

    public:
        // When the user wants to save this setting value, this function is 
        // called - this is where you should actually set the value of your 
        // setting
        void commit() override;
        // Geode calls this to query if the setting value has been changed, 
        // and those changes haven't been committed
        bool hasUncommittedChanges() override;

        // Geode calls this to query if the setting has a value that is 
        // different from its default value
        bool hasNonDefaultValue() override;

        // Geode calls this to reset the setting's value back to default
        void resetToDefault() override;

        static ArrayListNode* create(ArrayListValue* value, float width);
};