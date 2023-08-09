//
// Created by larsewi on 19.08.2020.
//

#ifndef BOGUS_SANDBOX_APP_HPP
#define BOGUS_SANDBOX_APP_HPP

#include <bogus.hpp>

class SandboxApp : public Bogus::Application {
public:
protected:
  bool OnInit() override;
  bool OnEvent() override;
  bool OnUpdate() override;
  bool OnDraw() override;
  bool OnExit() override;
};

#endif // BOGUS_SANDBOX_APP_HPP
