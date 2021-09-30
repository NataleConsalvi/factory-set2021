#include "catch2/catch2.hpp"
#include "factory.h"


TEST_CASE("Adding machines and assembly line", "[machines]") {

    Factory factory;

    factory.addMachine("e", 4);    
    factory.addMachine("f", 8);
    factory.addMachine("g", 5);    
    factory.addMachine("h", 3);
    factory.addMachine("i", 7);
    factory.addMachine("l", 9);
    factory.addMachine("m", 4);
    factory.addMachine("n", 4);

    factory.addAssemblyLine("A", 10,  {"e", "f", "g", "h", "i","m"});

    factory.addProduct("X", {"A","e","f","h","i","m"});
    factory.addProduct("X", {"A","e"});
    
    factory.enqueue("X");
    factory.step();
    factory.step();
    factory.step();
    factory.step();
    factory.step();
}

/*
TEST_CASE("negative square_root should throw exception ", "[cxx_examples]") {
    

    // expects std::invalid_argument exception, if it is not thrown test fails        
    REQUIRE_THROWS_AS( square_root(-1.0), std::invalid_argument);

    REQUIRE(square_root(0.0) == Approx(0.0));
}


TEST_CASE("square_root >= 0 should give positive result ", "[cxx_examples]") {
                
    REQUIRE(square_root(4.0) == Approx(2.0));
}


TEST_CASE("say_hello should produce a string ", "[cxx_examples]") {
    
    REQUIRE( cxx_examples::say_hello("peppo") == std::string("hello peppo"));        
}
*/





