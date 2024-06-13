// the main routine makes the window, and then runs an even loop
// until the window is closed
// #include <windows.h>
#include "../include/MyGlWindow.h"

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Value_Slider.H>
#include <ctime>

Fl_Group *widgets;

long lastRedraw = 0;
int frameRate = 1920;

void changeFrameCB(Fl_Widget *w, void *data)
{
	auto *widget = dynamic_cast<Fl_Choice *>(w);
	int i = widget->value();
	const char *menu = widget->text(i);
	frameRate = atoi(menu);

	auto *win = (MyGlWindow *)data;
	win->redraw();
}

void idleCB(void *w)
{
	auto *win = (MyGlWindow *)w;
	if (clock() - lastRedraw > CLOCKS_PER_SEC / frameRate) {
		lastRedraw = clock();
		win->update();
	}
	win->redraw();
}

void but_cb(Fl_Widget *o, void *data)
{
	auto *b = dynamic_cast<Fl_Button *>(o); // Ä³½ºÆÃÀÌ ¹Ýµå½Ã ÇÊ¿ä
	auto *win = (MyGlWindow *)data;
	if (b->value())
		win->run = 1;
	else
		win->run = 0;
	win->damage(1);
}

void but_cb2(Fl_Widget *o, void *data)
{
	auto *b = dynamic_cast<Fl_Button *>(o); // Ä³½ºÆÃÀÌ ¹Ýµå½Ã ÇÊ¿ä
	auto *win = (MyGlWindow *)data;
	win->test();
	win->damage(1);
}

// void but_cb3(Fl_Widget *o, void *data)
// {
// 	Fl_Value_Slider *b = (Fl_Value_Slider *)o; //캐스팅이 반드시 필요
// 	MyGlWindow *win = (MyGlWindow *)data;
// 	win->testValue(b->value());
// 	win->damage(1);
// }

int main()
{
	Fl::scheme("plastic"); // plastic
	int width = 800;
	int height = 800;
	auto *wind = new Fl_Double_Window(100, 100, width, height, "GL 3D FrameWork");

	wind->begin(); // put widgets inside of the window

	widgets = new Fl_Group(0, 0, 800, 800);
	widgets->begin();

	auto *gl = new MyGlWindow(10, 10, width - 20, height - 50);
	Fl::add_idle((void (*)(void *))idleCB, gl); //

	widgets->end();
	Fl_Group::current()->resizable(widgets);

	Fl_Choice *choice = nullptr;
	choice = new Fl_Choice(100, height - 40, 50, 20, "FrameRate");
	choice->add("15");
	choice->add("30");
	choice->add("60");
	choice->add("120");
	choice->add("240");
	choice->add("480");
	choice->add("960");
	choice->add("1920");
	choice->value(2);
	choice->callback((Fl_Callback *)changeFrameCB, gl);

	auto *test = new Fl_Light_Button(width - 600, height - 40, 100, 20, "Run");
	test->callback(but_cb, gl);
	gl->ui = test;

	auto *test2 = new Fl_Button(width - 400, height - 40, 100, 20, "Test");
	test2->callback(but_cb2, gl);

	Fl_Value_Slider *test3 = new Fl_Value_Slider(width - 200, height - 40, 150, 20, "Test");
	test3->type(FL_HORIZONTAL);
	// test3->callback(but_cb3, gl);

	wind->end();

	wind->show(); // this actually opens the window

	Fl::run();
	delete wind;

	return 1;
}
