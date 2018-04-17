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
    Frame<long> f1({1,2,3},{"A","B"},1.0);
    Frame<long> f2({1,2,3},{"A","B"},3.0);
    auto ftotal = f1+f2;

    auto m = ftotal.GetMatrix();
    for(int i=0;i<m.rows();++i)
        for(int j=0;j<m.cols();++j)
            BOOST_CHECK_MESSAGE(m(i,j)==4,"Error in Frame summation");


}
