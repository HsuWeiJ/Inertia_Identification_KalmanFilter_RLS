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

typedef struct Kalman{
    Matrix A;
    Matrix A_t;
    Matrix Test_result;
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

inline void Kalman_Ini(Kalman* k , int order)
{
    float A_data[6] = {2,0,1,1,0,2};
    Matrix_Generate(&(k->A),2,3,A_data);
    float A_T_data[6] = {2,1,0,0,1,2};
    Matrix_Generate(&(k->A_t),3,2,A_T_data);
    float Test_result_data[4] = {0};
    Matrix_Generate(&(k->Test_result),2,2,Test_result_data);

//    Matrix_Product(&k->A,&k->A_t,&k->Test_result);
}


#endif /* KALMANFILTER_RLS_H_ */
