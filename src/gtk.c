#include "gtk.h"

#include <cairo.h>
#include <gtk/gtk.h>
#include <string.h>

char *copy_expr_from_label(char *str, const char *label) {
  const char *p = strstr(label, " = ");
  if (p != NULL)
    strncpy(str, label, p - label);
  else
    strcpy(str, label);
  return str;
}

void gtk_entry_set_double(GtkEntry *entry, double d) {
  char str[MAXSTR] = {0};
  sprintf(str, "%lf", d);
  gtk_entry_set_text(GTK_ENTRY(entry), str);
}
int gtk_entry_get_double(GtkEntry *entry, double *d) {
  const gchar *p;
  int res = 1;
  p = gtk_entry_get_text(GTK_ENTRY(entry));
  if (sscanf(p, "%lf", d) != 1) {
    *d = 0;
    res = 0;
  }
  return res;
}

extern void on_set_graph_size(GtkWidget *widget, gpointer data) {
  calc_data *d = data;
  const gchar *name = gtk_widget_get_name(widget);

  if (strcmp(name, "graph_size_box") == 0) {
    gtk_container_foreach(GTK_CONTAINER(widget), on_set_graph_size, data);
  }
  if (strcmp(name, "min_x") == 0) {
    gtk_entry_set_double(GTK_ENTRY(widget), d->clip_x1);
  }
  if (strcmp(name, "max_x") == 0) {
    gtk_entry_set_double(GTK_ENTRY(widget), d->clip_x2);
  }
  if (strcmp(name, "min_y") == 0) {
    gtk_entry_set_double(GTK_ENTRY(widget), d->clip_y1);
  }
  if (strcmp(name, "max_y") == 0) {
    gtk_entry_set_double(GTK_ENTRY(widget), d->clip_y2);
  }
}
extern void on_get_graph_size(GtkWidget *widget, gpointer data) {
  calc_data *d = data;
  const gchar *name = gtk_widget_get_name(widget);

  if (strcmp(name, "graph_size_box") == 0) {
    gtk_container_foreach(GTK_CONTAINER(widget), on_get_graph_size, data);
  }
  if (strcmp(name, "min_x") == 0) {
    if (gtk_entry_get_double(GTK_ENTRY(widget), &d->clip_x1) == 0) {
      d->error = 1;
      strcpy(d->error_message, "Can't read min x");
    }
  }
  if (strcmp(name, "max_x") == 0) {
    if (gtk_entry_get_double(GTK_ENTRY(widget), &d->clip_x2) == 0) {
      d->error = 1;
      strcpy(d->error_message, "Can't read max x");
    }
  }
  if (strcmp(name, "min_y") == 0) {
    if (gtk_entry_get_double(GTK_ENTRY(widget), &d->clip_y1) == 0) {
      d->error = 1;
      strcpy(d->error_message, "Can't read min y");
    }
  }
  if (strcmp(name, "max_y") == 0) {
    if (gtk_entry_get_double(GTK_ENTRY(widget), &d->clip_y2) == 0) {
      d->error = 1;
      strcpy(d->error_message, "Can't read max y");
    }
  }
}

extern void set_graph_size(GtkWidget *widget, gpointer data) {
  GtkContainer *calc_screen =
      (GtkContainer *)gtk_widget_get_parent((GtkWidget *)widget);
  gtk_container_foreach(calc_screen, on_set_graph_size, data);
}

/**
 * @brief Get the graph size from "grap_size box" fields
 * fills data->clip_x1 etc. dimensions of graph in user coordinates
 * @param widget - any "cacl_screen" child widget
 * @param data calc_data structure pointer to fill with coordinates
 */
extern void get_graph_size(GtkWidget *widget, gpointer data) {
  GtkContainer *calc_screen =
      (GtkContainer *)gtk_widget_get_parent((GtkWidget *)widget);
  gtk_container_foreach(calc_screen, on_get_graph_size, data);
}

void draw_grid(GtkWidget *widget, cairo_t *cr, gpointer data, int width,
               int height) {
  calc_data *d = data;
  /* Draws x and y axis */
  // double dx = 10, dy = 10;
  cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
  cairo_move_to(cr, d->clip_x1, 0.0);
  cairo_line_to(cr, d->clip_x2, 0.0);
  cairo_move_to(cr, 0.0, d->clip_y1);
  cairo_line_to(cr, 0.0, d->clip_y2);

  // cairo_device_to_user_distance(cr, &dx, &dy);

  //  cairo_clip_extents (cr, &clip_x1, &clip_y1, &clip_x2, &clip_y2);
  // cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
  // cairo_move_to(cr, d->clip_x1 + dx, d->clip_y1);
  // cairo_line_to(cr, d->clip_x1 + dx, d->clip_y2);
  // }

  // if (d->clip_y1 < 0 && d->clip_y2 > 0) {
  // cairo_move_to(cr, d->clip_x1, d->clip_y1 - dy);
  // cairo_line_to(cr, d->clip_x2, d->clip_y1 - dy);
  // } else {
  // cairo_move_to(cr, 50., 0.);
  // cairo_line_to(cr, 50., 100.);
  // cairo_restore(cr);

  // }
  cairo_stroke(cr);

  /*for (double ya = d->clip_y1; ya < d->clip_y2;
       ya += fabs(d->clip_y2 - d->clip_y1) / 4) {
    // преобразовывем значение координаты риски в строку
    char buf[MAXSTR];
    sprintf(buf, "%.1lf", ya);

    // рисуем текст метки в нужной точке

    cairo_move_to(cr, d->clip_x1, ya);
    cairo_line_to(cr, d->clip_x1 +, ya);

    // cairo_show_text(cr, buf);

    // задаем зеленый цвет
    /*
        cairo_set_source_rgb(cr, 0, 0.5, 0);

        // рисуем линии сетки

        cairo_move_to(cr, 47, ya - 40);

        cairo_line_to(cr, 600, ya - 40);

        cairo_stroke(cr);

        ya -= 40;
  }*/
}

extern gboolean on_draw(GtkWidget *widget, cairo_t *cr, gpointer data) {
  /* Prepare formula */
  GtkLabel *history_label = data;
  char expr[MAXSTR] = {0};
  copy_expr_from_label(expr, gtk_label_get_text(history_label));
  GdkRectangle da;            /* GtkDrawingArea size */
  gdouble dx = 1.0, dy = 1.0; /* Pixels between each point */
  calc_data d;
  init_calc_data(&d);
  gdouble x;
  gdouble zx, zy;
  GdkWindow *window = gtk_widget_get_window(widget);

  /* Determine GtkDrawingArea dimensions */
  gdk_window_get_geometry(window, &da.x, &da.y, &da.width, &da.height);
  /* Draw on a white background */
  cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
  cairo_paint(cr);
  /* read function domain and codomain */
  get_graph_size(widget, &d);

  /* compute scale */
  zx = da.width / fabs((d.clip_x2) - (d.clip_x1));
  zy = da.height / fabs((d.clip_y2) - (d.clip_y1));
  /* Change the transformation matrix */
  cairo_translate(
      cr, zx * (fabs((d.clip_x2) - (d.clip_x1)) - fmax(d.clip_x2, d.clip_x1)),
      zy * fmax(d.clip_y2, d.clip_y1)); /* Set 0.0 point */
  cairo_scale(cr, zx, -zy);

  /* Determine the data points to calculate (ie. those in the clipping zone */
  cairo_device_to_user_distance(cr, &dx, &dy);
  cairo_set_line_width(cr, dx);

  /* Draws x and y axis */
  // cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
  // cairo_move_to(cr, d.clip_x1, 0.0);
  // cairo_line_to(cr, d.clip_x2, 0.0);
  // cairo_move_to(cr, 0.0, d.clip_y1);
  // cairo_line_to(cr, 0.0, d.clip_y2);
  draw_grid(widget, cr, &d, da.width, da.height);
  // cairo_stroke(cr);
  /* Link each data point */
  int good = 0, draw = 0;
  for (x = d.clip_x1; x < d.clip_x2; x += dx) {
    double y = calc(expr, x, &good);
    if (good && draw && isfinite(y))
      cairo_line_to(cr, x, y);
    else
      cairo_move_to(cr, x, y);
    if (isfinite(y))
      draw = 1;
    else
      draw = 0;
  }

  /* Draw the curve */
  cairo_set_source_rgba(cr, 1, 0.2, 0.2, 0.6);
  cairo_stroke(cr);

  return FALSE;
}

extern void func_button_clicked(GtkButton *button, gpointer data) {
  GtkEntry *src_str_entry = data;
  int cur_pos = gtk_editable_get_position((GtkEditable *)src_str_entry);
  const char *func_name = gtk_button_get_label(button);
  const char *src_str = gtk_entry_get_text(src_str_entry);
  char new_str[MAXSTR] = {0};
  int new_pos = 0;
  if (is_alpha(*func_name) && *func_name != 'X' && *func_name != 'm' &&
      *func_name != '^') {
    if (gtk_editable_get_selection_bounds((GtkEditable *)src_str_entry,
                                          &new_pos, &cur_pos) != FALSE) {
      sprintf(new_str, "%.*s%s(%.*s)%s", new_pos, src_str, func_name,
              cur_pos - new_pos, src_str + new_pos, src_str + cur_pos);
      new_pos += 2;  // 2 Brackets around selection
    } else {         // If no selected text
      sprintf(new_str, "%.*s%s%s%s", cur_pos, src_str, func_name, "(",
              src_str + cur_pos);
      new_pos += 1;  // Bracket behind func name
    }
  } else if (*func_name == 'm') {
    gtk_editable_delete_selection((GtkEditable *)src_str_entry);
    cur_pos = gtk_editable_get_position((GtkEditable *)src_str_entry);
    sprintf(new_str, "%.*s %s %s", cur_pos, src_str, func_name,
            src_str + cur_pos);
    new_pos += 2;  // 2 spaces around func name
  } else if (*func_name == '(' || *func_name == ')') {
    if (gtk_editable_get_selection_bounds((GtkEditable *)src_str_entry,
                                          &new_pos, &cur_pos) != FALSE) {
      sprintf(new_str, "%.*s(%.*s)%s", new_pos, src_str, cur_pos - new_pos,
              src_str + new_pos, src_str + cur_pos);
      new_pos += 2;  // 2 Bracets around selection
    } else {
      sprintf(new_str, "%.*s%s%s", cur_pos, src_str, func_name,
              src_str + cur_pos);
    }
  } else {
    gtk_editable_delete_selection((GtkEditable *)src_str_entry);
    cur_pos = gtk_editable_get_position((GtkEditable *)src_str_entry);
    sprintf(new_str, "%.*s%s%s", cur_pos, src_str, func_name,
            src_str + cur_pos);
  }
  new_pos += cur_pos + strlen(func_name);
  gtk_entry_set_text(src_str_entry, new_str);
  gtk_editable_set_position((GtkEditable *)src_str_entry, new_pos);
}

extern void get_history(GtkWidget *widget, gpointer data) {
  calc_data *d = data;
  const gchar *name = gtk_widget_get_name(widget);

  if (strcmp(name, "last_expr_label") == 0) {
    copy_expr_from_label(d->str, gtk_label_get_text(GTK_LABEL(widget)));
  }
}

extern void historybutton_clicked(GtkButton *button, gpointer data) {
  GtkEntry *src_str_entry = data;
  calc_data d;

  GtkContainer *history_box =
      (GtkContainer *)gtk_widget_get_parent((GtkWidget *)button);

  init_calc_data(&d);
  gtk_container_foreach(history_box, get_history, &d);
  if (d.error == 0) {
    gtk_entry_set_text(src_str_entry, d.str);
    gtk_editable_set_position((GtkEditable *)src_str_entry, -1);
  }
}

extern void backspace_clicked(GtkButton *button, gpointer data) {
  GtkEntry *src_str_entry = data;
  const char *src_str = gtk_entry_get_text(src_str_entry);
  int cur_pos;
  int new_pos;
  if (gtk_editable_get_selection_bounds((GtkEditable *)src_str_entry, &new_pos,
                                        &cur_pos) == FALSE) {
    cur_pos = gtk_editable_get_position((GtkEditable *)src_str_entry);
    new_pos = cur_pos - 1;
  }
  if (new_pos >= 0) {
    char new_str[MAXSTR] = {0};
    sprintf(new_str, "%.*s%s", new_pos, src_str, src_str + cur_pos);
    gtk_entry_set_text(src_str_entry, new_str);
    gtk_editable_set_position((GtkEditable *)src_str_entry, new_pos);
  }
}

void init_calc_data(calc_data *d) {
  d->iteration = 0;
  memset(d->str, 0, sizeof(d->str));
  d->x = 0;
  d->error = 0;
  memset(d->error_message, 0, sizeof(d->error_message));
  d->clip_x1 = 0;
  d->clip_x2 = 0;
  d->clip_y1 = 0;
  d->clip_y2 = 0;
}

extern void calculate(GtkWidget *widget, gpointer data) {
  calc_data *d = data;

  const char *src_str_ptr = gtk_entry_get_text((GtkEntry *)widget);
  strcpy(d->str, src_str_ptr);  // Save formula
  if (strlen(d->str)) {
    int good = 1;
    struct expr *infix = expr_from_string(d->str, &good);
    char res_str[MAXSTR];
    if (good) {
      double res;
      struct expr *postfix = expr_shunt(infix);
      res = rpn_reduce(postfix, d->x);
      expr_destroy(&postfix);
      sprintf(res_str, "%f", res);
      sprintf(d->str, "%s = %f", src_str_ptr, res);
    } else {
      d->error = 1;
      strcpy(d->error_message, "Expression error");
      sprintf(res_str, "%.300s = %.100s", d->str, d->error_message);
      strcpy(d->str, res_str);
    }
    gtk_entry_set_text((GtkEntry *)widget, res_str);
    gtk_editable_select_region((GtkEditable *)widget, 0, -1);
    // gtk_editable_set_position((GtkEditable *)widget, -1);

    expr_destroy(&infix);
  }
}

extern void on_calculate(GtkWidget *widget, gpointer data) {
  calc_data *d = data;
  const gchar *name = gtk_widget_get_name(widget);

  if (d->iteration == 0 && strcmp(name, "src_str_entry") == 0) {
    calculate(widget, data);
  }
  if (d->iteration == 1 && strcmp(name, "history_box") == 0) {
    gtk_container_foreach(GTK_CONTAINER(widget), on_calculate, data);
  }
  if (d->iteration == 1 && strcmp(name, "last_expr_label") == 0) {
    gtk_label_set_text(GTK_LABEL(widget), (const gchar *)d->str);
  }
}

extern int x_focus_out(GtkWidget *widget, GdkEventFocus event, gpointer data) {
  const char *x_value_str = gtk_entry_get_text((GtkEntry *)widget);
  const char *p = x_value_str;
  int len = 0;
  while (*p && is_space(*p)) {
    p++;
    len++;
  }
  if ((*p == '-')) {
    p++;
    len++;
  }
  while (*p && is_digit(*p)) {
    p++;
    len++;
  }
  if (len != strlen(x_value_str)) {
    gtk_entry_set_text((GtkEntry *)widget, "");
  }
  return FALSE;
}

extern void get_x_value(GtkWidget *widget, gpointer data) {
  const gchar *name = gtk_widget_get_name(widget);
  calc_data *d = data;

  if (strcmp(name, "X_value_entry") == 0) {
    d->x = 0;
    const char *src_str_ptr = gtk_entry_get_text((GtkEntry *)widget);
    if (sscanf(src_str_ptr, "%lf", &(d->x)) != 1) {
      d->x = 0;
      d->error = 1;
      strcpy(d->error_message, "Error reading X value");
    }
  }
}

extern void calc_button_clicked(GtkButton *button, gpointer data) {
  calc_data d;
  GtkContainer *calc_main_box = data;
  GtkContainer *keyboard_grid =
      (GtkContainer *)gtk_widget_get_parent((GtkWidget *)button);

  init_calc_data(&d);
  gtk_container_foreach(keyboard_grid, get_x_value, &d);
  gtk_container_foreach(calc_main_box, on_calculate, &d);
  d.iteration = 1;
  gtk_container_foreach(calc_main_box, on_calculate, &d);
  gtk_widget_queue_draw((GtkWidget *)data);
}

int check_graph_sizes(calc_data *d) {
  int res = 1;
  if (d->clip_x1 < VERY_MIN_X || d->clip_x1 > d->clip_x2) res = 0;
  if (d->clip_x2 > VERY_MAX_X || d->clip_x2 < d->clip_x1) res = 0;
  if (d->clip_y1 < VERY_MIN_Y || d->clip_y1 > d->clip_y2) res = 0;
  if (d->clip_y2 > VERY_MAX_Y || d->clip_y2 < d->clip_y1) res = 0;
  return res;
}

extern void apply_button_clicked(GtkButton *button, gpointer data) {
  calc_data d;
  init_calc_data(&d);
  GtkWidget *graph_area = data;
  get_graph_size((GtkWidget *)graph_area, &d);
  if (d.error != 0 || check_graph_sizes(&d) != 1) {
    d.clip_x1 = MINX;
    d.clip_x2 = MAXX;
    d.clip_y1 = MINY;
    d.clip_y2 = MAXY;
  }

  set_graph_size((GtkWidget *)graph_area, &d);
  gtk_widget_queue_draw((GtkWidget *)graph_area);
}

extern void AC_button_clicked(GtkButton *button, gpointer data) {
  GtkEntry *src_str_entry = data;
  char new_str[MAXSTR] = {0};
  gtk_entry_set_text(src_str_entry, new_str);
}

extern void exit_button_clicked(GtkWidget *widget, gpointer data) {
  gtk_main_quit();
}

int main(int argc, char *argv[]) {
  GtkBuilder *builder;
  GError *error = NULL;

  gtk_init(&argc, &argv);

  /* Construct a GtkBuilder instance and load our UI description */
  builder = gtk_builder_new();
  if (gtk_builder_add_from_file(builder, "newversion-v5.ui", &error) == 0) {
    g_printerr("Error loading file: %s\n", error->message);
    g_clear_error(&error);
    return 1;
  }

  //Теперь получаем виджет из Builder
  // В данном случае ищем виджет окна
  GtkWidget *window =
      GTK_WIDGET(gtk_builder_get_object(builder, "calc_window"));

  //Подключаем сигналы)
  gtk_builder_connect_signals(builder, NULL);

  // Разрешаем отображение
  gtk_widget_show_all(window);

  //Пошла программа
  gtk_main();

  return 0;
}