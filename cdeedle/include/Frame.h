//
// Created by fran on 16.04.18.
//

#ifndef DEEP_FRAME_H
#define DEEP_FRAME_H

#include <vector>
#include <string>
#include <eigen3/Eigen/Eigen>
#include <memory>

using Eigen::MatrixXd;

using namespace std;
namespace deep {
    namespace data{

        template<typename K>
        class Frame;

        template<typename K>
        Frame<K> operator+(const Frame<K>& l,const Frame<K> &r);

        template<typename K>
        class Frame {
        public:
            Frame();
            Frame(const vector<K>& rows,const vector<string>& columns,const double& v=std::numeric_limits<double>::quiet_NaN());
            Frame(const vector<K>& rows,const vector<string>& columns,const MatrixXd& m);

            const MatrixXd& GetMatrix();

        protected:
            std::vector<K> _index;
            std::vector<std::string> _columns;
            MatrixXd frame;


            friend Frame operator+<>(const Frame<K>&,const Frame<K>&);



        };

        template<typename K>
        Frame<K>::Frame(const vector<K> &rows, const vector<string> &columns, const MatrixXd &m) {
            frame =  m;
            _index=rows;
            _columns=columns;
        }


        template<typename K>
        Frame<K>::Frame(const vector<K> &rows, const vector<string> &columns,const double& v) {
             frame =  v * Eigen::MatrixXd::Ones(rows.size(),columns.size());
            _index=rows;
            _columns=columns;
        }

        template<typename K>
        Frame<K> operator+(const Frame<K> &l, const Frame<K> &r) {
            return Frame<K>(l._index,l._columns, l.frame+r.frame);
        }

        template<typename K>
        const MatrixXd &Frame<K>::GetMatrix() {
            return frame;
        }


    }


}


#endif //DEEP_FRAME_H
