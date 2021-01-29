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

        void move_right(){
            Pos_x++;
        };
        void move_left(){
            Pos_x--;
        };
        void move_up(){
            Pos_y++;
        };
        void move_down(){
            Pos_y--;
        };

        void prendre_un_coup(const Alive opponent){
            int damage_taken=opponent.Str-this->Armor;
            if (damage_taken>0){Hits=Hits-damage_taken;}
        };
};