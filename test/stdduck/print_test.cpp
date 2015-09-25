#include <gtest/gtest.h>

extern "C"
{
#include "lib/stdduck.h"
}

TEST(StdDuck, print_value_string)
{
    CreateEnvironment();
    testing::internal::CaptureStdout();

    VALUE val;
    val.type = VAL_STRING;
    val.data.string = "1";

    PrintValue(val);
    ASSERT_STREQ("1", testing::internal::GetCapturedStdout().c_str());

    FreeEnvironment();
}

namespace TestStdDuck
{
    int DummyFunc(int num_args, void* user_data)
    {
        int error = 0;
        VALUE argument = GetRecord("arg0", gCurrentContext);
        return error;
    }
}

TEST(StdDuck, print_value_function)
{
    CreateEnvironment();
    testing::internal::CaptureStdout();

    VALUE func = CreateFunction(TestStdDuck::DummyFunc);
    AddParameter(func, "arg0");

    PrintValue(func);
    ASSERT_STREQ("function(arg0)", testing::internal::GetCapturedStdout().c_str());

    FreeEnvironment();
}

