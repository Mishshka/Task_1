#pragma once
// подключение библиотек
#include <iostream>
#include <filesystem>
#include <Windows.h>
#include <vector>
#include <string>
#include <conio.h>
#include <chrono>
#include <thread>

// подключение пространства имен
using namespace std;
namespace fs = filesystem;

//константы с возможными символами
const string ENG_let = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const string RUS_let = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЮЯaабвгдеёжзийклмнопрстуфхцчшщъыьюя";
const string num = "0123456789";
const string SPec = "~!@#$%^&*()+`'\"; :<> / \ |";

