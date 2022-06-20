#include <stdio.h>
#include <stdlib.h>
#include "ordonnancement.h"

void main (int argc, char *argv[])
{
    int wt[20]; int tat[20];
    FILE *file = fopen("process.txt","r");//Ouverture du fichier en mode ecriture
      if(file==NULL)
    {
        exit(1);// Si le fichier est vide , le fermer 
    }
    if(feof(file))
        {
            exit(1); //Si le curseur est a la fin du fichier , le fermer
        } 
        int nbreProcessus = charToInt(fgetc(file));
        Processus processus [nbreProcessus]; // On charge notre tableau de processus avec le nombre de processus recuperer plus haut 
    for (int i=0 ; i<nbreProcessus ; i++) //on fais une boucle sur le nombre de processus 
      {
        printf("Processus [%d] :",i+1);
          if(feof(file))
            {
                    exit(1);// Si le curseur est a la fin du fichier , le fermer
            }
        for (int j=0;j<8;j++)
          {
            if(feof(file))
              {
                    exit(1);//Si le curseur est a la fin du fichier , le fermer
              }
              char value = fgetc(file);
            if(value != '\n' && value != ' ')
              {
                int num = charToInt(value);
                switch (j)
                {
                  case 1:
                   processus[i]._id  = num; //A chaque processus i de notre tableau , on recupere l'element qui est a l'indice du processus_id dans notre fichier et on le lui afffecte
                   
                  break;
                  case 3:
                  processus[i]._t_arrivage = num;//A chaque processus i de notre tableau , on recupere l'element qui est a l'indice du processus_temps_arrivage dans notre fichier et on le lui afffecte
                       break;
                    case 5:
                       processus[i]._t_execution = num;//A chaque processus i de notre tableau , on recupere l'element qui est a l'indice du processus_temps_execution dans notre fichier et on le lui afffecte
                       
                       break;   
                    case 7:
                       processus[i].priorite = num;//A chaque processus i de notre tableau , on recupere l'element qui est a l'indice du processus_priorite dans notre fichier et on le lui afffecte
                       break;  
                    default:
                        break;
                    }
                  }
                else{continue;}
                  
            }
            printf("\n");
        }
    /*--------------------------------------------------------------------*/
    // Initialisation des processus
    
    Processus *Process = processus;
    int continuer =1;
    int choix = 0 ;
    double quantum=0;
    char next;
    while(continuer)
    {
      system("clear");
     printf("\n\nHey --");
     printf("Selectionnez une option --> \n\n");
     printf("1 - Lister les processus \n");
     printf("2 - \033[0;33mAlgorithme FIFO (Processus) \033[0;37m \n");
     printf("3 - \033[0;31mAlgorithme SJF \033[0;37m \n");
     printf("4 - \033[0;34mAlgorithme Pre-emptif \033[0;37m\n");
     printf("5 - \033[0;33mTemps Sejour/Attente \033[0;37m\n");
     printf("8 - Temps avec Quantum \n");
     printf("\033[0;31m9 - Exit\033[0;37m \n");
     printf("--->");scanf("%d",&choix);
     int n = nbreProcessus;
    int wt[n];
    int st[n];
    int ct[n];
    int tat[n];
     switch (choix)
     {
      case 1 :
      printf("\n");
        afficherProcessus(Process,ArraySize(processus)) ;
      break ; 
     case 2:
      printf("\n");
      Process = FIFO(Process,ArraySize(processus));
      afficherProcessus(Process,ArraySize(processus)) ;
      break;
     case 3 : 
     printf("\n");
     printf("\n");
         calculTempFin(Process, n, ct);
             tatwt( ct, Process, tat, wt, n);
                 Process = sortSJF(Process, n, wt);
                 afficherProcessus(Process,ArraySize(processus));
     
     break; 
     case 4 : 
     printf("\n");
     // ---------------------------------------PRIORITY SORT ------------------------------
     printf("\n"); 
     int bt[20],p[20],wt[20],tat[20],pr[20],i,j,n,total=0,pos,temp,avg_wt,avg_tat;
    n=nbreProcessus;
 
    printf("\nEnter Burst Time and Priority\n");
    for(i=0;i<nbreProcessus;i++)
    {
        bt[i] = processus[i]._t_execution;
        pr[i] = processus[i].priorite;
        p[i]=i+1;           //contains process number
    }
 
    //sorting burst time, priority and process number in ascending order using selection sort
    for(i=0;i<n;i++)
    {
        pos=i;
        for(j=i+1;j<n;j++)
        {
            if(pr[j]<pr[pos])
                pos=j;
        }
 
        temp=pr[i];
        pr[i]=pr[pos];
        pr[pos]=temp;
 
        temp=bt[i];
        bt[i]=bt[pos];
        bt[pos]=temp;
 
        temp=p[i];
        p[i]=p[pos];
        p[pos]=temp;
    }
 
    wt[0]=0; //waiting time for first process is zero
 
    //calculate waiting time
    for(i=1;i<n;i++)
    {
        wt[i]=0;
        for(j=0;j<i;j++)
            wt[i]+=bt[j];
 
        total+=wt[i];
    }
 
    avg_wt=total/n;      //average waiting time
    total=0;
 
    printf("\nProcess\t    Burst Time    \tWaiting Time\tTurnaround Time");
    for(i=0;i<n;i++)
    {
        tat[i]=bt[i]+wt[i];     //calculate turnaround time
        total+=tat[i];
        printf("\nP[%d]\t\t  %d\t\t    %d\t\t\t%d",p[i],bt[i],wt[i],tat[i]);
    }
 
    avg_tat=total/n;     //average turnaround time
    printf("\n\nAverage Waiting Time=%d",avg_wt);
    printf("\nAverage Turnaround Time=%d\n",avg_tat);
     break;
     case 5 :
     printf("\n");
     CalculTemps(Process,ArraySize(processus));
     break;
     case 6 : 
     break;
     case 7 :
     continuer = 0 ;
     break;
     case 8 : 
     printf("\n");
     printf("Entrez la valeur du quantum \n");
     scanf("%lf",&quantum);
     calculWithQuantum(processus,quantum,nbreProcessus,wt,tat);
     break;
     case 9 : 
     continuer=0;
     break;
     default:
     printf("Choix errone , Merci de reessayer :)");
      break;
     }
     
     if(continuer == 1)
     {
     printf("Voulez vous continuer ? o / n  ");
     scanf("%s",&next);
      if(next=='o')
     {
      continue;
     }
     else {
     continuer=0;
     }
       
     }
     else {
      continue;
         }
     
   

     
    }
    printf("A la prochaine :) \n");
    system("clear");
     
    
}   
