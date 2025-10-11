#include "../headers/datacontroller.h"

void onDoneClicked(GtkButton *button,gpointer user_data){
  GtkEntry *label = GTK_ENTRY(user_data);
  char *text = gtk_editable_get_text(GTK_EDITABLE(label));
  g_print("\nBook Name is: %s",text);
}

void onCancelClicked(GtkButton *button,gpointer user_data){
  GtkWindow *window = GTK_WINDOW(user_data);
  if(window != NULL){
    gtk_widget_set_visible(GTK_WIDGET(window),FALSE);
  }else{
    g_print("window is NULL");
  }
}
