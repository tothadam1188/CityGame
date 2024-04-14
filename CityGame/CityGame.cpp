#include "CityGame.h"
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

int main()
{
    srand(time(NULL));
    string PlayerName="";
    string Difficulty ="";
    int Money=10000;
    int Population = 10;
    int NewPopulation = 0;
    int CityLevel = 1;
    int HouseholdCount = 0;
    string PlayerInput="";
    char Base[ROWCOUNT][COLUMNCOUNT];
    vector<int> CurrentDate = { 2000,1,0 };
    int OverallCityHappiness = 100;
    vector<int> OverallCityStatistics;
    for (int i = 0; i < ROWCOUNT; i++)
    {
        for (int j = 0; j < COLUMNCOUNT; j++)
        {
            Base[i][j] = '_';
        }
    }
    cout << "Welcome to the City Game!" << endl;
    cout << "Please enter your name: ";
    getline(cin, PlayerName);
    cout << "Nice to meet you, " << PlayerName << "! Please choose a difficulty:"<<endl;
    cout << "Easy \n \t - Starting money: $30,000" << endl;
    cout << "Medium \n \t - Starting money: $20,000" << endl;
    cout << "Hard \n \t - Starting money: $10,000" << endl;
    cin >> Difficulty;
    Money*=DifficultyChecker(Difficulty);
    Population *= DifficultyChecker(Difficulty);
    HouseholdCount=GamePopulator(Base, Population, CityLevel);
    while (true)
    {
        DateChanger(CurrentDate);
        GamePopulator(Base, NewPopulation, CityLevel);
        system("CLS");
        PrintBoard(Base, Money, Population, CurrentDate, OverallCityHappiness);
        SaveFileAgent(Base);
        PrintGameMenu();
        while (true)
        {
            cin >> PlayerInput;
            if(PlayerInput=="s")
                {
                    StatisticsMenu(DataToStatisticsVector(Population, CityLevel, HouseholdCount, NewPopulation));
                }
            if (PlayerInput == "x")
            {
                ExitMenu(Base);
                system("CLS");
                PrintBoard(Base, Money, Population, CurrentDate, OverallCityHappiness);
                PrintGameMenu();
            }
            if (PlayerInput == "f")
            {
                break;
            }

            PlayerInput = "";
        }
        
    }

    return 0;
}