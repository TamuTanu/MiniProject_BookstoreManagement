#include <gtk/gtk.h>

static void
activate (GtkApplication *app,
          gpointer        user_data)
{

  GtkWidget *window;
  GtkWidget *grid;
  GtkWidget *sub_grid;
  GtkWidget *header;
  GtkWidget *dropdown;
  GtkWidget *overlay;
  GtkWidget *headerBox;

  //Header
  headerBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
  //gtk_widget_add_css_class(headerBox, "header-box");
  gtk_widget_set_name(headerBox, "header-box");
  gtk_widget_set_size_request(headerBox, 800, 100);
  header =  gtk_label_new("    BookstoreManagement");
  //gtk_widget_add_css_class(header, "header-label");
  gtk_widget_set_name(header, "header-label");
  gtk_box_append(GTK_BOX(headerBox), header);
   
  //DropDown
  dropdown = gtk_drop_down_new(NULL,NULL);
  
  //main Grid
  grid = gtk_grid_new();
 
  //sub Grid
  sub_grid = gtk_grid_new();
  gtk_widget_add_css_class(sub_grid, "grid-bg");

  //Main Grid Attach area
  gtk_grid_attach (GTK_GRID (grid), headerBox, 0, 0, 1,1);
  gtk_grid_attach (GTK_GRID (grid), sub_grid, 0, 1, 1,1);
  gtk_grid_attach (GTK_GRID (sub_grid), dropdown, 0,0, 1,1);

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "BookstoreManager");
  gtk_window_set_child(GTK_WINDOW(window),grid);
  
  gtk_widget_set_size_request(window, 800, 600);

  //CSS Loader Area
  GtkCssProvider *provider = gtk_css_provider_new();
  gtk_css_provider_load_from_path(provider,"css/headerstyle.css");
  gtk_css_provider_load_from_path(provider,"css/gridbg.css");
  //Appled CSS to Window
    GdkDisplay *display = gdk_display_get_default();
    gtk_style_context_add_provider_for_display(
        display,
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );
  
  gtk_window_present (GTK_WINDOW (window));
}

int
main (int    argc,
      char **argv)
{
  GtkApplication *app;
  int status;

  app = gtk_application_new ("net.tamutanu.bookstoremanager", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}

