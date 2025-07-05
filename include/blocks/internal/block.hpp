#pragma once
#include <SDL3/SDL.h>
#include <functional>
#include <string>
#include "blocks/internal/ui/block_ui.hpp"

class Block
{
public:
    virtual ~Block(){};
    virtual void Update() {};
    virtual void Reset() {};
    virtual std::vector<std::weak_ptr<Block>> Propagate(){};
    virtual bool IsReady(){};

    std::string GetName() const {return m_name;}
    int GetID() const {return m_id;}

protected:
    BlockUI m_ui;
    std::string m_name;
    unsigned int m_id;
    bool m_available{true};
};

struct BlockHash
{
    size_t operator()(Block const& b) const 
    {
        return std::hash<unsigned int>()(b.GetID());
    }
};