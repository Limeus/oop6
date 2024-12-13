#pragma once
#include <cstring>
#include <iostream>
#include <cmath>
#include <set>
#include <memory>
#include <fstream>
#include <vector>
#include <string>
#include <random>

class NPC;
class Princess;
class Knight;
class Dragon;

using npc_set = std::set<std::shared_ptr<NPC>>;
enum NPCtype {Somebody = 0, PrincessT = 1, KnightT = 2, DragonT = 3};

struct FightObserver {
    virtual void res_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool winner) =0;
};

class NPC : public std::enable_shared_from_this<NPC>{
protected:
    NPCtype type;
    std::string name{""};
    int x{0};
    int y{0};
    std::vector<std::shared_ptr<FightObserver>> observers;

public:
    std::shared_ptr<NPC> get_shared(){
        return shared_from_this();
    }

    NPC(NPCtype j, const std::string &name, int _x, int _y);
    NPC(NPCtype j, std::istream &is);

    NPCtype get_type();

    virtual bool opportunity(const std::shared_ptr<NPC> &attacer) const = 0;
    void subscribe(const std::shared_ptr<FightObserver> &observer);
    void fight_notify_result(const std::shared_ptr<NPC> defender,bool winner) const;
    virtual bool space_check(const std::shared_ptr<NPC> &other, size_t distance) const;
    virtual void print() = 0;
    virtual void save(std::ostream &os);
    std::pair <int, int> position() const;
    friend std::ostream &operator<<(std::ostream &os, NPC &npc);
};