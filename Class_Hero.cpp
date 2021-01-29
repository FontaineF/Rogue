#include <iostream>
#include "alive.cpp"
using namespace std;


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

int main(){
    Hero Hero1();
    return 0;
}