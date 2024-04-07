// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once

#define _CRT_SECURE_NO_DEPRECATE 1

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
// #include <windows.h>

#include <malloc.h>
#include <memory.h>

#include "GL/glut.h"

// FLTK widgets.
//
// The FLTK source is rife with dubious type conversions (i.e., void* to long),
// which causes a slew of compiler warnings to be generated.  All of the Fl
// widgets that we use are included in the following block, and for this block
// we temporarily supress display of these warnings.

#pragma warning(disable : 4312)
#pragma warning(disable : 4311)
#pragma warning(disable : 4244)
#pragma warning(disable : 4275)

#include "FL/Fl.h"
#include "FL/Fl_Gl_Window.h"
#include "FL/Fl_Group.h"
#include "FL/Fl_Widget.h"
#include "FL/Fl_Window.h"

#include "FL/filename.h"
#include "FL/fl_message.h"
#pragma warning(default : 4312)
#pragma warning(default : 4311)
#pragma warning(default : 4244)

// TODO: reference additional headers your program requires here
