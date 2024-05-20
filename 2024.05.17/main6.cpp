//
#include "graphics.hpp"
//
#include <vector>
#include <string>
#include <ctime>
#include <functional>

using namespace std;
//
using namespace genv;
//

const int XX = 1400;
const int YY = XX/2;

//osszdata
struct Reserved {
    int x, y;
    string id;
};

//hajok tablazata
struct Ship {
    int x, y;
    string id;
};

//legordulo widget loszertipus kivalasztasahoz
class Ammoselect_widget {
protected:
public:

};

//jatekmester
class Gamemaster {
    protected:

    bool IsMenu;
    bool IsGame;
    bool Player_1_Turn;
    bool Player_2_Turn;

    public:

    Gamemaster(bool im, bool ig, bool p1t, bool p2t) : IsMenu(im), IsGame(ig), Player_1_Turn(p1t), Player_2_Turn(p2t) {};
};

//kivalaszto widget
class Sea : public Gamemaster {
    protected:

    int on_field_x;
    int on_field_y;
    bool OnShip;

    public:

    Sea(bool IsMenu, bool IsGame, bool Player_1_Turn, bool Player_2_Turn, int ofx, int ofy, bool os) :
        Gamemaster(IsMenu, IsGame, Player_1_Turn, Player_2_Turn), on_field_x(ofx), on_field_y(ofy), OnShip(os) {};

    void event_loop(vector<string> b, vector<int> sz, vector<Reserved> &rl, vector<Reserved> &rr, vector<Reserved> &sol, vector<Reserved> &sor, bool left_ok);
    void win_open(const int XX,const int YY);
    void info_load(vector<string> &b, vector<int> &sz);
    void shot(vector<Reserved> &rl, vector<Reserved> &rr);
};

//tobbi hajo struct-ja

class Ships : public Sea {
    protected:

    vector<Ship>cv;
    vector<Ship>bv;
    vector<Ship>crv;
    vector<Ship>sv;
    vector<Ship>dv;
    bool left_ok;
    bool right_ok;
    //tobbi hajo vektora

    public:

    Ships(bool IsMenu, bool IsGame, bool Player_1_Turn, bool Player_2_Turn, int on_field_x, int on_field_y, bool os, vector<Ship>cv,
           vector<Ship>bv, vector<Ship>crv, vector<Ship>sv, vector<Ship>dv, bool lo, bool ro) :
        Sea(IsMenu, IsGame, Player_1_Turn, Player_2_Turn, on_field_x, on_field_y, os), cv(cv),
         bv(bv), crv(crv), sv(sv), dv(dv), left_ok(lo), right_ok(ro) {}

    //fuggvenybe fuggvenyt hogy?
    void f_in_f();

    bool Getleft_ok() {return left_ok;}
    bool Getright_ok() {return right_ok;}

    //vizsgaljuk a hajok szabalyos ehelyezkedeset
    void left_check(vector<Reserved> rl);
    void right_check(vector<Reserved> rl);

    void generate_ships_left(vector<Reserved> &rl);
    void generate_ships_right(vector<Reserved> &rr);
};

void Sea::event_loop(vector<string> b, vector<int> sz, vector<Reserved> &rl,
                      vector<Reserved> &rr, vector<Reserved> &sol, vector<Reserved> &sor,
                      bool left_ok) {
    event ev;
    Reserved res;
    gout.showmouse(false);

    int epos_x;
    int epos_y;

    std::function<void()> base_squares;
        base_squares = [](){gout << color(255,255,200) << move_to(0,0) << box(XX,YY) << color(0,0,0);
        gout << font("LiberationSans-Regular.ttf",20);
        gout << color(255,0,0) << move_to(100,100) << box(YY-199,YY-199);
        gout << color(0,0,255) << move_to(XX/2+100,100) << box(YY-199,YY-199);};

    std::function<void(bool,int,int)> cursor_refresh;
        cursor_refresh = [](bool OnShip,int epos_x,int epos_y){if (OnShip) {
                gout << color(0,0,0) << move_to(epos_x-10,epos_y-10) << box(4,10);
                gout << move_to(epos_x-10,epos_y-10) << box(10,4);

                gout << move_to(epos_x+10,epos_y-10) << box(-10,4);
                gout<< move_to(epos_x+10,epos_y-10) << box(-4,10);

                gout << move_to(epos_x+10,epos_y+10) << box(-4,-10);
                gout << move_to(epos_x+10,epos_y+10) << box(-10,-4);

                gout << move_to(epos_x-10,epos_y+10) << box(10,-4);
                gout << move_to(epos_x-10,epos_y+10) << box(4,-10);
            }
            else {
                gout << color(0,0,0) << move_to(epos_x-20,epos_y-2) << box(40,4);
                gout << move_to(epos_x-2,epos_y-20) << box(4,40);
            }
        };

    std::function<void(bool,bool)> playerturn_text;
        playerturn_text = [](bool Player_1_Turn,bool Player_2_Turn){if (Player_1_Turn) {
            gout << color(255,0,0) << move_to(XX/2-gout.twidth("PLAYER 1 TURN")/2,20) << text("PLAYER 1 TURN");
        }
        if (Player_2_Turn) {
            gout << color(0,0,255) << move_to(XX/2-gout.twidth("PLAYER 2 TURN")/2,20) << text("PLAYER 2 TURN");
        }};

    std::function<void()> player_tags;
        player_tags = [](){string p1 = "PLAYER 1"; string p2 = "PLAYER 2";
        gout << font("LiberationSans-Regular.ttf",30);
        gout << color(255,0,0) << move_to(100,100-gout.cascent()-5) << text(p1);
        gout << color(0,0,255) << move_to(XX-100-gout.twidth(p2),100-gout.cascent()-5) << text(p2);};

    std::function<void(bool,vector<Reserved> &,int,int)> player1_ships;
        player1_ships = [](bool Player_1_Turn,vector<Reserved>&rl,int XX,int YY){if(Player_1_Turn) {
            for (int k = 0; k < rl.size(); k++) {
                if (rl[k].id == "CAR") {
                    gout << color(170,0,0) << move_to(((YY-200)/10)*rl[k].x+101,((YY-200)/10)*rl[k].y+101) << box((YY-200)/10-2,(YY-200)/10-2);
                }
                else if (rl[k].id == "BAT") {
                    gout << color(190,0,0) << move_to(((YY-200)/10)*rl[k].x+101,((YY-200)/10)*rl[k].y+101) << box((YY-200)/10-2,(YY-200)/10-2);
                }
                else if (rl[k].id == "CRU") {
                    gout << color(210,0,0) << move_to(((YY-200)/10)*rl[k].x+101,((YY-200)/10)*rl[k].y+101) << box((YY-200)/10-2,(YY-200)/10-2);
                }
                else if (rl[k].id == "SUB") {
                    gout << color(230,0,0) << move_to(((YY-200)/10)*rl[k].x+101,((YY-200)/10)*rl[k].y+101) << box((YY-200)/10-2,(YY-200)/10-2);
                }
                else if (rl[k].id == "DES") {
                    gout << color(250,0,0) << move_to(((YY-200)/10)*rl[k].x+101,((YY-200)/10)*rl[k].y+101) << box((YY-200)/10-2,(YY-200)/10-2);
                }
            }
        }};

    std::function<void(bool,vector<Reserved> &,int,int)> player2_ships;
        player2_ships = [](bool Player_2_Turn,vector<Reserved>&rr,int XX,int YY){if (Player_2_Turn) {
            for (int k = 0; k < rr.size(); k++) {
                if (rr[k].id == "CAR") {
                    gout << color(0,0,170) << move_to(((YY-200)/10)*rr[k].x+101+XX/2,((YY-200)/10)*rr[k].y+101) << box((YY-200)/10-2,(YY-200)/10-2);
                }
                else if (rr[k].id == "BAT") {
                    gout << color(0,0,190) << move_to(((YY-200)/10)*rr[k].x+101+XX/2,((YY-200)/10)*rr[k].y+101) << box((YY-200)/10-2,(YY-200)/10-2);
                }
                else if (rr[k].id == "CRU") {
                    gout << color(0,0,210) << move_to(((YY-200)/10)*rr[k].x+101+XX/2,((YY-200)/10)*rr[k].y+101) << box((YY-200)/10-2,(YY-200)/10-2);
                }
                else if (rr[k].id == "SUB") {
                    gout << color(0,0,230) << move_to(((YY-200)/10)*rr[k].x+101+XX/2,((YY-200)/10)*rr[k].y+101) << box((YY-200)/10-2,(YY-200)/10-2);
                }
                else if (rr[k].id == "DES") {
                    gout << color(0,0,250) << move_to(((YY-200)/10)*rr[k].x+101+XX/2,((YY-200)/10)*rr[k].y+101) << box((YY-200)/10-2,(YY-200)/10-2);
                }
            }
        }};

    std::function<void(bool &,bool &,vector<Reserved>&,vector<Reserved>&)> player1_shot;
        player1_shot = [](bool &Player_2_Turn,bool &Player_1_Turn,vector<Reserved>&sor,vector<Reserved>&rr){for (int k = 0; k < sor.size(); k++) {
            for (int l = 0; l < rr.size(); l++) {
                if (rr[l].x == sor[k].x && rr[l].y == sor[k].y) {
                    gout << color(255,0,0) << move_to(((YY-200)/10)*sor[k].x+101+XX/2+13,((YY-200)/10)*sor[k].y+101+13) << box(20,20);
                    Player_1_Turn = true;
                    Player_2_Turn = false;
                    break;
                }
                else {
                    gout << color(255,255,255) << move_to(((YY-200)/10)*sor[k].x+101+XX/2+13,((YY-200)/10)*sor[k].y+101+13) << box(20,20);
                    Player_2_Turn = true;
                    Player_1_Turn = false;
                }
            }
        }};

    std::function<void(bool &,bool &,vector<Reserved>&,vector<Reserved>&)> player2_shot;
        player2_shot = [](bool &Player_1_Turn,bool &Player_2_Turn,vector<Reserved>&sol,vector<Reserved>&rl){for (int k = 0; k < sol.size(); k++) {
            for (int l = 0; l < rl.size(); l++) {
                if (rl[l].x == sol[k].x && rl[l].y == sol[k].y) {
                    gout << color(255,0,0) << move_to(((YY-200)/10)*sol[k].x+101+13,((YY-200)/10)*sol[k].y+101+13) << box(20,20);
                    Player_2_Turn = true;
                    Player_1_Turn = false;
                    break;
                }
                else {
                    gout << color(255,255,255) << move_to(((YY-200)/10)*sol[k].x+101+13,((YY-200)/10)*sol[k].y+101+13) << box(20,20);
                    Player_1_Turn = true;
                    Player_2_Turn = false;
                }
            }
        }};

    std::function<void()> set_textsize;
        set_textsize = [](){gout << font("LiberationSans-Regular.ttf",20);};

    std::function<void()> screen_refresh;
        screen_refresh = [](){gout << refresh;};

    while (gin >> ev && ev.keycode != key_escape) {
        if (ev.type == ev_mouse) {
            epos_x = ev.pos_x;
            epos_y = ev.pos_y;
        }

        base_squares();

        //bal oldal
        for (int i = 0; i < 10; i++) {
            //nagy negyzet
            if (epos_x >= ((YY-200)/10)*i+101 && epos_x <= ((YY-200)/10)*i+101+((YY-200)/10)) {
                gout << color(255,0,0) << move_to(100+i*(XX/2-200)/10+15,YY-100+15) << text(b[i]);
            }
            else {
                gout << color(255,200,200) << move_to(100+i*(XX/2-200)/10+15,YY-100+15) << text(b[i]);
            }
            for (int j = 0; j < 10; j++) {
                if (epos_y >= ((YY-200)/10)*j+101 && epos_y <= ((YY-200)/10)*j+101+((YY-200)/10) && epos_x <= XX/2) {
                    gout << color(255,0,0) << move_to(XX/2-100+15,100+j*(YY-200)/10+15) << text(to_string(sz[j]));
                }
                else {
                    gout << color(255,200,200) << move_to(XX/2-100+15,100+j*(YY-200)/10+15) << text(to_string(sz[j]));
                }
                if (epos_x >= ((YY-200)/10)*j+101 && epos_x <= ((YY-200)/10)*j+101+((YY-200)/10) &&
                    epos_y >= ((YY-200)/10)*i+101 && epos_y <= ((YY-200)/10)*i+101+((YY-200)/10)) {
                    if (ev.button == btn_left && Player_2_Turn) {
                        res.x = j;
                        res.y = i;
                        //res.id = "-";
                        sol.push_back(res);
                    }
                    gout << color(150,150,150) << move_to(((YY-200)/10)*j+101,((YY-200)/10)*i+101) <<
                    box((YY-200)/10 - 2,(YY-200)/10 - 2);
                }
                else {
                    gout << color(0,0,0) << move_to(((YY-200)/10)*j+101,((YY-200)/10)*i+101) <<
                    box((YY-200)/10 - 2,(YY-200)/10 - 2);
                }
            }
        }

        //jobb oldal
        for (int i = 0; i < 10; i++) {
            if (epos_x >= ((YY-200)/10)*i+101+XX/2 && epos_x <= ((YY-200)/10)*i+XX/2+101+((YY-200)/10)) {
                gout << color(0,0,255) << move_to(100+XX/2+i*(XX/2-200)/10+15,YY-100+15) << text(b[i]);
            }
            else {
                gout << color(200,200,255) << move_to(100+XX/2+i*(XX/2-200)/10+15,YY-100+15) << text(b[i]);
            }
            for (int j = 0; j < 10; j++) {
                if (epos_y >= ((YY-200)/10)*j+101 && epos_y <= ((YY-200)/10)*j+101+((YY-200)/10) && epos_x >= XX/2) {
                    gout << color(0,0,255) << move_to(XX/2+100-25,100+j*(YY-200)/10+15) << text(to_string(sz[j]));
                }
                else {
                    gout <<color(200,200,255) << move_to(XX/2+100-25,100+j*(YY-200)/10+15) << text(to_string(sz[j]));
                }
                if (epos_x >= ((YY-200)/10)*j+101+XX/2 && epos_x <= ((YY-200)/10)*j+XX/2+101+((YY-200)/10) &&
                    epos_y >= ((YY-200)/10)*i+101 && epos_y <= ((YY-200)/10)*i+101+((YY-200)/10)) {
                    if (ev.button == btn_left && Player_1_Turn) {
                        res.x = j;
                        res.y = i;
                        //res.id = "-";
                        sor.push_back(res);
                    }
                    gout << color(150,150,150) << move_to(((YY-200)/10)*j+XX/2+101,((YY-200)/10)*i+101) <<
                    box((YY-200)/10 - 2,(YY-200)/10 - 2);
                }
                else {
                    gout << color(0,0,0) << move_to(((YY-200)/10)*j+XX/2+101,((YY-200)/10)*i+101) <<
                    box((YY-200)/10 - 2,(YY-200)/10 - 2);
                }
            }
        }

        player_tags();
        player1_ships(Player_1_Turn,rl,XX,YY);
        player2_ships(Player_2_Turn,rr,XX,YY);
        //hibas resz
        player1_shot(Player_2_Turn,Player_1_Turn,sor,rr);
        player1_shot(Player_1_Turn,Player_2_Turn,sol,rl);
        //
        playerturn_text(Player_1_Turn,Player_2_Turn);
        set_textsize();

        //hatulrol indexeles, hogy a lagutoljara rajzoltat csekkolja, pop_back eseten szet kell szedni majd
        for (int k = rl.size(); k >= 0; k--) {
            if (Player_1_Turn && epos_x >= ((YY-200)/10)*rl[k].x+101 && epos_x <= ((YY-200)/10)*rl[k].x+101+((YY-200)/10) &&
                epos_y >= ((YY-200)/10)*rl[k].y+101 && epos_y <= ((YY-200)/10)*rl[k].y+101+((YY-200)/10)) {
                OnShip = true;
                if (rl[k].id == "CAR") {
                    gout << move_to(epos_x+25,epos_y-10) << color(0,0,0) << box(gout.twidth("Carrier")+10,gout.cascent()+5)
                    << color(255,150,150) << move_to(epos_x+30,epos_y-10) << text("Carrier");
                }
                else if (rl[k].id == "BAT") {
                    gout << move_to(epos_x+25,epos_y-10) << color(0,0,0) << box(gout.twidth("Battleship")+10,gout.cascent()+5)
                    << color(255,150,150) << move_to(epos_x+30,epos_y-10) << text("Battleship");
                }
                else if (rl[k].id == "CRU") {
                    gout << move_to(epos_x+25,epos_y-10) << color(0,0,0) << box(gout.twidth("Cruiser")+10,gout.cascent()+5)
                    << color(255,150,150) << move_to(epos_x+30,epos_y-10) << text("Cruiser");
                }
                else if (rl[k].id == "SUB") {
                    gout << move_to(epos_x+25,epos_y-10) << color(0,0,0) << box(gout.twidth("Submarine")+10,gout.cascent()+5)
                    << color(255,150,150) << move_to(epos_x+30,epos_y-10) << text("Submarine");
                }
                else if (rl[k].id == "DES") {
                    gout << move_to(epos_x+25,epos_y-10) << color(0,0,0) << box(gout.twidth("Destroyer")+10,gout.cascent()+5)
                    << color(255,150,150) << move_to(epos_x+30,epos_y-10) << text("Destroyer");
                }
                break;
            }
            if (Player_2_Turn && epos_x >= ((YY-200)/10)*rr[k].x+101+XX/2 && epos_x <= ((YY-200)/10)*rr[k].x+101+XX/2+((YY-200)/10) &&
                epos_y >= ((YY-200)/10)*rr[k].y+101 && epos_y <= ((YY-200)/10)*rr[k].y+101+((YY-200)/10)) {
                OnShip = true;
                if (rr[k].id == "CAR") {
                    gout << move_to(epos_x+25,epos_y-10) << color(0,0,0) << box(gout.twidth("Carrier")+10,gout.cascent()+5)
                    << color(150,150,255) << move_to(epos_x+30,epos_y-10) << text("Carrier");
                }
                else if (rr[k].id == "BAT") {
                    gout << move_to(epos_x+25,epos_y-10) << color(0,0,0) << box(gout.twidth("Battleship")+10,gout.cascent()+5)
                    << color(150,150,255) << move_to(epos_x+30,epos_y-10) << text("Battleship");
                }
                else if (rr[k].id == "CRU") {
                    gout << move_to(epos_x+25,epos_y-10) << color(0,0,0) << box(gout.twidth("Cruiser")+10,gout.cascent()+5)
                    << color(150,150,255) << move_to(epos_x+30,epos_y-10) << text("Cruiser");
                }
                else if (rr[k].id == "SUB") {
                    gout << move_to(epos_x+25,epos_y-10) << color(0,0,0) << box(gout.twidth("Submarine")+10,gout.cascent()+5)
                    << color(150,150,255) << move_to(epos_x+30,epos_y-10) << text("Submarine");
                }
                else if (rr[k].id == "DES") {
                    gout << move_to(epos_x+25,epos_y-10) << color(0,0,0) << box(gout.twidth("Destroyer")+10,gout.cascent()+5)
                    << color(150,150,255) << move_to(epos_x+30,epos_y-10) << text("Destroyer");
                }
                break;
            }
            else {
                OnShip = false;
            }
        }

        cursor_refresh(OnShip,epos_x,epos_y);
        screen_refresh();
    }
}

void Sea::win_open(const int XX,const int YY) {
    event ev;
    gout.open(XX,YY);
}

void Sea::info_load(vector<string> &b, vector<int> &sz) {
    b.push_back("A");
    b.push_back("B");
    b.push_back("C");
    b.push_back("D");
    b.push_back("E");
    b.push_back("F");
    b.push_back("G");
    b.push_back("H");
    b.push_back("I");
    b.push_back("J");
    for (int i = 1; i < 11; i++) {
        sz.push_back(i);
    }
}

void Ships::generate_ships_left(vector<Reserved> &rl) {

    Reserved res;
    int x = time(0);
    bool left_good = false;

    while (!left_good) {

        srand(x++);

        //Carrier
        Ship s;
        bool horizontal_c = rand()%2-1;
        int randx_c;
        int randy_c;
        if (horizontal_c) {
            randx_c = rand()%5;
            randy_c = rand()%10;
        }
        else {
            randx_c = rand()%10;
            randy_c = rand()%5;
        }
        s.x = randx_c;
        s.y = randy_c;
        s.id = "CAR";
        cv.push_back(s);
        res.x = s.x;
        res.y = s.y;
        res.id = s.id;
        rl.push_back(res);
        for (int i = 1; i < 5; i++) {
            if (horizontal_c) {
                s.x = randx_c + i;
                s.y = randy_c;
                s.id = "CAR";
                cv.push_back(s);
            }
            else {
                s.x = randx_c;
                s.y = randy_c + i;
                s.id = "CAR";
                cv.push_back(s);
            }
            res.x = s.x;
            res.y = s.y;
            res.id = s.id;
            rl.push_back(res);
        }

        //Battleship
        bool horizontal_b = rand()%2-1;
        int randx_b;
        int randy_b;
        if (horizontal_b) {
            randx_b = rand()%6;
            randy_b = rand()%10;
        }
        else {
            randx_b = rand()%10;
            randy_b = rand()%6;
        }
        s.x = randx_b;
        s.y = randy_b;
        s.id = "BAT";
        bv.push_back(s);
        res.x = s.x;
        res.y = s.y;
        res.id = s.id;
        rl.push_back(res);
        for (int i = 1; i < 4; i++) {
            if (horizontal_b) {
                s.x = randx_b + i;
                s.y = randy_b;
                s.id = "BAT";
                bv.push_back(s);
            }
            else {
                s.x = randx_b;
                s.y = randy_b + i;
                s.id = "BAT";
                bv.push_back(s);
            }
            res.x = s.x;
            res.y = s.y;
            res.id = s.id;
            rl.push_back(res);
        }

        //Cruiser
        bool horizontal_cr = rand()%2-1;
        int randx_cr;
        int randy_cr;
        if (horizontal_cr) {
            randx_cr = rand()%7;
            randy_cr = rand()%10;
        }
        else {
            randx_cr = rand()%10;
            randy_cr = rand()%7;
        }
        s.x = randx_cr;
        s.y = randy_cr;
        s.id = "CRU";
        crv.push_back(s);
        res.x = s.x;
        res.y = s.y;
        res.id = s.id;
        rl.push_back(res);
        for (int i = 1; i < 3; i++) {
            if (horizontal_cr) {
                s.x = randx_cr + i;
                s.y = randy_cr;
                s.id = "CRU";
                crv.push_back(s);
            }
            else {
                s.x = randx_cr;
                s.y = randy_cr + i;
                s.id = "CRU";
                crv.push_back(s);
            }
            res.x = s.x;
            res.y = s.y;
            res.id = s.id;
            rl.push_back(res);
        }

        //Submarine
        bool horizontal_s = rand()%2-1;
        int randx_s;
        int randy_s;
        if (horizontal_s) {
            randx_s = rand()%7;
            randy_s = rand()%10;
        }
        else {
            randx_s = rand()%10;
            randy_s = rand()%7;
        }
        s.x = randx_s;
        s.y = randy_s;
        s.id = "SUB";
        sv.push_back(s);
        res.x = s.x;
        res.y = s.y;
        res.id = s.id;
        rl.push_back(res);
        for (int i = 1; i < 3; i++) {
            if (horizontal_s) {
                s.x = randx_s + i;
                s.y = randy_s;
                s.id = "SUB";
                sv.push_back(s);
            }
            else {
                s.x = randx_s;
                s.y = randy_s + i;
                s.id = "SUB";
                sv.push_back(s);
            }
            res.x = s.x;
            res.y = s.y;
            res.id = s.id;
            rl.push_back(res);
        }

        //Destroyer
        bool horizontal_d = rand()%2-1;
        int randx_d;
        int randy_d;
        if (horizontal_d) {
            randx_d = rand()%7;
            randy_d = rand()%10;
        }
        else {
            randx_d = rand()%10;
            randy_d = rand()%7;
        }
        s.x = randx_d;
        s.y = randy_d;
        s.id = "DES";
        dv.push_back(s);
        res.x = s.x;
        res.y = s.y;
        res.id = s.id;
        rl.push_back(res);
        for (int i = 1; i < 2; i++) {
            if (horizontal_d) {
                s.x = randx_d + i;
                s.y = randy_d;
                s.id = "DES";
                dv.push_back(s);
            }
            else {
                s.x = randx_d;
                s.y = randy_d + i;
                s.id = "DES";
                dv.push_back(s);
            }
            res.x = s.x;
            res.y = s.y;
            res.id = s.id;
            rl.push_back(res);
        }

        //ellenorzes
        for (int i = 0; i < rl.size(); i++) {
            for (int j = 0; j < rl.size(); j++)
            if ((i != j) && (rl[i].x == rl[j].x && rl[i].y == rl[j].y)) {
                for (int i = 0; i < rl.size(); i++) {
                    rl.pop_back();
                }
                break;
            }
            else {
                left_good = true;
            }
            if (!left_good) {
                break;
            }
        }
        if (left_good) {
            break;
        }
    }
}

void Ships::generate_ships_right(vector<Reserved> &rr) {

    Reserved res;

    //OnShip = false;

    srand(time(0)+1);

    //Carrier
    Ship s;
    bool horizontal_c = rand()%2-1;
    int randx_c;
    int randy_c;
    if (horizontal_c) {
        randx_c = rand()%5;
        randy_c = rand()%10;
    }
    else {
        randx_c = rand()%10;
        randy_c = rand()%5;
    }
    s.x = randx_c;
    s.y = randy_c;
    s.id = "CAR";
    cv.push_back(s);
    res.x = s.x;
    res.y = s.y;
    res.id = s.id;
    rr.push_back(res);
    for (int i = 1; i < 5; i++) {
        if (horizontal_c) {
            s.x = randx_c + i;
            s.y = randy_c;
            s.id = "CAR";
            cv.push_back(s);
        }
        else {
            s.x = randx_c;
            s.y = randy_c + i;
            s.id = "CAR";
            cv.push_back(s);
        }
        res.x = s.x;
        res.y = s.y;
        res.id = s.id;
        rr.push_back(res);
    }

    //Battleship
    bool horizontal_b = rand()%2-1;
    int randx_b;
    int randy_b;
    if (horizontal_b) {
        randx_b = rand()%6;
        randy_b = rand()%10;
    }
    else {
        randx_b = rand()%10;
        randy_b = rand()%6;
    }
    s.x = randx_b;
    s.y = randy_b;
    s.id = "BAT";
    bv.push_back(s);
    res.x = s.x;
    res.y = s.y;
    res.id = s.id;
    rr.push_back(res);
    for (int i = 1; i < 4; i++) {
        if (horizontal_b) {
            s.x = randx_b + i;
            s.y = randy_b;
            s.id = "BAT";
            bv.push_back(s);
        }
        else {
            s.x = randx_b;
            s.y = randy_b + i;
            s.id = "BAT";
            bv.push_back(s);
        }
        res.x = s.x;
        res.y = s.y;
        res.id = s.id;
        rr.push_back(res);
    }

    //Cruiser
    bool horizontal_cr = rand()%2-1;
    int randx_cr;
    int randy_cr;
    if (horizontal_cr) {
        randx_cr = rand()%7;
        randy_cr = rand()%10;
    }
    else {
        randx_cr = rand()%10;
        randy_cr = rand()%7;
    }
    s.x = randx_cr;
    s.y = randy_cr;
    s.id = "CRU";
    crv.push_back(s);
    res.x = s.x;
    res.y = s.y;
    res.id = s.id;
    rr.push_back(res);
    for (int i = 1; i < 3; i++) {
        if (horizontal_cr) {
            s.x = randx_cr + i;
            s.y = randy_cr;
            s.id = "CRU";
            crv.push_back(s);
        }
        else {
            s.x = randx_cr;
            s.y = randy_cr + i;
            s.id = "CRU";
            crv.push_back(s);
        }
        res.x = s.x;
        res.y = s.y;
        res.id = s.id;
        rr.push_back(res);
    }

    //Submarine
    bool horizontal_s = rand()%2-1;
    int randx_s;
    int randy_s;
    if (horizontal_s) {
        randx_s = rand()%7;
        randy_s = rand()%10;
    }
    else {
        randx_s = rand()%10;
        randy_s = rand()%7;
    }
    s.x = randx_s;
    s.y = randy_s;
    s.id = "SUB";
    sv.push_back(s);
    res.x = s.x;
    res.y = s.y;
    res.id = s.id;
    rr.push_back(res);
    for (int i = 1; i < 3; i++) {
        if (horizontal_s) {
            s.x = randx_s + i;
            s.y = randy_s;
            s.id = "SUB";
            sv.push_back(s);
        }
        else {
            s.x = randx_s;
            s.y = randy_s + i;
            s.id = "SUB";
            sv.push_back(s);
        }
        res.x = s.x;
        res.y = s.y;
        res.id = s.id;
        rr.push_back(res);
    }

    //Destroyer
    bool horizontal_d = rand()%2-1;
    int randx_d;
    int randy_d;
    if (horizontal_d) {
        randx_d = rand()%7;
        randy_d = rand()%10;
    }
    else {
        randx_d = rand()%10;
        randy_d = rand()%7;
    }
    s.x = randx_d;
    s.y = randy_d;
    s.id = "DES";
    dv.push_back(s);
    res.x = s.x;
    res.y = s.y;
    res.id = s.id;
    rr.push_back(res);
    for (int i = 1; i < 2; i++) {
        if (horizontal_d) {
            s.x = randx_d + i;
            s.y = randy_d;
            s.id = "DES";
            dv.push_back(s);
        }
        else {
            s.x = randx_d;
            s.y = randy_d + i;
            s.id = "DES";
            dv.push_back(s);
        }
        res.x = s.x;
        res.y = s.y;
        res.id = s.id;
        rr.push_back(res);
    }
}

int main() {

    vector<Reserved>rl;
    vector<Reserved>rr;

    vector<Ship>cv;
    vector<Ship>bv;
    vector<Ship>crv;
    vector<Ship>sv;
    vector<Ship>dv;

    vector<Reserved>sol; //shot on left
    vector<Reserved>sor; //shot on right

    vector<string> b;
    vector<int> sz;

    Gamemaster gm = Gamemaster(false,false,true,false);
    Sea s = Sea(false,false,true,false,0,0,false);
    Ships sh = Ships(false,false,true,false,0,0,false,cv,bv,crv,sv,dv,true,true);
    sh.generate_ships_left(rl);
    sh.generate_ships_right(rr);
    s.win_open(XX,YY);
    s.info_load(b,sz);
    s.event_loop(b,sz,rl,rr,sol,sor,sh.Getleft_ok());

    return 0;
}