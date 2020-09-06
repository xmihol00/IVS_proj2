/**
 * This header file contains declaration of main graphics class and all the widgets (buttons, labels)
 * @file graphics.h
 * @author Mihola David
 * @author Sokolovskii Vladislav
 * @date 27.02.2019
 * @copyright ©Pied Piper
 * @brief Header file consisting declarations of the graphics user interface functions and variables
*/

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <gtk/gtk.h>
#include <unistd.h>
#include "logic.h"

/**
 * @def NUM_OF_BUTTONS
 * @brief the number of used buttons on the calculator (appart from the state switch button) 
 */ 
#define NUM_OF_BUTTONS 27 /**< Number of all the buttons*/

/**
 @class GUI
 @brief This class includes all the widgets and functions that are needed for initialization of graphics.
 */
class GUI
{
    protected:
        //parts of the GUI
        static GtkWidget *window;   /**<Main window widget*/
        static GtkWidget *fixed;    /**<Main grid of the app*/
        static GtkWidget *main_menu;/**<Container with basic functions*/
        static GtkWidget *advanced_menu;         /**<Container with advanced functions*/
        static GtkWidget *button[NUM_OF_BUTTONS];
        static GtkWidget *label;    /**<Main label for displaying the result*/
        static GtkWidget *label_advanced;        /**<Advanced label for displaying the steps of the calculation process*/
        static GtkWidget *mode;     /**<Name of the current mode*/
        static GtkBuilder *builder; /**<Widget for connecting to the grape.glade file*/
        static GtkWidget *switcher_button;       /**<Button for switching between modes*/
        static GdkScreen *screen;                /**<Widget for setting the CSS styles*/
        static GtkCssProvider *provider;         /**<Widget for setting the CSS styles*/
        static GdkDisplay *display;              /**<Widget for setting the CSS styles*/
        static GtkWidget *calculator;            /**<Calculator menu button*/   
        static GtkWidget *view;                  /**<top menu bar*/
        static GtkWidget *quit;                  /**<Calculator quit option in menu*/   
        static GtkWidget *help;                  /**<Help menu button*/
        static GtkWidget *basic_mode;            /**<Basic mode option in menu*/
        static GtkWidget *pro_mode;              /**<PRO mode option in menu*/
        
        static Logic logic;                      /**<Object of the calculation*/
        static int index_arr[NUM_OF_BUTTONS];    /**< Array the assigned button numbers*/
        static const char *button_names[NUM_OF_BUTTONS];/**<IDs of all buttons declared in the grap.glade file*/
        static char button_text[NUM_OF_BUTTONS];        /**<One char values of every button*/
        static std::string label_text;           /**< text to be leaded to the claculator main dispaly */
        static std::string label_text_advanced;  /**< text to be leaded to the claculator advanced dispaly */
        static bool graphics_mode;               /**< true for PRO mode, false for Basic mode*/   

        /**
         * @brief This function is responsible for switching to the basic mode after choosing the option in the menu bar
         * View –> Basic mode. Checks graphics_mode variable and switch the mode if it is needed, otherwise does nothing.
         */
        static void on_basic_mode_active();
        /**
         *  @brief This function is responsible for switching to the PRO mode after choosing the option in the menu bar
         * View –> Professional mode. Checks graphics_mode variable and switch the mode if it is needed, otherwise does nothing.
        */
        static void on_pro_mode_active();
    
    /**
     * @brief This function open the separate window with help message if the user chose option in the menu bar Help.
     *  Starts separate gtk_main_loop. 
     */
        static void on_help_active();
        /** 
         * @brief This function reacts to a buttons clicks, in both modes.
         * @param button Pointer to the button that was clicked.
         * @param data Void pointer to a data sent to the function with each button click.
         */
        static void on_button_clicked(GtkButton *button, gpointer data);

        /**
        @brief This function resizes the window, moves container with the basic buttons and makes the advanced functions visible.
        * When gets a callback from the switcher button switch the mode – moves container with basic buttons and makes
        * advanced menu visible/invisible. Also, switching from basic to PRO mode sets graphics_mode variable to true (necessary for connecting to logic).
        */
        static void on_switch_state_set();

    public:
       /**
        @brief This functions starts the main loop of the window, connects the graphics to the grap.glade file, handles callbacks and sets the CSS styles for the calculator. Basically the main GUI function.
        * Retrieves all the information about eh widgets from the frab.glade file (builder), checks validity of the widgets and initialized all buttons. Handles the callbacks of buttons and 'window destoyer'.
        * In CSS sections sets fonts and colors for all widgets.
        @param[in] argc Number of arguments from the comand line.
        @param[in] argv Vector of given arguments.
        @return Returns zero value if work of the window was finihed successfully, otherwise returns non-zero value.
        */
        static int init_graphics(int argc, char **argv);
};

#endif //__GRAPHICS_H__
