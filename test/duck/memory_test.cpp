#include <gtest/gtest.h>

extern "C"
{
#include "memory.h"
}

TEST(Memory, get_undefined_record)
{
    CreateEnvironment();

    // create context
    CLOSURE* context = (CLOSURE*)ALLOC(sizeof(CLOSURE));
    context->parent = NULL;
    context->list = NULL;
    context->ref_count = -1;

    // store string record
    VALUE v_str;
    v_str.type = VAL_STRING;
    v_str.data.string = "world";
    StoreRecord("hello", v_str, context);

    // get undefiend record
    VALUE v_ret = GetRecord("hello2", context);
    ASSERT_EQ(v_ret.type, VAL_NIL);

    FreeEnvironment();
}

TEST(Memory, store_and_get_string_record)
{
    CreateEnvironment();

    // create context
    CLOSURE* context = (CLOSURE*)ALLOC(sizeof(CLOSURE));
    context->parent = NULL;
    context->list = NULL;
    context->ref_count = -1;

    // store string record
    VALUE v_str;
    v_str.type = VAL_STRING;
    v_str.data.string = "world";
    StoreRecord("hello", v_str, context);

    VALUE v_ret = GetRecord("hello", context);
    ASSERT_EQ(v_ret.type, VAL_STRING);
    ASSERT_EQ(v_ret.data.string, "world");

    FreeEnvironment();
}

