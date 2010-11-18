/* *************************************************************************
 *  Copyright 2010 Jakob Gruber                                            *
 *                                                                         *
 *  This program is free software: you can redistribute it and/or modify   *
 *  it under the terms of the GNU General Public License as published by   *
 *  the Free Software Foundation, either version 3 of the License, or      *
 *  (at your option) any later version.                                    *
 *                                                                         *
 *  This program is distributed in the hope that it will be useful,        *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *  GNU General Public License for more details.                           *
 *                                                                         *
 *  You should have received a copy of the GNU General Public License      *
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.  *
 ************************************************************************* */

#ifndef PROGRAM_H
#define PROGRAM_H

#include <algorithm>
#include <iostream>
#include <ncurses.h>
#include <vector>
#include <stdarg.h>
#include <boost/bind.hpp>
#include <boost/format.hpp>

#include "package.h"
#include "alpmexception.h"
#include "cursesframe.h"
#include "curseslistbox.h"
#include "config.h"
#include "filter.h"

using std::string;
using std::vector;

typedef struct __pmdb_t pmdb_t;
typedef struct __alpm_list_t alpm_list_t;

#define KEY_ESC (27)
#define KEY_RETURN (10)
#define KEY_SPACE (32)
#define KEY_TAB (9)
#define KEY_KONSOLEBACKSPACE (127)

enum RightPaneEnum {
    RPE_INFO,
    RPE_QUEUE
};

enum ModeEnum {
    MODE_STANDARD,
    MODE_INPUT,
    MODE_HELP,
};

enum FilterOperationEnum {
    OP_SEARCH,
    OP_FILTER,
    OP_COLORCODE,
    OP_NONE,
};

class Program
{
public:
    Program();
    ~Program();

    void Init();
    void MainLoop();

private:

    void init_alpm();
    void init_curses();
    void print_help();
    void deinit_curses();
    void printinfosection(AttributeEnum attr, string text);
    void updatedisplay();
    void clearfilter();
    void filterpackages(string str);
    void updatelistinfo();
    void displayprocessingmsg();
    string optostr(FilterOperationEnum o) const;


    RightPaneEnum rightpane;
    ModeEnum mode;

    bool
            quit;

    CursesListBox
            *list_pane,
            *queue_pane,
            *focused_pane;
    CursesFrame
            *info_pane,
            *input_pane,
            *help_pane;

    std::vector<Package*>
            packages,
            filteredpackages,
            opqueue;

    pmdb_t
            *localdb;

    std::string
            inputbuf,
            searchphrases;

    FilterOperationEnum
            op;
};

#endif // PROGRAM_H
