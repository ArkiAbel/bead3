#include "Gamemaster.hpp"
#include "graphics.hpp"

#include <vector>
#include <string>
#include <ctime>
#include <functional>

using namespace genv;

const int XX = 1400;
const int YY = XX/2;

void Gamemaster::win_open(const int XX,const int YY) {
    event ev;
    gout.open(XX,YY);
}

void Gamemaster::info_load(std::vector<std::string> &b, std::vector<int> &sz) {
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

void Gamemaster::event_loop(std::vector<std::string> b,std::vector<int>sz,std::vector<Reserved>&rl,std::vector<Reserved>&rr,
                       std::vector<Reserved>&sol,std::vector<Reserved>&sor,bool left_ok) {
    event ev;
    Reserved res;
    gout.showmouse(false);
    gin.timer(40);

    int epos_x;
    int epos_y;
    double timecount = 0;
    bool click;
    bool space;
    bool hit;

    std::function<void(bool,bool &,bool &,int,int)> menu_screen;
        menu_screen = [](bool click,bool &IsMenu,bool &IsGame,int epos_x,int epos_y){gout << color(255,255,200) << move_to(0,0) << box(XX,YY) << color(0,0,0);
        std::string title = "BATTLESHIPS";
        std::string play = "PLAY";
        std::string bottom = "CREATED BY ABEL ARKI - SUPPORTED BY FLUGIGRAPHICS - VERSION ALPHA: 0.8.1.";
        gout << color(200,200,150) << move_to(0,YY/2-gout.cascent()/2-218) << box(XX,60);
        gout << font("LiberationSans-Regular.ttf",50);
        gout << color(255,255,200) << move_to(XX/2-gout.twidth(title)/2,YY/2-gout.cascent()/2-200) << text(title);
        gout << color(200,200,150) << move_to(XX/2-120,YY/2-60) << box(240,120);
        if (epos_x >= XX/2-115 && epos_x <= XX/2+115 && epos_y >= YY/2-55 && epos_y <= YY/2+55) {
            gout << color(255,255,255) << move_to(XX/2-120,YY/2-60) << box(240,120) << color(180,0,0)
            << move_to(XX/2-115,YY/2-55) << box(115,110) << move_to(XX/2,YY/2-55) << color(0,0,180) << box(115,110)
            << color(255,255,255) << move_to(XX/2-gout.twidth(play)/2,YY/2-gout.cascent()/2-8) << text(play);
            if (click) {
                IsMenu = false;
                IsGame = true;
            }
        }
        else {
            gout << color(255,255,200) << move_to(XX/2-115,YY/2-55) << box(230,110)
            << color(200,200,150) << move_to(XX/2-gout.twidth(play)/2,YY/2-gout.cascent()/2-8) << text(play);
        }
        gout << font("LiberationSans-Regular.ttf",15);
        gout << color(200,200,150) << move_to(XX/2-gout.twidth(bottom)/2,YY-50) << text(bottom);};

    std::function<void()> game_screen_reset;
        game_screen_reset = [](){gout << color(255,255,200) << move_to(0,0) << box(XX,YY) << color(0,0,0);
        gout << font("LiberationSans-Regular.ttf",20);
        gout << color(255,0,0) << move_to(100,100) << box(YY-199,YY-199);
        gout << color(0,0,255) << move_to(XX/2+100,100) << box(YY-199,YY-199);};

    std::function<void(bool,bool &,bool&,std::string &,int,int,std::vector<std::string>,std::vector<int>,std::vector<Reserved>&)> leftgrid_hover_getshot;
        leftgrid_hover_getshot = [](bool click,bool &IsGame,bool &IsTurn,std::string &Player,int epos_x,int epos_y,std::vector<std::string>b,std::vector<int>sz,std::vector<Reserved>&sol){Reserved res; for (int i = 0; i < 10; i++) {
            //nagy negyzet
            if (epos_x > ((YY-200)/10)*i+101 && epos_x < ((YY-200)/10)*i+101+((YY-200)/10)) {
                gout << color(255,0,0) << move_to(100+i*(XX/2-200)/10+15,YY-100+15) << text(b[i]);
            }
            else {
                gout << color(255,200,200) << move_to(100+i*(XX/2-200)/10+15,YY-100+15) << text(b[i]);
            }
            for (int j = 0; j < 10; j++) {
                if (epos_y > ((YY-200)/10)*j+101 && epos_y < ((YY-200)/10)*j+101+((YY-200)/10) && epos_x < XX/2) {
                    gout << color(255,0,0) << move_to(XX/2-100+15,100+j*(YY-200)/10+15) << text(std::to_string(sz[j]));
                }
                else {
                    gout << color(255,200,200) << move_to(XX/2-100+15,100+j*(YY-200)/10+15) << text(std::to_string(sz[j]));
                }
                if (epos_x > ((YY-200)/10)*j+101 && epos_x < ((YY-200)/10)*j+101+((YY-200)/10) &&
                    epos_y > ((YY-200)/10)*i+101 && epos_y < ((YY-200)/10)*i+101+((YY-200)/10)) {
                    if (click && Player == "masodik") {
                        res.x = j;
                        res.y = i;
                        //res.id = "-";
                        sol.push_back(res);
                        Player = "elso";
                        IsGame = false;
                        IsTurn = true;
                    }
                    gout << color(150,150,150) << move_to(((YY-200)/10)*j+101,((YY-200)/10)*i+101) <<
                    box((YY-200)/10 - 2,(YY-200)/10 - 2);
                }
                else {
                    gout << color(0,0,0) << move_to(((YY-200)/10)*j+101,((YY-200)/10)*i+101) <<
                    box((YY-200)/10 - 2,(YY-200)/10 - 2);
                }
            }
        }};

    std::function<void(bool,bool,bool &,bool &,std::string &,int,int,std::vector<std::string>,std::vector<int>,std::vector<Reserved>&)> rightgrid_hover_getshot;
        rightgrid_hover_getshot = [](bool active_2,bool click,bool &IsGame, bool &IsTurn,std::string &Player,int epos_x,int epos_y,std::vector<std::string>b,std::vector<int>sz,std::vector<Reserved>&sor){Reserved res; for (int i = 0; i < 10; i++) {
            if (epos_x > ((YY-200)/10)*i+101+XX/2 && epos_x < ((YY-200)/10)*i+XX/2+101+((YY-200)/10)) {
                gout << color(0,0,255) << move_to(100+XX/2+i*(XX/2-200)/10+15,YY-100+15) << text(b[i]);
            }
            else {
                gout << color(200,200,255) << move_to(100+XX/2+i*(XX/2-200)/10+15,YY-100+15) << text(b[i]);
            }
            for (int j = 0; j < 10; j++) {
                if (epos_y > ((YY-200)/10)*j+101 && epos_y < ((YY-200)/10)*j+101+((YY-200)/10) && epos_x > XX/2) {
                    gout << color(0,0,255) << move_to(XX/2+100-25,100+j*(YY-200)/10+15) << text(std::to_string(sz[j]));
                }
                else {
                    gout <<color(200,200,255) << move_to(XX/2+100-25,100+j*(YY-200)/10+15) << text(std::to_string(sz[j]));
                }
                if (epos_x > ((YY-200)/10)*j+101+XX/2 && epos_x < ((YY-200)/10)*j+XX/2+101+((YY-200)/10) &&
                    epos_y > ((YY-200)/10)*i+101 && epos_y < ((YY-200)/10)*i+101+((YY-200)/10)) {
                    if (click && Player == "elso") {
                        res.x = j;
                        res.y = i;
                        //res.id = "-";
                        sor.push_back(res);
                        Player = "masodik";
                        IsGame = false;
                        IsTurn = true;
                    }
                    gout << color(150,150,150) << move_to(((YY-200)/10)*j+XX/2+101,((YY-200)/10)*i+101) <<
                    box((YY-200)/10 - 2,(YY-200)/10 - 2);
                }
                else {
                    gout << color(0,0,0) << move_to(((YY-200)/10)*j+XX/2+101,((YY-200)/10)*i+101) <<
                    box((YY-200)/10 - 2,(YY-200)/10 - 2);
                }
            }
        }};

     std::function<void(bool,std::string &,int,int)> player1_attack;
        player1_attack = [](bool active_2,std::string &Player,int epos_x,int epos_y){Reserved res; for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (epos_x > ((YY-200)/10)*j+101+XX/2 && epos_x < ((YY-200)/10)*j+XX/2+101+((YY-200)/10) &&
                    epos_y > ((YY-200)/10)*i+101 && epos_y < ((YY-200)/10)*i+101+((YY-200)/10)) {
                    if (active_2 && Player == "elso") {
                        gout << color(150,150,150) << move_to(((YY-200)/10)*j+XX/2+101,((YY-200)/10)*i+101) <<
                        box((YY-200)/10 - 2,(YY-200)/10 - 2);
                        gout << move_to(((YY-200)/10)*(j-1)+XX/2+101,((YY-200)/10)*(i-1)+101) <<
                        box((YY-200)/10 - 2,(YY-200)/10 - 2);
                        gout << move_to(((YY-200)/10)*(j+1)+XX/2+101,((YY-200)/10)*(i+1)+101) <<
                        box((YY-200)/10 - 2,(YY-200)/10 - 2);
                        gout << move_to(((YY-200)/10)*(j+1)+XX/2+101,((YY-200)/10)*(i-1)+101) <<
                        box((YY-200)/10 - 2,(YY-200)/10 - 2);
                        gout << move_to(((YY-200)/10)*(j-1)+XX/2+101,((YY-200)/10)*(i+1)+101) <<
                        box((YY-200)/10 - 2,(YY-200)/10 - 2);
                    }
                    else {
                        gout << color(150,150,150) << move_to(((YY-200)/10)*j+XX/2+101,((YY-200)/10)*i+101) <<
                        box((YY-200)/10 - 2,(YY-200)/10 - 2);
                    }
                }
            }
        }};

    std::function<void(std::string)> playerturn_text;
        playerturn_text = [](std::string Player){if (Player == "elso") {
            gout << color(255,0,0) << move_to(XX/2-gout.twidth("PLAYER 1 TURN")/2,20) << text("PLAYER 1 TURN");
        }
        if (Player == "masodik") {
            gout << color(0,0,255) << move_to(XX/2-gout.twidth("PLAYER 2 TURN")/2,20) << text("PLAYER 2 TURN");
        }};

    std::function<void()> player_tags;
        player_tags = [](){std::string p1 = "PLAYER 1"; std::string p2 = "PLAYER 2";
        gout << font("LiberationSans-Regular.ttf",30);
        gout << color(255,0,0) << move_to(100,100-gout.cascent()-5) << text(p1);
        gout << color(0,0,255) << move_to(XX-100-gout.twidth(p2),100-gout.cascent()-5) << text(p2);};

    std::function<void(std::string,std::vector<Reserved>&,int,int)> player1_ships;
        player1_ships = [](std::string Player,std::vector<Reserved>&rl,int XX,int YY){if(Player == "elso") {
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

    std::function<void(std::string,std::vector<Reserved> &,int,int)> player2_ships;
        player2_ships = [](std::string Player,std::vector<Reserved>&rr,int XX,int YY){if (Player == "masodik") {
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

    std::function<void(bool &,std::string &,std::vector<Reserved>&,std::vector<Reserved>&)> player1_shot;
        player1_shot = [=](bool &hit,std::string &Player,std::vector<Reserved>&sor,std::vector<Reserved>&rr){for (int k = 0; k < sor.size(); k++) {
            for (int l = 0; l < rr.size(); l++) {
                if (rr[l].x == sor[k].x && rr[l].y == sor[k].y) {
                    gout << color(255,0,0) << move_to(((YY-200)/10)*sor[k].x+101+XX/2+13,((YY-200)/10)*sor[k].y+101+13) << box(20,20);
                    hit = true;
                    break;
                }
                else {
                    gout << color(255,255,255) << move_to(((YY-200)/10)*sor[k].x+101+XX/2+13,((YY-200)/10)*sor[k].y+101+13) << box(20,20);
                }
            }
        }};

    std::function<void(std::string &,std::vector<Reserved>&,std::vector<Reserved>&)> player2_shot;
        player2_shot = [=](std::string &Player,std::vector<Reserved>&sol,std::vector<Reserved>&rl){for (int k = 0; k < sol.size(); k++) {
            for (int l = 0; l < rl.size(); l++) {
                if (rl[l].x == sol[k].x && rl[l].y == sol[k].y) {
                    gout << color(255,0,0) << move_to(((YY-200)/10)*sol[k].x+101+13,((YY-200)/10)*sol[k].y+101+13) << box(20,20);
                    break;
                    }
                else {
                    gout << color(255,255,255) << move_to(((YY-200)/10)*sol[k].x+101+13,((YY-200)/10)*sol[k].y+101+13) << box(20,20);
                }
            }
        }};

    std::function<void()> set_textsize;
        set_textsize = [](){gout << font("LiberationSans-Regular.ttf",20);};

    std::function<void(std::string &,bool &,int,int,int,std::vector<Reserved>&)> player1_shiptitles;
        player1_shiptitles = [](std::string &Player,bool &OnShip,int epos_x,int epos_y,int YY,std::vector<Reserved>&rl){for (int k = rl.size(); k >= 0; k--) {
            if (Player == "elso" && epos_x >= ((YY-200)/10)*rl[k].x+101 && epos_x <= ((YY-200)/10)*rl[k].x+101+((YY-200)/10) &&
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
            else {
                OnShip = false;
            }
        }};

    std::function<void(std::string &,bool &,int,int,int,int,std::vector<Reserved>&)> player2_shiptitles;
        player2_shiptitles = [](std::string &Player,bool &OnShip,int epos_x,int epos_y,int YY,int XX,std::vector<Reserved>&rr){for (int k = rr.size(); k >= 0; k--) {
            if (Player == "masodik" && epos_x >= ((YY-200)/10)*rr[k].x+101+XX/2 && epos_x <= ((YY-200)/10)*rr[k].x+101+XX/2+((YY-200)/10) &&
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
        }};

    std::function<void(int,int,bool,bool &,bool &,bool &)> widgets;
        widgets = [](int epos_x,int epos_y,bool click,bool &active_1,bool &active_2,bool &active_3){
        if (epos_x >= 300 && epos_x <= 350 && epos_y >= 50 && epos_y <= 100) {
            //elso
            gout << color(255,0,0) << move_to(300,50) << box(50,40) << color(255,155,200) << move_to(301,51) << box(48,38);
            if (click) {
                active_1 = true;
                active_2 = false;
                active_3 = false;
            }
        }
        else {
            gout << color(255,0,0) << move_to(300,50) << box(50,40) << color(255,255,200) << move_to(301,51) << box(48,38);
        }
        if (active_1) {
            gout << color(255,0,0) << move_to(295,45) << box(60,50) << color(255,155,200) << move_to(301,51) << box(48,38);
        }
        //kozepso
        if (epos_x >= 360 && epos_x <= 410 && epos_y >= 50 && epos_y <= 100) {
            gout << color(255,0,0) << move_to(360,50) << box(50,40) << color(255,155,200) << move_to(361,51) << box(48,38);
            if (click) {
                active_1 = false;
                active_2 = true;
                active_3 = false;
            }
        }
        else {
            gout << color(255,0,0) << move_to(360,50) << box(50,40) << color(255,255,200) << move_to(361,51) << box(48,38);
        }
        if (active_2) {
            gout << color(255,0,0) << move_to(355,45) << box(60,50) << color(255,155,200) << move_to(361,51) << box(48,38);
        }
        //utolso
        if (epos_x >= 420 && epos_x <= 460 && epos_y >= 50 && epos_y <= 100) {
            gout << color(255,0,0) << move_to(420,50) << box(50,40) << color(255,155,200) << move_to(421,51) << box(48,38);
            if (click) {
                active_1 = false;
                active_2 = false;
                active_3 = true;
            }
        }
        else {
            gout << color(255,0,0) << move_to(420,50) << box(50,40) << color(255,255,200) << move_to(421,51) << box(48,38);
        }
        if (active_3) {
            gout << color(255,0,0) << move_to(415,45) << box(60,50) << color(255,155,200) << move_to(421,51) << box(48,38);
        }};

    std::function<void(bool,int,int)> cursor_refresh;
        cursor_refresh = [](bool OnShip,int epos_x,int epos_y){if (OnShip) {
                gout << color(0,0,0) << move_to(epos_x-10,epos_y-10) << box(4,10);
                gout << move_to(epos_x-10,epos_y-10) << box(10,4);

                gout << move_to(epos_x+10,epos_y-10) << box(-10,4);
                gout << move_to(epos_x+10,epos_y-10) << box(-4,10);

                gout << move_to(epos_x+10,epos_y+10) << box(-4,-10);
                gout << move_to(epos_x+10,epos_y+10) << box(-10,-4);

                gout << move_to(epos_x-10,epos_y+10) << box(10,-4);
                gout << move_to(epos_x-10,epos_y+10) << box(4,-10);
            }
            else {
                gout << color(0,0,0) << move_to(epos_x-15,epos_y-1) << box(30,2);
                gout << move_to(epos_x-1,epos_y-15) << box(2,30);
            }
        };

    std::function<void(bool &,bool &,bool,bool &,double &,std::string)> turnscreen;
        turnscreen = [](bool &IsGame,bool &IsTurn,bool space,bool &hit,double &timecount,std::string Player){event ev;
        if (timecount <= 120) {
            gin.timer(40);
            timecount++;
            std::string turn;
            std::string hit_ = "HIT!";
            gout << color(255,255,200) << move_to(0,0) << box(XX,YY) << color(0,0,0);
            gout << font("LiberationSans-Regular.ttf",30);
            if (hit) {
                gout << color(200,200,150) << move_to(XX/2-gout.twidth(hit_)/2,YY/2-180-gout.cascent()) << text(hit_);
            }
            else {
                gout << color(200,200,150) << move_to(XX/2-gout.twidth("DIDNT HIT...")/2,YY/2-180-gout.cascent()) << text("DIDNT HIT...");
            }
            gout << font("LiberationSans-Regular.ttf",50);
            if (Player == "elso") {
                turn = "PLAYER 1'S TURN IN";
                gout << color(200,200,150) << move_to(XX/2-gout.twidth(turn)/2,YY/2-100-gout.cascent()) << text(turn);
                gout << color(200,200,150) << move_to(XX/2-gout.twidth(turn)/2,YY/2-20) << box(gout.twidth(turn)-(gout.twidth(turn)/100)*timecount,50);
            }
            else if (Player == "masodik") {
                turn = "PLAYER 2'S TURN IN";
                gout << color(200,200,150) << move_to(XX/2-gout.twidth(turn)/2,YY/2-100-gout.cascent()) << text(turn);
                gout << color(200,200,150) << move_to(XX/2-gout.twidth(turn)/2,YY/2-20) << box(gout.twidth(turn)-(gout.twidth(turn)/100)*timecount,50);
            }
            if (space) {
                timecount = 120;
            }
            //hit = false;
        }
        else {
            timecount = 0;
            IsTurn = false;
            IsGame = true;
        }};

    std::function<void()> screen_refresh;
        screen_refresh = [](){gout << refresh;};

    while (gin >> ev && ev.keycode != key_escape) {

        if (ev.type == ev_mouse) {epos_x = ev.pos_x; epos_y = ev.pos_y;}
        if (ev.button == btn_left) {click = true;} else {click = false;}
        if (ev.keycode == key_space) {space = true;} else {space = false;}

        if (IsMenu) {
            menu_screen(click,IsMenu,IsGame,epos_x,epos_y);
            cursor_refresh(OnShip,epos_x,epos_y);
            screen_refresh();
        }
        else if (IsGame) {
            game_screen_reset();
            leftgrid_hover_getshot(click,IsGame,IsTurn,Player,epos_x,epos_y,b,sz,sol);
            rightgrid_hover_getshot(active_2,click,IsGame,IsTurn,Player,epos_x,epos_y,b,sz,sor);
            player1_attack(active_2,Player,epos_x,epos_y);
            player_tags();
            player1_ships(Player,rl,XX,YY);
            player2_ships(Player,rr,XX,YY);
            player1_shot(hit,Player,sor,rr);
            player2_shot(Player,sol,rl);
            playerturn_text(Player);
            set_textsize();
            player1_shiptitles(Player,OnShip,epos_x,epos_y,YY,rl);
            player2_shiptitles(Player,OnShip,epos_x,epos_y,YY,XX,rr);
            widgets(epos_x,epos_y,click,active_1,active_2,active_3);
            cursor_refresh(OnShip,epos_x,epos_y);
            screen_refresh();
        }
        else if (ev.type == ev_timer && IsTurn) {
            turnscreen(IsGame,IsTurn,space,hit,timecount,Player);
            screen_refresh();
        }
    }
}
