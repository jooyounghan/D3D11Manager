#include "InputManager.h"
#include <unordered_map>

#include <string>

using namespace App;

struct InputKeyMap
{
    std::unordered_map<int, std::string> map;
};

struct InputMouseMap
{
    std::unordered_map<int, std::string> map;
};