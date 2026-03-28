#include <gtest/gtest.h>
#include <vector>

#include "ipWorker.h"
#include "type.h"

// Тест на создание объекта через MakePtr
TEST( IpWorkerTest, FactoryMethodCreatesObject ) {
    WorkParams params;
    auto worker = IpWorker::MakePtr( params );
    
    ASSERT_NE( worker, nullptr ); 
}

// Тест фильтрации по первому октету
TEST( IpWorkerTest, FilterByFirstOctet ) {
    WorkParams params;
    params.type = FilterType::First;
    params.numFilter = { 1, 0 };

    auto worker = IpWorker::MakePtr( params );
    
    auto& pool = const_cast< std::vector< IP >& >( worker->GetIpPool() );
    pool = {
        { 1, 1, 1, 1 },
        { 46, 70, 0, 1 },
        { 1, 2, 3, 4 }
    };
    
    worker->Filtration();
    
    EXPECT_EQ( worker->GetIpPool().size(), 2 ); // Ожидаем 2 адреса
    EXPECT_EQ( worker->GetIpPool()[ 0 ][ 0 ], 1 ); 
    EXPECT_EQ( worker->GetIpPool()[ 1 ][ 0 ], 1 );

    // Проверяем, что адрес с 46 исчез
    for( const auto& ip : worker->GetIpPool() ) 
    {
        EXPECT_NE( ip[ 0 ], 46 );
    }
}

// Тест фильтрации по двум октетам
TEST( IpWorkerTest, FilterByFirstSecondOctet ) {
    WorkParams params;
    params.type = FilterType::FirstSecond;
    params.numFilter = { 46, 70 };

    auto worker = IpWorker::MakePtr( params );
    
    auto& pool = const_cast< std::vector< IP >& >( worker->GetIpPool() );
    pool = {
        { 1, 1, 1, 1 },
        { 46, 70, 0, 1 },
        { 1, 2, 3, 4 },
        { 46, 70, 1, 2 }
    };
    
    worker->Filtration();
    
    EXPECT_EQ( worker->GetIpPool().size(), 2 ); // Ожидаем 2 адреса
    EXPECT_EQ( worker->GetIpPool()[ 0 ][ 0 ], 46 ); 
    EXPECT_EQ( worker->GetIpPool()[ 0 ][ 1 ], 70 ); 

    EXPECT_EQ( worker->GetIpPool()[ 1 ][ 0 ], 46 );
    EXPECT_EQ( worker->GetIpPool()[ 1 ][ 1 ], 70 );
}

// Тест фильтрации "any"
TEST( IpWorkerTest, FilterByAnyOctet ) {
    WorkParams params;
    params.type = FilterType::Any;
    params.numFilter = { 1 , 0 };

    auto worker = IpWorker::MakePtr( params );
    
    auto& pool = const_cast< std::vector< IP >& >( worker->GetIpPool() );
    pool = {
        { 192, 168, 46, 1 },
        { 10, 0, 0, 1 },
        { 46, 255, 255, 255 }
    };
    
    worker->Filtration();
    
    EXPECT_EQ( pool.size(), 2 );
    // Проверяем, что адрес с 255 исчез
    for( const auto& ip : worker->GetIpPool() ) 
    {
        EXPECT_NE( ip[ 1 ], 255 );
    }
}

int main( int argc, char **argv ) {
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}