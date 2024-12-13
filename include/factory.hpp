#pragma once
#include "observer.hpp"
#include "npc.hpp"
#include "knight.hpp"
#include "princess.hpp"
#include "dragon.hpp"
#include "npc.hpp"

class Factory {
  public:
    static std::shared_ptr<NPC>
    CreateNPC(const NPCtype &type, const std::string &name, int x, int y) {
        std::shared_ptr<NPC> result;
        switch (type) {
        case NPCtype::DragonT:
            result = std::static_pointer_cast<NPC>(
                std::make_shared<Dragon>(name, x, y));
            break;

        case NPCtype::PrincessT:
            result = std::static_pointer_cast<NPC>(
                std::make_shared<Princess>(name, x, y));
            break;

        case NPCtype::KnightT:
            result = std::static_pointer_cast<NPC>(
                std::make_shared<Knight>(name, x, y));
            break;
        default:
            break;
        }

        if (result) {
            result->subscribe(TextObserver::get());
            result->subscribe(FileObserver::get());
        }

        return result;
    }

    static std::shared_ptr<NPC> CreateNPC(std::istream &is) {
        std::shared_ptr<NPC> result;
        int type{0};
        if (is >> type) {
            switch (type) {
            case NPCtype::DragonT:
                result =
                    std::static_pointer_cast<NPC>(std::make_shared<Dragon>(is));
                break;

            case NPCtype::PrincessT:
                result =
                    std::static_pointer_cast<NPC>(std::make_shared<Princess>(is));
                break;

            case NPCtype::KnightT:
                result =
                    std::static_pointer_cast<NPC>(std::make_shared<Knight>(is));
                break;
            default:
                break;
            }
        } else {
            std::cerr << "Unexpected NPC type:" << type << std::endl;
        }

        if (result) {
            result->subscribe(TextObserver::get());
            result->subscribe(FileObserver::get());
        }

        return result;
    }
};