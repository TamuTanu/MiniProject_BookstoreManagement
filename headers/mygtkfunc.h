#ifndef MYGTKFUNC_H 
#define MYGTKFUNC_H 

#include <gtk/gtk.h>

extern GtkCssProvider *provider;

struct data{
	GtkApplication *app;
	GtkWidget *window;
};

extern struct data gData;

void initCSS();

void cssAddLoadCSS(GtkCssProvider *provider,char *path,GtkWidget *widget,char *class);

void showPopupAddWindow(GtkWidget *button,gpointer user_data);

void showPopupRemoveWindow(GtkWidget *button,gpointer user_data);

void showPopupEditWindow(GtkWidget *button,gpointer user_data);

#endif
