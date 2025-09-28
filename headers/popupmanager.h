#ifndef POPUPMANAGER_H
#define POPUPMANAGER_H

#include <gtk/gtk.h>

extern GtkWidget *popupwindow;

GtkWidget* getwindow(GtkWidget *window);

void initPopupWidget();

void setWindow();

#endif
