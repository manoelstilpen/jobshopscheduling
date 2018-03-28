//
// Created by manoel on 26/03/18.
//

#ifndef JOBSHOPSCHEDULING_CONFIG_HPP
#define JOBSHOPSCHEDULING_CONFIG_HPP

#include <Commons.hpp>

#include <boost/program_options.hpp>

using namespace twtjssp;
namespace po = boost::program_options;

class Config {

public:

    static bool parseArguments(int argc, char* argv[]);
    static void showHelp(const po::options_description& desc, const std::string& topic = "");

    static string instancePath;
    static string method;

    static int repeat;
    static double alpha;
    static long seed;

    static bool printProgress;

};

#endif //JOBSHOPSCHEDULING_CONFIG_HPP
