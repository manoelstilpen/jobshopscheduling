//
// Created by manoel on 26/03/18.
//

#ifndef JOBSHOPSCHEDULING_RANDGEN_HPP
#define JOBSHOPSCHEDULING_RANDGEN_HPP

#include <Commons.hpp>

using namespace twtjssp;

class RandGen {

public:

    static void setSeed(long); // sets random seed
    static int randomInt(int); // generates random int between 0 and specified number
    static void printSeed();
//    static int randomInt(int, int); // generates random number within specified interval

private:
    static long seed;

};

#endif //JOBSHOPSCHEDULING_RANDGEN_HPP
