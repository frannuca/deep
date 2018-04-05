//
// Created by fran on 02.04.18.
//
#include <vector>
#include <decisiontrees/Node.h>
#include <queue>
#include <memory>
#include <stack>

#ifndef DEEP_NODEALGORITHMS_H
#define DEEP_NODEALGORITHMS_H
namespace deep {
    namespace decisiontrees {

        class NodeOps{
        public:
            template<typename C>
            static std::vector<std::weak_ptr<deep::decisiontrees::Node<C>>> BreadthFirstSearch(std::shared_ptr<deep::decisiontrees::Node<C>> root);

            template<typename C>
            static std::vector<std::weak_ptr<deep::decisiontrees::Node<C>>> DepthFirstSearch(std::shared_ptr<deep::decisiontrees::Node<C>> root);

            template<typename C>
            static std::weak_ptr<deep::decisiontrees::Node<C>> FindNode(std::shared_ptr<deep::decisiontrees::Node<C>> root);


        };

        template<typename C>
        std::vector<std::weak_ptr<deep::decisiontrees::Node<C>>> deep::decisiontrees::NodeOps::BreadthFirstSearch(std::shared_ptr<deep::decisiontrees::Node <C>> root) {
            std::queue<std::shared_ptr<deep::decisiontrees::Node<C>>> queue;
            queue.push(root);
            std::vector<std::weak_ptr<Node<C>>> listofnodes;
            while(!queue.empty()){
                auto node = queue.front();
                queue.pop();
                listofnodes.push_back(node);
                for(auto child: node->m_children){
                    queue.push(child);
                }
            }

        return listofnodes;
        }

        template<typename C>
        std::vector<std::weak_ptr<deep::decisiontrees::Node< C>>>  NodeOps::DepthFirstSearch(std::shared_ptr<deep::decisiontrees::Node < C>> root) {
        std::stack<std::shared_ptr< deep::decisiontrees::Node<C>> > stack;
        stack.push(root);
        std::vector<std::weak_ptr<deep::decisiontrees::Node<C>>> listofnodes;
        while(!stack.empty()){
            auto node = stack.top();
            stack.pop();
            listofnodes.push_back(node);
            std::for_each(node->m_children.begin(),node->m_children.end(),[&stack](std::shared_ptr<Node<C>> piter){stack.push(piter);});
        }
        
        return listofnodes;
    }

    template<typename C>
    std::weak_ptr<deep::decisiontrees::Node<C>> NodeOps::FindNode(std::shared_ptr<deep::decisiontrees::Node<C>> root){
            auto nodes = BreadthFirstSearch(root);

        }

    }

    }
#endif //DEEP_NODEALGORITHMS_H
