//
#include "graphics.hpp"
//
#include <vector>
#include <string>
#include <ctime>

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

//hajok
struct Carrier {
    int x, y;
    string id;
};

struct Battleship {
    int x, y;
    string id;
};

struct Cruiser {
    int x, y;
    string id;
};

struct Submarine {
    int x, y;
    string id;
};

struct Destroyer {
    int x, y;
    string id;
};

class Gamemaster {
    bool IsMenu;
    bool IsGame;
    bool Player_1_Turn;
    bool Player_2_Turn;
};

class Sea {
    protected:

    int field_x;
    int field_y;
    bool OnShip;

    public:

    Sea(int fx, int fy, bool os) : field_x(fx), field_y(fy), OnShip(os) {};

    void event_loop(vector<string> b, vector<int> sz, vector<Reserved> r);
    void win_open(const int XX,const int YY);
    void info_load(vector<string> &b, vector<int> &sz);
};

//tobbi hajo struct-ja

class Ships : public Sea {
    protected:

    vector<Carrier>cv;
    vector<Battleship>bv;
    vector<Cruiser>crv;
    vector<Submarine>sv;
    vector<Destroyer>dv;
    //tobbi hajo vektora

    public:

    Ships(int field_x, int field_y, bool os, vector<Carrier>cv, vector<Battleship>bv, vector<Cruiser>crv, vector<Submarine>sv, vector<Destroyer>dv) :
        Sea(field_x, field_y, os), cv(cv), bv(bv), crv(crv), sv(sv), dv(dv) {}

    //fuggvenybe fuggvenyt hogy?
    void f_in_f();

    void generate_ships(vector<Reserved> &r);
};

void Sea::event_loop(vector<string> b, vector<int> sz, vector<Reserved> r) {
    event ev;
    gout.showmouse(false);
    int epos_x;
    int epos_y;
    while (gin >> ev && ev.keycode != key_escape) {
        if (ev.type == ev_mouse) {
            epos_x = ev.pos_x;
            epos_y = ev.pos_y;
        }
        gout << color(0,0,0) << move_to(0,0) << box(XX,YY) << color(255,255,255);
        gout << font("LiberationSans-Regular.ttf",20);
        gout << color(255,255,255) << move_to(100,100) << box(YY-199,YY-199);
        gout << color(255,255,255) << move_to(XX/2+100,100) << box(YY-199,YY-199);
        //jobb oldal
        for (int i = 0; i < 10; i++) {
            if (epos_x >= ((YY-200)/10)*i+101 && epos_x <= ((YY-200)/10)*i+101+((YY-200)/10)) {
                gout <<color(255,0,0) << move_to(100+i*(XX/2-200)/10+15,YY-100+15) << text(b[i]);
            }
            else {
                gout <<color(150,150,150) << move_to(100+i*(XX/2-200)/10+15,YY-100+15) << text(b[i]);
            }
            for (int j = 0; j < 10; j++) {
                if (epos_y >= ((YY-200)/10)*j+101 && epos_y <= ((YY-200)/10)*j+101+((YY-200)/10) && epos_x <= XX/2) {
                    gout <<color(255,0,0) << move_to(XX/2-100+15,100+j*(YY-200)/10+15) << text(to_string(sz[j]));
                }
                else {
                    gout <<color(150,150,150) << move_to(XX/2-100+15,100+j*(YY-200)/10+15) << text(to_string(sz[j]));
                }
                if (epos_x >= ((YY-200)/10)*j+101 && epos_x <= ((YY-200)/10)*j+101+((YY-200)/10) &&
                    epos_y >= ((YY-200)/10)*i+101 && epos_y <= ((YY-200)/10)*i+101+((YY-200)/10)) {
                    gout << color(150,0,0) << move_to(((YY-200)/10)*j+101,((YY-200)/10)*i+101) <<
                    box((YY-200)/10 - 2,(YY-200)/10 - 2);
                }
                else {
                    gout << color(0,0,0) << move_to(((YY-200)/10)*j+101,((YY-200)/10)*i+101) <<
                    box((YY-200)/10 - 2,(YY-200)/10 - 2);
                }
            }
        }
        //bal oldal
        for (int i = 0; i < 10; i++) {
            if (epos_x >= ((YY-200)/10)*i+101+XX/2 && epos_x <= ((YY-200)/10)*i+XX/2+101+((YY-200)/10)) {
                gout <<color(255,255,255) << move_to(100+XX/2+i*(XX/2-200)/10+15,YY-100+15) << text(b[i]);
            }
            else {
                gout <<color(100,100,100) << move_to(100+XX/2+i*(XX/2-200)/10+15,YY-100+15) << text(b[i]);
            }
            for (int j = 0; j < 10; j++) {
                if (epos_y >= ((YY-200)/10)*j+101 && epos_y <= ((YY-200)/10)*j+101+((YY-200)/10) && epos_x >= XX/2) {
                    gout <<color(255,255,255) << move_to(XX/2+100-25,100+j*(YY-200)/10+15) << text(to_string(sz[j]));
                }
                else {
                    gout <<color(100,100,100) << move_to(XX/2+100-25,100+j*(YY-200)/10+15) << text(to_string(sz[j]));
                }
                if (epos_x >= ((YY-200)/10)*j+101+XX/2 && epos_x <= ((YY-200)/10)*j+XX/2+101+((YY-200)/10) &&
                    epos_y >= ((YY-200)/10)*i+101 && epos_y <= ((YY-200)/10)*i+101+((YY-200)/10)) {
                    gout << color(150,150,150) << move_to(((YY-200)/10)*j+XX/2+101,((YY-200)/10)*i+101) <<
                    box((YY-200)/10 - 2,(YY-200)/10 - 2);
                }
                else {
                    gout << color(0,0,0) << move_to(((YY-200)/10)*j+XX/2+101,((YY-200)/10)*i+101) <<
                    box((YY-200)/10 - 2,(YY-200)/10 - 2);
                }
            }
        }
        string p1 = "PLAYER 1";
        string p2 = "PLAYER 2";
        gout << font("LiberationSans-Regular.ttf",30);
        gout << color(255,255,255) << move_to(100,100-gout.cascent()-5) << text(p1);
        gout << color(255,255,255) << move_to(XX-100-gout.twidth(p2),100-gout.cascent()-5) << text(p2);

        //reserved check
        gout << move_to(20,20) << text(to_string(r.size()));

        for (int k = 0; k < r.size(); k++) {
            if (r[k].id == "CAR") {
                gout << color(100,100,100) << move_to(((YY-200)/10)*r[k].x+101,((YY-200)/10)*r[k].y+101) << box((YY-200)/10-2,(YY-200)/10-2);
            }
            else if (r[k].id == "BAT") {
                gout << color(130,130,130) << move_to(((YY-200)/10)*r[k].x+101,((YY-200)/10)*r[k].y+101) << box((YY-200)/10-2,(YY-200)/10-2);
            }
            else if (r[k].id == "CRU") {
                gout << color(160,160,160) << move_to(((YY-200)/10)*r[k].x+101,((YY-200)/10)*r[k].y+101) << box((YY-200)/10-2,(YY-200)/10-2);
            }
            else if (r[k].id == "SUB") {
                gout << color(190,190,190) << move_to(((YY-200)/10)*r[k].x+101,((YY-200)/10)*r[k].y+101) << box((YY-200)/10-2,(YY-200)/10-2);
            }
            else if (r[k].id == "DES") {
                gout << color(220,220,220) << move_to(((YY-200)/10)*r[k].x+101,((YY-200)/10)*r[k].y+101) << box((YY-200)/10-2,(YY-200)/10-2);
            }
        }

        gout << font("LiberationSans-Regular.ttf",20);

        //hatulrol indexeles, hogy a lagutoljara rajzoltat csekkolja
        for (int k = r.size(); k >= 0; k--) {
            if (epos_x >= ((YY-200)/10)*r[k].x+101 && epos_x <= ((YY-200)/10)*r[k].x+101+((YY-200)/10) &&
                epos_y >= ((YY-200)/10)*r[k].y+101 && epos_y <= ((YY-200)/10)*r[k].y+101+((YY-200)/10)) {
                OnShip = true;
                if (r[k].id == "CAR") {
                    gout << move_to(epos_x+25,epos_y-10) << color(0,0,0) << box(gout.twidth("Carrier")+10,gout.cascent()+5)
                    << color(255,255,255) << move_to(epos_x+30,epos_y-10) << text("Carrier");
                    break;
                }
                else if (r[k].id == "BAT") {
                    gout << move_to(epos_x+25,epos_y-10) << color(0,0,0) << box(gout.twidth("Battleship")+10,gout.cascent()+5)
                    << color(255,255,255) << move_to(epos_x+30,epos_y-10) << text("Battleship");
                    break;
                }
                else if (r[k].id == "CRU") {
                    gout << move_to(epos_x+25,epos_y-10) << color(0,0,0) << box(gout.twidth("Cruiser")+10,gout.cascent()+5)
                    << color(255,255,255) << move_to(epos_x+30,epos_y-10) << text("Cruiser");
                    break;
                }
                else if (r[k].id == "SUB") {
                    gout << move_to(epos_x+25,epos_y-10) << color(0,0,0) << box(gout.twidth("Submarine")+10,gout.cascent()+5)
                    << color(255,255,255) << move_to(epos_x+30,epos_y-10) << text("Submarine");
                    break;
                }
                else if (r[k].id == "DES") {
                    gout << move_to(epos_x+25,epos_y-10) << color(0,0,0) << box(gout.twidth("Destroyer")+10,gout.cascent()+5)
                    << color(255,255,255) << move_to(epos_x+30,epos_y-10) << text("Destroyer");
                    break;
                }
                break;
            }
            else {
                OnShip = false;
            }
        }
        if (OnShip) {
            gout << color(255,255,255) << move_to(epos_x-10,epos_y-10) << box(4,10);
            gout << move_to(epos_x-10,epos_y-10) << box(10,4);

            gout << move_to(epos_x+10,epos_y-10) << box(-10,4);
            gout<< move_to(epos_x+10,epos_y-10) << box(-4,10);

            gout << move_to(epos_x+10,epos_y+10) << box(-4,-10);
            gout << move_to(epos_x+10,epos_y+10) << box(-10,-4);

            gout << move_to(epos_x-10,epos_y+10) << box(10,-4);
            gout << move_to(epos_x-10,epos_y+10) << box(4,-10);
        }
        else {
            gout << color(255,255,255) << move_to(epos_x-20,epos_y-2) << box(40,4);
            gout << move_to(epos_x-2,epos_y-20) << box(4,40);
        }

        gout << refresh;
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

void Ships::generate_ships(vector<Reserved> &r) {
    Reserved res;

    //OnShip = false;

    int x = time(0);
    srand(x);

    //Carrier
    Carrier c;
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
    c.x = randx_c;
    c.y = randy_c;
    c.id = "CAR";
    cv.push_back(c);
    res.x = c.x;
    res.y = c.y;
    res.id = c.id;
    r.push_back(res);
    for (int i = 1; i < 5; i++) {
        if (horizontal_c) {
            c.x = randx_c + i;
            c.y = randy_c;
            c.id = "CAR";
            cv.push_back(c);
        }
        else {
            c.x = randx_c;
            c.y = randy_c + i;
            c.id = "CAR";
            cv.push_back(c);
        }
        res.x = c.x;
        res.y = c.y;
        res.id = c.id;
        r.push_back(res);
    }

    //Battleship
    Battleship b;
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
    b.x = randx_b;
    b.y = randy_b;
    b.id = "BAT";
    bv.push_back(b);
    res.x = b.x;
    res.y = b.y;
    res.id = b.id;
    r.push_back(res);
    for (int i = 1; i < 4; i++) {
        if (horizontal_b) {
            b.x = randx_b + i;
            b.y = randy_b;
            b.id = "BAT";
            bv.push_back(b);
        }
        else {
            b.x = randx_b;
            b.y = randy_b + i;
            b.id = "BAT";
            bv.push_back(b);
        }
        res.x = b.x;
        res.y = b.y;
        res.id = b.id;
        r.push_back(res);
    }

    //Cruiser
    Cruiser cr;
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
    cr.x = randx_cr;
    cr.y = randy_cr;
    cr.id = "CRU";
    crv.push_back(cr);
    res.x = cr.x;
    res.y = cr.y;
    res.id = cr.id;
    r.push_back(res);
    for (int i = 1; i < 3; i++) {
        if (horizontal_cr) {
            cr.x = randx_cr + i;
            cr.y = randy_cr;
            cr.id = "CRU";
            crv.push_back(cr);
        }
        else {
            cr.x = randx_cr;
            cr.y = randy_cr + i;
            cr.id = "CRU";
            crv.push_back(cr);
        }
        res.x = cr.x;
        res.y = cr.y;
        res.id = cr.id;
        r.push_back(res);
    }

    //Submarine
    Submarine s;
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
    r.push_back(res);
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
        r.push_back(res);
    }

    //Destroyer
    Destroyer d;
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
    d.x = randx_d;
    d.y = randy_d;
    d.id = "DES";
    dv.push_back(d);
    res.x = d.x;
    res.y = d.y;
    res.id = d.id;
    r.push_back(res);
    for (int i = 1; i < 2; i++) {
        if (horizontal_d) {
            d.x = randx_d + i;
            d.y = randy_d;
            d.id = "DES";
            dv.push_back(d);
        }
        else {
            d.x = randx_d;
            d.y = randy_d + i;
            d.id = "DES";
            dv.push_back(d);
        }
        res.x = d.x;
        res.y = d.y;
        res.id = d.id;
        r.push_back(res);
    }
    //tobbi hajo generalasa
}

int main() {

    vector<Reserved>r;
    vector<Carrier>cv;
    vector<Battleship>bv;
    vector<Cruiser>crv;
    vector<Submarine>sv;
    vector<Destroyer>dv;

    vector<string> b;
    vector<int> sz;

    Ships sh = Ships(0,0,false,cv,bv,crv,sv,dv);
    sh.generate_ships(r);
    Sea s = Sea(0,0,false);
    s.win_open(XX,YY);
    s.info_load(b,sz);
    s.event_loop(b,sz,r);

    return 0;
}