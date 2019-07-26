
#pragma once

#include <vector>

using namespace std;

template <class T>
class MatrixCerealWrapper {
    private:
        vector< vector<T> > theMatrix;
    public:
        MatrixCerealWrapper();
        MatrixCerealWrapper(T** thedata, int rowsize, int colsize);
        T** toMatrix();
        int getRowSize();
        int getColSize();

        template<class Archive>
        void serialize(Archive & archive);

};

template<class T>
template<class Archive>
void MatrixCerealWrapper<T>::serialize(Archive & archive) {
    archive(theMatrix);
}