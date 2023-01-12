/*
 * SpeedLoop.h
 *
 *  Created on: 2023/01/05
 *      Author: WeiJ
 *      Speed PI Controller
 *      Enhanced Speed Estimator + ACC Estimator for no per unit bandwidth design
 */

#ifndef SPEEDLOOP_H_
#define SPEEDLOOP_H_

typedef struct {  _iq  Ref;             // Input: MechThetaerence set-point
                  _iq  Fbk;             // Input: feedback
                  _iq  Out;             // Output: controller output
                  _iq  c1;              // Internal: derivative filter coefficient 1
                  _iq  c2;              // Internal: derivative filter coefficient 2
                } PI_TERMINALS;
                // note: c1 & c2 placed here to keep structure size under 8 words

typedef struct {  _iq  Kr;              // Parameter: MechThetaerence set-point weighting
                  _iq  Kp;              // Parameter: proportional loop gain
                  _iq  Ki;              // Parameter: integral gain
                  _iq  Kd;              // Parameter: derivative gain
                  _iq  Km;              // Parameter: derivative weighting
                  _iq  Umax;            // Parameter: upper saturation limit
                  _iq  Umin;            // Parameter: lower saturation limit
                  _iq  T;               // Parameter: Contorl Sampling time
                  _iq  divT;            // Parameter: Divide Contorl Sampling time
                  _iq  Kt;              // Parameter: Torque Constant (Nm/A)
                } PI_PARAMETERS;

typedef struct {  _iq  up;              // Data: proportional term
                  _iq  ui;              // Data: integral term
                  _iq  v1;              // Data: pre-saturated controller output
                  _iq  i1;              // Data: integrator storage: ui(k-1)
                  _iq  w1;              // Data: saturation record: [u(k-1) - v(k-1)]
                } PI_DATA;


typedef struct {  PI_TERMINALS term;
                  PI_PARAMETERS param;
                  PI_DATA      data;
                } PI_SPEED_CONTROLLER;

/*-----------------------------------------------------------------------------
Default initialization values for the PI objects
-----------------------------------------------------------------------------*/

#define PI_TERM_DEFAULTS {             \
                           0,           \
                           0,           \
                           0,           \
                           0,           \
                           0            \
                          }

#define PI_PARAM_DEFAULTS {            \
                           _IQ(1.0),    \
                           _IQ(1.0),    \
                           _IQ(0.0),    \
                           _IQ(0.0),    \
                           _IQ(1.0),    \
                           _IQ(1.0),    \
                           _IQ(-1.0),   \
                           _IQ(0.001),  \
                           _IQ(1000),   \
                           _IQ(0.169)   \
                          }

#define PI_DATA_DEFAULTS {             \
                           _IQ(0.0),    \
                           _IQ(0.0),    \
                           _IQ(0.0),    \
                           _IQ(0.0),    \
                           _IQ(1.0)     \
                          }


/*------------------------------------------------------------------------------
    PI Macro Definition
------------------------------------------------------------------------------*/

#define PI_SPEED(v)                                                                                 \
                                                                                                    \
    /* proportional term */                                                                         \
    v.data.up = _IQmpy(v.param.Kp , _IQmpy(v.param.Kr, v.term.Ref) - v.term.Fbk );                                        \
                                                                                                    \
    /* integral term */                                                                             \
    v.data.ui = _IQmpy(v.param.Ki * v.param.T, _IQmpy(v.data.w1, (v.term.Ref - v.term.Fbk))) + v.data.i1;       \
    v.data.i1 = v.data.ui;                                                                          \
                                                                                                    \
    /* control output */                                                                            \
    v.data.v1 = (v.data.up + v.data.ui) / v.param.Kt ;                                                             \
    v.term.Out= _IQsat(v.data.v1, v.param.Umax, v.param.Umin);                                      \
    v.data.w1 = (v.term.Out == v.data.v1) ? _IQ(1.0) : _IQ(0.0);                                    \

/*------------------------------------------------------------------------------
 Velocity Estimator Struct Definition
 ------------------------------------------------------------------------------*/
typedef struct
{
    float MechTheta;              // Input: MechTheta get from encoder (pu)
    float OldMechTheta;           // Internal: Last step of estimated theta (pu)
    float PosError;               // Internal: MechTheta - OldMechTheta
    float PosErrorKdDivJest;      // Internal: Enhanced term for derivative
    float PosErrorKp;             // Internal: Error * Kp
    float PosErrorKi;             // Internal: Error * Ki/s
    float TorqueCmd;              // Internal: CurrentCmd * Kt
    float D_est;                  // Internal: Estimated disturbance
    float CurrentCmd;             // Input : pi_iq.Ref * BASE_CURRENT;
    float AccEst;       // Internal: Estimted Acc
    float Enhanced_SpeedEst;      // Internal: Enhanced estimted speed
    float Enhanced_SpeedEst_pu;   // Output: Enhanced estimted speed (pu)
    float SpeedEst;               // Internal: Estimted speed (Hz)
    float PosEst;                 // Internal: Estimated theta
    int32 SpeedRpm;               // Output : Speed in rpm
} V_EST_TERMINALS;

typedef struct
{
    float Kd;                     // Parameter: Derivative gain
    float Kp;                     // Parameter: Proportional gain
    float Ki;                     // Parameter: Integral gain
    float Kt;                     // Parameter: Torque constant
    float T_est;                  // Parameter: Sampling time of speed estimator
    float f_est;                  // Parameter: 1/T_est
    float J_est;                  // Parameter: Estimated inertia in the observer system
    float divJ_est;               // Parameter: 1/J_est
    Uint32 BaseRpm;               // Parameter: Base speed in rpm
} V_EST_PARAMETERS;


typedef struct
{
    V_EST_TERMINALS term;
    V_EST_PARAMETERS param;
} V_ESTIMATOR;

/*-----------------------------------------------------------------------------
 Default initalisation values for the V_EST objects
 -----------------------------------------------------------------------------*/

#define V_EST_TERM_DEFAULTS {             \
                           0.0,           \
                           0.0,           \
                           0.0,           \
                           0.0,           \
                           0.0,           \
                           0.0,           \
                           0.0,           \
                           0.0,           \
                           0.0,           \
                           0.0,           \
                           0.0,           \
                           0.0,           \
                           0.0,           \
                           0.0,           \
                           0              \
                          }

#define V_EST_PARAM_DEFAULTS {            \
                           0.0,           \
                           0.0,           \
                           0.0,           \
                           0.0,           \
                           0.0,           \
                           0.0,           \
                           0.0,           \
                           0.0,           \
                           0              \
                          }


/*------------------------------------------------------------------------------
 Speed Estimator Macro Definition
 ------------------------------------------------------------------------------*/
#define SPEED_EST_MACRO(v)\
        v.term.PosError = v.term.MechTheta - v.term.OldMechTheta;\
        if (v.term.PosError < -_IQ(0.5))                                       \
            v.term.PosError = v.term.PosError + _IQ(1.0);                                      \
        else if (v.term.PosError > _IQ(0.5))                                       \
            v.term.PosError = v.term.PosError - _IQ(1.0);                                      \
        v.term.PosError *= (2*PI);\
        v.term.PosErrorKdDivJest = v.term.PosError * v.param.Kd * v.param.divJ_est;\
        v.term.PosErrorKp = v.term.PosError * v.param.Kp;\
        v.term.PosErrorKi += v.term.PosError * v.param.Ki * v.param.T_est;\
        \
        v.term.D_est = v.term.PosErrorKp + v.term.PosErrorKi;\
        v.term.TorqueCmd = v.term.CurrentCmd * v.param.Kt;\
        \
        /*current(CCW) is Position(CW) inverse => -current(CW)*/\
        v.term.AccEst = (v.term.D_est + v.term.TorqueCmd) * v.param.divJ_est;\
        v.term.Enhanced_SpeedEst += v.term.AccEst * v.param.T_est;\
        v.term.SpeedEst = (v.term.PosErrorKdDivJest + v.term.Enhanced_SpeedEst)/(2*PI);\
        v.term.PosEst += v.term.SpeedEst * v.param.T_est;\
        if (v.term.PosEst < -_IQ(0.0))                                       \
            v.term.PosEst += _IQ(1.0);                                      \
        else if (v.term.PosEst > _IQ(1.0))                                       \
            v.term.PosEst -= _IQ(1.0);                                      \
        v.term.OldMechTheta = v.term.PosEst;\
        v.term.Enhanced_SpeedEst_pu = v.term.Enhanced_SpeedEst / (2*PI*BASE_FREQ);\
        v.term.SpeedRpm = _IQmpy(v.param.BaseRpm,v.term.Enhanced_SpeedEst_pu);



#endif /* SPEEDLOOP_H_ */
