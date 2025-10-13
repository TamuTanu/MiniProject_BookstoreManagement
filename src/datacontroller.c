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
  char *err = NULL;
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

void saveBookData(){

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
