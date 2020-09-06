/**
 * @file our_math.h
 * @author Mihola David
 * @author Foltyn Lukas
 * @date 27.02.2019
 * @copyright ©Pied Piper
 * @brief Header file containing definition of inline functions for basic arithmetics like addition, subtraction, division, multiplication as well as more advanced functions for calculating factorial, n-power, n-root, cosx, sinx, tanx. Also contains a declaration of xpow function.
*/
#ifndef __OUR_MATH_H__
#define __OUR_MATH_H__ 

#include <cmath>
#include <math.h>
#include <functional>
#include <stdexcept>

/**
 *@def XPOW_EPS
 *@brief deviation for x-power functions
 *to calculate decimal part as well as fraction part
*/
#define XPOW_EPS 1e-4

/**
 *@def GONIO_EPS
 *@brief deviation for goniometric functions
*/
#define GONIO_EPS 1e-5

/**
 *@def ACCURACY_SIN
 *@brief limit for loop in sinx fucntion, 
 *where cosx is accurate in 5 decimal places at minimum
*/
#define ACCURACY_SIN 26

/**
 *@def ACCURACY_COS
 *@brief limit for loop in cosx function, 
 *where cosx is accurate in 5 decimal places at minimum
*/
#define ACCURACY_COS 25

/**
 *@def PI
 *@brief constant for calculatin sinx, cosx and tanx
*/
#define PI 3.14159265358979323846

/**
 *@def EPS
 *@brief deviation for npower, xpower, nroot to get quite accurate result
*/
#define EPS 1e-10

/**
 * @brief calculates addition of given numbers
 * @param x first number for addition
 * @param y second number for addition
 * @return addition of given numbers x,y
 */
inline long double add (long double x, long double y)
{
    return x + y;
}

/**
 * @brief calculates subtraction of given numbers
 * @param x number being subtracted from
 * @param y number that is subtracted
 * @return subtraction of given numbers x,y
 */
inline long double sub (long double x, long double y)
{
    return x - y;
}
/**
 * @brief claculates multiplication of given numbers
 * @param x first number for multiplication
 * @param y second number for multiplication
 * @return multiplication of given numbers x,y
 */
inline long double mul (long double x, long double y)
{
    return x * y;
}
/**
 * @brief calculates division of given numbers
 * @param x number that is divided
 * @param y number that divides
 * @return divison of given numbers x,y
 */
inline long double div_ (long double x, long double y)
{
    if (y == 0)
        throw std::runtime_error("Division by 0");
    return x / y;
}

/**
 * @brief calculates a factorial of input number
 * @param n number to calculate factorial from
 * @return factorial of the input number
 */
inline long double factorial (int n)
{
    if (n < 0)
        throw std::runtime_error("Factorial of negative number.");

    if (n == 0 || n == 1 )
        return 1;

    //if (n > 20)
      //  throw std::runtime_error("Too large number for factorial.");

    long double x = (long double)n;
    for (unsigned i = n; i > 1; --i, x*= i);

    return x;
}

/**
 * @brief calculates the power of input number, the number can be powerd only to a natural number
 * @param x number to be powered
 * @param n the exponent
 * @return number powered by the exponent
 */
inline long double npow (long double x, long unsigned n)
{
    if (n == 0)
        return 1;
    long double hold = x;
    if (x >= 1 - EPS && x <= 1 + EPS)
        return x;
    while (--n) x *= hold;

    return x;
}


/**
 * @brief calculates the nth-root of input number, the number can be rooted only to a natural number
 * @param x number to be rooted
 * @param n the exponent
 * @return the nth-root of a number
 */
inline long double nroot (long double x, long unsigned n)
{
    if (n == 0)
        return 1;
    if (n == 1)
        return x;
    if (x >= 1 - EPS && x <= 1 + EPS)
        return 1;

    if (x < 0 && !(n&1))
    {
        throw std::runtime_error("Cannot root this.");
        return -1;
    }

    if (x >= -EPS && x <= EPS)
        return 0;

    //aproximation of the result
    long double delta = x;
    long unsigned i = 1;

    while ((delta /= 10) > 1 && ++i);

    long double guess = 1;
    if (i / n)
    {
        for (long unsigned j = 0; j < i/n; j++)
            guess *= 10;

        guess *= i % n + 1;
    }
    //end of approximation

    delta = 0;

    do
    {
        guess += delta;
        delta = (((x/npow(guess, (n-1)))-guess)/n);
    }
    while(delta > EPS || delta < -EPS);
    return guess+delta;
}

/**
 * @brief calculates calculates power of a floating point number powered by floating point number (also works as nroot)
 * @param base the number to be powered
 * @param exponent the exponent on which the number is powerd
 * @return result of power the base to it's exponent
 */
long double xpow (long double base, long double exponent);

/**
 * @brief calculates sinus value of input number given in degrees
 * @param x angle in degrees
 * @return the numerical value of angle
 */
inline long double sinx (double x)
{
    while(x>=360)
        x-=360;
    while(x<=-360)
        x+=360;

    //values for 90, 180, 270, 360 degrees
    long test = (long)x;
    if (test == 90)
        return 1;
    else if (test == 270)
        return -1;
    else if (test == 0 || test == 180)
        return 0;

    double radians=x*PI/180;
    long double result,previous_result,temp;
    result=temp=radians;
    for(unsigned i=2;i<ACCURACY_SIN;i+=2)
    {
        temp=temp*(-1)*radians*radians/(i*(i+1));
        previous_result=result;
        result+=temp;
        if(fabs(result-previous_result)<GONIO_EPS)
            break;
    }
    return result;
}
#if 0
inline long double bhaskara_approximation_sin (double x)
{
    while(x>=360)
        x-=360;
    while(x<=-360)
        x+=360;
    return (4*x*(180-x))/(40500-x*(180-x));
}
#endif

/**
 * @brief calculates cosinus value of input number given in degrees
 * @param x angle in degrees
 * @return the numerical value of angle
 */
inline long double cosx (double x)
{
    while(x>=360)
        x-=360;
    while(x<=-360)
        x+=360;

    long test = (long)x;
    if (test == 0)
        return 1;
    else if (test == 180)
        return -1;
    else if (test == 90 || test == 270)
        return 0;

    double radians=x*PI/180;
    long double result,previous_result,temp;
    result=temp=1; 
    for(unsigned i = 1; i < ACCURACY_COS; i += 2)
    {
        temp=temp*(-1)*radians*radians/(i*(i+1));
        previous_result=result;
        result+=temp;
        if(fabs(result-previous_result)<GONIO_EPS)
            break;
    }
    return result;
}
#if 0
inline long double bhaskara_approximation_cos (double x)
{
    while(x>=360)
        x-=360;
    while(x<=-360)
        x+=360;
    return ((-5*pow(x,2))/(32400+pow(x,2)))+1;
}
#endif

/** 
 * @brief calculates tangens value of input number given in degrees
 * @param x angle in degrees
 * @return the numerical value of angle 
 */
inline long double tanx (double x)
{
   if(!(fmod(x,90)) && (fmod(x,180)))
        return 0.0;
   return sinx(x)/cosx(x);
}
#if 0
inline long double bhaskara_approximation_tan (double x)
{
    if(!(fmod(x,90)) && (fmod(x,180)))
        return 0.0;
    return bhaskara_approximation_sin(x)/bhaskara_approximation_cos(x);
}
#endif

#endif //__OUR_MATH_H__
