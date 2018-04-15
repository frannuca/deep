//
// Created by fran on 02.04.18.
//
#include <vector>
#include <Node.h>
#include <queue>
#include <memory>
#include <stack>

#ifndef DEEP_NODEALGORITHMS_H
#define DEEP_NODEALGORITHMS_H
namespace deep {
    namespace hierarchy {

        class NodeOps{
        public:
            template<typename C>
            static std::vector<const deep::hierarchy::Node<C>*> BreadthFirstSearch(const deep::hierarchy::Node <C>* root);

            template<typename C>
            static  std::vector<const deep::hierarchy::Node<C>*>  DepthFirstSearch(const deep::hierarchy::Node <C>* root);

            template<typename C>
            static std::weak_ptr<deep::hierarchy::Node<C>> FindNode(std::shared_ptr<deep::hierarchy::Node<C>> root,const std::string& nodename);

            template<typename C>
            static  std::string Print(const deep::hierarchy::Node <C>* root);

        };

        template<typename C>
        std::vector<const deep::hierarchy::Node<C>*> deep::hierarchy::NodeOps::BreadthFirstSearch(const deep::hierarchy::Node <C>* root) {
            std::queue<const deep::hierarchy::Node<C>*> queue;
            queue.push(root);
            std::vector<const Node<C>*> listofnodes;
            while(!queue.empty()){
                const Node<C>* node = queue.front();
                queue.pop();
                listofnodes.push_back(node);
                for(auto child= node->begin();child != node->end();++child){
                    queue.push(&*child);
                }
            }

        return listofnodes;
        }

        template<typename C>
        std::vector<const deep::hierarchy::Node<C>*> deep::hierarchy::NodeOps::DepthFirstSearch(const deep::hierarchy::Node <C>* root) {
            std::stack<const deep::hierarchy::Node<C>*> stack;
            stack.push(root);
            std::vector<const Node<C>*> listofnodes;
            while(!stack.empty()){
                const Node<C>* node = stack.top();
                stack.pop();
                listofnodes.push_back(node);
                for(auto child= node->begin();child != node->end();++child){
                    const Node<C>& p = *child;
                    stack.push(&p);
                }
            }

            return listofnodes;
        }


//    template<typename C>
//    std::weak_ptr<deep::hierarchy::Node<C>> NodeOps::FindNode(std::shared_ptr<deep::hierarchy::Node<C>> root,const std::string& nodename){
//            auto nodes = BreadthFirstSearch(root);
//            auto iter = std::find_if(nodes.begin(),nodes.end(),[&nodename](std::weak_ptr<Node<C>>& x){return x.lock()->Name()==nodename;});
//            if(iter != nodes.end()) return *iter;
//            else std::weak_ptr<deep::hierarchy::Node<C>>();
//        }

        template<typename C>
        std::string NodeOps::Print(const Node <C> *root) {
            std::ostringstream os;
            auto nodes = DepthFirstSearch(root);

            for(const Node<C>* node:nodes){
                os<<node->toString()<<std::endl;
            }

            return os.str();
        }
    }

    }
#endif //DEEP_NODEALGORITHMS_H
