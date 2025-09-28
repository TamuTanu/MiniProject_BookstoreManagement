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
	
	struct data *gData = (struct data*) user_data;

	GtkWidget *popup = GTK_WIDGET(gData -> window);
	gtk_window_set_title(GTK_WINDOW(popup),"AddBook Window");
	gtk_widget_set_size_request(popup, 600,400);
	gtk_window_set_resizable(GTK_WINDOW(popup),FALSE);
	gtk_window_set_application(GTK_WINDOW(popup),gData -> app);	
		
	setWindow();

	gtk_window_present(GTK_WINDOW(popup));
	
}

void showPopupRemoveWindow(GtkWidget *button,gpointer user_data){
	g_print("2");
}


void showPopupEditWindow(GtkWidget *button,gpointer user_data){
	g_print("3");
}
