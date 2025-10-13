#include <../headers/displaybook.h>

GtkWidget *scrollingWindow;
GtkWidget *testbutton;

void initScrolling(){

  testbutton = gtk_button_new_with_label("test");

  scrollingWindow = gtk_scrolled_window_new();
  g_object_ref_sink(scrollingWindow);

  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrollingWindow),testbutton);

  gtk_widget_set_visible(scrollingWindow,TRUE);

  g_print("init scrollingWindow successfuly.");
}
