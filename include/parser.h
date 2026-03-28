#pragma once
/// @file Парсер командной строки. Объявление.

#include "type.h"

/// @brief Парсинг командной строки.
/// @param[out] params Параметры работы.
/// @param[out] ipPool Пул адресов.
/// @param[in] argc Кол-во входных аргументов. 
/// @param[in] argv Входные аргументы. 
/// @return true - успешный парсинг, false - неуспешный парсинг.
bool ParserCommandLine( WorkParams& params, int argc, char const *argv[] );