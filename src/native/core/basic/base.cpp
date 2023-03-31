#include "base.hpp"


std::unordered_map<std::string, BasicComponent*> comp_map;

BasicComponent::BasicComponent (std::string& uid) {
    this->uid = uid;
    comp_map.insert({ this->uid, this });
};


BasicComponent::~BasicComponent () {
    comp_map.erase(this->uid);
};