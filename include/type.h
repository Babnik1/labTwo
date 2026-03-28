#pragma once
/// @file Типы перечислений и структур.

#include <string>
#include <utility>
#include <array>

constexpr int octetsCount = 4; 

/// @brief Тип адреса.
using IP = std::array< unsigned char, octetsCount >;

/// @brief Тип фильтрации.
enum class FilterType
{
    First           = 0,        /// Фильруем по первому октету.
    FirstSecond     = 1,        /// Фильтруем по первому и второму октету, два числа.
    Any             = 2,        /// Фильтруем по всем октетам, одно число.
    None            = 3         /// Не установлено.
};


/// @brief Тип вывода.
enum class OutType
{
    Console         = 0,        /// Вывод в консоль.
    File            = 1         /// Вывод в файл.
};


/// @brief Параметры работы программы.
struct WorkParams
{
    std::string inFile{};                   /// Входной файл.
    std::string outFile{};                  /// Файл результатов работы.
    OutType outType = OutType::Console;     /// Направление вывода.
    FilterType type{};                      /// Тип фильтрации.
    std::pair< int, int > numFilter{};      /// Фильтры.
};

/// @brief Класс исключения при неверной комманде.
class ErrCommand : public std::exception
{
private:
    std::string message;
public:
    ErrCommand( std::string msg ) : message{ msg } {};

    const char* what() const noexcept override
    {
        return message.c_str();
    }
};
