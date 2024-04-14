#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <conio.h>
#include <algorithm>
#define COLUMNCOUNT 40
#define ROWCOUNT    20

using namespace std;

void PrintBoard(char Base[][COLUMNCOUNT], int Money, int Population, vector<int> CurrentDate, int CityHappiness)
{
    cout << "Money: $" << Money << "      Population: " << Population << "      Date: " << CurrentDate[0] << "." << CurrentDate[1] << "." << CurrentDate[2] << "      Happiness: " << CityHappiness << "%" << endl;
    for (int i = 0; i < ROWCOUNT; i++)
    {
        for (int j = 0; j < COLUMNCOUNT; j++)
        {
            cout << Base[i][j];
        }
        cout << endl;
    }
};

int DifficultyChecker(string difficulty)
{
    for (int i = 0; i < difficulty.length(); i++) difficulty[i] = tolower(difficulty[i]);
    if (difficulty == "easy" || difficulty == "e") return 3;
    else if (difficulty == "medium" || difficulty == "m") return 2;
    else if (difficulty == "hard" || difficulty == "h") return 1;
    else return -1;
};

int RandomLoc(int num)
{
    int loc = rand() % num;
    return loc;
};

int GamePopulator(char(Base)[ROWCOUNT][COLUMNCOUNT], int Population, int CityLevel)
{
    CityLevel *= 5;
    int HouseFull = Population / CityLevel;
    int HouseRemainder = Population % CityLevel;
    int HouseholdCount = HouseFull + HouseRemainder;
    for (int i = 0; i < HouseholdCount; i++)
    {
        int locx = 0;
        int locy = 0;
        while (Base[locx][locy] != '_')
        {
            locx = RandomLoc(ROWCOUNT);
            locy = RandomLoc(COLUMNCOUNT);
        }
        Base[locx][locy] = 'A';
    }
    return HouseholdCount;
};

void SaveFileAgent(char(Base)[ROWCOUNT][COLUMNCOUNT])
{
    ofstream outfile("save1.txt");
    for (int i = 0; i < ROWCOUNT; i++)
    {
        for (int j = 1; j < COLUMNCOUNT; j++)
        {
            outfile << Base[i][j];
        }
        outfile << endl;
    }
};

void PrintGameMenu()
{
    cout << "b)   Build mode\t";
    cout << "\ts)   Statistics" << endl;
    cout << "m)   Management ";
    cout << "\ti)   Inspect tile" << endl;
};

void DateChanger(vector<int>& Date)
{
    bool IsLeapYear = false;
    if (Date[0] % 400 == 0 || (Date[0] % 100 != 100 && Date[0] % 4 == 1)) IsLeapYear = true;
    vector<int> Months30 = { 4,6,9,11 };
    vector<int> Months31 = { 1,3,5,7,10,12 };
    if (find(Months30.begin(), Months30.end(), Date[1]) != Months30.end() && Date[2] + 1 == 31)
    {
        if (Date[1] + 1 == 13) Date[1] = 1;
        else
        {
            Date[1]++;
            Date[2] = 1;
        }
    }
    else if (find(Months31.begin(), Months31.end(), Date[1]) != Months31.end() && Date[2] + 1 == 32)
    {
        if (Date[1] + 1 == 13) Date[1] = 1;
        else
        {
            Date[1]++;
            Date[2] = 1;
        }
    }
    else if ((Date[1] == 2 && Date[2] + 1 == 29 && IsLeapYear == false) || Date[1] == 2 && Date[2] + 1 == 30 && IsLeapYear == true)
    {
        Date[1]++;
        Date[2] = 1;
    }
    else Date[2]++;
}

vector<int> DataToStatisticsVector(int population, int citylevel, int householdcount, int newpopulation)
{
    vector<int> stats;
    stats.push_back(population);
    stats.push_back(citylevel);
    stats.push_back(householdcount);
    stats.push_back(newpopulation);

    return stats;
};

void StatisticsMenu(vector<int> stats)
{
    if(stats[3]>0) cout << "Population:\t" << stats[0] << " (+" << stats[3] << " change)" << endl;
    else cout << "Population:\t" << stats[0] << " (+" << stats[3] << " change)" << endl;
    cout << "Number of households:\t" << stats[2] << endl;
    cout << "City level:\t" << stats[1] << endl;
};

void ExitMenu(char(Base)[ROWCOUNT][COLUMNCOUNT])
{
    string Input="";
    cout << "Are you sure you'd like to quit? (y/n)" << endl;
    cin >> Input;
    if (Input == "y")
    {
        cout << "Save before quitting? yes(y) / no(n) / cancel (c)" << endl;
        Input = "";
        cin >> Input;
        if (Input == "y")
        {
            SaveFileAgent(Base);
            exit(0);
        }
        else if (Input == "n")
        {
            exit(0);
        }
    }
}