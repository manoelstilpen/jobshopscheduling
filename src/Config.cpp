//
// Created by manoel on 26/03/18.
//

#include <Config.hpp>

string Config::instancePath = "../instances/bierwirth.txt";
string Config::method = "grasp";

int Config::repeat = 1;
double Config::alpha = 0.40f;
long Config::seed = time(NULL);

bool Config::printProgress = false;

bool Config::parseArguments(int argc, char* argv[]){
    po::options_description desc("Usage");
    desc.add_options()

            ("help,h", po::value< std::string >()->implicit_value("")->notifier(
                    [&desc](const std::string& topic) {
                        showHelp(desc, topic);
                    }
            ),"Show help.")
            ("instance,i", po::value<string>(), "Instance path")
            ("alpha,a", po::value<double>()->default_value(Config::alpha))
            ("method,m", po::value<string>()->default_value("grasp"), "(Optional) Specify the constructive method to use")
            ("repeat,r", po::value<int>()->default_value(1), "(Optional) Specify how many times run the program")
            ("progress,p", "(Optional) If enabled program will print execution bar");

    if (argc == 1) {
        showHelp(desc);
        return false;
    }

    po::variables_map args;

    try {
        po::store(po::parse_command_line(argc, argv, desc), args);
    } catch (po::error const& e) {
        std::cerr << e.what() << '\n';
        return false;
    }
    po::notify(args);

    Config::method = args["method"].as<string>();

    if(args.count("repeat")){
        Config::repeat = args["repeat"].as<int>();
    }

    if(args.count("alpha")){
        Config::alpha = args["alpha"].as<double>();
    }

    if(args.count("print")){
        //*print = true;
    }

    if(args.count("progress")){
        Config::printProgress = true;
    }

    if(args.count("instance")){
        Config::instancePath = args["instance"].as<string>();
    } else {
        cerr << "Instance parameter is required" << endl << endl;
        showHelp(desc);
        return false;
    }

    return true;
}

void Config::showHelp(const po::options_description& desc, const std::string& topic ){
    std::cout << desc << '\n';
    if (topic != "") {
        std::cout << "You asked for help on: " << topic << '\n';
    }
    exit(EXIT_SUCCESS);
}

