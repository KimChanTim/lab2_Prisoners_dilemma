#include "modes.h"
#include <iostream>
#include <cstring>
#include <time.h>


InState readState(int argc, char **argv) {
    InState state;
    for(int i = 1; i < argc; i++) {
        try {
            if (!strncmp(argv[i], "--mode=", 7)) {
                if (!strcmp(argv[i] + 7, "detailed")) {
                    state.mode = 0;
                } else if (!strcmp(argv[i] + 7, "fast")) {
                    state.mode = 1;
                } else if (!strcmp(argv[i] + 7, "tournament")) {
                    state.mode = 2;
                } else {
                    throw std::out_of_range("out of range");
                }
                continue;
            }
            if (!strncmp(argv[i], "--steps=", 8)) {
                state.steps = std::stoi(argv[i] + 8);
                continue;
            }
            if (!strncmp(argv[i], "--configs=", 10)) {
                state.configs_dirname = argv[i] + 10;
                continue;
            }
            if (!strncmp(argv[i], "--matrix=", 9)) {
                state.matrix_filename = argv[i] + 9;
                continue;
            }
            state.strategy_names.push_back(argv[i]);
        } catch (std::out_of_range& ex) {
            std::cerr << ex.what() << std::endl;
        } catch (std::invalid_argument& ex) {
            std::cerr << ex.what() << std::endl;
        } catch (...) {
            std::cerr << "unknown error" << std::endl;
        }
    }
    return state;
}

int main(int argc, char **argv) {
    try {
        srand(time(nullptr));
        InState state = readState(argc, argv);
        if (state.strategy_names.size() < 3)
            throw std::invalid_argument("strategy names are not enough");
        switch (state.mode) {
            case 0:
                detailed_mode(state);
                break;
            case 1:
                fast_mode(state);
                break;
            case 2:
                tournament_mode(state);
                break;
            default:
                detailed_mode(state);
                break;
        }
    } catch(std::invalid_argument& ex) {
        std::cerr << ex.what() << std::endl;
    } catch(...) {
        std::cerr << "unknown error" << std::endl;
    }
    return 0;
}
