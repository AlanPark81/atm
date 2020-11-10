#pragma once
#include <memory>
#include <unordered_map>
#include <vector>

using namespace std;

class Bank {
    static unordered_map<string, string> card_pin_map_;
    static unordered_map<string, vector<pair<string, int>>> card_account_;
    static shared_ptr<Bank> object_;
    string card_num_;
    bool verified_;

    public:
    Bank() : card_num_(""), verified_(false){}
    
    static shared_ptr<Bank> getInstance();

    virtual bool verifyCard(const string& card_num);

    virtual bool verifyPin(const string& pin);

    virtual bool verified() const;

    virtual vector<string> getAccList() const;

    virtual int getBalance(int acc_num) const;
};

class ATM {
    static shared_ptr<ATM> object_;

    public:
    static shared_ptr<ATM> getInstance();

    ATM() {}

    bool insertCard(const string& card_num);

    bool checkPIN() const;

    int getBalance(int acc_op) const;
};