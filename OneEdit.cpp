#include "catch.hpp"

using namespace std; // I don't do this often

bool oneEditAway(string const &a, string const &b) {

    if (a == b) {
        return false;
    }

    const size_t lengthA = a.length();
    const size_t lengthB = b.length();

    const size_t lengthDiff = (lengthA > lengthB)
                              ? lengthA - lengthB
                              : lengthB - lengthA;

    if (lengthDiff > 1) {
        return false;
    }

    size_t diff = 0, i = 0, j = 0;

    while (i < lengthA && j < lengthB) {
        char f = a.at(i);
        char s = b.at(j);
        if (f != s) {
            diff++;
            if (lengthA > lengthB) {
                i++;
            } else if (lengthB > lengthA) {
                j++;
            } else { // lengthA == lengthB
                i++;
            }
        } else {
            i++;
            j++;
        }
        if (diff > 1) {
            return false;
        }
    }

    return true;

}

TEST_CASE("aaa !== bbb") {
    REQUIRE_FALSE(oneEditAway("aaa", "bbb"));
}

TEST_CASE("aaa !== bcc") {
    REQUIRE_FALSE(oneEditAway("aaa", "bbbcc"));
}

TEST_CASE("bbbbbb !== bbb") {
    REQUIRE_FALSE(oneEditAway("bbbbbb", "bbb"));
}

TEST_CASE("aaa === aab") {
    REQUIRE(oneEditAway("aaa", "aab"));
}

TEST_CASE("aaaa === aaa") {
    REQUIRE(oneEditAway("aaaa", "aaa"));
}

TEST_CASE("abc !== bde") {
    REQUIRE_FALSE(oneEditAway("abc", "abde"));
}

TEST_CASE("abc === abd") {
    REQUIRE(oneEditAway("abc", "abd"));
}

TEST_CASE("oabc === abc") {
    REQUIRE(oneEditAway("oabc", "abc"));
}

TEST_CASE("abc !== fcc") {
    REQUIRE_FALSE(oneEditAway("abc", "afcc"));
}

TEST_CASE("abc === abxc") {
    REQUIRE(oneEditAway("abc", "abxc"));
}

TEST_CASE("abc === ac") {
    REQUIRE(oneEditAway("abc", "ac"));
}

