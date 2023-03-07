#include "knight.h"

void handleOpponent(string opponentName, double baseDamage, Knight& Knight) {
    int b = Knight.level % 10;
    int levelO = Knight.level > 6 ? (b > 5 ? b : 5) : b;

    cout << "Knight's level: " << Knight.level << endl;
    cout << "Opponent's level: " << levelO << endl;

    if (Knight.level > levelO) {
        cout << "Knight wins!" << endl;
        if (Knight.level < 10) {
            ++Knight.level;
            cout << "Knight's level increased to " << Knight.level << endl;
        }
    } else if (Knight.level == levelO) {
        cout << "Draw!" << endl;
    } else {
        cout << "Opponent wins!" << endl;
        int damage = baseDamage * levelO * 10;
        Knight.HP -= damage;
        cout << "Knight's HP reduced by " << damage << " to " << Knight.HP << endl;
        if (Knight.HP <= 0) {
            if (Knight.phoenixdown > 0) {
                cout << "Knight uses PhoenixDown to restore HP!" << endl;
                Knight.HP = MAX_HP;
                --Knight.phoenixdown;
            } else {
                cout << "Knight is defeated! Game over." << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
}

void processEvent(int event_code, Knight& Knight) {
    switch(event_code) {
        case 0: // Bowser surrendered and handed over the princess
            Knight.rescue = 1;
            break;
        case 1: // Meet MadBear
            handleOpponent("MadBear", 1, Knight);
            break;
        case 2: // Meet Bandit
            handleOpponent("Bandit", 1.5, Knight);
            break;
        case 3: // Meet LordLupin
            handleOpponent("LordLupin", 4.5, Knight);
            break;
        case 4: // Meet Elf
            handleOpponent("Elf", 7.5, Knight);
            break;
        case 5: // Meet Troll
            handleOpponent("Troll", 9.5, Knight);
            break;
        case 6: // Meet Shaman
            if(Knight.level >= 2) {
                Knight.HP += 10;
            } else {
                Knight.HP -= 15;
            }
            break;
        case 7: // Meet Siren Vajsh
            if(Knight.level >= 9) {
                Knight.HP += 50;
            } else {
                Knight.HP -= 70;
            }
            break;
        case 11: // Pick up the power-up mushroom MushMario
            Knight.level += 1;
            break;
        case 12: // Pick up the Fibonacci mushroom MushFib
            Knight.level += 2;
            break;
        case 13: // Pick up the ghost mushroom MushGhost
            Knight.maidenkiss += 1;
            break;
        case 15: // Obtain recovery potion Remedy
            Knight.remedy += 1;
            break;
        case 16: // Obtain the antidote MaidenKiss
            Knight.maidenkiss += 1;
            break;
        case 17: // Pick up the phoenix tear PhoenixDown
            Knight.phoenixdown += 1;
            break;
        case 18: // Meet Merlin
            Knight.level += 3;
            break;
        case 19: // Meet Asclepius
            Knight.remedy += 3;
            break;
        case 99: // Meet Bowser
            if(Knight.level >= 10) {
                Knight.rescue = 1;
            } else {
                Knight.HP -= 999;
            }
            break;
        default:
            cerr << "Error: Unknown event code " << event_code << endl;
            break;
    }
}

void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    ifstream fin(file_input);
    if (!fin) {
        cerr << "Unable to open input file" << endl;
        exit(EXIT_FAILURE);
    }

    // read first line
    string line;
    if (!getline(fin, line)) {
        cerr << "Error reading first line from input file" << endl;
        exit(EXIT_FAILURE);
    }

    istringstream iss(line);
    if (!(iss >> HP >> level >> remedy >> maidenkiss >> phoenixdown)) {
        cerr << "Error parsing first line in input file" << endl;
        exit(EXIT_FAILURE);
    }
    Knight knight(HP, level, remedy, maidenkiss, phoenixdown);

    // read second line
    if (!getline(fin, line)) {
        cerr << "Error reading second line from input file" << endl;
        exit(EXIT_FAILURE);
    }

    string event = line;
    for (int i = 0; i < event.length(); i++) {
        // check if journey is over due to successful rescue
        if (knight.rescue == 1) {
            break;
        }

        // process event
        if(event[i] != ' '){
            cout << event[i] << endl;
            int code = event[i] - '0';
            cout << code << endl;
            processEvent(code, knight);
        }
        // check if journey is over due to unsuccessful rescue
        if (knight.rescue == 0) {
            break;
        }
    }

    if (knight.rescue == -1) {
        cerr << "Journey is not over" << endl;
    }

    // read third line
    if (!getline(fin, line)) {
        cerr << "Error reading third line from input file" << endl;
        exit(EXIT_FAILURE);
    }

    stringstream ss(line);
    string file_mush_ghost, file_asclepius_pack, file_merlin_pack;
    getline(ss, file_mush_ghost, ',');
    getline(ss, file_asclepius_pack, ',');
    getline(ss, file_merlin_pack);

    fin.close();
    knight.display();
}