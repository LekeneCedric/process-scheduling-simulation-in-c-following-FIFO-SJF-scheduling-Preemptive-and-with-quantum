#include "ordonnancement.h"

int charToInt(char c)
{
    return c - '0';
}

Processus *FIFO(Processus processus[],int taille)
{
    int index ;
    for (int i=0; i < taille-1; i++)
  {
      index = i;
    for (int j=i + 1; j < taille; j++)
    {
      if (processus[index]._t_arrivage >processus[j]._t_arrivage)
      {
        index = j;
      }
    }
    if (index != i)
    {
      Processus tmp = processus[i];
      processus[i] = processus[index];
      processus[index] = tmp;
    }}
    printf("Operation execute avec succes \n");
    return processus;
}

Processus *PRIORITE(Processus processus[],int taille)
{
    int index ;
    for (int i=0; i < taille-1; i++)
  {
      index = i;
    for (int j=i + 1; j < taille; j++)
    {
      if (processus[index].priorite >processus[j].priorite)
      {
        index = j;
      }
    }
    if (index != i)
    {
      Processus tmp = processus[i];
      processus[i] = processus[index];
      processus[index] = tmp;
    }}
    printf("Operation execute avec succes \n");
    return processus;
}

void CalculTemps(Processus processus[],int taille)
{
    int temps =0 ;
    int t_sejour=0;
    int t_attente=0;
    float t_total_sejour =0;
    float t_total_attente=0;
    printf("Temps Sejour et Temps d'attente\n");
    for(int i=0; i<taille;i++)
    {
      temps  = temps + processus[i]._t_execution;
      t_sejour = temps - processus[i]._t_arrivage;
      t_total_sejour+=t_sejour;
      t_attente = t_sejour - processus[i]._t_execution  ;
      t_total_attente += t_attente;
      printf("PID : [%d]-> T_Execution : %f ns  T_Arrive : %d -> Priorite : %d ->  Temps Sejour : %d ns -> Temps d'attente : %d\n",processus[i]._id,processus[i]._t_execution,processus[i]._t_arrivage,processus[i].priorite,t_sejour,t_attente);
    }
    printf("Le temps Moyen de sejour est de : %f et le temps moyen d'attente est : %f \n",t_total_sejour/taille,(t_total_attente/taille));
}

void afficherProcessus(Processus processus[],int taille)
{
  for(int i=0; i<taille;i++)
    {
        printf("PID :\033[0;32m [%d] \033[0;37m-> \033[0;31m T_Execution : %f ns \033[0;37m ->  \033[0;33m T_Arrive : [%d]  \033[0;37m ->   \033[0;34m Priorite : %d \033[0;37m \n"
        ,processus[i]._id,processus[i]._t_execution,processus[i]._t_arrivage,processus[i].priorite);
    }
}


/* --------------------------CALCUL SJF ----------------------*/

void swap(int *x, int *y)
{
    int temp=*x;
    *x=*y;
    *y=temp;
}

void swapExec(double *x, double *y)
{
    double temp=*x;
    *x=*y;
    *y=temp;
}
void calculTempFin(Processus tab[], int n, int ct[])
{
    int i, j, pos, min=1000;
    ct[0]=tab[0]._t_arrivage + tab[0]._t_execution;
  for(i=1; i<n; i++)
  {
	for(j=i; j<n; j++)
	{
	    if(tab[j]._t_arrivage<=ct[i-1])
	   {
              if(tab[j]._t_execution<min)
              {
                 min=tab[j]._t_execution;
                 pos=j;
              }
	   }
	}
    swap(&tab[i]._id, &tab[pos]._id);
    swap(&tab[i]._t_arrivage, &tab[pos]._t_arrivage);
    swapExec(&tab[i]._t_execution, &tab[pos]._t_execution);
    swap(&tab[i].priorite, &tab[pos].priorite);
    min=1000;
    ct[i]=ct[i-1]+tab[i]._t_execution;
  }  
}

/* calculate turnaround time and waiting time */
void tatwt( int ct[], Processus tab[], int tat[], int wt[], int n)
{
   int i;
   for(i=0;i<n;i++)
   {
	tat[i]=ct[i]-tab[i]._t_arrivage;
	wt[i]=tat[i]-tab[i]._t_execution;
   }
}

Processus* sortSJF(Processus tab[], int n, int wt[])
{
    Processus *newTab = (Processus *)malloc(sizeof(Processus) * n);
    for (size_t i = 0; i < n; i++)
    {
        newTab[i] = tab[i];
    }
    
    Processus tmp;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = i+1; j < n; j++)
        {
            if(wt[j] < wt[i])
            {
                tmp = tab[i];
                tab[i] = tab[j];
                tab[j] = tmp;
            }
        }
        
    }
    return newTab;
}

void calculWithQuantum(Processus tab[], double quantum, int n, int wt[], int tat[])
{
    int total_wt = 0, total_tat = 0;
    int rem_bt[n];
    for (int i = 0 ; i < n ; i++)
        rem_bt[i] = tab[i]._t_execution;

    int t = 0; // Current time

    while (1)
    {
        int done = 1;
        // Traverse all processes one by one repeatedly
        for (int i = 0 ; i < n; i++)
        {
            if (rem_bt[i] > 0)
            {
                done = 0; // There is a pendingmake process
 
                if (rem_bt[i] > quantum)
                {
                    t += quantum;
                    rem_bt[i] -= quantum;
                }
                else
                {
                    t = t + rem_bt[i];
                    wt[i] = t - tab[i]._t_execution;
                    rem_bt[i] = 0;
                }
            }
        }
 
        // If all processes are done
        if (done == 1)
        break;
    }

    for (int i = 0; i < n ; i++)
        tat[i] = tab[i]._t_execution + wt[i];
  
    for (int i=0; i<n; i++)
    {
        total_wt = total_wt + wt[i];
        total_tat = total_tat + tat[i];
    }
    
    printf("\nProcess\t    Burst Time    \tWaiting Time   \tTemps de sejour");
    for(int i=0;i<n;i++)
    {
        printf("\nP[%d]\t\t  %.2f\t\t    %d\t\t  %d\n", i+1, tab[i]._t_execution, wt[i], tat[i]);
    }

    printf("Temps moyen de sejour : %.2f \n", (float)total_tat/(float)n);
    printf("Temps moyen d'attente : %.2f \n", (float)total_wt/(float)n);
}