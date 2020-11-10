#include "ATM.h"
#include <iostream>

using namespace std;

int main() {
    auto atm = ATM::getInstance();
    string card_num;
    cout << "insert card" << endl;
    cin >> card_num;
    if (not atm->insertCard(card_num)) {
        cout << "invalid card" << endl;
        return 1;
    }
    auto bank = Bank::getInstance();
    for (int i = 0; i < 5; i++) {
        cout << "enter PIN" << endl;
        string pin;
        cin >> pin;
        if (not bank->verifyPin(pin)) cout << "PIN not correct" << endl;
        else break;
    }
    if (not bank->verified()) {
        cout << "too much trial for PIN" << endl;
        return 1;
    }
    const auto& acc_list = bank->getAccList();
    for (int i = 0; i < acc_list.size(); i++) {
        cout << i << ". " << acc_list[i] << endl;
    }
    int acc_op = -1;
    for (int i = 0; i < 5; i++) {
        cout << "choose account:" << endl;
        cin >> acc_op;
        if (acc_op <acc_list.size() and acc_op >= 0) break;
    }
    if (acc_op >= acc_list.size() and acc_op < 0) {
        cout << "wrong choice of account" << endl;
        return 1;
    }
    cout << "your balance is " << atm->getBalance(acc_op) << endl;
    return 0;
}