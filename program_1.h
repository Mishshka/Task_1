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
const string RUS_let = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдеёжзийклмнопрстуфхцчшщъыьэюя";
const string num = "0123456789";
const string SPec = "~!@#$%^&*()+`'\":<> / |";

const int size_c = 256;

//функции
void write_to_file(string folder_name); // функция записи в новый файл
void add_to_file(string folder_name); // функция записи в существующий файл

int count_files(string folder_name); // функция получения числа файлов
string* get_filenames(string folder_name); //  функция для получения массива из имен файлов
void write_stud(FILE* fout); // функция ввода в файл студентов
void write_pas(FILE* fout); // функция ввода в файл паролей

void ClearScreen(); // функция для очистки экрана консоли
void ShowMenu(int selected); //функция для вывода меню
void ShowActive(int selected); // функция выбора записываемой информации

struct Stud { //структура студентов
	char family[size_c];
	char group[size_c];
	char gr_ind[size_c];
};
struct Pass { //структура паролей
	char group[size_c];
	char gr_ind[size_c];
	char password[size_c];
};