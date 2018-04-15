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
#include <boost/uuid/uuid.hpp>            // _uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <boost/uuid/uuid_io.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/ptr_container/serialize_ptr_vector.hpp>


namespace deep {
    namespace hierarchy {

        /**
         * \brief  Node defines a unit within a acyclic graph.
         *
         * Node is used as the unit building block of acyclic dependency tree.
         * @tparam T
         */
        template<typename T>
        class Node {
        public:

            /**
             * construct a new node with the provided name. Other member such as parent or children are left as default
             * @param name : Name of the node
             */
            explicit Node(const std::string &name);



            /**
             * Initializes a new node with the provided name, data and parent
             * @param name Name of the node
             * @param data Data object to be copied into the internal data member.
             * @param parent pointer to the parent node
             */
            Node(const std::string &name, const T &data, std::unique_ptr<Node<T>> parent= nullptr);

            Node(const std::string &name, T &&data, std::unique_ptr<Node<T>> parent= nullptr);


            int depth() const;

            std::string toString() const;

            template<typename... Args>
            void AddChildren(Node<T>* first, Args... args);


            std::string _name;
            std::string _uuid;

            const Node<T>& GetChild(int n);

            T& Data() const;
            void set_parent(Node<T>* p);
            typename boost::ptr_vector<Node<T>>::iterator begin() const;
            typename boost::ptr_vector<Node<T>>::iterator end() const ;

        private:
            /**
             * Default ctors. This constructure is only used for serialization operations
             */
            Node();
            Node(const Node<T> &that);
            template<typename... Args>
            void AddChildren();

            friend class boost::serialization::access;
            template<class Archive>
            void serialize(Archive & ar, const unsigned int version);


            Node(Node<T> &&that);
            Node<T> &operator=(const Node<T> &that);
            Node<T> &operator=(Node<T> &&that);

        protected:

            static boost::uuids::random_generator generator;
            mutable boost::ptr_vector<Node<T>> m_children;
            Node<T>* m_parent;
            mutable T m_data;

        };

        template<typename T>
        boost::uuids::random_generator Node<T>::generator;

        template<typename T>
        Node<T>::Node(const std::string &name):_name(name),_uuid(boost::uuids::to_string(generator())) {

        }

        template<typename T>
        Node<T>::Node(const std::string &name, const T &data, std::unique_ptr<Node<T>> parent):m_parent(parent.get()),_name(name),_uuid(boost::uuids::to_string(generator())) {
            m_data=data;
        }

        template<typename T>
        Node<T>::Node(const std::string &name,  T &&data, std::unique_ptr<Node<T>> parent):m_parent(parent.get()),_name(name),_uuid(boost::uuids::to_string(generator())) {
            m_data= std::move(data);
        }

        template<typename T>
        template<class Archive>
        void Node<T>::serialize(Archive &ar, const unsigned int version) {

            ar & boost::serialization::make_nvp("children", m_children);
            ar & boost::serialization::make_nvp("parent", m_parent);
            ar & boost::serialization::make_nvp("name", _name);
            ar & boost::serialization::make_nvp("uuid", _uuid);
            ar & boost::serialization::make_nvp("data", m_data);

        }



        template<typename T>
        T &Node<T>::Data() const{
            return m_data;
        }

        template<typename T>
        const Node<T>& Node<T>::GetChild(int n) {
            return m_children.at(0);
        }

        template<typename T>
        typename boost::ptr_vector<Node<T>>::iterator
        Node<T>::begin() const {
            return m_children.begin();
        }

        template<typename T>
        typename boost::ptr_vector<Node<T>>::iterator
        Node<T>::end() const {
            return m_children.end();
        }

        template<typename T>
        template<typename... Args>
        void Node<T>::AddChildren() {

        }

        template<typename T>
        template<typename... Args>
        void Node<T>::AddChildren(Node<T> *first, Args... args) {
            m_children.push_back(first);
            first->set_parent(this);
            AddChildren(args ...);
        }

        template<typename T>
        Node<T>::Node(const Node<T> &that):_name(that._name),_uuid(that._uuid),m_children(that.m_children),m_parent(that.m_parent) {
            that.m_children.clear();
            auto thatagain = that.m_children;
        }

        template<typename T>
        Node<T>::Node() {

        }

        template<typename T>
        int Node<T>::depth() const {
            int depth=0;
            int maxdepth=20000;
            const Node<T>* node = this;
            while(node->m_parent != nullptr){
                ++depth;
                if(depth>maxdepth){
                    throw "cyclic tree detected while computing depth";
                }
                node = node->m_parent;
            }

            return depth;

        }



        template<typename T>
        void Node<T>::set_parent(Node<T> *p) {
            this->m_parent=p;
        }

        template<typename T>
        std::string Node<T>::toString() const {
            std::ostringstream os;
            auto d = depth();
            os<<std::string(depth(),'\t')<<_name<<"("<<_uuid<<","<<m_data<<")";

            return os.str();
        }


    }
}

#endif //DEEP_NODE_H


