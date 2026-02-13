#ifndef REGISTER_HPP
#define REGISTER_HPP

#include <godot_cpp/variant/string.hpp>
#include <vector>

using godot::ModuleInitializationLevel, godot::String, std::vector;

struct SettingProperty;

void initialize(ModuleInitializationLevel p_level);
void uninitialize(ModuleInitializationLevel p_level);

#endif // REGISTER_HPP