//
// Created by fran on 12.04.18.
//

#ifndef DEEP_NUMERICDEFAULTS_H
#define DEEP_NUMERICDEFAULTS_H

#include <limits>

namespace deep {
    namespace data {

        template<typename C>
        class Default {
        public:
            static const C &missing;
            static const C &minus;
        };
        template<>
        class Default<double> {
        public:
            static const double missing;
            static const double minus;
        };

        template<>
        class Default<int> {
        public:
            static const int missing;
            static const int minus;
        };

        template<>
        class Default<float> {
        public:
            static const float missing;
            static const float minus;
        };
    }
}

#endif //DEEP_NUMERICDEFAULTS_H
