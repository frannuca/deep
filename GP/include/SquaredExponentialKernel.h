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

        protected:
            mutable double _sigma;
            mutable double _scale;
        };
    }
}

#endif //DEEP_SQUAREDEXPONENTIALKERNEL_H
