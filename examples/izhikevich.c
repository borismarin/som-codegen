/*****************************************************************/
/* C code automatically generated from a dLEMS description.      */
/* Compile with enclosed Makefile.                               */
/* Work in progress, expect substantial changes in the template. */
/*****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sundials/sundials_types.h> 
#include <nvector/nvector_serial.h>  
#include <cvode/cvode_dense.h>       
#include <cvode/cvode.h>             

/* Problem Constants */
#define NEQ   2 /* number of equations */
#define NRF   3 /* number of rootfinding functions */
#define RTOL  RCONST(1.0e-4)   /* scalar relative tolerance */
#define ATOL0 RCONST(1.0e-6)   /* vector absolute tolerance components */
#define ATOL1 RCONST(1.0e-6)   /* vector absolute tolerance components */
#define T0    RCONST(0)/* initial time */
#define T1    RCONST(300)  /* total integration time */
#define DT    RCONST(0.01)     /* output stepsize */

static void PrintOutput(FILE *pf, realtype t, N_Vector y);
static void PrintRootInfo(realtype t, N_Vector y, int *rootsfound);
static void PrintFinalStats(void *cvode_mem);
static int check_flag(void *flagvalue, char *funcname, int opt);
static int dstate_dt(realtype t, N_Vector state, N_Vector dstate, void *params);
static int root_functions(realtype t, N_Vector state, realtype *gout, void *params);

static int dstate_dt(realtype t, N_Vector state, N_Vector dstate,  void *p){

    realtype *pars = (realtype *) p;

 
    realtype a = pars[0];
    realtype b = pars[1];
    realtype c = pars[2];
    realtype d = pars[3];
    realtype I = pars[4];
    realtype v0 = pars[5];

    realtype v = NV_Ith_S(state, 0);
    realtype u = NV_Ith_S(state, 1);

    realtype phi = 0.04 * pow(v, 2) + 5 * v + 140;

    NV_Ith_S(dstate, 0) = phi - u + I;
    NV_Ith_S(dstate, 1) = a * (b * v - u);

    return(0);
}

static int root_functions(realtype t, N_Vector state, realtype *gout, void *p)
{

    realtype *pars = (realtype *) p;

    realtype v = NV_Ith_S(state, 0);
    realtype u = NV_Ith_S(state, 1);
    realtype a = pars[0];
    realtype b = pars[1];
    realtype c = pars[2];
    realtype d = pars[3];
    realtype I = pars[4];
    realtype v0 = pars[5];
    realtype phi = 0.04 * pow(v, 2) + 5 * v + 140;

    //spike
    gout[0] = v - 30;
    //start_inj
    gout[1] = t - 30.0001;
    //end_inj
    gout[2] = t - 150.0001;

    return(0);
}


int main(int narg, char **args)
{
    realtype reltol, t, tout;
    N_Vector state, abstol;
    void *cvode_mem;
    int flag, flagr;
    int rootsfound[NRF];
    int rootdir[] = {1,1,1,};

    FILE *pout;
    pout = stdout;

    state = abstol = NULL;
    cvode_mem = NULL;

    state = N_VNew_Serial(NEQ);
    if (check_flag((void *)state, "N_VNew_Serial", 0)) return(1);
    abstol = N_VNew_Serial(NEQ); 
    if (check_flag((void *)abstol, "N_VNew_Serial", 0)) return(1);
    
    realtype a = 0.02;
    realtype b = 0.2;
    realtype c = -50;
    realtype d = 2;
    realtype I = 0;
    realtype v0 = -70;
    realtype p[] = {a, b, c, d, I, v0, };

    realtype v = v0;
    realtype u = b * v0;
    NV_Ith_S(state, 0) = v0;
    NV_Ith_S(state, 1) = b * v0;

    reltol = RTOL;
    NV_Ith_S(abstol,0) = ATOL0;
    NV_Ith_S(abstol,1) = ATOL1;
 
    /* Allocations and initializations */
    cvode_mem = CVodeCreate(CV_BDF, CV_NEWTON);
    if (check_flag((void *)cvode_mem, "CVodeCreate", 0)) return(1);
    
    flag = CVodeInit(cvode_mem, dstate_dt, T0, state);
    if (check_flag(&flag, "CVodeInit", 1)) return(1);
   
    flag = CVodeSetUserData(cvode_mem, p);
    if (check_flag(&flag, "CVodeSetUserData", 1)) return(1);
   
    flag = CVodeSVtolerances(cvode_mem, reltol, abstol);
    if (check_flag(&flag, "CVodeSVtolerances", 1)) return(1);
   
        flag = CVodeRootInit(cvode_mem, NRF, root_functions);
    if (check_flag(&flag, "CVodeRootInit", 1)) return(1);

    CVodeSetRootDirection(cvode_mem, rootdir);
    if (check_flag(&flag, "CVodeSetRootDirection", 1)) return(1);
        
   
    flag = CVDense(cvode_mem, NEQ);
    if (check_flag(&flag, "CVDense", 1)) return(1);


    printf(" \n Integrating izhikevich_burster \n\n");
    printf("#t v, u, \n");
    PrintOutput(pout, t, state);
   
    tout = DT;
    while(1) {
        flag = CVode(cvode_mem, tout, state, &t, CV_NORMAL);
        
        if(flag == CV_ROOT_RETURN) {
            /* Event detected */
            flagr = CVodeGetRootInfo(cvode_mem, rootsfound);
            if (check_flag(&flagr, "CVodeGetRootInfo", 1)) return(1);
            PrintRootInfo(t, state, rootsfound);
          
            if(rootsfound[0]){
                //spike
                v = NV_Ith_S(state, 0);
                u = NV_Ith_S(state, 1);
                NV_Ith_S(state, 0) = c;
                NV_Ith_S(state, 1) = u + d;

        }
            if(rootsfound[1]){
                //start_inj
                I = 5;
                p[0] = a;
                p[1] = b;
                p[2] = c;
                p[3] = d;
                p[4] = I;
                p[5] = v0;
        }
            if(rootsfound[2]){
                //end_inj
                I = 0;
                p[0] = a;
                p[1] = b;
                p[2] = c;
                p[3] = d;
                p[4] = I;
                p[5] = v0;
        }
            

        /* Restart integration with event-corrected state */
            flag = CVodeSetUserData(cvode_mem, p);
            if (check_flag(&flag, "CVodeSetUserData", 1)) return(1);
        CVodeReInit(cvode_mem, t, state);
        //PrintRootInfo(t, state, rootsfound);
    }
        else
                {
            PrintOutput(pout, t, state);
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

    fclose(pout);
    return(0);
}



static void PrintOutput(FILE *pout, realtype t, N_Vector state)
{
    unsigned int i = 0;
    fprintf(pout, "%g", t);
    for (i = 0; i < NEQ; i++){
        fprintf(pout, " %g", NV_Ith_S(state, i));
    }
    fprintf(pout, "\n");

    return;
}

static void PrintRootInfo(realtype t, N_Vector state, int *rootfound)
{
    unsigned int i = 0;

    printf("#events ");
    for (i = 0; i < NRF; i++) if(rootfound[i]) printf("%d", i);
    printf(":%g", t);
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

