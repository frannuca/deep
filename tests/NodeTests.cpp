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

using namespace deep;
using namespace decisiontrees;
BOOST_AUTO_TEST_CASE( trees )
{
    auto root = std::shared_ptr<Node<double>>(new Node<double>("Root"));
    auto child1 = std::shared_ptr<Node<double>>(new Node<double>("Child1"));
    auto child2 = std::shared_ptr<Node<double>>(new Node<double>("Child2"));
    auto child11 = std::shared_ptr<Node<double>>(new Node<double>("Child11"));
    root->withData(0.00111).lock()->withChildren({child1,child2});

    child1->withData(0.999).lock()->withParent(root);
    child2->withData(0.888).lock()->withParent(root);
    auto data11=20.0;
    child11->withParent(child1).lock()->withData(data11);


    auto aa = NodeOps::BreadthFirstSearch((std::shared_ptr<Node<double>>)root);
    auto bb = NodeOps::DepthFirstSearch((std::shared_ptr<Node<double>>)root);
    std::for_each(bb.begin(),bb.end(),[&](std::weak_ptr<Node<double>>& node){std::cout<<node.lock()->Name()<<std::endl;});

    std::vector<std::string> breadthSeq = {"Root","Child1","Child2","Child11"};
    std::vector<std::string> computedBreadthSeq;
    std::transform(std::begin(aa),std::end(aa),std::back_inserter(computedBreadthSeq),[](std::weak_ptr<Node<double>> node){return node.lock()->Name();});

    BOOST_CHECK_MESSAGE(breadthSeq.size()==computedBreadthSeq.size(),"Invalid number of nodes returned by Breadth Search First alorithm");
    //BOOST_EQUAL_COLLECTIONS(breadthSeq.begin(),breadthSeq.end(),computedBreadthSeq.begin(),computedBreadthSeq.end());

    auto child11_found = NodeOps::FindNode(root,"Child11");
    BOOST_CHECK(child11_found.lock()->Name()==child11->Name());

}

// ----------------------------------------------------------------------------------------

