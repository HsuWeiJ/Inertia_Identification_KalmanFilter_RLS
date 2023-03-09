/*
 * KalmanFilter_RLS.h
 *
 *  Created on: 2023¦~1¤ë12¤é
 *      Author: jason
 */

#ifndef KALMANFILTER_RLS_H_
#define KALMANFILTER_RLS_H_

#include "math.h"
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
    float KalmanToRls_TL;
    Matrix A;
    Matrix B;
    Matrix X_Priori;
    Matrix X_Posteriori;
    Matrix P;
    Matrix K;
    Matrix H;
    Matrix Q;
    Matrix Tem_nXn_1;
    Matrix Tem_nXn_2;
    Matrix Tem_1Xn;
    Matrix Tem_nX1_1;
    Matrix Tem_nX1_2;
    Matrix Tem_1X1;
    Matrix I;
    Matrix Zero;
    Kalman_Terminal Terminal;
}Kalman;

typedef struct RLS_Terminal{
    float Inertia;
    float Friction;
    float error;
}RLS_Terminal;

typedef struct RLS{
    float a0;
    float Ka;
    float Kb;
    float q_bar;
    float e;
    float omega_e;
    float omega_v;
    float Alpha;
    float Beta;
    float Gamma;
    float F;
    float F_max;
    float F_min;
    float acc;
    float speed[2];
    float Te_TL[2];
    float tem;
    Matrix Fai;
    Matrix Theda;
    Matrix K;
    Matrix P;
    Matrix Tem_nXn_1;
    Matrix Tem_nXn_2;
    Matrix Tem_1Xn;
    Matrix Tem_nX1_1;
    Matrix Tem_nX1_2;
    Matrix Tem_1X1;
    Matrix I;
    Matrix Zero;
    RLS_Terminal Terminal;
}RLS;



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
    k->KalmanToRls_TL = 0;

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
    Matrix_Generate(&(k->Tem_nXn_1),4,Tem_nXn_data);
    Matrix_Generate(&(k->Tem_nXn_2),4,Tem_nXn_data);
    float Tem_1Xn_data[2] = {0};
    Matrix_Generate(&(k->Tem_1Xn),2,Tem_1Xn_data);
    float Tem_nX1_data[2] = {0};
    Matrix_Generate(&(k->Tem_nX1_1),2,Tem_nX1_data);
    Matrix_Generate(&(k->Tem_nX1_2),2,Tem_nX1_data);
    float Tem_1X1_data[1] = {0};
    Matrix_Generate(&(k->Tem_1X1),1,Tem_1X1_data);
    float I_data[4] = {1,0,0,1};
    Matrix_Generate(&(k->I),4,I_data);
    float Zero_data[4] = {0};
    Matrix_Generate(&(k->Zero),4,Zero_data);

}

inline void Kalman2X2_Calculate(Kalman* k, float speed, float u, float RLS_J)
{
    //Update Inertia in A
    k->A[0] = (1-BM/RLS_J*TS);
    k->A[2] = (-TS/RLS_J);

    //X_Priori=A*X+B.*u;
    mpy_SP_RMxRM(k->Tem_nX1_1, k->A, k->X_Posteriori, 2, 2, 1);   // Tem_nX1_1 : A*X
    Matrix_Dot_Product(k->B, u, k->Tem_nX1_2, 2);                 // Tem_nX1_2 : B.*u
    Matrix_Add(k->Tem_nX1_1, k->Tem_nX1_2, k->X_Priori , 2);

    //P=A*P*A'+Q;
    mpy_SP_RMxRM(k->Tem_nXn_1, k->A, k->P, 2, 2, 2);              // Tem_nXn_1 : A*P
    Matrix_Transpose(k->A, k->Tem_nXn_2, 2);                      // Tem_nXn_2 : A'
    mpy_SP_RMxRM(k->P, k->Tem_nXn_1, k->Tem_nXn_2, 2, 2, 2) ;     // P : A*P*A'
    Matrix_Add(k->P, k->Q, k->P, 4);


    //K=(P*H')./(H*P*H'+R);
    mpy_SP_RMxRM(k->Tem_1Xn, k->H, k->P, 1, 2, 2);                // Tem_1Xn : H*P
    mpy_SP_RMxRM(k->Tem_1X1, k->Tem_1Xn, k->H, 1, 2, 1);          // Tem_1X1 : H*P*H'
    k->tem = k->Tem_1X1[0] + k->R;                                // tem : (H*P*H'+R)
    mpy_SP_RMxRM(k->Tem_nX1_2, k->P, k->H, 2, 2, 1);              // Tem_nX1_2 : P*H';
    Matrix_Dot_Product(k->Tem_nX1_2, (1/k->tem), k->K, 2);

    //X_Posteriori=X_Priori+K.*(Speed-H*X_Priori);
    mpy_SP_RMxRM(k->Tem_1X1, k->H, k->X_Priori, 1, 2, 1);         // Tem_1X1 : H*X_Priori
    k->e = speed - k->Tem_1X1[0];                                 // e : (Speed-H*X_Priori)
    Matrix_Dot_Product(k->K, k->e, k->Tem_nX1_1, 2);              // Tem_nX1_1 : K.*(Speed-H*X_Priori)
    Matrix_Add(k->X_Priori, k->Tem_nX1_1, k->X_Posteriori, 2);

    //P=(eye(2)-K*H)*P;
    mpy_SP_RMxRM(k->Tem_nXn_1, k->K, k->H, 2, 1, 2);              // Tem_nXn_1 : K*H
    Matrix_Minor(k->I, k->Tem_nXn_1, k->Tem_nXn_2, 4);            // Tem_nXn_2 : (eye(2)-K*H)
    mpy_SP_RMxRM(k->Tem_nXn_1, k->Tem_nXn_2, k->P, 2, 2, 2);      // Tem_nXn_1 : (eye(2)-K*H)*P;
    Matrix_Add(k->Tem_nXn_1, k->Zero, k->P, 4);

    //Update Q Matrix
    if(fabs(k->e) > k->e_threshold)
    {
        k->Q[0] = 0.1;
        k->Q[3] = 0.01;
    }
    else
    {
        k->Q[0] = 0.01;
        k->Q[3] = 0.0001;
    }

    //Update Terminal
    k->Terminal.speed = k->X_Posteriori[0];
    k->Terminal.TL = k->X_Posteriori[1];
    k->Terminal.error = k->e;
}

void Kalman_Ini_3X3(Kalman* k)
{
    //float initialization
    k->u = 0;
    k->R = 1;
    k->e_threshold = 0.0001;
    k->e = 0;
    k->tem = 0;
    k->KalmanToRls_TL = 0;

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
    Matrix_Generate(&(k->Tem_nXn_1),9,Tem_nXn_data);
    Matrix_Generate(&(k->Tem_nXn_2),9,Tem_nXn_data);
    float Tem_1Xn_data[3] = {0};
    Matrix_Generate(&(k->Tem_1Xn),3,Tem_1Xn_data);
    float Tem_nX1_data[3] = {0};
    Matrix_Generate(&(k->Tem_nX1_1),3,Tem_nX1_data);
    Matrix_Generate(&(k->Tem_nX1_2),3,Tem_nX1_data);
    float Tem_1X1_data[1] = {0};
    Matrix_Generate(&(k->Tem_1X1),1,Tem_1X1_data);
    float I_data[9] = {1,0,0,0,1,0,0,0,1};
    Matrix_Generate(&(k->I),9,I_data);
    float Zero_data[9] = {0};
    Matrix_Generate(&(k->Zero),9,Zero_data);

}


inline void Kalman3X3_Calculate(Kalman* k ,float theda , float u, float RLS_J)
{
    //Update Inertia in A
    k->A[4] = (1-BM/RLS_J*TS);
    k->A[7] = (-TS/RLS_J);

    //X_Priori=A*X+B.*u;
    mpy_SP_RMxRM(k->Tem_nX1_1, k->A, k->X_Posteriori, 3, 3, 1);   // Tem_nX1_1 : A*X
    Matrix_Dot_Product(k->B, u, k->Tem_nX1_2, 3);                 // Tem_nX1_2 : B.*u
    Matrix_Add(k->Tem_nX1_1, k->Tem_nX1_2, k->X_Priori , 3);
    if(k->X_Priori[0] < 0.0)
        k->X_Priori[0] += TWO_PI;
    else if(k->X_Priori[0] > TWO_PI)
        k->X_Priori[0] -= TWO_PI;

    //P=A*P*A'+Q;
    mpy_SP_RMxRM(k->Tem_nXn_1, k->A, k->P, 3, 3, 3);              // Tem_nXn_1 : A*P
    Matrix_Transpose(k->A, k->Tem_nXn_2,3);                       // Tem_nXn_2 : A'
    mpy_SP_RMxRM(k->P, k->Tem_nXn_1, k->Tem_nXn_2, 3, 3, 3) ;     // P : A*P*A'
    Matrix_Add(k->P, k->Q, k->P, 9);


    //K=(P*H')./(H*P*H'+R);
    mpy_SP_RMxRM(k->Tem_1Xn, k->H, k->P, 1, 3, 3);                // Tem_1Xn : H*P
    mpy_SP_RMxRM(k->Tem_1X1, k->Tem_1Xn, k->H, 1, 3, 1);          // Tem_1X1 : H*P*H'
    k->tem = k->Tem_1X1[0] + k->R;                                // tem : (H*P*H'+R)
    mpy_SP_RMxRM(k->Tem_nX1_2, k->P, k->H, 3, 3, 1);              // Tem_nX1_2 : P*H';
    Matrix_Dot_Product(k->Tem_nX1_2, (1/k->tem), k->K, 3);

    //X_Posteriori=X_Priori+K.*(Theda-H*X_Priori);
    mpy_SP_RMxRM(k->Tem_1X1, k->H, k->X_Priori, 1, 3, 1);         // Tem_1X1 : H*X_Priori
    k->e = theda - k->Tem_1X1[0];                                 // e : (Theda-H*X_Priori)
    if(k->e < -PI )
        k->e += TWO_PI;
    else if(k->e > PI)
        k->e -= TWO_PI;
    Matrix_Dot_Product(k->K, k->e, k->Tem_nX1_1, 3);              // Tem_nX1_1 : K.*(Theda-H*X_Priori)
    Matrix_Add(k->X_Priori, k->Tem_nX1_1, k->X_Posteriori, 3);
    if(k->X_Posteriori[0] < 0.0)
        k->X_Posteriori[0] += TWO_PI;
    else if(k->X_Posteriori[0] > TWO_PI)
        k->X_Posteriori[0] -= TWO_PI;

    //P=(eye(3)-K*H)*P;
    mpy_SP_RMxRM(k->Tem_nXn_1, k->K, k->H, 3, 1, 3);             // Tem_nXn_1 : K*H
    Matrix_Minor(k->I, k->Tem_nXn_1, k->Tem_nXn_2, 9);           // Tem_nXn_2 : (eye(3)-K*H)
    mpy_SP_RMxRM(k->Tem_nXn_1, k->Tem_nXn_2, k->P, 3, 3, 3);     // Tem_nXn_1 : (eye(3)-K*H)*P;
    Matrix_Add(k->Tem_nXn_1, k->Zero, k->P, 9);

    //Update Q Matrix
    if(fabs(k->e) > k->e_threshold)
    {
        k->Q[0] = 0.01;
        k->Q[4] = 0.01;
        k->Q[8] = 1;
    }
    else
    {
        k->Q[0] = 0.001;
        k->Q[4] = 0.001;
        k->Q[8] = 0.01;
    }

    //Update Terminal
    k->Terminal.theda = k->X_Posteriori[0];
    k->Terminal.speed = k->X_Posteriori[1];
    k->Terminal.TL = k->X_Posteriori[2];
    k->Terminal.error = k->e;
}

void RLS_Ini(RLS* r)
{
    //float initialization
    r->a0 = 0.875;
    r->Ka = 2.5;
    r->Kb = 3.0;
    r->q_bar = 0;
    r->e = 0;
    r->omega_e = 0;
    r->omega_v = 0;
    r->Alpha = 1-1/(r->Ka * 2);
    r->Beta = 1-1/(r->Kb * 2);
    r->Gamma = 1.05;
    r->F_max = 0.9998;
    r->F_min = 0.9995;
    r->F = 0.9998;
    r->acc = 0;
    r->speed[0] = 0;
    r->tem = 0;

    //Matrix initialization
    float Fai_data[2] = {0};
    Matrix_Generate(&(r->Fai),2,Fai_data);
    float Theda_data[2] = {-0.5,0.1};
    Matrix_Generate(&(r->Theda),2,Theda_data);
    float P_data[4] = {10000,0,0,10000};
    Matrix_Generate(&(r->P),4,P_data);
    float K_data[2] = {0};
    Matrix_Generate(&(r->K),2,K_data);
    float Tem_nXn_data[4] = {0};
    Matrix_Generate(&(r->Tem_nXn_1),4,Tem_nXn_data);
    Matrix_Generate(&(r->Tem_nXn_2),4,Tem_nXn_data);
    float Tem_1Xn_data[2] = {0};
    Matrix_Generate(&(r->Tem_1Xn),2,Tem_1Xn_data);
    float Tem_nX1_data[2] = {0};
    Matrix_Generate(&(r->Tem_nX1_1),2,Tem_nX1_data);
    Matrix_Generate(&(r->Tem_nX1_2),2,Tem_nX1_data);
    float Tem_1X1_data[1] = {0};
    Matrix_Generate(&(r->Tem_1X1),1,Tem_1X1_data);
    float I_data[4] = {1,0,0,1};
    Matrix_Generate(&(r->I),4,I_data);
    float Zero_data[4] = {0};
    Matrix_Generate(&(r->Zero),4,Zero_data);

}

inline void RLS_Calculate(RLS* r, float speed, float Te_TL, float acc)
{
    //Update Speed in RLS Handler
    r->speed[1] = r->speed[0];
    r->speed[0] = speed;

    //Update Te-TL in RLS Handler
    r->Te_TL[1] = r->Te_TL[0];
    r->Te_TL[0] = Te_TL;

    if (fabsf(acc) > 30)
    {
        /******************IVFF*******************/
        //q=Fai'*P*Fai;
        mpy_SP_RMxRM(r->Tem_1Xn, r->Fai, r->P, 1, 2, 2);            // Tem_1Xn : Fai'*P
        mpy_SP_RMxRM(r->Tem_1X1, r->Tem_1Xn, r->Fai, 1, 2, 1);       // Tem_1X1 : Fai'*P*Fai
        r->q_bar = r->a0 * r->q_bar + (1 - r->a0) * r->Tem_1X1[0];          //q_bar=a0*q_bar+(1-a0)*q;

        //e=speed-(Fai')*Theda
        mpy_SP_RMxRM(r->Tem_1X1, r->Fai, r->Theda, 1, 2, 1);        // Tem_1X1 : (Fai')*Theda
        r->e = r->speed[0] - r->Tem_1X1[0];
        r->omega_e = r->Alpha * r->omega_e + (1 - r->Alpha) * r->e * r->e;  //omega_e=alpha*omega_e_1+(1-alpha)*e^2;
        r->omega_v = r->Beta * r->omega_v + (1 - r->Beta) * r->e * r->e;    //omega_v=beta*omega_v_1+(1-beta)*e^2;

        if(sqrtf(r->omega_e) <= r->Gamma * sqrtf(r->omega_v))
        {
            r->F = r->F_max;
            //GPIO_WritePin(GPIO25,TRUE);
        }
        else
        {
            r->F = fminf(r->q_bar * r->omega_v/(1e-08) + fabsf(r->omega_e - r->omega_v) , r->F_max);
            //GPIO_WritePin(GPIO25,FALSE);
        }
        if(r->F < r->F_min)
            r->F = r->F_min;

        /******************RLS*******************/
        r->Fai[0] = -r->speed[1];  r->Fai[1] = r->Te_TL[1];

        //K=(P*Fai)./(F+Fai'*P*Fai);
        mpy_SP_RMxRM(r->Tem_1Xn, r->Fai, r->P, 1, 2, 2);                // Tem_1Xn : Fai'*P
        mpy_SP_RMxRM(r->Tem_1X1, r->Tem_1Xn, r->Fai, 1, 2, 1);          // Tem_1X1 : Fai'*P*Fai
        r->tem = r->F + r->Tem_1X1[0];
        mpy_SP_RMxRM(r->Tem_nX1_2, r->P, r->Fai, 2, 2, 1);              // Tem_nX1_2 : P*Fai;
        Matrix_Dot_Product(r->Tem_nX1_2, (1/r->tem), r->K, 2);

        //P=1/F .* (eye(2)-K*Fai')*P;
        mpy_SP_RMxRM(r->Tem_nXn_1, r->K, r->Fai, 2, 1, 2);              // Tem_nXn_1 : K*Fai'
        Matrix_Minor(r->I, r->Tem_nXn_1, r->Tem_nXn_2, 4);            // Tem_nXn_2 : (eye(2)-K*Fai')
        mpy_SP_RMxRM(r->Tem_nXn_1, r->Tem_nXn_2, r->P, 2, 2, 2);      // Tem_nXn_1 : (eye(2)-K*Fai')*P;
        Matrix_Dot_Product(r->Tem_nXn_1, (1/r->F), r->Tem_nXn_2, 4);        // Tem_nXn_2 : 1/F .* (eye(2)-K*Fai')*P;
        Matrix_Add(r->Tem_nXn_2, r->Zero, r->P, 4);

        //Theda=Theda+K.*(Speed-(fai')*Theda);
        Matrix_Dot_Product(r->K, r->e, r->Tem_nX1_1, 2);                  // Tem_nX1_1 : K.*(Speed-(fai')*Theda);
        Matrix_Add(r->Tem_nX1_1, r->Theda, r->Theda, 2);

        r->Terminal.Friction = (1 + r->Theda[0])/r->Theda[1];
        if(r->Theda[0] < -1e-06)
        {
//            r->Terminal.Inertia = TS/r->Theda[1];
            r->Terminal.Inertia = -TS * r->Terminal.Friction / logf(-r->Theda[0]);
        }

        else
            r->Terminal.Inertia = -TS * r->Terminal.Friction / logf(-0.999999);
    }
    else
    {

    }

}

#endif /* KALMANFILTER_RLS_H_ */
