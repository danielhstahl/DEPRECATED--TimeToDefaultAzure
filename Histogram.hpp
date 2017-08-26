template<typename Number>
std::vector<int> bin(int numBins, const Number& min, const Number& max, const std::vector<Number>& data){
    int n=data.size();
    std::vector<int> bins(numBins, 0);
    double binWidth=(max-min)/numBins;

    for(int i=0; i<n; ++i){
        bins[(int)(data[i]-min)/binWidth]++;
    }
    return bins;
}
template<typename Number, typename WS>
<<<<<<< HEAD
void binAndSend(const WS& ws, int numBins, const Number& min, const Number& max,  const std::vector<Number>& data){
    int n=data.size();
    //std::cout<<min<<", "<<max<<std::endl;
    std::vector<int> bins(numBins, 0);
    double binWidth=(max-min)/(numBins-1);
=======
void binAndSend(WS& ws, int numBins, const Number& min, const Number& max,  const std::vector<Number>& data){
    int n=data.size();
    std::vector<int> bins(numBins, 0);
    double binWidth=(max-min)/numBins;
>>>>>>> de01e4110c8f7db6d2a14471596b93464cf1f880
    double orderMagnitude=max-min;

    orderMagnitude=pow(10.0, 2-(int)log10(orderMagnitude));
    for(int i=0; i<n; ++i){
        bins[(int)((data[i]-min)/binWidth)]++;
    }

    std::stringstream wsMessage;
    wsMessage<<"{\"bins\":[";
    for(int i=0; i<(numBins-1); ++i){
        wsMessage<<"\""<<((int)((min+i*binWidth)*orderMagnitude))/orderMagnitude<<"-"<<((int)((min+(i+1)*binWidth)*orderMagnitude))/orderMagnitude<<"\",";
    }
    wsMessage<<"\""<<((int)((min+(numBins-1)*binWidth)*orderMagnitude))/orderMagnitude<<"-"<<((int)((min+numBins*binWidth)*orderMagnitude))/orderMagnitude<<"\"], \"count\":[";
    for(int i=0; i<(numBins-1); ++i){
        wsMessage<<bins[i]<<",";
    }
    wsMessage<<bins[numBins-1]<<"]}";
    ws(wsMessage.str());
}

template<typename Number, typename WS>
<<<<<<< HEAD
void binAndSend(const WS& ws, Number& min, Number& max, const std::vector<Number>& data){
=======
void binAndSend(WS& ws, Number& min, Number& max, const std::vector<Number>& data){
>>>>>>> de01e4110c8f7db6d2a14471596b93464cf1f880
    int n=data.size();
    for(int i=0; i<n; ++i){
        if(data[i]<min){
            min=data[i];
        }
<<<<<<< HEAD
        if(data[i]>max){
=======
        else if(data[i]>max){
>>>>>>> de01e4110c8f7db6d2a14471596b93464cf1f880
            max=data[i];
        }
    }
    int numBins=2*pow(n, 1.0/3.0);//Rice Rule
    binAndSend(ws, numBins, min, max, data);

}