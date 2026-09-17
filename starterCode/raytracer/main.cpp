#include "Framebuffer.h"

int main() {
    Framebuffer fb(500,500);

    fb.clearToGradient(vec3(0,1,1),vec3(1,0,1));

    fb.exportToPNG("gradient.png");

};