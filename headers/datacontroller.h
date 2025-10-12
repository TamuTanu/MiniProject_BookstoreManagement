#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#include <gtk/gtk.h>

struct recivedata{
  GtkEntry *bookName;
  GtkEntry *bookAuthor;
  GtkEntry *bookPrice;
  GtkEntry *bookCoverPath;
};

extern struct recivedata data;

void initAlertWindow();
void onCancelClicked(GtkButton *button,gpointer user_data);
void onDoneClicked(GtkButton *button,gpointer user_data);

#endif
