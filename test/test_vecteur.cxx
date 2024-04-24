#include <gtest/gtest.h>
#include "../include/vecteur.hxx"

TEST(VecteurTest, testGettersAndSetters){
    Vecteur<double> vec(1.0, 2.0, 3.0);

    ASSERT_EQ(vec.getX(), 1.0);
    ASSERT_EQ(vec.getY(), 2.0);
    ASSERT_EQ(vec.getZ(), 3.0);

    vec.setX(4.0);
    vec.setY(5.0);
    vec.setZ(6.0);

    ASSERT_EQ(vec.getX(), 4.0);
    ASSERT_EQ(vec.getY(), 5.0);
    ASSERT_EQ(vec.getZ(), 6.0);
}

TEST(VecteurTest, testOperatorEqual){
    Vecteur<double> vec1(3.0, 4.0, 5.0);
    Vecteur<double> vec2(3.0, 4.0, 5.0);

    ASSERT_TRUE(vec1 == vec2);
    ASSERT_TRUE(vec1 == Vecteur<double>(3.0, 4.0, 5.0));
    ASSERT_TRUE(Vecteur<double>(3.0, 4.0, 5.0) == Vecteur<double>(3, 4, 5));
}

TEST(VecteurTest, testOperatorPlusEqual){
    Vecteur<double> vec1(1.0, 2.0, 3.0);
    Vecteur<double> vec2(4.0, 5.0, 6.0);

    vec1 += vec2;

    ASSERT_EQ(vec1.getX(), 5.0);
    ASSERT_EQ(vec1.getY(), 7.0);
    ASSERT_EQ(vec1.getZ(), 9.0);
}

TEST(VecteurTest, testOperatorMinusEqual){
    Vecteur<double> vec1(4.0, 5.0, 6.0);
    Vecteur<double> vec2(1.0, 2.0, 3.0);

    vec1 -= vec2;

    ASSERT_EQ(vec1.getX(), 3.0);
    ASSERT_EQ(vec1.getY(), 3.0);
    ASSERT_EQ(vec1.getZ(), 3.0);
}

TEST(VecteurTest, testOperatorOutput){
    Vecteur<double> vec(1.0, 2.0, 3.0);

    std::stringstream ss;
    ss << vec;

    ASSERT_EQ(ss.str(), "(1, 2, 3)");
}

TEST(VecteurTest, testDistance){
    Vecteur<double> vec1(4.0, 3.3, -2);
    Vecteur<double> vec2(5.0, 4.5, 4);

    double distance = vec1.distance(vec2);

    ASSERT_EQ(distance, 6.2);
}

TEST(VecteurTest, testOperatorPlus){
    Vecteur<double> vec1(1.0, 2.0, 3.0);
    Vecteur<double> vec2(4.0, 5.0, 6.0);

    Vecteur<double> result = vec1 + vec2;

    ASSERT_EQ(result.getX(), 5.0);
    ASSERT_EQ(result.getY(), 7.0);
    ASSERT_EQ(result.getZ(), 9.0);
}

TEST(VecteurTest, testOperatorMinus){
    Vecteur<double> vec1(4.0, 5.0, 6.0);
    Vecteur<double> vec2(1.0, 2.0, 3.0);

    Vecteur<double> result = vec1 - vec2;

    ASSERT_EQ(result.getX(), 3.0);
    ASSERT_EQ(result.getY(), 3.0);
    ASSERT_EQ(result.getZ(), 3.0);
}

TEST(VecteurTest, testOperatorMultiply){
    Vecteur<double> vec(1.0, 2.0, 3.0);
    double scalaire = 2.0;

    Vecteur<double> result1 = vec * scalaire;
    Vecteur<double> result2 = scalaire * vec;

    ASSERT_EQ(result1.getX(), 2.0);
    ASSERT_EQ(result1.getY(), 4.0);
    ASSERT_EQ(result1.getZ(), 6.0);

    ASSERT_EQ(result2.getX(), 2.0);
    ASSERT_EQ(result2.getY(), 4.0);
    ASSERT_EQ(result2.getZ(), 6.0);
}

TEST(VecteurTest, testOperatorDivision){
    Vecteur<double> vec(2.0, 4.0, 6.0);
    double scalaire = 2.0;

    Vecteur<double> result = vec / scalaire;

    ASSERT_EQ(result.getX(), 1.0);
    ASSERT_EQ(result.getY(), 2.0);
    ASSERT_EQ(result.getZ(), 3.0);
}
