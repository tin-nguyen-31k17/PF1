void handleMushroom(int mushroomType, int &HP, int MaxHP, const string& file_mush_ghost) {
    // read file_mush_ghost
    ifstream fin(file_mush_ghost);
    int n2;
    fin >> n2;
    vector<int> numbers(n2);
    for (int i = 0; i < n2; i++) {
        int num;
        char c;
        fin >> num >> c;
        if (mushroomType == 3 && num < 0) {
            num = -num;
        }
        num = (17*num + 9) % 257;
        numbers[i] = num;
    }
    fin.close();

    // update knight's HP based on mushroom type
    switch (mushroomType) {
        case 1: {
            int maxi = *max_element(numbers.begin(), numbers.end());
            int mini = *min_element(numbers.begin(), numbers.end());
            HP -= (maxi + mini);
            break;
        }
        case 2: {
            bool isMountain = true;
            int mtx = -2, mti = -3;
            for (int i = 0; i < (int)numbers.size() - 1; i++) {
                if (numbers[i] >= numbers[i+1]) {
                    isMountain = false;
                    break;
                }
            }
            if (isMountain) {
                mtx = *max_element(numbers.begin(), numbers.end());
                mti = max_element(numbers.begin(), numbers.end()) - numbers.begin();
            }
            HP -= (mtx + mti);
            break;
        }
        case 3: {
            int maxi2 = max_element(numbers.begin(), numbers.end()) - numbers.begin();
            int mini2 = min_element(numbers.begin(), numbers.end()) - numbers.begin();
            HP -= (maxi2 + mini2);
            break;
        }
        case 4: {
            int max23x = -5, max23i = -7;
            if (numbers.size() >= 3) {
                int max1 = numbers[0], max2 = -1, max3 = -1;
                int max1i = 0, max2i = -1, max3i = -1;
                for (int i = 1; i < 3; i++) {
                    if (numbers[i] > max1) {
                        max1 = numbers[i];
                        max1i = i;
                    }
                }
                for (int i = 3; i < (int)numbers.size(); i++) {
                    if (numbers[i] > max1) {
                        max3 = max2;
                        max3i = max2i;
                        max2 = max1;
                        max2i = max1i;
                        max1 = numbers[i];
                        max1i = i;
                    } else if (numbers[i] > max2) {
                        max3 = max2;
                        max3i = max2i;
                        max2 = numbers[i];
                        max2i = i;
                    } else if (numbers[i] > max3) {
                        max3 = numbers[i];
                        max3i = i;
                    }
                }
                if (max2 != -1) {
                    max23x = max2;
                    max23i = max2i;
                }
            }
            HP -= (max23x + max23i);
            break;
        }
        default:
            break;
    }
}
