#include <cstdio>
#include <iostream>
#include <string>

#include "CustomEventHandler.hpp"

using namespace std;

string CustomEventHandler::getClassTag(){
    string tag(CustomEventHandler::CLASS_TAG);
    return tag;
}