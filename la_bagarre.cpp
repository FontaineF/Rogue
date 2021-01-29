#include <iostream>

#include "classe_globale.cpp"

void bagarre(Hero& heros, Enemy& mechant){

    while((mechant.Hits > 0) and (heros.Hits > 0)){
        mechant.prendre_un_coup(heros);
        if (mechant.Hits > 0){
            heros.prendre_un_coup(mechant);
        }
    }
}