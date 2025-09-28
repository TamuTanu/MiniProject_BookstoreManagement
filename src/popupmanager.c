#include "../headers/popupmanager.h"

//GtkWidget Declared zone
GtkWidget *popupwindow;
GtkWidget *bookNamebar;
GtkWidget *bookAuthorbar;
GtkWidget *bookPricebar;
GtkWidget *doneButton;
GtkWidget *cancerButton;
GtkWidget *bookCoverImage;
GtkWidget *bookCoverPathbar;
GtkWidget *findPathButton;

GtkWidget *paned;
GtkWidget *grid;
GtkWidget *box;

GtkWidget* getwindow(GtkWidget *window){
	return window;
}

void initPopupWidget(){

	bookNamebar = gtk_entry_new();
	gtk_widget_set_size_request(bookNamebar,300,30);
	gtk_widget_set_hexpand(bookNamebar,TRUE);

	bookAuthorbar = gtk_entry_new();
	gtk_widget_set_size_request(bookAuthorbar,300,30);
	gtk_widget_set_hexpand(bookAuthorbar,TRUE);

	bookPricebar = gtk_entry_new();
	gtk_widget_set_size_request(bookPricebar,300,30);
	gtk_widget_set_hexpand(bookPricebar,TRUE);

	doneButton = gtk_button_new();
	gtk_widget_set_size_request(doneButton,120,60);
	//gtk_widget_set_hexpand(doneButton,TRUE);
	//gtk_widget_set_vexpand(doneButton,TRUE);

	cancerButton = gtk_button_new();
	gtk_widget_set_size_request(cancerButton,120,60);
	//gtk_widget_set_hexpand(cancerButton,TRUE);
	//gtk_widget_set_vexpand(cancerButton,TRUE);

	bookCoverImage = gtk_image_new_from_file("/home/tamutanu/Dev/C/MiniProject_BookstoreManagement/images/placeholder.png");
	gtk_widget_set_size_request(bookCoverImage,230,310);

	bookCoverPathbar = gtk_entry_new();
	gtk_widget_set_size_request(bookCoverPathbar,260,30);
	gtk_widget_set_hexpand(bookCoverPathbar,TRUE);

	findPathButton = gtk_button_new();
	gtk_widget_set_size_request(findPathButton,30,30);
	gtk_widget_set_hexpand(findPathButton,TRUE);

	paned = gtk_paned_new(0);
	gtk_paned_set_position(GTK_PANED(paned),270);
	grid = gtk_grid_new();
	box = gtk_box_new(0,10);

}

void initWidget(){
	
}

void setWindow(){
	
	//grid attach column,row
	gtk_grid_attach(GTK_GRID(grid),bookNamebar,0,0,2,1);
	gtk_grid_attach(GTK_GRID(grid),bookAuthorbar,0,1,2,1);
	gtk_grid_attach(GTK_GRID(grid),bookPricebar,0,2,2,1);

	gtk_grid_attach(GTK_GRID(grid),bookCoverPathbar,0,3,1,1);
	gtk_grid_attach(GTK_GRID(grid),findPathButton,1,3,1,1);

	//gtk_grid_attach(GTK_GRID(grid),doneButton,0,4,1,1);
	//gtk_grid_attach(GTK_GRID(grid),cancerButton,1,4,1,1);

	gtk_box_append(GTK_BOX(box), doneButton);
	gtk_widget_set_margin_start(doneButton, 40);	
	gtk_box_append(GTK_BOX(box), cancerButton);
	gtk_grid_attach(GTK_GRID(grid), box, 0, 4, 2, 1);

	gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
	gtk_grid_set_column_spacing(GTK_GRID(grid), 20);


	gtk_window_set_child(GTK_WINDOW(popupwindow),paned);
	gtk_paned_set_start_child(GTK_PANED(paned),bookCoverImage);
	gtk_paned_set_end_child(GTK_PANED(paned),grid);

}
