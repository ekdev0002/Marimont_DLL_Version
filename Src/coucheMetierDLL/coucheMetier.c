#include"coucheMetier.h"
#define DllExport __declspec(dllexport)

graphe DllExport lireGraphe(const gchar * sText1, const gchar * sText2)
{

    char X[100]="",A[100]="";
    int n;
    graphe G,H;

    strcpy(X,sText1);
    correct(X);
    n=strlen(X);
    G=initialiser(G,n,X);
    strcpy(A,sText2);
    G=A_to_Mat(G,A);

    return G;
}


int DllExport Marimont(graphe G)
{
    char E[100]="",S[100]="",V[100]="";
    int n,Hvide;
    graphe H;

    //copier G dans H
    H=copGtoH(G,H);
    Hvide=videH(H);
    point_entree(E,H);
    point_sortie(S,H);
    while( Hvide!=0 && videE(E)!=0 && videE(S)!=0 )
    {
        reunion(E,S,V);
        sous_graphe(&H,V);
        point_entree(E,H);
        point_sortie(S,H);
        Hvide=videH(H);

    }

return (Hvide);

}

void DllExport reunion(char * E,char * S,char V[])
{

    strcpy(V,E);
    printf("\n l'ensemble V: apres copie de E %s \n",V);
    strcat(V,S);
}



void DllExport correct(char * X)
{
    int c=0,i=0,j=0;
    char ens[100]="";

    while(X[i]!='\0')
    {
        if(X[i]!=';')
        {
            ens[j]=X[i];
            i++;
            j++;
        }
        else
        {
            i++;
        }
    }
    strcpy(X,ens);
}

graphe DllExport A_to_Mat(graphe G, char * A)
{
    int i=0;
    char a,b;
    while(A[i+4]!='\0')
    {
        if((A[i]='(') && (A[i+4]=')') )
        {
            a=(A[i+1]);
            b=(A[i+3]);
            modifier(a,b,G);
        }
       i=i+6;

    }

    return G;
}



graphe DllExport initialiser(graphe G,int n,char * X)
{
    G.N=n;
    G.A.L=NULL;
    strcpy(G.X,X);


    int i,j,val;
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            G=ajouter_a(i,j,0,G);
        }
    }
    return G;
}


graphe DllExport copGtoH(graphe G,graphe H)
{
    int i,j,n,val;
    CELL P,p;
    LIGNE M,m;

    n=G.N;
    H=initialiser(H,n,G.X);
    m=H.A.L;
    M=G.A.L;

    for(i=0; i<n; i++)
    {
        P=(*M).cel;
        p=(*m).cel;
        for(j=0; j<n; j++)
        {
            (*p).a=(*P).a;
            P=(*P).suivant;
            p=(*p).suivant;
        }
        M=(*M).suivant;
        m=(*m).suivant;
    }

return H;
}


graphe DllExport ajouter_cell(CELL newcell,graphe G)
{
    CELL P;
    LIGNE M;

    //recuperation de la l'adresse de la première ligne du graphe G dans la variable M
    M=G.A.L;

    //parcourir les ligne pour se rendre à la dernière ligne
    while((*M).suivant!=NULL)
    {

        M=(*M).suivant;
    }

   // On a atteint la dernière ligne, On peut inserer la cellule de type "element" dans la ligne

    //Si la liste chainée contenu dans la ligne est vide  on insere dans la première cellule sinon,

     //on parcours pour se rendre jusqu'a la dernière avant d'inserer


    if ((*M).cel==NULL)
    {
        (*M).cel=newcell;
    }

    else
    {
        P=(*M).cel;
        while((*P).suivant!=NULL)
        {
            P=(*P).suivant;
        }
        (*P).suivant=newcell;
    }

    return G;
}

graphe DllExport ajouter_ligne(graphe G,int i)
{

    LIGNE newligne,M;

    //Creation et initialisation de la nouvelle ligne de type "ligne" en mémoire
    newligne=(LIGNE)malloc(sizeof(ligne));
    (*newligne).suivant=NULL;
    (*newligne).cel=NULL;
    (*newligne).i=i;

    //Si le graphe n'a pas de ligne, chainage de la nouvelle ligne à G.A.L
    if(G.A.L==NULL)
    {
        G.A.L=newligne;
    }

    //sinon parcourir la liste chainée de ligne pour se rendre a la dernière ligne
    else
    {

        M=G.A.L;
        while((*M).suivant!=NULL)
        {
            M=(*M).suivant;
        }
        //On a atteint la dernière ligne, on peut effectuer le chainage
        (*M).suivant=newligne;
    }

    return G;
}


graphe DllExport ajouter_a(int i,int j,int val,graphe G)
{

    //creation et initialisation de la cellule de type "element"
    CELL newcell;
    newcell=(CELL)malloc(sizeof(element));
    (*newcell).a=val;
    (*newcell).j=j;
    (*newcell).suivant=NULL;

// affectation (chainnage) de la nouvelle cellule dans l'existant

    //Si j==0 , la cellule doit etre inseree en debut de ligne,

    if(j==0)
    {
        //necessité de creer une cellule de type "ligne"
        G=ajouter_ligne(G,i);

       //chainage de la nouvelle cellule à l'existant
        G=ajouter_cell(newcell,G);
    }
    else
    {
        G=ajouter_cell(newcell,G);
    }
    return G;
}

int DllExport videH (graphe G)
{

    return G.N;
}


int DllExport videE (char * E)
{

    return strlen(E);
}



//fonction pour afficher la matrice d'adjacence dans la console pour debogage
void DllExport afficher( graphe G)
{

    int i,j,n,val;
    n=G.N;
    CELL P;
    LIGNE M;
    M=G.A.L;


    for(i=0; i<n; i++)
    {

        printf("\n");
        P=(*M).cel;
        for(j=0; j<n; j++)
        {
            printf("%d",(*P).a);
            P=(*P).suivant;
        }
        M=(*M).suivant;
    }
}


void DllExport point_sortie (char S[],graphe G)
{
    int n=G.N,i,j,c=0,tab[n][n],k=0;
    char ens[100]="";

    CELL P;
    LIGNE M;
    M=G.A.L;

    for(i=0; i<n; i++)
    {
        P=(*M).cel;
        for(j=0; j<n; j++)
        {
            tab[i][j]=((*P).a);

            P=(*P).suivant;
        }
        M=(*M).suivant;
    }

    for(i=0; i<n; i++)
    {
        c=0;
        for(j=0; j<n; j++)
        {
            c=c+tab[i][j];

        }
        if(c==0)
        {
            ens[k]=G.X[i];
            k++;
        }

    }

    strcpy(S,ens);
}

void DllExport point_entree (char E[],graphe G)
{
    int n=G.N,i,j,c=0,tab[n][n],k=0;
    char ens[100]="";

    CELL P;
    LIGNE M;
    M=G.A.L;

    for(i=0; i<n; i++)
    {
        P=(*M).cel;
        for(j=0; j<n; j++)
        {
            tab[i][j]=((*P).a);

            P=(*P).suivant;
        }
        M=(*M).suivant;
    }

    for(j=0; j<n; j++)
    {
        c=0;
        for(i=0; i<n; i++)
        {
            c=c+tab[i][j];

        }
        if(c==0)
        {
            ens[k]=G.X[j];
            k++;
        }

    }

    strcpy(E,ens);
}

void DllExport supp_ligne(graphe * G,int I)
{
    int fin;
    LIGNE M,N,K,P,Q;
    CELL p,q;
    M=(*G).A.L;
    if(I==0)
    {
        Q=M;
        p=(*Q).cel;
        while(p!=NULL)
        {
            q=p;
            p=(*p).suivant;
            free(q);

        }

        M=(*M).suivant;
        K=M;
        while(K!=NULL)
        {
            (*K).i=(*K).i-1;
            K=(*K).suivant;
        }
        (*G).A.L=M;
        free(Q);

    }

    else
    {

        P=M;
        M=(*M).suivant;
        N=(*M).suivant;
        fin=1;
        while(M!=NULL  && fin!=0)
        {
            if((*M).i==I)
               {
                    Q=M;
                    p=(*Q).cel;
                    while(p!=NULL)
                    {
                        q=p;
                        p=(*p).suivant;
                        free(q);

                    }

                (*P).suivant=N;
                M=N;
                if(M==NULL)
                {
                    N=NULL;

                }
                else
                {
                    N=(*M).suivant;
                }

                K=M;
                while(K!=NULL)
                {
                    (*K).i=(*K).i-1;
                    K=(*K).suivant;
                }
                free(Q);
                fin=0;
               }
           else
           {
                P=M;
                M=(*M).suivant;
                if(M==NULL)
                {
                    N=NULL;

                }
                else
                {
                    N=(*M).suivant;
                }
           }
        }
    }
}



void DllExport supp_col(graphe * G,int J)
{

    int fin;
    CELL P,Q,p,m,n,k;
    LIGNE M,K;
    M=(*G).A.L;

    while(M!=NULL)
    {
        P=(*M).cel;
        m=P;

        if(J==0)
        {
            Q=P;
            P=(*P).suivant;
            (*M).cel=P;
            k=(*M).cel;
            while(k!=NULL)
            {
                (*k).j=(*k).j-1;
                k=(*k).suivant;
            }
            free(Q);
        }
        else
        {
            p=m;
            m=(*m).suivant;
            n=(*m).suivant;
            fin=1;
            while(m!=NULL  && fin!=0)
            {
                if( (*m).j == J)
                   {
                    Q=m;
                    (*p).suivant=n;
                    m=n;
                    if(m==NULL)
                    {
                        n=NULL;
                    }
                    else
                    {
                        n=(*m).suivant;
                    }

                    k=m;

                    while(k!=NULL)
                    {
                        (*k).j=(*k).j-1;
                        k=(*k).suivant;

                    }
                    free(Q);
                    fin=0;
                   }
               else
               {

                    p=m;
                    m=(*m).suivant;
                    if(m==NULL)
                    {
                        n=NULL;
                    }
                    else
                    {
                        n=(*m).suivant;
                    }
                }
            }
        }


    M=(*M).suivant;
    }
}

void DllExport supp_caract(char V[],int I)
{
    char ens[100]="";
    int i=0,j=0;
    while(V[i]!='\0')
    {
        if(i!=I)
        {
            ens[j]=V[i];
            i++;
            j++;
        }
        else
        {
            i++;
        }
    }
    strcpy(V,ens);
}

void DllExport sous_graphe(graphe * H,char V[])
{
    char  * Xtemp = (char*) malloc( sizeof(char)*strlen(V));
    int i=0,c=0;

    memcpy(Xtemp,H->X,strlen(H->X)+2);

    while(H->X[i]!='\0')
    {
        if(strchr(V,H->X[i])!=NULL)
        {
            printf("\n caractère %c va etre supprimer ; i =  %d ; c =  %d  i= %d \n",H->X[i],i,c,i);
            supp_ligne(H,c);
            supp_col(H,c);
            supp_caract(Xtemp,c);
        }
        else
        {
               c++;

        }
        i++;


        printf("\n hors G.X = %s\n",H->X);
        printf("\n hors Xtemp = %s\n",Xtemp);
    }

        printf("\n avant copie G.X = %s\n",H->X);
        printf("\n avant copie Xtemp = %s\n",Xtemp);


    strcpy(H->X,Xtemp);
    H->N=strlen(Xtemp);
    printf("\n H.X= %s H.N %d\n",H->X,H->N);
    free(Xtemp);


}

void DllExport supprime(char *texte, char x)   // supprime x dans la chaine
{
    int p ,i;
    for(i=0; texte[i] != '\0'; i++)
    {
        if (texte[i] == x)  // on a trouve
        {
            for(p=i; texte[p]!=0; p++)
                texte[p]=texte[p+1];
        }
    }
}
void DllExport modifier(char a,char b, graphe G)
{
    char * str;
    int i=0,j=0,c=0,n,u,v;

    CELL P;
    LIGNE M;


    str=G.X;
    n=G.N;
    M=G.A.L;

    while(str[c]!='\0')
    {
        if(str[c]==a)
        {
            u=c;
        }
        if(str[c]==b)
        {
            v=c;
        }

        c++;
    }


    for(i=0; i<n; i++)
    {
        printf("\n");
        P=(*M).cel;
        for(j=0; j<n; j++)
        {
            if(((*M).i==u) && ((*P).j==v))
            {
                (*P).a=1;
            }
            P=(*P).suivant;
        }
        M=(*M).suivant;
    }

}
