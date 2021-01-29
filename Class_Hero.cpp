#include <iostream>
#include "alive.cpp"
using namespace std;


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
            if(c='b'){                  //Barbare : Force haute mais peu de PV
                this->Hits = 7;
                this->max_Hits = 7;
                this->Str = 7;
                this->Armor = 0;
            }

            if(c='c'){                  //Chevalier : Force moyenne PV moyen
                this->Hits = 10;
                this->max_Hits = 10;
                this->Str = 5;
                this->Armor = 2;
            }

            if(c='g'){                  //Geant : Force faible mais PV eleve
                this->Hits = 20;
                this->max_Hits = 20;
                this->Str = 3;
                this->Armor = 0;
            }
        }

    private:
    int Gold;
};

/*
int main(){
    Hero* pHero1 = new Hero();
    Hero Hero2;
    pHero1->move_up();
    pHero1->move_up();
    cout<< pHero1->is_neighbour(Hero2)<<'\n';
    delete pHero1;
    return 0;
}
*/