#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

#include "vec3.h"

// Member function tests
TEST_CASE( "Tests operator- member function") {
    vec3 myVector = vec3(1,1,1);
    vec3 negatedVector = -myVector;

    REQUIRE(negatedVector.x() == -1);
    REQUIRE(negatedVector.y() == -1);
    REQUIRE(negatedVector.z() == -1);
}

TEST_CASE("Testing index operator overload member function"){
    // Testing the reference
    vec3 myVector = vec3(1,1,1);

    myVector[0] = 2;

    REQUIRE(myVector[0] == 2);

    // Testing the const
    const vec3 myVector2 = vec3(1,1,1);

    double x = myVector2[0];

    REQUIRE(x == 1);

}

TEST_CASE("Testing += Operator overload member function for vector addition"){

    vec3 vector1 = vec3(1,1,1);
    vec3 vector2 = vec3(2,2,2);

    vector1 += vector2;

    REQUIRE(vector1.x() == 3);
    REQUIRE(vector1.y() == 3);
    REQUIRE(vector1.z() == 3);

}

TEST_CASE("Testing *= Opereator overload member function for scalar multiplication"){
    vec3 vector1 = vec3(1,1,1);
    double scalar = 5;
    vector1 *= scalar;

    REQUIRE(vector1.x() == 5);
    REQUIRE(vector1.y() == 5);
    REQUIRE(vector1.z() == 5);

}   

TEST_CASE("Testing /= Opereator overload member function for scalar division "){
    vec3 vector1 = vec3(5,5,5);
    double scalar = 5;
    vector1 /= scalar;

    REQUIRE(vector1.x() == 1);
    REQUIRE(vector1.y() == 1);
    REQUIRE(vector1.z() == 1);

}   

TEST_CASE("Test the length function and helper function"){
    vec3 vector1 = vec3(1,2,2);

    double vecLength = vector1.length();
    
    REQUIRE(vecLength == 3);


}

//Utility function tests
TEST_CASE("Test for operator overload of +, adds two vectors together and returns a new vector"){
    vec3 vector1 = vec3(1,1,1);
    vec3 vector2 = vec3(1,1,1);
    vec3 newVector = vector1 + vector2;

    REQUIRE(newVector.x() == 2);
    REQUIRE(newVector.y() == 2);
    REQUIRE(newVector.z() == 2);
}

TEST_CASE("Test for operator overload of -, subtracts two vectors and returns a new vector"){
    vec3 vector1 = vec3(1,1,1);
    vec3 vector2 = vec3(1,1,1);
    vec3 newVector = vector1 - vector2;

    REQUIRE(newVector.x() == 0);
    REQUIRE(newVector.y() == 0);
    REQUIRE(newVector.z() == 0);
}

TEST_CASE("Test for operator overload of *, multiplies two vectors together and returns a new vector (component wise multiplication)"){
    vec3 vector1 = vec3(2,2,2);
    vec3 vector2 = vec3(2,2,2);
    vec3 newVector = vector1 * vector2;

    REQUIRE(newVector.x() == 4);
    REQUIRE(newVector.y() == 4);
    REQUIRE(newVector.z() == 4);
}

TEST_CASE("Test for operator overload of *, multiplies a vector by a scalar (scalar multiplication) *Test does both versions*"){
    // v * t
    vec3 vector1 = vec3(2,2,2);
    double scalar1 = 2;
    vec3 newVector = vector1 * scalar1;

    REQUIRE(newVector.x() == 4);
    REQUIRE(newVector.y() == 4);
    REQUIRE(newVector.z() == 4);

    //t * v
    vec3 vector2 = vec3(2,2,2);
    double scalar2 = 2;
    vec3 newVector2 = scalar2 * vector2;

    REQUIRE(newVector2.x() == 4);
    REQUIRE(newVector2.y() == 4);
    REQUIRE(newVector2.z() == 4);
}

TEST_CASE("Test for operator overload of /, divides a vector by a scaler (scalar division)"){
    vec3 vector = vec3(2,2,2);
    double scalar = 2;
    vec3 newVector = vector / scalar;

    REQUIRE(newVector.x() == 1);
    REQUIRE(newVector.y() == 1);
    REQUIRE(newVector.z() == 1);
}

TEST_CASE("Test for dot product"){
    vec3 vector1 = vec3(2,2,2);
    vec3 vector2 = vec3(2,2,2);
    double dotProduct = dot(vector1,vector2);

    REQUIRE(dotProduct == 12);

    vec3 vector3 = vec3(1,2,3);
    vec3 vector4 = vec3(4,5,6);
    double dotProduct2 = dot(vector3,vector4);

    REQUIRE(dotProduct2 == 32);

}

TEST_CASE("Test for cross product"){
    vec3 vector1 = vec3(2,2,2);
    vec3 vector2 = vec3(2,2,2);
    vec3 crossProduct = cross(vector1,vector2);

    REQUIRE(crossProduct.x() == 0);
    REQUIRE(crossProduct.y() == 0);
    REQUIRE(crossProduct.z() == 0);

    vec3 vector3 = vec3(1,2,3);
    vec3 vector4 = vec3(4,5,6);
    vec3 crossProduct2 = cross(vector3,vector4);

    REQUIRE(crossProduct2.x() == -3);
    REQUIRE(crossProduct2.y() == 6);
    REQUIRE(crossProduct2.z() == -3);
}

TEST_CASE("Test for unit vector"){
    vec3 vector1 = vec3(3,4,0);
    vec3 unit = unit_vector(vector1);

    REQUIRE(unit.x() == Catch::Approx(0.6)); //got a weird floating point error so this is good enough i think
    REQUIRE(unit.y() == 0.8);
    REQUIRE(unit.z() == 0);
    REQUIRE(unit.length() == 1);
}
