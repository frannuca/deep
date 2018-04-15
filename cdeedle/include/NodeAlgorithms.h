//
// Created by fran on 02.04.18.
//
#include <vector>
#include <Node.h>
#include <queue>
#include <memory>
#include <stack>
#include <boost/archive/xml_oarchive.hpp>
#include <fstream>
#include <boost/archive/xml_iarchive.hpp>

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
            static const deep::hierarchy::Node<C>* FindNode(const deep::hierarchy::Node<C>* root,const std::string& nodename);

            template<typename C>
            static  std::string Print(const deep::hierarchy::Node <C>* root);

            template<typename C>
            static std::string toXml(const Node<C>* root);

            template<typename C>
            static void WritetoFile(const Node<C>* root,std::string filename);

            template<typename C>
            static Node<C>* LoadFromStream( std::istream& is);

            template<typename C>
            static Node<C>* LoadFromXmlString(const std::string &xmlstring);

            template<typename C>
            static Node<C>* LoadFromFile(const std::string &fileLocation);
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
                for(auto child: node->Children()){
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
                for(auto child:node->Children()){
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

        template<typename C>
        std::string NodeOps::toXml(const Node <C> *root) {
            // make an archive
            std::ostringstream oss;
            boost::archive::xml_oarchive oa(oss);
            oa << BOOST_SERIALIZATION_NVP(root);
            return oss.str();
        }

        template<typename C>
        void NodeOps::WritetoFile(const Node <C> *root,std::string filename) {
            std::ofstream of(filename);
            boost::archive::xml_oarchive oa(of);
            oa << BOOST_SERIALIZATION_NVP(root);
        }

        template<typename C>
        Node <C> *NodeOps::LoadFromStream(std::istream &is) {

            Node<C> * root = new Node<C>("");
            boost::archive::xml_iarchive ia(is);
            // restore the schedule from the archive
            ia >> BOOST_SERIALIZATION_NVP(*root);
            return root;
        }

        template<typename C>
        Node <C> *NodeOps::LoadFromXmlString(const std::string &is) {
            std::istringstream iss(is);
            return NodeOps::LoadFromStream<C>(iss);
        }

        template<typename C>
        Node <C> *NodeOps::LoadFromFile(const std::string &fileLocation) {
            std::ifstream ifs(fileLocation.c_str());
            if(ifs.good()){
                return NodeOps::LoadFromStream<C>(ifs);
            }
            else{
                return nullptr;
            }
        }

        template<typename C>
        const deep::hierarchy::Node<C>* NodeOps::FindNode(const Node <C> *root, const std::string &nodename) {
            std::vector<const deep::hierarchy::Node<C>*>  nodes = BreadthFirstSearch(root);
            auto item=std::find_if(nodes.begin(),nodes.end(),[&nodename](const Node<C>* x){return x->Name()==nodename;});
            if(item != nodes.end())
                return *item;
            else
                return nullptr;
        }


    }

    }
#endif //DEEP_NODEALGORITHMS_H
