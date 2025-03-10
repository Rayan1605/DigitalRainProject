#include "Drawing.h"
#include <iostream>
char Drawing::getRandomChar() {
    return 'A' + (5 % 26); // Always returns 'F'
}