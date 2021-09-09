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


  std::cout <<"Usage:     ./meshinfo <arg1> <arg2>" << std::endl;
  std::cout <<"           ./meshinfo <arg>" << std::endl;

  std::cout <<"Options: " << std::endl;

  std::cout << "                      -i   <filename>  Input file." << std::endl;
  std::cout << "                      -o   <filename>  Output file." << std::endl;
  std::cout << "                      -id  <dim>       Expected input dimension.  " << std::endl;
  std::cout << "                      -od  <dim>       Expected output dimension. " << std::endl;
  std::cout << "                      -r   <refine#>   How many refine times are expected." << std::endl;
  std::cout << "                      -b               Extract boundary and output boundary ID" << std::endl;

  
  std::cout << "\n " << std::endl;
  std::cout <<"When entering output file, make sure you enter the entire file name. \n" << 
              "Like 'example.vtu' instead of 'example' or 'vtu', this way the nameing \n" <<
              "of the output file is user defined so that it won't bother other files in the folder.\n" << std::endl;
  std::cout << "\n" << std::endl;
  std::cout << "dimension is by default, 2." << std::endl;

}


template <int dim>
Triangulation<dim> reading_file(const std::string & input_file)
{

  const Triangulation<dim> &triangulation;

  int pos_dot = input_file.find(".");

  std::string input_file_type = input_file.substr(pos_dot+1, input_file.length()-1);
  
  std::cout << "input file type is " << input_file_type << std::endl;

  GridIn<dim> gridin;

  gridin.attach_triangulation(triangulation);

  std::ifstream f(input_file);

  if (input_file_type.compare("vtu")){

    gridin.read_vtu(f);

  } else if (input_file_type.compare("msh"))

  {
   
    gridin.read_msh(f);

  }

  return triangulation;

}



template <int dim>
void writing_file(const Triangulation<dim> &triangulation,const std::string & output_file)
{

  int pos_dot = output_file.find(".");

  std::string output_file_type = output_file.substr(pos_dot+1, output_file.length()-1);
  
  std::cout << "Output file type is " << output_file_type << std::endl;

  std::ofstream out(output_file);
  GridOut       grid_out;
  
  if (output_file_type.compare("vtu")){

    grid_out.write_vtu(triangulation, out);

  } else if (output_file_type.compare("msh"))

  {

      grid_out.write_msh(triangulation, out);
      
  }
  
}



void refine_grid(int refine_times){
    
    
    
}

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
























//main!



int main(int argc, char *argv[]){
    
  bool input_flag = false;
  bool out_dim_flag = false;
  bool in_dim_flag = false;
  bool output_flag = false;
  bool bound_flag = false;
  bool fine_flag = false;
  
  int dimension = 2;
  int refine_times = 1;

  int i = 1;

  while(i < argc){

    std::string arg = argv[i];
    ++i;

    if (arg.compare(0,1,"-") == 0){

      if (arg == "-h") {

        help_menu();

      } else if (arg == "-o"){
          
        output_flag = true;

        std::string output_file = argv[i];

        ++i;

      } else if (arg == "-i") {
          
        input_flag = true;
        
        std::string input_file = argv[i];
        
        ++i;

      } else if (arg == "-id"){

        in_dim_flag = true;
        
        const int in_dim = atoi(argv[i]);
        
        ++i;
        
        std::cout << "The dimension of input file is: " << in_dim << std::endl;

      } else if (arg == "-od"){

        out_dim_flag = true;
        
        const int out_dim = atoi(argv[i]);
        
        ++i;
        
        std::cout << "The dimension of output file is: " << out_dim << std::endl;

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
  
  
  //If you don't read then you don't write.
  
  if (input_flag){
      
      switch(in_dim){
          
          case 2:
              
          case 3:
              
      }
      
      //Other operations will be plugged in this section. like refine and boundary output.
      
  
      if (output_flag){
      
          switch(out_dim){
              
              case 2:
                  
              case 3:
              
          }
          
      
    }
  
  } 
  

 

  return EXIT_SUCCESS;

}
