#include "graphics.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
//
using namespace genv;
//

const int XX = 1200;
const int YY = 600;

class Sea {
    protected:

    int field_x;
    int field_y;

    public:

    Sea(int fx, int fy) : field_x(fx), field_y(fy) {};

    void event_loop();
    void win_open(const int XX,const int YY);
};

void Sea::event_loop() {
    event ev;
    while (gin >> ev && ev.keycode != key_escape) {
        gout << color(0,0,0) << move_to(0,0) << box(XX,YY) << color(255,255,255);
        //
        gout << color(255,255,255) << move_to(100,100) << box(YY-199,YY-199);
        gout << color(255,255,255) << move_to(XX/2+100,100) << box(YY-199,YY-199);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                gout << color(0,0,0) << move_to(((YY-200)/10)*j+101,((YY-200)/10)*i+101) <<
                box((YY-200)/10 - 2,(YY-200)/10 - 2);
            }
        }
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                gout << color(0,0,0) << move_to(((YY-200)/10)*j+XX/2+101,((YY-200)/10)*i+101) <<
                box((YY-200)/10 - 2,(YY-200)/10 - 2);
            }
        }
        string opp = "OPPONENT";
        string you = "YOU";
        gout << font("LiberationSans-Regular.ttf",20);
        gout << color(255,255,255) << move_to(100,100-gout.cascent()-5) << text(opp);
        gout << color(255,255,255) << move_to(XX-100-gout.twidth(you),100-gout.cascent()-5) << text(you);
        //
        gout << refresh;
    }
}

void Sea::win_open(const int XX,const int YY) {
    event ev;
    gout.open(XX,YY);
}

int main() {

    Sea s = Sea(0,0);
    s.win_open(XX,YY);
    s.event_loop();

    return 0;
}
