#pragma once

#include <exception>
#include <string>
class potentia_error_code : public std::exception {
public:
  potentia_error_code(const std::string &id);
  const char *what() const noexcept override;
  
protected:
 const  std::string& m_id;
};

// ERROR - engine_config is locked and cannot its values be set
#define THROW_P000001 throw potentia_error_code("P000001");
// ERROR - cannot find usable queue for graphics or present
#define THROW_P000002 throw potentia_error_code("P000002");
// ERROR - vk DepthStencilAttachment is not supported for D16Unorm depth format. 
#define THROW_P000003 throw potentia_error_code("P000003");
// ERROR - Validation Layers are explicitly enabled but not supported
#define THROW_P000004 throw potentia_error_code("P000004");
