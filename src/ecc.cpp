#include "../include/bigint.hpp"
#include "../include/ecc.hpp"
#include <iostream>

Ecc_Point Ecc_Point::operator+(const Ecc_Point& other) const {
    if (this->isInfinity) return other;
    if (other.isInfinity) return *this;
    if (*this == -other) return Ecc_Point();

    if (*this == other) {
        return this->doublePoint();
    }
    BigInt lambda = (other.yCoord - yCoord) * ((other.xCoord - xCoord).modInverse(curveParams.p));
    BigInt x3 = (lambda * lambda - xCoord - other.xCoord) % curveParams.p;
    BigInt y3 = (lambda * (xCoord - x3) - yCoord) % curveParams.p;

    return Ecc_Point(x3, y3);
}


Ecc_Point Ecc_Point::operator-() const {
    if (this->isInfinity) return *this;
    return Ecc_Point(xCoord, curveParams.p - yCoord);
}


Ecc_Point Ecc_Point::operator*(const BigInt& scalar) const {
if (scalar.isZero() || this->isInfinity) {
    return Ecc_Point();
}
    Ecc_Point result;
    Ecc_Point point = *this;

    BigInt k = scalar;
    while (k > BigInt(static_cast<unsigned long int>(0))) {
        if (k % BigInt(static_cast<unsigned long int>(2)) != BigInt(static_cast<unsigned long int>(0))) {
            result = result + point;
        }
        point = point.doublePoint();
        k /= BigInt(static_cast<unsigned long int>(2));
    }
    return result;
}


bool Ecc_Point::operator==(const Ecc_Point& other) const {
    if (isInfinity && other.isInfinity) return true;
    if (isInfinity || other.isInfinity) return false;
    return (xCoord == other.xCoord) && (yCoord == other.yCoord);
}

Ecc_Point Ecc_Point::doublePoint() const {
    if (this->isInfinity || yCoord.isZero()) {
        return Ecc_Point();
    }

    BigInt lambda = (BigInt(static_cast<unsigned long int>(3)) * xCoord * xCoord + curveParams.a) * 
                    (BigInt(static_cast<unsigned long int>(2)) * yCoord).modInverse(curveParams.p);
    BigInt x3 = (lambda * lambda - BigInt(static_cast<unsigned long int>(2)) * xCoord) % curveParams.p;
    BigInt y3 = (lambda * (xCoord - x3) - yCoord) % curveParams.p;

    return Ecc_Point(x3, y3);
}

// int main() {
//     Ecc_Point G;
//     G=Ecc_Point(BigInt("6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296",16),BigInt("4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5",16));

//     // std::cout << "Prime p = " << G.getP().toString(16) << std::endl;
//     // std::cout << "x = " << G.getX().toString(16) << std::endl;
//     // std::cout << "y = " << G.getY().toString(16) << std::endl;

//     // Test vector for Point Addition
//     // Let's add G to itself and compare with 2*G
//     Ecc_Point pointAdditionResult = G + G;
//     // Output the results of Point Addition
//     std::cout << "Point Addition Result:" << std::endl;
//     std::cout << "x = " << pointAdditionResult.getX().toString(16) << std::endl;
//     std::cout << "y = " << pointAdditionResult.getY().toString(16) << std::endl;

//     Ecc_Point G1;
//     G1=Ecc_Point(BigInt("6b17d1f2e12c4247f8bce6e563a440f277037d812deb33a0f4a13945d898c296",16),BigInt("4fe342e2fe1a7f9b8ee7eb4a7c0f9e162bce33576b315ececbb6406837bf51f5",16));

//     Ecc_Point expectedAdditionResult = G1 * BigInt(static_cast<unsigned long int>(2));
//     std::cout << "Scalar Multiplication Result:" << std::endl;
//     std::cout << "x = " << expectedAdditionResult.getX().toString(16) << std::endl;
//     std::cout << "y = " << expectedAdditionResult.getY().toString(16) << std::endl;


//     // Comparing and output the test result for Point Addition
//     bool isAdditionCorrect = pointAdditionResult == expectedAdditionResult;
//     std::cout << "Point Addition Test " << (isAdditionCorrect ? "PASSED" : "FAILED") << std::endl;


//     // Test vector for Scalar Multiplication
//     // Scalar value k = 3
//     // G.print();
//     Ecc_Point scalarMultiplicationResult = G * BigInt(static_cast<unsigned long int>(3));
//     // Expected values for 3*G (you can compute this using an external ECC calculator or library)
//     std::string expected_x_str = "5ecbe4d1a6330a44c8f7ef951d4bf165e6c6b721efada985fb41661bc6e7fd6c";
//     std::string expected_y_str = "8734640c4998ff7e374b06ce1a64a2ecd82ab036384fb83d9a79b127a27d5032";

//     // Output of the results of Scalar Multiplication
//     std::cout << "Scalar Multiplication Result:" << std::endl;
//     std::cout << "x = " << scalarMultiplicationResult.getX().toString(16) << std::endl;
//     std::cout << "y = " << scalarMultiplicationResult.getY().toString(16) << std::endl;

//     // Comparing and output the test result for Scalar Multiplication
//     bool isMultiplicationCorrect = (scalarMultiplicationResult.getX().toString(16) == expected_x_str) &&
//                                    (scalarMultiplicationResult.getY().toString(16) == expected_y_str);
//     std::cout << "Scalar Multiplication Test " << (isMultiplicationCorrect ? "PASSED" : "FAILED") << std::endl;

//     return 0;
// }