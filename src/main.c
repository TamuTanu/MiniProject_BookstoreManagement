#include <gtk/gtk.h>
#include <../headers/mygtkfunc.h>

static GtkWidget *window = NULL;
static GtkWidget *headerLabel;
static GtkWidget *mainGrid;
static GtkWidget *subGrid;
static GtkWidget *mainCenterBox;
static GtkWidget *subCenterBox;
static GtkWidget *selectDropdown;
//static GtkWidget *verticalPaned;

static GtkWidget *addButton;
static GtkWidget *removeButton;
static GtkWidget *editButton;
static GtkWidget *searchBar;

static GtkWidget *windowControls;

static void activate(GtkApplication *app,gpointer user_data){
	
	window = gtk_application_window_new (app);
  	gtk_window_set_title (GTK_WINDOW (window), "BookstoreManagement");
  	gtk_widget_set_size_request (window,800,800);
	gtk_window_set_resizable(GTK_WINDOW(window), FALSE); 

	initCSS();	
	windowControls = gtk_window_controls_new(GTK_PACK_END);

	//Widget
	mainCenterBox = gtk_center_box_new();
	cssAddLoadCSS(provider,"css/header.css",mainCenterBox,"mainCenterBox");
	gtk_widget_set_size_request(mainCenterBox,800,100);

	subCenterBox = gtk_center_box_new();
	gtk_widget_set_size_request(subCenterBox,800,30);
	cssAddLoadCSS(provider,"css/header.css",subCenterBox,"subCenterBox");

	mainGrid = gtk_grid_new();
	subGrid = gtk_grid_new();

	headerLabel = gtk_label_new("    BookstoreManagement");
	cssAddLoadCSS(provider,"css/header.css",headerLabel,"header");
 
	selectDropdown = gtk_drop_down_new(NULL,NULL);
	
	searchBar = gtk_search_entry_new();

/*	verticalPaned = gtk_paned_new(1);
	gtk_paned_set_start_child(GTK_PANED(verticalPaned),searchBar);
	gtk_paned_set_end_child(GTK_PANED(verticalPaned),selectDropdown);
*/
	
	//Button
	addButton = gtk_button_new_with_label("Add");
	gtk_widget_set_size_request(addButton, 266, 30);
	cssAddLoadCSS(provider,"css/header.css",addButton,"optionsButton");
	gtk_widget_set_hexpand(addButton, TRUE);
	g_signal_connect(addButton,"clicked",G_CALLBACK(showPopupAddWindow),window);

	removeButton = gtk_button_new_with_label("Remove");
	gtk_widget_set_size_request(removeButton, 266, 30);
	cssAddLoadCSS(provider,"css/header.css",removeButton,"optionsButton");
	gtk_widget_set_hexpand(removeButton, TRUE);
	g_signal_connect(removeButton,"clicked",G_CALLBACK(showPopupRemoveWindow),NULL);
	
	editButton = gtk_button_new_with_label("Edit");
	gtk_widget_set_size_request(editButton, 266, 30);
	cssAddLoadCSS(provider,"css/header.css",editButton,"optionsButton");
	gtk_widget_set_hexpand(editButton, TRUE);
	g_signal_connect(editButton,"clicked",G_CALLBACK(showPopupEditWindow),NULL);

	gtk_grid_attach(GTK_GRID(mainGrid),mainCenterBox,0,0,1,1);
	gtk_center_box_set_start_widget(GTK_CENTER_BOX(mainCenterBox),headerLabel);
	gtk_center_box_set_start_widget(GTK_CENTER_BOX(subCenterBox),addButton);
	gtk_center_box_set_center_widget(GTK_CENTER_BOX(subCenterBox),removeButton);
	gtk_center_box_set_end_widget(GTK_CENTER_BOX(subCenterBox),editButton);

	//gtk_grid_attach(GTK_GRID(subGrid),verticalPaned,0,0,3,1);
	gtk_grid_attach(GTK_GRID(mainGrid),mainCenterBox,0,0,1,1);
	gtk_grid_attach(GTK_GRID(mainGrid),searchBar,0,1,1,1);
	gtk_grid_attach(GTK_GRID(mainGrid),subCenterBox,0,2,1,1);
	gtk_grid_attach(GTK_GRID(mainGrid),subGrid,0,3,1,1);
	gtk_window_set_child (GTK_WINDOW (window),mainGrid);

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
