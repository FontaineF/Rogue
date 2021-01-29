int la_chasse(Hero hero, Enemy ennemi){
    int x=hero.pos_x - ennemi.pos_x;
    int y=hero.pos_y - ennemi.posy_y;
    if (x*x>y*y){
        if (x<0){return 4;}
        else {return 6;}

    }
    else {
        if (y<0){return 2;}
        else{return 8;} 
    }

}