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


template<int dim>
void bound_func(const Triangulation<dim> &triangulation){
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

}


void help_menu(){


  std::cout <<"Usage:     ./meshinfo <arg1> <arg2>" << std::endl;
  std::cout <<"           ./meshinfo <arg>" << std::endl;

  std::cout <<"Options: " << std::endl;

  std::cout << "                      -i   <filename>  Input file." << std::endl;
  std::cout << "                      -o   <filename>  Output file." << std::endl;
  std::cout << "                      -id  <dim>       Expected input dimension. (not ready yet)  " << std::endl;
  std::cout << "                      -od  <dim>       Expected output dimension. (not ready yet)" << std::endl;
  std::cout << "                      -r   <refine#>   How many refine times are expected. (not ready yet)" << std::endl;
  std::cout << "                      -b               Extract boundary and output boundary ID. (not ready yet)" << std::endl;


  std::cout << "\n " << std::endl;
  std::cout <<"When entering output file, make sure you enter the entire file name. \n" <<
              "Like 'example.vtu' instead of 'example' or 'vtu', this way the nameing \n" <<
              "of the output file is user defined so that it won't bother other files in the folder.\n" << std::endl;
  std::cout << "\n" << std::endl;

}


void convert_type(const std::string output_file, const std::string input_file, bool print_bound){

  Triangulation<2> triangulation;

  int pos_dot = input_file.find(".");

  std::string input_file_type = input_file.substr(pos_dot+1, input_file.length()-1);

  std::cout << "input file type is " << input_file_type << std::endl;

  GridIn<2> gridin;

  if (input_file_type.compare("vtu") == 0){

    std::ifstream f(input_file);

    gridin.read_vtu(f);

    //keeping this error here intionally, so I don't to write the error myself
    //:P

  } else if (input_file_type.compare("msh") == 0)

  {

    gridin.attach_triangulation(triangulation);

    std::ifstream f(input_file);

    gridin.read_msh(f);

  }

  if (print_bound){

    bound_func(triangulation);

  }

  pos_dot = output_file.find(".");

  std::string output_file_type = output_file.substr(pos_dot+1, output_file.length()-1);

  std::cout << "Output file type is " << output_file_type << std::endl;

  std::ofstream out(output_file);
  GridOut       grid_out;

  if (output_file_type.compare("vtu") == 0){

    grid_out.write_vtu(triangulation, out);

  } else if (output_file_type.compare("msh") == 0)

  {

    grid_out.write_msh(triangulation, out);

  }


}

int main(int argc, char *argv[]){

  bool input_flag = false;
  bool output_flag = false;
  bool bound_flag = false;
  bool fine_flag = false;

  std::string input_file = " ";
  std::string output_file = " ";
  int refine_times = 0;

  int i = 1;

  while(i < argc){

    std::string arg = argv[i];
    ++i;

    if (arg.compare(0,1,"-") == 0){

      if (arg == "-h") {

        help_menu();

      } else if (arg == "-o"){

        output_flag = true;

        output_file = argv[i];
        //std::cout << "output file name is " << output_file << std::endl;

        ++i;

      } else if (arg == "-i") {

        input_flag = true;

        input_file = argv[i];
        //std::cout << "input file name is " << input_file << std::endl;

        ++i;

      } else if (arg == "-r"){

        fine_flag = true;

        refine_times = atoi(argv[i]);

        ++i;

      } else if (arg == "-b"){

        bound_flag = true;

      } else {

        std::cout <<"invalid input, please check the help menu. " << std::endl;

        help_menu();

      }

    }

  }



  if (input_flag && output_flag && bound_flag){

      convert_type(output_file, input_file, true);
      std::cout << "file converted and saved." << std::endl;

  } else if (input_flag && output_flag && !bound_flag){

      convert_type(output_file, input_file, false);
      std::cout << "file converted and saved." << std::endl;

  } else {

      std::cout << "Not enough input argument, please check help menu." << std::endl;

      help_menu();

  }





  return EXIT_SUCCESS;

}
