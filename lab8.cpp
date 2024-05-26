#include "Head.h"
#include "Drawing.h"


int main(){
    Clock clock;
    getTextures();
    initWalls();
    draw_all(window);
    return 0;
}