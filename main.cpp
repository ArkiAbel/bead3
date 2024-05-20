
#include "Gamemaster.hpp"
#include "Ships.hpp"

#include <vector>
#include <string>
#include <ctime>
#include <functional>

using namespace std;

const int XX = 1400;
const int YY = XX/2;

int main() {

    vector<Reserved>rl;
    vector<Reserved>rr;

    vector<Ship>cv; //carrier
    vector<Ship>bv; //battleship
    vector<Ship>crv; //cruiser
    vector<Ship>sv; //submarine
    vector<Ship>dv; //destroyer

    vector<Reserved>sol; //shot on left
    vector<Reserved>sor; //shot on right

    vector<string> b; //koordinatak
    vector<int> sz;

    //kezdojatekos
    string kezdo = "elso";

    Gamemaster gm = Gamemaster(true,false,false,true,false,false,false,kezdo,false);
    Ships sh = Ships(false,cv,bv,crv,sv,dv,true,true);
    sh.generate_ships_left(rl);
    sh.generate_ships_right(rr);
    gm.win_open(XX,YY);
    gm.info_load(b,sz);
    gm.event_loop(b,sz,rl,rr,sol,sor,false);

    return 0;
}
