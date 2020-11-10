#include "ATM.h"


unordered_map<string, string> Bank::card_pin_map_;
unordered_map<string, vector<pair<string, int>>> Bank::card_account_;
shared_ptr<Bank> Bank::object_;

shared_ptr<Bank> Bank::getInstance() {
    if (card_pin_map_.empty()) {
        card_pin_map_["0123456789ABCDEF012"] = "1234";
        card_pin_map_["23456789ABCDEF01201"] = "2345";
    }

    if (card_account_.empty()) {
        card_account_["0123456789ABCDEF012"] = vector<pair<string, int>> {{"1234", 100}, {"1235", 100000}} ;
        card_account_["23456789ABCDEF01201"] = vector<pair<string, int>> {{"2345", 100}, {"35709", 10000000}} ;
    }
    if (not object_) object_ = make_shared<Bank>();
    return object_;
}

bool Bank::verifyCard(const string& card_num) {
    if (card_pin_map_.find(card_num) == card_pin_map_.end())
        return false;
    card_num_ = card_num;
    return true;
}

bool Bank::verifyPin(const string& pin) {
    verified_ = (card_pin_map_[card_num_] == pin);
    return verified_;
}

bool Bank::verified() const {
    return verified_;
}

void Bank::deposit(int acc_op, unsigned int money) const {
    card_account_[card_num_][acc_op].second += money;
}
bool Bank::withdraw(int acc_op, unsigned int money) const {
    if (card_account_[card_num_][acc_op].second < money) return false;
    card_account_[card_num_][acc_op].second -= money;
    return true;
}

vector<string> Bank::getAccList() const {
    vector<string> ret_val;
    const auto& list = card_account_[card_num_];
    for (const auto& acc : list) {
        ret_val.push_back(acc.first);
    }
    return ret_val;
}

int Bank::getBalance(int acc_num) const {
    if (not verified_) return -1;
    return card_account_[card_num_][acc_num].second;
}

shared_ptr<ATM> ATM::object_;

shared_ptr<ATM> ATM::getInstance() {
    if (not object_) object_ = make_shared<ATM>();
    return object_;
}

bool ATM::insertCard(const string& card_num) {
    auto bank = Bank::getInstance();
    return bank->verifyCard(card_num);
}

bool ATM::checkPIN() const {
    return Bank::getInstance()->verified();
}

int ATM::getBalance(int acc_op) const {
    return Bank::getInstance() -> getBalance(acc_op);
}

void ATM::deposit(int acc_op, unsigned int money) const {
    Bank::getInstance() -> deposit(acc_op, money);
}

bool ATM::withdraw(int acc_op, unsigned int money) const {
    return Bank::getInstance() ->withdraw(acc_op, money);
}