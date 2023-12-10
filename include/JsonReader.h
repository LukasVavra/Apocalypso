#pragma once
#include <ArduinoJson-v6.19.4.h>
#include <fstream>
#include <iostream>

bool load_json(JsonDocument& doc, const char* path);