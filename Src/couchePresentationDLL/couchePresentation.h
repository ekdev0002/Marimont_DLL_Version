#ifndef COUCHEPRESENTATION_H_INCLUDED
#define COUCHEPRESENTATION_H_INCLUDED
#define DllExport __declspec(dllexport)


#include <stdlib.h>
#include <gtk/gtk.h>
#include"coucheMetier.h"

void DllExport lancerApplication();
void DllExport demarrage();
void DllExport accueil();
void DllExport continuer(GtkWidget *pButton, gpointer data);
void DllExport button_ok(GtkWidget *pButton, gpointer data);
void DllExport affich_resul(GtkWidget *pLabel,gpointer data);
void DllExport traitement(const gchar *sText1,const gchar *sText2,gpointer data );
void DllExport Resolution();
void DllExport button_initialiser(GtkWidget *pButton, gpointer data);
void DllExport on_quitter_btn(GtkWidget* widget, gpointer data);
void DllExport on_quitter_icon(GtkWidget* widget, gpointer data);


#endif // COUCHEPRESENTATION_H_INCLUDED
