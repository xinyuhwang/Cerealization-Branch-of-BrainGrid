

#include "MatrixCerealWrapper.h"

template<class T>
MatrixCerealWrapper<T>::MatrixCerealWrapper() {

}

template<class T>
MatrixCerealWrapper<T>::MatrixCerealWrapper(T** thedata, int rowsize, int colsize) {

    if(!thedata || !thedata[0]) {return;}

    theMatrix(rowsize, vector<T>(colsize));

    for(int i = 0; i < rowsize; i++) {
        for(int j = 0; j < colsize; j++) {
            theMatrix[i][j] = *(thedata + (i*colsize+j));
        }
    }
}

//TODO::delete memory
template<class T>
T** MatrixCerealWrapper<T>::toMatrix() {
    T** twodArray = new T*[theMatrix.size()];
    for(int i = 0; i < theMatrix.size(); i++) {
        
        twodArray[i] = new T[theMatrix[0].size()]; 

        for(int j = 0; j < theMatrix[0].size(); j++) {
            twodArray[i][j] = theMatrix[i][j];
        }
    }
    return twodArray;
}

template<class T>
int MatrixCerealWrapper<T>::getRowSize() {
    return theMatrix.size();
}

template<class T>
int MatrixCerealWrapper<T>::getColSize() {
    return theMatrix[0].size();
}
