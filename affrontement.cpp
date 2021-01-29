#include "classe_globale.cpp"
#include "la_bagarre.cpp"


void affrontement(Hero& h, Enemy& e){
    int x_h = h.Pos_x;
    int y_h = h.Pos_y;
    int x_e = e.Pos_x;
    int y_e = e.Pos_y;

    int diff_x = x_h - x_e;
    int diff_y = y_h - y_e;

    if((diff_x==0 and (-1 < diff_y < 1)) or (diff_y==0 and (-1 < diff_x < 1))){
        bagarre(h,e);
    }

}