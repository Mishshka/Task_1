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
const string RUS_let = "�����Ũ�������������������������a�������������������������������";
const string num = "0123456789";
const string SPec = "~!@#$%^&*()+`'\"; :<> / \\ |";

//�������
void write_to_file(string folder_name); // ������� ������ � ����� ����
void add_to_file(string folder_name); // ������� ������ � ������������ ����

int count_files(string folder_name); // ������� ��������� ����� ������
string* get_filenames(string folder_name); //  ������� ��� ��������� ������� �� ���� ������
void write_stud(ofstream* fout); // ������� ����� � ���� ���������
void write_pas(ofstream* fout); // ������� ����� � ���� �������

void ClearScreen(); // ������� ��� ������� ������ �������
void ShowMenu(int selected); //������� ��� ������ ����
void ShowActive(int selected);