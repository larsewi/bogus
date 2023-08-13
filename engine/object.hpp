#ifndef BOGUS_OBJECT_HPP
#define BOGUS_OBJECT_HPP

namespace bogus {

class Object {
public:
  virtual ~Object() {}

protected:
  virtual bool Events() { return true; }
  virtual bool Update() { return true; }
  virtual bool Render() { return true; }
};

} // namespace bogus

#endif // BOGUS_OBJECT_HPP
