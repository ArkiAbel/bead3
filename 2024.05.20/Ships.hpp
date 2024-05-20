#ifndef SHIPS_HPP
#define SHIPS_HPP

#include <string>
#include <vector>

//hajok tipusa
struct Ship {
    int x, y;
    std::string id;
};

//foglalt mezok tipusa
struct Reserved;

class Ships {
    protected:

    std::vector<Ship>cv;
    std::vector<Ship>bv;
    std::vector<Ship>crv;
    std::vector<Ship>sv;
    std::vector<Ship>dv;
    bool left_ok;
    bool right_ok;
    //tobbi hajo vektora

    public:

    Ships(bool os, std::vector<Ship>cv,
           std::vector<Ship>bv, std::vector<Ship>crv, std::vector<Ship>sv, std::vector<Ship>dv, bool lo, bool ro) :
            cv(cv), bv(bv), crv(crv), sv(sv), dv(dv), left_ok(lo), right_ok(ro) {}

    void generate_ships_left(std::vector<Reserved> &rl);
    void generate_ships_right(std::vector<Reserved> &rr);
};

#endif // SHIPS_HPP
