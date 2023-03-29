#include "knight.h"

int main(int argc, char ** argv) {
    string file_input(argv[1]);
    // string file_mush_ghost(argv[2]);
    int HP, level, remedy, maidenkiss, phoenixdown, rescue;
    adventureToKoopa(file_input, HP, level, remedy, maidenkiss, phoenixdown, rescue);
    return 0;
}