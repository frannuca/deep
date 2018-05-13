//
// Created by fran on 11.05.18.
//

#ifndef DEEP_SQUAREDEXPONENTIALKERNEL_H
#define DEEP_SQUAREDEXPONENTIALKERNEL_H
#include "IKernel.h"

namespace deep {
    namespace GP {

        class SquaredExponentialKernel:public IKernel {
        public:
            SquaredExponentialKernel(const double& sigma,const double& scale);
            virtual double kernel(const double &a, const double &b) override;
            void CalibrateParameters(const std::vector<std::tuple<double, double>> &values);
            void setParams(const double &sigma, const double &scale);
        protected:


            double kernel_internal(const double &a, const double &b,const double& s, const double& l);
            mutable double _sigma;
            mutable double _scale;
        };
    }
}

#endif //DEEP_SQUAREDEXPONENTIALKERNEL_H
