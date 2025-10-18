#include <../headers/deletebook.h>
#include <../headers/datacontroller.h>
#include <../headers/displaybook.h>
#include <../headers/mygtkfunc.h>
#include <../thirdparty/sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

GtkWidget *deleteWindow = NULL;
GtkWidget *confirmWindow = NULL;
GtkWidget *deleteScrolling;
GtkWidget *deleteTitle;
GtkWidget *itemBox;
GtkWidget *deleteBox;
GtkWidget *buttonBox;
GtkWidget *deleteButton;
GtkWidget *cancelWindow;

GtkWidget *confirmLabel;
GtkWidget *confirmButton;
GtkWidget *cancelPopup;
GtkWidget *pGrid;

static int pID;

void bookButtonClicked(GtkWidget *button,gpointer user_data){
  int id = GPOINTER_TO_INT(user_data);
  pID = id;
  gtk_widget_set_visible(confirmWindow,TRUE);
  g_print("\nStill Listening from id: %d.",id);
}

void loadNReloadBook(GtkBox *bookBox){
  
  sqlite3 *db;
  sqlite3_stmt *stmt;
  int rc;

  rc = sqlite3_open("books.db",&db);
  if(rc != SQLITE_OK){
    g_print("\nFailed to loadBook from database on deleteWindow.");
  }else{
    g_print("\nDatabase Successfuly load on deleteWindow");
  }
  
  const char *sql = "SELECT id,title FROM books;";
  rc = sqlite3_prepare_v2(db,sql,-1,&stmt,0);
  if(rc != SQLITE_OK){
    g_print("\nFailed to loadBook from database on deleteWindow.");
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
    cssAddLoadCSS(provider,"css/header.css",btn,"DeleteList");
    g_signal_connect(btn,"clicked",G_CALLBACK(bookButtonClicked),GINT_TO_POINTER(id));
    gtk_box_append(bookBox,btn);
  }

}

void onDeleteConfirm(GtkWidget *button,gpointer user_data){

  int id = pID;
  g_print("\nID: %d preparing for delete.",id);

  sqlite3 *db;
  sqlite3_stmt *stmt;
  int rc;

  rc = sqlite3_open("books.db", &db);
  if (rc != SQLITE_OK) {
    g_print("\n[ERROR] cannot open database: %s", sqlite3_errmsg(db));
  }
  const char *sql = "DELETE FROM books WHERE id = ?;";
  rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
  if (rc != SQLITE_OK){
    g_print("\n[ERROR] Failed to prepare delete statement: %s", sqlite3_errmsg(db));
    sqlite3_close(db);
  }

    sqlite3_bind_int(stmt, 1, id);

    rc = sqlite3_step(stmt);

    if (rc != SQLITE_DONE){
      g_print("\n[ERROR] Failed to execute delete statement : %s", sqlite3_errmsg(db));
    }else{
      g_print("\nBook with ID %d has been deleted Successfuly.",id);
    }
   sqlite3_finalize(stmt);
    sqlite3_close(db);

  gtk_widget_set_visible(confirmWindow,FALSE);
  loadNReloadBook(GTK_BOX(itemBox));
  mainWindowReload(GTK_FLOW_BOX(displayFlowBox),NULL);
}

void cancelClicked(GtkButton *button,gpointer user_data){
  gtk_widget_set_visible(deleteWindow,FALSE);
  gtk_widget_set_visible(confirmWindow,FALSE);
}

void setDeleteWindow(){
  
  deleteScrolling = gtk_scrolled_window_new();
  cssAddLoadCSS(provider,"css/header.css",deleteScrolling,"paned");
  gtk_widget_set_size_request(deleteScrolling,430,350);
  gtk_widget_set_hexpand(deleteScrolling, TRUE);
  gtk_widget_set_vexpand(deleteScrolling, TRUE);

  deleteTitle = gtk_label_new("Select Item");
    cssAddLoadCSS(provider,"css/header.css",deleteTitle,"deleteTitle");
  gtk_widget_set_size_request(deleteTitle,470,60);
  //deleteBox = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
  deleteBox = gtk_grid_new();
  itemBox = gtk_box_new(GTK_ORIENTATION_VERTICAL,5);
    cssAddLoadCSS(provider,"css/header.css",itemBox,"itemBox");
  buttonBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);

  cancelWindow = gtk_button_new_with_label("EXIT");
  gtk_widget_set_size_request(cancelWindow,160,90);
  gtk_widget_set_hexpand(cancelWindow,TRUE);
  gtk_widget_set_vexpand(cancelWindow,TRUE);
    cssAddLoadCSS(provider,"css/header.css",cancelWindow,"exitButton");
  g_signal_connect(cancelWindow,"clicked",G_CALLBACK(cancelClicked),NULL);
  

  gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(deleteScrolling), itemBox);
  
  gtk_box_append(GTK_BOX(buttonBox),cancelWindow);

  gtk_grid_attach(GTK_GRID(deleteBox), deleteTitle, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(deleteBox), deleteScrolling, 0, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(deleteBox), buttonBox, 0, 2, 1, 1);

  gtk_window_set_child(GTK_WINDOW(deleteWindow),deleteBox);

}

void showPopupDelete(){
  if(deleteWindow != NULL){
    loadNReloadBook(GTK_BOX(itemBox));
    gtk_widget_set_visible(deleteWindow,TRUE);
  }else{
    g_print("DeleteWindow is NULL.");
  }
}

void initAlertPopup(){
  
  pGrid = gtk_grid_new();
  confirmLabel = gtk_label_new("Comfirm delete?");
  cssAddLoadCSS(provider,"css/header.css",confirmLabel,"datailabel");
  gtk_widget_set_hexpand(confirmLabel, TRUE);
  gtk_widget_set_vexpand(confirmLabel, TRUE);

  
  confirmButton = gtk_button_new_with_label("confirm");
  cssAddLoadCSS(provider,"css/header.css",confirmButton,"exitButton");
  gtk_widget_set_size_request(confirmButton, 125,50);
  gtk_widget_set_hexpand(confirmButton, TRUE);
  gtk_widget_set_vexpand(confirmButton, TRUE);
  g_signal_connect(confirmButton,"clicked",G_CALLBACK(onDeleteConfirm),NULL);
  cancelPopup = gtk_button_new_with_label("Cancel");
  cssAddLoadCSS(provider,"css/header.css",cancelPopup,"exitButton");
  gtk_widget_set_size_request(cancelPopup, 125,50);
  gtk_widget_set_hexpand(cancelPopup, TRUE);
  gtk_widget_set_vexpand(cancelPopup, TRUE);
  g_signal_connect(cancelPopup,"clicked",G_CALLBACK(cancelClicked),NULL);

  gtk_grid_attach(GTK_GRID(pGrid),confirmLabel,0,0,3,1);
  gtk_grid_attach(GTK_GRID(pGrid),confirmButton,1,1,1,1);
  gtk_grid_attach(GTK_GRID(pGrid),cancelPopup,2,1,1,1);

  confirmWindow = gtk_window_new();
  gtk_widget_set_size_request(confirmWindow, 250, 150);
  gtk_window_set_resizable(GTK_WINDOW(confirmWindow), FALSE);
  gtk_window_set_decorated(GTK_WINDOW(confirmWindow), FALSE);
  gtk_window_set_transient_for(GTK_WINDOW(confirmWindow), GTK_WINDOW(deleteWindow));
  gtk_window_set_modal(GTK_WINDOW(confirmWindow), TRUE);

  gtk_window_set_child(GTK_WINDOW(confirmWindow),pGrid);

  gtk_widget_set_visible(confirmWindow, FALSE);

  

}

void initDeletePopup(GtkWindow *window,GtkApplication *app){

  if(deleteWindow == NULL){
    deleteWindow = gtk_window_new();
    gtk_widget_set_size_request(deleteWindow,470,465);
    gtk_window_set_resizable(GTK_WINDOW(deleteWindow),FALSE);
    gtk_window_set_application(GTK_WINDOW(deleteWindow),app);
    gtk_window_set_decorated(GTK_WINDOW(deleteWindow),FALSE);
    gtk_window_set_transient_for(GTK_WINDOW(deleteWindow),window);
    gtk_window_set_modal(GTK_WINDOW(deleteWindow),TRUE);
    g_object_ref_sink(deleteWindow);
    gtk_widget_set_visible(deleteWindow,FALSE);
    setDeleteWindow();
    initAlertPopup();
    g_print("\nDelete Popup Successfuly init.");
  }else{
    g_print("\nDelete Popup isn't NULL.");
  }

}
