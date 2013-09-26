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
#define NEQ   3 /* number of equations */
#define RTOL  RCONST(1.0e-4)   /* scalar relative tolerance */
#define ATOL0 RCONST(1.0e-6)   /* vector absolute tolerance components */
#define ATOL1 RCONST(1.0e-6)   /* vector absolute tolerance components */
#define ATOL2 RCONST(1.0e-6)   /* vector absolute tolerance components */
#define T0    RCONST(0)/* initial time */
#define T1    RCONST(2000.0)  /* total integration time */
#define DT    RCONST(0.05)     /* output stepsize */

static void PrintOutput(realtype t, N_Vector y);
static void PrintRootInfo(realtype t, N_Vector y, int *rootsfound);
static void PrintFinalStats(void *cvode_mem);
static int check_flag(void *flagvalue, char *funcname, int opt);
static int dstate_dt(realtype t, N_Vector state, N_Vector dstate, void *params);

static int dstate_dt(realtype t, N_Vector state, N_Vector dstate,  void *p){

    realtype *pars = (realtype *) p;

 
    realtype a = pars[0];
    realtype c = pars[1];
    realtype b = pars[2];
    realtype d = pars[3];
    realtype I = pars[4];
    realtype s = pars[5];
    realtype r = pars[6];
    realtype y0 = pars[7];
    realtype x0 = pars[8];
    realtype x1 = pars[9];
    realtype z0 = pars[10];
    realtype SEC = pars[11];

    realtype y = NV_Ith_S(state, 0);
    realtype x = NV_Ith_S(state, 1);
    realtype z = NV_Ith_S(state, 2);

    realtype Q = c - d * pow(x, 2) - y;
    realtype P = y - a * pow(x, 3) + b * pow(x, 2) + I;
    realtype R = s * (x - x1) - z;

    NV_Ith_S(dstate, 0) = Q / SEC;
    NV_Ith_S(dstate, 1) = (P - z) / SEC;
    NV_Ith_S(dstate, 2) = r * R / SEC;

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
    
    realtype a = 1.0;
    realtype c = -3.0;
    realtype b = 3.0;
    realtype d = 5.0;
    realtype I = 5.0;
    realtype s = 4.0;
    realtype r = 0.002;
    realtype y0 = -1.0;
    realtype x0 = -1.3;
    realtype x1 = -1.3;
    realtype z0 = 1.0;
    realtype SEC = 1.0;
    realtype p[] = {a, c, b, d, I, s, r, y0, x0, x1, z0, SEC, };

    realtype y = y0;
    realtype x = x0;
    realtype z = z0;
    NV_Ith_S(state, 0) = y0;
    NV_Ith_S(state, 1) = x0;
    NV_Ith_S(state, 2) = z0;

    reltol = RTOL;
    NV_Ith_S(abstol,0) = ATOL0;
    NV_Ith_S(abstol,1) = ATOL1;
    NV_Ith_S(abstol,2) = ATOL2;
 
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


    printf(" \n Integrating hr_regular \n\n");
    printf("#t y, x, z, \n");
    PrintOutput(t, state);
   
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

