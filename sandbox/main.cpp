
#define WIDTH 720
#define HEIGHT 480
#define TITLE "Acrylic Game Engine"

#include "SandboxApp.h"

int main() {
    auto app = SandboxApp(WIDTH, HEIGHT, TITLE);
    app.run();
    return 0;
}
