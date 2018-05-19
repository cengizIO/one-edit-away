#include "catch.hpp"

using namespace std; // I don't do this often

bool oneEditAway(string const &a, string const &b) {
    size_t lenA = a.length();
    size_t lenB = b.length();

    const size_t initialDiff = lenA > lenB
                               ? lenA - lenB
                               : lenB - lenA;

    if (initialDiff > 1) {
        return false;
    }

    bool diff = false;

    size_t i = 0, j = 0;

    while (i < lenA && j < lenB) {
        // If current characters don't match
        if (a.at(i) != b.at(j)) {
            if (diff) {
                return false;
            }

            // If length of one string is
            // more, then only possible edit
            // is to remove a character
            if (lenA > lenB) {
                i++; // skip a character from a
            } else if (lenA < lenB) {
                j++; // skip a character from b
            } else {
                i++;
                j++;
            }

            diff = true;
        } else { // If current characters match
            i++;
            j++;
        }
    }

    // If last character is extra in any string
    if (i < lenA || j < lenB) {
        diff = true;
    }

    return diff;
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

TEST_CASE("cat !== dog") {
    REQUIRE_FALSE(oneEditAway("cat", "dog"));
}

TEST_CASE("cat === cats") {
    REQUIRE(oneEditAway("cat", "cats"));
}

TEST_CASE("cat === cut") {
    REQUIRE(oneEditAway("cat", "cut"));
}

TEST_CASE("cat === cast") {
    REQUIRE(oneEditAway("cat", "cast"));
}

TEST_CASE("cat === at") {
    REQUIRE(oneEditAway("cat", "at"));
}

TEST_CASE("cat !== act") {
    REQUIRE_FALSE(oneEditAway("cat", "act"));
}
