#include <gtk/gtk.h>

#include "graph.h"
#include "rpr/expr.h"

extern void func_button_clicked(GtkButton *button, gpointer data) {
  GtkEntry *src_str_entry = data;
  const char *func_name = gtk_button_get_label(button);
  const char *src_str = gtk_entry_get_text(src_str_entry);
  char new_str[MAXSTR] = {0};
  if (is_alpha(*func_name) && *func_name != 'X' && *func_name != 'm') {
    sprintf(new_str, "%s%s%s", src_str, func_name, "(");
  } else if (*func_name == 'm') {
    sprintf(new_str, "%s %s ", src_str, func_name);
  } else {
    sprintf(new_str, "%s%s", src_str, func_name);
  }
  gtk_entry_set_text(src_str_entry, new_str);
}

extern void exit_button_clicked(GtkWidget *widget, gpointer data) {
  gtk_main_quit();
}

int main(int argc, char *argv[]) {
  GtkBuilder *builder;
  // GObject *window;
  GObject *button;
  GError *error = NULL;

  gtk_init(&argc, &argv);

  /* Construct a GtkBuilder instance and load our UI description */
  builder = gtk_builder_new();
  if (gtk_builder_add_from_file(builder, "newversion-v1.ui", &error) == 0) {
    g_printerr("Error loading file: %s\n", error->message);
    g_clear_error(&error);
    return 1;
  }

  //Теперь получаем виджет из Builder
  // Помните мы указывали ID? Вот по нему мы и ищем нужный
  // В данном случае ищем виджет окна
  GtkWidget *window =
      GTK_WIDGET(gtk_builder_get_object(builder, "calc_window"));

  //Таким же образом можно получить и другие виджеты
  // но нам они не понадобятся

  //Подключаем сигналы)
  gtk_builder_connect_signals(builder, NULL);

  // Разрешаем отображение
  gtk_widget_show_all(window);

  //Пошла программа
  gtk_main();

  return 0;
}