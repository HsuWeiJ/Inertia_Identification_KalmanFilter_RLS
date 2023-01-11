/*
 * Filter.h
 *
 *  Created on: 2022¦~7¤ë21¤é
 *      Author: jason
 */

#ifndef FILTER_H_
#define FILTER_H_

typedef struct {  float  Input;               // Input: filter input
                  float  Out;             // Output: filter output
                  float  u;               // Data: input data
                  float  u1;              // Data: previous input data:u(k-1)
                  float  y;               // Data: ouput data
                  float  y1;              // Data: previous output data:y(k-1)
                  float  BW;               // Parameter:cut-off freq  (must set)
                  float  T;               // Parameter:switch frequency  (must set)
                } LOW_PASS_FILTER;
/*-----------------------------------------------------------------------------
Default initalisation values for the NOTCH_FILTER objects
-----------------------------------------------------------------------------*/

#define LOW_PASS_FILTER_DEFAULTS {     \
                           0,           \
                           0,           \
                           0,      \
                           0,      \
                           0,      \
                           0,      \
                           2*3.14159*1000,      \
                           0.0001 \
                          }

#define LPF_MARCRO(v) \
    v.u = v.Input; \
    v.y = (v.BW*v.T)*(v.u+v.u1)-(v.BW*v.T-2)*v.y1; \
    v.y = v.y / (v.BW*v.T+2); \
    v.y1 = v.y; \
    v.u1 = v.u; \
    v.Out = v.y;

typedef struct {  _iq  Input;               // Input: filter input
                  _iq  Out;             // Output: filter output
                  _iq  u;               // Data: input data
                  _iq  u1;              // Data: previous input data:u(k-1)
                  _iq  u2;              // Data: previous input data:u(k-2)
                  _iq  y;               // Data: ouput data
                  _iq  y1;              // Data: previous output data:y(k-1)
                  _iq  y2;              // Data: previous output data:y(k-2)
                  _iq  w;               // Parameter:cut-off freq  (must set)
                  _iq  T;               // Parameter:switch frequency  (must set)
                  _iq  z;               // Parameter:damp coifficient   (must set)
                  _iq  g;               // Parameter:constant of width
                  _iq  a;               // Parameter:notch width:from(w/a)~(a*w)   (must set)
                  _iq Gd;               // Parameter:denominator of notch
                  _iq Gn;               // Parameter:nominator of notch
                  _iq Gn1;               // Parameter:nominator of notch
                  _iq Gn2;               // Parameter:nominator of notch
                  _iq Gn3;               // Parameter:nominator of notch

                } NOTCH_FILTER;
/*-----------------------------------------------------------------------------
Default initalisation values for the NOTCH_FILTER objects
-----------------------------------------------------------------------------*/

#define NOTCH_FILTER_DEFAULTS {     \
                           0,           \
                           0,           \
                           _IQ(0),      \
                           _IQ(0),      \
                           _IQ(0),      \
                           _IQ(0),      \
                           _IQ(0),      \
                           _IQ(0),      \
                           _IQ(2*3.14159*180),      \
                           _IQ(0.000125),      \
                           _IQ(0),\
                           _IQ(0), \
                           _IQ(0), \
                           _IQ(0), \
                           _IQ(0), \
                           _IQ(0), \
                           _IQ(0), \
                           _IQ(0) \
                          }
#define NOTCH_MARCRO(v) \
    /*notch parameter set*/  \
    v.g=(1/v.a+v.a)/(2*v.z); \
    v.Gd=4/(v.T*v.T)+4*v.z*v.g*v.w/v.T+v.w*v.w;\
    v.Gn=4/(v.T*v.T)+4*v.z*v.w/v.T+v.w*v.w;\
    v.Gn1=-8/(v.T*v.T)+2*v.w*v.w;\
    v.Gn2=4/(v.T*v.T)-4*v.z*v.w/v.T+v.w*v.w;\
    v.Gn3=4/(v.T*v.T)-4*v.z*v.g*v.w/v.T+v.w*v.w;\
    /*set input is u*/\
    v.u=v.Input;\
    /*let output is y*/\
    v.y=(v.u*v.Gn+v.u1*v.Gn1+v.u2*v.Gn2-v.y1*v.Gn1-v.y2*v.Gn3)/v.Gd;\
    /*save previous step data*/\
    v.y2=v.y1;\
    v.y1=v.y;\
    v.u2=v.u1;\
    v.u1=v.u;\
    /*let oupput is y*/\
    v.Out=v.y;


#endif /* FILTER_H_ */
