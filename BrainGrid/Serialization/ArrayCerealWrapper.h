
#pragma once


#include <vector>


using namespace std;

template <class T>
class ArrayCerealWrapper {
    private:
        vector<T> thevec;
    public:
        ArrayCerealWrapper();
        ArrayCerealWrapper(T* thedate, int thesize);
        T* toArray();
        int getSize();

        template<class Archive>
        void serialize(Archive & archive);

};

template<class T>
template<class Archive>
void ArrayCerealWrapper<T>::serialize(Archive & archive) {
    archive(thevec);
}

