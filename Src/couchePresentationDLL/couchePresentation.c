#include"couchePresentation.h"
#define DllExport __declspec(dllexport)
void DllExport lancerApplication()
{
    //gestion de la fenetre de demarrage
    demarrage();

    //gestion fenetre de traitement
    accueil();

}


void DllExport demarrage()
{
    GtkWidget *pWindow;
    GtkWidget *pMainVBox;
    GtkWidget *pLabelBox;
    GtkWidget *pProgress;
    GtkWidget *fictif1;
    GtkWidget *fictif2;
    GtkWidget *pLabel;
    gchar *sUtf8;
    gtk_rc_parse ("./ressources/config/gtk2.rc");

    gdouble dFraction;
    gint i;
    gint iTotal = 1000;
    const gchar stext[100]="";

    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 838, 556);
    gtk_window_move(pWindow,280,40);
    gtk_window_set_decorated(pWindow,FALSE);

    pMainVBox = gtk_vbox_new(FALSE, 0);
    pLabelBox = gtk_hbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(pWindow), pMainVBox);

    pProgress = gtk_progress_bar_new();
    fictif1 = gtk_label_new("");
    fictif2 = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(pMainVBox), fictif1, TRUE, TRUE, 100);

    pLabel = gtk_label_new(NULL);
    sUtf8 = g_locale_to_utf8("<span face=\"Arial Black\"  weight=\"bold\" foreground=\"#DDADFF\" size=\"320\">Démarrage...</span>", -1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(pLabel), sUtf8);
    g_free(sUtf8);
    gtk_box_pack_start(GTK_BOX(pLabelBox), pLabel, FALSE, TRUE, 10);
    gtk_box_pack_start(GTK_BOX(pMainVBox), pLabelBox, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(pMainVBox), pProgress, FALSE,FALSE , 0);
    gtk_box_pack_start(GTK_BOX(pMainVBox), fictif2, TRUE,TRUE , 0);
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pProgress), 0.0);
    gtk_widget_show_all(pWindow);
    gtk_grab_add(pProgress);

    for(i = 0 ; i < iTotal ; ++i)
    {
      dFraction = (gdouble)i / (gdouble)iTotal;
      gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(pProgress), dFraction);
      gtk_main_iteration();
    }

    gtk_grab_remove(pProgress);
    gtk_widget_destroy(pWindow);
}


void DllExport   accueil()
{

    GtkWidget *pWindow;
    GtkWidget *pMainVBox;
    GtkWidget *pLabelBox;
    GtkWidget *fictif1;
    GtkWidget *pLabel;
    GtkWidget *sUtf8;
    GtkWidget *pVBoxFrame_butt;
    GtkWidget *pButton[2];

    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(pWindow), "Accueil");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 838, 556);
    gtk_window_set_icon_from_file (pWindow,"./ressources/images/accueil.ico",NULL);
    gtk_window_move(pWindow,280,40);

    pMainVBox = gtk_vbox_new(FALSE, 0);
    pLabelBox = gtk_hbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(pWindow), pMainVBox);

    fictif1 = gtk_label_new("");
    gtk_box_pack_start(GTK_BOX(pMainVBox), fictif1, TRUE, TRUE, 150);

    pButton[0] = gtk_button_new_with_label("Quitter");
    pButton[1] = gtk_button_new_with_label("Continuer");

    pVBoxFrame_butt=gtk_hbox_new(TRUE,0);
    gtk_box_pack_start(GTK_BOX(pVBoxFrame_butt), pButton[0], TRUE, TRUE, 100);
    gtk_box_pack_start(GTK_BOX(pVBoxFrame_butt), pButton[1], TRUE, TRUE, 100);

    gtk_box_pack_start(GTK_BOX(pMainVBox), pVBoxFrame_butt, FALSE,FALSE , 0);

    pLabel = gtk_label_new(NULL);
    sUtf8 = g_locale_to_utf8("<span face=\"Arial Black\"  weight=\"bold\" foreground=\"#FFFFFF\" size=\"12\">Réalisé par: </span> \n"
                             "<span face=\"Gabriola\"  weight=\"bold\" foreground=\"#FFFFFF\" size=\"12\">\t KABORE Y. Eric</span> \n"
                             "<span face=\"Arial Black\"  weight=\"bold\" foreground=\"#FFFFFF\" size=\"12\">Sous la supervision de: </span> \n"
                             "<span face=\"Gabriola\"  weight=\"bold\" foreground=\"#FFFFFF\" size=\"12\">\t Dr Roger NOUSSI</span> \n"
                             "<span face=\"Gabriola\"  weight=\"bold\" foreground=\"#FFFFFF\" size=\"12\">Dans le cadre du cours de Type Abstrait de Données </span> \n \n"
                             "<span face=\"Gabriola\"  weight=\"bold\" foreground=\"#FFFFFF\" size=\"12\"> \t \t \t \t \t \t \t \t Copyright @IAI 2017 </span> \n", -1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(pLabel), sUtf8);
    g_free(sUtf8);

    gtk_box_pack_start(GTK_BOX(pLabelBox), pLabel, FALSE, FALSE, 30);
    gtk_box_pack_start(GTK_BOX(pMainVBox), pLabelBox, TRUE,TRUE , 0);

    g_signal_connect(G_OBJECT(pButton[0]), "clicked", G_CALLBACK(on_quitter_btn), (GtkWidget*) pWindow);
    g_signal_connect(G_OBJECT(pButton[1]), "clicked", G_CALLBACK(continuer), (GtkWidget*) pWindow);

    gtk_widget_show_all(pWindow);

}

void DllExport on_quitter_btn(GtkWidget* widget, gpointer data)
{
    GtkWidget *pQuestion;

    /* Création de la boite de message */
    /* Type : Question -> GTK_MESSAGE_QUESTION */
    /* Boutons : 1 OUI, 1 NON -> GTK_BUTTONS_YES_NO */
    pQuestion = gtk_message_dialog_new (GTK_WINDOW(data),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Voulez-vous vraiment\nquitter ce programme?");

    /* Affichage et attente d une réponse */
    switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
    {
        case GTK_RESPONSE_YES:
            /* OUI -> on quitte l application */
            gtk_main_quit();
            break;
        case GTK_RESPONSE_NO:
            /* NON -> on détruit la boite de message */
            gtk_widget_destroy(pQuestion);
            break;
    }
}


void DllExport on_quitter_icon(GtkWidget* widget, gpointer data)
{
    GtkWidget *pQuestion;

    /* Création de la boite de message */
    /* Type : Question -> GTK_MESSAGE_QUESTION */
    /* Boutons : 1 OUI, 1 NON -> GTK_BUTTONS_YES_NO */
    //gtk_window_move(pQuestion,280,40);
    pQuestion = gtk_message_dialog_new (GTK_WINDOW(data),
        GTK_DIALOG_MODAL,
        GTK_MESSAGE_QUESTION,
        GTK_BUTTONS_YES_NO,
        "Voulez-vous vraiment\nquitter ce programme?");



    /* Affichage et attente d une réponse */
    switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
    {
        case GTK_RESPONSE_YES:
            /* OUI -> on quitte l application */
            gtk_main_quit();
            break;
        case GTK_RESPONSE_NO:
            /* NON -> on détruit la boite de message */
            gtk_widget_destroy(pQuestion);
            Resolution();
            break;
    }
}


void DllExport continuer(GtkWidget *pButton, gpointer data)
{

    gtk_widget_destroy(GTK_CONTAINER((GtkWindow*)data));
    Resolution();

}



void  DllExport  Resolution()
{

    GtkWidget *pWindow;
    GtkWidget *pVBoxMain;
    GtkWidget *pVBox1;
    GtkWidget *pVBox2;
    GtkWidget *pFrame;
    GtkWidget *pVBoxFrame1;
    GtkWidget *pVBoxFrame2;
    GtkWidget *pVBoxFrame3;
    GtkWidget *pVBoxFrame;
    GtkWidget *pVBoxFrame_butt;
    GtkWidget *pSeparator;
    GtkWidget *pEntry;
    GtkWidget *pEntry1;
    GtkWidget *pEntry2;
    GtkWidget *pSortie;
    GtkWidget *pLabel;
    GtkWidget *pLabel1;
    GtkWidget *pLabel2;
    gchar *sUtf8;
    GtkWidget *pButton[2];

    gtk_rc_parse ("./ressources/config/gtk.rc");
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER(pWindow), 5);
    gtk_window_set_title(GTK_WINDOW(pWindow), "Marimont");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 838, 556);
    gtk_window_set_icon_from_file (pWindow,"./ressources/images/accueil.ico",NULL);
    gtk_window_move(pWindow,280,40);

    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(on_quitter_icon), NULL);

    pVBoxMain = gtk_hbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(pWindow), pVBoxMain);

    pVBox1 = gtk_vbox_new(TRUE,0);
    gtk_box_pack_start(GTK_BOX(pVBoxMain), pVBox1, TRUE, TRUE, 20);

    sUtf8 = g_locale_to_utf8("Entrez les données", -1, NULL, NULL, NULL);

    pFrame = gtk_frame_new(sUtf8);
    gtk_box_pack_start(GTK_BOX(pVBox1), pFrame, TRUE, TRUE, 20);
    g_free(sUtf8);

    pVBoxFrame1 = gtk_hbox_new(TRUE, 0);
    pVBoxFrame2 = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(pFrame), pVBoxFrame1);
    gtk_box_pack_start(GTK_BOX(pVBoxFrame1), pVBoxFrame2, TRUE, TRUE, 50);
    pLabel = gtk_label_new(NULL);
    sUtf8 = g_locale_to_utf8("<span foreground=\"#9C00FF\" weight=\"bold\" size=\"172\" >Entrez la liste des sommets,     exemple:    A;B;C    :</span>\n", -1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(pLabel), sUtf8);
    g_free(sUtf8);
    gtk_box_pack_start(GTK_BOX(pVBoxFrame2), pLabel, TRUE, TRUE, 0);
    pEntry1 = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame2), pEntry1, TRUE, TRUE, 0);
    pLabel1 = gtk_label_new(NULL);
    sUtf8 = g_locale_to_utf8("<span foreground=\"#9C00FF\" weight=\"bold\" size=\"172\" >Entrez la liste des arcs,    exemple:    (A,B);(B,C)   :</span>\n", -1, NULL, NULL, NULL);
    gtk_label_set_markup(GTK_LABEL(pLabel1), sUtf8);
    g_free(sUtf8);
    gtk_box_pack_start(GTK_BOX(pVBoxFrame2), pLabel1, FALSE, FALSE, 0);
    pEntry2 = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame2), pEntry2, TRUE, TRUE, 0);
    pButton[0] = gtk_button_new_with_label("OK");
    sUtf8 = g_locale_to_utf8("Réinitialiser", -1, NULL, NULL, NULL);
    pButton[1] = gtk_button_new_with_label(sUtf8);
    pVBox2 = gtk_vbox_new(FALSE,0);
    gtk_box_pack_start(GTK_BOX(pVBox1), pVBox2, TRUE, TRUE, 50);
    sUtf8 = g_locale_to_utf8("Affichage des Résultats", -1, NULL, NULL, NULL);
    pFrame = gtk_frame_new(sUtf8);
    gtk_box_pack_start(GTK_BOX(pVBox2), pFrame, TRUE, TRUE, 0);
    pVBoxFrame = gtk_vbox_new(TRUE, 0);
    pVBoxFrame3 = gtk_hbox_new(TRUE, 0);
    gtk_box_pack_start(pVBoxFrame3, pVBoxFrame, FALSE, TRUE, 50);
    gtk_container_add(GTK_CONTAINER(pFrame), pVBoxFrame3);
    sUtf8 = g_locale_to_utf8("Résultats", -1, NULL, NULL, NULL);
    pSortie = gtk_frame_new(sUtf8);
    gtk_frame_set_label_align(pSortie,0.5,0);
    gtk_frame_set_shadow_type(GTK_FRAME(pSortie), GTK_SHADOW_ETCHED_OUT);
    gtk_box_pack_start(pVBoxFrame, pSortie, FALSE, TRUE, 20);
    pLabel = gtk_label_new("RAS");
    gtk_container_add(GTK_CONTAINER(pSortie), pLabel);
    pVBoxFrame_butt=gtk_hbox_new(TRUE,0);
    gtk_box_pack_start(GTK_BOX(pVBoxFrame_butt), pButton[0], TRUE, TRUE, 100);
    gtk_box_pack_start(GTK_BOX(pVBoxFrame_butt), pButton[1], TRUE, TRUE, 100);
    gtk_box_pack_start(GTK_BOX(pVBoxFrame2), pVBoxFrame_butt, TRUE,FALSE, 0);
    g_signal_connect(G_OBJECT(pButton[0]), "clicked", G_CALLBACK(button_ok),(GtkWidget*) pVBox1);
    g_signal_connect(G_OBJECT(pButton[1]), "clicked", G_CALLBACK(button_initialiser),(GtkWidget*) pVBox1);
    gtk_widget_show_all(pWindow);

    g_free(sUtf8);

}



void DllExport affich_resul(GtkWidget *pLabel,gpointer data)
{

    GtkWidget *pSortie;
    GtkWidget *pSortie2;
    GList *pList;

    pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)data));
    pList = g_list_next(pList);
    pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)(pList->data)));
    pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)(pList->data)));
    pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)(pList->data)));
    pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)(pList->data)));
    pSortie = GTK_WIDGET(pList->data);
    pList =  gtk_container_get_children(GTK_CONTAINER((GtkWidget*)(pList->data)));
    pSortie2 = GTK_WIDGET(pList->data);
    if(pSortie2!=NULL)
    {
        gtk_widget_destroy(pSortie2);
    }


    gtk_container_add(GTK_CONTAINER(pSortie), pLabel);
    gtk_widget_show_all(GTK_CONTAINER(pSortie));


}


void DllExport traitement(const gchar *sText1,const gchar *sText2,gpointer data )
{
    int result;
    const gchar *sText;
    GtkWidget *pLabel;
    gchar *sUtf8;
    pLabel = gtk_label_new(NULL);

    printf("\n --------------------------------------------NOUVEAU traitement------------------------------------------------------ \n");


    result=Marimont(lireGraphe(sText1,sText2));

    if(result)
    {
        printf("\nHvide = %d donc presence circuit\n",result);
        sUtf8 = g_locale_to_utf8("<span background=\"#FFFFFF\" foreground=\"#FFC800\" weight=\"bold\" size=\"172\" >Présence de circuit dans le graphe</span>\n", -1, NULL, NULL, NULL);
        gtk_label_set_markup(GTK_LABEL(pLabel), sUtf8);
        g_free(sUtf8);

    }
    else
    {
        printf("\nHvide = %d donc pas de circuit\n",result);
        sUtf8 = g_locale_to_utf8("<span background=\"#FFFFFF\" foreground=\"#FF0000\" weight=\"bold\" size=\"172\" >Absence de circuit dans le graphe</span>\n", -1, NULL, NULL, NULL);
        gtk_label_set_markup(GTK_LABEL(pLabel), sUtf8);
        g_free(sUtf8);

    }
    printf("\n --------------------------------------------FIN traitement------------------------------------------------------ \n");


    affich_resul(pLabel,data);

}

void DllExport button_ok(GtkWidget *pButton, gpointer data)
{
    GtkWidget *pTempEntry1;
    GtkWidget *pTempEntry2;
    GtkWidget *pTempLabel;
    GList *pList;
    const gchar *sText1;
    const gchar *sText2;

    pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)data));
    pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)(pList->data)));
    pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)(pList->data)));
    pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)(pList->data)));
    pList = g_list_next(pList);
    pTempEntry1 = GTK_WIDGET(pList->data);
    pList = g_list_next(pList);
    pList = g_list_next(pList);
    pTempEntry2 = GTK_WIDGET(pList->data);
    sText1 = gtk_entry_get_text(GTK_ENTRY(pTempEntry1));
    sText2 = gtk_entry_get_text(GTK_ENTRY(pTempEntry2));

    traitement(sText1,sText2,data);

    g_list_free(pList);
}
void DllExport button_initialiser(GtkWidget *pButton, gpointer data)
{
    GtkWidget *pTempEntry1;
    GtkWidget *pTempEntry2;
    GtkWidget *pTempLabel;
    GtkWidget *pSortie;
    GtkWidget *pSortie2;
    GtkWidget *pLabel;

    GList *pList;
    GList *pList1;
    const gchar *sText1;
    const gchar *sText2;

    pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)data));
    pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)(pList->data)));
    pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)(pList->data)));
    pList = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)(pList->data)));
    pList = g_list_next(pList);
    pTempEntry1 = GTK_WIDGET(pList->data);
    pList = g_list_next(pList);
    pList = g_list_next(pList);
    pTempEntry2 = GTK_WIDGET(pList->data);
    gtk_entry_set_text(GTK_ENTRY(pTempEntry1),"");
    gtk_entry_set_text(GTK_ENTRY(pTempEntry2),"");



    pList1 = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)data));
    pList1 = g_list_next(pList1);
    pList1 = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)(pList1->data)));
    pList1 = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)(pList1->data)));
    pList1 = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)(pList1->data)));
    pList1 = gtk_container_get_children(GTK_CONTAINER((GtkWidget*)(pList1->data)));
    pSortie = GTK_WIDGET(pList1->data);
    pList1 =  gtk_container_get_children(GTK_CONTAINER((GtkWidget*)(pList1->data)));
    pSortie2 = GTK_WIDGET(pList1->data);
    if(pSortie2!=NULL)
    {
        gtk_widget_destroy(pSortie2);
    }

    pLabel = gtk_label_new("RAS");
    gtk_container_add(GTK_CONTAINER(pSortie), pLabel);
    gtk_widget_show_all(GTK_CONTAINER(pSortie));

    g_list_free(pList);
}
