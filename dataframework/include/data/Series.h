//
// Created by fran on 07.04.18.
//

#ifndef DEEP_SERIES_H
#define DEEP_SERIES_H
#include <map>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
#include <set>
#include <functional>
#include "NumericDefaults.h"

namespace deep {
    namespace data {


        //Class Series:
        template<typename K, typename C>
        class Series: public Default<C> {
        public:
            //----------------------
            //Ctors
            Series(const std::set<K>& keys,const C& v);

            Series(const std::set<K>& keys);


            //Copy ctors
            Series(const Series<K, C> &that);
            Series(Series<K, C> &&that);


            Series<K,C>& operator=(Series<K,C>&& that);
            Series<K,C>& operator=(const Series<K,C>& that);

            C& operator[](const K& key) const;
            Series<K,C> operator-() ;

            std::set<K> Keys() const;



            template<typename K_, typename C_>
            friend Series<K_,C_> operator+(const Series<K_,C_>& r, const Series<K_,C_>& l);

            template<typename K_, typename C_>
            friend Series<K_,C_> operator*(const Series<K_,C_>& r, const Series<K_,C_>& l);

            template<typename K_, typename C_>
            friend Series<K_,C_> operator*(const C_& s, const Series<K_,C_>& l);

            template<typename K_, typename C_>
            friend Series<K_,C_> operator/(const Series<K_,C_>& l,const Series<K_,C_>& r);

            template<typename K_, typename C_>
            friend Series<K_,C_> operator/(const C_& s,const Series<K_,C_>& r);

        protected:
            mutable std::map<K, C> _data;

        };

        template<typename K,typename C>
        Series<K,C> operator+(const Series<K,C>& r, const Series<K,C>& l){
            auto keys_r = r.Keys();
            auto keys_l = l.Keys();

            std::set<K> intersection, allkeys;

            std::set_intersection(keys_l.begin(),keys_l.end(),keys_r.begin(),keys_r.end(),std::inserter(intersection,intersection.begin()));
            allkeys.insert(keys_l.begin(),keys_l.end());
            allkeys.insert(keys_r.begin(),keys_r.end());

            Series<K,C> sum(allkeys,Series<K,C>::missing);
            for(const K& key:intersection){sum._data[key]=r._data[key]+l._data[key];}

            return std::move(sum);

        };

        template<typename K,typename C>
        Series<K,C> operator-(const Series<K,C>& r, const Series<K,C>& l){
            auto s = -(const_cast<Series<K,C>&>(l));
            return r+ s;
        };

        template<typename K,typename C>
        Series<K,C> operator*(const Series<K,C>& r, const Series<K,C>& l){
            auto keys_r = r.Keys();
            auto keys_l = l.Keys();

            std::set<K> intersection, allkeys;

            std::set_intersection(keys_l.begin(),keys_l.end(),keys_r.begin(),keys_r.end(),std::inserter(intersection,intersection.begin()));
            allkeys.insert(keys_l.begin(),keys_l.end());
            allkeys.insert(keys_r.begin(),keys_r.end());

            Series<K,C> sum(allkeys,Series<K,C>::missing);
            for(const K& key:intersection){sum._data[key]=r._data[key]*l._data[key];}

            return std::move(sum);

        };


        template<typename K,typename C>
        Series<K,C> operator/(const Series<K,C>& l, const Series<K,C>& r){
            auto keys_r = r.Keys();
            auto keys_l = l.Keys();

            std::set<K> intersection, allkeys;

            std::set_intersection(keys_l.begin(),keys_l.end(),keys_r.begin(),keys_r.end(),std::inserter(intersection,intersection.begin()));
            allkeys.insert(keys_l.begin(),keys_l.end());
            allkeys.insert(keys_r.begin(),keys_r.end());

            Series<K,C> sum(allkeys,Series<K,C>::missing);
            for(const K& key:intersection){sum._data[key]=l._data[key]/r._data[key];}

            return std::move(sum);

        };


        template<typename K,typename C>
        Series<K,C> operator/(const Series<K,C>& l, const C& s) {
            return 1.0/s * l;
        }

        template<typename K,typename C>
        Series<K,C> operator/(const C& s,const Series<K,C>& r) {


            std::set<K> allkeys= r.Keys();


            Series<K,C> sum(allkeys,Series<K,C>::missing);
            for(const K& key:allkeys){sum._data[key]=s/r._data[key];}

            return std::move(sum);
        }

        template<typename K,typename C>
        Series<K,C> operator*(const C& s, const Series<K,C>& r) {


            std::set<K> allkeys=r.Keys();

            Series<K,C> sum(allkeys,Series<K,C>::missing);
            for(const K& key:allkeys){sum._data[key]=s*r._data[key];}

            return std::move(sum);
        }


        template<typename K, typename C>
        Series<K, C>::Series(const std::set<K> &keys, const C &v) {
            for(auto key:keys){_data.insert(std::make_pair(key,v));}

        }

        template<typename K,typename C>
        Series<K,C> operator*(const Series<K,C>& r,const C& s) {
            return s*r;
        }


        template<typename K, typename C>
        Series<K, C>::Series(const Series<K, C> &that) {
            _data=that._data;
        }

        template<typename K, typename C>
        Series<K, C>::Series(Series<K, C> &&that) {
            _data = std::move(that._data);
            that._data.clear();
        }

        template<typename K, typename C>
        Series<K, C> &Series<K, C>::operator=(Series<K, C> &&that) {
            _data=that._data;
        }

        template<typename K, typename C>
        Series<K, C> &Series<K, C>::operator=(const Series<K, C> &that) {
            _data = std::move(that._data);
            that._data.clear();
        }

        template<typename K, typename C>
        C &Series<K, C>::operator[](const K &key) const {
            return _data.at(key);
        }

        template<typename K, typename C>
        std::set<K> Series<K, C>::Keys() const {
            std::set<K> keys;
            for(auto kv:_data){keys.insert(kv.first);}
            return std::move(keys);
        }

        template<typename K, typename C>
        Series<K, C> Series<K, C>::operator-()  {
            Series<K,C> series = *this;
            for(typename std::map<K,C>::iterator piter=series._data.begin();piter!=series._data.end();++piter){piter->second*= Series<K,C>::minus;}
            return std::move(series);
        }

        template<typename K, typename C>
        Series<K, C>::Series(const std::set<K> &keys) {
            for(auto key:keys){_data.insert(std::make_pair(key,Series<K, C>::missing));}
        }
    }
}

#endif //DEEP_SERIES_Hi
