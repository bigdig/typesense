#include <gtest/gtest.h>
#include "string_utils.h"
#include <iconv.h>
#include <unicode/translit.h>

TEST(StringUtilsTest, ShouldNormalizeString) {
    StringUtils string_utils;

    std::string alphanum = "Aa12Zz";
    string_utils.unicode_normalize(alphanum);
    ASSERT_STREQ("aa12zz", alphanum.c_str());

    std::string alphanum_space = "Aa12Zz 12A";
    string_utils.unicode_normalize(alphanum_space);
    ASSERT_STREQ("aa12zz12a", alphanum_space.c_str());

    std::string alphanum_specialchars = "Aa12Zz@W-_?,.R";
    string_utils.unicode_normalize(alphanum_specialchars);
    ASSERT_STREQ("aa12zzwr", alphanum_specialchars.c_str());

    std::string alphanum_unicodechars = "abcÅà123ß";
    string_utils.unicode_normalize(alphanum_unicodechars);
    ASSERT_STREQ("abcaa123ss", alphanum_unicodechars.c_str());

    std::string tamil_unicodechars = "தமிழ் நாடு";
    string_utils.unicode_normalize(tamil_unicodechars);
    ASSERT_STREQ("தமிழ்நாடு", tamil_unicodechars.c_str());

    std::string chinese_unicodechars = "你好吗";
    string_utils.unicode_normalize(chinese_unicodechars);
    ASSERT_STREQ("你好吗", chinese_unicodechars.c_str());
}

TEST(StringUtilsTest, ShouldJoinString) {
    std::vector<std::string> parts = {"foo", "bar", "baz", "bazinga"};

    const std::string & joined_str1 = StringUtils::join(parts, "/");
    ASSERT_STREQ("foo/bar/baz/bazinga", joined_str1.c_str());

    const std::string & joined_str2 = StringUtils::join(parts, "/", 2);
    ASSERT_STREQ("baz/bazinga", joined_str2.c_str());
}
