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

void help_menu(){

    std::cout << "NAME" << std::endl;
    std::cout << "        meshinfo - print boundary info and convert type of mesh." << std::endl;
    std::cout << " " << std::endl;


    std::cout << "SYNOPSIS " << std::endl;
    std::cout << "         ./meshinfo -i [input file name]" << std::endl;
    std::cout << "         ./meshinfo -o [otuput file name]" << std::endl;
    std::cout << "         ./meshinfo -d [dim]" << std::endl;
    std::cout << " " << std::endl;

    std::cout << "DESCRIPTION " << std::endl;
    std::cout << "          meshinfo is a script that can read a mesh, print" << std::endl;
    std::cout << "          mesh information and convert output type of a mesh." << std::endl;
    std::cout << "          The boundary info will be stored into a file called " << std::endl;
    std::cout << "          bound.vtu." << std::endl;
    std::cout << " " << std::endl;

    std::cout << "OPTIONS " << std::endl;
    std::cout << "          -i [input file name]" << std::endl;
    std::cout << "                    reading a file from command line, make sure" << std::endl;
    std::cout << "                    that file is in the same folder with the script" << std::endl;
    std::cout << "          -o [output file name]" << std::endl;
    std::cout << "                    this is the file you will find after running this script."<< std::endl;
    std::cout << "                    make sure the extension of the file is written as well, for" << std::endl;
    std::cout << "                    example, write a.msh if you wish to have a msh as output format." << std::endl;
    std::cout << "          -d [dim]" << std::endl;
    std::cout << "                    if your input mesh is 2d then dim = 2 otherwise put 3" << std::endl;
    std::cout << "                    the default dimension is 2." << std::endl;

}

template<int dim>
Triangulation<dim> reading_file(const std::string& input_file){

  //initialize tria
  Triangulation<dim> triangulation;

  //find out file type
  int pos_dot = input_file.find(".");
  std::string input_file_type = input_file.substr(pos_dot+1, input_file.length()-1);
  std::cout << "===========================================" << std::endl;
  std::cout << "input file type is " << input_file_type << std::endl;


  //read file
  GridIn<dim> gridin;
  gridin.attach_triangulation(triangulation);
  std::ifstream f(input_file);
  typename GridIn<dim>::Format reading_type = GridIn<dim>::parse_format(input_file_type);
  gridin.read(f, reading_type);


  std::cout << "===========================================" << std::endl;
  std::cout << " input file complete." << std::endl;
  return triangulation;

}


//Timo's Code.
template<int dim>
void output_boundary_info(Triangulation<dim> &triangulation, const std::string boundary_info_file){

  std::ofstream out(boundary_info_file);
  GridOut gridout;
  GridOutFlags::Vtk flags;
  flags.output_cells = false;
  flags.output_only_relevant = false;
  gridout.set_flags(flags);
  gridout.write_vtk(triangulation, out);

  std::cout << "===========================================" << std::endl;
  std::cout << "Boundary info stored in" << boundary_info_file << std::endl;

  //for more types.

}


template<int dim>
void writing_file(Triangulation<dim> &triangulation, const std::string output_file){

   //output type.
   int pos_dot = output_file.find(".");
   std::string output_file_type = output_file.substr(pos_dot+1, output_file.length()-1);
   std::cout << "===========================================" << std::endl;
   std::cout << "Output file type is " << output_file_type << std::endl;

   //output file
   std::ofstream out(output_file);
   GridOut       grid_out;
   typename GridIn<dim>::Format writing_type = GridIn<dim>::parse_format(output_file_type);
   grid_out.write(triangulation, out);


   std::cout << "===========================================" << std::endl;
   std::cout << " input file complete." << std::endl;

}




int main(int argc, char *argv[]){

  bool input_flag = false;
  bool output_flag = false;
  bool dim_flag = false;
  // print bound is default, so it will always print

  int dim = 2;

  std::string boundary_info_file = "bound.vtk";
  std::string input_file = " ";
  std::string output_file = " ";

  Triangulation<2> tria2;
  Triangulation<3> tria3;


  int i = 1;
  while(i < argc){

    std::string arg = argv[i];
    ++i;

    if (arg.compare(0,1,"-") == 0){

      if (arg == "-o"){
        output_flag = true;
        output_file = argv[i];
        std::cout << "===========================================" << std::endl;
        std::cout << "output file name is " << output_file << std::endl;
        ++i;
      } else if (arg == "-i") {
        input_flag = true;
        input_file = argv[i];
        std::cout << "===========================================" << std::endl;
        std::cout << "input file name is " << input_file << std::endl;
        ++i;
      } else if (arg == "-d"){
        dim_flag = true;
        dim = atoi(argv[i]);
        std::cout << "===========================================" << std::endl;
        std::cout << "The input dimension is: " << dim << std::endl;
        ++i;
      } else {
        help_menu();
      }

    }

  }

  switch (dim){

    case 2:

        if (input_flag){
          Triangulation<2> tria2 = reading_file<2>(input_file);
          output_boundary_info<2>(tria2, boundary_info_file);
        }

        if (output_flag){
          writing_file<2>(tria2, output_file);
        }

    case 3:

        if (input_flag){
          Triangulation<3> tria3 = reading_file<3>(input_file);
          output_boundary_info<3>(tria3, boundary_info_file);
        }

        if (output_flag){
          writing_file<3>(tria3, output_file);
        }


  }

}
