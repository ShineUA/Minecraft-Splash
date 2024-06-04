#pragma once
#include <Geode/loader/SettingNode.hpp>
#include <vector>
#include <matjson/stl_serialize.hpp>
#include <random>
#include <Geode/Bindings.hpp>
#include <string>
#include <cstring>

using namespace geode::prelude;

class ArrayListValue : public SettingValue {
    protected:
        std::vector<std::vector<std::string>> m_splashArray;
    public:
        ArrayListValue(std::string const& key, std::string const& modID, std::vector<std::vector<std::string>> const& splashArray) : SettingValue(key, modID), m_splashArray(splashArray) {}

        bool load(matjson::Value const& json) override {
            try {
                m_splashArray = Mod::get()->getSavedValue<std::vector<std::vector<std::string>>>("splashes-vector");
                return true;
            } catch(...) {
                return false;
            }
            return true;
        }
        bool save(matjson::Value& json) const override {
            Mod::get()->setSavedValue<std::vector<std::vector<std::string>>>("splashes-vector", m_splashArray);
            return true;
        }
        SettingNode* createNode(float width) override;

        void setArray(std::vector<std::vector<std::string>> splashArray) {
            this->m_splashArray.clear();
            this->m_splashArray.assign(splashArray.begin(), splashArray.end());
        }

        std::vector<std::vector<std::string>> getArray() {
            return m_splashArray;
        }

};

class ArrayListNode : public SettingNode {
    protected:
        std::vector<std::vector<std::string>> m_unsavedArray;
        virtual bool init(ArrayListValue* value, float width);
        virtual void createPopup(cocos2d::CCObject* sender);
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

        std::vector<std::vector<std::string>> getValue();

        void setValue(std::vector<std::vector<std::string>> value);

        void dispatchChangedPublic();

        static ArrayListNode* create(ArrayListValue* value, float width);
};