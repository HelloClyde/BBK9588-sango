#ifndef SANGO_UI_PAINT_H
#define SANGO_UI_PAINT_H

/* Nestable scope for a complete menu/table redraw. End before waiting for input. */
/* Apply selection inversion after ending the scope: it needs the native window. */
void sango_ui_paint_begin(void);
void sango_ui_paint_end(void);
int sango_ui_paint_active(void);
/* Legacy primitives must not flush the window while a modal is offscreen. */
void sango_ui_paint_guard(unsigned int enabled);
void sango_ui_paint_redraw(void);

#endif
