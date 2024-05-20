#include "Ships.hpp"

#include <ctime>

//foglalt mezok tipusa
struct Reserved {
    int x, y;
    std::string id;
};

void Ships::generate_ships_left(std::vector<Reserved> &rl) {

    Reserved res;
    srand(time(0));

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
}

void Ships::generate_ships_right(std::vector<Reserved> &rr) {

    Reserved res;

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
