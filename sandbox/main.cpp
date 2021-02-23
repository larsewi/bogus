
#define WIDTH 720
#define HEIGHT 480
#define TITLE "Bogus Game Engine"

#include "SandboxApp.h"

int main() {
    const char *const tag = "main";
    auto logger = Bogus::Logger::getInstance();
    logger->setLogLevel(Bogus::Logger::LOG_LEVEL_DEBUG);

    logger->logDebug(tag, "Starting sandbox");
    auto app = SandboxApp(WIDTH, HEIGHT, TITLE);
    app.run();

    delete logger;
    return 0;
}
