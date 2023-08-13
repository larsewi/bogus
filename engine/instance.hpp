#ifndef BOGUS_INSTANCE_HPP
#define BOGUS_INSTANCE_HPP

#include <vulkan/vulkan.h>

#include <memory>
#include <stdexcept>
#include <vector>

#include "object.hpp"
#include "window.hpp"

namespace bogus {

class InstanceException : public std::exception {
public:
  InstanceException(const std::string &message) : m_message(message){};
  virtual const char *what() const throw() { return m_message.c_str(); };

private:
  std::string m_message;
};

class Instance : public Object {
public:
  Instance(const std::string &name, int major, int minor, int patch,
           const std::unique_ptr<Window> &window);
  Instance(const Instance &instance) = default;
  ~Instance();
  bool Events() override;
  bool Update() override;
  bool Render() override;

private:
  const std::string m_name;
  const int m_major;
  const int m_minor;
  const int m_patch;
  VkInstance m_instance;
};

} // namespace bogus

#endif // BOGUS_INSTANCE_HPP
