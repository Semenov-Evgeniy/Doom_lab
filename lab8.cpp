#include "Head.h"
#include "Drawing.h"


int main(){
    getTextures();
    initWalls();
    initEnemies();
    initText();
    initHealths();
    draw_all(window);
    return 0;
}
