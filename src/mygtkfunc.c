#include "../headers/mygtkfunc.h"
#include "../headers/popupmanager.h"
#include "../headers/deletebook.h"
#include "../headers/editBook.h"

//extern area
GtkCssProvider *provider = NULL;
struct data gData;

void initCSS(){
	provider = gtk_css_provider_new();
	gtk_style_context_add_provider_for_display(
	gdk_display_get_default(),
	GTK_STYLE_PROVIDER(provider),
	GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
	);
  g_object_ref_sink(provider);
}

void cssAddLoadCSS(GtkCssProvider *provider,char *path,GtkWidget *widget,char *class){
	gtk_widget_add_css_class(widget,class);
	gtk_css_provider_load_from_path(provider,path);
}

void showPopupAddWindow(GtkWidget *button,gpointer user_data){
	
  showPopupWindow();
	
}

void showPopupRemoveWindow(GtkWidget *button,gpointer user_data){
	showPopupDelete();
}


void showPopupEditWindow(GtkWidget *button,gpointer user_data){
	showPopupEdit();
}
