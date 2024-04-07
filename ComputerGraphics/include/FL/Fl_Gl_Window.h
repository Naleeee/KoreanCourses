//
// "$Id$"
//
// OpenGL header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 1998-2015 by Bill Spitzak and others.
//
// This library is free software. Distribution and use rights are outlined in
// the file "COPYING" which should have been included with this file.  If this
// file is missing or damaged, see the license at:
//
//     http://www.fltk.org/COPYING.php
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

/* \file
   Fl_Gl_Window widget . */

#ifndef Fl_Gl_Window_H
#define Fl_Gl_Window_H

#include "Fl_Window.H"

#ifndef GLContext
/**
  Opaque pointer type to hide system specific implementation.
*/
typedef void* GLContext; // actually a GLXContext or HGLDC
#endif

class Fl_Gl_Choice; // structure to hold result of glXChooseVisual

/**
  The Fl_Gl_Window widget sets things up so OpenGL works.
  
  It also keeps an OpenGL "context" for that window, so that changes to the
  lighting and projection may be reused between redraws. Fl_Gl_Window
  also flushes the OpenGL streams and swaps buffers after draw() returns.

  OpenGL hardware typically provides some overlay bit planes, which
  are very useful for drawing UI controls atop your 3D graphics.  If the
  overlay hardware is not provided, FLTK tries to simulate the overlay.
  This works pretty well if your graphics are double buffered, but not
  very well for single-buffered.

  Please note that the FLTK drawing and clipping functions
  will not work inside an Fl_Gl_Window. All drawing
  should be done using OpenGL calls exclusively.
  Even though Fl_Gl_Window is derived from Fl_Group, 
  it is not useful to add other FLTK Widgets as children,
  unless those widgets are modified to draw using OpenGL calls.
*/
class FL_EXPORT Fl_Gl_Window : public Fl_Window {

  int mode_;
  const int *alist;
  Fl_Gl_Choice *g;
  GLContext context_;
  char valid_f_;
  char damage1_; // damage() of back buffer
  virtual void draw_overlay();
  void init();

  void *overlay;
  void make_overlay();
  friend class _Fl_Gl_Overlay;

  static int can_do(int, const int *);
  int mode(int, const int *);
  static int gl_plugin_linkage();

public:

  void show();
  void show(int a, char **b) {Fl_Window::show(a,b);}
  void flush();
  void hide();
  void resize(int,int,int,int);
  int handle(int);
  
  /**
    Is turned off when FLTK creates a new context for this window or 
    when the window resizes, and is turned on \e after draw() is called.
    You can use this inside your draw() method to avoid unnecessarily
    initializing the OpenGL context. Just do this:
    \code
    void mywindow::draw() {
     if (!valid()) {
       glViewport(0,0,pixel_w(),pixel_h());
       glFrustum(...);
       ...other initialization...
     }
     if (!context_valid()) {
       ...load textures, etc. ...
     }
     ... draw your geometry here ...
    }
    \endcode
    
    You can turn valid() on by calling valid(1).  You
    should only do this after fixing the transformation inside a draw()
    or after make_current().  This is done automatically after 
    draw() returns.
  */
  char valid() const {return valid_f_ & 1;}
  /**
    See char Fl_Gl_Window::valid() const 
  */
  void valid(char v) {if (v) valid_f_ |= 1; else valid_f_ &= 0xfe;}
  void invalidate();

  /**
    Will only be set if the 
    OpenGL context is created or recreated. It differs from
    Fl_Gl_Window::valid() which is also set whenever the context
    changes size.
  */
  char context_valid() const {return valid_f_ & 2;}
  /**
    See char Fl_Gl_Window::context_valid() const 
  */
  void context_valid(char v) {if (v) valid_f_ |= 2; else valid_f_ &= 0xfd;}

  /**  Returns non-zero if the hardware supports the given OpenGL mode. */
  static int can_do(int m) {return can_do(m,0);}
  /**  Returns non-zero if the hardware supports the given OpenGL mode.
   \see Fl_Gl_Window::mode(const int *a) */
  static int can_do(const int *m) {return can_do(0, m);}
  /**  Returns non-zero if the hardware supports the current OpenGL mode. */
  int can_do() {return can_do(mode_,alist);}
  /** Returns the current OpenGL capabilites of the window.
   Don't use this if capabilities were set through Fl_Gl_Window::mode(const int *a).
   */
  Fl_Mode mode() const {return (Fl_Mode)mode_;}
  /**
   Set or change the OpenGL capabilites of the window.  The value can be
   any of the following OR'd together:
   
   - \c FL_RGB - RGB color (not indexed)
   - \c FL_RGB8 - RGB color with at least 8 bits of each color
   - \c FL_INDEX - Indexed mode
   - \c FL_SINGLE - not double buffered
   - \c FL_DOUBLE - double buffered
   - \c FL_ACCUM - accumulation buffer
   - \c FL_ALPHA - alpha channel in color
   - \c FL_DEPTH - depth buffer
   - \c FL_STENCIL - stencil buffer
   - \c FL_MULTISAMPLE - multisample antialiasing
   - \c FL_OPENGL3 - use OpenGL version 3.0 or more.
   
   FL_RGB and FL_SINGLE have a value of zero, so they
   are "on" unless you give FL_INDEX or FL_DOUBLE.
   
   If the desired combination cannot be done, FLTK will try turning off
   FL_MULTISAMPLE.  If this also fails the show() will call
   Fl::error() and not show the window.
   
   You can change the mode while the window is displayed.  This is most
   useful for turning double-buffering on and off.  Under X this will
   cause the old X window to be destroyed and a new one to be created.  If
   this is a top-level window this will unfortunately also cause the
   window to blink, raise to the top, and be de-iconized, and the xid()
   will change, possibly breaking other code.  It is best to make the GL
   window a child of another window if you wish to do this!
   
   mode() must not be called within draw() since it
   changes the current context.
   
   The FL_OPENGL3 flag is required to access OpenGL version 3 or more
   under the X11 and MacOS platforms; it's optional under Windows.
   See more details in \ref opengl3.
   
   \version the <tt>FL_OPENGL3</tt> flag appeared in version 1.3.4
   */
  int mode(int a) {return mode(a,0);}
  /** Set the OpenGL capabilites of the window using platform-specific data.
   \param a zero-ending array of platform-specific attributes and attribute values
   <p><b>Unix/Linux platform</b>: attributes are GLX attributes adequate for the 3rd argument of
   the <tt>glXChooseVisual()</tt> function (e.g., <tt>GLX_DOUBLEBUFFER</tt>, defined by including <GL/glx.h>).
   \note What attributes are adequate here is subject to change.
   The preferred, stable public API is Fl_Gl_Window::mode(int a).
   <p><b>MSWindows platform</b>: this member function is of no use.
   <p><b>Mac OS X platform</b>: attributes belong to the <tt>CGLPixelFormatAttribute</tt> enumeration
   (defined by including <tt><OpenGL/OpenGL.h></tt>, e.g., <tt>kCGLPFADoubleBuffer</tt>)
   and may be followed by adequate attribute values.
   */
  int mode(const int *a) {return mode(0, a);}
  /** Returns a pointer to the GLContext that this window is using.
   \see void context(void* v, int destroy_flag) */
  void* context() const {return context_;}
  void context(void*, int destroy_flag = 0);
  void make_current();
  void swap_buffers();
  void ortho();

  /**
    Returns true if the hardware overlay is possible.  If this is false,
    FLTK will try to simulate the overlay, with significant loss of update
    speed.  Calling this will cause FLTK to open the display.
  */
  int can_do_overlay();
  /**
    This method causes draw_overlay() to be called at a later time.
    Initially the overlay is clear. If you want the window to display
    something in the overlay when it first appears, you must call this
    immediately after you show() your window.
  */
  void redraw_overlay();
  void hide_overlay();
  /**
    The make_overlay_current() method selects the OpenGL context
    for the widget's overlay.  It is called automatically prior to the 
    draw_overlay() method being called and can also be used to
    implement feedback and/or selection within the handle()
    method.
  */
  void make_overlay_current();

  // Note: Doxygen docs in Fl_Widget.H to avoid redundancy.
  virtual Fl_Gl_Window* as_gl_window() {return this;}
  
  /** The number of pixels per FLTK unit of length for the window.
   Returns 1, except for a window mapped to
   an Apple 'retina' display, and if Fl::use_high_res_GL(bool) is set to true,
   when it returns 2. This method dynamically adjusts its value when the window
   is moved to/from a retina display. This method is useful, e.g., to convert,
   in a window's handle() method, the FLTK units returned by Fl::event_x() and
   Fl::event_y() to the pixel units used by the OpenGL source code.
   \version 1.3.4
   */
#ifdef __APPLE__
  float pixels_per_unit();
#else
  float pixels_per_unit() { return 1; }
#endif
  /** Gives the window width in OpenGL pixels.
   Generally identical with the result of the w() function, but for a window mapped to
   an Apple 'retina' display, and if Fl::use_high_res_GL(bool) is set to true,
   pixel_w() returns 2 * w(). This method detects when the window has been moved
   between low and high resolution displays and automatically adjusts the returned value.
   \version 1.3.4
   */
  int pixel_w() { return int(pixels_per_unit() * w() + 0.5); }
  /** Gives the window height in OpenGL pixels.
   Generally identical with the result of the h() function, but for a window mapped to
   an Apple 'retina' display, and if Fl::use_high_res_GL(bool) is set to true,
   pixel_h() returns 2 * h(). This method detects when the window has been moved
   between low and high resolution displays and automatically adjusts the returned value.
   \version 1.3.4
   */
  int pixel_h() { return int(pixels_per_unit() * h() + 0.5); }
  
  ~Fl_Gl_Window();
  /**
    Creates a new Fl_Gl_Window widget using the given size, and label string. 
    The default boxtype is FL_NO_BOX. The default mode is FL_RGB|FL_DOUBLE|FL_DEPTH.
  */
  Fl_Gl_Window(int W, int H, const char *l=0) : Fl_Window(W,H,l) {init();}
  /**
    Creates a new Fl_Gl_Window widget using the given position,
    size, and label string. The default boxtype is FL_NO_BOX. The
    default mode is FL_RGB|FL_DOUBLE|FL_DEPTH.
  */

  Fl_Gl_Window(int X, int Y, int W, int H, const char *l=0)
    : Fl_Window(X,Y,W,H,l) {init();}

protected:
  /**
    Draws the Fl_Gl_Window.

    You \e \b must override the draw() method.
  */
  virtual void draw();
};

#endif

//
// End of "$Id$".
//
