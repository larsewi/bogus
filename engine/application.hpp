//
// Created by larsewi on 18.08.2020.
//

#ifndef BOGUS_APPLICATION_HPP
#define BOGUS_APPLICATION_HPP

#include <iostream>
#include <string>

namespace Bogus {

class Application {
public:
  Application(int width, int height, const std::string &title);
  virtual ~Application();

  bool run();

  operator bool() { return m_goodbit; }

protected:
  virtual bool OnInit() { return true; };
  virtual bool OnEvent() { return true; };
  virtual bool OnUpdate() { return true; };
  virtual bool OnDraw() { return true; };
  virtual bool OnExit() { return true; };

private:
  bool m_shouldRun;
  bool m_goodbit;

  bool Init();
  bool Events();
  bool Update();
  bool Render();
  bool Exit();
};

} // namespace Bogus

#endif // BOGUS_APPLICATION_HPP
