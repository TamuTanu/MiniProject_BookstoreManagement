#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#include <gtk/gtk.h>

struct recivedata{
  GtkEntry *bookName;
  GtkEntry *bookAuthor;
  GtkEntry *bookPrice;
  GtkEntry *bookCoverPath;
};

struct books{
  const char *name;
  const char *author;
  const char *price;
  const char *coverpath;
};

extern struct recivedata data;

void loadBook();
void initAlertWindow();
void onCancelClicked(GtkButton *button,gpointer user_data);
void onDoneClicked(GtkButton *button,gpointer user_data);

#endif
