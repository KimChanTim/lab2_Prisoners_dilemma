#include "modes.h"
#include <iostream>
#include <fstream>
#include <iomanip>

#define DEFAULT_MATRIX {{4, 4, 4},{0, 0, 6},{0, 6, 0},{6, 0, 0},{-3, 2, 2},{2, -3, 2},{2, 2, -3},{-2, -2, -2}}

Mat read_matrix(std::string filename) {
    std::string str;
    std::ifstream file(filename);
    if (file.fail())
        throw std::invalid_argument("invalid file");
    Mat matrix;
    for (int i = 0; i < 8; i++) {
        std::vector<int> vector;
        for (int j = 0; j < 3; j++) {
            file >> str;
            vector.push_back(std::stoi(str));
        }
        matrix.push_back(vector);
    }
    file.close();
    return matrix;
}

int decision_processing(Istrategy* strategy1, Istrategy* strategy2, Istrategy* strategy3) {
    if (strategy1->Get_cooperate()) {
        if (strategy2->Get_cooperate()) {
            if (strategy3->Get_cooperate())
                return 0;
            else
                return 1;
        } else {
            if (strategy3->Get_cooperate())
                return 2;
            else
                return 4;
        }
    } else {
        if (strategy2->Get_cooperate()) {
            if (strategy3->Get_cooperate())
                return 3;
            else
                return 5;
        } else {
            if (strategy3->Get_cooperate())
                return 6;
            else
                return 7;
        }
    }
}

void detailed_mode(InState& state) {
    Mat game_matrix;
    if (state.matrix_filename)
        game_matrix = read_matrix(state.matrix_filename);
    else
        game_matrix = DEFAULT_MATRIX;

    std::vector<Istrategy*> strategy_vector;
    for (int i = 0; i < state.strategy_names.size(); i++) {
        try {
            Ifactory *strategy_factory;
            strategy_vector.push_back(strategy_factory->make_strategy(state.strategy_names[i]));
        } catch(std::out_of_range& ex) {
            std::cerr << state.strategy_names[i] << " " << ex.what() << std::endl;
        }
    }
    if (strategy_vector.size() < 3) abort();

    std::string str;
    while (str != "quit") {
        strategy_vector[0]->make_decision();
        strategy_vector[1]->make_decision();
        strategy_vector[2]->make_decision();
        int decision = decision_processing(strategy_vector[0], strategy_vector[1], strategy_vector[2]);

        strategy_vector[0]->push_decision(game_matrix[decision][0], strategy_vector[1]->Get_cooperate(), strategy_vector[2]->Get_cooperate());
        strategy_vector[1]->push_decision(game_matrix[decision][1], strategy_vector[0]->Get_cooperate(), strategy_vector[2]->Get_cooperate());
        strategy_vector[2]->push_decision(game_matrix[decision][2], strategy_vector[0]->Get_cooperate(), strategy_vector[1]->Get_cooperate());

        std::cout << std::setw(30) << std::left << "Scores for current step:" << std::right << "Total scores:" << std::endl;
        for (int i = 0; i < 3; i++) {
            std::cout << std::setw(20) << std::left << strategy_vector[i]->Get_name() << std::right
            << (strategy_vector[i]->Get_cooperate() ? 'C' : 'D') << " " << std::setw(10) << std::left
            << game_matrix[decision][i] << std::right
            << strategy_vector[i]->Get_scores() << std::endl;
        }
        std::cout << std::endl;
        std::cin >> str;
        std::cout << std::endl;
    }

    for (auto & it : strategy_vector) {
        delete it;
    }

    for (const auto & it : FactoryMap) {
        delete it.second;
    }
}

void fast_mode(InState& state) {
    if (state.steps == 0)
        throw std::invalid_argument("steps = 0");

    Mat game_matrix;
    if (state.matrix_filename)
        game_matrix = read_matrix(state.matrix_filename);
    else
        game_matrix = DEFAULT_MATRIX;

    std::vector<Istrategy*> strategy_vector;
    for (int i = 0; i < state.strategy_names.size(); i++) {
        try {
            Ifactory *strategy_factory;
            strategy_vector.push_back(strategy_factory->make_strategy(state.strategy_names[i]));
        } catch(std::out_of_range& ex) {
            std::cerr << state.strategy_names[i] << " " << ex.what() << std::endl;
        }
    }
    if (strategy_vector.size() < 3) abort();

    for (int i = 0; i < state.steps; i++) {
        strategy_vector[0]->make_decision();
        strategy_vector[1]->make_decision();
        strategy_vector[2]->make_decision();
        int decision = decision_processing(strategy_vector[0], strategy_vector[1], strategy_vector[2]);

        strategy_vector[0]->push_decision(game_matrix[decision][0], strategy_vector[1]->Get_cooperate(), strategy_vector[2]->Get_cooperate());
        strategy_vector[1]->push_decision(game_matrix[decision][1], strategy_vector[0]->Get_cooperate(), strategy_vector[2]->Get_cooperate());
        strategy_vector[2]->push_decision(game_matrix[decision][2], strategy_vector[0]->Get_cooperate(), strategy_vector[1]->Get_cooperate());
    }
    std::cout << "Total scores:" << std::endl;
    for (int i = 0; i < 3; i++) {
        std::cout << std::setw(20) << std::left << strategy_vector[i]->Get_name()
        << std::right << strategy_vector[i]->Get_scores() << std::endl;
    }

    for (auto & it : strategy_vector) {
        delete it;
    }

    for (const auto & it : FactoryMap) {
        delete it.second;
    }
}

void tournament_mode(InState& state) {
    if (state.steps == 0)
        throw std::invalid_argument("steps = 0");

    Mat game_matrix;
    if (state.matrix_filename)
        game_matrix = read_matrix(state.matrix_filename);
    else
        game_matrix = DEFAULT_MATRIX;

    std::vector<Istrategy*> strategy_vector;
    for (int i = 0; i < state.strategy_names.size(); i++) {
        try {
            Ifactory *strategy_factory;
            strategy_vector.push_back(strategy_factory->make_strategy(state.strategy_names[i]));
        } catch(std::out_of_range& ex) {
            std::cerr << state.strategy_names[i] << " " << ex.what() << std::endl;
        }
    }
    if (strategy_vector.size() < 3) abort();

    std::vector<int> scores_vector(strategy_vector.size(), 0);
    for (int j = 0; j < strategy_vector.size() - 2; j++) {
        for (int k = j + 1; k < strategy_vector.size() - 1; k++) {
            for (int t = k + 1; t < strategy_vector.size(); t++) {
                for (int i = 0; i < state.steps; i++) {
                    strategy_vector[j]->make_decision();
                    strategy_vector[k]->make_decision();
                    strategy_vector[t]->make_decision();
                    int decision = decision_processing(strategy_vector[j], strategy_vector[k], strategy_vector[t]);

                    strategy_vector[j]->push_decision(game_matrix[decision][0], strategy_vector[k]->Get_cooperate(), strategy_vector[t]->Get_cooperate());
                    strategy_vector[k]->push_decision(game_matrix[decision][1], strategy_vector[j]->Get_cooperate(), strategy_vector[t]->Get_cooperate());
                    strategy_vector[t]->push_decision(game_matrix[decision][2], strategy_vector[j]->Get_cooperate(), strategy_vector[k]->Get_cooperate());
                }
                scores_vector[j] += strategy_vector[j]->Get_scores();
                scores_vector[k] += strategy_vector[k]->Get_scores();
                scores_vector[t] += strategy_vector[t]->Get_scores();


                std::cout << std::setw(20) << std::left << strategy_vector[j]->Get_name()
                        << std::right << strategy_vector[j]->Get_scores() << std::endl;
                std::cout << std::setw(20) << std::left << strategy_vector[k]->Get_name()
                        << std::right << strategy_vector[k]->Get_scores() << std::endl;
                std::cout << std::setw(20) << std::left << strategy_vector[t]->Get_name()
                        << std::right << strategy_vector[t]->Get_scores() << std::endl;
                std::cout << std::endl;

                strategy_vector[j]->clear_history();
                strategy_vector[k]->clear_history();
                strategy_vector[t]->clear_history();
            }
        }
    }
    std::cout << "Final results:" << std::endl;
    for (int i = 0; i < scores_vector.size(); i++) {
        std::cout << std::setw(20) << std::left << strategy_vector[i]->Get_name()
                  << std::right << scores_vector[i] << std::endl;
    }

    for (auto & it : strategy_vector) {
        delete it;
    }

    for (const auto & it : FactoryMap) {
        delete it.second;
    }
}
