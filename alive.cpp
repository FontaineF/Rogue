#include<iostream>

class Alive{
    protected:
        char Name;
        int Hits;
        int max_Hits;
        int Str;
        int Armor;
        int Pos_x;
        int Pos_y;

    public:

        void move_right();
        void move_left();
        void move_up();
        void move_down();

        void prendre_un_coup(Alive);
};