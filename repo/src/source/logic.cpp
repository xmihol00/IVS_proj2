/**
 * @file logic.cpp
 * @author Mihola David
 * @author Foltyn Lukas
 * @copyright ©Pied Piper
 * @brief Source file containing all the the definitions of functions declared in logic.h, serves
 * as a "brain" of the calculator.It is connected to all math functions in the library and put them
 * to use for solving advanced mathematical equations
*/

#include "../include/logic.h"

Logic::Logic()
{
    //some variables are initilized
    result = 0.0;
    currently_entered_num = 0.0;
    position = INTEGER;
    op_count_strcnt = 0;
    result_parts_op.push_back(0);
    result_parts.push_back(0);
    decimal_position = 0;
    result_parts_state.push_back(START_STATE);
    bracket_count = 0;
    negate = false;
}

long double Logic::get_result()
{
    return result;
}

void Logic::result_print()
{
    //result is printed to stdin
    std::cout << result << std::endl;
}


void Logic::math_calculation(int iterration_reduction = 0) //in C++ you can specify the initial value
{
    //if there is some reduction specified, than the number of calculation cycles is reduced to that number
    iterration_reduction = ((iterration_reduction)?(result_parts_op.size()-iterration_reduction):0);
    //to start the equation the currently entered number becomes the first result
    result = currently_entered_num;

    for (int i = result_parts_op.size()-1; i >= iterration_reduction; i--)
    { 
        switch(result_parts_op[i]) //the result operatores as the result_parts are stored in stack,
        {                          //based on the operator the mathematical calculation is proccede 
            case '+': 
                result = add(result_parts[i], result);
                break;

            case '-':
                result = sub(result_parts[i], result);
                break;

            case '*':
                result = mul(result_parts[i], result);
                break;
            
            case '/':
                if (result > -EPS && result < EPS)
                {
                    throw std::runtime_error("Division by 0.");
                    return;
                }

                result = div_(result_parts[i], result);
                break;
            
            case '?': 
                result = nroot(result_parts[i], result);
                break;

            case '!':
                result = factorial(result);
                break;
            
            case '%':
                result = (long double)((long)result_parts[i] % (long)result);
                break;
            
            case '^':
                result = xpow(result_parts[i], result);
                break;

            case 's':
                result = sinx(result); //sin has only one operand, so the result_parts are skipped
                break;

            case 'c':
                result = cosx(result); //cos has only one operand, so the result_parts are skipped
                break;

            case 't':
                result = tanx(result); //tan has only one operand, so the result_parts are skipped
                break;

            default:
                break;
        }
    }
}

#if 0
int Logic::pre_calculation_setup(char input_char)
{
    if (input_char == '!')
        currently_entered_num = factorial(currently_entered_num);
    else
    {
        if (input_char == '+' || input_char == '-')
        {
            LOG("level 1");
            math_calculation();
            result_parts.resize(1);
            result_parts_op.resize(1);

            result_parts[0] = result;
            result_parts_op[0] = input_char;
        }
        else if (input_char == '*' || input_char == '/' || input_char == '%')
        {
            if (result_parts_op.back() == '*' || result_parts_op.back() == '/' || result_parts_op.back() == '%')
            {
                LOG("level 2.2");
                math_calculation((result_parts.size()==1)?0:1);
                result_parts_op.back() = input_char;
                result_parts.back() = result;
            }
            else if (result_parts_op.back() == '+' || result_parts_op.back() == '-')
            {
                LOG("level 2.1");
                result_parts_op.push_back(input_char);
                result_parts.push_back(currently_entered_num);
            }
            else if (result_parts_op.back() == '?' || result_parts_op.back() == '^')
            {
                if (result_parts_op.size() == 1 || (result_parts_op[result_parts_op.size()-2] == '+' || result_parts_op[result_parts_op.size()-2] == '-'))
                {
                    LOG("level 2.3.1");
                    math_calculation((result_parts.size()==1)?0:1);
                    result_parts_op.back() = input_char;
                    result_parts.back() = result;
                }
                else
                {
                    LOG("level 2.3.2");
                    math_calculation(2);
                    result_parts_op.pop_back();
                    result_parts.pop_back();
                    result_parts_op.back() = input_char;
                    result_parts.back() = result;
                }
            }
            else
            {
                result_parts_op.back() = input_char;
                result_parts.back() = currently_entered_num;
            }
        }
        else if (input_char == '=')
        {
            LOG("equal");
            math_calculation();
            result_parts_op.clear();
            result_parts.clear();
            result_parts_op.push_back(0);
            result_parts.push_back(0);
            return 0;
        }
        else
        {
            if (result_parts_op.back() == '?' || result_parts_op.back() == '^')
            {
                LOG("level 3.1");
                math_calculation((result_parts.size()==1)?0:1);
                result_parts_op.back() = input_char;
                result_parts.back() = result;
            }
            else if (result_parts_op.back() == 0)
            {
                LOG("level 3.2");
                result_parts_op.back() = input_char;
                result_parts.back() = currently_entered_num;
            }
            else
            {
                LOG("level 3.3");
                result_parts_op.push_back(input_char);
                result_parts.push_back(currently_entered_num);
            }
        }
    }
    //math_calculation();
    return 0;
}
#endif

void Logic::recalculate_after_delete(const std::string &input_str)
{
    std::size_t increase;
    std::size_t j;

    long double result_hold = 0;
    currently_entered_num = 0;

    //cleares the current equation
    result_parts.clear();
    result_parts_op.clear();
    result_parts_state.clear();
    result_parts.push_back(0);
    result_parts_op.push_back(0);
    result_parts_state.push_back(START_STATE);
    add_to_calculation('R', ' ');

    for (std::size_t i = 0; i < input_str.size(); i++)
    {
        //the test can be converted to a number if this conditions is true
        if ((input_str[i] >= '0' && input_str[i] <= '9') || (i == 0 && input_str.size() > 1 && 
            input_str[i] == '-' && IS_DIGIT(input_str[1])) || ( input_str[i] == '-' && 
          (input_str[i-1] == '+' || input_str[i-1] == '-' || input_str[i-1] == '*' || input_str[i-1] == '/' || 
          input_str[i-1] == '^' || input_str[i-1] == '?' ||  input_str[i-1] == '%' || input_str[i-1] == '(') 
          && i != input_str.size() - 1 && (i + 1 < input_str.size() && input_str[i+1] != '(')))
        {
            currently_entered_num = std::stold(&input_str[i], &increase);
            j = i += increase; //the iterator is increased for the lenght of the converted number

            while(j < input_str.size()) //checks if there are more more numbers
                if (IS_DIGIT(input_str[j++]))
                    break;

            if (j >= input_str.size()) //when there are no more numbers
	        {  
                try
                {
	        	    math_calculation();    //the result is calculated
                }
                catch(const std::exception &e)
                {
                    throw std::runtime_error("Cannot delete this.");
                }
                  
            	result_hold = result;  //and it is remembered, becuase other characters (operators, brackets) can be added
	        }                          //aterwards and the result can change by these additions
        }

        if (i < input_str.size())
        {
            add_to_calculation(input_str[i], (i > 0)?input_str[i-1]:0); //operator, bracket, ... is added to the equation

            //if there are more operators f.e. +-(
            while (i + 2 < input_str.size() && !IS_DIGIT(input_str[i + 1]) && !IS_DIGIT(input_str[i + 2])) 
            {
                try
                {
                    i++;
                    if (input_str[i] == '-' && (IS_OPERATOR_NF(input_str[i-1])))
                    {
                        add_to_calculation('M', ' ');
                    }    
                    else
                    {
                        add_to_calculation(input_str[i], input_str[i - 1]);
                    }

                    if(input_str[i] == 's' || input_str[i] == 'c' || input_str[i] == 't')
                        i+=2;
                }
                catch(const std::exception &e)
                {
                    throw std::runtime_error("Cannot delete this.");
                }
                
            }
        }
    }

    //last calculated result is loaded to result, as result can be changed also with adding the operatores
    result = result_hold;
}

int Logic::calculate(std::string input_str, std::string &output_str)
{
    //adding R resets the current calculation
    add_to_calculation('R', ' ');
    output_str.clear();
    std::setlocale(LC_ALL, "C");
    std::size_t increase;
    for (std::size_t i = 0; i < input_str.size(); i++)
    {
        //the test can be converted to a number if this conditions is true
        if ((input_str[i] >= '0' && input_str[i] <= '9') || (i == 0 && input_str.size() > 1 && 
            input_str[i] == '-' && IS_DIGIT(input_str[1])) || ( input_str[i] == '-' && 
          (input_str[i-1] == '+' || input_str[i-1] == '-' || input_str[i-1] == '*' || input_str[i-1] == '/' || 
          input_str[i-1] == '^' || input_str[i-1] == '?' ||  input_str[i-1] == '%' || input_str[i-1] == '(') 
          && i != input_str.size() - 1 && (i + 1 < input_str.size() && input_str[i+1] != '(')))
        {
            currently_entered_num = std::stold(&input_str[i], &increase);
            i += increase; //the iterator is increased for the lenght of the converted number
        }

        if (i < input_str.size())
        {
            try
            {
                //the first operator is added
                add_to_calculation(input_str[i], (i > 0)?input_str[i-1]:0);
                
                //if there are multiple operators, they are also added
                while (i + 2 < input_str.size() && !IS_DIGIT(input_str[i + 1]) && !IS_DIGIT(input_str[i + 2]))
                {                 
                    i++;  
                    if (input_str[i] == '-' && (IS_OPERATOR_NF(input_str[i-1])))
                    {
                        add_to_calculation('M', ' ');
                    }
                    else
                    {
                        add_to_calculation(input_str[i], input_str[i - 1]);
                    }
                    
                    if(input_str[i] == 's' || input_str[i] == 'c' || input_str[i] == 't')
                        i+=2;
                }
            }
            catch(const std::exception& e)
            {
                //when the calculation fails f.e. division by 0
                output_str.clear();
                output_str.assign(e.what());
                return 1;
            }
        }
    
    }

    try
    {   
        //the final result is calculated by simulatinf the press of '='
        add_to_calculation('=', ' ');
    }
    catch(const std::exception &e)
    {
        output_str.assign(e.what());
        return 1;
    }
    
    //the double result is converted to text, which is displayed on the calculator screen
    output_str.assign(std::to_string(result));
    //the trailing 0 are stripped
    output_str.erase(output_str.find_last_not_of('0') + 1, std::string::npos);
    //if the number wasn't floating point number the decimal dot is stripped
    if (output_str.back() == '.')
        output_str.pop_back();
        
    return 0;
}

int Logic::calculate(std::string input_str, long double &output_result)
{
    //adding R resets the current calculation
    add_to_calculation('R', ' ');
    std::size_t increase;
    for (std::size_t i = 0; i < input_str.size(); i++)
    {
        //the test can be converted to a number if this conditions is true
        if ((input_str[i] >= '0' && input_str[i] <= '9') || (i == 0 && input_str.size() > 1 && 
            input_str[i] == '-' && IS_DIGIT(input_str[1])) || ( input_str[i] == '-' && 
          (input_str[i-1] == '+' || input_str[i-1] == '-' || input_str[i-1] == '*' || input_str[i-1] == '/' || 
          input_str[i-1] == '^' || input_str[i-1] == '?' ||  input_str[i-1] == '%' || input_str[i-1] == '(') 
          && i != input_str.size() - 1 && (i + 1 < input_str.size() && input_str[i+1] != '(')))
        {
            currently_entered_num = std::stold(&input_str[i], &increase); 
            i += increase; //the iterator is increased for the lenght of the converted number
        }
        if (i < input_str.size())
        {
            try
            {
                //the first operator is added
                add_to_calculation(input_str[i], (i > 0)?input_str[i-1]:0);

                //if there are multiple operators, they are also added
                while (i + 2 < input_str.size() && !IS_DIGIT(input_str[i + 1]) && !IS_DIGIT(input_str[i + 2]))
                {  
                    if (input_str[++i] == '-' && (IS_OPERATOR_NF(input_str[i-1])))
                        add_to_calculation('M', ' ');
                    else
                        add_to_calculation(input_str[i], input_str[i - 1]);
                    
                    if(input_str[i] == 's' || input_str[i] == 'c' || input_str[i] == 't')
                        i+=2;
                }
            }
            catch(const std::exception& e)
            {
                // if the calculation fails, the result is set to NAN 
                output_result = NAN;
                return 1;
            }
        }
    
    }
    try
    {
        //simulates pressing equal button
        add_to_calculation('=', ' ');
    }
    catch(const std::exception &e)
    {
        output_result = NAN;
        return 1;
    }
    
    //the result is loaded to the output_result
    output_result = result;

    return 0;
}

character_input_states Logic::get_state(char input_char, char last)
{
    static bool decimal;

    if (input_char == 'Q') //sets the static variable decimal to true -> floating ponit number is added (used for deleteing)
    {
        decimal = true;
        return UNDEFINED;
    }
    else if (input_char == 'q') //sets the static variable decima to false -> integer is added
    {
        decimal = false;
        return UNDEFINED;
    }
    else if (input_char == 'U') // U means undefined 
    {
        return UNDEFINED;
    }
    else if (input_char == 'R') // returns signal to reset the calculation
    {
        return RESET;
    }

    if (IS_DIGIT(input_char)) //if the input character is digit
    {
        if (decimal)
            return DECIMAL;
        return DIGIT;
    }
    else if (input_char == 'N') //if the N is input, then negation of a number has to be performed
    {
        return NEGATION;
    }

    decimal = false; //if some other character is added, then floating number ends

    if (input_char == '!') //factorial has to be calculated
    {
        return FACTORIAL;
    }
    else if (input_char == '.') //deciaml number creation is engaged
    {
        decimal = true;
        return DECIMAL_DOT;
    }
    else if (input_char == 'M') //M - minus: simulates minus (used while deleting) 
    {
        return NEGATE;
    }
    else if (input_char == '=') //equal
    {
        return EQUAL;
    }
    else if (input_char == 'C') //clear 
    {
        return CLEAR;
    } 
    else if (input_char == '(') //open bracket
    {
        return OPENED_BRACKET;
    }
    else if (input_char == ')') //closed bracket
    {
        return CLOSED_BRACKET;
    }
    else if (input_char == '+' || input_char == '-') //plus or minus is added
    {
        // if it the addition is minus and the last addition was an operator, opened bracked or it is the first operator
        //then the next number will be negative
        if (input_char == '-' && (IS_OPERATOR_NF(last) || last == 0 || last == '('))
        {
            return NEGATE;
        }
        
        // '+' and '-' are the lowest level operators (L1), 
        //so if one of this operator is pressed the stack ahs to be reduced to minimum

        //the stack is of size 1, therfore no reduction
        if (result_parts_state.back() == L1 || result_parts_state.back() == L3 || result_parts_state.back() == L2 ||
            result_parts_state.back() == START_STATE)
        {
            result_parts_state.back() = L1;
            return PROCCEDE;
        }
        //the stack has size 3, it has to be reduced to 1
        else if (result_parts_state.back() == L1L2L3)
        {
            result_parts_state.back() = L1;
            return REDUCTION_BY2;
        }
        //if the opened bracket is presed, than the stack size in the bracket is 0, therfore 1 has to be created
        else if (result_parts_state.back() == OPENED_BRACKET)
        {
            result_parts_state.back() = L1;
            return ADDITION;
        }
        //no other possibilites as L
        
        //when goniometric functions are used, the number of stack size increases by 1, as calculation of gonimetric function
        //requires one operator
        
        //only goniometric function was used, the satack size is 1, therfore no reduction
        else if(result_parts_state.back() == GONIO)
        {
            result_parts_state.back() = L1;
            return PROCCEDE;
        }
        //the stack size is 3, has to be reduced to 1
        else if(result_parts_state.back() == L1L2_GONIO)
        {
            result_parts_state.back() = L1;
            return REDUCTION_BY2;
        }
        //the stack size is 3, has to be reduced to 1
        else if(result_parts_state.back() == L1L3_GONIO)
        {
            result_parts_state.back() = L1;
            return REDUCTION_BY2;
        }
        //the stack size is 3, has to be reduced to 1
        else if(result_parts_state.back() == L2L3_GONIO)
        {
            result_parts_state.back() = L1;
            return REDUCTION_BY2;
        }
        //the stack size is 4, has to be reduced to 1
        else if(result_parts_state.back() == L1L2L3_GONIO)
        {
            result_parts_state.back() = L1;
            return REDUCTION_BY3;
        }
        else //the stack size is 2 (including states L1L2, L2L3, L1_GONIO, L2_GONIO, L3_GONIO), has to be reduced to 1
        {
            result_parts_state.back() = L1;
            return REDUCTION_BY1;
        }
    }
    else if (input_char == '*' || input_char == '/' || input_char == '%') //the operator pressed is of level 2 priority -> L2
    {
        //stack has to be increased
        if (result_parts_state.back() == L1)
        {
            result_parts_state.back() = L1L2;
            return ADDITION;
        }
        //nothing is in the equation or the operator level is the same, stack size does not change
        else if (result_parts_state.back() == START_STATE || result_parts_state.back() == L2)
        {
            result_parts_state.back() = L2;
            return PROCCEDE;
        }
        //if there is only one operator of level 3, then the stack size is 1, so no reduction occures
        else if (result_parts_state.back() == L3)
        {
            result_parts_state.back() = L2;
            return PROCCEDE;
        }
        //the stack size is 2, the level 3 is changed to level 2, but the stack is not reduced
        else if (result_parts_state.back() == L1L3)
        {
            result_parts_state.back() = L1L2;
            return PROCCEDE;
        }
        //the stack size is 2, level 3 operator is reduced to level 2 and the stack size has to be decreased
        else if (result_parts_state.back() == L2L3)
        {
            result_parts_state.back() = L2;
            return REDUCTION_BY1;
        }
        //the stack size is 3, the level 3 operator is reduced to level 2 and the stack size has to be decreased
        else if (result_parts_state.back() == L1L2L3)
        {
            result_parts_state.back() = L1L2;
            return REDUCTION_BY1;
        }
        //the state does not change, the calculation is procceded
        else if (result_parts_state.back() == L1L2)
        {
            return PROCCEDE;
        }
        //the state does not change, the calculation is procceded
        else if (result_parts_state.back() == L2)
        {
            return PROCCEDE;
        }
        //the stack size is 0, it has to be increased to 1
        else if (result_parts_state.back() == OPENED_BRACKET)
        {
            result_parts_state.back() = L2;
            return ADDITION;
        }
        //the stack size is 1, it remains 1
        else if(result_parts_state.back() == GONIO)
        {
            result_parts_state.back() = L2;
            return PROCCEDE;
        }
        //the satack size is 2, it remains 2
        else if(result_parts_state.back() == L1_GONIO)
        {
            result_parts_state.back() = L1L2;
            return PROCCEDE;
        }
        //the stack size is 2, it has to be reduced to 1
        else if(result_parts_state.back() == L2_GONIO)
        {
            result_parts_state.back() = L2;
            return REDUCTION_BY1;
        }
        //the stack size is 2, it has to be reduced to 1
        else if(result_parts_state.back() == L3_GONIO)
        {
            result_parts_state.back() = L2;
            return REDUCTION_BY1;
        }
        //the stack size is 3, it has to be reduced to 2
        else if(result_parts_state.back() == L1L2_GONIO)
        {
            result_parts_state.back() = L1L2;
            return REDUCTION_BY1;
        }
        //the stack size is 3, it has to be reduced to 2
        else if(result_parts_state.back() == L1L3_GONIO)
        {
            result_parts_state.back() = L1L2;
            return REDUCTION_BY1;
        }
        //the stack size is 3, it has to be reduced to 1
        else if(result_parts_state.back() == L2L3_GONIO)
        {
            result_parts_state.back() = L2;
            return REDUCTION_BY2;
        }
        //the stack size is 4, it has to be reduced to 2
        else if(result_parts_state.back() == L1L2L3_GONIO)
        {
            result_parts_state.back() = L1L2;
            return REDUCTION_BY2;
        }
    }
    else if (input_char == '?' || input_char == '^') //the operators pressed is of level 3 (L3)
    {
        //the stack size is 1, it remains the same
        if (result_parts_state.back() == START_STATE || result_parts_state.back() == L3)
        {
            result_parts_state.back() = L3;
            return PROCCEDE;
        }
        //stack size is 1, has to be increased
        else if (result_parts_state.back() == L1)
        {
            result_parts_state.back() = L1L3;
            return ADDITION;
        }
        //stack size is 1, has to be increased
        else if (result_parts_state.back() == L2)
        {
            result_parts_state.back() = L2L3;
            return ADDITION;
        }
        //stack size is 2, has to be increased
        else if (result_parts_state.back() == L1L2)
        {
            result_parts_state.back() = L1L2L3;
            return ADDITION;
        }
        //the stack size is 3, remains 3
        else if (result_parts_state.back() == L1L2L3)
        {
            return PROCCEDE;
        }
        //the stack size is 2, remains 2
        else if (result_parts_state.back() == L1L3)
        {
            return PROCCEDE;
        }
        //the stack size is 2, remains 2
        else if (result_parts_state.back() == L2L3)
        {
            return PROCCEDE;
        }
        //the stack size is 0, has to be increased to 1
        else if (result_parts_state.back() == OPENED_BRACKET)
        {
            result_parts_state.back() = L3;
            return ADDITION;
        }
        //the stacks size is 1, remains 1
        else if(result_parts_state.back() == GONIO)
        {
            result_parts_state.back() = L3;
            return PROCCEDE;
        }
        //the stacks size is 2, remains 2
        else if(result_parts_state.back() == L1_GONIO)
        {
            result_parts_state.back() = L1L3;
            return PROCCEDE;
        }
        //the stacks size is 2, remains 2
        else if(result_parts_state.back() == L2_GONIO)
        {
            result_parts_state.back() = L2L3;
            return PROCCEDE;
        }
        //the stacks size is 2, has to be decreased to 1
        else if(result_parts_state.back() == L3_GONIO)
        {
            result_parts_state.back() = L3;
            return REDUCTION_BY1;
        }
        //the stacks size is 3, remains 3
        else if(result_parts_state.back() == L1L2_GONIO)
        {
            result_parts_state.back() = L1L2L3;
            return PROCCEDE;
        }
        //the stacks size is 3, has to be decreased to 2
        else if(result_parts_state.back() == L1L3_GONIO)
        {
            result_parts_state.back() = L1L3;
            return REDUCTION_BY1;
        }
        //the stacks size is 3, has to be decreased to 2
        else if(result_parts_state.back() == L2L3_GONIO)
        {
            result_parts_state.back() = L2L3;
            return REDUCTION_BY1;
        }
        //the stacks size is 4, has to be decreased to 3
        else if(result_parts_state.back() == L1L2L3_GONIO)
        {
            result_parts_state.back() = L1L2L3;
            return REDUCTION_BY1;
        }
    }
    else if (input_char == 's' || input_char == 'c' || input_char == 't') //the goniometric butto is pressed (GONIO)
    {
        //if there is minus in front of the goniometric functiond, then the fundtion has to be negated by adding *-1 to the stack
        if(negate && result_parts_state.back() == START_STATE)
            result_parts_state.back() = GONIO_PROCCEDE;
        //the stack size is 1, remains 1
        else if(result_parts_state.back() == START_STATE)
        {
            result_parts_state.back() = GONIO;
            return PROCCEDE;
        }
        //at any other nput, the stack size has to be increased by 1
        else if (result_parts_state.back() == OPENED_BRACKET)
            result_parts_state.back() = GONIO;
        else if(result_parts_state.back() == L1)
            result_parts_state.back() = L1_GONIO;
        else if(result_parts_state.back() == L2)
            result_parts_state.back() = L2_GONIO;
        else if(result_parts_state.back() == L3)
            result_parts_state.back() = L3_GONIO;
        else if(result_parts_state.back() == L1L2)
            result_parts_state.back() = L1L2_GONIO;
        else if(result_parts_state.back() == L1L3)
            result_parts_state.back() = L1L3_GONIO;
        else if(result_parts_state.back() == L2L3)
            result_parts_state.back() = L2L3_GONIO;
        else if(result_parts_state.back() == L1L2L3)
            result_parts_state.back() = L1L2L3_GONIO;

        return GONIO_ADDITION;
    }
    
    return UNDEFINED; //this should never happend
}

void Logic::add_to_calculation(char input_char, char last_input)
{
    switch (get_state(input_char, last_input)) //gets the current operation, that has to be proccede
    {
    case DIGIT:
        //digit was added
        if (negate) //if the number is negative
        {
            currently_entered_num = currently_entered_num * 10 - (input_char - '0');
        }
        else //if the number is positive
            currently_entered_num = currently_entered_num * 10 + (input_char - '0');

        // after any change of the currently entered number, the result has to be recalculated
        if (result_parts_op.back() == '/' && currently_entered_num == 0) //when the last operator is / division by 0 is avoided
        {                                                                //f.e. when floating point number is added
            currently_entered_num = 1;
            math_calculation();
            currently_entered_num = 0;
        }
        else
            math_calculation(); //otherwise the calculation is performed normaly
        break;
            
    case DECIMAL:
        decimal_position *= 10; //the floating point position increases
        if (negate) //if the number is negative
        {
            currently_entered_num -= ((long double)(input_char - '0')/(decimal_position));
        }
        else //if the number is positive
            currently_entered_num += ((long double)(input_char - '0')/(decimal_position));

        if (result_parts_op.back() == '/' && currently_entered_num < EPS && currently_entered_num > - EPS) //when the last operator is / division by 0 is avoided
        {
            currently_entered_num = 1;
            math_calculation();
            currently_entered_num = 0;
        }
        else
            math_calculation(); //otherwise the calculation is performed normaly
        
        break;
    
    case DECIMAL_DOT:
        decimal_position = 1; //resets the floating point position
        break;
    
    case NEGATE:
        negate = true; //when the number is negative, negate is set to true
        break;

    case NEGATION:
        negate = !negate; //on press of the button 'N', the currently entered number is negated
        currently_entered_num = - currently_entered_num;
        if (result_parts_op.back() == '/' && currently_entered_num < EPS && currently_entered_num > - EPS) //when the last operator is / division by 0 is avoided
        {
            currently_entered_num = 1;
            math_calculation();
            currently_entered_num = 0;
        }
        else
            math_calculation(); //otherwise the calculation is performed normaly
        break;

    case FACTORIAL:
        currently_entered_num = factorial(currently_entered_num); //factorial of a number is calculated
        math_calculation(); 

        break;
    
    case REDUCTION_BY3: //the current stack size is reduced by 3
        negate = false;
        math_calculation(4); // the result of the current stack is calculated
        //varibles that represent the stack are reduced
        result_parts_op.erase(result_parts_op.end() - 3, result_parts_op.end());
        result_parts.erase(result_parts.end() - 3, result_parts.end());
        result_parts_op.back() = input_char;
        result_parts.back() = result; //the caculated result is stored to the reduced stack
        currently_entered_num = 0;

        //the stack size has to be reduced by further one, if there is a negation in front of a goniometric function
        if (result_parts_state.size() > 1 && result_parts_state[result_parts_state.size() - 2] == GONIO_NEGATE)
        {
            math_calculation(2);
            result_parts_op.pop_back();
            result_parts.pop_back();
            result_parts_state[result_parts_state.size() - 2] = result_parts_state.back();
            result_parts_state.pop_back();
            result_parts.back() = result;
            result_parts_op.back() = input_char;
            currently_entered_num = result;
        }
        break;

    case REDUCTION_BY2: //the current stack size is reduced by 2
        negate = false;
        math_calculation(3); //result of the stack size is calculated
        //varibles that represent the stack are reduced
        result_parts_op.pop_back();
        result_parts_op.pop_back();
        result_parts.pop_back();
        result_parts.pop_back();
        result_parts_op.back() = input_char;
        result_parts.back() = result; //the calculated result is sotored to the decreased stack
        currently_entered_num = 0;

        //the stack size has to be reduced by further one, if there is a negation in front of a goniometric function
        if (result_parts_state.size() > 1 && result_parts_state[result_parts_state.size() - 2] == GONIO_NEGATE)
        {
            math_calculation(2);
            result_parts_op.pop_back();
            result_parts.pop_back();
            result_parts_state[result_parts_state.size() - 2] = result_parts_state.back();
            result_parts_state.pop_back();
            result_parts.back() = result;
            result_parts_op.back() = input_char;
            currently_entered_num = result;
        }
        break;

    case REDUCTION_BY1: //the current stack size is reduced by 1
        negate = false;
        math_calculation(2); //the result of the stack size is reduced
        //varibles that represent the stack are reduced
        result_parts_op.pop_back();
        result_parts.pop_back();
        result_parts_op.back() = input_char;
        result_parts.back() = result; //the calculated result is stored to the reduced stack
        currently_entered_num = 0;

        //the stack size has to be reduced by further one, if there is a negation in front of a goniometric function
        if (result_parts_state.size() > 1 && result_parts_state[result_parts_state.size() - 2] == GONIO_NEGATE)
        {
            math_calculation(2);
            result_parts_op.pop_back();
            result_parts.pop_back();
            result_parts_state[result_parts_state.size() - 2] = result_parts_state.back();
            result_parts_state.pop_back();
            result_parts.back() = result;
            result_parts_op.back() = input_char;
            currently_entered_num = 0;
        }
        break;

    case ADDITION:
        //the stack size is increased by 1
        negate = false;
        result_parts.push_back(currently_entered_num);
        result_parts_op.push_back(input_char);
        currently_entered_num = 0;
        break;
    
    case GONIO_ADDITION: //the stack size can be increased by 1, 2 or remain the same
        if (negate) //when minus was pressed before goniometric function
        {
            // adding *-1 ensures the negation
            result_parts_op.push_back('*');
            result_parts.push_back(-1);
            if (result_parts_state.back() != GONIO_PROCCEDE) 
                result_parts_state.insert(result_parts_state.end()-1, GONIO_NEGATE);
            else
                result_parts_state.back() = GONIO_NEGATE;
        }       
        // when the stack size has to be increased
        if(result_parts_state.back() != GONIO_PROCCEDE)
        {
            negate = false;
            result_parts.push_back(0);
            result_parts_op.push_back(input_char);
            currently_entered_num = 0;
        }
        //at some occasions addition of the negation is enough
        else
            result_parts_state.back() = GONIO;

        break;
    
    case OPENED_BRACKET:
        //when negation is in fron of the bracket
        if (negate)
        {
            // adding *-1 ensures the negation
            result_parts_op.push_back('*');
            result_parts.push_back(-1);
            result_parts_state.push_back(NEGATE);

        }
        //when multiple brackets are open at one time, the stack has to be increased, but the stack is not increased,
        //when only one bracket is added, this increase is preformed later on by adding an operator inside the bracket,
        //beaucese f.e. x+((z))-y == x+z-y
        if (last_input == '(')
        {
            result_parts_op.push_back(0);
            result_parts.push_back(0);
            result_parts_state.back() = START_STATE; //empty bracket is considered as a start state
        }
        result_parts_state.push_back(OPENED_BRACKET); //only new state is created
        negate = false;
        break;

    case CLOSED_BRACKET:
        negate = false;
        //when bracket is closed, the stack size has to be reduced based on the ongoing calculation in that bracket

        //if the stack size is 1, then it is reduced by 1
        if (result_parts_state.back() == L1 || result_parts_state.back() == L2 || result_parts_state.back() == L3 
            || result_parts_state.back() == GONIO || result_parts_state.back() == START_STATE)
        {
            math_calculation(1);
            result_parts_state.pop_back();
            result_parts_op.pop_back();
            result_parts.pop_back();
            currently_entered_num = result;
        }
        //if the stack size is 2, then it is reduced by 2
        else if (result_parts_state.back() == L1L2 || result_parts_state.back() == L1L3 || result_parts_state.back() == L2L3 ||
                 result_parts_state.back() == L3_GONIO || result_parts_state.back() == L2_GONIO || result_parts_state.back() == L1_GONIO)
        {
            math_calculation(2);
            result_parts_op.pop_back();
            result_parts.pop_back();
            result_parts_op.pop_back();
            result_parts.pop_back();
            result_parts_state.pop_back();
            currently_entered_num = result;
        }
        //if the stack size is 3, then it is reduced by 3
        else if (result_parts_state.back() == L1L2L3 || result_parts_state.back() == L1L2L3 || result_parts_state.back() == L1L2_GONIO ||
                 result_parts_state.back() == L1L3_GONIO || result_parts_state.back() == L2L3_GONIO)
        {
            math_calculation(3);
            result_parts_op.erase(result_parts_op.end() - 3, result_parts_op.end());
            result_parts.erase(result_parts.end() -3, result_parts.end());
            result_parts_state.pop_back();
            currently_entered_num = result;
        }
        //if the stack size is 4, then it is reduced by 4
        else if (result_parts_state.back() == L1L2L3_GONIO)
        {
            math_calculation(4);
            result_parts_op.erase(result_parts_op.end() - 4, result_parts_op.end());
            result_parts.erase(result_parts.end() -4, result_parts.end());
            result_parts_state.pop_back();
            currently_entered_num = result;
        }

        //additionaly, when the bracket was nagated, the negation has to be reduced
        if (result_parts_state.back() == NEGATE)
        {
            math_calculation(1);
            result_parts_op.pop_back();
            result_parts.pop_back();
            result_parts_state.pop_back();
            currently_entered_num = result;
        }
        //if there is only opened bracket, then the state is reduced withou reducing the stack
        else if (result_parts_state.back() == OPENED_BRACKET)
            result_parts_state.pop_back();

        break;
    
    case EQUAL:     
        //when the equal button is pressed, then the result is calculated and everything is cleared  
        math_calculation();
        result_parts_state.clear();
        result_parts_op.clear();
        result_parts.clear();
        result_parts_op.push_back(0);
        result_parts.push_back(0);
        result_parts_state.push_back(START_STATE);
        decimal_position = 1;
        currently_entered_num = result; //the result is stored there, so it can be increased, decreased or operator can be put behind
        if (currently_entered_num < 0) // the negation is set accordingly to the result
            negate = true;
        else
            negate = false;

        return; 

    case CLEAR: //everything is cleared and reseted
        negate = false;
        result_parts_state.clear();
        result_parts_op.clear();
        result_parts.clear();
        result_parts_op.push_back(0);
        result_parts.push_back(0);
        result_parts_state.push_back(START_STATE);
        currently_entered_num = 0;
        result = 0;
        last_input = 0;
        return;

    case UNDEFINED: //should never happen
        return;

    case PROCCEDE:
        //special case of proccede, when the goniometric negation has to be decresed
        if (result_parts_state.size() > 1 && result_parts_state[result_parts_state.size() - 2] == GONIO_NEGATE)
        {
            math_calculation(2);
            result_parts_op.pop_back();
            result_parts.pop_back();
            result_parts_state[result_parts_state.size() - 2] = result_parts_state.back();
            result_parts_state.pop_back();
            result_parts.back() = result;
            result_parts_op.back() = input_char;
            currently_entered_num = 0;
            negate = false;
        }
        //the size of the stack remains the same, only the number on the top changes
        else
        {
            negate = false;
            math_calculation(1); //calculates just two numbers together
            result_parts.back() = result;
            result_parts_op.back() = input_char;
            currently_entered_num = 0;
        }
        break;

    case RESET:
        negate = false;
        return;

    default:
        break;
    }

    return;
}

int Logic::real_time_calculation(char input_char, std::string &output_str_result, std::string &output_str_equation)
{
    //setting the locale, so that the decimal dot is used rather than comma
    std::setlocale(LC_ALL, "C");
    //static variables that holds data about the ongoing equation
    static bool add;
    static unsigned add_position;
    static char last_input;
    static unsigned digit_count;

    //when the equation is cleared or the last character is deleted, then the equation is reseted to the starting state 
    if (input_char == 'C' || (input_char == 'D' && output_str_equation.size() == 1))
    {
        reset_equation_string_control();
        output_str_equation.clear();
        output_str_result.clear();
        //output_str_result.push_back('0');
        add_to_calculation('C', last_input);
        add = false;
        add_position = 0;
    }
    else if (input_char == 'D') //when character is deleted
    {
        last_input = output_str_equation.back();
        //the request is sent to the equation string cotrol to change the string accordingly
        equation_string_control(output_str_equation, input_char);

        if (last_input == 'n' || last_input == 's') //if goniometric function was deleted
        {
            add_position -= 2; //the position of currentlu added character to a equation is reduced accordingly
        }
        if (add_position == output_str_equation.size() + 1) //if the deleted character was already added to the equation 
        {                                                   //f.e. operators aren't added immidiately, but with the first following digit3
            add = false;
            if (last_input == '(' || last_input == ')' || last_input == '!') //the equation has to be recalculated
            {
                try
                {
                    recalculate_after_delete(output_str_equation);
                }
                catch(const std::exception &e)
                {
                    output_str_result.clear();
                    output_str_result.assign(e.what());
                    currently_entered_num = 0;
                    if (add_position > 0)
                        add_position--;
                    return 1;  
                }
                
            }
            else if (last_input == '.') //get state has to be informed, that integer was created from a floating point number
            {
                get_state('q', 0);
            }
            else if (output_str_equation.back() == '(') //if the current last character in the equation string is bracket,
            {                                           //then the equation has to be recalculated, to avoid
                currently_entered_num = 0;              //calculation with 0
                decimal_position = 0;
                try
                {
                    recalculate_after_delete(output_str_equation);
                }
                catch(const std::exception &e)
                {
                    output_str_result.clear();
                    output_str_result.assign(e.what());
                    currently_entered_num = 0;
                    if (add_position > 0)
                        add_position--;
                    return 1;  
                }
            }
            else if (IS_OPERATOR_NF(output_str_equation.back())) //if the current last character is an operator, then
            {                                                    //the equation has to be recalculated, but without the operators,
                currently_entered_num = 0;                       //so that the operator can be changed
                decimal_position = 0;
                add = true;
                add_position--;
                char hold1 = output_str_equation.back(); //the first operator is separated
                output_str_equation.pop_back();
                if (IS_OPERATOR_NF(output_str_equation.back())) //if there is +-, *-, /-, ... two operators have to be separated
                {
                    add_position--;
                    char hold2 = output_str_equation.back(); //the first operator is separated
                    output_str_equation.pop_back();
                    try
                    {
                        recalculate_after_delete(output_str_equation);
                    }
                    catch(const std::exception &e)
                    {
                        output_str_result.clear();
                        output_str_result.assign(e.what());
                        currently_entered_num = 0;
                        if (add_position > 0)
                            add_position--;
                        return 1;  
                    } 
                    output_str_equation.push_back(hold2);   //operator is added back
                    output_str_equation.push_back(hold1);   //operator is added back
                }
                else
                {
                    try
                    {
                        recalculate_after_delete(output_str_equation);
                    }
                    catch(const std::exception &e)
                    {
                        output_str_result.clear();
                        output_str_result.assign(e.what());
                        currently_entered_num = 0;
                        if (add_position > 0)
                            add_position--;
                        return 1;  
                    }
                    output_str_equation.push_back(hold1); //operator is added back
                }
            }
            //if the deleted operator was a gonimetric function, the result has to be recalculated
	    else if (output_str_equation.back() == 'n' || output_str_equation.back() == 's')
            {
                currently_entered_num = 0;              //calculation with 0
                decimal_position = 0;
                try
                {
                    recalculate_after_delete(output_str_equation);
                }
                catch(const std::exception &e)
                {
                    output_str_result.clear();
                    output_str_result.assign(e.what());
                    currently_entered_num = 0;
                    if (add_position > 0)
                        add_position--;
                    return 1;  
                }
            }
            else if (IS_DIGIT(last_input)) //the currently entered number has to change 
            {
                if (decimal_position > 2) //if it is a floating point number
                {
                    if (negate)
                        currently_entered_num += (last_input - '0')/decimal_position;
                    else
                        currently_entered_num -= (last_input - '0')/decimal_position;
                }
                else //if it is an integer
                {
                    if (negate)
                        currently_entered_num = (currently_entered_num + (last_input - '0')) / 10;
                    else
                        currently_entered_num = (currently_entered_num - (last_input - '0')) / 10;
                }

                decimal_position /= 10; // the decimal position is decresed
                
                //the new number has to be included to the calculation
                if (result_parts_op.back() == '/' && currently_entered_num > -EPS && currently_entered_num < EPS)
                {
                    //if the last operation is division and the currentlu entered number is 0, division by 0 is avoided
                    currently_entered_num = 1; 
                    try
                    {
                        math_calculation();

                    }
                    catch(const std::exception &e)
                    {
                        output_str_result.clear();
                        output_str_result.assign(e.what());
                        currently_entered_num = 0;
                        if (add_position > 0)
                            add_position--;
                        return 1;    
                    }
                    currently_entered_num = 0;
                }
                else //otherwise the reusult is calculated
                {
                    try
                    {
                        math_calculation();
                    }
                    catch(const std::exception &e)
                    {
                        output_str_result.clear();
                        output_str_result.assign(e.what());
                        if (add_position > 0)
                            add_position--;
                        return 1;
                    }
                }

            }
                 
            if (add_position > 0)
                add_position--; //the add position is decreased
        }

        //if the current last character is a digit and operator or closed bracket was deleted, then the current number and data
        //about the number have to be reloaded (negative/positive, number of decimal places)
        if (IS_DIGIT(output_str_equation.back()) && (IS_OPERATOR(last_input) || last_input == ')'))
        {
            decimal_position = 1;
            for (int i = output_str_equation.size()-1; i >= 0; i--)
            {
                if (output_str_equation[i] == '.')
                {
                    get_state('Q', 0);
                    break;
                }
                else if (IS_OPERATOR(output_str_equation[i]) || i == 0)
                {
                    get_state('q', 0);
                    decimal_position = 1;
                    break;
                }
                decimal_position *= 10;
            }
            if (currently_entered_num < 0) 
                negate = true;
            else
                negate = false;
            
        }
    }
    else if (input_char != '=') //if digit, operators or brackets are added to the equation
    {
        //adding the character to the string, that is going to be diplayed in the window
        //the string is changed only when the input character is valid
        equation_string_control(output_str_equation, input_char);
        
        if (IS_OPERATOR_NF(input_char) && !add && output_str_equation.size() > 1) //if operator is added
        {
            add_position = output_str_equation.size() - 1; //the position is rembered, and the next addition to the equation,
            add = true;                                    //will be performed after a first digit is added 
        }
        else if (input_char == 'N' && add_position != output_str_equation.size())//&& (output_str_equation.size() && !IS_OPERATOR(output_str_equation.back()))))
        //when the nagation button was pressed and the equation string changed (either minus was added, or subtracted)
        {                                                    
            try
            {
                add_to_calculation('N', last_input); //the current number is negated
                math_calculation();
            }
            catch(const std::exception& e)
            {
                output_str_result.clear();
                output_str_result.assign(e.what());
                return 1;
            }
            
            add_position = output_str_equation.size();
            add = false;
        }
        else if (!IS_OPERATOR_NF(input_char) && add_position < output_str_equation.size() && input_char != 'N' && 
                 output_str_equation.back() == input_char) //if the added character is not operator and there are characters to be
        //added (add_position < str.size()), then the remaining characters are added         
        { 
            for (unsigned i = add_position; i < output_str_equation.size(); i++)
            {   
                digit_count++;
                if (digit_count >= 20 && IS_DIGIT(output_str_equation[i])) //limitation to the size of a number
                {                                                          //solves the double overflow
                    output_str_equation.pop_back();
                    continue;
                }
                else if (digit_count == 0xFFFFFFFF)
                    digit_count = 20;
                else if (!IS_DIGIT(output_str_equation[i]))
                    digit_count = 0;

                try
                {
                    add_to_calculation(output_str_equation[i], last_input); //charcter is added to the calculation
                    if (output_str_equation[i] == 't' || output_str_equation[i] == 'c' || output_str_equation[i] == 's')
                        i += 2; //when sin, cos, tan are 3 character, two of them have to be skipped
                
                    if (output_str_result[0] == 'C' || output_str_result[0] == 'D' || output_str_result[0] == 'D')
                        break;
                }
                catch(const std::exception& e) //when something fails (division by 0, factoria of negative number..)
                {
                    output_str_result.clear();
                    output_str_result.assign(e.what());
                    add_position = output_str_equation.size();
                    return 1;
                }
                last_input = output_str_equation[i]; //the current input is stored to the last input, which is going to be used
            }                                        //in the next call of this function
            add_position = output_str_equation.size();
            add = false;
        }
    }
    else if (input_char == '=') //equal button was pressed
    {
        try
        {
            //add to calculation calculates the result, and then is reseted
            add_to_calculation('=', last_input);
        }
        catch(const std::exception& e)
        {
            output_str_result.clear();
            output_str_result.assign(e.what());
            return 1;
        }
        output_str_equation.clear();
        output_str_equation.assign(output_str_result);

        //resets the string control
        reset_equation_string_control();
        add_position = output_str_result.size(); //the add position has to be reseted
        add = false;
    }

    if (IS_DIGIT(input_char) || input_char == '!' || input_char == '=' || input_char == 'D' || input_char == 'N')
    // when some of these buttons were pressed, the calculated result has to be diplayed on the calculator
    {
        //output_str_result.clear();
        output_str_result.assign(std::to_string(result)); //the result is converted to string
        output_str_result.erase(output_str_result.find_last_not_of('0') + 1, std::string::npos); //trailing 0 are striped
        if (output_str_result.back() == '.') //id the last character is '.', then it is also striped
            output_str_result.pop_back();

    }

    if (!output_str_result.size()) //if the strig is empty, then 0 is displayed
       {
        output_str_result.push_back('0');
       } 

    if (output_str_equation.size() && add_position > 0)
        last_input = output_str_equation[add_position-1]; //the last input is stored, if it is possible
    else
        last_input = 0; //if not, it does not really matter, what the last input will be

    return 0;
}

void Logic::reset_equation_string_control()
{
    //variables, that holds data about the ongoing equation are reseted
    bracket_count = 0;
    op_count_strcnt = 0;
    position = NO_STATE;
}

void Logic::equation_string_control(std::string &current, char addition)
{
    static bool active_int_op; //for modulo as it can be used only with integers
    static bool active_minus;  //remembers if the current number is negative or not

    if (current.size() == 1 && current.back() == '0' && addition != '.')
    {
        current.pop_back();
    }

    //when the function is called for the first time or was reseted, it has to find the state of the current equation
    if (!current.size()) //empty current string
    {
        position = INTEGER;
        active_minus = false;
        active_int_op = false;
    }
    else if (!IS_DIGIT(current.back()) && position == NO_STATE) //this cleares invalid strings
    {
        current.clear();
        position = INTEGER;
    }
    else if (position == NO_STATE) //there is a number in the current string, but the string control was reseted
    {
        position = INTEGER;         //default sate
        for (int i = current.size()-1; i >= 0; i--)
        {
            if (current[i] == '.') //when it is floating point number, then the state is changed
            {
                position = DECIMAL_NUM;
                break;
            }
        }
        if (current[0] == '-') //if the number is negative
            active_minus = true;
        else
            active_minus = false;
    }

    switch(position) //the state from last call of this function is now used to detemin what has to happen it the currnet call
    {
        case INTEGER: //when digits before decimal point are added (the number is integer)
            op_count_strcnt = 0; //the number of operators is reseted
            if (IS_DIGIT(addition)) //another digit was added
                position = INTEGER;
            else if (addition == '-' && !current.size() && !active_minus) //when the first character added to the equation is minus
                active_minus = true;
            else if ((active_minus && current.size() == 1) || current.size() == 0) //special operators that can be added to the
            {                                                                      //beginnig of an equation
                if (addition == '(')
                {
                    position = O_BRACKET; //the state is changed for next call of the function
                    current.push_back('(');
                    bracket_count++; //number of not closed brackets is increased
                }
                else if (addition == 's')
                {
                    current += "sin";
                    position = GONIOOMETRY; //the state is changed for next call of the function
                }
                else if (addition == 't')
                {
                    current += "tan";
                    position = GONIOOMETRY; //the state is changed
                }
                else if (addition == 'c')
                {
                    current += "cos";
                    position = GONIOOMETRY; //the state is changed
                }
                
                    return;
            }
            else if (IS_OPERATOR(addition) && current.size()) //if there is already at least one digit operator can be added
            {
                if (current.back() == '-') //if the current.size() == 1 and the first character is minus, operator cannot be added
                    return;

                if (current.size() && current.back() == '.') //if the last character is a decimal dot, then it is deleted
                    current.pop_back();
                
                if (addition == '!' && active_minus) //if the current number is negative, then factorial is ignored
                {
                    return;
                }
                
                if (addition == '%') //if the added operator is % then the next number can be only an integer
                    active_int_op = true;
                else
                    active_int_op = false;

                position = OPERATOR; //the next position is set

                if (addition != '!') //the number of currently added oprators is increased, factorial is not included
                    op_count_strcnt++;
                
                active_minus = false;
            }
            else if (addition == '.' && !active_int_op) //if the floating point number can be added
            {
                if (current.size() == 0) //if the string is empty, the number cannot start with decimal dot
                    return;
                position = DECIMAL_NUM; //position is changed
            }
            else if (addition == 'D' && current.size()) //if the delete button was pressed
            {
                current.pop_back(); //one character is deleted

                if (current.size() == 0) //if the string is empty
                {
                    active_minus = false;
                    return;
                }

                if (current.back() == 's' || current.back() == 'n') //if the last character of the string after deleting is
                {                                                   // cos, sin or tan
                    position = GONIOOMETRY; 
                    return;
                }

                if (current.size() > 1 && IS_OPERATOR(current.back()))
                {
                    if (current.back() == '-' && (current[current.size() - 2] == '(' || current[current.size() - 2] == 'n' ||
                        current[current.size() - 2] == 's')) //if the deleted character was a digit and the number was negative,
                    {                                        //then it reamains in this position
                        position = INTEGER;
                        active_minus = true;
                        return;
                    }
                    //otherwise the position changes
                    position = OPERATOR;
                    op_count_strcnt = 1; //by default, there is at least one operator
                    if (IS_OPERATOR_NF(current[current.size()-2])) // but there can be two
                        op_count_strcnt = 2;
                }
                else if (current.back() == '(') //if the number was inside bracket
                {
                    position = O_BRACKET;
                }
                
                return; //no characters are added

            }
            else if (addition == ')' && bracket_count > 0) //if closed bracket can be added
            {
                bracket_count--; // number of open brackets is decreased
                position = C_BRACKET;
            }
            else if (addition == '(' && current.size() == 0) //if the first character added is a open bracket
            {
                bracket_count++;
                position = O_BRACKET;
            }
            else if (addition == 'N') //negate button was pressed
            {
                for (int i = current.size()-1; i >= 0; i--) //the string is searched from the end 
                {

                    if (IS_OPERATOR(current[i])) //if operator was found, that means that the current number ends
                    {
                        //if the number is not already negative
                        if (i > 0 && (IS_DIGIT(current[i-1]) || current[i-1] == ')' || current[i-1] == '!'))
                        {
                            active_minus = true;
                            current.insert(i+1, 1, '-'); //minus is inserted
                        }
                        //if the number is negative
                        else
                        {
                            active_minus = false;
                            current.erase(i, 1); //minus is deleted
                        }
                        
                        break;
                    }
                    else if ((current[i] == 'n' || current[i] == 's')) //ensures the negation after goniometric functions
                    {
                        current.insert(i+1, 1, '-'); 
                        break;
                    }
                    else if (current[i] == '(') // if the number is in bracket, it can also be negated
                    {
                        active_minus = true;    
                        current.insert(i+1, 1, '-');
                        break;
                    }
                    else if (i == 0) //or if the number has no operators in front, then it can also be negated
                    {
                        active_minus = true;    
                        current.insert(0, 1, '-');
                    }
                }
                return; //nothing else is added to the string
            }
            else //if something else is added
                return;

            current.push_back(addition); //the character is added to the string
            return;

        case DECIMAL_NUM: //when digits after decimal point are added
            op_count_strcnt = 0;

            //these characters cannot be added after a floating point number
            if (addition == '.' || addition == '(' || (addition == ')' && current.back() == '.'))
                return;

            //modulo and factorial cannot be used after floating point number
            if (addition == '+' || addition == '-' || addition == '*' || addition == '/' || addition == '^' || 
                addition == '?')
            {
                if (current.back() == '.') //if the last character is '.', then it is stripped
                    current.pop_back();
                position = OPERATOR;

                    op_count_strcnt++; //the operator count is increased
            }
            else if (addition == 'D') //deletion is pressed
            {
                if (current.back() == '.') //the state has to change when the deleted character is '.'
                    position = INTEGER;
                current.pop_back();
                return;
            }
            else if (addition == '!' || addition == '%') //modulo and factorial cannot be used after floating point number
                return;
            else if (addition == ')' && bracket_count > 0) //if it is possible to add closed bracket
            {
                bracket_count--;
                position = C_BRACKET;
            }
            else if (addition == 'N')
            {
                for (int i = current.size()-1; i >=0; i--) //the string is searched from the end 
                {

                    if (IS_OPERATOR(current[i])) //if operator was found, that means that the current number ends
                    {
                        //if the number is not already negative
                        if (i > 0 && (IS_DIGIT(current[i-1]) || current[i-1] == ')' || current[i-1] == '!'))
                        {
                            active_minus = true;
                            current.insert(i+1, 1, '-'); //minus is added
                        }
                        //if it is negative
                        else
                        {
                            active_minus = false; 
                            current.erase(i, 1); //minus is removed
                        }
                        
                        break;
                    }
                    else if ((current[i] == 'n' || current[i] == 's')) //if the number is as an argument of a goniometric function
                    {
                        current.insert(i+1, 1, '-');
                        break;
                    }
                    else if (current[i] == '(') // if the number is in bracket, it can also be negated
                    {
                        active_minus = true;    
                        current.insert(i+1, 1, '-');
                        break;
                    }
                    else if (i == 0) //if the equation starts with the negated number
                    {
                        active_minus = true;    
                        current.insert(0, 1, '-');
                    }
                }
                return;
            }
            else if (!IS_DIGIT(addition)) //if something other than digit and the cases above is added, 
                return;                  //then it is not added to the string
                
            current.push_back(addition); //character is added to the string
            return;


        case OPERATOR: //when multiple opperators are added
            //theses characters cannot be added after operator
            if (addition == '.' || (addition == ')' && current.back() != '!') || addition == 'N')
                return;

            if (IS_DIGIT(addition) && current.back() != '!') //when digit is added and the operator is not factorial
                position = INTEGER; //position is changed

            else if (IS_OPERATOR(addition)) //if more operators are added
            {
                if (addition == '!' && !IS_DIGIT(current.back())) //factorail can be added only after digit
                    return;

                op_count_strcnt++; 

                if ((addition != '-' && op_count_strcnt == 2)) //if the newly added operator is not minus, which represents the
                {                                              //the negation of the next number, than the operators are changed
                    current.pop_back(); //operator is removed
                    op_count_strcnt--;
                    active_int_op = false;
                }
                else if (op_count_strcnt == 2) //otherwise minus is activated
                    active_minus = true;

                if (op_count_strcnt == 3) //if there is already an operator and minus after that operator and another operator
                {                         //is added, then two has to be deleted first
                    current.pop_back(); //operator is removed
                    current.pop_back(); //operator is removed
                    op_count_strcnt = 1; //number of operators is reseted to 1
                    active_minus = false;
                    active_int_op = false;
                }

                if (addition == '%') //if modulo is added, the next number has to be integer
                    active_int_op = true;    
            }
            else if (addition == 'D') //when deleting
            {
                active_minus = false; //if there is a minus, which has the function of negation, it will be always deleted first
                current.pop_back(); //charcter is removed

                if (IS_DIGIT(current.back())) //if the last character of the string is digit
                {
                    active_int_op = false;  //modulo was surely removed
                    position = INTEGER;  //by default
                    for (int i = current.size()-2; i >= 0; i--)
                    {
                        if (current[i] == '.')
                        {
                            position = DECIMAL_NUM; //if the number was floating point
                            break;
                        }
                        else if (IS_OPERATOR(current[i])) //if the number wasn't floating point
                            break;
                    }
                }
                else if (current.back() == ')') 
                {
                    position = C_BRACKET;
                }
                    op_count_strcnt--; //number od operators is decreased

                return;
            }
            else if (addition == '(' && op_count_strcnt > 0) //open bracket can be added only after operator
            {
                bracket_count++;
                op_count_strcnt = 0;
                position = O_BRACKET;
            }
            //goniometric functions
            else if (addition == 's' && current.back() != '!')
            {
                current += "sin"; //3 charcters have to be inserted
                position = GONIOOMETRY;
                return;
            }
            else if (addition == 'c' && current.back() != '!')
            {
                current += "cos"; //3 charcters have to be inserted
                position = GONIOOMETRY;
                return;
            }
            else if (addition == 't' && current.back() != '!')
            {
                current += "tan"; //3 charcters have to be inserted
                position = GONIOOMETRY;
                return;
            }
            else if (addition == ')') //at this point the current.back() == !, so close bracket can be added 
            {
                bracket_count--;
                position = C_BRACKET;
            }
            else
                return;

            current.push_back(addition); //the charcter is inserted to the stirng
            return;
        
        case O_BRACKET:
            //charcters that cannot be added after open bracket
            if ((addition == ')' || IS_OPERATOR(addition) || addition == '.' || addition == 'N') && 
                (addition != '-' || current.back() == '-'))
                return;
            
            else if (IS_DIGIT(addition)) //when digit is added
            {
                position = INTEGER;
            } 
            else if (addition == '-') //minus that works as a negation is added
            {
                active_minus = true;
            }
            else if (addition == 'D') //when deleting
            {
                current.pop_back();
                bracket_count--; //by default the bracket count is decreased
                if (IS_OPERATOR(current.back())) //if the last not deleted character is an operator
                {
                    if (current.back() == '-' && IS_OPERATOR(current[current.size()-2])) //either there are two
                    {
                        op_count_strcnt = 2;
                    }
                    else
                        op_count_strcnt = 1; //or one
                    position = OPERATOR;
                }
                else if (current.back() == 'n' || current.back() == 's') //if the last not deleted charcter represents goniometric function
                    position = GONIOOMETRY;

                return;
            }
            else if (addition == '(') //if the addition is another open bracket
                bracket_count++;

            //when goniometric functions are added directly after open bracket
            else if (addition == 's')
            {
                current += "sin";
                position = GONIOOMETRY;
                return;
            }
            else if (addition == 'c')
            {
                current += "cos";
                position = GONIOOMETRY;
                return;
            }
            else if (addition == 't')
            {
                current += "tan";
                position = GONIOOMETRY;
                return;
            }
            else //if something else
                return;

            current.push_back(addition); //open bracket is added to the string
            break;

        case C_BRACKET:
            //these character cannot be added after a close bracket
            if (addition == '(' || addition == '.' || IS_DIGIT(addition))
                return;
            else if (addition == '!') //factorial is added
            {
                op_count_strcnt = 0;
                position = OPERATOR;
            }
            else if (IS_OPERATOR(addition)) //operator is added
            {
                active_minus = false;
                op_count_strcnt = 1;
                position = OPERATOR;
            }
            else if (addition == 'D') //when deleting
            {
                current.pop_back();
                bracket_count++; //number of open bracekts have to be increased
                
                if (current.back() == ')') //if there are multiple close brackets
                    return;

                else if (current.back() == '!') //if the last charcter is factorial, other operators cannot occure
                {
                    op_count_strcnt = 0;
                    position = OPERATOR;
                }
                else //when the last operator is a digit
                {
                    active_int_op = false;
                    position = INTEGER; //by default it is an integer
                    for (int i = current.size()-2; i >= 0; i--)
                    {
                        if (current[i] == '.') //if decimal dot occures, it is a floating point number
                        {
                            position = DECIMAL_NUM;
                            break;
                        }
                        else if (IS_OPERATOR(current[i]))
                            break;
                    }
                }
                
                return; //no characters are added
            }
            else if (addition == 'N') //negation
            {
                for (int i = current.size()-1, j = 0; i >= 0; i--) //the string is searched from the end
                {
                    if (current[i] == ')') //close brackets are skipped and the counter is increased
                        j++;
                    else if (j && current[i] == '(') //open brackets are skipped only when closed bracket was skipped before
                        j--;
                    else if (j == 0 && IS_OPERATOR(current[i])) //when operator occures
                    {
                        //when the number is positive, negation is added
                        if (i > 0 && (IS_DIGIT(current[i-1]) || current[i-1] == ')' || current[i-1] == '!'))
                        {
                            active_minus = true;
                            current.insert(i+1, 1, '-');
                        }
                        //when the number is negative, the negation is deleted
                        else
                        {
                            active_minus = false;
                            current.erase(i, 1);
                        }
                        
                        break;
                    }
                    else if (j == 0 && (current[i] == 'n' || current[i] == 's')) //neagtion inside goniometric function
                    {
                        current.insert(i+1, 1, '-');
                        break;
                    }
                    else if (j == 0 && current[i] == '(') //negation in front of open bracket
                    {
                        active_minus = true;    
                        current.insert(i+1, 1, '-');
                        return;
                    }

                    if (i == 0) //negation when the bracket is the first part of the equation 
                    {
                        active_minus = true;    
                        current.insert(i, 1, '-');
                    }
                }

                return;
            }
            else if (bracket_count && addition == ')') //the close bracket is added
                bracket_count--;
            else
                return;

            current.push_back(addition); //the character is added to the string
            break;
        
        case GONIOOMETRY:
            if (addition == '-' && current.back() != '-') //to create negative number inside the goniometric function
            {
                current.push_back('-');
                active_minus = true;
            }
            if (IS_DIGIT(addition)) //digit is added
            {
                current.push_back(addition);
                position = INTEGER;
            }
            if (addition == '(') //open bracket is added
            {
                bracket_count++;
                position = O_BRACKET;
                current.push_back('(');
            }
            if (addition == 'D')
            {
                current.erase(current.end()-3, current.end()); // 3 characters have to be deleted
                if (current.size()) 
                {
                    if (current.size() == 1 && current.back() == '-') //when there is only one character and it is minus
                    {                                                 //then the position is going to be a negative integer
                        position = INTEGER; 
                        active_minus = true;
                        return;
                    }
                    if (IS_OPERATOR_NF(current.back())) //if the currently last character is an operator,
                    {                                   //then the number of oprators is loaded
                        op_count_strcnt = 1;
                        if (IS_OPERATOR_NF(current[current.size() - 2]))
                            op_count_strcnt = 2;
                        position = OPERATOR;
                        return;
                    }
                }
            }

            break;

        case NO_STATE: //should not happen
            return;
    }
}

void Logic::erase_equation()
{
    //erases the variables that are used for the current ongoing equation and sets them to the default values
    result = 0;
    result_parts.clear();
    result_parts_op.clear();
    result_parts_state.clear();
    result_parts_op.push_back(0);
    result_parts.push_back(0);
    result_parts_state.push_back(START_STATE);
    reset_equation_string_control(); //the equation control also has to be reseted
}

Stddev_function::Stddev_function()
{
    data_array = (long double*)malloc(BLOCK_SIZE*sizeof(long double));;
    total_addition = 0;
    loaded_nums = 0;
}

Stddev_function::~Stddev_function()
{
    delete(data_array);
    data_array = NULL;
}

int Stddev_function::load_function() 
{
    short int success_load = 0;
    unsigned block_count = 1;
    while((success_load = scanf("%Lf", &data_array[loaded_nums])) != EOF && success_load != 0) //loading data til EOF or error
    {
        if(loaded_nums == block_count*BLOCK_SIZE-1)  
        {
            block_count++;
            long double *resize =(long double*) realloc(data_array,block_count*BLOCK_SIZE*sizeof(long double)); //increasing the size of allocated memory 
            if(resize != NULL)
                data_array = resize;
            else
                return -1; 
 
        }
        total_addition += data_array[loaded_nums];
        loaded_nums++;
    }

    if (loaded_nums < 2)
    {
        std::cerr << "stddev: Enter at least two numbers." << std::endl;
        return -1;
    }

    if(!success_load)
        return -1;
    else
        return 1; 
}

long double Stddev_function::get_summation()
{
    long double mean = get_mean();
    long double summation = 0;
    for(unsigned i=0; i < loaded_nums; i++)
    {
         summation += npow(data_array[i] - mean, 2);
    }
    return summation;   
}

long double Stddev_function::get_mean()
{
    return total_addition/loaded_nums;
}

long double Stddev_function::calculate_stddev()
{
    return nroot(get_summation()/(loaded_nums-1),2);   
}
long double* Stddev_function::get_data_pointer()
{
    return data_array;
}
