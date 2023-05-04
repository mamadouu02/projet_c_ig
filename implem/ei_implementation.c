/**
 * @file	ei_implementation.c
 *
 * @brief 	Private definitions.
 *
 */

#include <stdint.h>

#include "hw_interface.h"
#include "ei_types.h"
#include "ei_widget.h"



/**
 * \brief	Converts the red, green, blue and alpha components of a color into a 32 bits integer
 * 		than can be written directly in the memory returned by \ref hw_surface_get_buffer.
 * 		The surface parameter provides the channel order.
 *
 * @param	surface		The surface where to store this pixel, provides the channels order.
 * @param	color		The color to convert.
 *
 * @return 			The 32 bit integer corresponding to the color. The alpha component
 *				of the color is ignored in the case of surfaces that don't have an
 *				alpha channel.
 */
uint32_t ei_impl_map_rgba(ei_surface_t surface, ei_color_t color)
{
	int ir, ig, ib, ia;
	uint32_t color_32 = 0;
	hw_surface_get_channel_indices(surface, &ir, &ig, &ib, &ia);
	for (int i = 0; i < 4; i++) {
		if (ir == i) color_32 += color.red << 8*i;
		if (ig == i) color_32 += color.green << 8*i;
		if (ib == i) color_32 += color.blue << 8*i;
		if (ia == i) color_32 += color.alpha << 8*i;
	}
	return color_32;
}

/**
 * \brief	Tells the placer to recompute the geometry of a widget.
 *		The widget must have been previously placed by a call to \ref ei_place.
 *		Geometry re-computation is necessary for example when the text label of
 *		a widget has changed, and thus the widget "natural" size has changed.
 *
 * @param	widget		The widget which geometry must be re-computed.
 */
void ei_impl_placer_run(ei_widget_t widget);

/**
 * @brief	Draws the children of a widget.
 * 		The children are draw withing the limits of the clipper and
 * 		the widget's content_rect.
 *
 * @param	widget		The widget which children are drawn.
 * @param	surface		A locked surface where to draw the widget's children.
 * @param	pick_surface	The picking offscreen.
 * @param	clipper		If not NULL, the drawing is restricted within this rectangle
 *				(expressed in the surface reference frame).
 */
void ei_impl_widget_draw_children      (ei_widget_t		widget,
					ei_surface_t		surface,
					ei_surface_t		pick_surface,
					ei_rect_t*		clipper);