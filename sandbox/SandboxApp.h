//
// Created by larsewi on 19.08.2020.
//

#ifndef ACRYLIC_SANDBOXAPP_H
#define ACRYLIC_SANDBOXAPP_H

#include <Acrylic.h>

class SandboxApp : public Application {
public:
    SandboxApp(int width, int height, const std::string& title);
    ~SandboxApp() override = default;

protected:
    void onBegin() override;
    void onEvent() override;
    void onUpdate() override;
    void onDraw() override;
    void onExit() override;
};

#endif //ACRYLIC_SANDBOXAPP_H
