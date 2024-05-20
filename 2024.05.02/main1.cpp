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
};

void Sea::event_loop() {
    event ev;
    while (gin >> ev && ev.keycode != key_escape) {
        gout << color(0,0,0) << move_to(0,0) << box(XX,YY) << color(255,255,255);
        board_update();
    }
}

void Sea::board_update(const int XX,const int YY) {
    event ev;
    gout << color(255,255,255) << move_to(100,100) << box(YY-200,YY-200);
    gout << color(255,255,255) << move_to(XX/2+100,100) << box(YY-200,YY-200);
}

int main() {

    Sea s = Sea(0,0);
    s.event_loop();
    s.board_update(XX,YY);

    return 0;
}
