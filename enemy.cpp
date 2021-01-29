#include "alive.cpp"
#include<iostream>

class Enemy : public Alive{
    protected:

    public:
        Enemy(char c, int x, int y): Alive(){this->Name = c;};

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