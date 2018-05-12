//
// Created by fran on 17.04.18.
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

#include <boost/archive/tmpdir.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

#include <Frame.h>
using namespace deep;
using namespace data;


BOOST_AUTO_TEST_CASE( frames )
{
    std::vector<std::string> cols={"A","B"};
    std::vector<long> rows = {1,2,3};
    Frame<long> f1(rows,cols,1.0);
    Frame<long> f2(rows,cols,3.0);
    auto ftotal = f1+f2;

    auto m = ftotal.GetMatrix();
    for(int i=0;i<m.n_rows;++i)
        for(int j=0;j<m.n_cols;++j)
            BOOST_CHECK_MESSAGE(m(i,j)==4,"Error in Frame summation");

    for(auto i:rows){
        for(auto c:cols)
            BOOST_CHECK_MESSAGE(ftotal(i,c)==4,"Sum of two frame failed");
    }



    std::vector<std::string> rows2={"B","C","A"};
    std::vector<std::string> cols2 = {"Col2","Col1"};


    Frame<std::string> mframe3x2(rows2,cols2,2.0);
    Frame<std::string> mframe2x3(cols2,rows2,5.0);
    Frame<std::string> mframe3x3 = mframe3x2 * mframe2x3;

    mframe3x2.sort_rows();
    mframe3x2.sort_columns();

    BOOST_CHECK_MESSAGE(mframe3x3.ncols()==3 && mframe3x3.nrows()==3,"Frame from multiplication 3x3 is incorrect");
    for(auto i:mframe3x3.GetRows()){
        std::cout<<i<<"  ";
        for(auto c:mframe3x3.GetCols())
            std::cout<<mframe3x3(i,c)<<" ";
        std::cout<<std::endl;
    }



    Frame<std::string> frame2x2prod = mframe3x2 % mframe3x2;
    std::cout<<"   ";
    for(auto c:frame2x2prod.GetCols()) std::cout<<c<<"  ";
    std::cout<<std::endl;
    for(auto i:frame2x2prod.GetRows()){
        std::cout<<i<<"  ";
        for(auto c:frame2x2prod.GetCols())
            std::cout<<frame2x2prod(i,c)<<" ";
        std::cout<<std::endl;
    }

    auto r = frame2x2prod["A"];

    r = arma::ones(1,2);

    std::cout<<"......................."<<std::endl;
    std::cout<<"   ";
    for(auto c:frame2x2prod.GetCols()) std::cout<<c<<"  ";
    std::cout<<std::endl;
    for(auto i:frame2x2prod.GetRows()){
        std::cout<<i<<"  ";
        for(auto c:frame2x2prod.GetCols())
            std::cout<<frame2x2prod(i,c)<<" ";
        std::cout<<std::endl;
    }


    std::vector<std::string> rows_5={"B","C","A","X","Z"};
    std::vector<std::string> cols_3 = {"C3","C2","C1"};

    std::vector<std::string> rows_7={"B","C","A","X","Z","I1","I2"};
    std::vector<std::string> cols_5 = {"C3","C2","C1","CI1","CI2"};


    Frame<std::string> mframe5x3(rows_5,cols_3,7.0);
    Frame<std::string> mframe7x5(rows_7,cols_5,5.0);

    std::cout<<"......................."<<std::endl;
    std::cout<<"   ";
    for(auto c:mframe5x3.GetCols()) std::cout<<c<<"  ";
    std::cout<<std::endl;
    for(auto i:mframe5x3.GetRows()){
        std::cout<<i<<"  ";
        for(auto c:mframe5x3.GetCols())
            std::cout<<mframe5x3(i,c)<<" ";
        std::cout<<std::endl;
    }

    mframe5x3.fillGapWith(mframe7x5,9.0);
    std::cout<<"......................."<<std::endl;
    std::cout<<"   ";
    for(auto c:mframe5x3.GetCols()) std::cout<<c<<"  ";
    std::cout<<std::endl;
    for(auto i:mframe5x3.GetRows()){
        std::cout<<i<<"  ";
        for(auto c:mframe5x3.GetCols())
            std::cout<<mframe5x3(i,c)<<" ";
        std::cout<<std::endl;
    }


}
