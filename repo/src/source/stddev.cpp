/**
 * @file stddev.cpp
 * @author Foltyn Lukas
 * @author Mihola David
 * @copyright ©Pied Piper
 * @brief Source file, which serves for calculating sample standard deviation
 * with help of functions from math library
*/
#include "../include/logic.h"

int main()
{
    Stddev_function sample_std_deviation; // initialization with constructor
    if(sample_std_deviation.get_data_pointer() != NULL) // testing if allocation in constructor did not fail
    {
        if(sample_std_deviation.load_function() != -1) // loading data from user given file and testing for error
            std::cout << sample_std_deviation.calculate_stddev() << std::endl; 
        else
            std::cerr << "stddev: Loading of data failed." << std::endl;
    }
    else
        std::cerr << "stddev: Allocation of initial memory failed." << std::endl;
        
    return 0;
}
