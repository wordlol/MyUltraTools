#pragma once
#include "Boarder.h"
#include <functional>
#include <map>
//3
//Тестирование программного обеспечения. Уровни и виды тестирования…
//Разработка через тестирование.


class TestRunner {
    struct Test {
        std::string name;
        std::function<void()> func;
    };
    static inline std::vector<Test> tests;
public:
    static void addTest(const std::string& name, std::function<void()> f) {
        tests.push_back({ name, f });
    }
    static void runAll() {
        int passed = 0;
        for (auto& t : tests) {
            try {
                t.func();
                std::cout << "[PASS] " << t.name << std::endl;
                ++passed;
            }
            catch (const std::exception& e) {
                std::cout << "[FAIL] " << t.name << " - " << e.what() << std::endl;
            }
        }
        std::cout << passed << "/" << tests.size() << " tests passed." << std::endl;
    }
};

#define ASSERT_EQUAL(expected, actual) \
if ((expected) != (actual)) throw std::runtime_error("ASSERT_EQUAL: " #expected " != " #actual);

#define ASSERT_TRUE(condition)
#define ASSERT_FALSE(expression)

#define ASSERT_THROWS(expression) \
do { \
    try { \
        expression; \
        throw std::runtime_error("Expected exception, but none thrown"); \
    } catch (const std::exception&) { \
        break; \
    } \
} while(0)

#define ASSERT_DOUBLE_EQUAL(expected, actual, eps) \
    if (std::abs((expected) - (actual)) > (eps)) \
        throw std::runtime_error("ASSERT_DOUBLE_EQUAL: " #expected " != " #actual);


std::string ToRoman(int num) {
    const std::pair<int, std::string> table[] = {
     {1000, "M"},
     {900, "CM"},
     {500, "D"},
     {400, "CD"},
     {100, "C"},
     {90, "XC"},
     {50, "L"},
     {40, "XL"},
     {10, "X"},
     {9, "IX"},
     {5, "V"},
     {4, "IV"},
     {1, "I"}
    };
    std::string result;
    for (auto& [value, roman] : table) {
        while (num >= value) {
            result += roman;
            num -= value;
        }
    }
    return result;
}
int ToArabic(const std::string& roman) {
    std::map<char, int> values = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}
    };
    int result = 0;
    for (size_t i = 0; i < roman.size(); ++i) {
        int current = values[roman[i]];
        int next = (i + 1 < roman.size()) ? values[roman[i + 1]] : 0;
        if (current < next) {
            result -= current;
        }
        else {
            result += current;
        }
    }
    return result;
}

void testToRoman_OutOfRange() {
    ASSERT_THROWS(ToRoman(0));
    ASSERT_THROWS(ToRoman(4000));
    ASSERT_THROWS(ToRoman(-5));
}
void testToArabic_Invalid() {
    ASSERT_THROWS(ToArabic("ABC"));
    ASSERT_THROWS(ToArabic("XIIII"));
    ASSERT_THROWS(ToArabic(""));
}
void testRoundTrip() {
    for (int i = 1; i <= 3999; ++i) {
        ASSERT_EQUAL(i, ToArabic(ToRoman(i)));
    }
}
void testToRoman_1() {
    ASSERT_EQUAL("I", ToRoman(1));
}
void testToRoman_2() {
    ASSERT_EQUAL("II", ToRoman(2));
}
void testToRoman_3() {
    ASSERT_EQUAL("III", ToRoman(3));
}
void testToRoman_4() {
    ASSERT_EQUAL("IV", ToRoman(4));
}
void testToRoman_5() {
    ASSERT_EQUAL("V", ToRoman(5));
}
void testToArabic_1() {
    ASSERT_EQUAL(1, ToArabic("I"));
}
void testToArabic_2() {
    ASSERT_EQUAL(5, ToArabic("V"));
}
void testToArabic_3() {
    ASSERT_EQUAL(10, ToArabic("X"));
}
void testToArabic_4() {
    ASSERT_EQUAL(100, ToArabic("C"));
}
void testToArabic_IV() { ASSERT_EQUAL(4, ToArabic("IV")); }
void testToArabic_VI() { ASSERT_EQUAL(6, ToArabic("VI")); }
void testToArabic_IX() { ASSERT_EQUAL(9, ToArabic("IX")); }
void testToArabic_XL() { ASSERT_EQUAL(40, ToArabic("XL")); }
void testToArabic_XC() { ASSERT_EQUAL(90, ToArabic("XC")); }
void testToArabic_CD() { ASSERT_EQUAL(400, ToArabic("CD")); }
void testToArabic_CM() { ASSERT_EQUAL(900, ToArabic("CM")); }
void testToArabic_MCMXCIX() { ASSERT_EQUAL(1999, ToArabic("MCMXCIX")); }


void MegaTest()
{
    TestRunner::addTest("TestRoman_1", testToRoman_1);
    TestRunner::addTest("TestRoman_2", testToRoman_2);
    TestRunner::addTest("TestRoman_3", testToRoman_3);
    TestRunner::addTest("TestRoman_4", testToRoman_4);
    TestRunner::addTest("TestRoman_5", testToRoman_5);
    TestRunner::addTest("TestArabic_1", testToArabic_1);
    TestRunner::addTest("TestArabic_2", testToArabic_2);
    TestRunner::addTest("TestArabic_3", testToArabic_3);
    TestRunner::addTest("TestArabic_4", testToArabic_4);
    TestRunner::addTest("testToArabic_IV", testToArabic_IV);
    TestRunner::addTest("testToArabic_VI", testToArabic_VI);
    TestRunner::addTest("testToArabic_IX", testToArabic_IX);
    TestRunner::addTest("testToArabic_XL", testToArabic_XL);
    TestRunner::addTest("testToArabic_XC", testToArabic_XC);
    TestRunner::addTest("testToArabic_CD", testToArabic_CD);
    TestRunner::addTest("testToArabic_CM", testToArabic_CM);

    TestRunner::addTest("testToRoman_OutOfRange", testToRoman_OutOfRange);
    TestRunner::addTest("testToArabic_Invalid", testToArabic_Invalid);
    TestRunner::addTest("testRoundTrip", testRoundTrip);


    TestRunner::runAll();
}


