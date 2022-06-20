#ifndef ORDONNANCEMENT_H
#define ORDONNANCEMENT_H
#define ArraySize(x)  (sizeof(x) / sizeof((x)[0]))

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Processus{
 int _id;
 double _t_execution;
 int _t_arrivage;
 int priorite;
} Processus;

int charToInt(char c);

void afficherProcessus(Processus processus[],int taille);

Processus *FIFO(Processus processus[],int taille);

Processus *PRIORITE(Processus processus[],int taille);

void CalculTemps(Processus processus[],int taille);
// 
void swapExec(double *x, double *y);
void swap(int *x, int *y);
void calculTempFin(Processus tab[], int n, int ct[]);
void tatwt( int ct[], Processus tab[], int tat[], int wt[], int n);
Processus* sortSJF(Processus tab[], int n, int wt[]);


// 
void calculWithQuantum(Processus *tab, double quantum, int n, int wt[], int tat[]);

#endif