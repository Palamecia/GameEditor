#include "project.h"

Project::Project() {

}

Project &Project::instance() {
    static Project g_instance;
    return g_instance;
}

QString Project::getPath() const {
    return "/home/palamecia/Documents/Developpement/C++/AngrySamurai/rc";
}
