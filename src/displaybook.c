#include <../headers/displaybook.h>
#include <../headers/datacontroller.h>
#include <../thirdparty/sqlite3.h>
#include <../headers/mygtkfunc.h>

GtkWidget *scrollingWindow;
GtkWidget *displayFlowBox;
GtkWidget *searchBar;

//showDetailBook
GtkWidget *showBookWindow;
GtkWidget *img = NULL;
GtkWidget *titleLabel = NULL;
GtkWidget *authorLabel = NULL;
GtkWidget *priceLabel = NULL;
GtkWidget *showBookBox;
GtkWidget *exitbtn;

GtkWindow *Pwindow;

GtkWindow* returnWindow(GtkWindow *window){
  return window;
}

void showDetailBook(GtkWidget *button,gpointer user_data){ 
  int id = GPOINTER_TO_INT(user_data);
  
  sqlite3 *db;
  sqlite3_stmt *stmt;
  int rc;

  rc = sqlite3_open("books.db",&db);
  if(rc != SQLITE_OK){
    g_print("\nFailed to loadBook from database on deleteWindow.");
  }else{
    g_print("\nDatabase Successfuly load on detailWindow");
  }
  
   const char *sql = "SELECT title, author, price, cover_path FROM books WHERE id = ?;";
  rc = sqlite3_prepare_v2(db,sql,-1,&stmt,0);
  if(rc != SQLITE_OK){
    g_print("\nFailed to loadBook from database on deleteWindow.");
    sqlite3_close(db);
  }

  sqlite3_bind_int(stmt, 1, id);
  rc = sqlite3_step(stmt);

  if (rc == SQLITE_ROW) {

    const char * title = (const char*)sqlite3_column_text(stmt,0);
    const char * author = (const char*)sqlite3_column_text(stmt,1);
    const char * price = (const char*)sqlite3_column_text(stmt,2);
    const char * coverpath = (const char*)sqlite3_column_text(stmt,3);
    
    if (coverpath && coverpath[0] != '\0') {
            gtk_image_set_from_file(GTK_IMAGE(img), coverpath);
        } else {
            gtk_image_set_from_file(GTK_IMAGE(img), "images/placeholder.png");
    }

    gtk_label_set_text(GTK_LABEL(titleLabel), title);
    gtk_label_set_text(GTK_LABEL(authorLabel), author);
    gtk_label_set_text(GTK_LABEL(priceLabel), price);

    gtk_widget_set_visible(showBookWindow,TRUE);
  }else{
    g_print("\nError: Could not find or step book data for ID %d.\n", id);
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
}

void onExitDetail(GtkWidget *button,gpointer user_data){
  gtk_widget_set_visible(showBookWindow,FALSE);
}

void initDetailWindow(){

  img = gtk_image_new_from_file("images/placeholder.png");
  gtk_widget_set_size_request(img,230,310);

  titleLabel = gtk_label_new("Title");
  authorLabel = gtk_label_new("Author");
  priceLabel = gtk_label_new("priceLabel");
  showBookBox = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
  exitbtn = gtk_button_new_with_label("CLOSE");
  g_signal_connect(exitbtn,"clicked",G_CALLBACK(onExitDetail),NULL);

  gtk_box_append(GTK_BOX(showBookBox),img);
  gtk_box_append(GTK_BOX(showBookBox),titleLabel);
  gtk_box_append(GTK_BOX(showBookBox),authorLabel);
  gtk_box_append(GTK_BOX(showBookBox),priceLabel);
  gtk_box_append(GTK_BOX(showBookBox),exitbtn);

  showBookWindow = gtk_window_new();
  gtk_widget_set_size_request(showBookWindow,270,500);
  gtk_window_set_resizable(GTK_WINDOW(showBookWindow),FALSE);
  gtk_window_set_decorated(GTK_WINDOW(showBookWindow),FALSE);
  gtk_window_set_transient_for(GTK_WINDOW(showBookWindow),Pwindow);
  gtk_window_set_modal(GTK_WINDOW(showBookWindow),TRUE);
  g_object_ref_sink(showBookWindow);

  gtk_window_set_child(GTK_WINDOW(showBookWindow),showBookBox);

  gtk_widget_set_visible(showBookWindow,FALSE);
  g_print("\nInit DetailWindow;");
}

void mainWindowReload(GtkFlowBox *flowbox, const char *searchterm) {

    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    const char *sql;
    char *search_value = NULL;

    rc = sqlite3_open("books.db", &db);
    if (rc != SQLITE_OK) {
        g_print("\nFailed to loadBook from database on mainWindow.");
        return;
    } else {
        g_print("\nDatabase Successfuly load on mainWindow");
    }

    if (searchterm && searchterm[0] != '\0') {
        sql = "SELECT id, title, cover_path FROM books WHERE title LIKE ?;";
        search_value = g_strdup_printf("%%%s%%", searchterm);
    } else {
        sql = "SELECT id, title, cover_path FROM books;";
    }

    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        g_print("\nFailed to loadBook from database on mainWindow: %s", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    if (search_value) {
        sqlite3_bind_text(stmt, 1, search_value, -1, SQLITE_TRANSIENT);
        g_free(search_value); // เมื่อ bind แล้ว ก็ free ได้เลย
    }

    if (flowbox != NULL) {
        GtkWidget *child;
        while ((child = gtk_widget_get_first_child(GTK_WIDGET(flowbox))) != NULL) {
            gtk_flow_box_remove(flowbox, child);
        }
    }

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char *title = (const char*)sqlite3_column_text(stmt, 1);
        const char *path = (const char*)sqlite3_column_text(stmt, 2);
        g_print("\nImage path: %s", path);

        GtkWidget *img;
        if (path && path[0] != '\0') {
            img = gtk_image_new_from_file(path);
        } else {
            img = gtk_image_new_from_file("images/placeholder.png");
        }

        gtk_widget_set_size_request(img, 230, 310);
        cssAddLoadCSS(provider,"css/header.css",img,"fixed-image");
        gtk_widget_set_hexpand(img, FALSE);
        gtk_widget_set_vexpand(img, FALSE);
        GtkWidget *bookLabel = gtk_label_new(title);
        GtkWidget *bookBoxs = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);        
        cssAddLoadCSS(provider,"css/header.css",bookBoxs,"fixed-box");
        gtk_widget_set_hexpand(bookBoxs, FALSE);
        gtk_widget_set_vexpand(bookBoxs, FALSE);
        gtk_box_append(GTK_BOX(bookBoxs), img);
        gtk_box_append(GTK_BOX(bookBoxs), bookLabel);
        gtk_widget_set_size_request(bookBoxs,270,350);
        GtkWidget *btn = gtk_button_new();
        cssAddLoadCSS(provider,"css/header.css",btn,"datailabel");
        gtk_widget_set_vexpand(btn, FALSE);
        gtk_widget_set_valign(btn, GTK_ALIGN_START);
        gtk_button_set_child(GTK_BUTTON(btn), bookBoxs);
        gtk_widget_set_size_request(btn,270,350);
        g_signal_connect(btn, "clicked", G_CALLBACK(showDetailBook), GINT_TO_POINTER(id));

        gtk_flow_box_append(flowbox, btn);
        g_print("\nsuccessfuly create item");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void on_search_changed(GtkSearchEntry *entry,gpointer user_data){
  
  const char *search_text = gtk_editable_get_text(GTK_EDITABLE(entry));
  mainWindowReload(GTK_FLOW_BOX(displayFlowBox),search_text);
}

void initScrolling(){
  displayFlowBox = gtk_flow_box_new();
  gtk_flow_box_set_selection_mode(GTK_FLOW_BOX(displayFlowBox), GTK_SELECTION_NONE);
  gtk_flow_box_set_max_children_per_line(GTK_FLOW_BOX(displayFlowBox),3);
  gtk_flow_box_set_min_children_per_line(GTK_FLOW_BOX(displayFlowBox),2);
    
  scrollingWindow = gtk_scrolled_window_new();
  gtk_widget_set_size_request(scrollingWindow,800,600);
  g_object_ref_sink(scrollingWindow);
  
  mainWindowReload(GTK_FLOW_BOX(displayFlowBox),NULL);
  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrollingWindow),displayFlowBox);
  searchBar = gtk_search_entry_new();
  g_signal_connect(searchBar,"search-changed",G_CALLBACK(on_search_changed),NULL);
  initDetailWindow();
  gtk_widget_set_visible(scrollingWindow,TRUE);

  g_print("\ninit scrollingWindow successfuly.");
}
