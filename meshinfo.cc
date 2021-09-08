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

int main(int argc, char *argv[]){

  int i = 1;

  while(i < argc){

    std::string arg = argv[i];
    ++i;

    if (arg.compare(0,1,"-") == 0){

//	std::cout << arg.at(1) << std::endl;

      if (arg == "-h") {

        help_menu();

      } else if (arg == "-o"){

	std::string output_file = argv[i];

	int pos_dot = output_file.find(".");

	std::string output_file_type = output_file.substr(pos_dot+1, output_file.length()-1);

	std::cout << "input file type is: " << output_file_type << std::endl;

	++i;

      } else if (arg == "-i") {

	std::string input_file = argv[i];

	int pos_dot = input_file.find(".");

	std::string input_file_type = input_file.substr(pos_dot+1, input_file.length()-1);

	std::cout << "input file type is: " << input_file_type << std::endl;

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

template <int dim>
void print_mesh_info(const Triangulation<dim> &triangulation,
                     const std::string &       filename)
{
  std::cout << "Mesh info:" << std::endl
            << " dimension: " << dim << std::endl
            << " no. of cells: " << triangulation.n_active_cells() << std::endl;
  {
    std::map<types::boundary_id, unsigned int> boundary_count;
    for (const auto &face : triangulation.active_face_iterators())
      if (face->at_boundary())
        boundary_count[face->boundary_id()]++;
    std::cout << " boundary indicators: ";
    for (const std::pair<const types::boundary_id, unsigned int> &pair :
         boundary_count)
      {
        std::cout << pair.first << "(" << pair.second << " times) ";
      }
    std::cout << std::endl;
  }
  std::ofstream out(filename);
  GridOut       grid_out;
  grid_out.write_vtu(triangulation, out);
  std::cout << " written to " << filename << std::endl << std::endl;
}
