#include "solid.h"

using namespace std;

int main(int argc, char** argv) {
    Solid solid = Solid("/home/zanymonk/Coding/INFO2/Sys/SurfaceMeasurer/data/bouddha1m.off");

    cout << "This solid surface is " << solid.computeSurface();
    return 0;
}
