#include <iostream>
#include <string>
//#include "la_chasse.cpp"
#include "classe_globale.cpp"
//#include "Class_Hero.cpp"
//#include "enemy.cpp"
//#include "alive.cpp"

#include <vector>

// Attention ce code est très basique et très mal structuré: des
// variables globales et des fonctions globales là où on attendrait
// une structure de classe avec des attributs (éventuellement
// static). Il n'est là que pour vous aider dans l'utilisation d'une
// petite librairie ncurses qui permet un graphique alphanumérique
// basique et minimal dans un terminal. Vous devez naturellement faire
// une bonne structure de code et y appeler les fonctions ncurses dont
// vous voyez ci-dessous une utilisation rudimentaire.

// LA LIBRAIRIE
// ============
// Pour obtenir ce graphique minimal "au terminal" vous devez
// 1) installer la librarie ncurses
// sudo apt-get update
// sudo apt-get install ncurses-dev

// 2) importer son header
#include <ncurses.h>

// 3) compiler en linkant la librarie
// g++ nethack.cpp -lncurses -o play


// LE CODE
// =======

// Ci-dessous voici le code très basique et pas structuré pour faire
// courrir un '@'

// LE HÉRO
// =======

// la position du '@' qui est aussi la position du curseur de votre
// terminal
/*
int xcursor = 3; // ligne
int ycursor = 4; // colonne
*/

// un exemple de héro et d'une bébête quelconque
/*
const char hero = '@';
const char bebete = 'E';
*/

// LE TERMINAL
// ===========

// Le terminal est votre playground. Il est constituée d'un nombre de
// lignes et de colonnes (une sorte de matrice). CEs deux valeurs vous
// seront données par une fonction de ncurses.

// Dans cet exemple de code très simpliste, on repère, de manière
// basique, l'espace de jeu (celui où se baladera votre héro) par:
int window_top;
int window_left;
int window_bottom;
int window_right;


// LES TOUCHES DE DÉPLACEMENT
// ==========================
// On décide des 4 touches pour déplacer le héro (ici les 4 flêches en
// bas et à droite de votre clavier)
constexpr int left_arrow = 4;
constexpr int right_arrow = 5;
constexpr int top_arrow = 3;
constexpr int bottom_arrow = 2;
// On crée (ici par une énumération) un ensemble des 4 directions de
// déplacement.
enum DIRECTION
  {
   LEFT = left_arrow,
   RIGHT = right_arrow,
   TOP = top_arrow,
   BOTTOM = bottom_arrow,
  };


// DES COULEURS
// ============

// On décide d'un ensemble de couleurs, par exemple:
enum COLOR
  {
   BLACK = 0,
   RED = 1,
   BLUE = 2,
   GREEN = 3,
   CYAN = 4,
   YELLOW = 5
  };
// On initialise ces couleurs pour notre ternimal (si celui-ci possède
// des couleurs).
void init_color () {
  if (has_colors()) {
  start_color();
  init_pair(BLACK, COLOR_BLACK, COLOR_BLACK);
  init_pair(RED, COLOR_RED, COLOR_BLACK);
  init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
  init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
  init_pair(CYAN, COLOR_CYAN, COLOR_BLACK);
  init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
  }
}

// AFFICHAGE DES MESSAGES
// ======================
// On va afficher des messages de jeu, par exemple ici à la première
// ligne première colonne du terminal.
int xmsg = 0;
int ymsg = 0;

// On doit effacer le message précédent i.e. le recouvrir par une
// chaine de caractères blancs, qu'on crée avec la fonction
// suivante. Faites mieux !
char* white_line;

char* init_white_line (int size) {
  char* buff = new char [size];
  for (int i = 0; i < size; ++i)
    buff[i] = ' ';
  buff[size-1] = '\0';
  return buff;
}

// On affiche le message msg dans la couleur YELLOW par défaut. à la
// position de la ligne de message décidée auparavant (remarquez
// l'horrible utilisation de variables globales dans cette
// fonction. Il faut faire une structure de classes.
void print_message (const char* msg,  Alive& hero, int color_pair = YELLOW) {
  // on charge la couleur color_pair.
  attron(COLOR_PAIR(color_pair));
  // move déplace le curseur à la position du message en ligne colonne
  // (ici ligne xmsg, colonne ymsg)
  move(xmsg, ymsg);
  // On affiche la ligne blanche (pour effacer le message précédent).
  addstr(white_line);
  // On revient à la position du message.
  move(xmsg, ymsg);
  // On affiche le message.
  addstr(msg);
  // On retourne à la position du héro.
  move(hero.Pos_x, hero.Pos_y);
  // On enlève la couleur choisie.
  attroff(COLOR_PAIR(color_pair));
  refresh();
}

void debug_print_hero_position (Alive& hero) {
  std::string str = "the hero is at position line ";
  str += std::to_string(hero.Pos_x);
  str += ", column ";
  str += std::to_string(hero.Pos_y);
  attron(COLOR_PAIR(BLUE));
  move(1, 0);
  addstr(white_line);
  move(1, 0);
  addstr(str.c_str());
  move(hero.Pos_x, hero.Pos_y);
  attroff(COLOR_PAIR(BLUE));
  refresh();
}

// INITIALISATION DU TERMINAL
// ==========================
void init () {
  // on initialise le terminal en mode curses
  initscr();
  // on initialise des couleurs
  init_color();

  clear();
  // on efface le stdscr (le terminal, the standard screen)

  // Comme nous allons taper des caractères pour les commandes du
  // héro, on ne veut pas qu'ils s'affichent (i.e. qu'ils aient un
  // écho sur le standard screen. noecho() switchs off echoing
  noecho();  

  // Par défaut, les caractères entrés sont stockés dans une mémoire
  // tampon (buffer) jusqu'au prochain retour à la ligne (enter). Pour
  // obtenir les caractères dès que nous les tapons, nous devons
  // désactiver la mise en mémoire tampon de la ligne.
  // Nous passons en mode brut (raw), cela empêche les
  // caractères de contrôle (CTRL-C) de générer leur signal (genre
  // tuer l'exécutable). Donc vous ne pouvez pas quitter le programme
  // avec CTRL-C ni le suspendre avec CTRL-Z.
  cbreak(); // or raw();

  // On active les clés F1, F2... et les flêches (puisqu'on veut
  // déplacer notre héro avec).
  keypad(stdscr, TRUE);
  refresh();

 // On demande la taille en nombre de lignes de la fenêtre.
  getmaxyx(stdscr, window_bottom, window_right);

  // On délimite notre playground n'importe comment dans cet exemple
  window_left = 1;
  window_top = 2;
  window_bottom = 15;//window_bottom - 15;
  window_right = window_right - 15;




  white_line = init_white_line(window_right+1);
}


// AFFICHER UN CARACTÈRE
// =====================

// Cette fonction déplace le curseur à la position (xpos, ypos)
// affiche le caractère thing et, comme l'affichage fait avancer le
// curseur, on le remet à la position initiale move it back to
// xcursor, ycursor
/*
void affiche (Alive& entity, int color_pair = 0) {
  attron(COLOR_PAIR(color_pair));
  move(entity.Pos_x, entity.Pos_y);
  addch(entity.Name);
  move(entity.Pos_x, entity.Pos_y);
  attroff(COLOR_PAIR(color_pair));
  refresh();
}
*/
void affiche (int xpos, int ypos, char thing, int color_pair = 0) {
  attron(COLOR_PAIR(color_pair));
  move(xpos, ypos);
  addch(thing);
  move(xpos, ypos);
  attroff(COLOR_PAIR(color_pair));
  refresh();
}

// DÉPLACEMENT DU HÉRO
// ===================

// mon héro laisse une trace en marchant (aucun intérêt on pourrait
// juste écrire un step ' ' pour effacee le héro)
const char step = ' ';

// En argument on passe le caractère qui représente la mouvement du
// héro i.e LEFT, RIGHT, TOP ou BOTTOM. Le héro est à la position
// (xcursor, ycursor) après le mouvement, par exemple 'LEFT', il va à
// la nouvelle position (xcursor, ycursor-1) - si c'est possible -

void move (char c, Alive& hero) {
  // On affiche un step pour effacer le héro de la position qu'il va
  // quitter.
  affiche(hero.Pos_x, hero.Pos_y, step);
  
  // Le héro est en noir.
  int color = BLACK;
  

  if (c == LEFT) {
    print_message("the hero is heading left", hero);
    if (hero.Pos_y != window_left) {
      // le mouvement est possible
      // on bouge le curseur à la position (xcursor, ycursor-1)
      hero.move_left();
    } else {
      print_message("the hero reached the playground left side", hero);
      color = RED; // il voit rouge
    }
  }
  else if (c == RIGHT) {
    print_message("the hero is heading right", hero);
    if (hero.Pos_y != window_right) {
      // on modifie la position du curseur à la position (xcursor, ycursor+1)
      hero.move_right();
    } else {
      print_message("the hero reached the playground right side", hero);
      color = CYAN; // il est cyanosé 
    }
  }
  else if (c == BOTTOM) {
    print_message("the hero is heading down", hero);

    if (hero.Pos_x != window_bottom) {
      // on modifie la position du curseur à la position (xcursor+1, ycursor)
      hero.move_up();
    } else {
      print_message("the hero reached the playground bottom side", hero);
      color = YELLOW; // il est malade
    }
  }
  else if (c == TOP) {
    print_message("the hero is heading up", hero);
    if (hero.Pos_x != window_top) {
      // on bouge le curseur à la position (xcursor-1, ycursor)
      hero.move_down();
    } else {
      print_message("the hero reached the playground top side", hero);
      color = GREEN; // il a peur
    }
  }
  // On affiche le héro à la position (xcursor, ycursor)
  affiche(hero.Pos_x, hero.Pos_y, hero.Name, color);
  // pour debugger on affiche la position du héro en bleu sur la
  // seconde ligne
  debug_print_hero_position(hero);
}


int la_chasse(Hero hero, Enemy ennemi){
    int x=hero.Pos_x - ennemi.Pos_x;
    int y=hero.Pos_y - ennemi.Pos_y;
    if (x*x>y*y){
        if (x<0){return 4;}
        else {return 6;}

    }
    else {
        if (y<0){return 8;}
        else{return 2;} 
    }

}


void move_mechant (Hero& hero,Enemy& mechant) {
  // On affiche un step pour effacer le héro de la position qu'il va
  // quitter.
  affiche(mechant.Pos_x, mechant.Pos_y, step);
  
  // Le héro est en noir.
  int color = BLACK;
  int c=la_chasse(hero,mechant);

  if (c == 4) {
    
    if (mechant.Pos_y != window_left) {
      // le mouvement est possible
      // on bouge le curseur à la position (xcursor, ycursor-1)
      mechant.move_left();
    } 
  }
  else if (c == 6) {
    
    if (mechant.Pos_y != window_right) {
      // on modifie la position du curseur à la position (xcursor, ycursor+1)
      mechant.move_right();
    }
  }
  else if (c ==2) {
    

    if (mechant.Pos_x != window_bottom) {
      // on modifie la position du curseur à la position (xcursor+1, ycursor)
      mechant.move_up();
    } 
  }
  else if (c == 8) {
   
    if (mechant.Pos_x != window_top) {
      // on bouge le curseur à la position (xcursor-1, ycursor)
      mechant.move_down();
    } 
  }
  // On affiche le héro à la position (xcursor, ycursor)
  affiche(mechant.Pos_x, mechant.Pos_y, mechant.Name, color);

}


void bagarre(Hero& heros, Enemy& mechant){

    while((mechant.Hits > 0) and (heros.Hits > 0)){
        mechant.prendre_un_coup(heros);
        if (mechant.Hits > 0){
            heros.prendre_un_coup(mechant);
        }
    }
}

void affrontement(Hero& h, Enemy& e){
    int x_h = h.Pos_x;
    int y_h = h.Pos_y;
    int x_e = e.Pos_x;
    int y_e = e.Pos_y;

    int diff_x = x_h - x_e;
    int diff_y = y_h - y_e;

    if((diff_x==0 and (diff_y * diff_y < 1)) or (diff_y==0 and (diff_x * diff_x < 1))){
        bagarre(h,e);
    }

}


// ON JOUE
// =======
// Retourne vrai si le caractère c est une direction.
bool is_direction (char c) {
  return ((c == LEFT) or (c == RIGHT)
	  or (c == BOTTOM) or (c == TOP));
}
// On affiche une erreur quand le caractère n'est pas connu, ne pas
// garder cette fonction, c'est juste pour debugger ce que vous tapez.
void print_char_error_message(char c, Alive& hero) {
  std::string msg = "the character '";
  msg += c;
  msg += "' is not an action !";
  print_message(msg.c_str(), hero, RED);
}
void play () {
  // On initialise le terminal en ncurses.
  init();

  Hero hero('g');
  hero.initialiser();

  Enemy serpent('s',15,15);
  serpent.initialiser();
  Enemy zombie('z', 12,26);
  zombie.initialiser();
  Enemy vampire('v',5,47);
  vampire.initialiser();
  std::vector<Enemy> entites{serpent,zombie,vampire};



  // On affiche le héro.
  affiche(hero.Pos_x, hero.Pos_y, hero.Name);

  // on affiche une bébête
  
  for(Enemy& e : entites){
    affiche(e.Pos_x, e.Pos_y, e.Name);
  }
  
  //affiche(serpent.Pos_x, serpent.Pos_y, serpent.Name);
  //affiche(zombie.Pos_x, zombie.Pos_y, zombie.Name);
  //affiche(vampire.Pos_x, vampire.Pos_y, vampire.Name);

  print_message("Welcome to our brave hero !", hero);
  debug_print_hero_position(hero);
  char c = '\0';
  // On entre dans une boucle sans fin sauf si le caractère 'q' est
  // entré.
  while (c != 'q') {
    // On récupère le caractère tapé.
    c = getch();
    if (is_direction(c)) {
      // Si le caractère est une direction en bouge le héro.
      move(c, hero);
      
      for(Enemy& e : entites){
        if(e.Hits>0){
          affrontement(hero,e);
          if(hero.Hits < 1){
            print_message("Vous êtes mort.", hero);
          delete white_line;
          endwin();
          exit(1);
          }
        }
      }
      for(Enemy& e : entites){
        if(e.Hits>0){
          move_mechant(hero,e);
          affrontement(hero,e);
        }
      }
      
    } else {
      // Et là le caractère peut être des tas d'autres choses !
      // monstres qu'il faut combattre, objet magique qu'il faut
      // ramasser etc.
      print_char_error_message(c, hero);
    }
  }
  // Vous devez terminer curses proprement sinon votre terminal sera
  // dans un état tout bizarre...
  delete white_line;
  endwin();
}

// et le main
int main () {
  play();
  return 0;
}
