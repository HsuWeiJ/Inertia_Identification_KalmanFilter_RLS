/*
 * KalmanFilter_RLS.h
 *
 *  Created on: 2023¦~1¤ë12¤é
 *      Author: jason
 */

#ifndef KALMANFILTER_RLS_H_
#define KALMANFILTER_RLS_H_

#include "dsp.h"
#include "fpu32/fpu_vector.h"

typedef float* Matrix;

typedef struct Kalman_Terminal{
    float theda;
    float speed;
    float TL;
    float error;
}Kalman_Terminal;

typedef struct Kalman{
    float u;
    float R;
    float e_threshold;
    float e;
    float tem;
    Matrix A;
    Matrix B;
    Matrix X_Priori;
    Matrix X_Posteriori;
    Matrix P;
    Matrix K;
    Matrix H;
    Matrix Q;
    Matrix tem_nXn_1;
    Matrix tem_nXn_2;
    Matrix tem_1Xn;
    Matrix tem_nX1_1;
    Matrix tem_nX1_2;
    Matrix tem_1X1;
    Matrix I;
    Matrix Zero;
    Kalman_Terminal Terminal;
}Kalman;



inline void Matrix_Generate(Matrix* m, int size, float* Ini_Data)
{
    int i;
    *m = (Matrix) calloc(size,sizeof(float));
    for(i = 0; i < size; i++)
    {
        (*m)[i] = Ini_Data[i];
    }
}

inline void Matrix_Transpose(Matrix src, Matrix dest, int n)
{
    //Matrix Transpose
    if(n == 2)
    {
        dest[0]=src[0];dest[3]=src[3];
        dest[1]=src[2];dest[2]=src[1];
    }
    else if(n == 3)
    {
        dest[0]=src[0];dest[4]=src[4];dest[8]=src[8];
        dest[1]=src[3];dest[2]=src[6];dest[3]=src[1];
        dest[5]=src[7];dest[6]=src[2];dest[7]=src[5];
    }
    else
    {
        // vector doesn't need to transpose
    }

}

inline void Matrix_Add(Matrix in1 , Matrix in2 , Matrix out , int size)
{
    // data section declare
    static int i ;

    //Matrix Add
    for(i = 0; i < size; i++)
    {
        out[i]= in1[i] + in2[i];
    }
}

inline void Matrix_Minor(Matrix in1 , Matrix in2 , Matrix out , int size)
{
    // data section declare
    static int i ;

    //Matrix Add
    for(i = 0; i < size; i++)
    {
        out[i]= in1[i] - in2[i];
    }
}
//inline void Matrix_Product(Matrix* in1 , Matrix* in2 , Matrix* out)
//{
//    // data section declare
//    static int i , j , k;
//    static int row , column ,middle;
//    static float tem;
//
//    //initialize
//    row = in1->row;
//    column = in2->column;
//    middle = in1->column;
//
//    //Matrix Product
//    for(i = 0; i < row; i++)
//    {
//        for(j = 0; j < column; j++)
//        {
//            tem = 0;
//            for ( k = 0; k < middle; k++)
//                tem += in1->data[i][k] * in2->data[k][j];
//            out->data[i][j] = tem;
//        }
//    }
//}
//
inline void Matrix_Dot_Product(Matrix in , float c , Matrix out, int size)
{
    // data section declare
    static int i ;

    //Matrix Dot Product
    for(i = 0; i < size; i++)
    {
        out[i] = c * in[i];
    }
}

void Kalman_Ini_2X2(Kalman* k)
{
    //float initialization
    k->u = 0;
    k->R = 1;
    k->e_threshold = 0.08;
    k->e = 0;
    k->tem = 0;

    //Matrix initialization
    float A_data[4] = {(1-BM/J*TS),0,(-TS/J),1};
    Matrix_Generate(&(k->A),4,A_data);
    float B_data[2] = {TS/J,0};
    Matrix_Generate(&(k->B),2,B_data);
    float X_Priori_data[2] = {0};
    Matrix_Generate(&(k->X_Priori),2,X_Priori_data);
    float X_Posteriori_data[2] = {0};
    Matrix_Generate(&(k->X_Posteriori),2,X_Posteriori_data);
    float P_data[4] = {10000,0,0,10000};
    Matrix_Generate(&(k->P),4,P_data);
    float K_data[2] = {0};
    Matrix_Generate(&(k->K),2,K_data);
    float H_data[2] = {1,0};
    Matrix_Generate(&(k->H),2,H_data);
    float Q_data[4] = {0.01,0,0,0.0001};
    Matrix_Generate(&(k->Q),4,Q_data);
    float Tem_nXn_data[4] = {0};
    Matrix_Generate(&(k->tem_nXn_1),4,Tem_nXn_data);
    Matrix_Generate(&(k->tem_nXn_2),4,Tem_nXn_data);
    float Tem_1Xn_data[2] = {0};
    Matrix_Generate(&(k->tem_1Xn),2,Tem_1Xn_data);
    float Tem_nX1_data[2] = {0};
    Matrix_Generate(&(k->tem_nX1_1),2,Tem_nX1_data);
    Matrix_Generate(&(k->tem_nX1_2),2,Tem_nX1_data);
    float Tem_1X1_data[1] = {0};
    Matrix_Generate(&(k->tem_1X1),1,Tem_1X1_data);
    float I_data[4] = {1,0,0,1};
    Matrix_Generate(&(k->I),4,I_data);
    float Zero_data[4] = {0};
    Matrix_Generate(&(k->Zero),4,Zero_data);

}

void Kalman_Ini_3X3(Kalman* k)
{
    //float initialization
    k->u = 0;
    k->R = 1;
    k->e_threshold = 0.0001;
    k->e = 0;
    k->tem = 0;

    //Matrix initialization
    float A_data[9] = {1,0,0,TS,(1-BM/J*TS),0,0,(-TS/J),1};
    Matrix_Generate(&(k->A),9,A_data);
    float B_data[3] = {0,TS/J,0};
    Matrix_Generate(&(k->B),3,B_data);
    float X_Priori_data[3] = {0};
    Matrix_Generate(&(k->X_Priori),3,X_Priori_data);
    float X_Posteriori_data[3] = {0};
    Matrix_Generate(&(k->X_Posteriori),3,X_Posteriori_data);
    float P_data[9] = {10000,0,0,0,10000,0,0,0,10000};
    Matrix_Generate(&(k->P),9,P_data);
    float K_data[3] = {0};
    Matrix_Generate(&(k->K),3,K_data);
    float H_data[3] = {1,0,0};
    Matrix_Generate(&(k->H),3,H_data);
    float Q_data[9] = {0.001,0,0,0,0.001,0,0,0,0.01};
    Matrix_Generate(&(k->Q),9,Q_data);
    float Tem_nXn_data[9] = {0};
    Matrix_Generate(&(k->tem_nXn_1),9,Tem_nXn_data);
    Matrix_Generate(&(k->tem_nXn_2),9,Tem_nXn_data);
    float Tem_1Xn_data[3] = {0};
    Matrix_Generate(&(k->tem_1Xn),3,Tem_1Xn_data);
    float Tem_nX1_data[3] = {0};
    Matrix_Generate(&(k->tem_nX1_1),3,Tem_nX1_data);
    Matrix_Generate(&(k->tem_nX1_2),3,Tem_nX1_data);
    float Tem_1X1_data[1] = {0};
    Matrix_Generate(&(k->tem_1X1),1,Tem_1X1_data);
    float I_data[9] = {1,0,0,0,1,0,0,0,1};
    Matrix_Generate(&(k->I),9,I_data);
    float Zero_data[9] = {0};
    Matrix_Generate(&(k->Zero),9,Zero_data);

}

void Kalman2X2_Calculate(Kalman* k ,float speed , float u)
{
    //X_Priori=A*X+B.*u;
    mpy_SP_RMxRM(k->tem_nX1_1, k->A, k->X_Posteriori, 2, 2, 1);   // tem_nX1_1 : A*X
    Matrix_Dot_Product(k->B, u, k->tem_nX1_2, 2);               // tem_nX1_2 : B.*u
    Matrix_Add(k->tem_nX1_1, k->tem_nX1_2, k->X_Priori , 2);

    //P=A*P*A'+Q;
    mpy_SP_RMxRM(k->tem_nXn_1, k->A, k->P, 2, 2, 2);    // tem_nXn_1 : A*P
    Matrix_Transpose(k->A, k->tem_nXn_2, 2);                    // tem_nXn_2 : A'
    mpy_SP_RMxRM(k->P, k->tem_nXn_1, k->tem_nXn_2, 2, 2, 2) ;    // P : A*P*A'
    Matrix_Add(k->P, k->Q, k->P, 4);


    //K=(P*H')./(H*P*H'+R);
    mpy_SP_RMxRM(k->tem_1Xn, k->H, k->P, 1, 2, 2);              // tem_1Xn : H*P
    mpy_SP_RMxRM(k->tem_1X1, k->tem_1Xn, k->H, 1, 2, 1);        // tem_1X1 : H*P*H'
    k->tem = k->tem_1X1[0] + k->R;                              // tem : (H*P*H'+R)
    mpy_SP_RMxRM(k->tem_nX1_2, k->P, k->H, 2, 2, 1);            // tem_nX1_2 : P*H';
    Matrix_Dot_Product(k->tem_nX1_2, (1/k->tem), k->K, 2);

    //X_Posteriori=X_Priori+K.*(Speed-H*X_Priori);
    mpy_SP_RMxRM(k->tem_1X1, k->H, k->X_Priori, 1, 2, 1);       // tem_1X1 : H*X_Priori
    k->e = speed - k->tem_1X1[0];                               // e : (Speed-H*X_Priori)
    Matrix_Dot_Product(k->K, k->e, k->tem_nX1_1, 2);            // tem_nX1_1 : K.*(Speed-H*X_Priori)
    Matrix_Add(k->X_Priori, k->tem_nX1_1, k->X_Posteriori, 2);

    //P=(eye(2)-K*H)*P;
    mpy_SP_RMxRM(k->tem_nXn_1, k->K, k->H, 2, 1, 2);            // tem_nXn_1 : K*H
    Matrix_Minor(k->I, k->tem_nXn_1, k->tem_nXn_2, 4);              // tem_nXn_2 : (eye(2)-K*H)
    mpy_SP_RMxRM(k->tem_nXn_1, k->tem_nXn_2, k->P, 2, 2, 2);            // tem_nXn_1 : K*H
    Matrix_Add(k->tem_nXn_1, k->Zero, k->P, 4);

    //Update Terminal
    k->Terminal.speed = k->X_Posteriori[0];
    k->Terminal.TL = k->X_Posteriori[1];
    k->Terminal.error = k->e;
}

void Kalman3X3_Calculate(Kalman* k ,float theda , float u)
{
    //X_Priori=A*X+B.*u;
    mpy_SP_RMxRM(k->tem_nX1_1, k->A, k->X_Posteriori, 3, 3, 1);   // tem_nX1_1 : A*X
    Matrix_Dot_Product(k->B, u, k->tem_nX1_2, 3);               // tem_nX1_2 : B.*u
    Matrix_Add(k->tem_nX1_1, k->tem_nX1_2, k->X_Priori , 3);
    if(k->X_Priori[0] < 0.0)
        k->X_Priori[0] += TWO_PI;
    else if(k->X_Priori[0] > TWO_PI)
        k->X_Priori[0] -= TWO_PI;

    //P=A*P*A'+Q;
    mpy_SP_RMxRM(k->tem_nXn_1, k->A, k->P, 3, 3, 3);    // tem_nXn_1 : A*P
    Matrix_Transpose(k->A, k->tem_nXn_2,3);                    // tem_nXn_2 : A'
    mpy_SP_RMxRM(k->P, k->tem_nXn_1, k->tem_nXn_2, 3, 3, 3) ;    // P : A*P*A'
    Matrix_Add(k->P, k->Q, k->P, 9);


    //K=(P*H')./(H*P*H'+R);
    mpy_SP_RMxRM(k->tem_1Xn, k->H, k->P, 1, 3, 3);              // tem_1Xn : H*P
    mpy_SP_RMxRM(k->tem_1X1, k->tem_1Xn, k->H, 1, 3, 1);        // tem_1X1 : H*P*H'
    k->tem = k->tem_1X1[0] + k->R;                              // tem : (H*P*H'+R)
    mpy_SP_RMxRM(k->tem_nX1_2, k->P, k->H, 3, 3, 1);            // tem_nX1_2 : P*H';
    Matrix_Dot_Product(k->tem_nX1_2, (1/k->tem), k->K, 3);

    //X_Posteriori=X_Priori+K.*(Theda-H*X_Priori);
    mpy_SP_RMxRM(k->tem_1X1, k->H, k->X_Priori, 1, 3, 1);       // tem_1X1 : H*X_Priori
    k->e = theda - k->tem_1X1[0];                               // e : (Theda-H*X_Priori)
    if(k->e < -PI )
        k->e += TWO_PI;
    else if(k->e > PI)
        k->e -= TWO_PI;
    Matrix_Dot_Product(k->K, k->e, k->tem_nX1_1, 3);            // tem_nX1_1 : K.*(Theda-H*X_Priori)
    Matrix_Add(k->X_Priori, k->tem_nX1_1, k->X_Posteriori, 3);
    if(k->X_Posteriori[0] < 0.0)
        k->X_Posteriori[0] += TWO_PI;
    else if(k->X_Posteriori[0] > TWO_PI)
        k->X_Posteriori[0] -= TWO_PI;

    //P=(eye(3)-K*H)*P;
    mpy_SP_RMxRM(k->tem_nXn_1, k->K, k->H, 3, 1, 3);            // tem_nXn_1 : K*H
    Matrix_Minor(k->I, k->tem_nXn_1, k->tem_nXn_2, 9);              // tem_nXn_2 : (eye(3)-K*H)
    mpy_SP_RMxRM(k->tem_nXn_1, k->tem_nXn_2, k->P, 3, 3, 3);            // tem_nXn_1 : K*H
    Matrix_Add(k->tem_nXn_1, k->Zero, k->P, 9);

    //Update Terminal
    k->Terminal.theda = k->X_Posteriori[0];
    k->Terminal.speed = k->X_Posteriori[1];
    k->Terminal.TL = k->X_Posteriori[2];
    k->Terminal.error = k->e;
}


#endif /* KALMANFILTER_RLS_H_ */
