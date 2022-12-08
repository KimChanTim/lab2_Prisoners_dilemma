#ifndef LAB2_FACTORY_H
#define LAB2_FACTORY_H

#pragma once

#include "strategy.h"
#include <map>
#include <string>

class Ifactory {
public:
    Istrategy* make_strategy(const std::string&);
    virtual Istrategy* create() = 0;
};

class Evil_factory : public Ifactory {
    Istrategy* create() override;
};

class Angel_factory : public Ifactory {
    Istrategy* create() override;
};

class RandomMaster_factory : public Ifactory {
    Istrategy* create() override;
};

class GrimTrigger_factory : public Ifactory {
    Istrategy* create() override;
};

class EyeForEye_factory : public Ifactory {
    Istrategy* create() override;
};

class EyeForEye_m_factory : public Ifactory {
    Istrategy* create() override;
};

class Brother_factory : public Ifactory {
    Istrategy* create() override;
};

class Sister_factory : public Ifactory {
    Istrategy* create() override;
};

static const std::map<std::string, Ifactory *> FactoryMap = {{"Evil",         new Evil_factory},
                                                            {"Angel",        new Angel_factory},
                                                            {"RandomMaster", new RandomMaster_factory},
                                                            {"GrimTrigger", new GrimTrigger_factory},
                                                            {"EyeForEye", new EyeForEye_factory},
                                                            {"EyeForEye_m", new EyeForEye_m_factory},
                                                            {"Brother", new Brother_factory},
                                                            {"Sister", new Sister_factory}};

#endif //LAB2_FACTORY_H
