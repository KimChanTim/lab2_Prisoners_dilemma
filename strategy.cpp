#include "strategy.h"
#include <stdlib.h>

bool Istrategy::Get_cooperate() const {
    return cooperate;
}

int Istrategy::Get_scores() const {
    return scores;
}

std::string strategy_Evil::Get_name() {
    return "Evil";
}
std::string strategy_Angel::Get_name() {
    return "Angel";
}
std::string strategy_RandomMaster::Get_name() {
    return "RandomMaster";
}
std::string strategy_GrimTrigger::Get_name() {
    return "GrimTrigger";
}
std::string strategy_EyeForEye::Get_name() {
    return "EyeForEye";
}
std::string strategy_EyeForEye_m::Get_name() {
    return "EyeForEye_m";
}
std::string strategy_Brother::Get_name() {
    return "Brother";
}
std::string strategy_Sister::Get_name() {
    return "Sister";
}

void strategy_Evil::make_decision() {
    cooperate = false;
}

void strategy_Angel::make_decision() {
    cooperate = true;
}

void strategy_RandomMaster::make_decision() {
    cooperate = rand() % 2;
}

void strategy_Evil::push_decision(int val, bool dec1, bool dec2) {
    scores += val;
}

void strategy_Angel::push_decision(int val, bool dec1, bool dec2) {
    scores += val;
}

void strategy_RandomMaster::push_decision(int val, bool dec1, bool dec2) {
    scores += val;
}

void strategy_Evil::clear_history() {
    scores = 0;
}

void strategy_Angel::clear_history() {
    scores = 0;
}

void strategy_RandomMaster::clear_history() {
    scores = 0;
}

void strategy_GrimTrigger::make_decision() {
    if (flag) {
        cooperate = false;
    } else {
        if (!opponent_decision.first || !opponent_decision.second) {
            flag = true;
            make_decision();
        } else {
            cooperate = true;
        }
    }
}

void strategy_GrimTrigger::push_decision(int val, bool first, bool second) {
    scores+=val;
    opponent_decision.first = first;
    opponent_decision.second = second;
}

void strategy_GrimTrigger::clear_history() {
    scores = 0;
    flag = false;
    opponent_decision = {true, true};
}

void strategy_EyeForEye::make_decision() {
    if (opponent_decision.first && opponent_decision.second) {
        cooperate = true;
    } else {
        cooperate = false;
    }
}

void strategy_EyeForEye::push_decision(int val, bool first, bool second) {
    scores+=val;
    opponent_decision.first = first;
    opponent_decision.second = second;
}

void strategy_EyeForEye::clear_history() {
    scores = 0;
    opponent_decision = {true, true};
}

void strategy_EyeForEye_m::make_decision() {
    if (rand() % 100 < 5) {
        cooperate = true;
    } else {
        strategy_EyeForEye::make_decision();
    }
}

void strategy_EyeForEye_m::push_decision(int val, bool first, bool second) {
    scores+=val;
    opponent_decision.first = first;
    opponent_decision.second = second;
}

void strategy_EyeForEye_m::clear_history() {
    scores = 0;
    opponent_decision = {true, true};
}

void strategy_Brother::make_decision() {
    if (key) {
        cooperate = true;
    } else {
        cooperate = false;
    }
    key = false;
}

void strategy_Brother::push_decision(int val, bool first, bool second) {
    scores+=val;
}

void strategy_Brother::clear_history() {
    key = true;
    scores = 0;
}

void strategy_Sister::make_decision() {
    strategy_EyeForEye::make_decision();
}

void strategy_Sister::push_decision(int val, bool first, bool second) {
    key = true;
    scores+=val;
    opponent_decision.first = first;
    opponent_decision.second = second;
}

void strategy_Sister::clear_history() {
    scores = 0;
    opponent_decision = {true, true};
}

bool strategy_Twins::key = true;
