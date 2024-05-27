#include "Head.h"
#include "Drawing.h"


int main(){
    getTextures();
    initWalls();
    initEnemies();
    initText();
    draw_all(window);
    return 0;
}
