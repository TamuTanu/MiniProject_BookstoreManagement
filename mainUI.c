#include <gtk/gtk.h>

//Define area
static Gtkwidget *window;
static Gtkwidget *grid;
static Gtkwidget *title;

static void init();

static void
activate (GtkApplication *app,
          gpointer        user_data)
{
  //GtkWidget *window; 
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "BookstoreManagement");
  gtk_window_set_default_size (GTK_WINDOW (window), 1200, 800);
  gtk_window_present (GTK_WINDOW (window));
  grid = gtk_grid_new();
  gtk_window_set_child(GTK_GRID (window),grid);
  init();
}

static void init(){
	
	//char *titleName[50];
	//titleName = "Bookstore Management";
	title = gtk_label_new_with_mnemonic("Bookstore Management");
	gtk_grid_attach(GTK_GRID (grid),title,0,0,1,1);

}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

