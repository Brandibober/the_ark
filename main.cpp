#include <iostream>
#include <iomanip>
#include <fstream>
#include "TheArk.h"
#include "menu.h"

using std::cin;
using std::cout;
using std::endl;
using std::setw;

void print_table_header(std::ostream & fout);

int main() {

    Menu the_ark;
    RenderWindow window;
    the_ark.welcome_page("../images/menu.jpg",
                         "../images/exit.png",
                         "../images/start.png" );

    if (the_ark.get_flight())
    {
        TheArk & ark = *TheArk::get_instance();

        std::ofstream fout("../TheArk.csv");
        ark.init(&cin, &fout);

        print_table_header(fout);

        ark.flight();
        ark.deleteArk();
    }

    return 0;
}

void print_table_header(std::ostream & fout)
{
    std::array<std::string, 6> services_names = {"Technical", "Biological",
                                                 "Medical", "Navigation",
                                                 "Emergency", "Social"};
    fout << setw(CELL_WIDTH) << "Year" << ","
         << setw(CELL_WIDTH) << "Total" << ","
         << setw(CELL_WIDTH) << "Child" << ","
         << setw(CELL_WIDTH) << "Adults" << ","
         << setw(CELL_WIDTH) << "Old" << ","
         << setw(CELL_WIDTH) << "Consum" << ","
         << setw(CELL_WIDTH) << "Compon" << ","
         << setw(CELL_WIDTH) << "Used" << ","
         << setw(CELL_WIDTH) << "Junk" << ","
         << setw(CELL_WIDTH) << "Ref" << ",";

    for (int i = 0; i < 6; ++i)
        fout << setw(CELL_WIDTH) << services_names[i] << ",";

    fout << endl;
}