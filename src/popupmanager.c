#include "../headers/popupmanager.h"
#include "../headers/mygtkfunc.h"

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
GtkFileDialog *fileDialog;

GtkWidget *paned;
GtkWidget *grid;
GtkWidget *box;

GtkWidget* getwindow(GtkWidget *window){
	return window;
}


void onFileDialogOpen(GtkFileDialog* self,GAsyncResult *res,gpointer user_data){

  GFile *file = gtk_file_dialog_open_finish(self,res,NULL);
  if(file){
    char *path = g_file_get_path(file);
    g_print("Cover path is %s\n",path);
    g_free(file);
    g_object_unref (file);
  }

}

void onButtonClicked(GtkWidget *button,gpointer user_data){

  fileDialog = gtk_file_dialog_new();

  gtk_file_dialog_open(fileDialog,GTK_WINDOW(user_data),NULL,(GAsyncReadyCallback)onFileDialogOpen,NULL);

}

void initPopupWidget(){

	bookNamebar = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(bookNamebar),"Input BookName.");
	gtk_widget_set_size_request(bookNamebar,300,30);
	gtk_widget_set_hexpand(bookNamebar,TRUE);
  gtk_widget_set_margin_top(bookNamebar,15 );
  gtk_widget_set_margin_start(bookNamebar,10);
  gtk_widget_set_margin_end(bookNamebar,10);
  cssAddLoadCSS(provider,"css/inputbar.css",bookNamebar,"entrybar");

	bookAuthorbar = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(bookAuthorbar),"Input Author Name.");
	gtk_widget_set_size_request(bookAuthorbar,300,30);
	gtk_widget_set_hexpand(bookAuthorbar,TRUE);
  gtk_widget_set_margin_top(bookAuthorbar, 15);
  gtk_widget_set_margin_start(bookAuthorbar,10);
  gtk_widget_set_margin_end(bookAuthorbar,10);
  cssAddLoadCSS(provider,"css/inputbar.css",bookAuthorbar,"inputbar");

	bookPricebar = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(bookPricebar),"Input BookPrice.");
	gtk_widget_set_size_request(bookPricebar,300,30);
	gtk_widget_set_hexpand(bookPricebar,TRUE);
  gtk_widget_set_margin_top(bookPricebar, 10);
  gtk_widget_set_margin_start(bookPricebar,10);
  gtk_widget_set_margin_end(bookPricebar,10);
  cssAddLoadCSS(provider,"css/inputbar.css",bookPricebar,"inputbar");

	doneButton = gtk_button_new_with_label("DONE");
	gtk_widget_set_size_request(doneButton,120,60);
  gtk_widget_set_margin_top(doneButton, 15);

	cancerButton = gtk_button_new_with_label("CANCEL");
	gtk_widget_set_size_request(cancerButton,120,60);
  gtk_widget_set_margin_top(cancerButton, 15);

	bookCoverImage = gtk_image_new_from_file("images/placeholder.png");
	gtk_widget_set_size_request(bookCoverImage,230,310);

	bookCoverPathbar = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(bookCoverPathbar),"Input Cover Path.");
	gtk_widget_set_size_request(bookCoverPathbar,260,30);
	gtk_widget_set_hexpand(bookCoverPathbar,TRUE);
  gtk_widget_set_margin_top(bookCoverPathbar, 15);
  gtk_widget_set_margin_start(bookCoverPathbar,10);
  cssAddLoadCSS(provider,"css/inputbar.css",bookAuthorbar,"inputbar");

	findPathButton = gtk_button_new();
  gtk_button_set_icon_name(GTK_BUTTON(findPathButton),"document-open");
	gtk_widget_set_size_request(findPathButton,30,30);
	gtk_widget_set_hexpand(findPathButton,TRUE);
  gtk_widget_set_margin_top(findPathButton, 15);
  g_signal_connect(findPathButton,"clicked",G_CALLBACK(onButtonClicked),popupwindow);

	paned = gtk_paned_new(0);
	gtk_paned_set_position(GTK_PANED(paned),270);
	grid = gtk_grid_new();
	box = gtk_box_new(0,10);

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
