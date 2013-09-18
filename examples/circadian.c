/*****************************************************************/
/* C code automatically generated from a LEMS/SEM description.   */
/* Compile with enclosed Makefile.                               */
/* Work in progress, expect substantial changes in the template. */
/*****************************************************************/

#include <stdio.h>
#include <math.h>
#include <sundials/sundials_types.h> 
#include <nvector/nvector_serial.h>  
#include <cvode/cvode_dense.h>       
#include <cvode/cvode.h>             

/* Problem Constants */
#define NEQ   8 /* number of equations */
#define RTOL  RCONST(1.0e-4)   /* scalar relative tolerance */
#define ATOL0 RCONST(1.0e-6)   /* vector absolute tolerance components */
#define ATOL1 RCONST(1.0e-6)   /* vector absolute tolerance components */
#define ATOL2 RCONST(1.0e-6)   /* vector absolute tolerance components */
#define ATOL3 RCONST(1.0e-6)   /* vector absolute tolerance components */
#define ATOL4 RCONST(1.0e-6)   /* vector absolute tolerance components */
#define ATOL5 RCONST(1.0e-6)   /* vector absolute tolerance components */
#define ATOL6 RCONST(1.0e-6)   /* vector absolute tolerance components */
#define ATOL7 RCONST(1.0e-6)   /* vector absolute tolerance components */
#define T0    RCONST(0)/* initial time */
#define T1    RCONST(50.0)  /* total integration time */
#define DT    RCONST(0.005)     /* output stepsize */

static void PrintOutput(realtype t, N_Vector y);
static void PrintRootInfo(realtype t, N_Vector y, int *rootsfound);
static void PrintFinalStats(void *cvode_mem);
static int check_flag(void *flagvalue, char *funcname, int opt);
static int dstate_dt(realtype t, N_Vector state, N_Vector dstate, void *params);

static int dstate_dt(realtype t, N_Vector state, N_Vector dstate,  void *p){

    realtype *pars = (realtype *) p;

 
    realtype Kc = pars[0];
    realtype v_4 = pars[1];
    realtype v_6 = pars[2];
    realtype vc = pars[3];
    realtype v_1 = pars[4];
    realtype v_2 = pars[5];
    realtype K = pars[6];
    realtype v_8 = pars[7];
    realtype L = pars[8];
    realtype n = pars[9];
    realtype k3 = pars[10];
    realtype K2 = pars[11];
    realtype K1 = pars[12];
    realtype k7 = pars[13];
    realtype K6 = pars[14];
    realtype k5 = pars[15];
    realtype K4 = pars[16];
    realtype K8 = pars[17];
    realtype init_X1 = pars[18];
    realtype tscale = pars[19];
    realtype init_Z1 = pars[20];
    realtype init_Z2 = pars[21];
    realtype init_V1 = pars[22];
    realtype init_V2 = pars[23];
    realtype init_X2 = pars[24];
    realtype compartment = pars[25];
    realtype init_Y1 = pars[26];
    realtype init_Y2 = pars[27];

    realtype Y2 = NV_Ith_S(state, 0);
    realtype V1 = NV_Ith_S(state, 1);
    realtype Y1 = NV_Ith_S(state, 2);
    realtype V2 = NV_Ith_S(state, 3);
    realtype X2 = NV_Ith_S(state, 4);
    realtype X1 = NV_Ith_S(state, 5);
    realtype Z1 = NV_Ith_S(state, 6);
    realtype Z2 = NV_Ith_S(state, 7);

    realtype rate__R6 = compartment * v_4 * Y1 / compartment / (K4 + Y1 / compartment);
    realtype rate__R7 = compartment * k5 * Y1 / compartment;
    realtype rate__R4 = compartment * L;
    realtype rate__R5 = compartment * k3 * X1 / compartment;
    realtype rate__R2 = compartment * v_2 * X1 / compartment / (K2 + X1 / compartment);
    realtype rate__R1 = compartment * v_1 * (pow(K1, n)) / ((pow(K1, n)) + (pow(Z1 / compartment, n)));
    realtype F = 1.0 / 2.0 * (V1 + V2);
    realtype rate__R3 = compartment * vc * K * F / (Kc + K * F);
    realtype rate__R8 = compartment * v_6 * Z1 / compartment / (K6 + Z1 / compartment);
    realtype rate__R9 = compartment * k7 * X1 / compartment;
    realtype rate__R14 = compartment * L;
    realtype rate__R15 = compartment * k3 * X2 / compartment;
    realtype rate__R16 = compartment * v_4 * Y2 / compartment / (K4 + Y2 / compartment);
    realtype rate__R17 = compartment * k5 * Y2 / compartment;
    realtype rate__R10 = compartment * v_8 * V1 / compartment / (K8 + V1 / compartment);
    realtype rate__R11 = compartment * v_1 * (pow(K1, n)) / ((pow(K1, n)) + (pow(Z2 / compartment, n)));
    realtype rate__R12 = compartment * v_2 * X2 / compartment / (K2 + X2 / compartment);
    realtype rate__R13 = compartment * vc * K * F / (Kc + K * F);
    realtype rate__R20 = compartment * v_8 * V2 / compartment / (K8 + V2 / compartment);
    realtype rate__R18 = compartment * v_6 * Z2 / compartment / (K6 + Z2 / compartment);
    realtype rate__R19 = compartment * k7 * X2 / compartment;

    NV_Ith_S(dstate, 0) = tscale * (rate__R15 - rate__R16);
    NV_Ith_S(dstate, 1) = tscale * (rate__R9 - rate__R10);
    NV_Ith_S(dstate, 2) = tscale * (rate__R5 - rate__R6);
    NV_Ith_S(dstate, 3) = tscale * (rate__R19 - rate__R20);
    NV_Ith_S(dstate, 4) = tscale * (rate__R11 - rate__R12 + rate__R13 + rate__R14);
    NV_Ith_S(dstate, 5) = tscale * (rate__R1 - rate__R2 + rate__R3 + rate__R4);
    NV_Ith_S(dstate, 6) = tscale * (rate__R7 - rate__R8);
    NV_Ith_S(dstate, 7) = tscale * (rate__R17 - rate__R18);

    return(0);
}



int main(int narg, char **args)
{
    realtype reltol, t, tout;
    N_Vector state, abstol;
    void *cvode_mem;
    int flag, flagr;

    state = abstol = NULL;
    cvode_mem = NULL;

    state = N_VNew_Serial(NEQ);
    if (check_flag((void *)state, "N_VNew_Serial", 0)) return(1);
    abstol = N_VNew_Serial(NEQ); 
    if (check_flag((void *)abstol, "N_VNew_Serial", 0)) return(1);
    
    realtype Kc = 4.8283;
    realtype v_4 = 1.0841;
    realtype v_6 = 4.6645;
    realtype vc = 6.7924;
    realtype v_1 = 6.8355;
    realtype v_2 = 8.4297;
    realtype K = 1.0;
    realtype v_8 = 3.5216;
    realtype L = 0.0;
    realtype n = 5.6645;
    realtype k3 = 0.1177;
    realtype K2 = 0.291;
    realtype K1 = 2.7266;
    realtype k7 = 0.2282;
    realtype K6 = 9.9849;
    realtype k5 = 0.3352;
    realtype K4 = 8.1343;
    realtype K8 = 7.4519;
    realtype init_X1 = 4.25;
    realtype tscale = 1.0;
    realtype init_Z1 = 2.25;
    realtype init_Z2 = 0.0;
    realtype init_V1 = 2.5;
    realtype init_V2 = 0.0;
    realtype init_X2 = 0.0;
    realtype compartment = 1.0;
    realtype init_Y1 = 3.25;
    realtype init_Y2 = 0.0;
    realtype p[] = {Kc, v_4, v_6, vc, v_1, v_2, K, v_8, L, n, k3, K2, K1, k7, K6, k5, K4, K8, init_X1, tscale, init_Z1, init_Z2, init_V1, init_V2, init_X2, compartment, init_Y1, init_Y2, };

    realtype X1 = init_X1;
    realtype X2 = init_X2;
    realtype V1 = init_V1;
    realtype V2 = init_V2;
    realtype Y1 = init_Y1;
    realtype Y2 = init_Y2;
    realtype Z1 = init_Z1;
    realtype Z2 = init_Z2;
    NV_Ith_S(state, 0) = init_X1;
    NV_Ith_S(state, 1) = init_X2;
    NV_Ith_S(state, 2) = init_V1;
    NV_Ith_S(state, 3) = init_V2;
    NV_Ith_S(state, 4) = init_Y1;
    NV_Ith_S(state, 5) = init_Y2;
    NV_Ith_S(state, 6) = init_Z1;
    NV_Ith_S(state, 7) = init_Z2;

    reltol = RTOL;
    NV_Ith_S(abstol,0) = ATOL0;
    NV_Ith_S(abstol,1) = ATOL1;
    NV_Ith_S(abstol,2) = ATOL2;
    NV_Ith_S(abstol,3) = ATOL3;
    NV_Ith_S(abstol,4) = ATOL4;
    NV_Ith_S(abstol,5) = ATOL5;
    NV_Ith_S(abstol,6) = ATOL6;
    NV_Ith_S(abstol,7) = ATOL7;
 
    /* Allocations and initializations */
    cvode_mem = CVodeCreate(CV_BDF, CV_NEWTON);
    if (check_flag((void *)cvode_mem, "CVodeCreate", 0)) return(1);
    
    flag = CVodeInit(cvode_mem, dstate_dt, T0, state);
    if (check_flag(&flag, "CVodeInit", 1)) return(1);
   
    flag = CVodeSetUserData(cvode_mem, p);
    if (check_flag(&flag, "CVodeSetUserData", 1)) return(1);
   
    flag = CVodeSVtolerances(cvode_mem, reltol, abstol);
    if (check_flag(&flag, "CVodeSVtolerances", 1)) return(1);
   
        
   
    flag = CVDense(cvode_mem, NEQ);
    if (check_flag(&flag, "CVDense", 1)) return(1);


    printf(" \n Integrating Locke2008_Circadian_Clock_0 \n\n");
    printf("#t Y2, V1, Y1, V2, X2, X1, Z1, Z2, \n");

    tout = DT;
    while(1) {
        flag = CVode(cvode_mem, tout, state, &t, CV_NORMAL);
        
        {
            PrintOutput(t, state);
            if(check_flag(&flag, "CVode", 1)) break;
            if(flag == CV_SUCCESS) {
                tout += DT;
            }
            if (t >= T1) break;
        }

    }

    PrintFinalStats(cvode_mem);

    N_VDestroy_Serial(state);
    N_VDestroy_Serial(abstol);

    CVodeFree(&cvode_mem);

    return(0);
}



static void PrintOutput(realtype t, N_Vector state)
{
    unsigned int i = 0;
    printf("%g", t);
    for (i = 0; i < NEQ; i++){
        printf(" %g", NV_Ith_S(state, i));
    }
    printf("\n");

    return;
}



static void PrintFinalStats(void *cvode_mem)
{
    long int nst, nfe, nsetups, nje, nfeLS, nni, ncfn, netf, nge;
    int flag;

    flag = CVodeGetNumSteps(cvode_mem, &nst);
    check_flag(&flag, "CVodeGetNumSteps", 1);
    flag = CVodeGetNumRhsEvals(cvode_mem, &nfe);
    check_flag(&flag, "CVodeGetNumRhsEvals", 1);
    flag = CVodeGetNumLinSolvSetups(cvode_mem, &nsetups);
    check_flag(&flag, "CVodeGetNumLinSolvSetups", 1);
    flag = CVodeGetNumErrTestFails(cvode_mem, &netf);
    check_flag(&flag, "CVodeGetNumErrTestFails", 1);
    flag = CVodeGetNumNonlinSolvIters(cvode_mem, &nni);
    check_flag(&flag, "CVodeGetNumNonlinSolvIters", 1);
    flag = CVodeGetNumNonlinSolvConvFails(cvode_mem, &ncfn);
    check_flag(&flag, "CVodeGetNumNonlinSolvConvFails", 1);

    flag = CVDlsGetNumJacEvals(cvode_mem, &nje);
    check_flag(&flag, "CVDlsGetNumJacEvals", 1);
    flag = CVDlsGetNumRhsEvals(cvode_mem, &nfeLS);
    check_flag(&flag, "CVDlsGetNumRhsEvals", 1);

    flag = CVodeGetNumGEvals(cvode_mem, &nge);
    check_flag(&flag, "CVodeGetNumGEvals", 1);

    printf("\nFinal Statistics:\n");
    printf("nst = %-6ld nfe  = %-6ld nsetups = %-6ld nfeLS = %-6ld nje = %ld\n",
           nst, nfe, nsetups, nfeLS, nje);
    printf("nni = %-6ld ncfn = %-6ld netf = %-6ld nge = %ld\n \n",
           nni, ncfn, netf, nge);
}


static int check_flag(void *flagvalue, char *funcname, int opt)
{
    int *errflag;

    /* Check if SUNDIALS function returned NULL pointer - no memory allocated */
    if (opt == 0 && flagvalue == NULL) {
      fprintf(stderr, "\nSUNDIALS_ERROR: %s() failed - returned NULL pointer\n\n",
              funcname);
      return(1); }

    /* Check if flag < 0 */
    else if (opt == 1) {
      errflag = (int *) flagvalue;
      if (*errflag < 0) {
        fprintf(stderr, "\nSUNDIALS_ERROR: %s() failed with flag = %d\n\n",
                funcname, *errflag);
        return(1); }}

    /* Check if function returned NULL pointer - no memory allocated */
    else if (opt == 2 && flagvalue == NULL) {
      fprintf(stderr, "\nMEMORY_ERROR: %s() failed - returned NULL pointer\n\n",
              funcname);
      return(1); }

    return(0);
}

