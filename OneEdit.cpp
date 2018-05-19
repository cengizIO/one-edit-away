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
        if (a.at(i) != b.at(j)) {
            if (diff) {
                return false;
            }

            diff = true;

            // We've found a difference and if one of the strings is longer,
            // only possible edit is to remove a character
            if (lenA > lenB) {
                i++; // skip a character from a
            } else if (lenA < lenB) {
                j++; // skip a character from b
            } else { // Lengths are same so we hope to replace this character
                i++;
                j++;
            }
        } else { // There's no difference. Move along...
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

TEST_CASE("Totally different") {
    REQUIRE_FALSE(oneEditAway("aaa", "bbb"));
    REQUIRE_FALSE(oneEditAway("aaa", "bbbcc"));
    REQUIRE_FALSE(oneEditAway("abc", "abde"));
    REQUIRE_FALSE(oneEditAway("abc", "afcc"));
    REQUIRE_FALSE(oneEditAway("cat", "dog"));
    REQUIRE_FALSE(oneEditAway("cat", "act"));
}

TEST_CASE("Way shorter") {
    REQUIRE_FALSE(oneEditAway("bbbbbb", "bbb"));
}

TEST_CASE("Replace a character from ends") {
    REQUIRE(oneEditAway("aaa", "aab"));
    REQUIRE(oneEditAway("abc", "abd"));
}

TEST_CASE("Replace a character from inside") {
    REQUIRE(oneEditAway("cat", "cut"));
}

TEST_CASE("Delete a character from ends") {
    REQUIRE(oneEditAway("aaaa", "aaa"));
    REQUIRE(oneEditAway("oabc", "abc"));
    REQUIRE(oneEditAway("cat", "cats"));
    REQUIRE(oneEditAway("cat", "at"));
}

TEST_CASE("Delete a character from inside") {
    REQUIRE(oneEditAway("abc", "abxc"));
    REQUIRE(oneEditAway("abc", "ac"));
    REQUIRE(oneEditAway("cat", "cast"));
}
