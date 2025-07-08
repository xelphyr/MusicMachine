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
    enum class Type
    {
        Emitter,
        Processor,
        Source
    };
    
    virtual ~Block(){};
    virtual void Init() {};
    virtual void Update() {};
    virtual void Reset() {};
    virtual std::vector<std::weak_ptr<Block>> Propagate() = 0;
    virtual bool IsReady() = 0;

    std::string GetName() const {return m_name;}
    std::string GetID() const {return m_id;}
    std::weak_ptr<BlockSprite> GetSprite() {return m_sprite;}  
    Type GetType() const {return m_type;}

protected:
    std::shared_ptr<BlockSprite> m_sprite;
    std::string m_name;
    std::string m_id;
    Type m_type;
    bool m_available{true};
};

struct BlockHash
{
    size_t operator()(Block const& b) const 
    {
        return std::hash<std::string>()(b.GetID());
    }
};