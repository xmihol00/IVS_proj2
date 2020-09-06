/**
 * @file tests.cpp
 * @author Mihola David
 * @author Sokolovskii Vladislav
 * @author Foltyn Lukas
 * @copyright ©Pied Piper
 * @brief Source file containing tests for each part of the math library.
 */


#include "../include/tests.h"

//Calculation str to str tests ======================================================================

TEST(Logic_test2, Calculation_str_to_str1)
{
    ADD_EQUATION_WITH_RESULT_STS(("2+3*-6/2+5"), ("-2"));
}

TEST(Logic_test2, Calculation_str_to_str2)
{
    ADD_EQUATION_WITH_RESULT_STS(("12+3.5^6*1.2-14*1"), ("2203.91875"));
}

TEST(Logic_test2, Calculation_str_to_str3)
{
    ADD_EQUATION_WITH_RESULT_STS(("3+8*2/0+5"), ("Division by 0."));
}

TEST(Logic_test2, Calculation_str_to_str4)
{
    ADD_EQUATION_WITH_RESULT_STS(("3+-8?4"), ("Cannot root this."));
}

TEST(Logic_test2, Calculation_str_to_str6)
{
    ADD_EQUATION_WITH_RESULT_STS(("2+8-15+-18"), ("-23"));
}

TEST(Logic_test2, Calculation_str_to_str7)
{
    ADD_EQUATION_WITH_RESULT_STS(("2*-4+5*2/2"), ("-3"));
}

TEST(Logic_test2, Calculation_str_to_str8)
{
    ADD_EQUATION_WITH_RESULT_STS(("-4-3-9-8+-8/4"), ("-26"));
}

TEST(Logic_test2, Calculation_str_to_str9)
{
    ADD_EQUATION_WITH_RESULT_STS(("15^2+2.5*8-4!"), ("221"));
}

TEST(Logic_test2, Calculation_str_to_str10)
{
    ADD_EQUATION_WITH_RESULT_STS(("16?4*3-4.35^1/2!"), ("3.825"));
}

TEST(Logic_test2, Calculation_str_to_str11)
{
    ADD_EQUATION_WITH_RESULT_STS(("2!-2!+4!*4!-2*576/2!"), ("0"));
}

TEST(Logic_test2, Calculation_str_to_str12)
{
    ADD_EQUATION_WITH_RESULT_STS(("4?2*8?3*16?4*32?5-5!"), ("-104"));
}

TEST(Logic_test2, Calculation_str_to_str13)
{
    ADD_EQUATION_WITH_RESULT_STS(("3!^2*3-8/4"), ("106"));
}

TEST(Logic_test2, Calculation_str_to_str14)
{
    ADD_EQUATION_WITH_RESULT_STS(("8.45*4-45+2/5/54*5!+-9+-8?8+66*5"), ("Cannot root this."));
}

TEST(Logic_test2, Calculation_str_to_str15)
{
    ADD_EQUATION_WITH_RESULT_STS(("6/6+6*6-2*4^2!"), ("5"));
}

TEST(Logic_test2, Calculation_str_to_str16)
{
    ADD_EQUATION_WITH_RESULT_STS(("18^2?2+18*18/18^2?2-3!^3"), ("-180"));
}

TEST(Logic_test2, Calculation_str_to_str17)
{
    ADD_EQUATION_WITH_RESULT_STS(("0!*125?3+-32?5+2*2!+2*8.5"), ("24"));
}

TEST(Logic_test2, Calculation_str_to_str18)
{
    ADD_EQUATION_WITH_RESULT_STS(("8!-45^23*12?2/0+-4!?3"), ("Division by 0."));
}

TEST(Logic_test2, Calculation_str_to_str19)
{
    ADD_EQUATION_WITH_RESULT_STS(("8*45*0/45*5!*4?2^12"), ("0"));
}

TEST(Logic_test2, Calculation_str_to_str20)
{
    ADD_EQUATION_WITH_RESULT_STS(("5!^3!+10*2^3/8--100-250^5*4+963258741"), ("-919302741149"));
}

TEST(Logic_test2, Calculation_str_to_str21)
{
    ADD_EQUATION_WITH_RESULT_STS(("2*(4+5)"), ("18"));
}

TEST(Logic_test2, Calculation_str_to_str22)
{
    ADD_EQUATION_WITH_RESULT_STS(("3+2*(4+5)^2"), ("165"));
}

TEST(Logic_test2, Calculation_str_to_str23)
{
    ADD_EQUATION_WITH_RESULT_STS(("3+2*(4+5)^2-65"), ("100"));
}

TEST(Logic_test2, Calculation_str_to_str24)
{
    //it is necessary to put sin cos and tan i to this equations, the don't go threw the string check mechanism
    ADD_EQUATION_WITH_RESULT_STS(("2*((2.5+2.5)-2*(sin90+(cos(0)))+-1*4)^2+2"), ("20"));
}

TEST(Logic_test2, Calculation_str_to_str25)
{
    ADD_EQUATION_WITH_RESULT_STS(("(((5)*2+-15/(1+2^2)+3+-(2*2^2+2))"), ("0"));
}

TEST(Logic_test2, Calculation_str_to_str26)
{
    ADD_EQUATION_WITH_RESULT_STS(("2*(2-((5)*2+-15/(1+2^2)+3+-(2*2^2+2)))-3"), ("1"));
}

TEST(Logic_test2, Calculation_str_to_str27)
{
    ADD_EQUATION_WITH_RESULT_STS(("10+-(sin90*2-cos0*4+2*(-sin90+6))*2"), ("-6"));
}

//End of Calculation str to str tests ======================================================================


//Calculation str to long double tests ======================================================================

TEST(Logic_test3, Calculation_str_to_ld1)
{
    ADD_EQUATION_WITH_RESULT_STD(("5!^3!+10*2^3/8--100-250^5*4+963258741"), (-919302741149));
}

TEST(Logic_test3, Calculation_str_to_ld2)
{
    ADD_EQUATION_WITH_RESULT_STD(("3.24+5.86*2.2/3*2^6/16?4+25/5*2"), (150.754666));
}

TEST(Logic_test3, Calculation_str_to_ld3)
{
    ADD_EQUATION_WITH_RESULT_STD(("1024?2/2/2/2*2^7+512"), (1024));
}

TEST(Logic_test3, Calculation_str_to_ld4)
{
    ADD_EQUATION_WITH_RESULT_STD(("-4.3*123+10^3*(12/-3.3)+0.7"), (-4164.56363636));
}

TEST(Logic_test3, Calculation_str_to_ld5)
{
    ADD_EQUATION_WITH_RESULT_STD(("(9!^0.5-14*2*(14488%300)^2)?5"), (-11.6676402745))
}

TEST(Logic_test3, Calculation_str_to_ld6)
{
    ADD_EQUATION_WITH_RESULT_STD(("-0.13*11-15*(13+69)-1228.57/12"), (-1333.81083333));
}

TEST(Logic_test3, Calculation_str_to_ld7)
{
    ADD_EQUATION_WITH_RESULT_STD(("(((543-122%2*2+(14+8)-540))"), (25));
}

TEST(Logic_test3, Calculation_str_to_ld8)
{
    ADD_EQUATION_WITH_RESULT_STD(("(((2)N+13N+20)!-100)?2"), (4.472135955));
}

TEST(Logic_test3, Calculation_str_to_ld9)
{
    ADD_EQUATION_WITH_RESULT_STD(("((10^0.3-16+22*2.5)/120+1.7)N"), (-2.04162718596));
}

TEST(Logic_test3, Calculation_str_to_ld10)
{
    ADD_EQUATION_WITH_RESULT_STD(("(144^(1/2)/3+2)!--333"), (1053));
}
//End of Calculation str to long double tests ======================================================================

//Input prasing tests ==============================================================================================

TEST_F(Input_control, Input_parsing1)
{
    EXPECT_TRUE(parse_string("2+2-4", "2+2-4"));
}

TEST_F(Input_control, Input_parsing2)
{
    EXPECT_TRUE(parse_string("2+---2.5!+*/0.25*+-6!+5^6.62", "2--2.5/0.25+-6+5^6.62"));
}

TEST_F(Input_control, Input_parsing3)
{
    EXPECT_TRUE(parse_string("2+*!+-*-5.5^-5!!!!", "2*-5.5^-5"));
}

TEST_F(Input_control, Input_parsing4)
{
    EXPECT_TRUE(parse_string("89+5.3%5+++**/-85!!!!^000.25", "89+5.35/-85^000.25"));
}

TEST_F(Input_control, Input_parsing5)
{
    EXPECT_TRUE(parse_string("((--+*/*-85+56N))", "((-85+-56))"));
}
//End of Input prasing tests ==============================================================================================


//Nroot tests ==============================================================================================

TEST_F(Nroot_test, Nroot_test1)
{
    EXPECT_TRUE(root_test(16, 4 , 2, NO));
}

TEST_F(Nroot_test, Nroot_test2)
{
    EXPECT_TRUE(root_test(-16, 4 , 2, YES));
}

TEST_F(Nroot_test, Nroot_test3)
{
    EXPECT_TRUE(root_test(2, 2, 1.41421, NO));
}

TEST_F(Nroot_test, Nroot_test4)
{
    EXPECT_TRUE(root_test(1, 999123131, 1, NO));
}

TEST_F(Nroot_test, Nroot_test5)
{
    EXPECT_TRUE(root_test(150, 10, 1.65047, NO));
}

TEST_F(Nroot_test, Nroot_test6)
{
    EXPECT_TRUE(root_test(123.2, 0, 1, NO));
}

TEST_F(Nroot_test, Nroot_test7)
{
    EXPECT_TRUE(root_test(-42.2, 1, -42.2, NO));
}

TEST_F(Nroot_test, Nroot_test8)
{
    EXPECT_TRUE(root_test(0, 15, 0, NO));
}

TEST_F(Nroot_test, Nroot_test9)
{
    EXPECT_TRUE(root_test(0.999999999999, 1432, 1, NO));
}

TEST_F(Nroot_test, Nroot_test10)
{
    EXPECT_TRUE(root_test(-52.124, 13, -1.3554385, NO));
}

TEST_F(Nroot_test, Nroot_test11)
{
    EXPECT_TRUE(root_test(-112, 4, 0, YES));
}

TEST_F(Nroot_test, Nroot_test12)
{
    EXPECT_TRUE(root_test(-1, 14, 0, YES));
}

//End of Nroot tests ==============================================================================================

//Real time calculation tests ==============================================================================================

TEST_F(Real_time_calc, Real_time_calc_test1)
{
    //checking at possition 1, 4 and 6. Expecting on results 10, 30, 33 at the possitions respectivly     
    test_real_time_calculation("10+20+30", {1, 4, 6}, {10, 30, 33});
}

TEST_F(Real_time_calc, Real_time_calc_test2)
{
    test_real_time_calculation("10+20*40", {0, 1, 4, 6, 7}, {1, 10, 30, 90, 810});
}

TEST_F(Real_time_calc, Real_time_calc_test3)
{
    test_real_time_calculation("10+20*40-410", {0, 1, 4, 6, 7, 10, 11}, {1, 10, 30, 90, 810, 769, 400});
}

TEST_F(Real_time_calc, Real_time_calc_test4)
{
    test_real_time_calculation("10+2*4^2", {3, 5, 7}, {12, 18, 42});
}

TEST_F(Real_time_calc, Real_time_calc_test5)
{
    test_real_time_calculation("10+2*4^2-5*8", {3, 5, 7, 9, 11}, {12, 18, 42, 37, 2});
}

TEST_F(Real_time_calc, Real_time_calc_test6)
{
    test_real_time_calculation("10+2*4^2-5*8", {3, 5, 7, 9, 11}, {12, 18, 42, 37, 2});
}

TEST_F(Real_time_calc, Real_time_calc_test7)
{
    test_real_time_calculation("5*2*4+2^3", {4, 8}, {40, 48});
}

TEST_F(Real_time_calc, Real_time_calc_test8)
{
    test_real_time_calculation("5*2*4+2^3-25.5", {4, 8, 11, 13}, {40, 48, 23, 22.5});
}

TEST_F(Real_time_calc, Real_time_calc_test9)
{
    test_real_time_calculation("5*2*4+2^3-25.5+7.5*3", {4, 8, 11, 13, 17, 19}, {40, 48, 23, 22.5, 30, 45});
}

TEST_F(Real_time_calc, Real_time_calc_test10)
{
    test_real_time_calculation("1+(2+3)+4", {3, 5, 8}, {3, 6, 10});
}

TEST_F(Real_time_calc, Real_time_calc_test11)
{
    test_real_time_calculation("1+((2+3))+4", {4, 6, 10}, {3, 6, 10});
}

TEST_F(Real_time_calc, Real_time_calc_test12)
{
    test_real_time_calculation("1+(((2+3)))+4", {5, 7, 12}, {3, 6, 10});
}

TEST_F(Real_time_calc, Real_time_calc_test13)
{
    test_real_time_calculation("2*(2+3)", {3, 5}, {4, 10});
}

TEST_F(Real_time_calc, Real_time_calc_test14)
{
    test_real_time_calculation("2*(2+3)*2", {3, 5, 8}, {4, 10, 20});
}

TEST_F(Real_time_calc, Real_time_calc_test15)
{
    test_real_time_calculation("10+2*(2+3)*2", {6, 8, 11}, {14, 20, 30});
}

TEST_F(Real_time_calc, Real_time_calc_test16)
{
    test_real_time_calculation("10+2*(2+3)^2", {6, 8, 11}, {14, 20, 60});
}

TEST_F(Real_time_calc, Real_time_calc_test17)
{
    test_real_time_calculation("10+2*(2+3*2)^2", {6, 8, 10, 13}, {14, 20, 26, 138});
}

TEST_F(Real_time_calc, Real_time_calc_test18)
{
    test_real_time_calculation("10+2*(4+3*2^2)?2", {6, 8, 10, 12, 15}, {18, 24, 30, 42, 18});
}

TEST_F(Real_time_calc, Real_time_calc_test19)
{
    test_real_time_calculation("10+2*(4+3*2^2)?2+2", {6, 8, 10, 12, 15, 17}, {18, 24, 30, 42, 18, 20});
}

TEST_F(Real_time_calc, Real_time_calc_test20)
{
    test_real_time_calculation("(2+6)*(3+7)", {3, 7, 9, 10}, {8, 24, 80, 80});
}

TEST_F(Real_time_calc, Real_time_calc_test21)
{
    test_real_time_calculation("(2+6)*(3+7)/8", {3, 7, 9, 10, 12}, {8, 24, 80, 80, 10});
}

TEST_F(Real_time_calc, Real_time_calc_test22)
{
    test_real_time_calculation("(2+6)*(3+7)/8+5", {3, 7, 9, 10, 12, 14}, {8, 24, 80, 80, 10, 15});
}

TEST_F(Real_time_calc, Real_time_calc_test23)
{
    test_real_time_calculation("(2+6)+(2*3)*4^(1+1)*2", {7, 9, 12, 17, 20}, {10, 14, 32, 104, 200});
}

TEST_F(Real_time_calc, Real_time_calc_test24)
{
    test_real_time_calculation("5.5+2*(3.5+27?3)^2-10", {3, 5, 10, 13, 15, 18, 21}, {5.5, 7.5, 12.5, 66.5, 18.5, 90, 80});
}

TEST_F(Real_time_calc, Real_time_calc_test25)
{
    test_real_time_calculation("(2*(10/(5+(2.5*2)))+8", {5, 8, 13, 15, 20}, {20, 4, 2.66666, 2, 10});
}

TEST_F(Real_time_calc, Real_time_calc_test26)
{
    test_real_time_calculation("2+3*(1+8/(2--2)+3.5*2)-10", {5, 7, 10, 13, 18, 20, 24}, {5, 29, 17, 11, 21.5, 32, 22});
}

TEST_F(Real_time_calc, Real_time_calc_test27)
{
    test_real_time_calculation("10+-(4+5)+5", {5, 7, 10}, {6, 1, 6});
}

TEST_F(Real_time_calc, Real_time_calc_test28)
{
    test_real_time_calculation("10+-(4+5)*2", {5, 7, 10}, {6, 1, -8});
}

TEST_F(Real_time_calc, Real_time_calc_test29)
{
    test_real_time_calculation("150+2*-(3+2)^3", {4, 8, 10, 13}, {152, 144, 140, -100});
}

TEST_F(Real_time_calc, Real_time_calc_test30)
{
    test_real_time_calculation("150+2*-(3+2)^3*2+300", {4, 8, 10, 13, 15, 18, 19}, {152, 144, 140, -100, -350, -320, -50});
}

TEST_F(Real_time_calc, Real_time_calc_test31)
{
    test_real_time_calculation("150/-(((2+1)*2)+4)*-2", {8, 10, 13, 16, 20}, {-75, -50, -25, -15, 30});
}

TEST_F(Real_time_calc, Real_time_calc_test32)
{
    test_real_time_calculation("-250+(2+4)!*2-190", {6, 8, 10, 12, 16}, {-248, -244, 470, 1190, 1000});
}

TEST_F(Real_time_calc, Real_time_calc_test33)
{
    test_real_time_calculation("8*(2+3)-6", {8}, {34});
}

TEST_F(Real_time_calc, Real_time_calc_test34)
{
    test_real_time_calculation("524D*2.5-5^2", {2, 3, 5, 6, 7, 9, 11}, {524, 52, 104, 104, 130, 125, 105});
}

TEST_F(Real_time_calc, Real_time_calc_test35)
{
    test_real_time_calculation("-2N^(32-28D)%22", {1, 2, 5, 6, 8, 9, 10, 13, 14}, {-2, 2, 8, 4294967296, 1073741824, 16, 1073741824, 0, 12});
}

TEST_F(Real_time_calc, Real_time_calc_test36)
{
    test_real_time_calculation("(s45)^2+(c45)^2", {3, 6, 11, 14}, {0.7071067811, 0.5, 1.2071067811, 1});
}

TEST_F(Real_time_calc, Real_time_calc_test37)
{
    test_real_time_calculation("(s25DD35)^2+(c75DD35)^2", {3, 7, 10, 15, 19, 22}, {0.4226182617, 0.573576436, 0.32898992, 
                                                           0.5878089734, 1.1481419726, 1});
}

TEST_F(Real_time_calc, Real_time_calc_test38)
{
    test_real_time_calculation("2+3*t45NN^6-3/s30NNN", {6, 7, 8, 10, 12, 16, 17, 18, 19}, {5, -1, 5, 5, 2, -1, 11, -1, 11});
}

TEST_F(Real_time_calc, Real_time_calc_test39)
{
    test_real_time_calculation("9-14D*(2D-5NN)^2", {1, 3, 4, 7, 8, 9, 15}, {9,-5, 8, 7, 8, 8,-16});
}

TEST_F(Real_time_calc, Real_time_calc_test40)
{
    test_real_time_calculation("((((3+5)-2*2)*4-1)+2)*2", {4, 6, 9, 11, 14, 16, 19, 22}, {3, 8, 6, 4, 16, 15, 17, 34});
}

TEST_F(Real_time_calc, Real_time_calc_test41)
{
    test_real_time_calculation("1*12345DNDDD+3D*2!N", {0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 14, 16, 17, 18}, {1, 12, 123, 1234, 12345, 1234, -1234, -123, -12, -1, -1, -2, -2, -2});
}

TEST_F(Real_time_calc, Real_time_calc_test42)
{
    test_real_time_calculation("((s90)-(3*(2-2)+5^(3-1)))+2D", {4, 8, 11, 13, 16, 19, 21, 26, 27, 28}, {1, -2, -5, 1, -4, -124, -24, -22, -24});
}

TEST_F(Real_time_calc, Real_time_calc_test43)
{
    test_real_time_calculation("((2+2)^(2-1))N*(2+48)", {2, 4, 8, 10, 13, 16, 18, 19}, {2, 4, 16, 4, -4, -8, -24, -200});
}

TEST_F(Real_time_calc, Real_time_calc_test44)
{
    test_real_time_calculation("((s0)N*(c0)N)^54", {15}, {0});
}

TEST_F(Real_time_calc, Real_time_calc_test45)
{
    test_real_time_calculation("(8+17D8)*2D10", {1, 3, 4, 5, 6, 9, 10, 11, 12}, {8, 9, 25, 9, 26, 52, 26, 26, 260});
}

TEST_F(Real_time_calc, Real_time_calc_test46)
{
    test_real_time_calculation("((2-3)*(4+2D1))N", {2, 4, 8, 10, 11, 12, 15}, {2, -1, -4, -6, -4, -5, 5});
}

TEST_F(Real_time_calc, Real_time_calc_test47)
{
    test_real_time_calculation("(35DNN-5ND)*2^3", {2, 3, 4, 5, 7, 8, 9, 12, 14}, {35, 3, -3, 3, -2, 8, 3, 6, 24});
}

TEST_F(Real_time_calc, Real_time_calc_test48)
{
    test_real_time_calculation("653DDNN98DN", {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, {6, 65, 653, 65, 6, -6, 6, 69, 698, 69, -69});
}

TEST_F(Real_time_calc, Real_time_calc_test49)
{
    test_real_time_calculation("(8+4+6)N*10D-44DN", {7, 9, 10, 11, 14, 15, 16}, {-18, -18, -180, -18, -62, -22, -14});
}

TEST_F(Real_time_calc, Real_time_calc_test50)
{
    test_real_time_calculation("(2^3D2N)+-1^2", {3, 4, 5, 6, 10, 12}, {8, 2, 4, 0.25, -0.75, 1.25});
}

TEST_F(Real_time_calc, Real_time_calc_test51)
{
    test_real_time_calculation("s(c0+89)*2^2.5-6^1.25", {3, 5, 6, 9, 13, 15, 20}, 
                                {0.0174524064, 0.156434465, 1, 2, 5.656854249, -0.3431457505, -3.7336532309});
}

TEST_F(Real_time_calc, Real_time_calc_test52)
{
    test_real_time_calculation("2!+3!*8!^(1/4!)+s(0!)-5", {1, 4, 7, 12, 13, 19, 22}, 
                                                {2, 8, 241922, 87.022012615, 11.333573221, 11.3510256282, 6.351025628});
}

TEST_F(Real_time_calc, Real_time_calc_test53)
{
    test_real_time_calculation("(s45+c45)!+2*3", {3, 7, 9, 11, 13}, {0.70710678, 1.4142135623, 1, 3, 7});
}

TEST_F(Real_time_calc, Real_time_calc_test54)
{
    test_real_time_calculation("2*(c0)+5*(s90+2)^3", {7, 12, 14, 17}, {7, 7, 17, 137});
}

TEST_F(Real_time_calc, Real_time_calc_test55)
{
    test_real_time_calculation("5+2*(1+2)^2*3-20*(c0+s90)*2/0.5+s45*2^0.5", {15, 19, 23, 26, 31, 40}, {39, 39, 19, -21, -101, -100});
}

TEST_F(Real_time_calc, Real_time_calc_test56)
{
    test_real_time_calculation("(-2*(s90))N^(2D2N)", {2, 7, 10, 13, 14, 15, 16}, {-2, -2, 2, 4, 2, 4, 0.25 });
}

TEST_F(Real_time_calc, Real_time_calc_test57)
{
    test_real_time_calculation("(s30)^(2N)DD-1)", {3, 7, 8, 11, 13}, {0.5, 0.25, 4, 0.5, 2});
}

TEST_F(Real_time_calc, Real_time_calc_test58)
{
    test_real_time_calculation("-(t180)+5!DN*123DN", {5, 8, 9, 10, 11, 15, 16,17}, {0, 5, 120, 5, -5, -615, -60, 60});
}

TEST_F(Real_time_calc, Real_time_calc_test59)
{
    test_real_time_calculation("(((4-2)+1)-3*2)/(6/2-((5+3)*(1+1)))", {5, 8, 11, 13, 19, 33}, {2, 3, 0, -3, -1, 0.23076923});
}

TEST_F(Real_time_calc, Real_time_calc_test60)
{
    test_real_time_calculation("((((5-3)*(3-1))N*(3+1))N^2)N", {6, 13, 15, 21, 23, 25, 27}, {2, 4, -4, -16, 16, 256, -256});
}

TEST_F(Real_time_calc, Real_time_calc_test61)
{
    test_real_time_calculation("((sin90)N)*(2-c0)N*3!DN", {8, 12, 15, 17, 19, 20, 21, 22}, {-1, -2, -1, 1, 3, 6, 3, -3});
}

TEST_F(Real_time_calc, Real_time_calc_test62)
{
    test_real_time_calculation("(83DN-(((c(s0))^1224243DDDD)^(1N)))-24/8", {4, 12, 18, 23, 25, 32, 39}, {-8, -9, -9, -9, -9, -9, -12});
}

TEST_F(Real_time_calc, Real_time_calc_test63)
{
    test_real_time_calculation("((c((360-4+2*2)/2))N+4)!", {6, 7, 18, 19, 21, 23}, {0.8090169943, 1,-1, 1, 5, 120});
}

TEST_F(Real_time_calc, Real_time_calc_test64)
{
    test_real_time_calculation("((s90*(22DN)^(23DN))N)*(-1)N", {4, 8, 9, 10, 15, 16, 17, 20, 27}, {1, 22, 2, -2,-8388608, 4, 0.25, -0.25, -0.25});
}

TEST_F(Real_time_calc, Real_time_calc_test65)
{
    test_real_time_calculation("(-(c45*(s30-t60))N)/3^((2*c0+2*s90)/2)", {17, 37}, {-0.8711914807, -0.0967990534});
}

TEST_F(Real_time_calc, Real_time_calc_test66)
{
    test_real_time_calculation("((6.5--sin90+-(-cos0+6.5)))N*2+5DDDDDDDDDDDDDDDDDDDDDDDDDDD1", 
                                {26, 29, 31, 32, 34, 39, 40, 41, 43, 44, 45, 47, 50, 51, 54, 56, 57, 59, 60}, 
                                {2, -4, 1, -4, -2, -2.5, -2.5, -8.5, -7.5, -7.5, -7.5, -7.5, -6.5, -6.5, -6, 0, 0, -1});
}

TEST_F(Real_time_calc, Real_time_calc_test67)
{
    test_real_time_calculation("(((3)))^2DDDDD1-+-5)*2-50)/2)/4NDDDDDDNDDDDDDNDDDDDD", 
                        {8, 10, 12, 14, 18, 21, 24, 27, 30, 31, 32, 36, 38, 40, 43, 45, 49, 51}, 
                        {9, 3, 3, 31, 26, 52, 2, 1, 0.25, -0.25, 1, 2, -2, -47, -26, 26, 31, 0});
}

#if 0 
TEST_F(Real_time_calc, Real_time_calc_test68)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test69)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test70)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test71)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test72)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test73)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test74)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test75)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test76)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test77)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test78)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test79)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test80)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test81)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test82)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test83)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test84)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test85)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test86)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test87)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test88)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test89)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test90)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test91)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test92)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test93)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test94)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test95)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test96)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test97)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test98)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test99)
{
    test_real_time_calculation("", {}, {});
}

TEST_F(Real_time_calc, Real_time_calc_test100)
{
    test_real_time_calculation("", {}, {});
}
#endif
//End of Real time calculation tests =================================================================================

//Factorial tests ===================================================================================================

TEST_F(Factorial_tests, Factorial_tests1)
{
    EXPECT_TRUE(fact_test(5, 120, NO));
}

TEST_F(Factorial_tests, Factorial_tests2)
{
    EXPECT_TRUE(fact_test(-4, 24, YES));
}

TEST_F(Factorial_tests, Factorial_tests3)
{
    EXPECT_TRUE(fact_test(0, 1, NO));
}

TEST_F(Factorial_tests, Factorial_tests4)
{
    //EXPECT_TRUE(fact_test(21, -1, YES));
    EXPECT_EQ(factorial(21), (double)5109094217170944e4);
}

TEST_F(Factorial_tests, Factorial_tests5)
{
    EXPECT_TRUE(fact_test(-1, -1, YES));
}

TEST_F(Factorial_tests, Factorial_tests6)
{
    EXPECT_TRUE(fact_test(-124, -1, YES));
}

TEST_F(Factorial_tests, Factorial_tests7)
{
    EXPECT_DOUBLE_EQ(factorial(124), (double)1.50614174151114087979501416199e207);
}
//End of Factorial tests ===================================================================================================

//Npow tests ===================================================================================================

TEST_F(Npow_test, Npow_test1)
{
    EXPECT_TRUE(pow_test(3.3, 2, 10.89, NO));
}

TEST_F(Npow_test, Npow_test2)
{
    EXPECT_TRUE(pow_test(123.32442, 0, 1, NO));
}

TEST_F(Npow_test, Npow_test3)
{
    EXPECT_TRUE(pow_test(-14.2, 0, 1, NO));
}

TEST_F(Npow_test, Npow_test4)
{
    EXPECT_TRUE(pow_test(0, 0, 1, NO));
}

TEST_F(Npow_test, Npow_test5)
{
    EXPECT_TRUE(pow_test(0.9999999999999, 2, 1, NO));
}

TEST_F(Npow_test, Npow_test6)
{
    EXPECT_TRUE(pow_test(0.99, 4, 0.96059601, NO));
}
//End of Npow tests ===================================================================================================

//Xpow tests ===================================================================================================

TEST_F(Xpow_test, Xpow_test1)
{
    EXPECT_TRUE(pow_test(5, 2, 25, NO));
}

TEST_F(Xpow_test, Xpow_test2)
{
    EXPECT_TRUE(pow_test(36.1556, 0, 1, NO));
}

TEST_F(Xpow_test, Xpow_test3)
{
    EXPECT_TRUE(pow_test(-14.2, 0.5, 1, YES));
}

TEST_F(Xpow_test, Xpow_test4)
{
    EXPECT_TRUE(pow_test(16, 0.25, 2, NO));
}

TEST_F(Xpow_test, Xpow_test5)
{
    EXPECT_TRUE(pow_test(4, 1.5, 8, NO));
}

TEST_F(Xpow_test, Xpow_test6)
{
    EXPECT_TRUE(pow_test(-5, 0.2, -1.37972966, NO));
}

TEST_F(Xpow_test, Xpow_test7)
{
    EXPECT_TRUE(pow_test(0.5, 3, 0.125, NO));
}

TEST_F(Xpow_test, Xpow_test8)
{
    EXPECT_TRUE(pow_test(-8, 2.5, 0, YES));
}

TEST_F(Xpow_test, Xpow_test9)
{
    EXPECT_TRUE(pow_test(4, -3, 0.015625, YES));
}

TEST_F(Xpow_test, Xpow_test10)
{
    EXPECT_TRUE(pow_test(0.2, -5, 3125, YES));
}

TEST_F(Xpow_test, Xpow_test11)
{
    EXPECT_TRUE(pow_test(0.5, -3.4, 10.5560632, YES));
}

TEST_F(Xpow_test, Xpow_test12)
{
    EXPECT_TRUE(pow_test(60, -3.2, 2.0413430699e-6, YES));
}
//End of Xpow tests ===================================================================================================

//Sinus tests ===================================================================================================
//table values with finite result
TEST_F(Nsin_test, Sinx_test1)
{
    EXPECT_TRUE(sinx_test(0, 0, NO));
    EXPECT_TRUE(sinx_test(30, 0.5, NO));
    EXPECT_TRUE(sinx_test(90, 1, NO));
    EXPECT_TRUE(sinx_test(150, 0.5, NO));
    EXPECT_TRUE(sinx_test(180, 0, NO));
    EXPECT_TRUE(sinx_test(210, -0.5, NO));
    EXPECT_TRUE(sinx_test(270, -1, NO));
    EXPECT_TRUE(sinx_test(360, 0, NO));
}
//table values with infinite result
TEST_F(Nsin_test, Sinx_test2)
{
    EXPECT_TRUE(sinx_test(45, 0.7071067811, NO));
    EXPECT_TRUE(sinx_test(60, 0.8660254037, NO));
    EXPECT_TRUE(sinx_test(120, 0.8660254037, NO));
    EXPECT_TRUE(sinx_test(135, 0.7071067811, NO));
}
//random values
TEST_F(Nsin_test, Sinx_test3)
{
    EXPECT_TRUE(sinx_test(15, 0.2588190451, NO));
    EXPECT_TRUE(sinx_test(-42, -0.66913060, NO));
    EXPECT_TRUE(sinx_test(-34.5, -0.566406235, NO));
    EXPECT_TRUE(sinx_test(42.2, 0.6717205893, NO));
}
TEST_F(Nsin_test, Sinx_test4)
{
    EXPECT_TRUE(sinx_test(90, 1.01, YES));
    EXPECT_TRUE(sinx_test(270, -1.0001, YES));
}
//End of Sinus tests ===================================================================================================


//Cosinus tests ===================================================================================================
//table values with finite result
TEST_F(Ncos_test, Cosx_test1)
{
    EXPECT_TRUE(cosx_test(0, 1, NO));
    EXPECT_TRUE(cosx_test(60, 0.5, NO));
    EXPECT_TRUE(cosx_test(90, 0, NO));
    EXPECT_TRUE(cosx_test(120, -0.5, NO));
    EXPECT_TRUE(cosx_test(180, -1, NO));
    EXPECT_TRUE(cosx_test(240, -0.5, NO));
    EXPECT_TRUE(cosx_test(270, 0, NO));
    EXPECT_TRUE(cosx_test(360, 1, NO));
}
//table values with infinite result
TEST_F(Ncos_test, Cosx_test2)
{
    EXPECT_TRUE(cosx_test(45, 0.7071067811, NO));
    EXPECT_TRUE(cosx_test(30, 0.8660254037, NO));
    EXPECT_TRUE(cosx_test(150, -0.8660254037, NO));
    EXPECT_TRUE(cosx_test(135, -0.7071067811, NO));
    EXPECT_TRUE(cosx_test(210, -0.8660254037, NO));
}
//random value
TEST_F(Ncos_test, Cosx_test3)
{
    EXPECT_TRUE(cosx_test(1337, -0.224951054, NO));
    EXPECT_TRUE(cosx_test(49, 0.6560590289, NO));
    EXPECT_TRUE(cosx_test(0.0001, 1, NO));
    EXPECT_TRUE(cosx_test(-3.14, 0.99849867, NO));
}
TEST_F(Ncos_test, Cosx_test4)
{
    EXPECT_TRUE(cosx_test(0.000001, 1.001, YES));
    EXPECT_TRUE(cosx_test(179.9, -1.1, YES));
    EXPECT_TRUE(cosx_test(359.9, 1, YES));
}
//End of Cosinus tests ===================================================================================================

//Tangens tests ===================================================================================================
//table values
TEST_F(Ntan_test, Tanx_test1)
{
    EXPECT_TRUE(tanx_test(0, 0, NO));
    EXPECT_TRUE(tanx_test(30, 0.5773502691, NO));
    EXPECT_TRUE(tanx_test(45, 1, NO));
    EXPECT_TRUE(tanx_test(60, 1.7320508075, NO));
    EXPECT_TRUE(tanx_test(90, 0, YES));
    EXPECT_TRUE(tanx_test(270, 0, YES));
}
TEST_F(Ntan_test, Tanx_test2)
{
    EXPECT_TRUE(tanx_test(32, 0.6248693519, NO));
    EXPECT_TRUE(tanx_test(-1180, 5.671281819, NO));
    EXPECT_TRUE(tanx_test(99, -6.3137515146, NO));
    EXPECT_TRUE(tanx_test(630, 0, YES));
}
//End of Tangens tests ===================================================================================================

//Add tests ===============================================================================================================
TEST(Add_test, Add_test1)
{
    EXPECT_DOUBLE_EQ(add(2.25, 1.25), 3.5);
}

TEST(Add_test, Add_test2)
{
    EXPECT_DOUBLE_EQ(add(5.3, -1.2), 4.1);
}

TEST(Add_test, Add_test3)
{
    EXPECT_DOUBLE_EQ(add(-8.25, -1.75), -10);
}

TEST(Add_test, Add_test4)
{
    EXPECT_DOUBLE_EQ(add(-4.8, 1.2), -3.6);
}

TEST(Add_test, Add_test5)
{
    EXPECT_DOUBLE_EQ(add(0, 0), 0);
}
//Endo of Add tests ==========================================================================================================

//Sub tests ==================================================================================================================
TEST(Sub_test, Sub_test1)
{
    EXPECT_DOUBLE_EQ(sub(2.25, 1.25), 1);
}

TEST(Sub_test, Sub_test2)
{
    EXPECT_DOUBLE_EQ(sub(5.3, -1.2), 6.5);
}

TEST(Sub_test, Sub_test3)
{
    EXPECT_DOUBLE_EQ(sub(-8.25, -1.75), -6.5);
}

TEST(Sub_test, Sub_test4)
{
    EXPECT_DOUBLE_EQ(sub(-4.8, 1.2), -6);
}

TEST(Sub_test, Sub_test5)
{
    EXPECT_DOUBLE_EQ(sub(0, 0), 0);
}
//End of Sub tests ============================================================================================================

//Mul tests ==================================================================================================================
TEST(Mul_test, Mul_test1)
{
    EXPECT_DOUBLE_EQ(mul(2.25, 1.25), 2.8125);
}

TEST(Mul_test, Mul_test2)
{
    EXPECT_DOUBLE_EQ(mul(5.3, -1.2), -6.36);
}

TEST(Mul_test, Mul_test3)
{
    EXPECT_DOUBLE_EQ(mul(-8.25, -1.75), 14.4375);
}

TEST(Mul_test, Mul_test4)
{
    EXPECT_DOUBLE_EQ(mul(-4.8, 1.2), -5.76);
}

TEST(Mul_test, Mul_test5)
{
    EXPECT_DOUBLE_EQ(mul(0, 0), 0);
}
//End of Mul tests ============================================================================================================

//Div tests ==================================================================================================================
TEST(Div_test, Div_test1)
{
    EXPECT_DOUBLE_EQ(div_(2.25, 1.25), 1.8);
}

TEST(Div_test, Div_test2)
{
    EXPECT_DOUBLE_EQ(div_(5.3, -1.2), -4.416666666666666);
}

TEST(Div_test, Div_test3)
{
    EXPECT_DOUBLE_EQ(div_(-8.25, -1.75), 4.7142857142857144);
}

TEST(Div_test, Div_test4)
{
    EXPECT_DOUBLE_EQ(div_(-4.8, 1.2), -4);
}

TEST(Div_test, Div_test5)
{
    EXPECT_THROW(div_(0, 0), std::runtime_error);
}
//End of Div tests ============================================================================================================
