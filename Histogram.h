#ifndef __HISTOGRAM_H_INCLUDED__
#define __HISTOGRAM_H_INCLUDED__
#include <vector>
#include <sstream>
<<<<<<< HEAD
#include <algorithm>  
=======
>>>>>>> de01e4110c8f7db6d2a14471596b93464cf1f880


template<typename Number>
std::vector<int> bin(
    int, //numbins 
    const Number&, //min 
    const Number&, //max
    const std::vector<Number>& //data
);
template<typename Number, typename WS>
void binAndSend(
<<<<<<< HEAD
    const WS&, 
=======
    WS&, 
>>>>>>> de01e4110c8f7db6d2a14471596b93464cf1f880
    int, //numbins
    const Number&, //min
    const Number&,  //max
    const std::vector<Number>& //data
);
template<typename Number, typename WS>
void binAndSend(
<<<<<<< HEAD
    const WS&, 
=======
    WS&, 
>>>>>>> de01e4110c8f7db6d2a14471596b93464cf1f880
    Number&, //min
    Number&, //max
    const std::vector<Number>& //data
);
#include "Histogram.hpp"
#endif