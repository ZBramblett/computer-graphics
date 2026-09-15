#include "vec3.h"
#include "color.h"
#include <string>
#include <vector>

class FrameBuffer {
    public:
    FrameBuffer();
    FrameBuffer() : width(100), height(100){ fb.resize(width * height); }

    void clearToColor(color&);
    void clearToGradient();
    void setPixelColor( int i, int j, const color& c);
    void exportAsPNG( std::string filename);

    private:
    int width, height;
    std::vector < vec3 > fb;
};




