#include <X11/X.h>  
#include <X11/Xutil.h>
#include <stdint.h>

void grab_screen(unsigned int x, unsigned int y, unsigned int width, unsigned int height, /* out */ uint8_t *out)
{
    Display *display = XOpenDisplay(NULL);
    Window root = DefaultRootWindow(display);

    XImage *image = XGetImage(display, root, x, y, width, height, AllPlanes, ZPixmap);

    size_t pos = 0;
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            unsigned long pixel = XGetPixel(image, j, i);
            uint8_t red = (pixel & image->red_mask) >> 16;
            uint8_t green = (pixel & image->green_mask) >> 8;
            uint8_t blue = (pixel & image->blue_mask);

            out[pos + 0] = red;
            out[pos + 1] = green;
            out[pos + 2] = blue;
            pos += 3;
        }
    }

    XDestroyImage(image);
    XDestroyWindow(display, root);
    XCloseDisplay(display);
}
