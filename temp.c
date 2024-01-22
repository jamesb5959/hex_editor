#include <gtk/gtk.h>

// Callback function to handle the destroy signal
void on_window_destroy(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Black Window GUI");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(on_window_destroy), NULL);

    // Set the background color to black
    GdkColor color;
    gdk_color_parse("#000000", &color);
    gtk_widget_modify_bg(window, GTK_STATE_NORMAL, &color);

    // Create a button with label "X"
    GtkWidget *button = gtk_button_new_with_label("X");
    
    // Connect the button's clicked signal to the destroy signal of the window
    g_signal_connect(button, "clicked", G_CALLBACK(on_window_destroy), NULL);
    
    // Add the button to the top right corner of the window
    gtk_button_set_alignment(GTK_BUTTON(button), 1, 0);
    gtk_container_add(GTK_CONTAINER(window), button);

    // Show all elements in the window
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}
