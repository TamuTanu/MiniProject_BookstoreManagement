#include <../headers/deletebook.h>
#include <../headers/datacontroller.h>
#include <../headers/mygtkfunc.h>

GtkWidget *deleteWindow = NULL;
GtkWidget *deleteScrolling;
GtkWidget *deleteTitle;
GtkWidget *itemBox;
GtkWidget *deleteBox;
GtkWidget *buttonBox;
GtkWidget *deleteButton;
GtkWidget *cancelWindow;

void cancelClicked(GtkButton *button,gpointer user_data){
  gtk_widget_set_visible(deleteWindow,FALSE);
}

void onDeleteClicked(GtkButton *button,gpointer user_data){

}

void setDeleteWindow(){
  
  deleteScrolling = gtk_scrolled_window_new();
  cssAddLoadCSS(provider,"css/deletebox.css",deleteScrolling,"scrolledwindow");
  gtk_widget_set_size_request(deleteScrolling,430,350);
  gtk_widget_set_hexpand(deleteScrolling, TRUE);
  gtk_widget_set_vexpand(deleteScrolling, TRUE);

  deleteTitle = gtk_label_new("Select Item");
  gtk_widget_set_size_request(deleteTitle,470,60);
  //deleteBox = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
  deleteBox = gtk_grid_new();
  itemBox = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
  buttonBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);

  deleteButton = gtk_button_new_with_label("DELETE");
  gtk_widget_set_size_request(deleteWindow,160,90);

  cancelWindow = gtk_button_new_with_label("CANCEl");
  gtk_widget_set_size_request(cancelWindow,160,90);
  g_signal_connect(cancelWindow,"clicked",G_CALLBACK(cancelClicked),NULL);
  

  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(deleteScrolling), itemBox);
  
  gtk_box_append(GTK_BOX(buttonBox),deleteButton);
  gtk_box_append(GTK_BOX(buttonBox),cancelWindow);
  /*
  gtk_box_append(GTK_BOX(deleteBox),deleteTitle);
  gtk_box_append(GTK_BOX(deleteBox),deleteScrolling);
  gtk_box_append(GTK_BOX(deleteBox),buttonBox);*/

  gtk_grid_attach(GTK_GRID(deleteBox), deleteTitle, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(deleteBox), deleteScrolling, 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(deleteBox), buttonBox, 0, 2, 1, 1);

  gtk_window_set_child(GTK_WINDOW(deleteWindow),deleteBox);

}

void showPopupDelete(){
  if(deleteWindow != NULL){
    reloadBook(GTK_BOX(itemBox));
    gtk_widget_set_visible(deleteWindow,TRUE);
  }else{
    g_print("DeleteWindow is NULL.");
  }
}

void initDeletePopup(GtkWindow *window,GtkApplication *app){

  if(deleteWindow == NULL){
    deleteWindow = gtk_window_new();
    gtk_widget_set_size_request(deleteWindow,470,465);
    gtk_window_set_resizable(GTK_WINDOW(deleteWindow),FALSE);
    gtk_window_set_application(GTK_WINDOW(deleteWindow),app);
    gtk_window_set_decorated(GTK_WINDOW(deleteWindow),FALSE);
    gtk_window_set_transient_for(GTK_WINDOW(deleteWindow),window);
    gtk_window_set_modal(GTK_WINDOW(deleteWindow),TRUE);
    g_object_ref_sink(deleteWindow);
    gtk_widget_set_visible(deleteWindow,FALSE);
    setDeleteWindow();
    g_print("\nDelete Popup Successfuly init.");
  }else{
    g_print("\nDelete Popup isn't NULL.");
  }

}
