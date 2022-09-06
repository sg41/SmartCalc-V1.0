#include <gtk/gtk.h>

static void on_button_clicked(GtkWidget *widget, gpointer data) {
  g_print("Hello World\n");
}

int main(int argc, char *argv[]) {
  GtkBuilder *builder;
  GObject *window;
  GObject *button;
  GError *error = NULL;

  gtk_init(&argc, &argv);

  /* Construct a GtkBuilder instance and load our UI description */
  builder = gtk_builder_new();
  if (gtk_builder_add_from_file(builder, "newversion.ui", &error) == 0) {
    g_printerr("Error loading file: %s\n", error->message);
    g_clear_error(&error);
    return 1;
  }

  gtk_builder_connect_signals(builder, NULL);

  gtk_main();

  return 0;
}