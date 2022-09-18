#include "gtk.h"

#include <cairo.h>
#include <gtk/gtk.h>
#include <string.h>
#include <time.h>

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
  sprintf(str, "%.2lf", d);
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
  GtkContainer *graph_box =
      (GtkContainer *)gtk_widget_get_parent((GtkWidget *)widget);
  const gchar *name = gtk_widget_get_name((GtkWidget *)graph_box);
  if (strcmp(name, "graph_box") == 0)
    gtk_container_foreach(graph_box, on_set_graph_size, data);
  else
    assert(0);
}

/**
 * @brief Get the graph size from "grap_size box" fields
 * fills data->clip_x1 etc. dimensions of graph in user coordinates
 * @param widget - any "graph_box" child widget
 * @param data calc_data structure pointer to fill with coordinates
 */
extern void get_graph_size(GtkWidget *widget, gpointer data) {
  GtkContainer *graph_box =
      (GtkContainer *)gtk_widget_get_parent((GtkWidget *)widget);
  const gchar *name = gtk_widget_get_name((GtkWidget *)graph_box);
  if (strcmp(name, "graph_box") == 0)
    gtk_container_foreach(graph_box, on_get_graph_size, data);
  else
    assert(0);
}

void draw_grid_new(GtkWidget *widget, cairo_t *cr, gpointer data, int width,
                   int height) {
  cairo_save(cr);
  calc_data *d = data;

  double dx, dy;

  dx = fabs((d->clip_x2) - (d->clip_x1));
  dy = fabs((d->clip_y2) - (d->clip_y1));
  cairo_set_line_width(cr, 0.5);

  int x = 0;
  cairo_font_extents_t fe;
  cairo_text_extents_t te;
  cairo_font_extents(cr, &fe);
  for (double i = d->clip_x1; i <= d->clip_x2; i += dx / 10, x += width / 10) {
    cairo_set_source_rgb(cr, 0, 0, 0);
    if (x != 0) {
      char grid[10];
      sprintf(grid, "%.1f", i);
      cairo_text_extents(cr, grid, &te);
      cairo_move_to(cr, x + 5, height - 5);
      cairo_show_text(cr, grid);
      if (fabs(i) <= EPS) {
        cairo_set_source_rgba(cr, 0, 0, 0, 1);
        cairo_move_to(cr, x, height);
        cairo_line_to(cr, x, 0);
        cairo_stroke(cr);
      } else {
        cairo_set_source_rgba(cr, .5, 0.5, 0.5, 0.5);
        cairo_move_to(cr, x, height);
        cairo_line_to(cr, x, 0);
        cairo_stroke(cr);
      }
    } else {
      cairo_move_to(cr, x, height);
      cairo_line_to(cr, x, 0);
    }
  }
  int y = height;
  for (double i = d->clip_y1; i <= d->clip_y2; i += dy / 10, y -= height / 10) {
    cairo_set_source_rgb(cr, 0, 0, 0);
    if (y != height) {
      char grid[10];
      sprintf(grid, "%.1f", i);
      cairo_text_extents(cr, grid, &te);
      cairo_move_to(cr, 10, y - 5 - fe.descent + fe.height / 2);
      cairo_show_text(cr, grid);
      if (fabs(i) <= EPS) {
        cairo_set_source_rgba(cr, 0, 0, 0, 1);
        cairo_move_to(cr, 0, y);
        cairo_line_to(cr, width, y);
        cairo_stroke(cr);
      } else {
        cairo_set_source_rgba(cr, .5, 0.5, 0.5, 0.5);
        cairo_move_to(cr, 0, y);
        cairo_line_to(cr, width, y);
        cairo_stroke(cr);
      }
    } else {
      cairo_move_to(cr, 0, y);
      cairo_line_to(cr, width, y);
    }
  }
  cairo_stroke(cr);
  cairo_restore(cr);
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
  /* Draws x and y axis */
  draw_grid_new(widget, cr, &d, da.width, da.height);
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
  /* Link each data point */
  int good = 0, draw = 0;
  for (x = d.clip_x1; x < d.clip_x2; x += dx) {
    double y = calc(expr, x, &good);
    if (!good) break;
    if (draw && isfinite(y))
      cairo_line_to(cr, x, y);
    else
      cairo_move_to(cr, x, y);
    if (isfinite(y))
      draw = 1;
    else
      draw = 0;
  }

  /* Draw the curve */
  cairo_set_source_rgb(cr, 1, 0, 0);
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
  d->amount = 0;
  d->duration = 0;
  d->pay_period = 0;
  d->rate = 0;
  d->tax_rate = 0;
  d->tax = 0;
  d->monthly_payment = 0;
  d->monthly_payment_min = 0;
  d->overpayment = 0;
  d->interest = 0;
  d->total_payment = 0;
  d->type = 0;
  d->round = 0;
  d->int_cap = 0;
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

extern void set_credit_result(GtkWidget *widget, gpointer data) {
  calc_data *d = data;
  const gchar *name = gtk_widget_get_name(widget);
  char buf[MAXSTR];
  int prec = 2;

  if (d->round) prec = 0;
  if (strcmp(name, "monthly_payment_label") == 0) {
    if (d->type == ANNUITET) {
      if (d->round && d->monthly_payment < 1) {
        sprintf(buf, "%s", "Incorrect input data");
        d->error = 1;
        strcpy(d->error_message, buf);
      } else {
        sprintf(buf, "%.*lf RUB", prec, d->monthly_payment);
      }
    } else {
      sprintf(buf, "%.*lf...%.*lf RUB", prec, d->monthly_payment, prec,
              d->monthly_payment_min);
    }
    gtk_label_set_text(GTK_LABEL(widget), (const gchar *)buf);
  }
  if (strcmp(name, "overpayment_label") == 0) {
    sprintf(buf, "%.*lf RUB", prec, d->overpayment);
    gtk_label_set_text(GTK_LABEL(widget), (const gchar *)buf);
  }
  if (strcmp(name, "total_payment_label") == 0) {
    sprintf(buf, "%.*lf RUB", prec, d->total_payment);
    gtk_label_set_text(GTK_LABEL(widget), (const gchar *)buf);
  }
  if (strcmp(name, "status_label") == 0) {
    if (d->error == 1) {
      sprintf(buf, "%.100s\nreset to defaults", d->error_message);
    } else if (d->error == 2) {
      sprintf(buf, "%.100s", d->error_message);
    } else {
      sprintf(buf, "%s", "Sucsess!");
    }
    gtk_label_set_text(GTK_LABEL(widget), (const gchar *)buf);
  }
}

extern void set_deposit_result(GtkWidget *widget, gpointer data) {
  calc_data *d = data;
  const gchar *name = gtk_widget_get_name(widget);
  char buf[MAXSTR];
  int prec = 2;

  if (d->round) prec = 0;
  if (strcmp(name, "dep_interest_label") == 0) {
    sprintf(buf, "%.*lf RUB", prec, d->interest);
    gtk_label_set_text(GTK_LABEL(widget), (const gchar *)buf);
  }
  if (strcmp(name, "dep_tax_label") == 0) {
    sprintf(buf, "%.*lf RUB", prec, d->tax);
    gtk_label_set_text(GTK_LABEL(widget), (const gchar *)buf);
  }
  if (strcmp(name, "total_deposit_label") == 0) {
    sprintf(buf, "%.*lf RUB", prec, d->total_payment);
    gtk_label_set_text(GTK_LABEL(widget), (const gchar *)buf);
  }
  if (strcmp(name, "dep_status_label") == 0) {
    if (d->error == 1) {
      sprintf(buf, "%.100s\nreset to defaults", d->error_message);
    } else if (d->error == 2) {
      sprintf(buf, "%.100s", d->error_message);
    } else {
      sprintf(buf, "%s", "Sucsess!");
    }
    gtk_label_set_text(GTK_LABEL(widget), (const gchar *)buf);
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

extern void get_credit_calc_data(GtkWidget *widget, gpointer data) {
  const gchar *name = gtk_widget_get_name(widget);
  calc_data *d = data;
  const gchar *active_id;

  if (strcmp(name, "amount_entry") == 0) {
    const char *src_str_ptr = gtk_entry_get_text((GtkEntry *)widget);
    if (sscanf(src_str_ptr, "%lf", &(d->amount)) != 1 || d->amount <= 0 ||
        d->amount > 10000000000) {
      d->amount = DEFAULT_AMOUNT;
      d->error = 1;
      gtk_entry_set_double((GtkEntry *)widget, d->amount);
      strcpy(d->error_message,
             "Error reading amount,\nplease enter values in range "
             "0-10000000000\n");
    }
  }
  if (strcmp(name, "duration_combo") == 0) {
    active_id = gtk_combo_box_get_active_id((GtkComboBox *)widget);
    if (active_id != NULL) {
      sscanf(gtk_combo_box_get_active_id((GtkComboBox *)widget), "%d",
             &(d->duration));
    } else {
      d->duration = DEFAULT_DURATION;
      d->error = 1;
      strcpy(d->error_message, "Error reading term\nPlease select one\n");
    }
  }
  if (strcmp(name, "type_combo") == 0) {
    active_id = gtk_combo_box_get_active_id((GtkComboBox *)widget);
    if (active_id != NULL) {
      sscanf(active_id, "%d", &(d->type));
    } else {
      d->type = ANNUITET;
      d->error = 1;
      strcpy(d->error_message, "Error reading type\nPlease select one\n");
    }
  }
  if (strcmp(name, "round_checkbutton") == 0) {
    d->round = gtk_toggle_button_get_active((GtkToggleButton *)widget);
  }
  if (strcmp(name, "rate_entry") == 0) {
    const char *src_str_ptr = gtk_entry_get_text((GtkEntry *)widget);
    if (sscanf(src_str_ptr, "%lf", &(d->rate)) != 1 || d->rate <= 0.01 ||
        d->rate > 999) {
      d->rate = DEFAULT_RATE;
      d->error = 1;
      gtk_entry_set_double((GtkEntry *)widget, d->rate);
      strcpy(d->error_message,
             "Error reading % rate\nPlease enter values in range 0.01-999\n");
    }
  }
}

void get_combo_value(GtkComboBox *widget, int *value, int def, calc_data *d,
                     char *err_msg) {
  const gchar *active_id;

  active_id = gtk_combo_box_get_active_id((GtkComboBox *)widget);
  if (active_id != NULL) {
    sscanf(active_id, "%d", value);
  } else {
    d->duration = def;
    d->error = 1;
    strcpy(d->error_message, err_msg);
  }
}

extern void get_deposit_calc_data(GtkWidget *widget, gpointer data) {
  const gchar *name = gtk_widget_get_name(widget);
  calc_data *d = data;
  const gchar *active_id;

  if (strcmp(name, "dep_amount_entry") == 0) {
    const char *src_str_ptr = gtk_entry_get_text((GtkEntry *)widget);
    if (sscanf(src_str_ptr, "%lf", &(d->amount)) != 1 || d->amount <= 0 ||
        d->amount > 10000000000) {
      d->amount = DEFAULT_AMOUNT;
      d->error = 1;
      gtk_entry_set_double((GtkEntry *)widget, d->amount);
      strcpy(d->error_message,
             "Error reading amount,\nplease enter values in range "
             "0-10000000000\n");
    }
  }
  if (strcmp(name, "dep_duration_combo") == 0) {
    get_combo_value((GtkComboBox *)widget, &(d->duration), DEFAULT_DURATION, d,
                    "Error reading term\nPlease select one\n");
  }
  if (strcmp(name, "dep_pay_period_combo") == 0) {
    get_combo_value((GtkComboBox *)widget, &(d->pay_period), DEFAULT_PAY_PERIOD,
                    d, "Error reading pay period\nPlease select one\n");
  }
  if (strcmp(name, "dep_round_checkbutton") == 0) {
    d->round = gtk_toggle_button_get_active((GtkToggleButton *)widget);
  }
  if (strcmp(name, "dep_int_cap_checkbutton") == 0) {
    d->int_cap = gtk_toggle_button_get_active((GtkToggleButton *)widget);
  }
  if (strcmp(name, "dep_rate_entry") == 0) {
    const char *src_str_ptr = gtk_entry_get_text((GtkEntry *)widget);
    if (sscanf(src_str_ptr, "%lf", &(d->rate)) != 1 || d->rate <= 0.01 ||
        d->rate > 999) {
      d->rate = DEFAULT_RATE;
      d->error = 1;
      gtk_entry_set_double((GtkEntry *)widget, d->rate);
      strcpy(d->error_message,
             "Error reading % rate\nPlease enter values in range 0.01-999\n");
    }
  }
  if (strcmp(name, "dep_tax_rate_entry") == 0) {
    const char *src_str_ptr = gtk_entry_get_text((GtkEntry *)widget);
    if (sscanf(src_str_ptr, "%lf", &(d->tax_rate)) != 1 || d->tax_rate < 0.0 ||
        d->tax_rate > 100) {
      d->tax_rate = DEFAULT_RATE;
      d->error = 1;
      gtk_entry_set_double((GtkEntry *)widget, d->tax_rate);
      strcpy(d->error_message,
             "Error reading tax rate\nPlease enter values in range 0.01-100\n");
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
  gtk_widget_queue_draw((GtkWidget *)calc_main_box);
}

extern void credit_calc_button_clicked(GtkButton *button, gpointer data) {
  calc_data d;
  GtkContainer *result_grid = data;
  GtkContainer *source_grid =
      (GtkContainer *)gtk_widget_get_parent((GtkWidget *)button);

  init_calc_data(&d);
  gtk_container_foreach(source_grid, get_credit_calc_data, &d);
  char monthly_payment_expr[MAXSTR];
  if (d.type == ANNUITET) {
    sprintf(monthly_payment_expr,
            "%lf*(%lf/100/12*(%lf/100/12+1)^%d/((1+%lf/100/12)^%d-1))",
            d.amount, d.rate, d.rate, d.duration, d.rate, d.duration);
    int good = 0;
    d.monthly_payment = round(calc(monthly_payment_expr, 0, &good) * 100) / 100;
    if (d.round && d.monthly_payment < 1) {
      d.error = 2;
      strcpy(d.error_message, "Incorrect input data - can't calculate");
    }
    if (d.round) d.monthly_payment = round(d.monthly_payment);
    d.overpayment = (d.monthly_payment) * d.duration - d.amount;
    d.total_payment = (d.monthly_payment) * d.duration;
  } else {  // DIFFERENTIATED
    double *mp = malloc(sizeof(*mp) * d.duration);
    sprintf(monthly_payment_expr, "%lf/%d+(%lf-(%lf/%d)*x)*(%lf/100/12)",
            d.amount, d.duration, d.amount, d.amount, d.duration, d.rate);
    int good;
    for (int m = 0; m < d.duration; m++) {
      mp[m] = calc(monthly_payment_expr, (double)m, &good);
      assert(good == 1);
      d.total_payment += mp[m];
    }
    d.monthly_payment = mp[0];
    d.monthly_payment_min = mp[d.duration - 1];
    d.overpayment = d.total_payment - d.amount;
    free(mp);
  }
  gtk_container_foreach(result_grid, set_credit_result, &d);
  gtk_widget_queue_draw((GtkWidget *)result_grid);
  if (d.error) gtk_widget_queue_draw((GtkWidget *)source_grid);
}

/**
 * @brief Get the number of days in the 'period' months from today
 *
 * @param period - number of months to add to current date
 * @return int number of days in 'period' moths from current date
 */
int get_days_in_period(int period) {
  int result = 0;
  time_t current_time, future_time;
  /* Obtain current time. */
  current_time = time(NULL);
  struct tm current_date = *localtime(&current_time);
  struct tm future_date = current_date;
  current_date.tm_year =
      current_date.tm_year + (current_date.tm_mon + period) / 12;
  current_date.tm_mon = (current_date.tm_mon + period) % 12;
  future_time = mktime(&current_date);
  result = round(difftime(future_time, current_time) / 86400);
  return result;
}

extern void deposit_calc_button_clicked(GtkButton *button, gpointer data) {
  calc_data d;
  GtkContainer *result_grid = data;
  GtkContainer *source_grid =
      (GtkContainer *)gtk_widget_get_parent((GtkWidget *)button);

  init_calc_data(&d);
  gtk_container_foreach(source_grid, get_deposit_calc_data, &d);
  char interest_expr[MAXSTR];
  if (d.int_cap == FALSE) {  // simple interest
    sprintf(interest_expr, "%lf*%lf*(%d/365)/100", d.amount, d.rate,
            get_days_in_period(d.duration));
    int good = 0;
    d.interest = round(calc(interest_expr, 0, &good) * 100) / 100;
    if (d.round && d.interest < 1) {
      d.error = 2;
      strcpy(d.error_message, "Incorrect input data - can't calculate");
    }
    if (d.round) d.interest = round(d.interest);
    d.tax = (d.interest) * (d.tax_rate / 100);
    d.total_payment = (d.interest) + d.amount - d.tax;
  } else {  // Complex interest
    int t, k;
    switch (d.pay_period) {
      case 1:
        t = get_days_in_period(d.duration);
        k = 365;
        break;
      case 30:
        t = d.duration;
        k = 12;
      case 7:
        t = round(get_days_in_period(d.duration) / 7. + 0.5);
        k = 52;
        break;

      default:
        break;
    }
    sprintf(interest_expr, "%lf*((1.+%lf/100./%d)^%d)", d.amount, d.rate, k, t);
    int good = 1;
    d.total_payment = d.amount * pow(1. + (d.rate / 100.) / k, (double)t);
    // d.total_payment = calc(interest_expr, 0, &good);
    assert(good = 1);
    d.interest = d.total_payment - d.amount;
    d.tax = (d.interest) * (d.tax_rate / 100);
    d.total_payment -= d.tax;
  }
  gtk_container_foreach(result_grid, set_deposit_result, &d);
  gtk_widget_queue_draw((GtkWidget *)result_grid);
  if (d.error) gtk_widget_queue_draw((GtkWidget *)source_grid);
}

int check_graph_sizes(calc_data *d) {
  int res = 1;
  if (d->clip_x1 < VERY_MIN_X || d->clip_x1 > d->clip_x2) res = 0;
  if (d->clip_x2 > VERY_MAX_X || d->clip_x2 < d->clip_x1) res = 0;
  if (d->clip_y1 < VERY_MIN_Y || d->clip_y1 > d->clip_y2) res = 0;
  if (d->clip_y2 > VERY_MAX_Y || d->clip_y2 < d->clip_y1) res = 0;
  if (fabs(d->clip_y2 - d->clip_y1) < 1) res = 0;
  if (fabs(d->clip_x2 - d->clip_x1) < 1) res = 0;
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

extern void graph_button_clicked(GtkButton *button, gpointer data) {
  // calc_data d;
  GtkWidget *graph_box = data;
  if (gtk_toggle_button_get_active((GtkToggleButton *)button)) {
    gtk_widget_hide(graph_box);
  } else {
    gtk_widget_show_all(graph_box);
  }
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
  if (gtk_builder_add_from_file(builder, "newversion-v7.ui", &error) == 0) {
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

  // освобождение памяти
  g_object_unref(G_OBJECT(builder));

  //Пошла программа
  gtk_main();

  // освобождение памяти
  gtk_widget_destroy(window);

  return 0;
}