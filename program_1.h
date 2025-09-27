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
const string RUS_let = "јЅ¬√ƒ≈®∆«»… ЋћЌќѕ–—“”‘’÷„ЎўЏџ№ёяaабвгдеЄжзийклмнопрстуфхцчшщъыью€";
const string num = "0123456789";
const string SPec = "~!@#$%^&*()+`'\"; :<> / \ |";

//функции
string choose_folder(); //выбор папки
void write_to_file(string folder_name); // запись в новый файл
int count_files(string folder_name); // число файлов
string* get_filenames(string folder_name); // массив из имен файлов
void write_stud(ofstream* fout); // ввод в файл студентов
void write_pas(ofstream* fout); // ввод в файл паролей