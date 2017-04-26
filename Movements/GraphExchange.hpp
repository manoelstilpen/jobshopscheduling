#ifndef GRAPHEXCHANGE_HPP
#define GRAPHEXCHANGE_HPP

#include <unistd.h>
#include "Movement.hpp"

using namespace twtjssp;

class GraphExchange : public Movement {

public:
    GraphExchange();
    GraphExchange(Solution);

    virtual Solution apply();

    float couldMoveTime;
    float evaluateTime;
    float invertTime;
};

#endif