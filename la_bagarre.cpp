#include <iostream>
#include <alive.cpp>
#include <enemy.cpp>

void bagarre(const Alive& heros, const Alive& mechant){

    mechant.prendre_un_coup(heros);
    if (mechant->Hits > 0){heros.prendre_un_coup(mechant);}
}