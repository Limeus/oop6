#include "dragon.hpp"

Dragon::Dragon(const std::string &name, int x, int y) : NPC(DragonT, name, x, y) {}
Dragon::Dragon(std::istream &is) : NPC(DragonT, is) {}

bool Dragon::opportunity(const std::shared_ptr<NPC> &attacker) const {
    std::shared_ptr<Visitor> attacker_visitor =
        FactoryV::create_visitor(attacker->get_type());

    std::shared_ptr<NPC> defender =
        std::const_pointer_cast<NPC>(shared_from_this());

    bool result = attacker_visitor->visit(defender);
    attacker->fight_notify_result(defender, result);
    return result;
}

void Dragon::print() { std::cout << *this; }

void Dragon::save(std::ostream &os) {
    os << DragonT << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Dragon &Dragon) {
    os << "Dragon: " << *static_cast<NPC *>(&Dragon) << std::endl;
    return os;
}