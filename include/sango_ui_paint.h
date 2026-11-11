#ifndef SANGO_UI_PAINT_H
#define SANGO_UI_PAINT_H

/* Nestable scope for a complete menu/table redraw. End before waiting for input. */
/* Apply selection inversion after ending the scope: it needs the native window. */
void sango_ui_paint_begin(void);
void sango_ui_paint_end(void);

#endif
