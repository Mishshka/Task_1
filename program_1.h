#pragma once
// ����������� ���������
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


// ����������� ������������ ����
using namespace std;
namespace fs = filesystem;

//��������� � ���������� ���������
const string ENG_let = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
const string RUS_let = "�����Ũ����������������������������������������������������������";
const string num = "0123456789";
const string SPec = "~!@#$%^&*()+`'\":<> / |";

const int size_c = 256;

//�������
void write_to_file(string folder_name); // ������� ������ � ����� ����
void add_to_file(string folder_name); // ������� ������ � ������������ ����

int count_files(string folder_name); // ������� ��������� ����� ������
string* get_filenames(string folder_name); //  ������� ��� ��������� ������� �� ���� ������
void write_stud(FILE* fout); // ������� ����� � ���� ���������
void write_pas(FILE* fout); // ������� ����� � ���� �������

void ClearScreen(); // ������� ��� ������� ������ �������
void ShowMenu(int selected); //������� ��� ������ ����
void ShowActive(int selected); // ������� ������ ������������ ����������

struct Stud { //��������� ���������
	char family[size_c];
	char group[size_c];
	char gr_ind[size_c];
};
struct Pass { //��������� �������
	char group[size_c];
	char gr_ind[size_c];
	char password[size_c];
};