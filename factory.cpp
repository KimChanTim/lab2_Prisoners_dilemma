#include "factory.h"
#include <iostream>

Istrategy* Ifactory::make_strategy(const std::string& str) {
    auto it = FactoryMap.find(str);
    if (it == FactoryMap.end())
        throw std::out_of_range("strategy not found");
    return it->second->create();
}

Istrategy* Evil_factory::create() {
    return new strategy_Evil;
}

Istrategy* Angel_factory::create() {
    return new strategy_Angel;
}

Istrategy* RandomMaster_factory::create() {
    return new strategy_RandomMaster;
}

Istrategy* GrimTrigger_factory::create() {
    return new strategy_GrimTrigger;
}

Istrategy* EyeForEye_factory::create() {
    return new strategy_EyeForEye;
}

Istrategy* EyeForEye_m_factory::create() {
    return new strategy_EyeForEye_m;
}

Istrategy* Brother_factory::create() {
    return new strategy_Brother;
}

Istrategy* Sister_factory::create() {
    return new strategy_Sister;
}
