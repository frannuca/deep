//
// Created by fran on 11.05.18.
//

#ifndef DEEP_IKERNEL_H
#define DEEP_IKERNEL_H
#include <armadillo>
#include <functional>
#include <tuple>

namespace deep{
    namespace GP{
        class IKernel{
        public:
            IKernel();
            void ComputeKernelMatrix(const std::vector<std::tuple<double, double>> &values, arma::mat &K,
                                                 std::vector<double> &x, std::vector<double> &y);

            void Compute(const std::vector<std::tuple<double, double>> &values, const std::vector<double> &xnew, arma::mat &mu,
                                     arma::mat &cov, arma::mat &K);

        protected:
            virtual double kernel(const double &a, const double &b) = 0;

        };
    }
}



#endif //DEEP_IKERNEL_H
