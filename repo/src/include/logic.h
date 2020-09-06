/**
 *@file logic.h
 *@author Mihola David
 *@author Sokolovskii Vladislav
 *@author Foltyn Lukas
 *@date 27.02.2019
 *@copyright ©Pied Piper
 *@brief Header file consisting declarations of functions and variables that creates the 'brain' of the calculator
 */

#ifndef __LOGIC_H__
#define __LOGIC_H__

#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <functional>
#include <clocale>
#include <cmath>
#include <locale>

#include "our_math.h"

/**
 * @def BLOCK_SIZE
 * @brief the size of one block of allocated data 
 */ 
#define BLOCK_SIZE 20

/**
 * @def EPS
 * @brief the deviation of a correct result 
 */ 
#define EPS 1e-10

/**
 * @def IS_OPERATOR
 * @brief determines wheather the input character is an operator or not
 * @char_value the character to be checked
 */ 
#define IS_OPERATOR(char_value) (char_value == '+' || char_value == '-' || char_value == '*' || char_value == '/' ||\
                                 char_value == '^' || char_value == '?' || char_value == '!' || char_value == '%')

/**
 * @def IS_OPERATOR_NF
 * @brief determines wheather the input character is an operator or not, '!' is not considered as an operator
 * @char_value the character to be checked
 */ 
#define IS_OPERATOR_NF(char_value) (char_value == '+' || char_value == '-' || char_value == '*' || char_value == '/' ||\
                                 char_value == '^' || char_value == '?' || char_value == '%')
/**
 * @def IS_DIGIT
 * @brief determines wheather the input character is a digit or not
 * @char_value the character to be checked
 */ 
#define IS_DIGIT(char_value) (char_value >= '0' && char_value <= '9')

/**
 * @enum charcter_input_states
 * @brief enumeration used to determin different states in which the equation can appear 
 * 	  level 1 operators:      '+', '-'
 * 	  level 2 operators:      '*', '/', '%'
 * 	  level 3 operators:      '^', '?' - which represents the nroot operator
 * 	  goniometric operators:  's' - for sinus, 'c' - for cosinus, 't' - for tangens   
 */ 
enum character_input_states {
	                     UNDEFINED = 0 /**Undefined state, nothing happends */, 
	                     L1 /**Level 1 operator */, 
			     L2 /**Level 2 operator */, L3 /** Level 3 operator */, 
			     L1L2 /**Combination of level 1 operator followed by level 2 operator */, 
			     L1L3 /**Combination of level 1 operator followed by level 3 operator*/, 
			     L2L3 /**Combination of level 2 operator followed by level 3 operator */, 
			     L1L2L3 /**Combination of level 1, level 2 and level 3 operators followed respectivly*/, 
			     DIGIT /**Digit was entered (i.e. '0', ..., '9' characters) */, 
			     L1_GONIO /**Combination of level 1 operator followed by goniometric operator */, 
			     L2_GONIO /**Combination of level 2 operator followed by goniometric operator */, 
			     L3_GONIO /**Combination of level 3 operator followed by goniometric operator */, 
			     GONIO_NEGATE /**Goniometric operator with a negation in front */,
                             L1L2_GONIO /**Combination of level 1, level 2 and goniometric operators followed respectivly */, 
			     L1L3_GONIO /**Combination of level 1, level 3 and goniometric operators followed respectivly */, 
			     L2L3_GONIO /**Combination of level 2, level 3 and goniometric operators followed respectivly */, 
			     L1L2L3_GONIO /**Combination of level 1, level 2, level 3 and goniometric operators followed respectivly */, 
			     GONIO /**Goniometric operator on its own */, 
			     REDUCTION_BY3 /**Reduction of 3 operators in the operator stack @relates add_to_calculation @relates result_parts_state */, 
			     GONIO_ADDITION /**When goniometric function is added*/, 
			     RESET /**For reseting the equation @relates add_to_calculation */,
                             DECIMAL /**Digit was entered to a floating point number */, 
			     PROCCEDE /**Operator that does not change the operator arrangement, calculation is procceded */, 
			     START_STATE /**State, in which is the calculation, when it starts or a new bracket is open */, 
			     REDUCTION_BY1 /**Reduction of 1 operator in the operator stack @relates add_to_calculation @relates result_parts_state */, 
			     REDUCTION_BY2 /**Reduction of 2 operators in the operator stack @relates add_to_calculation @relates result_parts_state */, 
			     ADDITION /**New operator is added to the operator stack @relates add_to_calculation @relates result_parts_state */, 
			     NEGATE /**Input number negation is engaged (i.e. the number is negative) */, 
			     NEGATION /**'N' was added negation of a currently entered number is performed @relates currently_entered_num*/,
                             OPENED_BRACKET /**'(' character was added, new bracket is opened */, 
			     CLOSED_BRACKET /**')' character was added, currently opened bracket is closed */, 
			     EQUAL /**'=' character was added, result is calculated */, 
			     FACTORIAL /**'!' character was added to the equation, which invokes the calculation of factorial */, 
			     DECIMAL_DOT /**'.' charcter was added to the equation, which invokes, that floating point nuber is added*/, 
			     CLEAR /**'C' character was added, equation cleared and reseted */, 
			     GONIO_PROCCEDE /**Operator that does not change the operator arrangement added after the goniometric operator, calculation is procceded */
};

/**
 * @enum string_control
 * @brief enumeration used to determin different states in which the equation string can appear 
 */ 
enum string_control {
		     INTEGER /**Digit was entered (i.e. '0', ..., '9' characters) */, 
		     DECIMAL_NUM /**Digit was added (i.e. '0', ..., '9' characters) to a floating point */, 
		     OPERATOR /**Operator was added ('+', '-', '*', '/', '%', '^', '?') */, 
		     NO_STATE /**First enter to the function */, 
		     O_BRACKET /**'(' character was entered */, 
		     C_BRACKET /**')' character was enterd */, 
		     GONIOOMETRY /**Goniometric operator was entered ('s' - for sinus, 'c' - for cosinus, 't' - for tangens) */
};

/**
 *@class Logic
 *@brief class containing all declaration needed to calculate complex equations, on which either GUI can be added or can be run from the terminal    
 */ 
class Logic
{
    private:

        /**
	 * @var result
         * @brief Variable to hold the result of currently ongoing equation
         */
        long double result;
        /** 
	 * @var result_parts
         * @brief Array of intercount results, which have to be calculated in cerain order,
         * so the equation is correct. Works as a stack
         */
        std::vector<long double> result_parts;

        /** 
	 * @var resutlts_parts_op
         * @brief Array of operands between the intercount results. This array is used tightly together with
         * the std::vector<long double> result_parts;
         * @relates result_parts
         */
        std::vector<char> result_parts_op;

        /** 
	 * @var currently_entered_num 
         * @brief Variable, that holds the currently entered number to an equation
         */
        long double currently_entered_num;
        
        /**
	 * @var psition_ 
         * @brief Holds the current state of an automat in string control @relates equation_string_control
         */
        string_control position;
        
        /**
	 * @var decimal_position
         * @brief Holds the information about the decimal position of a currenty entered number @relates currently_entered_num
         */
        long double decimal_position;

        /**
	 * @var negate
         * @brief Holds the information whether a currently entered num is negative @relates currently_entered_num
         */
        bool negate;
        
        /**
	 * @var op_count_strcnt
         * @brief Holds the information about the number of added operators after a number. Used by equation string control
         * @relates equation_string_control
         */
        char op_count_strcnt;

        /**
	 * @var bracket_count
         * @brief Holds the number of currently opened brackets. Used by add to calculation @relates add_to_calculation
         */
        int bracket_count;
        
        /**
	 * @var result_parts_state
         * @brief holds the states of an ongoing equation. Gets pushed back after an addition on a open bracket and poped 
         * after an addition of clos bracket. Used by real time calculation @relates real_time_calculation.
         */
        std::vector<character_input_states> result_parts_state;

        /**
         * @brief This function calculates the final result of current equation from all of it's parts
         * uses @relates result_parts @relates result_parts_op @relates result
         * @param[in] iterration_reduction when set to 0 no reduction occures,
         * otherwise the number of iterations is reduced to the specified number 
         */
        void math_calculation(int iterration_reduction); 
       
        /** 
         * @brief This function adds the input character to an equation, so the equation can be calculated imidiatelly
         * @param[in] input_char newely added character to an equation, can be either digit or an operator,
         * others will be ignored
         * @param output_string variable where the final result converted from long double will be stored
         */
        void add_to_calculation(char input_char, char last_input);

        /**
         * @brief This function recalalculates the the ongoing equation from it's string after deletion
         * @param input_str string with an equation
         */
        void recalculate_after_delete(const std::string &input_str);

        /**
         * @brief This function decides which state has to be followed to add the new character to an equation
         * @param input_char Currently entered char
         * @param last Last characters in the equation
         * @return The state to be followed in the calculation
         */
        character_input_states get_state(char input_char, char last);
        
    public:
        
        /**
         * @brief Constructor
         */
        Logic();

        /**
         * @brief Checks if a character can be added to an ongoing equation, so that the equation would retain mathematical
         * sense, if character cannot be added the equation string remains the same
         * @param current The string holding the text of an ongoing equation
         * @param addition Currently added character
         */
        void equation_string_control(std::string &current, char addition);
        
        /**
         * @brief Resets the equation string control to the starting state
         */
        void reset_equation_string_control();
        
        /**
         * @return Returns the result
         */
        long double get_result();
       
        /**
         * @brief Prints the result to stdout
         */
        void result_print();

        /** 
         * @brief Parse the input string to numbers and operators and uses @relates real_time_calculation
         * to calculate the final result
         * @param input_str String with the equation that needs to be calculated, this string has to be parsed, so
         * it has mathematical sence, otherwise the behaviour is undefined
         * @param output_str Variable where the final result converted from long double, or an error message will be stored.
         * @return Returs 0 on success otherwise 1
         */
        int calculate(std::string input_str, std::string &output_str);

        /**
         * @brief Parses the input string to numbers and operators and uses @relates real_time_calculation
         * to calculate the final result
         * @param input_str String with the equation that needs to be calculated, this string has to be parsed, so
         * it has mathematical sence, otherwise the behaviour is undefined
         * @param output_result variable where the final result will be stored
         * @return Returns 0 on success otherwise 1 and std::runtime_exception is thrown
         */
        int calculate(std::string input_str, long double &output_result);

        /** 
         *  @brief Erases the currently ongoing equation (including the equation string control),
         *  sets everything to the starting state, so that new equation can start
         */
        void erase_equation();

        /**
         * @brief Provides new result after any added character, supported characters:
         *      '0'-'9' for digits
         *      '+', '-', '*', '/', '^', '?', '%', '!', '=' for operators ('?' represents the nrooth of a number)
         *      '.' for decimal point
         *      'N' for negation of a number
         *      'D' for deletion of the last character
         *      'C' for clearing the equation
         *      '(', ')' for brackets
         *      other characters are ignored
         * @param input_char New addition to an ongoing equation or starts a new equation.
         * @param output_str_result String where the new result, or the error message will be stored
         * @param output_str_equation String where the ongoing equation will be stored in the text form
         * @return 0 on success (includes wrong character), otherwise 1, when mathematical error occures
         */
        int real_time_calculation(char input_char, std::string &output_str_result, std::string &output_str_equation);

};

/**
 * @class Stddev_function
 * @brief Class containing all the functions necessary for running the stddev program
 */ 
class Stddev_function
{
    private:
        /**
         * @brief Pointer to a dynamically allocated memory, stores data from a file
        */ 
        long double *data_array;
        /**
         * @brief Addition of all number in file
        */ 
        long double total_addition; 
        /**
         * @brief Counts, how many numbers were read from a file
        */
        unsigned loaded_nums; 
        /**
         * @brief Calculates the mean, takes the total_addition and devide it with the loaded_nums
         * @pre At least one number has to be loaded
         * @return Average value is returned
        */
        long double get_mean();
        /**
         * @brief Subtracts mean from every loaded number and power it, then adds up all numbers
         * @return Summation for sample/population standard deviation is returned
        */
        long double get_summation();

    public:
        /**
         * @brief Gets the pointer to an array
         * @return NULL is returned if nothing was allocated, else pointer to dynamic array is returned
        */

        long double *get_data_pointer();
        /**
         * @brief Calculates sample standard deviation from the given data
         * @return Sample standard deviation is returned
        */

        long double calculate_stddev();
        /**
         * @brief Constructor
         * @details Tries to allocate space for 20 long double values, then sets total_addition and loaded_nums to zero
        */

        Stddev_function();
        /**
         * @brief Deconstructor
         * @details Frees all the allocated memory and set the data_array pointer to NULL
        */

        ~Stddev_function();
        /**
         *  @brief Loads all the data from a file to the data_array
         *  @return -1 is returned if loading fails, 1 is returned when functions ends successfully
        */
   
        int load_function();
};

#endif //__LOGIC_H__
