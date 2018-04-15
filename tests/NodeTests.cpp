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

    NodeOps::WritetoFile(root,fileLocation);

    return root;
}

void
restore_schedule(Node<double> *&s, const char * filename)
{
    // open the archive
    s=NodeOps::LoadFromFile<double>(filename);

}

BOOST_AUTO_TEST_CASE( trees )
{
    std::string filename = "/home/fran/tmp/tree";
    auto root0= createTest(filename);
    Node<double>* root = new Node<double>("dummy");
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


    const Node<double>* child11_found = NodeOps::FindNode<double>(root,"child11");
    BOOST_CHECK_MESSAGE(child11_found!= nullptr,"Finding node child11 failed");

    NodeOps::RemoveNodeFromHierarchy(root,child11_found->Name());
    const Node<double>* child11_foundbis = NodeOps::FindNode<double>(root,"child11");
    BOOST_CHECK_MESSAGE(child11_foundbis== nullptr,"The node was not removed!!");


}

// ----------------------------------------------------------------------------------------

