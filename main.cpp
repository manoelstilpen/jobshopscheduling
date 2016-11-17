#include "Commons.hpp"
#include "ProblemInstance.hpp"

int main(){

	ProblemInstance instance;

	instance.set_name_file("abz5_f13.txt");
	instance.load_instance();
	instance.print();

}