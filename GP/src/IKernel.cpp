//
// Created by fran on 12.05.18.
//

#include "../include/IKernel.h"
#include <assert.h>
#include <exception>
#include <armadillo>


void printmatrix(const std::string& name,const arma::mat& m){
    std::cout<<std::endl;
    std::cout<<name<<std::endl;
    for(int i=0;i<m.n_rows;++i){
        for(int j=0;j<m.n_cols;++j){
            std::cout<<m(i,j)<<" ";
        }
        std::cout<<std::endl;
    }
}

void deep::GP::IKernel::Compute(const std::vector<std::tuple<double, double>> &values, const std::vector<double> &xnew,
                                arma::mat &mu, arma::mat &cov) {

    int szOld = values.size();
    int szNew = xnew.size();
    int sztot = szNew+szOld;
    arma::mat Kt(sztot,sztot,arma::fill::zeros);
    arma::mat Koo(szOld,szOld,arma::fill::zeros);
    arma::mat Kon(szOld,szNew,arma::fill::zeros);
    arma::mat Knn(szNew,szNew,arma::fill::zeros);

    //filling known iteractions on existing points
    std::vector<double> x,y;
    for(int i=0;i<szOld;++i){

        double xi,yi;
        std::tie(xi,yi)=values.at(i);
        x.push_back(xi);
        y.push_back(yi);

        for(int j=0;j<szOld;++j){
            double xj,yj;
            std::tie(xj,yj)=values.at(j);
            Koo(i,j)=kernel(xi,xj);
        }

    }


    //filling interactions in beween o(ld) and n(ew) points
    for(int i=0;i<szOld;++i){
        for(int j=0;j<szNew;++j){
            Kon(i,j)=kernel(x[i],xnew[j]);
        }
    }

    //filling interactions in beween n(ew) and n(ew) points
    for(int i=0;i<szNew;++i){
        for(int j=0;j<szNew;++j){
            Knn(i,j)=kernel(xnew[i],xnew[j]);
        }
    }

    printmatrix("KOO",Koo);
    printmatrix("KON",Kon);
    printmatrix("KNN",Knn);

    //assembling the whole matrix:
    Kt.submat(0,0,szOld-1,szOld-1)=Koo;
    Kt.submat(szOld,szOld,szOld+szNew-1,szOld+szNew-1)=Knn;
    Kt.submat(szOld,0,szOld+szNew-1,szOld-1)=Kon.t();
    Kt.submat(0,szOld,szOld-1,szOld+szNew-1)=Kon;

    arma::mat iKoo = arma::inv(Koo);
    arma::mat xnewvector(xnew);
    arma::mat yvec(y);
    mu = Kon.t() * iKoo * yvec;
    cov = Knn - Kon.t()*iKoo*Kon;
}

deep::GP::IKernel::IKernel() {

}

