//
// Created by larsewi on 19.08.2020.
//

#ifndef BOGUS_SANDBOX_APP_HPP
#define BOGUS_SANDBOX_APP_HPP

#include <bogus.hpp>

class SandboxApp : public Bogus::Application {
public:
  SandboxApp(int width, int height, const std::string &title);
  ~SandboxApp() override = default;

protected:
  void onInit() override;
  void onEvent() override;
  void onUpdate() override;
  void onDraw() override;
  void onExit() override;
};

#endif // BOGUS_SANDBOX_APP_HPP
