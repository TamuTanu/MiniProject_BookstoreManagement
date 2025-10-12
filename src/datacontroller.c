#include "../headers/datacontroller.h"
#include "../headers/popupmanager.h"

struct recivedata data;

const char *name;
const char *author;
const char *price;
const char *coverpath;

GtkWidget *alertWindow = NULL;
GtkWidget *closeButton;
GtkWidget *textLabel;
GtkWidget *alPaned;

void onAlertShow(GtkButton *button,gpointer user_data){
  gtk_widget_set_visible(alertWindow,FALSE);
  gtk_widget_set_visible(popupwindow,FALSE);
}

void initAlertWindow(){
  closeButton = gtk_button_new_with_label("CLOSE");
  gtk_widget_set_size_request(closeButton,250,60);
  g_signal_connect(closeButton,"clicked",G_CALLBACK(onAlertShow),NULL);

  textLabel = gtk_label_new("Book sucessfuly added.");

  alPaned = gtk_box_new(GTK_ORIENTATION_VERTICAL,90);
  //gtk_paned_set_position(GTK_PANED(alPaned),90);
  //gtk_paned_set_start_child(GTK_PANED(alPaned),textLabel);
  //gtk_paned_set_end_child(GTK_PANED(alPaned),closeButton);
  gtk_box_append(GTK_BOX(alPaned),textLabel);
  gtk_box_append(GTK_BOX(alPaned),closeButton);

  alertWindow = gtk_window_new();
  gtk_widget_set_size_request(alertWindow,250,150);
  gtk_window_set_resizable(GTK_WINDOW(alertWindow),FALSE);
  gtk_window_set_decorated(GTK_WINDOW(alertWindow),FALSE);
  gtk_window_set_transient_for(GTK_WINDOW(alertWindow),GTK_WINDOW(popupwindow));
  gtk_window_set_modal(GTK_WINDOW(alertWindow),TRUE);
  gtk_widget_set_visible(alertWindow,FALSE);

  gtk_window_set_child(GTK_WINDOW(alertWindow),alPaned);
}

void onDoneClicked(GtkButton *button,gpointer user_data){
  
  name = gtk_editable_get_text(GTK_EDITABLE(data.bookName));
  author = gtk_editable_get_text(GTK_EDITABLE(data.bookAuthor));
  price = gtk_editable_get_text(GTK_EDITABLE(data.bookPrice));
  coverpath = gtk_editable_get_text(GTK_EDITABLE(data.bookCoverPath));

  gtk_widget_set_visible(alertWindow,TRUE);
  g_print("\nBook Name is %s.\nAuthor is %s.\nPrice is %s.\nPath: %s",name,author,price,coverpath);
}

void onCancelClicked(GtkButton *button,gpointer user_data){
  if(popupwindow != NULL){
    gtk_widget_set_visible(GTK_WIDGET(popupwindow),FALSE);
  }else{
    g_print("window is NULL");
  }
}
