/**
* Pied Piper Calculator was implemented in a small team withtin the ISV course at Brno University of Technology
* @mainpage PP Calculator
* @image html ../../screenshot.png Basic mode
* @image latex ../../screenshot_pro.png PRO mode
* There are two modes of working. Basic mode provides you with basic arithmetic operations, factorial, modulo and power. With PRO mode you can handle
* more complicated calculations. You will be able to see the progress of calculations, use trigonometric functions and brackets.
* The calculator has a minimalistic design in blue hues that will be pleasant to the eye.
* There is a special button that allows you to switch between these two modes.
* @image html ../../screenshot_pro.png PRO mode
* @image latex ../../screenshot_pro.png PRO mode
* @author Mihola David
* @author Foltyn Lukas
* @author Sokolovskii Vladislav
* @copyright ©Pied Piper
*/
/**
 * This source file contains initialization of GUI of the calculator (based on the GTK tool kit), function for switching between two modes and function
 * for sending the on-click signals. Also, there is a CSS section where the styles and fonts of the calculator are set.
 * @file graphics.cpp
 * @author Sokolovskii Vladislav
 * @author Mihola David
 * @copyright ©Pied Piper
 * @brief Initializes graphics and its API, connects it to the grap.glade file and sets the styles for the calculator.
 */

#include "../include/graphics.h"

//inicialization of static variables
GtkWidget *GUI::window = NULL;
GtkWidget *GUI::fixed = NULL;
GtkWidget *GUI::calculator = NULL;
GtkWidget *GUI::view = NULL;
GtkWidget *GUI::help = NULL;
GtkWidget *GUI::quit = NULL;
GtkWidget *GUI::pro_mode = NULL;
GtkWidget *GUI::basic_mode = NULL;
GtkWidget *GUI::main_menu = NULL;
GtkWidget *GUI::advanced_menu = NULL;
GtkWidget *GUI::button[NUM_OF_BUTTONS] = {0,};
GtkWidget *GUI::label = NULL;
GtkWidget *GUI::label_advanced = NULL;
GtkWidget *GUI::mode = NULL;
GtkBuilder *GUI::builder = NULL;
GtkWidget *GUI::switcher_button = NULL;
GdkScreen *GUI::screen = NULL;
GtkCssProvider *GUI::provider = NULL;
GdkDisplay *GUI::display = NULL;

Logic GUI::logic;


//the indexes of a certain button
int GUI::index_arr[NUM_OF_BUTTONS] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
                                      15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26};
//the IDs of a certain buttons
char const *GUI::button_names[NUM_OF_BUTTONS]  = {"button0", "button1", "button2", "button3", "button4", "button5",
                                                  "button6", "button7", "button8", "button9", "add_button", "subb_button",
                                                  "mul_button", "div_button", "mod_button", "sign_button", "clear_button",
                                                  "comma_button", "equal_button", "fact_button", "pow_button",
                                                  "OB_button", "CB_button", "bck_button", "sin_button", "cos_button", "tan_button"};
//the value of a certain button
char GUI::button_text[NUM_OF_BUTTONS] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '-', '*', '/',
                                               '%', 'N', 'C', '.', '=', '!', '^', '(', ')', 'D', 's', 'c', 't'};
std::string GUI::label_text;
std::string GUI::label_text_advanced;
bool GUI::graphics_mode;
//end of inicialization

int GUI::init_graphics(int argc, char **argv)
{
    //initiates GTK
    gtk_init(&argc, &argv);

    //caling builder, which will toad graphics data from specified file
    //TODO expetions 
    //checking the location of the file contaning graphic layout
    if (access("/usr/local/bin/grap.glade", F_OK ) == 0)
    {
	//for installed version    
        builder = gtk_builder_new_from_file("/usr/local/bin/grap.glade");
    }
    else if (access("grap.glade", F_OK ) == 0)
    {
	//for version running prom the source directory    
        builder = gtk_builder_new_from_file("grap.glade");
    }	    
    else
    {
	//when the graphic file could not be locate    
        std::cerr << "Graphics initialization failed" << std::endl;
        std::cerr << "File with graphic layout coul not be located" << std::endl;
        return 1;
    }

    //inicialization of the main window
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    //inicialization of other parts of the graphics
    pro_mode = GTK_WIDGET(gtk_builder_get_object(builder, "pro_mode"));
    basic_mode = GTK_WIDGET(gtk_builder_get_object(builder, "basic_mode"));
    help = GTK_WIDGET(gtk_builder_get_object(builder, "help"));
    view = GTK_WIDGET(gtk_builder_get_object(builder, "view"));
    calculator = GTK_WIDGET(gtk_builder_get_object(builder, "calculator"));
    quit = GTK_WIDGET(gtk_builder_get_object(builder, "quit"));
    fixed = GTK_WIDGET(gtk_builder_get_object(builder, "fixed"));
    main_menu = GTK_WIDGET(gtk_builder_get_object(builder, "main_menu"));
    advanced_menu = GTK_WIDGET(gtk_builder_get_object(builder, "advanced_menu"));
    label = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
    label_advanced = GTK_WIDGET(gtk_builder_get_object(builder, "label3"));
    mode = GTK_WIDGET(gtk_builder_get_object(builder, "label2"));
    switcher_button = GTK_WIDGET(gtk_builder_get_object(builder, "switcher_button"));

    if (window == NULL || main_menu == NULL || advanced_menu == NULL  || label == NULL || basic_mode == NULL || view == NULL ||
        label_advanced == NULL || mode == NULL || switcher_button == NULL || pro_mode == NULL || calculator == NULL || 
        quit == NULL || help == NULL || fixed == NULL || switcher_button == NULL )
    {
        std::cerr << "Graphics initialization failed\n" << std::endl;
        return 1;
    }

    //add signal to close the app when the X button on the top of the window is pressed
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(quit, "activate", G_CALLBACK(gtk_main_quit), NULL);
    
    //signal for the switcher when it is turned on/off
    
    g_signal_connect(GTK_WIDGET (switcher_button), "clicked", G_CALLBACK (on_switch_state_set), NULL);
    
    g_signal_connect(GTK_WIDGET (help), "activate", G_CALLBACK(on_help_active), NULL);
    
    g_signal_connect(GTK_WIDGET (pro_mode), "activate", G_CALLBACK(on_pro_mode_active), NULL);
    
    g_signal_connect(GTK_WIDGET (basic_mode), "activate", G_CALLBACK(on_basic_mode_active), NULL);
    
    for (int i = 0; i < NUM_OF_BUTTONS; i++)
    {
        //inicialization of all the buttons (appart from advanced and basic)
        button[i] = GTK_WIDGET(gtk_builder_get_object(builder, button_names[i]));
        if (button[i] == NULL)
        {
            std::cerr << "Graphics initialization failed\n" << std::endl;
            return 1;
        }
        
        //signal for each button when pressed
        //passing data with poineter to the index_arr
        g_signal_connect(button[i], "clicked", G_CALLBACK(on_button_clicked), &index_arr[i]);
        //naming all the buttons for css styling
        gtk_widget_set_name(button[i], button_names[i]);
    }
    //advanced menu is hidden by default
    gtk_widget_hide(advanced_menu);

//------------------------------------------------------- CSS styles -------------------------------------------------------//
    display = gdk_display_get_default();
    if (display == NULL)
    {
        std::cerr << "Graphics initialization failed\n" << std::endl;
        return 1;
    }
    screen = gdk_display_get_default_screen (display);
    provider = gtk_css_provider_new ();
    if (screen == NULL || provider == NULL)
    {
        std::cerr << "Graphics initialization failed\n" << std::endl;
        return 1;
    }
    
    gtk_widget_set_name(view, "view");
    gtk_widget_set_name(help, "help");
    gtk_widget_set_name(calculator, "calculator");
    gtk_widget_set_name(mode, "mode");
    gtk_widget_set_name(switcher_button, "switcher");
    //css styling of all the widgets and text
    gtk_css_provider_load_from_data(GTK_CSS_PROVIDER(provider), "#button0, #button1, #button2, #button3, #button4,\
                                     #button5, #button6, #button7, #button8, #button9, #comma_button{\
                                     background: #E5E4E2; color:black; font-family: Helvetica Neue; font-size: 18px; font-weight: 200;\
                                     }\
                                     #equal_button, #add_button, #subb_button, #mul_button, #fact_button, #pow_button, #sign_button, \
                                     #div_button, #mod_button {background: #7494b8; color: white; font-family: Helvetica Neue; font-size: 18px; font-weight: 300;\
                                     }\
                                     #OB_button, #CB_button, #bck_button, #clear_button, \
                                     #sin_button, #cos_button, #tan_button{\
                                     background: #8394A1; color: #ffffff; font-family: Helvetica Neue; font-size: 18px; font-weight: 200;\
                                     }\
                                     #switcher{\
                                     font-family: Helvetica Neue;\
                                     background: #083A4A;\
                                     color: #ffffff;\
                                     }\
                                     #calculator, #view, #help{\
                                     font-family: Helvetica Neue;\
                                     font-weight: 400;\
                                     }\
                                     ", -1 , NULL);
    
    gtk_style_context_add_provider_for_screen (screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
//-------------------------------------------------------------------------------------------------------------------------//
    
    //windows shows on the screen
    gtk_widget_show(window);
    //program is held here waiting for new actions (user input)
    gtk_main();
    
    return 0;
}

//switchnig to the pro mode if needed
void GUI::on_pro_mode_active()
{
    if(graphics_mode)
        return;

    on_switch_state_set();
}

//switching to the basic mode if needed
void GUI::on_basic_mode_active()
{
    if(!graphics_mode)
        return;
  
    on_switch_state_set();
}

//starts new window with the help message
void GUI::on_help_active()
{
    GtkWidget *p_window;
    GtkWidget *p_v_box;
    GtkWidget *helpmsg;

    p_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(p_window), "Help");
    gtk_window_set_default_size(GTK_WINDOW(p_window), 320, 150);
    
    g_signal_connect(p_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    p_v_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(p_window), p_v_box);

    //help message
    helpmsg = gtk_label_new("\n\n"
                            "\t\tPied Piper Calculator can operte in two separate modes.\n" 
                            "\t\tBasic mode, which provides basic arithmetic operation,\n"
                            "\t\tand PRO mode, which enables you to see the the development of\n"
                            "\t\ta calculation in real time. It also offers additional functionality\t\n" 
                            "\t\tsuch as calculations with brackets and gonimetric functions.\n\n"
                            "\t\tTo switch between the two modes you can either use the\n"
                            "\t\tdark-blue button 'PRO/Basic mode' or you can navigate to\n"
                            "\t\tthe top menu bar and use the section View to chagne the mode\n"
                            "\t\tthere. Note, that any change in modes will reset the ongoing\n"
                            "\t\tcalculation.\n\n"
                            "\t\tTo calculate the result in Basic mode or to get the current result\t\t\n"
                            "\t\tin PRO mode use the '=' button. To reset the ongoing calculation\n"
                            "\t\tuse the 'C' button. And to delete the last character of the\n"
                            "\t\tcalculation use the backspace button. The 'x^y' button can be\n"
                            "\t\talso used as a root function, when the absolute value of 'y' is\n"
                            "\t\tbetween 0 and 1. Other buttons have expected functionalites as\t\t\n"
                            "\t\ttheir labels describes.\n"
                            "\n\n");
                            
    gtk_box_pack_start(GTK_BOX(p_v_box), helpmsg, TRUE, FALSE, 0);
    gtk_widget_show_all(p_window);
    gtk_main();
}


//window is resized and new widgets are added when switcher is active
void GUI::on_switch_state_set()
{
    if (!graphics_mode){
        gtk_label_set_text(GTK_LABEL(mode), "Basic\nmode");
        gtk_fixed_move(GTK_FIXED(fixed), main_menu, 0, 175);
        gtk_widget_show_all(advanced_menu);
        
        graphics_mode = true;
    }else{
        gtk_label_set_text(GTK_LABEL(mode), "PRO\nmode");
        gtk_fixed_move(GTK_FIXED(fixed), main_menu, 0, 100);
        gtk_widget_hide(advanced_menu);
        
        graphics_mode = false;
    }

    logic.real_time_calculation('C', label_text, label_text_advanced);
    logic.erase_equation();
    label_text_advanced.push_back('0');
    gtk_label_set_text(GTK_LABEL(label), label_text.c_str());
    gtk_label_set_text(GTK_LABEL(label_advanced), label_text_advanced.c_str());
} 

void GUI::on_button_clicked(GtkButton *button, gpointer data)
{
    int index = *(int *)data;

    if (graphics_mode) //for the advanced mode
    {   
        logic.real_time_calculation(button_text[index], label_text, label_text_advanced);

        gtk_label_set_text(GTK_LABEL(label), label_text.c_str());
        gtk_label_set_text(GTK_LABEL(label_advanced), label_text_advanced.c_str());

    }
    else // for the basic mode
    {
        if (button_text[index] == 'C')
        {
            logic.reset_equation_string_control();
            label_text.clear();

            label_text.push_back('0');
            gtk_label_set_text(GTK_LABEL(label), label_text.c_str());

            logic.erase_equation();
        }
        else if (button_text[index] != '=')
        {
            //adding the character to the string, that is going to be diplayed in the window
            logic.equation_string_control(label_text, button_text[index]);

            //displaying the changed text on the label
            gtk_label_set_text(GTK_LABEL(label), label_text.c_str());
        }
        else
        {
            try
            {
                logic.calculate(label_text, label_text);
                gtk_label_set_text(GTK_LABEL(label), label_text.c_str());
            }
            catch(const std::runtime_error &e)
            {
                gtk_label_set_text(GTK_LABEL(label), e.what());
                logic.erase_equation();
            }
            

            //prepares variables for next calculation
            logic.reset_equation_string_control();
        }
    }

    (void)button; //dummy for the compiler
}
