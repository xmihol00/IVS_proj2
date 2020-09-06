/**
 * @file tests.h
 * @author Mihola David
 * @author Foltyn Lukas
 * @author Sokolovskii Vladislav
 * @date 27.02.2019
 * @copyright ©Pied Piper
 * @brief Header file containing test classes with declarations of their test functions for logic.cpp and our_math.cpp
*/

#include "gtest/gtest.h"
#include "logic.h"

/**
 *@def TEST_EPS
 *@brief deviation for testing calculation from string to long double
*/
#define TEST_EPS 1e-3

/**
 *@def ADD_EQUATION_WITH_RESULT_STS(EQUATION_STR, RESULT_STR)
 *@brief macro that takes "string" equation which is calculated and compared with
 *its expected "string" result given as second parameter and return
 *true if matched, otherwise false is returned      
*/
#define ADD_EQUATION_WITH_RESULT_STS(EQUATION_STR, RESULT_STR)\
    Logic test_logic;\
    std::string result_hold;\
    test_logic.calculate(((std::string)EQUATION_STR), result_hold);\
    EXPECT_EQ(result_hold, ((std::string)RESULT_STR));

/**
 *@def ADD_EQUATION_WITH_RESULT_STD(EQUATION_STR, RESULT_LD)
 *@brief macro that takes "string" equation which is calculated and compared with
 *its expected long double result given as second parameter and return
 *true if matched, otherwise false is returned      
*/
#define ADD_EQUATION_WITH_RESULT_STD(EQUATION_STR, RESULT_LD)\
    Logic test_logic;\
    long double result_hold;\
    test_logic.calculate(((std::string)EQUATION_STR), result_hold);\
    EXPECT_TRUE((RESULT_LD) >= result_hold - TEST_EPS && (RESULT_LD) <= result_hold + TEST_EPS);\

/**
 *@def NUMS
 *@brief subsitution for vector of number(data type - double)
*/
#define NUMS (std::vector<double>)

/**
 *@def OPS
 *@brief substitution for vector of chars 
*/
#define OPS (std::vector<char>)

/**
 *@def YES
 *@brief substitution for true in test functions
*/
#define YES true

/**
 *@def NO
 *@brief substitution for false in test functions
*/
#define NO false

/**
*@class Nroot_test
*@brief class that tests the Nroot function
*/
class Nroot_test: public ::testing::Test
{
    protected:
        /**
	 *@brief function used in tests to test the nroot function from our_math library
	 *@param x base, which is rooted
	 *@powerd_to the exponent of the root
	 *@expected_result result which should be calculated by the nroot function
	 *@fail_expected true when the tester expects the nroot function to fail (i.e. negative number is rooted to an even exponent) 
	 *@return true on success (result matches the expected_result or when fail is expected and function throws an exception), otherwise false
	 */
	bool root_test(long double x, unsigned exponent, long double expected_result, bool fail_expected);
};

/**
*@class Input_control
*@brief class that tests the equation_string_control function
*/
class Input_control: public ::testing::Test
{
    protected:
        Logic test;
        std::string output;
	/**
	 *@brief function used to input charcters one by one to the equation_string_control function
	 *@param input_str string needed to be parsed
	 *@param expected_output_str the expected output of the equation_string_control
	 *@return true on success (equation_string_control output matches the expected_output_str), otherwise false
	 */
        bool parse_string (std::string input_str, std::string expected_output_str);
};

/**
*@class Real_time_calc
*@brief class that tests the calculations of the real time calculator
*/
class Real_time_calc: public ::testing::Test
{
    protected:
        Logic test;
        std::string result;
        /**
	    *@brief function gets an equation as an input and then tests the correctness of results at certain positions
	    *@param calculation_string equation that is being calculated
	    *@param comparison_offsets positions in equation, where we want to know the result, indexing starts from zero 
        *@param intercount_results results, that are expected at positions given by comparison_offsets 
	    *@return true on success - expected results matche the results of calculator, otherwise false is returned
	    */
        void test_real_time_calculation(std::string calculation_string, 
                                     std::vector<unsigned> comparison_offsets, std::vector<long double> intercount_results);
};

/**
*@class Factorial_tests
*@brief class that tests the factorial calculation
*/
class Factorial_tests: public ::testing::Test
{
    protected: 
        /**
	    *@brief function that compares calculation of factorial with expected result
        *@pre expected result has to be accurate to 5 decimal digits
        *@param num number from which factorial is calculated
	    *@param expected_result number, that is expected to be correct result of calculation
        *@param fail_expected boolean, set to true if fail of calc is expected (too large number), else set to to false
	    *@return true on success - expected_result matches the result of calculator or
        * calculation fails while fail_expected is set to true, otherwise false is returned
	    */
        bool fact_test(long unsigned num, long unsigned expected_result, bool fail_expected);
};

/**
*@class Npow_test
*@brief class that tests the N-power calculation(N - positive integer)
*/
class Npow_test: public ::testing::Test
{
    protected:
        /**
	    *@brief function that compares calculation of N-power with expected result
        *@pre expected result has to be accurate to 5 decimal digits
        *@param num number from which the N-power is calculated
        *@param exp exponent of num variable, must be positive integer
	    *@param expected_result number, that is expected to be correct result of calculation
        *@param fail_expected boolean, set to true if fail of calc is expected (too large number), else set to to false
	    *@return true on success - expected_result matches the result of calculator or
        * calculation fails while fail_expected is set to true, otherwise false is returned
	    */
        bool pow_test(long double num, long unsigned exp, long double expected_result, bool fail_expected);
};

/**
*@class Xpow_test
*@brief class that tests the X-power calculation(X - long double)
*/
class Xpow_test: public ::testing::Test
{
    protected:
        /**
	    *@brief function that compares calculation of X-power with expected result
        *@pre expected result has to be accurate to 5 decimal digits
        *@param num number from which the X-power is calculated
        *@param exp exponent of num variable
	    *@param expected_result number, that is expected to be correct result of calculation
        *@param fail_expected boolean, set to true if fail of calculation is expected (too large number), else set to to false
	    *@return true on success - expected_result matches the result of calculator or
        * calculation fails while fail_expected is set to true, otherwise false is returned
	    */
        bool pow_test(long double num, long double exp, long double expected_result, bool fail_expected);
};

/**
*@class Nsin_test
*@brief class that tests sinx calculation
*/
class Nsin_test: public ::testing::Test
{
    protected:
        /**
	    *@brief function that compares calculation of sinx with expected result
        *@pre expected result has to be accurate to 5 decimal digits
        *@pre sinx expects value in degrees
        *@param val number from which the sinx is calculated (given in degrees)
	    *@param expected_result number, that is expected to be correct result of calculation
        *@param fail_expected boolean, set to true if fail of calculation is expected (values where function does not exist), else set to to false
	    *@return true on success - expected_result matches the result of calculator or
        * calculation fails while fail_expected is set to true, otherwise false is returned
	    */
        bool sinx_test(double val, long double expected_result, bool fail_expected);
};

/**
*@class Ncos_test
*@brief class that tests cosx calculation
*/
class Ncos_test: public ::testing::Test
{
    protected:
        /**
	    *@brief function that compares calculation of cosx with expected result given user
        *@pre expected result has to be accurate to 5 decimal digits
        *@pre cosx expects value in degrees
        *@param val number from which the cosx is calculated (given in degrees)
	    *@param expected_result number, that is expected to be correct result of calculation
        *@param fail_expected boolean, set to true if fail of calculation is expected (values where function does not exist), else set to to false
	    *@return true on success - expected_result matches the result of calculator or
        * calculation fails while fail_expected is set to true, otherwise false is returned
	    */
        bool cosx_test(long double val, long double expected_result, bool fail_expected);
};

/**
*@class Ntan_test
*@brief class that tests tanx calculation
*/
class Ntan_test: public ::testing::Test
{
    protected:
        /**
	    *@brief function that compares calculation of tanx with expected result given user, uses both sinx and cosx
        *@pre expected result has to be accurate to 5 decimal digits
        *@pre tanx expects value in degrees
        *@param val number from which the tanx is calculated (given in degrees)
	    *@param expected_result number, that is expected to be correct result of calculation
        *@param fail_expected boolean, set to true if fail of calculation is expected (values where function does not exist), else set to to false
	    *@return true on success - expected_result matches the result of calculator or
        * calculation fails while fail_expected is set to true, otherwise false is returned
	    */
        bool tanx_test(double val, long double expected_result, bool fail_expected);
};

