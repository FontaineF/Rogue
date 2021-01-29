#include "classe_globale.cpp"
int la_chasse(Hero hero, Enemy ennemi){
    int x=hero.Pos_x - ennemi.Pos_x;
    int y=hero.Pos_y - ennemi.Pos_y;
    if (x*x>y*y){
        if (x<0){return 4;}
        else {return 5;}

    }
    else {
        if (y<0){return 3;}
        else{return 2;} 
    }

}
