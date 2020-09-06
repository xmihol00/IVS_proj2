/**
 * @file our_math.cpp
 * @author Mihola David
 * @author Foltyn Lukas
 * @copyright ©Pied Piper
 * @brief This source file contains extern declarations of inline functions and definition of xpow function from the math library.
*/

#include "../include/our_math.h"

extern long double add (long double x, long double y);

extern long double sub (long double x, long double y);

extern long double mul (long double x, long double y);

extern long double div_ (long double x, long double y);

extern long double cosx (double x);

extern long double sinx (double x);

extern long double tanx (double x);

extern long double npow (long double x, long unsigned n);

extern long double nroot (long double x, long unsigned n);

extern long double factorial (int n);

long double xpow (long double base, long double exponent)
{
    if (base < EPS && base > -EPS)
        return 0;

    if (exponent < EPS && exponent > -EPS)
        return 1;

    if (exponent >= 1 - EPS && exponent <= 1 + EPS)
        return base;

    //switching the values when exponent is negative
    if (exponent < 0)
    {
        base = 1 / base;
        exponent = -exponent;
    }

    //separating the number to it's natural part and decimal part
    long natural = (long)exponent;
    long double rest = exponent - natural;
    long double tmp = base;
    
    //calculating the npower of natural part
    if (natural)
        while(--natural)
            base *= tmp;
    else
        base = 1;


    //calculating the power of deciaml part, if the decimal part is large enough
    if (rest > XPOW_EPS - 0.00001)
    {
        // number^0.xxxx.. can be caulculated as number^(top/bot) == pow(nroot(number, bot), top), where top/bot = 0.xxxx.., 
        long double top = 1;
        long double bot = 2;
        long double delta = rest - 0.5;

        // approximating the fraction, f.e. 0.65 = 13/20
        while (delta > XPOW_EPS - 0.00001 || delta < -XPOW_EPS + 0.00001)
        {
            if (delta > 0)
                top += 1;
            else
                bot += 1;
            
            delta = rest - (top / bot);
        }
        //calculatig the nroot

        if (tmp < 0 && !((long unsigned)bot & 1))
        {
            throw std::runtime_error("Cannot calculate this.");
            return -1;
        }

        long double n_res = tmp = nroot(tmp, bot);
        //calculating the power of the rooted number
        while (--top)
            n_res *= tmp;
        
        //multiplying the natural part by the decial part 
        return base * n_res;
    }
    else
        return base;
        
    return 0;
}
