#include<iostream>

class Alive{
    public:
        char Name;
        int Hits;
        int max_Hits;
        int Str;
        int Armor;
        int Pos_x;
        int Pos_y;

    //public:

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

class Enemy : public Alive{
    protected:

    public:
        Enemy(char c, int x, int y): Alive(){this->Name = c; this->Pos_x = x; this->Pos_y = y;};
        // Enemy enemy1{'s',10,10}

        void initialiser(){
            char c;
            c = this->Name;
            if(c='s'){                  //Snake: enemi faible
                this->Hits = 3;
                this->max_Hits = 3;
                this->Str = 2;
                this->Armor = 0;
            }

            if(c='z'){                  //Zombie: enemi basique
                this->Hits = 6;
                this->max_Hits = 6;
                this->Str = 3;
                this->Armor = 0;
            }

            if(c='v'){                  //Vampire: général enemi
                this->Hits = 15;
                this->max_Hits = 15;
                this->Str = 5;
                this->Armor = 3;
            } 
        }
};

class Hero : public Alive
{
    public:
    Hero (
        char Name = 'A',   
        int Pos_x = 10, 
        int Pos_y = 10, 
        int Gold = 0
        ):
        Alive(), Gold(Gold){};
        
    private:
    int Gold;
};