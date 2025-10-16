#include <../headers/displaybook.h>
#include <../headers/datacontroller.h>

GtkWidget *scrollingWindow;
GtkWidget *displayBox;

void initScrolling(){
  displayBox = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);

  scrollingWindow = gtk_scrolled_window_new();
  gtk_widget_set_size_request(scrollingWindow,800,600);
  g_object_ref_sink(scrollingWindow);
  
  reloadBook(GTK_BOX(displayBox));
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrollingWindow),displayBox);

  gtk_widget_set_visible(scrollingWindow,TRUE);

  g_print("\ninit scrollingWindow successfuly.");
}
