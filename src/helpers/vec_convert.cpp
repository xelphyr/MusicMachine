#include "helpers/vec_convert.hpp"


SDL_FPoint MM::Helpers::ToSDL_FPoint(ImVec2 point)
{
    return SDL_FPoint({point.x, point.y});
}

ImVec2 MM::Helpers::ToImVec2(SDL_FPoint point)
{
    return ImVec2({point.x, point.y});
}
