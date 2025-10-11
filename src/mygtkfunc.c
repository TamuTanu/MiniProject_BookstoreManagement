#include "../headers/mygtkfunc.h"
#include "../headers/popupmanager.h"

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
}

void cssAddLoadCSS(GtkCssProvider *provider,char *path,GtkWidget *widget,char *class){
	gtk_widget_add_css_class(widget,class);
	gtk_css_provider_load_from_path(provider,path);
}

void showPopupAddWindow(GtkWidget *button,gpointer user_data){
	
  showPopupWindow();
	
}

void showPopupRemoveWindow(GtkWidget *button,gpointer user_data){
	g_print("2");
}


void showPopupEditWindow(GtkWidget *button,gpointer user_data){
	g_print("3");
}
