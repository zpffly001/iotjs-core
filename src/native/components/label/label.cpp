#include "label.hpp"


Label::Label(std::string uid, lv_obj_t *parent) : BasicComponent(uid)
{
    this->type = COMP_TYPE_LABEL;
    this->uid = uid;
    this->instance = lv_label_create(parent != nullptr ? parent : GetWindowInstance());
    this->parent_instance = parent;

    lv_group_add_obj(lv_group_get_default(), this->instance);

    lv_obj_clear_flag(this->instance, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    lv_obj_add_flag(this->instance, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_CLICK_FOCUSABLE);
    lv_obj_set_user_data(this->instance, this);
}