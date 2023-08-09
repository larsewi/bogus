//
// Created by larsewi on 19.08.2020.
//

#ifndef BOGUS_SANDBOX_HPP
#define BOGUS_SANDBOX_HPP

#include <bogus.hpp>

class Sandbox : public bogus::Application {
public:
  using Application::Application;

protected:
  bool OnInit() override;
  bool OnEvent() override;
  bool OnUpdate() override;
  bool OnDraw() override;
  bool OnExit() override;
};

#endif // BOGUS_SANDBOX_HPP
