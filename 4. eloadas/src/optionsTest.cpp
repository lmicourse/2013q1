#include <gtest/gtest.h>
#include "Options.h"

TEST(OptionTest, EmptyString)
{
    Options ops("");

    EXPECT_EQ(0, ops.GetOptions().size());
    EXPECT_EQ("", ops.GetOption("overwrite"));
}

TEST(OptionTest, OneBooleanOption)
{
    Options ops("-overwrite");

    EXPECT_EQ(1, ops.GetOptions().size());
    EXPECT_EQ("true", ops.GetOption("overwrite"));
}

TEST(OptionTest, OneOptionWithValue)
{
    Options ops("-target /tmp");
    EXPECT_EQ(1, ops.GetOptions().size());
    EXPECT_EQ("/tmp", ops.GetOption("target"));
}

TEST(OptionTest, TwoOptionsWithValue)
{
    Options ops("-source /usr -target /tmp");
    EXPECT_EQ(2, ops.GetOptions().size());
    EXPECT_EQ("/usr", ops.GetOption("source"));
    EXPECT_EQ("/tmp", ops.GetOption("target"));
}

TEST(OptionTest, OptionWithValueThanBooleanOption)
{
    Options ops("-source /usr -overwrite");
    EXPECT_EQ(2, ops.GetOptions().size());
    EXPECT_EQ("/usr", ops.GetOption("source"));
    EXPECT_EQ("true", ops.GetOption("overwrite"));
}

TEST(OptionTest, BooleanOptionThanOptionWithValue)
{
    Options ops("-overwrite -source /usr");
    EXPECT_EQ(2, ops.GetOptions().size());
    EXPECT_EQ("/usr", ops.GetOption("source"));
    EXPECT_EQ("true", ops.GetOption("overwrite"));
}

TEST(OptionTest, OptionWithValueThanBooleanOptionThanOptionWithValue)
{
    Options ops("-target /tmp -overwrite -source /usr");
    EXPECT_EQ(3, ops.GetOptions().size());
    EXPECT_EQ("/usr", ops.GetOption("source"));
    EXPECT_EQ("true", ops.GetOption("overwrite"));
    EXPECT_EQ("/tmp", ops.GetOption("target"));
}
