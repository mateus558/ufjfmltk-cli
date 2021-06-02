//
// Created by mateus on 29/05/2021.
//

#pragma once
#ifndef CPPCLI_UFJFMLTK_SETTINGS_H
#define CPPCLI_UFJFMLTK_SETTINGS_H

#include "ufjfmltk/ufjfmltk.hpp"

namespace settings{
    extern size_t seed;
    extern size_t verbose;
    extern size_t max_time;
    extern std::string data_folder;
    extern mltk::Data<> data, train, test;
}

#endif //CPPCLI_UFJFMLTK_SETTINGS_H
