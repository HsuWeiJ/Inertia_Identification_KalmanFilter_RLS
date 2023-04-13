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

#define FIRST_COLUMN 0
#define SECOND_COLUMN 3
#define THIRD_COLUMN 6

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
    float J_past;
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

typedef struct U_Kalman{
    float y;
    float R;
    float L;
    float alpha;
    float beta;
    float kappa;
    float lamda;
    float sqrt_L_Lamda;
    float e_threshold;
    float e;
    float w0_m;
    float w0_c;
    float wi_mc;
    float P_yy;
    float KalmanToRls_TL;
    float J_past;
    Matrix A;
    Matrix B;
    Matrix X[7];
    Matrix X_Priori;
    Matrix X_Posteriori;
    Matrix Sigma;
    Matrix P_Priori;
    Matrix P_Posteriori;
    Matrix P_xy;
    Matrix K;
    Matrix I;
    Matrix Q;
    Matrix Y;
    Matrix Tem_nXn_1;
    Matrix Tem_nXn_2;
    Matrix Tem_1Xn;
    Matrix Tem_nX1_1;
    Matrix Tem_nX1_2;
    Matrix Tem_1X1;
    Matrix Zero;
    Kalman_Terminal Terminal;

}U_Kalman;

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
    float e_threshold;
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
    char Switch;
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

inline void cholesky (Matrix a, int n) {
  float x, r;
  int i, j, k;

  /* Loop over columns */
  for(j = 0; j < n; j++) {
    /* i = j */
    x = a[j*n+j];  /* A_jj */

    for(k = 0; k < j; k++)
      x -= a[j*n+k] * a[j*n+k];  /* L_jk L_jk */

    if(x < 0)
      return;

    x = sqrtf(x);

    a[j*n+j] = x;  /* L_jj */
    r = 1.0 / x;

    /* i != j */
    for(i = j+1; i < n; i++) {
      x = a[i*n+j];  /* A_ij */

      for(k = 0; k < j; k++)
        x -= a[i*n+k] * a[j*n+k];  /* L_ik L_ij */

      a[i*n+j] = x * r;  /* L_ij = x / L_jj */
    }
  }

  return;
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
        k->Q[3] = 10;
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

void Kalman_Ini_U(U_Kalman* k)
{
    /*
    int i;
    //float initialization
    k->R = 1;
    k->L = 3;
    k->alpha = 0.9;
    k->beta = 2;
    k->kappa = 0;
    k->lamda = k->alpha * k->alpha * (k->L + k->kappa) - k->L;
    k->sqrt_L_Lamda = sqrtf(k->L + k->lamda);
    k->e_threshold = 1e-04;
    k->e = 0;
    k->w0_m = k->lamda / (k->L + k->lamda);
    k->w0_c = k->w0_m + 1 - k->alpha * k->alpha + k->beta;
    k->wi_mc = 1 / (2 * (k->L + k->lamda));

    //Matrix initialization
    float Zero_data[9] = {0};
    Matrix_Generate(&(k->Zero),9,Zero_data);
    float A_data[9] = {1,0,0,TS,(1-BM/J*TS),0,0,(-TS/J),1};
    Matrix_Generate(&(k->A),9,A_data);
    float B_data[3] = {0,TS/J,0};
    Matrix_Generate(&(k->B),3,B_data);
    float X_data[3] = {1,1,1};
    float Xi_data[3] = {0};
    Matrix_Generate(&(k->X[0]),3,X_data);
    for(i=1;i<=6;i++)
    {
        Matrix_Generate(&(k->X[i]),3,Xi_data);
    }
    float X_Priori_data[3] = {0};
    Matrix_Generate(&(k->X_Priori),3,X_Priori_data);
    float X_Posteriori_data[3] = {0};
    Matrix_Generate(&(k->X_Posteriori),3,X_Posteriori_data);
    float P_data[9] = {10000,0,0,0,10000,0,0,0,10000};
    Matrix_Generate(&(k->P_Priori),9,P_data);
    Matrix_Generate(&(k->P_Posteriori),9,Zero_data);
    Matrix_Generate(&(k->P_xy),3,X_Priori_data);
    float K_data[3] = {0};
    Matrix_Generate(&(k->K),3,K_data);
    float I_data[9] = {1,0,0,0,1,0,0,0,1};
    Matrix_Generate(&(k->I),9,I_data);
    float Sigma_data[9] = {0};
    Matrix_Generate(&(k->Sigma),9,Sigma_data);
    float Q_data[9] = {0.001,0,0,0,0.001,0,0,0,0.01};
    Matrix_Generate(&(k->Q),9,Q_data);
    float Y_data[7] = {0};
    Matrix_Generate(&(k->Y),7,Y_data);
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

    */
}

inline void Kalman_Calculate_U(U_Kalman* k ,float theda , float u, float RLS_J)
{
    /*
    //Step1. Variable initialization.
    //Update Inertia in A
    if(fabs(k->e) <= k->e_threshold)
    {
        k->J_past = RLS_J;
    }
    k->A[4] = (1-BM/k->J_past*TS);
    k->A[7] = (-TS/k->J_past);

    // Step2. Calculate the sigma point.
    // The dimension of x is L , and the dimension of sigma point is 2L+1

    //x(1:3) = x_hat;
    k->X[0][0] = k->X_Posteriori[0]; k->X[0][1] = k->X_Posteriori[1]; k->X[0][2] = k->X_Posteriori[2];
    Matrix_Add(k->P_Posteriori, k->Zero, k->Tem_nXn_1, 9);                  // Tem_nXn_1 : P
    cholesky(k->Tem_nXn_1, 3);
    Matrix_Transpose(k->Tem_nXn_1, k->Tem_nXn_2, 3);             // Tem_nXn_n : chol(P)
    Matrix_Dot_Product(k->Tem_nXn_2, k->sqrt_L_Lamda, k->Sigma, 9);
    k->Sigma[3]=0;k->Sigma[6]=0;k->Sigma[7]=0;
    Matrix_Add(k->X[0], k->Sigma+FIRST_COLUMN, k->X[1], 3);
    Matrix_Add(k->X[0], k->Sigma+SECOND_COLUMN, k->X[2], 3);
    Matrix_Add(k->X[0], k->Sigma+THIRD_COLUMN, k->X[3], 3);
    Matrix_Minor(k->X[0], k->Sigma+FIRST_COLUMN, k->X[4], 3);
    Matrix_Minor(k->X[0], k->Sigma+SECOND_COLUMN, k->X[5], 3);
    Matrix_Minor(k->X[0], k->Sigma+THIRD_COLUMN, k->X[6], 3);


    //Step3. State prediction.
    static int i;
    //X_Priori=A*X+B.*u;
//    mpy_SP_RMxRM(k->X, k->I, k->X, 3, 3, 7);   // Tem_nX1_1 : A*X

    //X=A*X+B.*u;
    for(i=0; i<7; i++)
    {
        mpy_SP_RMxRM(k->Tem_nX1_1, k->A, k->X[i], 3, 3, 1);           // Tem_nX1_1 : A*X
        Matrix_Dot_Product(k->B, u, k->Tem_nX1_2, 3);                 // Tem_nX1_2 : B.*u
        Matrix_Add(k->Tem_nX1_1, k->Tem_nX1_2, k->X[i] , 3);
    }

    //X_Priori=sigma(0~2L){W_i^m.*X}
    k->X_Priori[0]=0;k->X_Priori[1]=0;k->X_Priori[2]=0;
    for(i=0; i<7; i++)
    {
        if(!i)
            Matrix_Dot_Product(k->X[i], k->w0_m, k->Tem_nX1_1, 3);       // Tem_nX1_1 : w0_m.*X
        else
            Matrix_Dot_Product(k->X[i], k->wi_mc, k->Tem_nX1_1, 3);       // Tem_nX1_1 : wi_m.*X
        Matrix_Add(k->X_Priori, k->Tem_nX1_1, k->X_Priori, 3);
    }

    //P_Priori=sigma(0~2L){W_i^c.*(Xi - X_Priori)*(Xi - X_Priori)'}+Q
    for(i=0; i<8; i++)
        k->P_Priori[i] = 0;
    for(i=0; i<7; i++)
    {
        Matrix_Minor(k->X[i], k->X_Priori, k->Tem_nX1_1, 3);               // Tem_nX1_1 : Xi - X_Priori
        mpy_SP_RMxRM(k->Tem_nXn_1, k->Tem_nX1_1, k->Tem_nX1_1, 3, 1, 3);   // Tem_nXn_1 : (Xi - X_Priori)*(Xi - X_Priori)'
        if(!i)
            Matrix_Dot_Product(k->Tem_nXn_1, k->w0_c, k->Tem_nXn_2, 9);          // Tem_nXn_2 : w0_m.*(Xi - X_Priori)*(Xi - X_Priori)'
        else
            Matrix_Dot_Product(k->Tem_nXn_1, k->wi_mc, k->Tem_nXn_2, 9);       // Tem_nXn_2 : wi_m.*(Xi - X_Priori)*(Xi - X_Priori)'
        Matrix_Add(k->P_Priori, k->Tem_nXn_2, k->P_Priori, 9);
    }
    Matrix_Add(k->P_Priori, k->Q, k->P_Priori, 9);

    //y = sigma(0~2L){W_i^m.*Y}
    for(i=0; i<7; i++)
    {
        k->Y[i] = k->X[i][0];
    }
    k->y = 0;
    for(i=0; i<7; i++)
    {
        if(!i)
            k->y = k->y + k->w0_m * k->Y[i];
        else
            k->y = k->y + k->wi_mc * k->Y[i];
    }

    // Step4. Measurement update.
    // The measured value is corrected by the measured value, and the covariance matrix of the system state is updated.

    k->P_yy = 0;
    k->P_xy[0] = 0; k->P_xy[1] = 0; k->P_xy[2] = 0;
    for(i=0; i<7; i++)
    {
        //P_xy = sigma(0~2L){W_i^c.*((Xi - X_Priori)(Y[i]-y))}
        Matrix_Minor(k->X[i], k->X_Priori, k->Tem_nX1_1, 3);               // Tem_nX1_1 : Xi - X_Priori
        Matrix_Dot_Product(k->Tem_nX1_1, k->Y[i]-k->y, k->Tem_nX1_1, 3);   // Tem_nX1_1 : (Xi - X_Priori)(Y[i]-y);
        if(!i)
            Matrix_Dot_Product(k->Tem_nX1_1, k->w0_c, k->Tem_nX1_1, 3);   // Tem_nX1_1 : w0_c.*(Xi - X_Priori)(Y[i]-y);
        else
            Matrix_Dot_Product(k->Tem_nX1_1, k->wi_mc, k->Tem_nX1_1, 3);   // Tem_nX1_1 : wi_mc.*(Xi - X_Priori)(Y[i]-y);
        Matrix_Add(k->Tem_nX1_1, k->P_xy, k->P_xy, 3);

        //P_yy = sigma(0~2L){W_i^c.*((Y[i]-y)(Y[i]-y))}
        if(!i)
            k->P_yy = k->P_yy + k->w0_c * (k->Y[i]-k->y) * (k->Y[i]-k->y);
        else
            k->P_yy = k->P_yy + k->wi_mc * (k->Y[i]-k->y) * (k->Y[i]-k->y);
    }
    k->P_yy = k->P_yy + k->R;
    Matrix_Dot_Product(k->P_xy, 1/k->P_yy, k->K, 3);

    //X_Posteriori = X_Priori + K*(Theda - y)
    k->e = theda - k->y;
    if(k->e < -PI )
        k->e += TWO_PI;
    else if(k->e > PI)
        k->e -= TWO_PI;
    Matrix_Dot_Product(k->K, k->e, k->Tem_nX1_2, 3);                      // Tem_nX1_2 : K*(Theda - y)
    Matrix_Add(k->Tem_nX1_2, k->X_Priori, k->X_Posteriori, 3);

    if(k->X_Posteriori[0] < 0.0)
        k->X_Posteriori[0] += TWO_PI;
    else if(k->X_Posteriori[0] > TWO_PI)
        k->X_Posteriori[0] -= TWO_PI;

    //P_Posteriori = P_Priori - K*P_yy*K'
    Matrix_Dot_Product(k->K, k->P_yy, k->Tem_nX1_1, 3);                   // Tem_nX1_1 : K*P_yy
    mpy_SP_RMxRM(k->Tem_nXn_1, k->Tem_nX1_1, k->K, 3, 1, 3);              // Tem_nXn_1 : K*P_yy*K'
    Matrix_Minor(k->P_Priori, k->Tem_nXn_1, k->P_Posteriori, 9);

    //Update Q Matrix
    if(fabs(k->e) > k->e_threshold)
    {
        k->Q[0] = 0.01;
        k->Q[4] = 0.01;
        k->Q[8] = 0.1;
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

    */
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
    k->J_past = J;

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
    if(fabs(k->e) <= k->e_threshold)
    {
        k->J_past = RLS_J;
    }
    k->A[4] = (1-BM/k->J_past*TS);
    k->A[7] = (-TS/k->J_past);

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
        k->Q[8] = 0.1;
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
    r->e_threshold = 1e-04;
    r->omega_e = 0;
    r->omega_v = 0;
    r->Alpha = 1-1/(r->Ka * 2);
    r->Beta = 1-1/(r->Kb * 2);
    r->Gamma = 1.05;
//    r->F_max = 0.99999;
//    r->F_min = 0.9995;
    r->F_max = 0.999;
    r->F_min = 0.995;
    r->F = 0.9998;
    r->acc = 0;

    r->speed[0] = 0;
    r->tem = 0;
    r->Terminal.Friction = BM;
    r->Terminal.Inertia = J_INI;
    r->Switch = 0;

    //Matrix initialization
    float Fai_data[2] = {0};
    Matrix_Generate(&(r->Fai),2,Fai_data);
#if BUILDLEVEL == LEVEL4 || LEVEL6
    float Theda_data[2] = {-0.999,3.72};
#endif
#if   BUILDLEVEL == LEVEL5
    float Theda_data[2] = {-1,0.3831};
#endif
    Matrix_Generate(&(r->Theda),2,Theda_data);
    float P_data[4] = {10000,0,0,10000};
//    float P_data[4] = {0.000001,-0.00002,-0.00002,0.7};
    Matrix_Generate(&(r->P),4,P_data);
    float K_data[2] = {0};
//    float K_data[2] = {5e-07, 0.00027};
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

//inline void RLS_Calculate(RLS* r, Kalman* k, float speed, float Te_TL, float acc, char start)      //for Free Shaft Motor
//{
//    //Update Speed in RLS Handler
//    r->speed[1] = r->speed[0];
//    r->speed[0] = speed;
//
//    //Update Te-TL in RLS Handler
//    r->Te_TL[1] = r->Te_TL[0];
//    r->Te_TL[0] = Te_TL;
//
//    if (fabsf(acc) > 30 && start == 1)
//    {
//
//        /******************IVFF*******************/
//        //q=Fai'*P*Fai;
//        mpy_SP_RMxRM(r->Tem_1Xn, r->Fai, r->P, 1, 2, 2);            // Tem_1Xn : Fai'*P
//        mpy_SP_RMxRM(r->Tem_1X1, r->Tem_1Xn, r->Fai, 1, 2, 1);       // Tem_1X1 : Fai'*P*Fai
//        r->q_bar = r->a0 * r->q_bar + (1 - r->a0) * r->Tem_1X1[0];          //q_bar=a0*q_bar+(1-a0)*q;
//
//        //e=speed-(Fai')*Theda
//        mpy_SP_RMxRM(r->Tem_1X1, r->Fai, r->Theda, 1, 2, 1);        // Tem_1X1 : (Fai')*Theda
//        r->e = r->speed[0] - r->Tem_1X1[0];
//        r->omega_e = r->Alpha * r->omega_e + (1 - r->Alpha) * r->e * r->e;  //omega_e=alpha*omega_e_1+(1-alpha)*e^2;
//        r->omega_v = r->Beta * r->omega_v + (1 - r->Beta) * r->e * r->e;    //omega_v=beta*omega_v_1+(1-beta)*e^2;
//
//        if(sqrtf(r->omega_e) <= r->Gamma * sqrtf(r->omega_v))
//        {
//            r->F = r->F_max;
//            //GPIO_WritePin(GPIO25,TRUE);
//        }
//        else
//        {
//            r->F = fminf(r->q_bar * r->omega_v/(1e-08) + fabsf(r->omega_e - r->omega_v) , r->F_max);
//            //GPIO_WritePin(GPIO25,FALSE);
//        }
//        if(r->F < r->F_min)
//            r->F = r->F_min;
//
//        /******************RLS*******************/
//        r->Fai[0] = -r->speed[1];  r->Fai[1] = r->Te_TL[1];
//
//        //K=(P*Fai)./(F+Fai'*P*Fai);
//        mpy_SP_RMxRM(r->Tem_1Xn, r->Fai, r->P, 1, 2, 2);                // Tem_1Xn : Fai'*P
//        mpy_SP_RMxRM(r->Tem_1X1, r->Tem_1Xn, r->Fai, 1, 2, 1);          // Tem_1X1 : Fai'*P*Fai
//        r->tem = r->F + r->Tem_1X1[0];
//        mpy_SP_RMxRM(r->Tem_nX1_2, r->P, r->Fai, 2, 2, 1);              // Tem_nX1_2 : P*Fai;
//        Matrix_Dot_Product(r->Tem_nX1_2, (1/r->tem), r->K, 2);
//
//        //P=1/F .* (eye(2)-K*Fai')*P;
//        mpy_SP_RMxRM(r->Tem_nXn_1, r->K, r->Fai, 2, 1, 2);              // Tem_nXn_1 : K*Fai'
//        Matrix_Minor(r->I, r->Tem_nXn_1, r->Tem_nXn_2, 4);            // Tem_nXn_2 : (eye(2)-K*Fai')
//        mpy_SP_RMxRM(r->Tem_nXn_1, r->Tem_nXn_2, r->P, 2, 2, 2);      // Tem_nXn_1 : (eye(2)-K*Fai')*P;
//        Matrix_Dot_Product(r->Tem_nXn_1, (1/r->F), r->P, 4);
//
//        //Theda=Theda+K.*(Speed-(fai')*Theda);
//        Matrix_Dot_Product(r->K, r->e, r->Tem_nX1_1, 2);                  // Tem_nX1_1 : K.*(Speed-(fai')*Theda);
//        Matrix_Add(r->Tem_nX1_1, r->Theda, r->Theda, 2);
//
//        r->Terminal.Friction = (1 + r->Theda[0])/r->Theda[1];
//        if(r->Theda[0] < -1e-06)
//        {
////            r->Terminal.Inertia = TS/r->Theda[1];
//            r->Terminal.Inertia = -TS * r->Terminal.Friction / logf(-r->Theda[0]);
//        }
//
//        else
//            r->Terminal.Inertia = -TS * r->Terminal.Friction / logf(-0.999999);
//    }
//    else
//    {
//
//    }
//
//}

#if   BUILDLEVEL == LEVEL4
inline void RLS_Calculate(RLS* r, Kalman* k, float speed, float Te_TL, float acc, char start)            //for motor+Gearbox or brake
{
    //Update Speed in RLS Handler
    r->speed[1] = r->speed[0];
    r->speed[0] = speed;

    //Update Te-TL in RLS Handler
    r->Te_TL[1] = r->Te_TL[0];
    r->Te_TL[0] = Te_TL;

    r->F = r->F_max;
    if (fabsf(acc) > 30 && start == 1 && fabsf(k->e) < r->e_threshold )
    {
        r->Switch = 1;
        r->Fai[0] = -r->speed[1];  r->Fai[1] = r->Te_TL[1];
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



    }
    else
    {
        r->Switch = 0;
    }

    //Update Terminal
    r->Terminal.Friction = (1 + r->Theda[0])/r->Theda[1];
    if(r->Theda[0] < -1e-06)
    {
//            r->Terminal.Inertia = TS/r->Theda[1];
        r->Terminal.Inertia = -TS * r->Terminal.Friction / logf(-r->Theda[0]);
    }

    else
        r->Terminal.Inertia = -TS * r->Terminal.Friction / logf(-0.999999);

}
#endif

#if   BUILDLEVEL == LEVEL6
inline void RLS_Calculate(RLS* r, U_Kalman* k, float speed, float Te_TL, float acc, char start)            //for motor+Gearbox or brake
{
    //Update Speed in RLS Handler
    r->speed[1] = r->speed[0];
    r->speed[0] = speed;

    //Update Te-TL in RLS Handler
    r->Te_TL[1] = r->Te_TL[0];
    r->Te_TL[0] = Te_TL;

    r->F = r->F_max;
    if (fabsf(acc) > 30 && start == 1 && fabsf(k->e) < r->e_threshold )
    {
        r->Switch = 1;
        r->Fai[0] = -r->speed[1];  r->Fai[1] = r->Te_TL[1];
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



    }
    else
    {
        r->Switch = 0;
    }

    //Update Terminal
    r->Terminal.Friction = (1 + r->Theda[0])/r->Theda[1];
    if(r->Theda[0] < -1e-06)
    {
//            r->Terminal.Inertia = TS/r->Theda[1];
        r->Terminal.Inertia = -TS * r->Terminal.Friction / logf(-r->Theda[0]);
    }

    else
        r->Terminal.Inertia = -TS * r->Terminal.Friction / logf(-0.999999);

}

#endif
#endif /* KALMANFILTER_RLS_H_ */
