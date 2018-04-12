#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE "DeepTests"
#include <boost/test/unit_test.hpp>

#include <data/Series.h>
#include <data/NumericDefaults.h>
#include <memory>
#include <hierarchy/Node.h>
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <set>
using namespace deep;
using namespace data;


#include <boost/test/unit_test.hpp>
BOOST_AUTO_TEST_CASE( series )
{
    std::set<std::string> keys={"A","B","C"};

    //testing ctors
    {
        //Constructor
        {
            Series<std::string,double> seriesa(keys,1.0);
            BOOST_CHECK(seriesa["A"]==1.0 && seriesa["B"]== 1.0 && seriesa["C"] == 1.0);

        }

        {

            Series<std::string,double> series(keys);
            auto nan_as_default_value=
            series["A"]!=series["A"] &&
            series["B"]!= series["B"] &&
            series["C"]!=series["C"];

            BOOST_CHECK(nan_as_default_value);
        }
        {
            Series<std::string,double> seriesa(keys,1.0);
            Series<std::string,double> series(seriesa);
            auto values_from_cpy_ctor=series["A"]==seriesa["A"] &&
                       series["B"]==seriesa["B"] &&
                       series["C"]==seriesa["C"];
            BOOST_CHECK(values_from_cpy_ctor);

        }

        {
            Series<std::string,double> seriesa(keys,1.0);
            Series<std::string,double> series(std::move(seriesa));
            auto values_from_move_ctor=series["A"]==1.0 &&
                       series["B"]==1.0 &&
                       series["C"]==1.0  &&
                       seriesa.Keys().size()==0;
            BOOST_CHECK(values_from_move_ctor);

        }
        {
            Series<std::string,double> seriesa(keys);
            seriesa["A"]=1.0;
            seriesa["B"]=2.0;
            seriesa["C"]=3.0;

            Series<std::string,double> series= seriesa;
            auto values_from_cpy_ctro_and_different_numbers = series["A"]== seriesa["A"]&&
                         series["B"]==seriesa["B"] &&
                         series["C"]==seriesa["C"];
            BOOST_CHECK(values_from_cpy_ctro_and_different_numbers);

        }
        {
            Series<std::string,double> series(keys);
            series["A"]=1.0;
            series["B"]=2.0;
            series["C"]=3.0;

            Series<std::string,double> series_cpy= series;
            Series<std::string,double> series_move = std::move(series);
            auto copy_ctr_vs_move_ctor= series_cpy["A"]== series_move["A"]&&
                        series_cpy["B"]==series_move["B"] &&
                        series_cpy["C"]==series_move["C"] &&
                        series.Keys().size()==0;
            BOOST_CHECK(copy_ctr_vs_move_ctor);
        }

    }
//testing sum
    {
        double val1=1.0;
        double val2=2.0;
        double sum=val1+val2;
        Series<std::string,double> seriesa(keys,val1);
        Series<std::string,double> seriesb(keys,val2);

        auto sumofseries = seriesa+seriesb;

        BOOST_CHECK(sumofseries["A"]==sum && sumofseries["B"]==sum && sumofseries["C"]==sum);
    }


    {
        double val1=1.0;
        double val2=2.0;
        double sub=val1-val2;
        Series<std::string,double> seriesa(keys,val1);
        Series<std::string,double> seriesb(keys,val2);

        auto sumofseries = seriesa-seriesb;

        BOOST_CHECK(sumofseries["A"]==sub && sumofseries["B"]==sub && sumofseries["C"]==sub);
    }


    {
        double val1=3.0;
        double val2=2.0;
        double prod=val1*val2;
        Series<std::string,double> seriesa(keys,val1);
        Series<std::string,double> seriesb(keys,val2);

        auto sumofseries = seriesa*seriesb;

        BOOST_CHECK(sumofseries["A"]==prod && sumofseries["B"]==prod && sumofseries["C"]==prod);
    }

    {
        double val1=8.0;
        double val2=2.0;
        double prod=val1/val2;
        Series<std::string,double> seriesa(keys,val1);
        Series<std::string,double> seriesb(keys,val2);

        auto sumofseries = seriesa/seriesb;

        BOOST_CHECK(sumofseries["A"]==prod && sumofseries["B"]==prod && sumofseries["C"]==prod);
    }


    {
        double val1=8.0;
        double val2=2.0;
        double prod=val1/val2;
        Series<std::string,double> seriesa(keys,val1);
        Series<std::string,double> seriesb(keys,val2);

        auto sumofseries = seriesa/val2;

        BOOST_CHECK(sumofseries["A"]==prod && sumofseries["B"]==prod && sumofseries["C"]==prod);
    }

    {
        double val1=8.0;
        double val2=2.0;
        double prod=val1/val2;

        Series<std::string,double> seriesb(keys,val2);

        auto sumofseries = val1/seriesb;

        BOOST_CHECK(sumofseries["A"]==prod && sumofseries["B"]==prod && sumofseries["C"]==prod);
    }

    {
        double val2=8.0;
        double val1=2.0;
        double prod=val2/val1;

        Series<std::string,double> seriesb(keys,val2);

        auto sumofseries = seriesb/val1;

        BOOST_CHECK(sumofseries["A"]==prod && sumofseries["B"]==prod && sumofseries["C"]==prod);
    }
}