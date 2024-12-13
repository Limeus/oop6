#pragma once
#include "factory.hpp"
#include "npc.hpp"

void save(const npc_set &array, const std::string &filename);

npc_set load(const std::string &filename);

npc_set fight(const npc_set &array, size_t distance);

std::ostream &operator<<(std::ostream &os, const npc_set &array);