#include "knight.hpp"

Knight::Knight(const std::string &name, int x, int y) : NPC(KnightT, name, x, y) {}

Knight::Knight(std::istream &is) : NPC(KnightT, is) {}

bool Knight::opportunity(const std::shared_ptr<NPC> &attacker) const {
    std::shared_ptr<Visitor> attacker_visitor =
            FactoryV::create_visitor(attacker->get_type());

    std::shared_ptr<NPC> defender =
            std::const_pointer_cast<NPC>(shared_from_this());

    bool result = attacker_visitor->visit(defender);
    attacker->fight_notify_result(defender, result);
    return result;
}

void Knight::print() { std::cout << *this; }

void Knight::save(std::ostream &os) {
    os << KnightT << std::endl;
    NPC::save(os);
}

std::ostream &operator<<(std::ostream &os, Knight &Knight) {
    os << "Knight: " << *static_cast<NPC *>(&Knight) << std::endl;
    return os;
}