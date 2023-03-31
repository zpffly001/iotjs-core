#include <map>
#include <vector>
#include <unordered_map>
#include <mutex>
#include "native/core/common/common.hpp"


enum ECOMP_TYPE {
  COMP_TYPE_VIEW,
  COMP_TYPE_BUTTON,
  COMP_TYPE_IMAGE,
  COMP_TYPE_GIF,
  COMP_TYPE_SLIDER,
  COMP_TYPE_TEXT,
  COMP_TYPE_WINDOW,
  COMP_TYPE_SWITCH,
  COMP_TYPE_TEXTAREA,
  COMP_TYPE_CHECKBOX,
  COMP_TYPE_DROPDOWNLIST,
  COMP_TYPE_PROGRESSBAR,
  COMP_TYPE_ROLLER,
  COMP_TYPE_LINE,
  COMP_TYPE_CALENDAR,
  COMP_TYPE_LIST,
  COMP_TYPE_TABVIEW,
  COMP_TYPE_CHART,
  COMP_TYPE_MASK,
  COMP_TYPE_LABEL,
};

class BasicComponent {
  public:
    BasicComponent(std::string& uid);
    ~BasicComponent();

    lv_obj_t* instance = nullptr;
    lv_obj_t* parent_instance = nullptr;  // used to style position: fixed to normal position
    std::string uid;
    ECOMP_TYPE type;
};

extern std::unordered_map<std::string, BasicComponent*> comp_map;