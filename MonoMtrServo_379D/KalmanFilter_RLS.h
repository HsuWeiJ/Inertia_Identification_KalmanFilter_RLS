/*
 * KalmanFilter_RLS.h
 *
 *  Created on: 2023¦~1¤ë12¤é
 *      Author: jason
 */

#ifndef KALMANFILTER_RLS_H_
#define KALMANFILTER_RLS_H_

typedef struct Matrix{
    int row;
    int column;
    float **data;
}Matrix;

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



inline void Matrix_Generate(Matrix* m,int row,int column,float* Ini_Data)
{
    static int i ,j ,k;
    m->row = row;
    m->column = column;
    m->data = (float**) calloc(row,sizeof(float*));
    k = 0;
    for(i=0;i<row;i++)
    {
        m->data[i] = (float*) calloc(column,sizeof(float));
        for( j=0; j < column; j++,k++)
        {
            m->data[i][j] = Ini_Data[k];
        }
    }
}
inline void Matrix_Transpose(Matrix* src , Matrix* dest)
{
    // data section declare
    static int i , j;
    static int row , column;

    //initialize
    row = src->row;
    column = src->column;

    //Matrix Transpose
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < column; j++)
        {
            dest->data[j][i] = src->data[i][j];
        }
    }

}
inline void Matrix_Add(Matrix* in1 , Matrix* in2 , Matrix* out )
{
    // data section declare
    static int i , j;
    static int row , column;

    //initialize
    row = in1->row;
    column = in1->column;

    //Matrix Add
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < column; j++)
        {
            out->data[i][j] = in1->data[i][j] + in2->data[i][j];
        }
    }
}
inline void Matrix_Minor(Matrix* in1 , Matrix* in2 , Matrix* out )
{
    // data section declare
    static int i , j;
    static int row , column;

    //initialize
    row = in1->row;
    column = in1->column;

    //Matrix Add
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < column; j++)
        {
            out->data[i][j] = in1->data[i][j] - in2->data[i][j];
        }
    }
}
inline void Matrix_Product(Matrix* in1 , Matrix* in2 , Matrix* out)
{
    // data section declare
    static int i , j , k;
    static int row , column ,middle;
    static float tem;

    //initialize
    row = in1->row;
    column = in2->column;
    middle = in1->column;

    //Matrix Product
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < column; j++)
        {
            tem = 0;
            for ( k = 0; k < middle; k++)
                tem += in1->data[i][k] * in2->data[k][j];
            out->data[i][j] = tem;
        }
    }
}

inline void Matrix_Dot_Product(Matrix* in , float c , Matrix* out)
{
    // data section declare
    static int i , j ;
    static int row , column ;

    //initialize
    row = in->row;
    column = in->column;

    //Matrix Dot Product
    for(i = 0; i < row; i++)
    {
        for(j = 0; j < column; j++)
        {
            out->data[i][j] = c * in->data[i][j];
        }
    }
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
    float A_data[9] = {1,TS,0,0,(1-BM/J*TS),(-TS/J),0,0,1};
    Matrix_Generate(&(k->A),3,3,A_data);
    float B_data[3] = {0,TS/J,0};
    Matrix_Generate(&(k->B),3,1,B_data);
    float X_Priori_data[3] = {0};
    Matrix_Generate(&(k->X_Priori),3,1,X_Priori_data);
    float X_Posteriori_data[3] = {0};
    Matrix_Generate(&(k->X_Posteriori),3,1,X_Posteriori_data);
    float P_data[9] = {10000,0,0,0,10000,0,0,0,10000};
    Matrix_Generate(&(k->P),3,3,P_data);
    float K_data[3] = {0};
    Matrix_Generate(&(k->K),3,1,K_data);
    float H_data[3] = {1,0,0};
    Matrix_Generate(&(k->H),1,3,H_data);
    float Q_data[9] = {0.001,0,0,0,0.001,0,0,0,0.01};
    Matrix_Generate(&(k->Q),3,3,Q_data);
    float Tem_nXn_data[9] = {0};
    Matrix_Generate(&(k->tem_nXn_1),3,3,Tem_nXn_data);
    Matrix_Generate(&(k->tem_nXn_2),3,3,Tem_nXn_data);
    float Tem_1Xn_data[3] = {0};
    Matrix_Generate(&(k->tem_1Xn),1,3,Tem_1Xn_data);
    float Tem_nX1_data[3] = {0};
    Matrix_Generate(&(k->tem_nX1_1),3,1,Tem_nX1_data);
    Matrix_Generate(&(k->tem_nX1_2),3,1,Tem_nX1_data);
    float Tem_1X1_data[1] = {0};
    Matrix_Generate(&(k->tem_1X1),1,1,Tem_1X1_data);
    float I_data[9] = {1,0,0,0,1,0,0,0,1};
    Matrix_Generate(&(k->I),3,3,I_data);
    float Zero_data[9] = {0};
    Matrix_Generate(&(k->Zero),3,3,Zero_data);

}

void Kalman_Calculate(Kalman* k ,float theda , float u)
{

    //X_Priori=A*X+B.*u;
    Matrix_Product(&k->A, &k->X_Posteriori, &k->tem_nX1_1);    // tem_nX1_1 : A*X
    Matrix_Dot_Product(&k->B, u, &k->tem_nX1_2);               // tem_nX1_2 : B.*u
    Matrix_Add(&k->tem_nX1_1, &k->tem_nX1_2, &k->X_Priori);
    if(k->X_Priori.data[0][0] < 0.0)
        k->X_Priori.data[0][0] += TWO_PI;
    else if(k->X_Priori.data[0][0] > TWO_PI)
        k->X_Priori.data[0][0] -= TWO_PI;

    //P=A*P*A'+Q;
    Matrix_Product(&k->A, &k->P, &k->tem_nXn_1);               // tem_nXn_1 : A*P
    Matrix_Transpose(&k->A, &k->tem_nXn_2);                    // tem_nXn_2 : A'
    Matrix_Product(&k->tem_nXn_1, &k->tem_nXn_2, &k->P);       // P : A*P*A'
    Matrix_Add(&k->P, &k->Q , &k->P);

    //K=(P*H')./(H*P*H'+R);
    Matrix_Product(&k->H, &k->P, &k->tem_1Xn);                 // tem_1Xn : H*P
    Matrix_Transpose(&k->H, &k->tem_nX1_1);                    // tem_nX1_1 : H';
    Matrix_Product(&k->tem_1Xn, &k->tem_nX1_1, &k->tem_1X1);   // tem_1X1 : H*P*H'
    k->tem = k->tem_1X1.data[0][0] + k->R;                     // tem : (H*P*H'+R)
    Matrix_Product(&k->P, &k->tem_nX1_1, &k->tem_nX1_2);       // tem_nX1_2 : P*H';
    Matrix_Dot_Product(&k->tem_nX1_2 , (1/k->tem) , &k->K);

    //X_Posteriori=X_Priori+K.*(Theda-H*X_Priori);
    Matrix_Product(&k->H, &k->X_Priori, &k->tem_1X1);          // tem_1X1 : H*X_Priori
    k->e = theda - k->tem_1X1.data[0][0] ;                     // e : (Theda-H*X_Priori)
    if(k->e < -PI )
        k->e += TWO_PI;
    else if(k->e > PI)
        k->e -= TWO_PI;
    Matrix_Dot_Product(&k->K , k->e , &k->tem_nX1_1);          // tem_nX1_1 : K.*(Theda-H*X_Priori)
    Matrix_Add(&k->X_Priori,&k->tem_nX1_1,&k->X_Posteriori);
    if(k->X_Posteriori.data[0][0] < 0.0)
        k->X_Posteriori.data[0][0] += TWO_PI;
    else if(k->X_Posteriori.data[0][0] > TWO_PI)
        k->X_Posteriori.data[0][0] -= TWO_PI;

    //P=(eye(3)-K*H)*P;
    Matrix_Product(&k->K, &k->H, &k->tem_nXn_1);               // tem_nXn_1 : K*H
    Matrix_Minor(&k->I, &k->tem_nXn_1, &k->tem_nXn_2);         // tem_nXn_2 : (eye(3)-K*H)
    Matrix_Product(&k->tem_nXn_2, &k->P, &k->tem_nXn_1);       // tem_nXn_1 : (eye(3)-K*H)*P
    Matrix_Add(&k->tem_nXn_1, &k->Zero, &k->P);

    //Update Terminal
    k->Terminal.theda = k->X_Posteriori.data[0][0];
    k->Terminal.speed = k->X_Posteriori.data[1][0];
    k->Terminal.TL = k->X_Posteriori.data[2][0];
    k->Terminal.error = k->e;
}


#endif /* KALMANFILTER_RLS_H_ */
