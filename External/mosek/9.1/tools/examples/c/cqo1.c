/*
   Copyright: Copyright (c) MOSEK ApS, Denmark. All rights reserved.

   File:      cqo1.c

   Purpose:   To demonstrate how to solve a small conic quadratic
              optimization problem using the MOSEK API.
 */

#include "mosek.h" /* Include the MOSEK definition file. */

static void MSKAPI printstr(void *handle,
                            const char str[])
{
  printf("%s", str);
} /* printstr */

int main(int argc, const char *argv[])
{
  MSKrescodee  r;

  const MSKint32t numvar = 6,
                  numcon = 1;

  MSKboundkeye bkc[] = { MSK_BK_FX };
  double       blc[] = { 1.0 };
  double       buc[] = { 1.0 };

  MSKboundkeye bkx[] = {MSK_BK_LO,
                        MSK_BK_LO,
                        MSK_BK_LO,
                        MSK_BK_FR,
                        MSK_BK_FR,
                        MSK_BK_FR
                       };
  double       blx[] = {0.0,
                        0.0,
                        0.0,
                        -MSK_INFINITY,
                        -MSK_INFINITY,
                        -MSK_INFINITY
                       };
  double       bux[] = { +MSK_INFINITY,
                         +MSK_INFINITY,
                         +MSK_INFINITY,
                         +MSK_INFINITY,
                         +MSK_INFINITY,
                         +MSK_INFINITY
                       };

  double       c[]   = {0.0,
                        0.0,
                        0.0,
                        1.0,
                        1.0,
                        1.0
                       };

  MSKint32t   aptrb[] = {0, 1, 2, 3, 3, 3},
              aptre[] = {1, 2, 3, 3, 3, 3},
              asub[]  = {0, 0, 0, 0};
  double      aval[]  = {1.0, 1.0, 2.0};


  MSKint32t   i, j, csub[3];

  MSKenv_t    env  = NULL;
  MSKtask_t   task = NULL;

  /* Create the mosek environment. */
  r = MSK_makeenv(&env, NULL);

  if (r == MSK_RES_OK)
  {
    /* Create the optimization task. */
    r = MSK_maketask(env, numcon, numvar, &task);

    if (r == MSK_RES_OK)
    {
      MSK_linkfunctotaskstream(task, MSK_STREAM_LOG, NULL, printstr);

      /* Append 'numcon' empty constraints.
      The constraints will initially have no bounds. */
      if (r == MSK_RES_OK)
        r = MSK_appendcons(task, numcon);

      /* Append 'numvar' variables.
      The variables will initially be fixed at zero (x=0). */
      if (r == MSK_RES_OK)
        r = MSK_appendvars(task, numvar);

      for (j = 0; j < numvar && r == MSK_RES_OK; ++j)
      {
        /* Set the linear term c_j in the objective.*/
        if (r == MSK_RES_OK)
          r = MSK_putcj(task, j, c[j]);

        /* Set the bounds on variable j.
        blx[j] <= x_j <= bux[j] */
        if (r == MSK_RES_OK)
          r = MSK_putvarbound(task,
                              j,           /* Index of variable.*/
                              bkx[j],      /* Bound key.*/
                              blx[j],      /* Numerical value of lower bound.*/
                              bux[j]);     /* Numerical value of upper bound.*/

        /* Input column j of A */
        if (r == MSK_RES_OK)
          r = MSK_putacol(task,
                          j,                 /* Variable (column) index.*/
                          aptre[j] - aptrb[j], /* Number of non-zeros in column j.*/
                          asub + aptrb[j],   /* Pointer to row indexes of column j.*/
                          aval + aptrb[j]);  /* Pointer to Values of column j.*/

      }

      /* Set the bounds on constraints.
       for i=1, ...,numcon : blc[i] <= constraint i <= buc[i] */
      for (i = 0; i < numcon && r == MSK_RES_OK; ++i)
        r = MSK_putconbound(task,
                            i,           /* Index of constraint.*/
                            bkc[i],      /* Bound key.*/
                            blc[i],      /* Numerical value of lower bound.*/
                            buc[i]);     /* Numerical value of upper bound.*/

      if (r == MSK_RES_OK)
      {
        /* Append the first cone. */
        csub[0] = 3;
        csub[1] = 0;
        csub[2] = 1;

        r = MSK_appendcone(task,
                           MSK_CT_QUAD,
                           0.0, /* Can be set to 0.0 */
                           3,
                           csub);
      }

      if (r == MSK_RES_OK)
      {
        /* Append the second cone. */
        csub[0] = 4;
        csub[1] = 5;
        csub[2] = 2;

        r = MSK_appendcone(task,
                           MSK_CT_RQUAD,
                           0.0,
                           3,
                           csub);
      }

      if (r == MSK_RES_OK)
      {
        MSKrescodee trmcode;

        /* Run optimizer */
        r = MSK_optimizetrm(task, &trmcode);


        /* Print a summary containing information
           about the solution for debugging purposes*/
        MSK_solutionsummary(task, MSK_STREAM_MSG);

        if (r == MSK_RES_OK)
        {
          MSKsolstae solsta;

          MSK_getsolsta(task, MSK_SOL_ITR, &solsta);

          switch (solsta)
          {
            case MSK_SOL_STA_OPTIMAL:
              {
                double *xx = NULL;

                xx = calloc(numvar, sizeof(double));
                if (xx)
                {
                  MSK_getxx(task,
                            MSK_SOL_ITR,    /* Request the interior solution. */
                            xx);

                  printf("Optimal primal solution\n");
                  for (j = 0; j < numvar; ++j)
                    printf("x[%d]: %e\n", j, xx[j]);
                }
                else
                {
                  r = MSK_RES_ERR_SPACE;
                }
                free(xx);
              }
              break;
            case MSK_SOL_STA_DUAL_INFEAS_CER:
            case MSK_SOL_STA_PRIM_INFEAS_CER:
              printf("Primal or dual infeasibility certificate found.\n");
              break;
            case MSK_SOL_STA_UNKNOWN:
              printf("The status of the solution could not be determined. Termination code: %d.\n", trmcode);
              break;
            default:
              printf("Other solution status.");
              break;
          }
        }
        else
        {
          printf("Error while optimizing.\n");
        }
      }

      if (r != MSK_RES_OK)
      {
        /* In case of an error print error code and description. */
        char symname[MSK_MAX_STR_LEN];
        char desc[MSK_MAX_STR_LEN];

        printf("An error occurred while optimizing.\n");
        MSK_getcodedesc(r,
                        symname,
                        desc);
        printf("Error %s - '%s'\n", symname, desc);
      }
    }
    /* Delete the task and the associated data. */
    MSK_deletetask(&task);
  }

  /* Delete the environment and the associated data. */
  MSK_deleteenv(&env);

  return (r);
} /* main */