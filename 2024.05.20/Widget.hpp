#ifndef WIDGET_HPP
#define WIDGET_HPP

//kivalaszto widget loszertipus kivalasztasahoz
class Select_widget{
    protected:

    bool active_1;
    bool active_2;
    bool active_3;

    public:

    Select_widget(bool a1, bool a2, bool a3) : active_1(a1), active_2(a2), active_3(a3) {};
};

#endif // WIDGET_HPP
