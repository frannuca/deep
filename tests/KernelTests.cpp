//
// Created by fran on 11.05.18.
//
#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE "DeepTests"
#include <boost/test/unit_test.hpp>

#include <memory>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <boost/test/unit_test.hpp>
#include <boost/test/test_tools.hpp>
#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

#include <cstdio> // remove
#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::remove;
}
#endif

#include <IKernel.h>
#include <SquaredExponentialKernel.h>

using namespace deep;
using namespace GP;

BOOST_AUTO_TEST_CASE( frames ) {
    IKernel * kernel = new SquaredExponentialKernel(1.0,500.0);


    std::vector<std::tuple<double,double>> points;
    for(int i=0;i<3;++i){
        points.push_back(std::make_tuple(i,(i)*(i)));
    }

    std::vector<double> xnew;
    xnew.push_back(3);
    xnew.push_back(4);
    xnew.push_back(7);

    arma::mat mu;
    arma::mat cov;
    kernel->Compute(points,xnew,mu,cov);
    std::cout<<"MEAN="<<std::endl;

    mu=mu.t();
    for(int i=0;i<mu.n_rows;++i){
        for(int j=0;j<mu.n_cols;++j){
            std::cout<<mu(i,j)<<" ";
        }
        std::cout<<std::endl;
    }

    std::cout<<std::endl;
    std::cout<<"COVARIANCE="<<std::endl;
    for(int i=0;i<cov.n_rows;++i){
        for(int j=0;j<cov.n_cols;++j){
            std::cout<<cov(i,j)<<" ";
        }
        std::cout<<std::endl;
    }
    delete(kernel);

}
