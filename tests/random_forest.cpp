#include <decisiontrees/Node.h>
#include <decisiontrees/NodeAlgorithms.h>
#include <memory>
#include <decisiontrees/Node.h>
#include <stdexcept>
#include <algorithm>
#include <cctype>

using namespace deep;
using namespace decisiontrees;
int main(int argc, char** argv)
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
    std::for_each(bb.begin(),bb.end(),[&](std::weak_ptr<Node<double>>& node){std::cout<<node.lock()->name<<std::endl;});

    std::vector<std::string> breadthSeq = {"Root","Child1","Child2","Child11"};
    std::vector<std::string> computedBreadthSeq;
    std::transform(std::begin(aa),std::end(aa),std::back_inserter(computedBreadthSeq),[](std::weak_ptr<Node<double>> node){return node.lock()->name;});

    if(breadthSeq.size()!=computedBreadthSeq.size()){
        throw "Invalid number of nodes returned by Breadth Search First alorithm";
    }
    else{
        for(int i=0;i<breadthSeq.size();++i){
            if(breadthSeq[i]!=computedBreadthSeq[i]){
                throw "Invalid Node order. Node"+breadthSeq[i]+" is not matching returned "+computedBreadthSeq[i];
            }
        }
    }
    return 0;
}

// ----------------------------------------------------------------------------------------

