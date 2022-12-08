#ifndef LAB2_MODES_H
#define LAB2_MODES_H

#pragma once

#include "factory.h"
#include <vector>
#include <string>

struct InState {
    std::vector<char*> strategy_names;
    unsigned char mode;
    int steps = 0;
    char* configs_dirname = nullptr;
    char* matrix_filename = nullptr;
};

typedef std::vector<std::vector<int>> Mat;

Mat read_matrix(std::string);
int decision_processing(Istrategy*, Istrategy*, Istrategy*);

void detailed_mode(InState&);
void fast_mode(InState&);
void tournament_mode(InState&);

#endif //LAB2_MODES_H
