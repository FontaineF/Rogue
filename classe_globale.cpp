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
            Pos_y++;
        };
        void move_left(){
            Pos_y--;
        };
        void move_up(){
            Pos_x++;
        };
        void move_down(){
            Pos_x--;
        };

        void prendre_un_coup(const Alive opponent){
            int damage_taken=opponent.Str-this->Armor;
            if (damage_taken>0){this->Hits=(this->Hits-damage_taken);}
        };


};

class Enemy : public Alive{
    protected:

    public:
        Enemy(char c, int x, int y): Alive(){this->Name = c; this->Pos_x = x; this->Pos_y = y;};
        // Enemy enemy1{'s',10,10}
        int energie;
        int cout_mouvement;
        void initialiser(){
            char c;
            c = this->Name;
            if(c=='s'){                  //Snake: enemi faible
                this->Hits = 3;
                this->max_Hits = 3;
                this->Str = 2;
                this->Armor = 0;
                this->energie=1;
                this->cout_mouvement=1;
            }

            if(c=='z'){                  //Zombie: enemi basique
                this->Hits = 8;
                this->max_Hits = 8;
                this->Str = 3;
                this->Armor = 0;
                this->energie=0;
                this->cout_mouvement=2;
            }

            if(c=='v'){                  //Vampire: général enemi
                this->Hits = 15;
                this->max_Hits = 15;
                this->Str = 5;
                this->Armor = 1;
                this->energie=1;
                this->cout_mouvement=1;
            } 
            if(c=='t'){
                this->Hits = 1;
                this->max_Hits = 1;
                this->Str = 0;
                this->Armor = 0;
                this->energie=-999;
                this->cout_mouvement=1;
            } 
        }
};

class Hero : public Alive
{
    public:
    Hero (
        char c = 'A',   
        int x = 10, 
        int y = 10, 
        int Gold = 0
        ):
        Alive(), Gold(Gold){this->Name = c; this->Pos_x = x; this->Pos_y = y;};
        
    void initialiser(){
            char c;
            c = this->Name;
            if(c=='b'){                  //Bandit : Treès faible
                this->Hits = 5;
                this->max_Hits = 5;
                this->Str = 3;
                this->Armor = 0;
            }

            if(c=='c'){                  //Chevalier : Force moyenne PV moyen
                this->Hits = 10;
                this->max_Hits = 10;
                this->Str = 5;
                this->Armor = 2;
            }

            if(c=='g'){                  //Geant : Force faible mais PV eleve
                this->Hits = 20;
                this->max_Hits = 20;
                this->Str = 6;
                this->Armor = 0;
            }
        }

    private:
    int Gold;
};