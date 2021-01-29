#include <iostream>
void bagarre(Alive heros, Alive mechant){

    mechant.prendre_un_coup(heros);
    if (mechant->Hits > 0){heros.prendre_un_coup(mechant);}
}