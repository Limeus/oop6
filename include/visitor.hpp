#pragma once
#include "npc.hpp"

class Visitor {
    public:
    virtual bool visit(const std::shared_ptr<NPC> &) const = 0;
};

class DragonV final : public Visitor { // не может наследоваться
public:
    bool visit(const std::shared_ptr<NPC> &npc) const override {
        bool result{};
        switch (npc->get_type()){
            case NPCtype ::DragonT:
            result = false;
            break;
            
            case NPCtype::PrincessT:
            result = false;
            break;

            case NPCtype::KnightT:
            result = true;
            break;
        }
        return result;
    }
};

class PrincessV final : public Visitor{
    bool visit(const std::shared_ptr<NPC> &npc) const override{
        bool result{};
        switch(npc->get_type()) {
            case NPCtype::DragonT:
            result = false;
            break;

            case NPCtype::PrincessT:
            result = false;
            break;

            case NPCtype::KnightT:
            result = false;
            break;
        }
        return result;
    }
};

class KnightV final : public Visitor{
    bool visit(const std::shared_ptr<NPC> &npc) const override{
        bool result{};
        switch (npc->get_type()){
            case NPCtype::DragonT:
            result = true;
            break;

            case NPCtype::KnightT:
            result = false;
            break;

            case NPCtype::PrincessT:
            result = false;
            break;
        }
        return result;
        }
};

class FactoryV{
public:
    static std::shared_ptr<Visitor> create_visitor(const NPCtype &type){
        std::shared_ptr<Visitor> result;
        switch(type){
            case NPCtype::DragonT:
            result = std::static_pointer_cast<Visitor>(
                std::make_shared<DragonV>());
            break;
           

            case NPCtype::PrincessT:
            result = std::static_pointer_cast<Visitor>(
                std::make_shared<PrincessV>());
            break;

            case NPCtype::KnightT:
            result = std::static_pointer_cast<Visitor>(
                std::make_shared<KnightV>());
            break;
            default:
                break;
        }
        return result;
    }
};

