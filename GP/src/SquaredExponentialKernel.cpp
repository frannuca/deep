//
// Created by fran on 11.05.18.
//

#include "../include/SquaredExponentialKernel.h"
#include <math.h>
#include <nlopt.hpp>
#include <tuple>
namespace {
    double myvfunc(const std::vector<double> &params, std::vector<double> &grad, void *pdata)
    {
        std::tuple<deep::GP::SquaredExponentialKernel*,std::vector<std::tuple<double,double>>>* data =
                (std::tuple<deep::GP::SquaredExponentialKernel*,std::vector<std::tuple<double,double>>>*)(pdata);

        deep::GP::SquaredExponentialKernel* pthis;
        std::vector<std::tuple<double,double>> points;
        std::tie(pthis,points)=(*data);

        arma::mat Kt;
        std::vector<double> x,y;
        pthis->setParams(params[0],params[1]);

        pthis->ComputeKernelMatrix(points,Kt,x,y);
        arma::mat K = Kt.submat(0,0,points.size()-1,points.size()-1);
        arma::mat invK = arma::inv(K);
        double detK = arma::det(K);
        detK=detK<1e-12?1e-12:detK;
        if (!grad.empty()) {
            throw new std::invalid_argument("We cannot use gradient methods for gaussian process calibration");
        }

        arma::mat yv(x);

        arma::mat aux = -0.5*yv.t()*invK*yv-0.5*std::log(detK);
        std::cout<<"sigma="<<params[0]<<", scale="<<params[1]<<" "<<-aux(0,0)<<std::endl;

        return -aux(0,0);
    }


    double myvconstraint_scale_minus(const std::vector<double> &x, std::vector<double> &grad, void *data)
    {
        double a = *reinterpret_cast<double*>(data);

        if (!grad.empty()) {
            throw new std::invalid_argument("We cannot use gradient methods for gaussian process calibration");
        }
        return -(x[1]-a);

    }

    double myvconstraint_scale_plus(const std::vector<double> &x, std::vector<double> &grad, void *data)
    {
        double  a = *reinterpret_cast<double*>(data);

        if (!grad.empty()) {
            throw new std::invalid_argument("We cannot use gradient methods for gaussian process calibration");
        }
        return (x[1]-a);

    }

    double myvconstraint_sigma_plus(const std::vector<double> &x, std::vector<double> &grad, void *data)
    {

        double  a = *reinterpret_cast<double*>(data);
        if (!grad.empty()) {
            throw new std::invalid_argument("We cannot use gradient methods for gaussian process calibration");
        }
        return (x[0]-a);

    }

    double myvconstraint_sigma_minus(const std::vector<double> &x, std::vector<double> &grad, void *data)
    {
        double  a = *reinterpret_cast<double*>(data);
        if (!grad.empty()) {
            throw new std::invalid_argument("We cannot use gradient methods for gaussian process calibration");
        }
        return -(x[0]-a);

    }
}
double deep::GP::SquaredExponentialKernel::kernel(const double &a, const double &b) {
    return kernel_internal(a,b,_sigma,_scale);
}

deep::GP::SquaredExponentialKernel::SquaredExponentialKernel(const double &sigma, const double &scale):_sigma(sigma),_scale(scale) {

}

void deep::GP::SquaredExponentialKernel::CalibrateParameters(const std::vector<std::tuple<double, double>> &values) {
    std::vector<double> x,y;
    double mx(-HUGE_VAL),mn(HUGE_VAL),st;
    for(auto z:values){
        double a,b;
        std::tie(a,b)=z;
        x.push_back(a);
        y.push_back(b);
        if(mn<a){
            mn = a;
        }
        if(mx>a){
            mx = b;
        }
    }

    double d = mx-mn;

    //nlopt::opt opt(nlopt::LN_COBYLA, 2);
    //nlopt::opt opt(nlopt::LN_AUGLAG, 2);
    nlopt::opt opt(nlopt::LN_NELDERMEAD,2);


    std::vector<double> lb(2),ub(2);
    lb[0] = 1.0; lb[1] = 0.1;
    ub[0]= 10.0; ub[1]= 10;

    opt.set_lower_bounds(lb);
    opt.set_upper_bounds(ub);

//    double scale_min=1;
//    double scale_max = 10;
//    double sigma_min = 1;
//    double sigma_max = 20.0;
//
//    opt.add_inequality_constraint(myvconstraint_scale_plus, &scale_max, 1e-8);
//    opt.add_inequality_constraint(myvconstraint_scale_minus,&scale_min, 1e-8);
//
//    opt.add_inequality_constraint(myvconstraint_sigma_plus,  &sigma_max, 1e-8);
//    opt.add_inequality_constraint(myvconstraint_sigma_minus, &sigma_min, 1e-8);

    std::tuple<deep::GP::SquaredExponentialKernel*,std::vector<std::tuple<double,double>>> optdata=
            std::make_tuple(this,values);
    opt.set_min_objective(myvfunc, &optdata);

    opt.set_xtol_rel(1e-16);
    opt.set_ftol_abs(1e-16);
    opt.set_maxeval(10000);

    std::vector<double> xopt(2);
    xopt[0] = 1.0; xopt[1] = 1.0;
    double minf;
    nlopt::result result = opt.optimize(xopt, minf);
    this->setParams(xopt[0],xopt[1]);


    std::cout<<"Setting sigma "<<_sigma<<", scale="<<_scale<<std::endl;

}

double deep::GP::SquaredExponentialKernel::kernel_internal(const double &a, const double &b, const double &sigma,
                                                           const double &scale) {

    double x2 = std::pow((a-b),2);
    double l2 = std::pow(_scale,2);
    double s2 = std::pow(_sigma,2);
    return s2*std::exp(-0.5*x2/l2);
}

void deep::GP::SquaredExponentialKernel::setParams(const double &sigma, const double &scale) {
    _sigma=sigma;
    _scale=scale;
}
