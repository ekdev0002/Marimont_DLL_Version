#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED
#define DllExport __declspec(dllexport)

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>




    typedef struct elemn
    {
    int a;
    int j;
    struct elemn * suivant;
    }element;


    typedef element * CELL;


    typedef struct lign
    {
    CELL cel;
    int i;
    struct lign *suivant;
    }ligne;

    typedef ligne * LIGNE;


    typedef struct mat
    {
        LIGNE L;
    }MATRICE;

   typedef struct graf
    {
            char X[100];
            MATRICE A;
            int N;
    }graphe;


graphe lireGraphe(const gchar * sText1, const gchar * sText2);
int Marimont(graphe G);
void correct(char * X);
graphe A_to_Mat(graphe G, char * A);
void reunion(char * E,char * S,char V[]);


graphe DllExport initialiser(graphe G,int n,char * X);
graphe copGtoH(graphe G,graphe H);

graphe DllExport ajouter_cell(CELL newcell,graphe G);
graphe DllExport ajouter_ligne(graphe G,int i);
graphe DllExport ajouter_a(int i,int j,int val,graphe G);
void DllExport afficher(graphe G);
void DllExport point_entree (char E[],graphe G);
void DllExport point_entree (char S[],graphe G);
int DllExport videH (graphe G);
int DllExport videE (char * E);
void DllExport sous_graphe(graphe * H,char V[]);
void DllExport supp_col(graphe * G,int J);
void DllExport supp_ligne(graphe * G,int I);
void DllExport supp_caract(char V[],int I);
CELL DllExport supp_case(CELL C,int I);
void DllExport modifier(char a,char b, graphe G);

#endif // FONCTION_H_INCLUDED
