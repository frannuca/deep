//
// Created by fran on 01.04.18.
//

#ifndef DEEP_NODE_H
#define DEEP_NODE_H

#include <memory>
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <sstream>
#include <cassert>
#include <vector>
#include <iterator>
#include <algorithm>

namespace deep {
    namespace decisiontrees {

        template<typename T>
        class Node : public std::enable_shared_from_this<Node<T>> {
        public:
            std::string name;
            T m_data;
            std::vector<std::shared_ptr<Node<T> > >  m_children;
            std::weak_ptr<Node<T>> m_parent;
        public:
            Node(const std::string& nodeName);
            Node(std::string&& nodeName);

            std::weak_ptr<Node<T>>  withChildren(std::initializer_list<std::shared_ptr<Node<T>>> children);
            void RemoveChild(std::shared_ptr<Node<T>> child);
            bool HasChild(std::shared_ptr<Node<T>> child);
            std::weak_ptr<Node<T>> withParent(std::weak_ptr<Node<T>> parent);
            std::weak_ptr<Node<T>>  withData(T&& data);
            std::weak_ptr<Node<T>>  withData(const T& data);


        };

        template<typename T>
        Node<T>::Node(const std::string& nodeName):name(nodeName){

        }
        template<typename T>
        Node<T>::Node(std::string&& nodeName):name(nodeName){

        }



        template <typename T>
        std::weak_ptr<Node<T>> Node<T>::withChildren(std::initializer_list<std::shared_ptr<Node<T>>> children){
            auto ptr = this->shared_from_this();
            for(auto child: children){
                if(!HasChild(child)){
                    m_children.push_back(child);
                    if(child->m_parent.lock() != ptr){
                        child->withParent(ptr);
                    }
                }
            }
            return this->shared_from_this();
        }

        template<typename T>
        void Node<T>::RemoveChild(std::shared_ptr<Node<T>> child) {
                m_children.erase(std::remove(m_children.begin(),m_children.end(),child));
        }

        template<typename T>
        bool Node<T>::HasChild(std::shared_ptr<Node<T>> child) {
            return std::find(m_children.begin(),m_children.end(),child) != m_children.end();
        }

        template<typename T>
        std::weak_ptr<Node<T>> Node<T>::withData(T &&data) {
            m_data=data;
            return this->shared_from_this();

        }

        template<typename T>
        std::weak_ptr<Node<T>> Node<T>::withData(const T &data) {
            m_data=data;
            return this->shared_from_this();
        }

        template<typename T>
        std::weak_ptr<Node<T>>  Node<T>::withParent(std::weak_ptr<Node<T>> parent) {
            m_parent = parent;
            m_parent.lock()->withChildren({this->shared_from_this()});
            return this->shared_from_this();
        }
    }
}

#endif //DEEP_NODE_H
