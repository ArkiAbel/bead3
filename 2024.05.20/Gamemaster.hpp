#ifndef GAMEMASTER_HPP
#define GAMEMASTER_HPP

#include "Widget.hpp"
#include <string>
#include <vector>

//foglalt mezok tipusa
struct Reserved {
    int x, y;
    std::string id;
};

//jatekmester
class Gamemaster : public Select_widget {
    protected:

    bool IsMenu;
    bool IsGame;
    bool IsTurn;
    bool IsWinGame;
    std::string Player;
    bool OnShip;

    public:

    Gamemaster(bool active_1, bool active_2, bool active_3, bool im, bool ig, bool it, bool iwg, std::string pl, bool os) :
        Select_widget(active_1, active_2, active_3), IsMenu(im), IsGame(ig), IsTurn(it), IsWinGame(iwg), Player(pl), OnShip(os) {};

    void event_loop(std::vector<std::string> b, std::vector<int> sz, std::vector<Reserved> &rl, std::vector<Reserved> &rr, std::vector<Reserved> &sol, std::vector<Reserved> &sor, bool left_ok);
    void win_open(const int XX,const int YY);
    void info_load(std::vector<std::string> &b, std::vector<int> &sz);
    void shot(std::vector<Reserved> &rl, std::vector<Reserved> &rr);
};

#endif // GAMEMASTER_HPP
