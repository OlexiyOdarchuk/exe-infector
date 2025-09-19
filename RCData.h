#pragma once

#include <windows.h>

void PutFileInRCData(PCHAR file, PCHAR target, int id);
void RunFileInRCData(PCHAR target, int id, BOOL isPython);
