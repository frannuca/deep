#include <decisiontrees/Node.h>
#include <decisiontrees/NodeAlgorithms.h>
#include <memory>
#include <decisiontrees/Node.h>
#include <stdexcept>

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
    child11->withParent(child1);


    auto aa = NodeOps::BreadthFirstSearch((std::weak_ptr<Node<double>>)root);
    auto bb = NodeOps::DepthFirstSearch((std::weak_ptr<Node<double>>)root);
    std::for_each(bb.begin(),bb.end(),[&](std::weak_ptr<Node<double>>& node){std::cout<<node.lock()->name<<std::endl;});
    //throw new std::invalid_argument("Invalid tree");
    return 0;
}

// ----------------------------------------------------------------------------------------

