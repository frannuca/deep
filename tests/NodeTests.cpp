#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE "DeepTests"
#include <boost/test/unit_test.hpp>

#include <Node.h>
#include <NodeAlgorithms.h>
#include <memory>
#include <Node.h>
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

using namespace deep;
using namespace hierarchy;

void saveTest( const Node<double> &test, const char* filename)
{
    // make an archive
    std::ofstream ofs(filename);
    boost::archive::xml_oarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(test);
}

Node<double>* createTest(const std::string& fileLocation)
{
    Node<double>* root = new Node<double>("root",0.01);
    Node<double>* child1 = new Node<double>("child1",1.0);
    Node<double>* child2 = new Node<double>("child2",3.0);
    Node<double>* child3 = new Node<double>("child3",3.0);
    root->AddChildren(child1,child2,child3);


    Node<double>* child11 = new Node<double>("child11",11.0);
    Node<double>* child12 = new Node<double>("child12",12.0);
    Node<double>* child13 = new Node<double>("child13",13.0);

    child1->AddChildren(child11,child12,child13);


    Node<double>* child21 = new Node<double>("child21",21.0);
    Node<double>* child22 = new Node<double>("child22",22.0);
    Node<double>* child23 = new Node<double>("child23",23.0);

    child2->AddChildren(child21,child22,child23);

    saveTest( *root, fileLocation.c_str() );

    return root;
}

void
restore_schedule(Node<double> *s, const char * filename)
{
    // open the archive
    std::ifstream ifs(filename);
    assert(ifs.good());
    boost::archive::xml_iarchive ia(ifs);

    // restore the schedule from the archive
    ia >> BOOST_SERIALIZATION_NVP(*s);
}

BOOST_AUTO_TEST_CASE( trees )
{
    std::string filename = "/home/fran/tmp/tree";
    auto root0= createTest(filename);
    Node<double>* root = new Node<double>("root");
    restore_schedule(root,filename.c_str());
    std::cout<<"finished \n";

    std::cout<<NodeOps::Print(root0)<<std::endl;

    
    std::cout<<NodeOps::Print(root)<<std::endl;
    BOOST_CHECK_MESSAGE(root0->toString()==root->toString(),"Deserialized node does not match original");

    auto breadth = NodeOps::BreadthFirstSearch(root);
    for(auto n=breadth.begin();n!=breadth.end();++n){
        const Node<double>* p = *n;
        std::cout<<p->toString()<<std::endl;
    }

//    auto root = std::shared_ptr<Node<double>>(new Node<double>("Root"));
//    auto child1 = std::shared_ptr<Node<double>>(new Node<double>("Child1"));
//    auto child2 = std::shared_ptr<Node<double>>(new Node<double>("Child2"));
//    auto child11 = std::shared_ptr<Node<double>>(new Node<double>("Child11"));
//    root->withData(0.00111).lock()->withChildren({child1,child2});
//
//    child1->withData(0.999).lock()->withParent(root);
//    child2->withData(0.888).lock()->withParent(root);
//    auto data11=20.0;
//    child11->withParent(child1).lock()->withData(data11);
//
//
//    auto aa = NodeOps::BreadthFirstSearch((std::shared_ptr<Node<double>>)root);
//    auto bb = NodeOps::DepthFirstSearch((std::shared_ptr<Node<double>>)root);
//    std::for_each(bb.begin(),bb.end(),[&](std::weak_ptr<Node<double>>& node){std::cout<<node.lock()->Name()<<std::endl;});
//
//    std::vector<std::string> breadthSeq = {"Root","Child1","Child2","Child11"};
//    std::vector<std::string> computedBreadthSeq;
//    std::transform(std::begin(aa),std::end(aa),std::back_inserter(computedBreadthSeq),[](std::weak_ptr<Node<double>> node){return node.lock()->Name();});
//
//    BOOST_CHECK_MESSAGE(breadthSeq.size()==computedBreadthSeq.size(),"Invalid number of nodes returned by Breadth Search First alorithm");
//    //BOOST_EQUAL_COLLECTIONS(breadthSeq.begin(),breadthSeq.end(),computedBreadthSeq.begin(),computedBreadthSeq.end());
//
//    auto child11_found = NodeOps::FindNode(root,"Child11");
//    BOOST_CHECK(child11_found.lock()->Name()==child11->Name());

}

// ----------------------------------------------------------------------------------------

