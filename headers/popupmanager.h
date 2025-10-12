#ifndef POPUPMANAGER_H
#define POPUPMANAGER_H

#include <gtk/gtk.h>

extern GtkWidget *popupwindow;

void showPopupWindow();
void initPopupWindow(GtkWindow *mainWindow,GtkApplication *app);

#endif
