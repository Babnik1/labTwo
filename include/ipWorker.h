#pragma once
/// @file Класс работы с IP адресами. Объявление.

#include <string>
#include <vector>
#include <memory>

#include "type.h"

class IpWorker
{
public:

    /// @brief Конструктор.
    /// @param[in] params Параметры работы.
    IpWorker( WorkParams& params )
                : params_{ params }
    {}

    /// @brief Создание умного указателя на класс. 
    /// @param[in] params Параметры работы.
    /// @return Умный указатель.
    static std::unique_ptr< IpWorker > MakePtr( WorkParams& params );

    /// @brief Чтение адресов в пул из файла.
    void ReadIpPool();

    /// @brief Фильтрация адресов.
    /// @param[in] type Тип фильтрации.
    void Filtration();

    /// @brief Сортировка пула IP.
    void SortingIpPool();

    /// @brief Вывод результата в консоль или в файл.
    void OutAddresses() const;

    /// @brief Получить пул адресов.
    /// @return Ссылка на пул адресов.
    const std::vector< IP >& GetIpPool() const;

private:
    struct WorkParams params_{};
    std::vector< IP > ipPool_{};
};
