#pragma once

#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>

int getch();
std::string ReadPassword(std::string message);
void clearScreen();
