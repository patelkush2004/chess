#include <iostream>
#include <string>
#include <vector>
#include "board.h"
#include "player.h"
#include "textdisplay.h"

using namespace std;

int main() {

    // testing interface code

    Player *p1 = new Player("white");
    Player *p2 = new Player("black");

    Board b (p1, p2);
    
    cout << b;
    

    delete p1;
    delete p2;

}

