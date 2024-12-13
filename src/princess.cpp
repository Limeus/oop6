#include "princess.hpp"

Princess::Princess(const std::string &name, int x, int y) : NPC(PrincessT, name, x, y) {}
Princess::Princess(std::istream &is) : NPC(PrincessT, is) {}

bool Princess::opportunity(const std::shared_ptr<NPC> &attacker) const {
    std::shared_ptr<Visitor> attacker_visitor =
        FactoryV::create_visitor(attacker->get_type());

    std::shared_ptr<NPC> defender =
        std::const_pointer_cast<NPC>(shared_from_this());

    bool result = attacker_visitor->visit(defender);
    attacker->fight_notify_result(defender, result);
    return result;
}

void Princess::print() { std::cout << *this; }

void Princess::save(std::ostream &os) {
    os << PrincessT << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Princess &Princess) {
    os << "Princess: " << *static_cast<NPC *>(&Princess) << std::endl;
    return os;
}