// Implementation of simple Qt example
// cycles through background colors while display user-input lines
/*
Copyright (c) 2018 Jeff Trull <edaskel@att.net>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <QApplication>
#include <QTimer>

#include "colorrect.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // a really simple widget
    ColorRect cr;
    cr.setWindowTitle("Color Cycler");
    cr.show();

    // change widget color every 500ms
    QTimer * changeTimer = new QTimer(&app);
    QObject::connect(changeTimer, &QTimer::timeout,
                     [&]() { cr.changeColor(); });
    changeTimer->start(500);

    // draw lines from clicks
    bool got_first_point{false};
    QPointF first_point;

    QObject::connect(&cr, &ColorRect::click, [&](QPointF p) {
        if (got_first_point) {
            // draw
            cr.setLine(first_point, p);
            got_first_point = false;
        } else {
            first_point = p;
            got_first_point = true;
        }
    });

    return app.exec();
}
