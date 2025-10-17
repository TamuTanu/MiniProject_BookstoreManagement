#ifndef DISPLAYBOOK_H
#define DISPLAYBOOK_H

#include <gtk/gtk.h>

extern GtkWidget *searchBar;
extern GtkWidget *scrollingWindow;
extern GtkWidget *displayFlowBox;
extern GtkWindow *Pwindow;

GtkWindow* returnWindow(GtkWindow *window);
void mainWindowReload(GtkFlowBox *flowbox,const char *searchterm);
void initScrolling();

#endif
