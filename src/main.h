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

std::vector<std::vector<std::string>> default_splashes = {
	{"Also try minecraft...", "0.6"},
	{"Also try terraria...", "0.6"},
	{"Go touch some grass...", "0.6"},
	{"FIRE IN THE HOLE!!!!", "0.6"},
	{"I'm verified THE GOLDEN LETS GO!", "0.35"},
	{"Also try the impossible game...", "0.45"},
	{"WATER ON THE HILL!!!", "0.6"},
	{"Korivka top!","0.6"},
	{"Chomu ne na fronti?", "0.6"},
	{"jump on the spike to win...", "0.5"},
	{"try Tidal wave if you're new...", "0.45"},
	{"try Bloodbath if you're new...", "0.45"},
	{"don't crash on 99%...", "0.6"},
	{"lobotomy dash...", "0.6"},
	{"also try star echo...", "0.6"},
	{"RubRubRubRubRub", "0.6"},
	{"There's nothing we can do...", "0.45"},
	{"Vinovat neiron...", "0.6"},
	{"muplan challenge...", "0.6"},
	{"Ho hey!", "0.6"},
	{"Again? Really?", "0.6"},
	{"Continue?", "0.6"},
	{"GGWP", "0.6"},
	{"LOL", "0.6"},
	{"Take a break...", "0.6"},
	{"Not ok...", "0.6"},
	{"You ok?", "0.6"},
	{"BASED", "0.6"},
	{"el pepe", "0.6"},
	{"Harder than FNF", "0.6"},
	{"I am Batman", "0.6"},
	{"huhu yo", "0.6"},
	{"Kappa", "0.6"},
	{"pogchamp", "0.6"},
	{"Press alt + f4 for secret way", "0.45"},
	{"Take a break!", "0.6"},
	{"Time to go outside...", "0.6"},
	{"To be continued...", "0.6"},
	{"youre going to brazil", "0.6"},
	{"Click between frames!", "0.7"},
	{"Hello, I'm Robtop...", "0.6"},
	{"Robtop likes clicking between frames...", "0.35"},
	{"Consider being soggy...", "0.6"}
};

int splashIndex;

bool onOpenRandom = false;