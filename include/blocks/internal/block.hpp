#pragma once
#include <SDL3/SDL.h>
#include <functional>
#include <memory>
#include <string>
#include "systems/tex_manager.hpp"
#include "blocks/internal/sprite/block_sprite.hpp"

class Block : public std::enable_shared_from_this<Block>
{
public:
    virtual ~Block(){};
    virtual void Update() {};
    virtual void Reset() {};
    virtual std::vector<std::weak_ptr<Block>> Propagate(){};
    virtual bool IsReady(){};

    std::string GetName() const {return m_name;}
    int GetID() const {return m_id;}
    std::weak_ptr<BlockSprite> GetSprite() {return m_sprite;}  

protected:
    std::shared_ptr<BlockSprite> m_sprite;
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