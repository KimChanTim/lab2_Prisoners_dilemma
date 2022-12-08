#ifndef LAB2_STRATEGY_H
#define LAB2_STRATEGY_H

#pragma once
#include <string>

class Istrategy {
protected:
    bool cooperate;
    int scores = 0;

public:
    virtual ~Istrategy() = default;

    virtual void make_decision() = 0;
    virtual void push_decision(int, bool, bool) = 0;
    virtual std::string Get_name() = 0;
    virtual void clear_history() = 0;

    bool Get_cooperate() const;
    int Get_scores() const;
};

class strategy_Evil : public Istrategy {
protected:
    void make_decision() override;
    void push_decision(int, bool, bool) override;
    std::string Get_name() override;
    void clear_history() override;
};

class strategy_Angel : public Istrategy {
protected:
    void make_decision() override;
    void push_decision(int, bool, bool) override;
    std::string Get_name() override;
    void clear_history() override;
};

class strategy_RandomMaster : public Istrategy {
protected:
    void make_decision() override;
    void push_decision(int, bool, bool) override;
    std::string Get_name() override;
    void clear_history() override;
};

class strategy_GrimTrigger : public Istrategy {
protected:
    bool flag = false;
    std::pair<bool, bool> opponent_decision = {true, true};

    void make_decision() override;
    void push_decision(int, bool, bool) override;
    std::string Get_name() override;
    void clear_history() override;
};

class strategy_EyeForEye : virtual public Istrategy {
protected:
    std::pair<bool, bool> opponent_decision = {true, true};

    void make_decision() override;
    void push_decision(int, bool, bool) override;
    std::string Get_name() override;
    void clear_history() override;
};

class strategy_EyeForEye_m : public strategy_EyeForEye {
protected:
    void make_decision() override;
    void push_decision(int, bool, bool) override;
    std::string Get_name() override;
    void clear_history() override;
};

class strategy_Twins : virtual public Istrategy {
protected:
    static bool key;
};

class strategy_Brother : virtual public strategy_Twins {
protected:
    void make_decision() override;
    void push_decision(int, bool, bool) override;
    std::string Get_name() override;
    void clear_history() override;
};

class strategy_Sister : virtual public strategy_Twins, public strategy_EyeForEye {
protected:
    void make_decision() override;
    void push_decision(int, bool, bool) override;
    std::string Get_name() override;
    void clear_history() override;
};

#endif //LAB2_STRATEGY_H
