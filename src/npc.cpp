#include "npc.hpp"

NPC::NPC(NPCtype j, const std::string &_name, int _x, int _y) : type(j), name(_name), x(_x), y(_y) {} //инициализация

NPC::NPC(NPCtype j, std::istream &is) : type(j){ // чтение из потока
    is >> name;
    is >> x;
    is >> y;
}

void NPC::subscribe (const std::shared_ptr<FightObserver> &observer){
    observers.push_back(observer);
}

void NPC::fight_notify_result(const std::shared_ptr<NPC> defender, bool winner) const{// со стороны нападающего
    for (auto &o : observers)
        o->res_fight(std::const_pointer_cast<NPC>(shared_from_this()), defender, winner);
}

bool NPC::space_check(const std::shared_ptr<NPC> &other, size_t distance) const{
    if((std::pow(x - other->x, 2) + std::pow(y - other->y, 2)) <= std::pow(distance, 2)) return true;
    else
        return false;
}

NPCtype NPC::get_type() { return type; }

std::pair<int, int> NPC::position() const { return{x, y};}

void NPC::save(std::ostream &os) {
    os << name << std::endl;
    os << x << std::endl;
    os << y << std::endl;
}

std::ostream &operator<<(std::ostream &os, NPC &npc){
    os<<npc.name <<" " << "{x:" << npc.x << ", y:" << npc.y << "}";
    return os;
}