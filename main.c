#include <gtk/gtk.h>

static GtkWidget *window = NULL;

static void activate(GtkApplication *app,gpointer user_data){
	window = gtk_application_window_new (app);
  	gtk_window_set_title (GTK_WINDOW (window), "BookstoreManagement");
  	gtk_widget_set_size_request (window,800,600);
  	gtk_window_present (GTK_WINDOW (window));
}

int main(int argc,char **argv){
	 GtkApplication *app;
	 int status;
 
	app = gtk_application_new ("net.tamutanu.bookstoremanagement", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  	status = g_application_run (G_APPLICATION (app), argc, argv);
  	g_object_unref (app);
	return status;
}
