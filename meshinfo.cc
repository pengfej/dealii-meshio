#include <deal.II/grid/tria.h>
#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/grid_tools.h>
#include <deal.II/grid/manifold_lib.h>
#include <deal.II/grid/grid_out.h>
#include <deal.II/grid/grid_in.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace dealii;

void help_menu();
void bound_func();
//void reading_file();
//void writing_file();


int main(int argc, char *argv[]){

  int i = 1;

  while(i < argc){

    std::string arg = argv[i];
    ++i;

    if (arg.compare(0,1,"-") == 0){

      if (arg == "-h") {

        help_menu();

      } else if (arg == "-o"){

	std::string output_file = argv[i];

	++i;

      } else if (arg == "-i") {

	std::string input_file = argv[i];

	++i;

      } else if (arg == "-d"){

	int dimension = atoi(argv[i]);
	++i;

      } else if (arg == "-r"){

	int refine_times = atoi(argv[i]);
	++i;

      } else if (arg == "-b"){

	bound_func();

      } else {

	std::cout <<"invalid input, please check the help menu. " << std::endl;

	help_menu();

      }

    }

  }

  return EXIT_SUCCESS;

}

void help_menu(){

  std::cout <<"Usage:     ./meshinfo <arg1> <arg2>" << std::endl;
  std::cout <<"           ./meshinfo <arg>" << std::endl;

  std::cout <<"Options: " << std::endl;

  std::cout << "                      -i   <filename>  Input file." << std::endl;
  std::cout << "                      -o   <filename>  Output file." << std::endl;
  std::cout << "                      -d   <dim>       Expected dimension.  " << std::endl;
  std::cout << "                      -r   <refine#>   How many refine times are expected." << std::endl;
  std::cout << "                      -b               Extract boundary and output boundary ID" << std::endl;

}

void bound_func(){



}


//should have used template for this function.
void reading_file(std::string input_type, std::string input_name, int dim){

};


void writing_file(std::string output_type, std::string output_name // and a triangulation.){

};
