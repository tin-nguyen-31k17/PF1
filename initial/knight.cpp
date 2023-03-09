#include "knight.h"

bool isInputValid(int hp, int level, int remedy, int maidenkiss, int phoenixdown) {
    return hp >= MIN_HP && hp <= MAX_HP &&
           level >= MIN_LEVEL && level <= MAX_LEVEL &&
           remedy >= MIN_REMEDY && remedy <= MAX_REMEDY &&
           maidenkiss >= MIN_MAIDENKISS && maidenkiss <= MAX_MAIDENKISS &&
           phoenixdown >= MIN_PHOENIXDOWN && phoenixdown <= MAX_PHOENIXDOWN;
}

void handleOpponent(string opponentName, double baseDamage, Knight& Knight, int i) {
    int b = i % 10;
    int levelO = Knight.level > 6 ? (b > 5 ? b : 5) : b;
    
    if (Knight.level > levelO || Knight.O_HP == 999) 
    {
        if (Knight.level < 10) {
            if ((opponentName == "Shaman" ||opponentName == "Siren Vajish")  && Knight.level < 9) Knight.level += 2;
            else if (Knight.level == 9) ++Knight.level;
            if (Knight.tiny > 0) Knight.tiny--;
            if (Knight.frog > 0) Knight.frog--;
        }
    }

    else if (Knight.level == levelO) 
    {
        cout << "Draw!" << endl;
        if (Knight.tiny > 0) Knight.tiny--;
        if (Knight.frog > 0) Knight.frog--;
    }

    else 
    {
        cout << "Opponent wins!" << endl;

        if (Knight.tiny > 0) Knight.tiny--;
        if (Knight.frog > 0) Knight.frog--;

        if (opponentName != "Shaman")
        {
            int damage = baseDamage * levelO * 10;
            Knight.HP -= damage;
        }
        if (opponentName == "Shaman") 
        {
        // Combat with Shaman
            if (Knight.remedy > 0) {
                --Knight.remedy;
            } else {
                // Knight is in tiny state for the next 3 events
                Knight.tiny = 3;
                if (Knight.HP < 5) {
                    Knight.HP = 1;
                } else {
                    Knight.HP = Knight.HP / 5;
                }
            }
        }

        if (opponentName == "Siren Vajsh") 
        {
        // Combat with Siren Vajsh
            if (Knight.maidenkiss > 0) {
                --Knight.maidenkiss;
            } else {
                // Knight is in frog state for the next 3 events
                Knight.frog = 3;
                Knight.O_LV = Knight.level;
            }
        }
        
        if (Knight.HP <= 0) 
        {
            if (Knight.phoenixdown > 0) {
                Knight.HP = Knight.O_HP;
                --Knight.phoenixdown;
            } else {
            }
        }
    }
}

void processEvent(int event_code, Knight& Knight, int i) {
    switch(event_code) {
        case 0: // Bowser surrendered and handed over the princess
            Knight.rescue = 1;
            break;
        case 1: // Meet MadBear
            handleOpponent("MadBear", 1, Knight, i);
            break;
        case 2: // Meet Bandit
            handleOpponent("Bandit", 1.5, Knight, i);
            break;
        case 3: // Meet LordLupin
            handleOpponent("LordLupin", 4.5, Knight, i);
            break;
        case 4: // Meet Elf
            handleOpponent("Elf", 7.5, Knight, i);
            break;
        case 5: // Meet Troll
            handleOpponent("Troll", 9.5, Knight, i);
            break;
        case 6: // Meet Shaman
            handleOpponent("Shaman", 0, Knight, i);
            break;
        case 7: // Meet Siren Vajsh
            handleOpponent("Siren Vajsh", 0, Knight, i);
            break;
        case 11: // Pick up the power-up mushroom MushMario
            {
                int n1 = ((Knight.level + Knight.phoenixdown) % 5 + 1) * 3;
                int s1 = 0;
                for (int i = 99; i > 0; i -= 2) {
                    if (n1 > 0) {
                        s1 += i;
                        n1--;
                    } else break;
                }
                Knight.HP += s1 % 100;
                int new_HP = Knight.HP;
                bool is_prime = false;
                while (!is_prime) {
                    new_HP++;
                    is_prime = true;
                    for (int j = 2; j <= sqrt(new_HP); j++) {
                        if (new_HP % j == 0) {
                            is_prime = false;
                            break;
                        }
                    }
                }
                if (new_HP > Knight.O_HP) {
                    new_HP = Knight.O_HP;
                }
                Knight.HP = new_HP;
            }
            break;
        case 12: // Pick up the Fibonacci mushroom MushFib
            if (Knight.HP > 1) {
                int fib1 = 1, fib2 = 1, temp;
                while (fib2 <= Knight.HP) {
                    temp = fib2;
                    fib2 += fib1;
                    fib1 = temp;
                }
                Knight.HP = fib2 - Knight.HP < Knight.HP - fib1 ? fib2 : fib1;
            }
            break;
        case 13: // Pick up the ghost mushroom MushGhost
            Knight.maidenkiss += 1;
            break;
        case 15: // Obtain recovery potion Remedy
            if(Knight.remedy < 99) Knight.remedy++;
            break;
        case 16: // Obtain the antidote MaidenKiss
            if(Knight.maidenkiss < 99) Knight.maidenkiss++;
            break;
        case 17: // Pick up the phoenix tear PhoenixDown
            if(Knight.phoenixdown < 99) Knight.phoenixdown++;
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

    if (!isInputValid(HP, level, remedy, maidenkiss, phoenixdown))
    {
        cout << "Wrong input data";
        exit(EXIT_FAILURE);
    }

    // read second line
    if (!getline(fin, line)) {
        cerr << "Error reading second line from input file" << endl;
        exit(EXIT_FAILURE);
    }

    istringstream iss2(line);
    int num;
    int arr[line.size()];
    int k = 0;

    while (iss2 >> num) arr[k++] = num;

    for (int i = 0; i < k && knight.HP > 0 && knight.rescue == -1; i++) {
        processEvent(arr[i], knight, i+1);
    }
    if (knight.tiny == 0) knight.HP = knight.HP * 5;

    if (knight.frog == 0) knight.level = knight.O_LV;

    if (knight.HP > 0 && knight.rescue == -1) knight.rescue = 1;

    else if (knight.HP <= 0 && knight.rescue == -1)  knight.rescue = 0;

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