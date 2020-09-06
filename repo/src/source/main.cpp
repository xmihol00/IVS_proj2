/**
 * @file main.cpp
 * @author Mihola David
 * @author Sokolovskii Vladislav
 * @date 27.02.2019
 * @copyright ©Pied Piper
 * @brief Main function of the calculator, which just runs the graphics library.
 */
#include "../include/graphics.h"
#include <gtk/gtk.h>

/**
 * @brief the main function of the calculator
 */ 
int main(int argc, char **argv)
{

    GUI::init_graphics(argc, argv);

    return 0;
}
