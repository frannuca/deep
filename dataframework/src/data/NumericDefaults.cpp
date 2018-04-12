//
// Created by fran on 12.04.18.
//
#include "../../include/data/NumericDefaults.h"
namespace deep{
    namespace data{

        const double Default<double>::missing = {std::numeric_limits<double>::quiet_NaN()};
        const double Default<double>::minus = {-1.0};

        const int Default<int>::missing = {std::numeric_limits<int>::quiet_NaN()};
        const int Default<int>::minus = {-1};

        const float Default<float>::missing = {std::numeric_limits<float>::quiet_NaN()};
        const float Default<float>::minus = {-1.0};
    }
}
