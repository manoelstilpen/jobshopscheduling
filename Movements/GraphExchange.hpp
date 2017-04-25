#ifndef GRAPHEXCHANGE_HPP
#define GRAPHEXCHANGE_HPP

#include "../Commons.hpp"
#include "../Solution.hpp"
#include "../Evaluator.hpp"

using namespace twtjssp;

class GraphExchange {

public:
    GraphExchange();
    GraphExchange(Solution);

    void apply();
    void updateCouldMove();


private:
    Graph graph;
    Solution solution;
    Evaluator evaluator;
    ProblemInstance instance;

    vector<vector<Edge>> criticalPath;
    vector<Edge> couldMove;
};

#endif