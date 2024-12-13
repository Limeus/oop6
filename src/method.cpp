#include "method.hpp"

#include <filesystem>
#include <iostream>
#include <string>

std::string getCurrentDir() {
    try {
        return std::filesystem::current_path().string();
    } catch (const std::filesystem::filesystem_error &e) {
        std::cerr << "Error getting current directory: " << e.what() << std::endl;
        return std::string();
    }
}

void save(const npc_set &array, const std::string &filename) {
    std::string currentDir = getCurrentDir();
    if (currentDir.empty()) {
        return;  // Если не удалось получить директорию, прерываем выполнение
    }

    std::string fullPath = currentDir + "\\" + filename;

    std::ofstream fs(fullPath);
    if (!fs) {
        std::cerr << "Failed to open file: " << fullPath << std::endl;
        return;
    }
    fs << array.size() << std::endl;
    std::cout << "Saving " << array.size() << " NPCs to " << fullPath << std::endl;

    for (auto &n : array)
        n->save(fs);

    fs.flush();
    fs.close();
    std::cout << "File successfully saved and closed: " << fullPath << std::endl;
}



npc_set load(const std::string &filename) {
    npc_set result;
    std::ifstream is(filename);
    if (is.good() && is.is_open()) {
        int count;
        is >> count;
        for (int i = 0; i < count; ++i)
            result.insert(Factory::CreateNPC(is));
        is.close();
    } else
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
    return result;
}

npc_set fight(const npc_set &array, size_t distance) {
    npc_set dead_list;
    for (const auto &attacker : array)
        for (const auto &defender : array)
            if ((attacker != defender) &&
                (attacker->space_check(defender, distance))) {
                bool success = defender->opportunity(attacker);
                if (success)
                    dead_list.insert(defender);
            }
    return dead_list;
}

std::ostream &operator<<(std::ostream &os, const npc_set &array) {
    for (auto &n : array)
        n->print();
    return os;
}