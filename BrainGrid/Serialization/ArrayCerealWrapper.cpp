

#include "ArrayCerealWrapper.h"

template<class T>
ArrayCerealWrapper<T>::ArrayCerealWrapper() {

}

template<class T>
ArrayCerealWrapper<T>::ArrayCerealWrapper(T* thedate, int thesize) {
    if(!thedata) {return;}
    for(int i = 0; i < thesize; i++) {
        thevec.push_back(thedata[i]);
    }
}

template<class T>
T* ArrayCerealWrapper<T>::toArray() {
    return thevec.data();
}

template<class T>
int ArrayCerealWrapper<T>::getSize() {
    return thevec.size();
}
