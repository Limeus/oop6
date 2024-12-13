#pragma once
#include "npc.hpp"
#include "visitor.hpp"

struct Dragon : public NPC {
    Dragon(const std::string &name, int x, int y);
    Dragon(std::istream &is);

    void print() override;

    virtual bool opportunity(const std::shared_ptr<NPC> &attacker) const override;

    void save(std::ostream &os) override;

    friend std::ostream &operator<<(std::ostream &os, Dragon &Dragon);
};