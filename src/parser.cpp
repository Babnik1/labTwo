/// @file Парсер командной строки. Реализация.

#include "parser.h"
#include <string>
#include <iostream>

/// @brief Ключевые слова парсинга командной строки.
const std::string filterCom = "filtration";
const std::string inMarker = "in";
const std::string outMarker = "out";
const std::string firstType = "first";
const std::string firstSecType = "first-second";
const std::string anyType = "any";
const std::string noneType = "none";
const std::string consoleOut = "console";

bool ParserCommandLine( WorkParams& params, int argc, char const *argv[] )
{

    if ( argc < 2 ) 
    {
        std::cerr << "Reference: ./ipFilter filtration <[ [ first | first-second | any ]> <num[, num ]> ] | none ]> in <input_file>  out <[ output_file | console ]>\n";
        return false;
    }

    for ( int i = 1; i < argc - 1; ++i )
    {
        try
        {
            std::string_view token = argv[ i ];
            std::string_view overToken = argv[ i + 1 ];
            if ( !token.empty() )
            {
                if ( token == filterCom )
                {
                    if ( overToken == firstType )
                    {
                        params.type = FilterType::First;
                    }
                    else if ( overToken == firstSecType )
                    {
                        params.type = FilterType::FirstSecond;
                    }
                    else if ( overToken == anyType )
                    {
                        params.type = FilterType::Any;
                    }
                    else if ( overToken == noneType )
                    {
                        params.type = FilterType::None;
                        i++;
                        continue;
                    }
                    else
                    {
                        throw ErrCommand( "Type of filtration is not set" );
                    }

                    
                    switch ( params.type )
                    {
                        case FilterType::FirstSecond:
                        {
                            /// Сценарий, когда у нас два числа
                            if ( i + 2 >= argc )
                            {
                                throw ErrCommand( "Missing argument" );
                            }

                            std::string_view number = argv[ i + 2 ];
                            std::size_t pos = number.find( ',' );
                            if ( pos == std::string::npos )
                            {
                                throw ErrCommand( "Expected num1,num2" );
                            }
                            try
                            {
                                params.numFilter.first = std::stoi( std::string{ number.substr( 0, pos ) } );
                                params.numFilter.second = std::stoi( std::string{ number.substr( pos + 1 ) } );
                                i += 2;
                            }
                            catch( const std::exception& e )
                            {
                                std::cerr << "Error command\n";
                                throw ErrCommand( "The numeric argument after type of filtration was not found" );
                            }
                            break;
                        }
                        case FilterType::First:
                        case FilterType::Any:
                        {
                            /// Сценарий с одним числом
                            if ( i + 2 >= argc )
                            {
                                throw ErrCommand( "Missing argument" );
                            }
                            try
                            {
                                params.numFilter.first = std::stoi( argv[ i + 2 ] );
                                i += 2;
                            }
                            catch( const std::exception& e )
                            {
                                std::cerr << "Error command\n";
                                throw ErrCommand( "The numeric argument after type of filtration was not found" );
                            }
                            break;
                        }
                        default: // Any, None
                        {
                            break;
                        }
                    }
                }
                else if ( token == inMarker )
                {
                    params.inFile = overToken;
                    i++;
                }
                else if ( token == outMarker )
                {
                    if ( overToken != consoleOut )
                    {
                        /// По дефолту будет консоль
                        params.outType = OutType::File;
                        params.outFile = argv[ i + 1 ];
                    }
                }
                else
                {
                    std::cerr << "Error command\n";
                    throw ErrCommand( "Onknown argument: " + std::string( token ) );
                }
            }
        }
        catch( const std::exception& e )
        {
            std::cerr << e.what();
            std::cerr << "Reference: ./ipFilter filtration <[ [ first | first-second | any ]> <num[, num ]> ] | none ]> in <input_file>  out <[ output_file | console ]>\n";
            return false;
        }
    }
    return true;
} // ParseCommandLine