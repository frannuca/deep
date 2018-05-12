//
// Created by fran on 11.05.18.
//

#include "../include/SquaredExponentialKernel.h"


double deep::GP::SquaredExponentialKernel::kernel(const double &a, const double &b) {
    return _sigma*std::exp(-std::pow((a-b),2)/(2.0*_scale));
}

deep::GP::SquaredExponentialKernel::SquaredExponentialKernel(const double &sigma, const double &scale):_sigma(sigma),_scale(scale) {

}
