int window_right = 100;
int window_left = 2;
int window_bottom = 20;
int window_top = 3;

char map[17][98];
for(int i = 0; i<17; i++){
    for(int j = 0; j<98; j++){
        map[i][j] = ' ';
    }
}

for(int k = 5; k<35; k++){
    map[18][k] = '|';
}