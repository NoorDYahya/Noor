//
// Created by noor dar yahya on 15/05/2022.
//

#include "MlpNetwork.h"
#define TEN 10
#define PERCENTAGE 100
#define SIZE 4



MlpNetwork::MlpNetwork(const Matrix weights[SIZE],
                       const Matrix bias[SIZE])
{
    w1_ = weights[0];
    w2_ = weights[1];
    w3_ = weights[2];
    w4_ = weights[3];
    b1_ = bias[0];
    b2_ = bias[1];
    b3_ = bias[2];
    b4_ = bias[3];
}

digit MlpNetwork::operator()(const Matrix &m) {

    Dense m1(w1_,b1_,activation::relu);
    Dense m2(w2_,b2_,activation::relu);
    Dense m3(w3_,b3_,activation::relu);
    Dense m4(w4_,b4_,activation::softmax);

    Matrix r1 = m1(m);
    Matrix r2 = m2(r1);
    Matrix r3 = m3(r2);
    Matrix r4 =m4(r3);
    for (int i = 0; i < TEN; i++){
        std::cout<< r4[i] <<std::endl;
    }
    digit result;
    float max;
    int temp=0;
    max=r4[0];
    for (int i = 1; i < TEN; i++)
    {
        if (r4[i] > max)
        {
            max = r4[i];
            temp = i;
        }
    }
    result.value = temp;
    result.probability = max;
    return result;

}



