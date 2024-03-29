#ifndef __KNIGHT_H__
#define __KNIGHT_H__

const int MAX = 9999;

const int MIN_HP = 1;
const int MAX_HP = 999;

const int MIN_LEVEL = 1;
const int MAX_LEVEL = 10;

const int MIN_REMEDY = 0;
const int MAX_REMEDY = 99;

const int MIN_MAIDENKISS = 0;
const int MAX_MAIDENKISS = 99;

const int MIN_PHOENIXDOWN = 0;
const int MAX_PHOENIXDOWN = 99;

#include "main.h"

class Knight {
public:
    int HP;
    int level;
    int remedy;
    int maidenkiss;
    int phoenixdown;
    int rescue;
    int O_HP;
    int tiny;
    int frog;
    int O_LV;
    int Merlin;
    int Asclep;
    int King;
    int Lancelot;

    Knight(int hp, int lvl, int rmdy, int mdk, int pdown) :
        HP(hp), level(lvl), remedy(rmdy), maidenkiss(mdk), phoenixdown(pdown), rescue(-1), tiny(-1), frog(-1), O_HP(HP), Merlin(0), Asclep(0), King(0), Lancelot(0) {}

    void display() {
        cout << "HP=" << HP
            << ", level=" << level
            << ", remedy=" << remedy
            << ", maidenkiss=" << maidenkiss
            << ", phoenixdown=" << phoenixdown
            << ", rescue=" << rescue << endl;
    }
};

bool isInputValid(int hp, int level, int remedy, int maidenkiss, int phoenixdown);
bool isMountain(int arr[], int n);
bool isPrime(int n);
void handleHP(Knight& Knight);
void processEvent(int event_code, Knight& Knight, int i, string file);
void handleOpponent(string opponentName, double baseDamage, Knight& Knight, int i);
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);

#endif // __KNIGHT_H__
