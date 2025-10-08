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
#include <stdio.h>
#include <fstream>


// подключение пространства имен
using namespace std;
namespace fs = filesystem;

//константы с возможными символами
const string ENG_let = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const string RUS_let = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЮЯaабвгдеёжзийклмнопрстуфхцчшщъыьюя";
const string num = "0123456789";
const string SPec = "~!@#$%^&*()+`'\"; :<> / \\ |";

//функции
void write_to_file(string folder_name); // функция записи в новый файл
void add_to_file(string folder_name); // функция записи в существующий файл

int count_files(string folder_name); // функция получения числа файлов
string* get_filenames(string folder_name); //  функция для получения массива из имен файлов
void write_stud(ofstream* fout); // функция ввода в файл студентов
void write_pas(ofstream* fout); // функция ввода в файл паролей

void ClearScreen(); // функция для очистки экрана консоли
void ShowMenu(int selected); //функция для вывода меню
void ShowActive(int selected);