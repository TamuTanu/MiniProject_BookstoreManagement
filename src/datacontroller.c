#include "../headers/datacontroller.h"
#include "../headers/popupmanager.h"
#include "../thirdparty/sqlite3.h"

struct recivedata data;
struct books book;

const char *name;
const char *author;
const char *price;
const char *coverpath;

GtkWidget *alertWindow = NULL;
GtkWidget *closeButton;
GtkWidget *textLabel;
GtkWidget *alPaned;

void loadBook(){
  sqlite3 *db;
  const char *sqlChecker = "SELECT name FROM sqlite_master WHERE type='table' AND name='books';";
  sqlite3_stmt *stmt;

  if (sqlite3_open("books.db", &db) != SQLITE_OK) {
    g_warning("Cannot open database: %s", sqlite3_errmsg(db));
    return;
  }

  sqlite3_prepare_v2(db, sqlChecker, -1, &stmt, NULL);

  if (sqlite3_step(stmt) == SQLITE_ROW) {
    g_print("✅ Table exists.\n");
  } else {
    g_print("❌ Table not found.\n");

    sqlite3_exec(db,
    "CREATE TABLE IF NOT EXISTS books ("
    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "title TEXT,"
    "author TEXT,"
    "price TEXT,"
    "cover_path TEXT);",
    0, 0, 0
    );

    g_print("\nNew table Created.");

  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
}

void reloadBook(GtkBox *bookbox){
  
  sqlite3 *db;
  sqlite3_stmt *stmt;
  int rc;
  
  rc = sqlite3_open("books.db",&db);
  if(rc != SQLITE_OK){
    g_print("Failed to init database;");
  //Book list example.
    if(bookbox != NULL){
      GtkWidget *child;
      while ((child = gtk_widget_get_first_child(GTK_WIDGET(bookbox))) != NULL) {
          gtk_box_remove(bookbox, child);
      }
    }
    for (int i = 0; i < 50; i++) {
        char label[8];
        snprintf(label, sizeof(label), "NULL%d", i + 1);
        GtkWidget *btn = gtk_button_new_with_label(label);
        gtk_box_append(bookbox, btn);
    }
  }else{
    g_print("\nDatabase sucessfuly reload.");
  }

  const char *sql = "SELECT id,title FROM books;";
  rc = sqlite3_prepare_v2(db,sql,-1,&stmt,0);
  if(rc != SQLITE_OK){
    g_print("\nPromblem while preparing database commands.");
    sqlite3_close(db);
  }
  
  if(bookbox != NULL){
    GtkWidget *child;
    while((child = gtk_widget_get_first_child(GTK_WIDGET(bookbox))) != NULL){
        gtk_box_remove(bookbox,child);
    }
  }
  while((rc = sqlite3_step(stmt)) == SQLITE_ROW){
    int id = sqlite3_column_int(stmt,0);
    const char *title = (const char*)sqlite3_column_text(stmt,1);
    GtkWidget *btn = gtk_button_new_with_label(title);
    gtk_box_append(bookbox,btn);
  }

  if(rc != SQLITE_DONE){
    g_print("\nError while fetching data.",sqlite3_errmsg(db));
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);

}

void saveBookData(){
sqlite3 *db;
  sqlite3_stmt *stmt;
  int rc;
  rc = sqlite3_open("books.db",&db);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Can't open databese:%s\n", sqlite3_errmsg(db));
  }else{
    fprintf (stdout,"sucessfuly opendatabese!\n");
  }
const char *sql = "INSERT INTO books (title, author, price, cover_path) VALUES (?, ?, ?, ?);";
rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
if (rc !=SQLITE_OK){
  fprintf(stderr, "Cannot preparing SQL!:%s\n", sqlite3_errmsg(db));
  sqlite3_close(db);

sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
sqlite3_bind_text(stmt, 2, author, -1, SQLITE_STATIC);
sqlite3_bind_text(stmt, 3, price, -1, SQLITE_STATIC);
sqlite3_bind_text(stmt, 4, coverpath, -1, SQLITE_STATIC);
    }
rc = sqlite3_step(stmt);
if (rc != SQLITE_DONE) {
  fprintf(stderr, "Cannot execute statement:%s\n", sqlite3_errmsg(db));
}else{
  fprintf(stdout, "Sucessfuly input databese!");
  }

sqlite3_finalize(stmt);
sqlite3_close(db);
}

void onAlertShow(GtkButton *button,gpointer user_data){
  gtk_widget_set_visible(alertWindow,FALSE);
  gtk_widget_set_visible(popupwindow,FALSE);
}

void initAlertWindow(){
  closeButton = gtk_button_new_with_label("CLOSE");
  gtk_widget_set_size_request(closeButton,250,60);
  g_signal_connect(closeButton,"clicked",G_CALLBACK(onAlertShow),NULL);

  textLabel = gtk_label_new("Book sucessfuly added.");

  alPaned = gtk_box_new(GTK_ORIENTATION_VERTICAL,90);
  gtk_box_append(GTK_BOX(alPaned),textLabel);
  gtk_box_append(GTK_BOX(alPaned),closeButton);

  alertWindow = gtk_window_new();
  gtk_widget_set_size_request(alertWindow,250,150);
  gtk_window_set_resizable(GTK_WINDOW(alertWindow),FALSE);
  gtk_window_set_decorated(GTK_WINDOW(alertWindow),FALSE);
  gtk_window_set_transient_for(GTK_WINDOW(alertWindow),GTK_WINDOW(popupwindow));
  gtk_window_set_modal(GTK_WINDOW(alertWindow),TRUE);
  gtk_widget_set_visible(alertWindow,FALSE);

  gtk_window_set_child(GTK_WINDOW(alertWindow),alPaned);
}

void onDoneClicked(GtkButton *button,gpointer user_data){
  
  book.name = gtk_editable_get_text(GTK_EDITABLE(data.bookName));
  book.author = gtk_editable_get_text(GTK_EDITABLE(data.bookAuthor));
  book.price = gtk_editable_get_text(GTK_EDITABLE(data.bookPrice));
  book.coverpath = gtk_editable_get_text(GTK_EDITABLE(data.bookCoverPath));
  saveBookData();
  gtk_widget_set_visible(alertWindow,TRUE);
  g_print("\nBook Name is %s.\nAuthor is %s.\nPrice is %s.\nPath: %s",
          book.name,book.author,book.price,book.coverpath);
}

void onCancelClicked(GtkButton *button,gpointer user_data){
  if(popupwindow != NULL){
    gtk_widget_set_visible(GTK_WIDGET(popupwindow),FALSE);
  }else{
    g_print("window is NULL");
  }
}
