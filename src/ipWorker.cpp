/// @file Клас работы с IP адресами. реализация.
#include <iostream>
#include <algorithm>
#include <functional> 
#include <cctype>
#include <exception>
#include <fstream>

#include "type.h"
#include "ipWorker.h"


/// @brief Выделение из строки IP.
/// @param[in] str Входная строка.
/// @param[out] d Параметр отделения.
/// @return Вектор строковых IP.
std::vector< std::string > split( const std::string &str, char d )
{
    std::vector< std::string > r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of( d );
    while( stop != std::string::npos )
    {
        r.push_back( str.substr( start, stop - start ) );

        start = stop + 1;
        stop = str.find_first_of( d, start );
    }

    r.push_back( str.substr( start ) );

    return r;
} // split


std::unique_ptr< IpWorker > IpWorker::MakePtr( WorkParams& params )
{
    return std::make_unique< IpWorker >( params );
}

void IpWorker::Filtration()
{
    int target;
    switch ( params_.type )
    {
        case FilterType::First:
        {
            target = 1;
            break;
        }
        case FilterType::FirstSecond:
        {
            target = 2;
            break;
        }
        case FilterType::Any:
        {
            target = 4;
            break;
        }
        case FilterType::None:
        {
            return;
        }
        default:
        {
            return;;
        }
    }

    auto it = std::remove_if( ipPool_.begin(), ipPool_.end(), [ this, &target ]( const IP& ip ) 
    {
        bool exists = false;

        if ( target == 2 )
        {
            bool one = ip[ 0 ] == params_.numFilter.first;
            bool two = ip[ 1 ] == params_.numFilter.second;
            exists = one && two;
        }
        else
        {
            for ( int i = 0; i < target; ++i )
            {
                if ( ip[ i ] == params_.numFilter.first )
                {
                    exists = true;
                }
            }
        }
        return !exists;
    });

    ipPool_.erase( it, ipPool_.end() );
} // Filtration

void IpWorker::ReadIpPool()
{
    std::istream* in = &std::cin;
    std::ifstream fin;

    if ( !params_.inFile.empty() )
    {
        fin.open( params_.inFile );
        in = &fin;
    }
    for( std::string line; std::getline( *in, line ); )
    {
        const auto ip = split( line, '\t' );
        if ( ip.empty() )
        {
            continue;
        }
        std::vector< std::string > octets = split( ip.at( 0 ), '.' );
        if ( octets.size() != octetsCount )
        {
            continue;
        }

        try
        {
            IP tempIp{};
            for ( int i = 0; i < octetsCount; ++i )
            {
                int val = std::stoi( octets[ i ] );
                if ( val < 0 || val > 255 )
                {
                    throw std::out_of_range( "Octet out of range");
                }
                tempIp[ i ] =  static_cast< unsigned char >( val );
            }
            ipPool_.emplace_back( tempIp );
        }
        catch( const std::out_of_range& e )
        {
            std::cerr << "Out of range: " << e.what() << '\n';
            continue;
        }
        catch( const std::invalid_argument& e )
        {
            std::cerr << "Invalid argument: " <<  e.what() << '\n';
            continue;
        }
    }
} // ReadIpPool

void IpWorker::SortingIpPool()
{
    std::sort( ipPool_.begin(), ipPool_.end(), std::greater< IP >() );
    return;
}

void IpWorker::OutAddresses() const
{
    std::ofstream fout{};
    std::ostream* out = &std::cout;;

    if ( params_.outType == OutType::File )
    {
        fout.open( params_.outFile );
        if ( fout.is_open() )
        {
            out = &fout;
        }
    }

    for ( const auto& ip : ipPool_ )
    {
        ( *out ) << static_cast< int >( ip[ 0 ] ) 
                    << '.'
                    << static_cast< int >( ip[ 1 ] )
                    << '.'
                    << static_cast< int >( ip[ 2 ] )
                    << '.'
                    << static_cast< int >( ip[ 3 ] )
                    << "\n";
    }
} // OutAddresses

const std::vector< IP >& IpWorker::GetIpPool() const
{
    return ipPool_;
} // GetIpPool