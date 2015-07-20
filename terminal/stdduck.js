/*
    Duck Standard Library
    stdduck.js
*/


function LinkFunction()
{


}

function BindStandardLibrary()
{
    var print_func = {};
    print_func.type = VAL_FUNCTION;
    print_func.func = {};
    print_func.func.body = undefined;
    print_func.func.closure = gCurrentContext;
    print_func.func.built_in = 1;
    print_func.func.parameters = ["output"];
    print_func.func.functor = function (arg_count) 
    {
        var text = GetRecord("output", gCurrentContext);
        if (text.type == VAL_STRING) {
            program.print(text.string);
        } else if (text.type == VAL_PRIMITIVE) {
            program.print(text.primitive + "");
        } else if (text.type == VAL_FLOATING_POINT) {
            program.print(text.floatp + "");
        } else if (text.type == VAL_FUNCTION) {
            program.print("function");
        } else if (text.type == VAL_REFERENCE) {
            program.print("reference");
        } else if (text.type == VAL_NIL) {
            program.print("nill");
        } else {
            program.print("unknown type");
        }
        gLastExpression = {type: VAL_NIL, primitive: 0};
        return 0;
    };
    print_func.func.fn_name = "duck.print";
    
    var println_func = {};
    println_func.type = VAL_FUNCTION;
    println_func.func = {};
    println_func.func.body = undefined;
    println_func.func.closure = gCurrentContext;
    println_func.func.built_in = 1;
    println_func.func.parameters = ["output"];
    println_func.func.functor = function (arg_count) 
    {
        var text = GetRecord("output", gCurrentContext);
        if (text.type == VAL_STRING) {
            program.output(text.string);
        } else if (text.type == VAL_PRIMITIVE) {
            program.output(text.primitive + "");
        } else if (text.type == VAL_FLOATING_POINT) {
            program.output(text.floatp + "");
        } else if (text.type == VAL_FUNCTION) {
            program.output("function");
        } else if (text.type == VAL_REFERENCE) {
            program.output("reference");
        } else if (text.type == VAL_NIL) {
            program.output("nill");
        } else {
            program.output("unknown type");
        }
        gLastExpression = {type: VAL_NIL, primitive: 0};
        return 0;
    };
    println_func.func.fn_name = "duck.println";

    var duck_obj = {};
    
    duck_obj.type = VAL_REFERENCE;
    duck_obj.reference = {};
    duck_obj.reference.parent = undefined;
    duck_obj.reference.list = [];    

    StoreRecord("duck", duck_obj, gGlobalContext);
    StoreRecord("print", print_func, duck_obj.reference);
    StoreRecord("println", println_func, duck_obj.reference);

    return 0;
}

