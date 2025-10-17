#include <../headers/editBook.h>
#include <../headers/mygtkfunc.h>
#include <../thirdparty/sqlite3.h>
//selectWindow
GtkWidget *selectWindow = NULL;
GtkWidget *selectScrolling = NULL;
GtkWidget *selectItembox;
GtkWidget *editTitle;
GtkWidget *exitButton;
GtkWidget *selectBox;

//editWindow
GtkWidget *editWindow = NULL;
GtkWidget *booknamebar;
GtkWidget *bookauthorbar;
GtkWidget *bookpricebar;
GtkWidget *bookcoverimage;
GtkWidget *bookcoverbar;
GtkWidget *findpathbutton;
GtkWidget *donebutton;
GtkWidget *cancelbutton;
GtkWidget *editPaned;
GtkWidget *editGrid;
GtkWidget *editBox;

typedef struct {
  char *title;
  char *author;
  char *price;
  char *coverpath;
}BookData;

BookData *Edata = NULL;
BookData *Gdata = NULL;

static int ID;

void onItemClicked(GtkWidget *button,gpointer user_data){
  
  int id = GPOINTER_TO_INT(user_data);
  ID = id;

  sqlite3 *db;
  sqlite3_stmt *stmt;
  int rc;

  rc = sqlite3_open("books.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    }

  const char *sql = "SELECT title, author, price, cover_path FROM books WHERE id = ?;";
  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }

  sqlite3_bind_int(stmt, 1, ID);
  rc = sqlite3_step(stmt);

  if (rc == SQLITE_ROW) {
        Edata->title = g_strdup((const char*)sqlite3_column_text(stmt, 0));
        Edata->author = g_strdup((const char*)sqlite3_column_text(stmt, 1));
        Edata->price = g_strdup((const char*)sqlite3_column_text(stmt, 2));
        Edata->coverpath = g_strdup((const char*)sqlite3_column_text(stmt, 3));

        gtk_entry_set_placeholder_text(GTK_ENTRY(booknamebar),Edata -> title);
        gtk_entry_set_placeholder_text(GTK_ENTRY(bookauthorbar),Edata->author);
        gtk_entry_set_placeholder_text(GTK_ENTRY(bookpricebar),Edata->price);
        gtk_entry_set_placeholder_text(GTK_ENTRY(bookcoverbar),Edata->coverpath);

        
    } else {
        fprintf(stderr, "Book with ID %d not found.\n",ID);
    }
  
  sqlite3_finalize(stmt);
  sqlite3_close(db);
  gtk_widget_set_visible(editWindow,TRUE);
}

void loadReloadBook(GtkBox *bookBox){
  
  sqlite3 *db;
  sqlite3_stmt *stmt;
  int rc;

  rc = sqlite3_open("books.db",&db);
  if(rc != SQLITE_OK){
    g_print("\nFailed to loadBook from database on EditWindow.");
  }else{
    g_print("\nDatabase Successfuly load on EditWindow");
  }
  
  const char *sql = "SELECT id,title FROM books;";
  rc = sqlite3_prepare_v2(db,sql,-1,&stmt,0);
  if(rc != SQLITE_OK){
    g_print("\nFailed to loadBook from database on EditWindow.");
    sqlite3_close(db);
  }

  if(bookBox != NULL){
    GtkWidget *child;
    while((child = gtk_widget_get_first_child(GTK_WIDGET(bookBox))) != NULL){
      gtk_box_remove(bookBox,child);
    }
  }

  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW){
    int id = sqlite3_column_int(stmt,0);
    const char *titleOG = (const char*)sqlite3_column_text(stmt,1);
    GtkWidget *btn = gtk_button_new_with_label(titleOG);
    g_signal_connect(btn,"clicked",G_CALLBACK(onItemClicked),GINT_TO_POINTER(id));
    gtk_box_append(bookBox,btn);
    g_print("\nsuccessfuly create item");
  }

}

void editData(){
sqlite3 *db;
sqlite3_stmt *stmt;
int rc;

rc = sqlite3_open("books.db", &db);
if (rc != SQLITE_OK){
fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
 return; 
}

const char *sql = "UPDATE books SET title = ?, author = ?, price = ?, cover_path = ? WHERE id = ?;";
rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

if(rc != SQLITE_OK){
 fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
} else {
 sqlite3_bind_text(stmt, 1, Gdata->title, -1, SQLITE_STATIC);
 sqlite3_bind_text(stmt, 2, Gdata->author, -1, SQLITE_STATIC);
 sqlite3_bind_text(stmt, 3, Gdata->price, -1, SQLITE_STATIC);
 sqlite3_bind_text(stmt, 4, Gdata->coverpath, -1, SQLITE_STATIC);
 sqlite3_bind_int(stmt, 5, ID);

 rc = sqlite3_step(stmt);
 if (rc != SQLITE_DONE){
 fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
 } else {
 g_print("\nBook with ID %d has been updated successfully.", ID);
  }
 }

 sqlite3_finalize(stmt);
 sqlite3_close(db);
}

void DoneClicked(GtkWidget *button,gpointer user_data){
  
  g_free(Gdata->title);
  g_free(Gdata->author);
  g_free(Gdata->price);
  g_free(Gdata->coverpath);

  Gdata->title = g_strdup(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(booknamebar))));
  Gdata->author = g_strdup(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(bookauthorbar))));
  Gdata->price = g_strdup(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(bookpricebar))));
  Gdata->coverpath = g_strdup(gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(bookcoverbar))));

  g_print("\nNew Data detect");
  editData();
  gtk_widget_set_visible(editWindow,FALSE);
}

void showPopupEdit(){
  loadReloadBook(GTK_BOX(selectItembox));
  gtk_widget_set_visible(selectWindow,TRUE);
}

void CancelClicked(GtkWidget *button,gpointer user_data){
  gtk_widget_set_visible(editWindow,FALSE);
}

void initEditPopupWidget(){

  booknamebar = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(booknamebar),NULL);
	gtk_widget_set_size_request(booknamebar,300,30);
	gtk_widget_set_hexpand(booknamebar,TRUE);
  gtk_widget_set_margin_top(booknamebar,15 );
  gtk_widget_set_margin_start(booknamebar,10);
  gtk_widget_set_margin_end(booknamebar,10);
  cssAddLoadCSS(provider,"css/inputbar.css",booknamebar,"entrybar");

	bookauthorbar = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(bookauthorbar),NULL);
	gtk_widget_set_size_request(bookauthorbar,300,30);
	gtk_widget_set_hexpand(bookauthorbar,TRUE);
  gtk_widget_set_margin_top(bookauthorbar, 15);
  gtk_widget_set_margin_start(bookauthorbar,10);
  gtk_widget_set_margin_end(bookauthorbar,10);
  cssAddLoadCSS(provider,"css/inputbar.css",bookauthorbar,"inputbar");

	bookpricebar = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(bookpricebar),NULL);
	gtk_widget_set_size_request(bookpricebar,300,30);
	gtk_widget_set_hexpand(bookpricebar,TRUE);
  gtk_widget_set_margin_top(bookpricebar, 10);
  gtk_widget_set_margin_start(bookpricebar,10);
  gtk_widget_set_margin_end(bookpricebar,10);
  cssAddLoadCSS(provider,"css/inputbar.css",bookpricebar,"inputbar");
  
  bookcoverbar = gtk_entry_new();
  gtk_entry_set_placeholder_text(GTK_ENTRY(bookcoverbar),NULL);
	gtk_widget_set_size_request(bookcoverbar,260,30);
	gtk_widget_set_hexpand(bookcoverbar,TRUE);
  gtk_widget_set_margin_top(bookcoverbar, 15);
  gtk_widget_set_margin_start(bookcoverbar,10);
  cssAddLoadCSS(provider,"css/inputbar.css",bookcoverbar,"inputbar");

  findpathbutton = gtk_button_new();
  gtk_button_set_icon_name(GTK_BUTTON(findpathbutton),"document-open");
	gtk_widget_set_size_request(findpathbutton,30,30);
	gtk_widget_set_hexpand(findpathbutton,TRUE);
  gtk_widget_set_margin_top(findpathbutton, 15);
  //g_signal_connect(findPathButton,"clicked",G_CALLBACK(onButtonClicked),popupwindow);
  
  bookcoverimage = gtk_image_new_from_file("images/placeholder.png");
 	gtk_widget_set_size_request(bookcoverbar,230,310);

  donebutton = gtk_button_new_with_label("DONE");
	gtk_widget_set_size_request(donebutton,120,60);
  gtk_widget_set_margin_top(donebutton, 15);
  g_signal_connect(donebutton,"clicked",G_CALLBACK(DoneClicked),NULL); 

	cancelbutton = gtk_button_new_with_label("CANCEL");
	gtk_widget_set_size_request(cancelbutton,120,60);
  gtk_widget_set_margin_top(cancelbutton, 15);
  g_signal_connect(cancelbutton,"clicked",G_CALLBACK(CancelClicked),NULL); 
  
  editPaned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
  gtk_paned_set_position(GTK_PANED(editPaned),270);
  cssAddLoadCSS(provider,"css/inputbar.css",editPaned,"panedframe");
	editGrid = gtk_grid_new();
	editBox = gtk_box_new(0,10);

  //grid attach column,row
	gtk_grid_attach(GTK_GRID(editGrid),booknamebar,0,0,2,1);
	gtk_grid_attach(GTK_GRID(editGrid),bookauthorbar,0,1,2,1);
	gtk_grid_attach(GTK_GRID(editGrid),bookpricebar,0,2,2,1);

	gtk_grid_attach(GTK_GRID(editGrid),bookcoverbar,0,3,1,1);
	gtk_grid_attach(GTK_GRID(editGrid),findpathbutton,1,3,1,1);


	gtk_box_append(GTK_BOX(editBox), donebutton);
	gtk_widget_set_margin_start(donebutton, 40);	
	gtk_box_append(GTK_BOX(editBox), cancelbutton);
	gtk_grid_attach(GTK_GRID(editGrid), editBox, 0, 4, 2, 1);

	gtk_grid_set_row_spacing(GTK_GRID(editGrid), 10);
	gtk_grid_set_column_spacing(GTK_GRID(editGrid), 20);


	gtk_window_set_child(GTK_WINDOW(editWindow),editPaned);
	gtk_paned_set_start_child(GTK_PANED(editPaned),bookcoverimage);
	gtk_paned_set_end_child(GTK_PANED(editPaned),editGrid);

}

void initEditWindow(){
  if(editWindow == NULL){
      editWindow = gtk_window_new();
      gtk_widget_set_size_request(editWindow,600,400);
      gtk_window_set_resizable(GTK_WINDOW(editWindow),FALSE);
      
      gtk_window_set_decorated(GTK_WINDOW(editWindow),FALSE);
      gtk_window_set_transient_for(GTK_WINDOW(editWindow),GTK_WINDOW(selectWindow));
      gtk_window_set_modal(GTK_WINDOW(editWindow),TRUE);

      g_object_ref_sink(editWindow);
      
      initEditPopupWidget();
      gtk_widget_set_visible(editWindow,FALSE);

      g_print("\ninit EditPopup successfuly.");

  }else{
    g_print("\npopupWindow already used.");
  }
}

void onExitClicked(GtkWidget *button,gpointer user_data){
  gtk_widget_set_visible(selectWindow,FALSE);
}

void initSelectWidget(){
  selectScrolling = gtk_scrolled_window_new();
  gtk_widget_set_size_request(selectScrolling,430,350);
  gtk_widget_set_hexpand(selectScrolling, TRUE);
  gtk_widget_set_vexpand(selectScrolling, TRUE);

  editTitle = gtk_label_new("Select Item for Edit.");
  gtk_widget_set_size_request(editTitle,470,60);
  
  selectBox = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
  selectItembox = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);

  exitButton = gtk_button_new_with_label("EXIT");
  gtk_widget_set_size_request(exitButton,470,90);
  g_signal_connect(exitButton,"clicked",G_CALLBACK(onExitClicked),NULL);
  
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(selectScrolling),selectItembox);

  gtk_box_append(GTK_BOX(selectBox),editTitle);
  gtk_box_append(GTK_BOX(selectBox),selectScrolling);
  gtk_box_append(GTK_BOX(selectBox),exitButton);

  gtk_window_set_child(GTK_WINDOW(selectWindow),selectBox);

}

void initSelectWindow(GtkWindow *window,GtkApplication *app){
  if(selectWindow == NULL){
    selectWindow = gtk_window_new();
    gtk_widget_set_size_request(selectWindow,470,465);
    gtk_window_set_resizable(GTK_WINDOW(selectWindow),FALSE);
    gtk_window_set_application(GTK_WINDOW(selectWindow),app);
    gtk_window_set_decorated(GTK_WINDOW(selectWindow),FALSE);
    gtk_window_set_transient_for(GTK_WINDOW(selectWindow),window);
    gtk_window_set_modal(GTK_WINDOW(selectWindow),TRUE);
    g_object_ref_sink(selectWindow);
    gtk_widget_set_visible(selectWindow,FALSE);
    
    Edata = g_new0(BookData, 1);
    Gdata = g_new0(BookData, 1);
    initSelectWidget();
    initEditWindow();
    g_print("\nEdit Popup Successfuly init.");
  }else{
    g_print("\nDelete Popup isn't NULL.");
  }

}
