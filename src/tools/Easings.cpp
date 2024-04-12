#include "Easings.h"
#include "../main.h"
#include <string>


#if !defined GEODE_IS_MACOS
CCActionInterval* Easings::returnEasingIn(int num) {
    auto animation_length = Mod::get()->getSettingValue<double>("animation-length");
    auto splashes_vector = Mod::get()->getSavedValue<std::vector<std::vector<std::string>>>("splashes-vector");

	switch(num) {
        default:
            return cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1)) + Mod::get()->getSettingValue<double>("animation-scale"));
			break;
		case 0:
			return cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1)) + Mod::get()->getSettingValue<double>("animation-scale"));
			break;
        case 1:
            return cocos2d::CCEaseInOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1)) + Mod::get()->getSettingValue<double>("animation-scale")), animation_length);
            break;
        case 2:
            return cocos2d::CCEaseIn::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1)) + Mod::get()->getSettingValue<double>("animation-scale")), animation_length);
            break;
        case 3:
            return cocos2d::CCEaseOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1)) + Mod::get()->getSettingValue<double>("animation-scale")), animation_length);
            break;
        case 4:
            return cocos2d::CCEaseElasticInOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1)) + Mod::get()->getSettingValue<double>("animation-scale")), animation_length);
            break;
        case 5:
            return cocos2d::CCEaseElasticIn::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1)) + Mod::get()->getSettingValue<double>("animation-scale")), animation_length);
            break;
        case 6:
            return cocos2d::CCEaseElasticOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1)) + Mod::get()->getSettingValue<double>("animation-scale")), animation_length);
            break;
        case 7:
            return cocos2d::CCEaseBounceInOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1)) + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
        case 8:
            return cocos2d::CCEaseBounceIn::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1)) + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
        case 9:
            return cocos2d::CCEaseBounceOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1)) + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
        case 10:
            return cocos2d::CCEaseExponentialInOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1)) + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
        case 11:
            return cocos2d::CCEaseExponentialIn::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1)) + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
        case 12:
            return cocos2d::CCEaseExponentialOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1)) + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
        case 13:
            return cocos2d::CCEaseSineInOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1)) + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
        case 14:
            return cocos2d::CCEaseSineIn::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1)) + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
        case 15:
            return cocos2d::CCEaseSineOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1)) + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
        case 16:
            return cocos2d::CCEaseSineInOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1)) + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
        case 17:
            return cocos2d::CCEaseSineIn::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1)) + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
        case 18:
            return cocos2d::CCEaseSineOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1)) + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
	}
}

CCActionInterval* Easings::returnEasingOut(int num) {
    auto animation_length = Mod::get()->getSettingValue<double>("animation-length");
    auto splashes_vector = Mod::get()->getSavedValue<std::vector<std::vector<std::string>>>("splashes-vector");

	switch(num) {
        default:
            return cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1)));
			break;
		case 0:
			return cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1)));
			break;
        case 1:
            return cocos2d::CCEaseInOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1))), animation_length);
            break;
        case 2:
            return cocos2d::CCEaseIn::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1))), animation_length);
            break;
        case 3:
            return cocos2d::CCEaseOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1))), animation_length);
            break;
        case 4:
            return cocos2d::CCEaseElasticInOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1))), animation_length);
            break;
        case 5:
            return cocos2d::CCEaseElasticIn::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1))), animation_length);
            break;
        case 6:
            return cocos2d::CCEaseElasticOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1))), animation_length);
            break;
        case 7:
            return cocos2d::CCEaseBounceInOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1))));
            break;
        case 8:
            return cocos2d::CCEaseBounceIn::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1))));
            break;
        case 9:
            return cocos2d::CCEaseBounceOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1))));
            break;
        case 10:
            return cocos2d::CCEaseExponentialInOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1))));
            break;
        case 11:
            return cocos2d::CCEaseExponentialIn::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1))));
            break;
        case 12:
            return cocos2d::CCEaseExponentialOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1))));
            break;
        case 13:
            return cocos2d::CCEaseSineInOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1))));
            break;
        case 14:
            return cocos2d::CCEaseSineIn::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1))));
            break;
        case 15:
            return cocos2d::CCEaseSineOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1))));
            break;
        case 16:
            return cocos2d::CCEaseSineInOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1))));
            break;
        case 17:
            return cocos2d::CCEaseSineIn::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1))));
            break;
        case 18:
            return cocos2d::CCEaseSineOut::create(cocos2d::CCScaleTo::create(animation_length, std::stof(splashes_vector.at(random_splash).at(1))));
            break;
	}
}

CCActionInterval* EasingsPreview::returnEasingIn(int num, CCLabelBMFont* label) {
    auto animation_length = Mod::get()->getSettingValue<double>("animation-length");

	switch(num) {
        default:
            return cocos2d::CCScaleTo::create(animation_length, label->getScale() + Mod::get()->getSettingValue<double>("animation-scale"));
			break;
		case 0:
			return cocos2d::CCScaleTo::create(animation_length, label->getScale() + Mod::get()->getSettingValue<double>("animation-scale"));
			break;
        case 1:
            return cocos2d::CCEaseInOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale() + Mod::get()->getSettingValue<double>("animation-scale")), animation_length);
            break;
        case 2:
            return cocos2d::CCEaseIn::create(cocos2d::CCScaleTo::create(animation_length, label->getScale() + Mod::get()->getSettingValue<double>("animation-scale")), animation_length);
            break;
        case 3:
            return cocos2d::CCEaseOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale() + Mod::get()->getSettingValue<double>("animation-scale")), animation_length);
            break;
        case 4:
            return cocos2d::CCEaseElasticInOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale() + Mod::get()->getSettingValue<double>("animation-scale")), animation_length);
            break;
        case 5:
            return cocos2d::CCEaseElasticIn::create(cocos2d::CCScaleTo::create(animation_length, label->getScale() + Mod::get()->getSettingValue<double>("animation-scale")), animation_length);
            break;
        case 6:
            return cocos2d::CCEaseElasticOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale() + Mod::get()->getSettingValue<double>("animation-scale")), animation_length);
            break;
        case 7:
            return cocos2d::CCEaseBounceInOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale() + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
        case 8:
            return cocos2d::CCEaseBounceIn::create(cocos2d::CCScaleTo::create(animation_length, label->getScale() + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
        case 9:
            return cocos2d::CCEaseBounceOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale() + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
        case 10:
            return cocos2d::CCEaseExponentialInOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale() + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
        case 11:
            return cocos2d::CCEaseExponentialIn::create(cocos2d::CCScaleTo::create(animation_length, label->getScale() + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
        case 12:
            return cocos2d::CCEaseExponentialOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale() + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
        case 13:
            return cocos2d::CCEaseSineInOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale() + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
        case 14:
            return cocos2d::CCEaseSineIn::create(cocos2d::CCScaleTo::create(animation_length, label->getScale() + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
        case 15:
            return cocos2d::CCEaseSineOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale() + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
        case 16:
            return cocos2d::CCEaseSineInOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale() + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
        case 17:
            return cocos2d::CCEaseSineIn::create(cocos2d::CCScaleTo::create(animation_length, label->getScale() + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
        case 18:
            return cocos2d::CCEaseSineOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale() + Mod::get()->getSettingValue<double>("animation-scale")));
            break;
	}
}

CCActionInterval* EasingsPreview::returnEasingOut(int num, CCLabelBMFont* label) {
    auto animation_length = Mod::get()->getSettingValue<double>("animation-length");

	switch(num) {
        default:
            return cocos2d::CCScaleTo::create(animation_length, label->getScale());
			break;
		case 0:
			return cocos2d::CCScaleTo::create(animation_length, label->getScale());
			break;
        case 1:
            return cocos2d::CCEaseInOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale()), animation_length);
            break;
        case 2:
            return cocos2d::CCEaseIn::create(cocos2d::CCScaleTo::create(animation_length, label->getScale()), animation_length);
            break;
        case 3:
            return cocos2d::CCEaseOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale()), animation_length);
            break;
        case 4:
            return cocos2d::CCEaseElasticInOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale()), animation_length);
            break;
        case 5:
            return cocos2d::CCEaseElasticIn::create(cocos2d::CCScaleTo::create(animation_length, label->getScale()), animation_length);
            break;
        case 6:
            return cocos2d::CCEaseElasticOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale()), animation_length);
            break;
        case 7:
            return cocos2d::CCEaseBounceInOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale()));
            break;
        case 8:
            return cocos2d::CCEaseBounceIn::create(cocos2d::CCScaleTo::create(animation_length, label->getScale()));
            break;
        case 9:
            return cocos2d::CCEaseBounceOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale()));
            break;
        case 10:
            return cocos2d::CCEaseExponentialInOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale()));
            break;
        case 11:
            return cocos2d::CCEaseExponentialIn::create(cocos2d::CCScaleTo::create(animation_length, label->getScale()));
            break;
        case 12:
            return cocos2d::CCEaseExponentialOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale()));
            break;
        case 13:
            return cocos2d::CCEaseSineInOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale()));
            break;
        case 14:
            return cocos2d::CCEaseSineIn::create(cocos2d::CCScaleTo::create(animation_length, label->getScale()));
            break;
        case 15:
            return cocos2d::CCEaseSineOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale()));
            break;
        case 16:
            return cocos2d::CCEaseSineInOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale()));
            break;
        case 17:
            return cocos2d::CCEaseSineIn::create(cocos2d::CCScaleTo::create(animation_length, label->getScale()));
            break;
        case 18:
            return cocos2d::CCEaseSineOut::create(cocos2d::CCScaleTo::create(animation_length, label->getScale()));
            break;
	}
}

#endif