/**
 * @file test_mock_stub.cpp
 * @author Mihola David
 * @author Sokolovskii Vladislav
 * @author Foltyn Lukas
 * @copyright ©Pied Piper
 * @brief Source file containing the definitions of test functions, that test the functioanlity of math library
*/
#include "../include/tests.h"

//expected result has to be accurate to 5 decimal digits
bool Nroot_test::root_test(long double x, unsigned exponent, long double expected_result, bool fail_expected)
{
    long double nroot_result;
    try
    {
        nroot_result = nroot(x, exponent);
        if (nroot_result >= expected_result - TEST_EPS && nroot_result <= expected_result + TEST_EPS)
            return 1;
        else
        {
            fprintf(stderr, "%Lf\n", nroot_result);
            return 0;
        }
    }
    catch(const std::exception& e)
    {
        return fail_expected;
    }
}

bool Input_control::parse_string (std::string input_str, std::string expected_output_str)
{
    for (unsigned i = 0; i < input_str.size(); i++)
    {
        test.equation_string_control(output, input_str[i]);
    }
    return (output == expected_output_str)?(1):(fprintf(stderr, "%s\n", output.c_str()), 0);
}


/**
 * @brief function that adds to the real-time calculation characters from string by one and checks at given ofsets,
 *        if the intercount result is correct
 * @param calculation_string an equation that will be parsed, so it can contain random characters
 * @param comparison_offsets vector with the possitions where, the intercout result is going to be checked
 *                          (the index of the string where you want to check the intercount result)
 * @param intercount_results vector with results to be checked
 * */
void Real_time_calc::test_real_time_calculation(std::string calculation_string, 
                             std::vector<unsigned> comparison_offsets, std::vector<long double> intercount_results)
{
    std::string dummy;
    if (calculation_string.size() == 0 || comparison_offsets.size() == 0 || intercount_results.size() == 0)
    {
        fprintf(stderr, "Invalid parameters\n");
        return;
    }

    test.real_time_calculation('C', result, dummy);

    for (unsigned i = 0, j = 0, k = comparison_offsets[j]; i < calculation_string.size(); i++)
    {
        test.real_time_calculation(calculation_string[i], result, dummy);
        if (intercount_results.size() > j && k-- == 0)
        {
            if (!(std::stold(result) >= (intercount_results[j] - TEST_EPS) && 
                        std::stold(result) <= (intercount_results[j] + TEST_EPS)))
            {
                fprintf(stderr, "False result at position: %u. Value is: %s, expected: %Lf\n",  comparison_offsets[j],
                        result.c_str(), intercount_results[j]);
                EXPECT_TRUE(false);
            }
            if (comparison_offsets.size() > j + 1)
                k = comparison_offsets[j+1] - comparison_offsets[j] - 1;
            
            j++;
        }
    }
}

bool Factorial_tests::fact_test(long unsigned num, long unsigned expected_result, bool fail_expected)
{
    long unsigned fact_result;
    try
    {
        fact_result =  factorial(num);
        if (fact_result == expected_result)
            return 1;
        else
        {
            fprintf(stderr, "%lu\n", fact_result);
            return 0;
        }
    }
    catch(const std::exception& e)
    {
        return fail_expected;
    }
}

bool Npow_test::pow_test(long double num, long unsigned exp, long double expected_result, bool fail_expected)
{
    long double npow_result;
    try
    {
        npow_result = pow(num, exp);
        if (npow_result >= expected_result - TEST_EPS && npow_result <= expected_result + TEST_EPS)
            return 1;
        else
        {
            fprintf(stderr, "%Lf\n", npow_result);
            return 0;
        }
    }
    catch(const std::exception& e)
    {
        return fail_expected;
    }
}

bool Xpow_test::pow_test(long double num, long double exp, long double expected_result, bool fail_expected)
{
    long double npow_result;
    try
    {
        npow_result = xpow(num, exp);
        if (npow_result >= expected_result - TEST_EPS && npow_result <= expected_result + TEST_EPS)
            return 1;
        else
        {
            fprintf(stderr, "%Lf\n", npow_result);
            return 0;
        }
    }
    catch(const std::exception& e)
    {
        return fail_expected;
    }
}

//SINX EXPECTS VALUE IN DEGREES!!!
bool Nsin_test::sinx_test(double val, long double expected_result, bool fail_expected)
{
    if (expected_result > 1 || expected_result < -1)
        return fail_expected;
    
    long double sinx_result;
    try
    {
        sinx_result = sinx(val);
        if (sinx_result >= expected_result - TEST_EPS && sinx_result <= expected_result + TEST_EPS)
                return 1;
        else
        {
                fprintf(stderr, "%Lf\n", sinx_result);
                return 0;
        }
    }
    catch(const std::exception& e)
    {
        return fail_expected;
    }
}

bool Ncos_test::cosx_test(long double val, long double expected_result, bool fail_expected)
{
    if (expected_result > 1 || expected_result < -1)
        return fail_expected;
    
    long double cosx_result;
    try
    {
        cosx_result = cosx(val);
        if (cosx_result >= expected_result - TEST_EPS && cosx_result <= expected_result + TEST_EPS)
                return 1;
        else
        {
                fprintf(stderr, "%Lf\n", cosx_result);
                return 0;
        }
    }
    catch(const std::exception& e)
    {
        return fail_expected;
    }
}

bool Ntan_test::tanx_test(double val, long double expected_result, bool fail_expected)
{
    if (cos(val) == 0)
        return fail_expected;
    
    long double tanx_result;
    try
    {
        tanx_result = tanx(val);
        if (tanx_result >= expected_result - TEST_EPS && tanx_result <= expected_result + TEST_EPS)
                return 1;
        else
        {
                fprintf(stderr, "%Lf\n", tanx_result);
                return 0;
        }
    }
    catch(const std::exception& e)
    {
        return fail_expected;
    }
}
