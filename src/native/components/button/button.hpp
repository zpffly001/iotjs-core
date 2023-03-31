#include "native/components/component.hpp"

class Button : public BasicComponent {
public:
  Button(std::string uid, lv_obj_t* parent = nullptr);
};