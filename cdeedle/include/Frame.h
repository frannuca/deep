//
// Created by fran on 16.04.18.
//

#ifndef DEEP_FRAME_H
#define DEEP_FRAME_H

#include <vector>
#include <string>
#include <armadillo>
#include <memory>
#include <boost/range/combine.hpp>
#include <map>
#include <algorithm>

using namespace std;
namespace deep {
    namespace data{

        template<typename K>
        class Frame;

        template<typename K>
        Frame<K> operator+(const Frame<K>& l,const Frame<K> &r);

        template<typename K>
        Frame<K> operator*(const Frame<K>& l,const Frame<K> &r);

        template<typename K>
        Frame<K> operator%(const Frame<K>& l,const Frame<K> &r);

        template<typename K>
        class Frame {
        public:
            Frame();
            Frame(const vector<K>& rows,const vector<string>& columns,const double& v=std::numeric_limits<double>::quiet_NaN());
            Frame(const vector<K>& rows,const vector<string>& columns,const arma::mat & m);
            arma::subview<double>&& operator[](const K& row) const;
            double & operator()(const K& row,const string& col) const;

            const std::vector<std::string> GetCols() const;
            const std::vector<K> GetRows() const;
            const arma::mat& GetMatrix() const;

            unsigned long ncols() const;

            unsigned long nrows() const;

            const Frame<K>& sort_rows(bool descendent=false) const;

            const Frame<K>& sort_columns(bool descendent=false) const;
            bool check_compatibility(const Frame<K>& that);

            void fillGapWith(const Frame<K> &that, double v);

        protected:
            void initmappings();
            mutable std::vector<K> _index;
            mutable std::vector<std::string> _columns;
            mutable std::map<K,int> _rowmap;
            mutable std::map<std::string,int> _columnmap;
            mutable arma::mat frame;



            friend Frame operator+<>(const Frame<K>&,const Frame<K>&);
            friend Frame operator*<>(const Frame<K>&,const Frame<K>&);
            friend Frame operator%<>(const Frame<K>&,const Frame<K>&);



        };

        template<typename K>
        Frame<K>::Frame(const vector<K> &rows, const vector<string> &columns, const arma::mat &m) {
            frame =  m;
            _index=rows;
            _columns=columns;
            initmappings();
        }


        template<typename K>
        Frame<K>::Frame(const vector<K> &rows, const vector<string> &columns,const double& v) {
             frame =  v * arma::ones(rows.size(),columns.size());
            _index=rows;
            _columns=columns;
            initmappings();
        }

        template<typename K>
        Frame<K> operator+(const Frame<K> &l, const Frame<K> &r) {
            const Frame<K>& fl = l.sort_columns().sort_rows();

            const Frame<K>& fr = r.sort_columns().sort_rows();
            return Frame<K>(fl._index,fl._columns, fl.frame + fr.frame);
        }

        template<typename K>
        Frame<K> operator*(const Frame<K> &l, const Frame<K> &r) {
            auto fl = l.sort_columns().sort_rows();
            auto fr = r.sort_columns().sort_rows();
            return Frame<K>(l._index,r._columns,(arma::mat)(fl.frame*fr.frame));
        }

        template<typename K>
        Frame<K> operator%(const Frame<K> &l, const Frame<K> &r) {
            return Frame<K>(l.GetRows(),l.GetCols(),l.frame%r.frame);
        }

        template<typename K>
        const arma::mat &Frame<K>::GetMatrix() const {
            return frame;
        }

        template<typename K>
        arma::subview<double>&& Frame<K>::operator[](const K &row) const {
            return std::move(frame.row(((arma::uword )(_rowmap.at(row)))));
        }

        template<typename K>
        double &Frame<K>::operator()(const K &row, const string &col) const{
            int i=_rowmap.at(row);
            int j=_columnmap.at(col);
            return frame(i,j);
        }

        template<typename K>
        const vector<K> Frame<K>::GetRows() const {
            return _index;
        }

        template<typename K>
        const std::vector<std::string> Frame<K>::GetCols() const {
            return _columns;
        }

        template<typename K>
        unsigned long Frame<K>::ncols() const {
            return _columns.size();
        }

        template<typename K>
        unsigned long Frame<K>::nrows() const {
            return _index.size();
        }

        template<typename K>
        const Frame<K>& Frame<K>::sort_rows(bool descendent) const {

            std::vector<K> nindex = _index;
            if(descendent){
                std::sort(nindex.begin(),nindex.end(),[](const K &a,const K &b){return a>=b;});
            }
            else{
                std::sort(nindex.begin(),nindex.end());
            }

            int counter=0;
            for(auto index:nindex){
                auto piter = std::find(_index.begin(),_index.end(),index);
                auto d = std::distance(_index.begin(),piter);
                _rowmap[index]=counter;
                frame.swap_rows(counter++,d);
            }
            _index=nindex;
            return *this;
        }



        template<typename K>
        Frame<K>::Frame() {

        }

        template<typename K>
        const Frame<K>& Frame<K>::sort_columns(bool descendent) const {
            std::vector<std::string> nindex = _columns;
            if(descendent){
                std::sort(nindex.begin(),nindex.end(),[](const std::string &a,const std::string &b){return a>=b;});
            }
            else{
                std::sort(nindex.begin(),nindex.end());
            }

            int counter=0;
            for(auto index:nindex){
                auto piter = std::find(_columns.begin(),_columns.end(),index);
                auto d = std::distance(_columns.begin(),piter);
                _columnmap[index]=counter;
                frame.swap_cols(counter++,d);

            }
            _columns=nindex;
            return *this;
        }

        template<typename K>
        void Frame<K>::initmappings() {
            int counter=0;
            for(auto i:_index) _rowmap.insert(std::make_pair(i,counter++));
            counter=0;
            for(auto c:_columns) _columnmap.insert(std::make_pair(c,counter++));
        }

        template<typename K>
        bool Frame<K>::check_compatibility(const Frame<K> &that) {
            auto o1 = sort_rows().sort_columns();
            auto o2 = that.sort_rows().sort_columns();

            return o1._index==o2._index && o1._columns==o2._columns;
        }

        template<typename K>
        void Frame<K>::fillGapWith(const Frame<K> &that, double v) {
            if(!check_compatibility(that)){
                std::vector<K> newindex=_index;

                for(const K &i:that._index){
                    if(std::find(newindex.begin(),newindex.end(),i)==newindex.end()){
                        frame.insert_rows(frame.n_rows,1,true);
                        frame.row(frame.n_rows-1)=arma::ones(1,frame.n_cols)*v;
                        newindex.push_back(i);
                        _rowmap[i]=newindex.size()-1;
                    }

                }
                _index=newindex;

                std::vector<std::string> newcolumns=_columns;

                for(const std::string &i:that._columns){
                    if(std::find(newcolumns.begin(),newcolumns.end(),i)==newcolumns.end()){
                        frame.insert_cols(frame.n_cols,1,v);
                        newcolumns.push_back(i);
                        frame.col(frame.n_cols-1)=arma::ones(frame.n_rows,1)*v;
                        _columnmap[i]=newcolumns.size()-1;
                    }
                }

                _columns=newcolumns;
            }
        }

    }


}


#endif //DEEP_FRAME_H
