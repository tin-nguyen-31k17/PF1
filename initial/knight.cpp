#include "knight.h"

bool isInputValid(int hp, int level, int remedy, int maidenkiss, int phoenixdown) {
    return hp >= MIN_HP && hp <= MAX_HP &&
           level >= MIN_LEVEL && level <= MAX_LEVEL &&
           remedy >= MIN_REMEDY && remedy <= MAX_REMEDY &&
           maidenkiss >= MIN_MAIDENKISS && maidenkiss <= MAX_MAIDENKISS &&
           phoenixdown >= MIN_PHOENIXDOWN && phoenixdown <= MAX_PHOENIXDOWN;
}

bool isMountain(int* arr, int n)
{
    int check1 = 0;
    int check0 = 0;
    int check2 = 0;
    int check3 = 0;
    if (n < 3 && n > 1) return false;
    // Find the index of the largest element in the sequence
    int maxIndex = 0;
    for (int i = 1; i < n; i++) if (arr[i] > arr[maxIndex]) maxIndex = i;

    if (maxIndex == 0) 
    {
        for (int i = 0; i < n; i++)
        {
            if (arr[i] > arr[i+1]) check0 = 1;
            else check0 = 0;
        }
    }

    else if (maxIndex == n-1)
    {
        for (int i = 0; i < n; i++)
        {
            if (arr[i] < arr[i+1]) check3 = 1;
            else check3 = 0;
        }
    }

    else if (arr[maxIndex-1] > arr[maxIndex] && arr[maxIndex] > arr[maxIndex+1])
    {
        cout << check1 << " " << check2 << endl;
        for (int i = 0; i < maxIndex; i++) if (arr[i] > arr[i+1]) check1 = 1;
        for (int i = maxIndex; i < n; i++) if (arr[i] < arr[i+1]) check2 = 1;
    }

    else if (arr[maxIndex-1] < arr[maxIndex] && arr[maxIndex] < arr[maxIndex+1])
    {
        for (int i = 0; i < maxIndex; i++) if (arr[i] < arr[i+1]) check1 = 1;
        for (int i = maxIndex; i < n; i++) if (arr[i] > arr[i+1]) check2 = 1;
    }

    if (check1 == 1 && check2 == 1) return true;
    else if (check0 == 1 || check3 == 1) return true;
    else return false;
}

bool isPrime(int n) 
{
    if (n < 2) {
        return false;
    }
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

void handleHP(Knight& Knight)
{
    if (Knight.HP > Knight.O_HP) Knight.HP = Knight.O_HP;
    else if (Knight.HP < 0)
    {
        if (Knight.phoenixdown > 0) 
        {
            Knight.HP = Knight.O_HP;
            --Knight.phoenixdown;
        }
        else Knight.rescue = 0;
    }    
}

void handleOpponent(string opponentName, double baseDamage, Knight& Knight, int i) {
    int b = i % 10;
    int levelO = i > 6 ? (b > 5 ? b : 5) : b;
    if (Knight.level > levelO || Knight.King == 1 || Knight.Lancelot == 1) 
    {
        if (Knight.level < 10) {
            if ((opponentName == "Shaman" ||opponentName == "Siren Vajsh")  && Knight.level < 9) Knight.level += 2;
            else if (Knight.level == 9) ++Knight.level;
            else Knight.level++;
            
            if (Knight.tiny > 0) Knight.tiny--;
            else if (Knight.frog > 0) Knight.frog--;
        }
    }

    else if (Knight.level == levelO) 
    {
        if (Knight.tiny > 0) Knight.tiny--;
        if (Knight.frog > 0) Knight.frog--;
    }

    else 
    {
        if (opponentName != "Shaman" && opponentName != "Siren Vajsh")
        {
            int damage = baseDamage * levelO * 10;
            Knight.HP -= damage;
            if (Knight.HP <= 0) 
            {
                if (Knight.phoenixdown > 0) 
                {
                    Knight.HP = Knight.O_HP;
                    --Knight.phoenixdown;
                    if (Knight.tiny > 0) Knight.tiny--;
                    else if (Knight.frog > 0) Knight.frog--;
                }
                else Knight.rescue = 0;
            }
            if (Knight.HP > 0)
            {
                if (Knight.tiny > 0) Knight.tiny--;
                if (Knight.frog > 0) Knight.frog--;
                if (Knight.tiny == 0)
                {
                    Knight.HP = Knight.HP*5;
                    handleHP(Knight);
                }
                if (Knight.frog == 0) Knight.level = Knight.O_LV;
            }
        }
        else if ((opponentName == "Shaman" || opponentName == "Siren Vajsh") && (Knight.tiny > 0 || Knight.frog > 0))
        {
            if (Knight.tiny > 0)
            {
                Knight.tiny--;
                if (Knight.tiny == 0)
                {
                    Knight.HP = Knight.HP*5;
                    handleHP(Knight);
                }
            }
            if (Knight.frog > 0)
            {
                Knight.frog--;
                if (Knight.frog == 0) Knight.level = Knight.O_LV;
            }
        }
        else if (opponentName == "Shaman") 
        {
            // Combat with Shaman
            if (Knight.remedy > 0) --Knight.remedy;
            else 
            {
                // Knight is in tiny state for the next 3 events
                Knight.tiny = 3;
                if (Knight.HP < 5) Knight.HP = 1;
                else Knight.HP = Knight.HP / 5;
            }
        }

        else if (opponentName == "Siren Vajsh") 
        {
            // Combat with Siren Vajsh
            if (Knight.maidenkiss > 0) --Knight.maidenkiss;
            else 
            {
                // Knight is in frog state for the next 3 events
                Knight.frog = 3;
                Knight.O_LV = Knight.level;
                Knight.level = 1;
            }
        }
    }
}

void processEvent(int event_code, Knight& Knight, int i, string file) 
{
    if (Knight.rescue == -1)
    {
        switch(event_code) 
        {
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
                if (Knight.HP > 1) 
                {
                    int fib1 = 1, fib2 = 1, temp;
                    while (fib2 < Knight.HP) {
                        temp = fib2;
                        fib2 += fib1;
                        fib1 = temp;
                    }
                    // cout << fib2 << " " << fib1;
                    Knight.HP = Knight.HP - fib2 > Knight.HP - fib1 ? fib2 : fib1;
                }
                break;
            case 13:
            {
                // read file mush_ghost
                int n2;
                int num;
                char c;
                // ifstream fin(file);
                ifstream fin("file_mush_ghost.txt");
                if (!fin) {
                    cerr << "Unable to open mush file" << endl;
                    exit(EXIT_FAILURE);
                }
                fin >> n2;
                int* numbers = new int[n2];
                for (int j = 0; j < n2; j++) {
                    fin >> num >> c;
                    numbers[j] = num;
                }
                fin.close();
                // update knight's HP based on mushroom type
                switch (i) 
                {
                    case 1: 
                    {
                        int largest = numbers[0], min = numbers[0], maxi = 0, mini = 0;
                        for (int j = 0; j < n2; j++)
                        {
                            if (numbers[j] >= largest)
                            {
                                largest = numbers[j];
                                maxi = j;
                            }
                            if (numbers[j] <= min)
                            {
                                min = numbers[j];
                                mini = j;
                            }
                        }
                        // cout << maxi << " " << mini << endl;
                        Knight.HP -= (maxi + mini);
                        handleHP(Knight);
                        // cout << Knight.phoenixdown << endl;
                        break;
                    }
                    case 2: 
                    {
                        int mtx = -2, mti = -3;
                        if (isMountain(numbers, n2))
                        {
                            int largest = numbers[0];
                            for (int j = 0; j < n2; j++)
                            {
                                if (numbers[j] >= largest)
                                {
                                    mtx = numbers[j];
                                    mti = j;
                                    largest = numbers[j];
                                }
                            }
                        }
                        cout << mtx << " " << mti << endl;
                        Knight.HP -= (mtx + mti);
                        handleHP(Knight);
                        // cout << Knight.phoenixdown << endl;
                        break;
                    }
                    case 3: 
                    {       
                        int* n3 = numbers;
                        for (int i = 0; i < n2; i++) {
                            if (numbers[i] < 0) n3[i] = -numbers[i];

                            n3[i] = (17*numbers[i] + 9) % 257;
                        }
                        int largest = n3[0], min = n3[0], maxi2 = 0, mini2 = 0;
                        for (int j = 0; j < n2; j++)
                        {
                            if (n3[j] > largest)
                            {
                                largest = n3[j];
                                maxi2 = j;
                            }
                            if (n3[j] < min)
                                {
                                    min = n3[j];
                                    mini2 = j;
                                }
                        }
                        // cout << maxi2 << " " << mini2 << endl;
                        Knight.HP -= (maxi2 + mini2);
                        delete[] n3;
                        handleHP(Knight);
                        break;
                    }
                    case 4: 
                    {
                        int max23x = -5, max23i = -7;
                        int* n4 = numbers;
                        for (int i = 0; i < n2; i++) {
                            if (numbers[i] < 0) n4[i] = -numbers[i];
                            n4[i] = (17*numbers[i] + 9) % 257;
                            // cout << n4[i] << " ";
                        }
                        int max1 = -1, max2 = -1;
                        for (int j = 0; j < 3; ++j) 
                        {
                            if (n4[j] > max1)
                            {
                                max2 = max1;
                                max1 = n4[j];
                            }
                            else if (n4[j] > max2) max2 = n4[j];
                        }
                        if (max1 != max2)
                        {
                            max23x = max2;
                            for (int k = 0; k < 3; k++) if(n4[k] == max23x) max23i = k; 
                        }
                        Knight.HP -= (max23x + max23i);
                        delete[] n4;
                        handleHP(Knight);
                        // cout << Knight.phoenixdown << endl;
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            case 15: // Obtain recovery potion Remedy
                if(Knight.remedy < 99) Knight.remedy++;
                if (Knight.tiny > 0) 
                {
                    Knight.tiny--;
                    Knight.remedy--;
                    Knight.HP = Knight.O_HP;
                }
                break;
            case 16: // Obtain the antidote MaidenKiss
                if(Knight.maidenkiss < 99) Knight.maidenkiss++;
                if (Knight.frog > 0) 
                {
                    Knight.frog--;
                    Knight.maidenkiss--;
                }
                break;
            case 17: // Pick up the phoenix tear PhoenixDown
                if(Knight.phoenixdown < 99) Knight.phoenixdown++;
                break;
            case 18: // Meet Merlin
                {
                    Knight.Merlin++;
                    int n9;
                    string c;
                    ifstream fin(file);
                    // ifstream fin("file_merlin_pack.txt");
                    if (!fin) {
                        cerr << "Unable to open merlin file" << endl;
                        exit(EXIT_FAILURE);
                    }
                    fin >> n9;
                    string items[n9];
                    for (int j = 0; j < n9; j++) {
                        fin >> c;
                        items[j] = c;
                    }
                    fin.close();
                    for (int j = 0; j < n9; j++)
                    {
                        string line = items[j];
                        // cout << line << endl;
                        bool hasLetters = false, hasName = false;
                        int count = 0;
                        for (int k = 0; k < line.length(); k++)
                        {
                            char letter = tolower(line[k]);
                            if (letter == 'm' || letter == 'e' || letter == 'r' || letter == 'l' || letter == 'i' || letter == 'n') count++;
                        }
                        hasLetters = (count == 6);
                        hasName = (line.find("Merlin") != string::npos || line.find("merlin") != string::npos);
                        // cout << hasName << endl;
                        if (hasLetters && !hasName) Knight.HP += 2;
                        else if (hasName) Knight.HP += 3; 
                        handleHP(Knight);
                    }
                }
                break;
            case 19: // Meet Asclepius
                {
                    Knight.Asclep++;
                    int r1 = 0, c1 = 0;
                    int num = 0;
                    char c;
                    ifstream fin(file);
                    // ifstream fin("file_asclepius_pack.txt");
                    if (!fin) {
                        cerr << "Unable to open asclepius file" << endl;
                        exit(EXIT_FAILURE);
                    }
                    fin >> r1 >> c1;
                    for (int k = 0; k < r1; k++)
                    {
                        int count = 3;
                        for (int j = 0; j < c1; j++) 
                        {
                            fin >> num;
                            if ((num == 16 || num == 17 || num == 18) && count > 0) 
                            {
                                processEvent(num-1, Knight, 0, "");
                                --count;
                            }
                        }
                    }
                    fin.close();
                }
                break;
            case 99: // Meet Bowser
                if(Knight.level >= 10) Knight.rescue = 1;
                else Knight.HP -= 999;
                break;
            default:
                cerr << "Error: Unknown event code " << event_code << endl;
                break;
        }
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
    if (knight.HP == 999) knight.King = 1;
    if (isPrime(knight.HP)) knight.Lancelot = 1;

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

    // process line 2 n line 3
    while (iss2 >> num) arr[k++] = num;

    for (int i = 0; i < k && knight.HP > 0 && knight.rescue == -1; i++) 
    {
        string cCode = to_string(arr[i]).substr(0, 2);
        if (cCode == "13")
        {
            string mCode = to_string(arr[i]).substr(2);
            for (char c : mCode)
            {
                int mushType = c - '0';
                processEvent(13, knight, mushType, file_mush_ghost);
            }
        }
        else if (cCode == "19" && knight.Asclep == 0) processEvent(19, knight, i, file_asclepius_pack);
        else if (cCode == "18" && knight.Merlin == 0) processEvent(18, knight, i, file_merlin_pack);
        else if (cCode != "13" && cCode != "18" && cCode != "19") processEvent(arr[i], knight, i+1, "");

        if (i == k-1)
        {
            if (knight.HP > 0 && knight.rescue == -1) knight.rescue = 1;
            else if (knight.HP <= 0 && knight.rescue == -1)  knight.rescue = 0;
        }
        knight.display();
    }
    fin.close();
}