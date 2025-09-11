#ifndef MYGTKFUNC_H 
#define MYGTKFUNC_H 

#include <gtk/gtk.h>

extern GtkCssProvider *provider;

void initCSS();

void cssAddLoadCSS(GtkCssProvider *provider,char *path,GtkWidget *widget,char *class);

#endif
