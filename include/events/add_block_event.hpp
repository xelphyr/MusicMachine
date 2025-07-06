#pragma once
#include <memory>
#include "blocks/internal/block.hpp"

struct AddBlockEvent
{
    std::shared_ptr<Block> block;
};