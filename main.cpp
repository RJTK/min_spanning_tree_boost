#include "minimum_spanning_tree.hpp"
#include <iostream>
#include <stdexcept>

int main(int argc, char* argv[]);
void print_file_format_info(void);

int main(int argc, char* argv[]){
    if(argc != 2){
	std::cout <<"Usage: " <<argv[0] <<" <path to graph file>." << std::endl;
	return -1;
    }

    try{
	std::cout<<"MST Value: " <<minimum_spanning_tree::mst_value(
	    std::string{argv[1]}) <<std::endl;
    }
    catch (minimum_spanning_tree::bad_file_format){
	print_file_format_info();
	return -1;
    }
    catch (minimum_spanning_tree::file_not_found){
	std::cout <<"Can't find file " << std::string{argv[1]} <<std::endl;
	return -1;
    }
    catch (std::exception){
	std::cout <<"Caught unexpected exception, exiting..." <<std::endl;
	return -1;
    }
    return 0;
}

void print_file_format_info(void){
    std::cout <<"Caught bad_file_format error."  <<std::endl;
    std::cout <<"Graph input format should be given as: " <<std::endl;
    std::cout <<"num_nodes num_edges" <<std::endl;
    std::cout <<"v1 u1 w1" <<std::endl;
    std::cout <<"v2 u2 w2" <<std::endl;
    std::cout <<"......." <<std::endl;
    std::cout <<"Where v and u are ints (vertices) and w "
	"is a float (weight)" <<std::endl;
    return;
}
