#include "../Model/matrix.h"
#include <gtest/gtest.h>
#include <vector>
#include <string>
/*
find . -name "*.gcda" -delete
find . -name "*.gcno" -delete
*/

class MatrixTest : public ::testing::Test{

protected:

    void SetUp() override {
    }
    
    void TearDown() override {
    }

};

TEST_F(MatrixTest, DefaultConstructor){

    MyMatrix::Matrix<int> m;
    
    EXPECT_EQ(m.GetRows(), 0);
    EXPECT_EQ(m.GetColumns(), 0);
    EXPECT_EQ(m.size(), 0);
    EXPECT_TRUE(m.empty());

}

TEST_F(MatrixTest, ParamConstructor){

    MyMatrix::Matrix<int> m{2,2};
    
    EXPECT_EQ(m.GetRows(), 2);
    EXPECT_EQ(m.GetColumns(), 2);
    EXPECT_EQ(m.size(), 4);
    EXPECT_FALSE(m.empty());

}

TEST_F(MatrixTest, ParamFillConstructor){

    MyMatrix::Matrix<int> m{2,3,10};
    
    EXPECT_EQ(m.GetRows(), 2);
    EXPECT_EQ(m.GetColumns(), 3);
    EXPECT_EQ(m.size(), 6);
    EXPECT_EQ(m[0],10);
    EXPECT_EQ(m[5],10);
    EXPECT_FALSE(m.empty());

}

TEST_F(MatrixTest, ElementAccess){

    MyMatrix::Matrix<int> m{2,3};
    
    m(0,0) = 5;
    m(1,2) = 10;
    
    EXPECT_EQ(m(0,0), 5);
    EXPECT_EQ(m(1,2), 10);
    
    m[1] = 20;
    m[4] = 30;
    
    EXPECT_EQ(m[1], 20);
    EXPECT_EQ(m[4], 30);
    EXPECT_EQ(m(0,1), 20);
    EXPECT_EQ(m(1,1), 30);

}

TEST_F(MatrixTest, FillMethod){

    MyMatrix::Matrix<int> m{3,3};
    m.Fill(42);
    
    for (size_t i = 0; i < m.size(); i++){

        EXPECT_EQ(m[i], 42);

    }

}

TEST_F(MatrixTest, GenerateData){

    MyMatrix::Matrix<int> m{2,3};
    m.GenerateData();
    
    EXPECT_EQ(m(0,0), 0);
    EXPECT_EQ(m(0,1), 1);
    EXPECT_EQ(m(0,2), 2);
    EXPECT_EQ(m(1,0), 3);
    EXPECT_EQ(m(1,1), 4);
    EXPECT_EQ(m(1,2), 5);

}

TEST_F(MatrixTest, OutputOperator){

    MyMatrix::Matrix<int> m{2,2};
    m.GenerateData();
    
    std::stringstream ss;
    ss << m;
    
    std::string line;
    std::getline(ss, line);
    EXPECT_EQ(line, "01");
    std::getline(ss, line);
    EXPECT_EQ(line, "23");

}

TEST_F(MatrixTest, CheckBounds){

    MyMatrix::Matrix<int> m{2,3};
    
    EXPECT_TRUE(m.CheckBounds(0,0));
    EXPECT_TRUE(m.CheckBounds(1,2));
    
}

TEST_F(MatrixTest, AddRow){

    MyMatrix::Matrix<int> m{2,3};
    m.GenerateData();
    
    m.AddRow({10, 11, 12});
    
    EXPECT_EQ(m.GetRows(), 3);
    EXPECT_EQ(m.GetColumns(), 3);
    EXPECT_EQ(m(2,0), 10);
    EXPECT_EQ(m(2,1), 11);
    EXPECT_EQ(m(2,2), 12);
    
    EXPECT_EQ(m(0,0), 0);
    EXPECT_EQ(m(1,2), 5);
}

TEST_F(MatrixTest, AddColumn){

    MyMatrix::Matrix<int> m{3,2};
    m.GenerateData();
    
    m.AddColumn({10, 11, 12});
    
    EXPECT_EQ(m.GetRows(), 3);
    EXPECT_EQ(m.GetColumns(), 3);
    EXPECT_EQ(m(0,2), 10);
    EXPECT_EQ(m(1,2), 11);
    EXPECT_EQ(m(2,2), 12);
    
    EXPECT_EQ(m(0,0), 0);
    EXPECT_EQ(m(2,1), 5);

}

TEST_F(MatrixTest, Iterator){

    MyMatrix::Matrix<int> m{2,2};

    m.GenerateData();
    
    int sum = 0;
    for (const auto& val : m){

        sum += val;
        
    }
    EXPECT_EQ(sum, 6);

    auto it = m.begin();
    EXPECT_EQ(*it, 0);
    ++it;
    EXPECT_EQ(*it, 1);
    
    auto end = m.end();
    EXPECT_NE(it, end);

}

TEST_F(MatrixTest, EmptyMatrixOperations){

    MyMatrix::Matrix<int> m;
    EXPECT_TRUE(m.empty());
    
    EXPECT_EQ(m.GetRows(), 0);
    EXPECT_EQ(m.GetColumns(), 0);
    EXPECT_EQ(m.size(), 0);

}

TEST_F(MatrixTest, DifferentTypes){

    MyMatrix::Matrix<double> m1{2,2, 3.14};
    EXPECT_DOUBLE_EQ(m1(0,0), 3.14);
    
    MyMatrix::Matrix<std::string> m2{1,1, "hello"};
    EXPECT_EQ(m2(0,0), "hello");
    
    m2(0,0) = "world";
    EXPECT_EQ(m2(0,0), "world");

}

TEST_F(MatrixTest, EdgeCases){

    MyMatrix::Matrix<int> m1{1,1, 99};
    EXPECT_EQ(m1(0,0), 99);
    
    MyMatrix::Matrix<int> m2{100,100};
    EXPECT_EQ(m2.size(), 10000);

    EXPECT_THROW(m1(10, 10), std::out_of_range);
    EXPECT_THROW(m1.AddRow({10},100), std::out_of_range);
    EXPECT_THROW(m1.AddColumn({10},100), std::out_of_range);

}

int main(int argc, char **argv){

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}

