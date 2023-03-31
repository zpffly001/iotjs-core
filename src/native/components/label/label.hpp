#include "native/components/component.hpp"

class Label : public BasicComponent
{
public:
    Label(std::string uid, lv_obj_t * parent = nullptr);
};

