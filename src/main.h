#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <string>
#include <matjson/stl_serialize.hpp>
#include <random>
#include "./tools/Easings.h"
#include "./settings/CustomSettings.h"
#include "./settings/SectionSetting.hpp"

using namespace geode::prelude;

std::vector<std::string> default_splashes = {
	"Also try minecraft...",
	"Also try terraria...",
	"Go touch some grass...",
	"FIRE IN THE HOLE!!!!",
	"I'm verified THE GOLDEN LETS GO!",
	"Also try the impossible game...",
	"WATER ON THE HILL!!!",
	"Korivka top!",
	"Chomu ne na fronti?",
	"jump on the spike to win...",
	"try Tidal wave if you're new...",
	"try Bloodbath if you're new...",
	"don't crash on 99%...",
	"lobotomy dash...",
	"also try star echo...",
	"RubRubRubRubRub",
	"There's nothing we can do...",
	"Vinovat neiron...",
	"muplan challenge...",
	"Ho hey!",
	"Again? Really?",
	"Continue?",
	"GGWP",
	"LOL",
	"Take a break...",
	"Not ok...",
	"You ok?",
	"BASED",
	"el pepe",
	"Harder than FNF",
	"I am Batman",
	"huhu yo",
	"Kappa",
	"pogchamp",
	"Press alt + f4 for secret way",
	"Take a break!",
	"Time to go outside...",
	"To be continued...",
	"youre going to brazil",
	"Click between frames!",
	"Hello, I'm Robtop...",
	"Robtop likes clicking between frames...",
	"Consider being soggy...",
};

int splashIndex;