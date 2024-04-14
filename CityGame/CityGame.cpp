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

void PrintBoard(char Base[][COLUMNCOUNT], int Money, int Population, vector<int> CurrentDate, int CityHappiness);

int DifficultyChecker(string difficulty);

int GamePopulator(char Base[][COLUMNCOUNT], int Population, int CityLevel);

void SaveFileAgent(char(Base)[ROWCOUNT][COLUMNCOUNT]);

void PrintGameMenu();

void DateChanger(vector<int> &Date);

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
    string PlayerInput;
    char Base[ROWCOUNT][COLUMNCOUNT];
    vector<int> CurrentDate = { 2000,1,0 };
    int OverallCityHappiness = 100;
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
    GamePopulator(Base, Population, CityLevel);
    while (PlayerInput != "x")
    {
        DateChanger(CurrentDate);
        GamePopulator(Base, NewPopulation, CityLevel);
        system("CLS");
        PrintBoard(Base, Money, Population, CurrentDate, OverallCityHappiness);
        SaveFileAgent(Base);
        PrintGameMenu();
        cin >> PlayerInput;
    }

    return 0;
}

void PrintBoard(char Base[][COLUMNCOUNT], int Money, int Population, vector<int> CurrentDate, int CityHappiness)
{
    cout << "Money: $" << Money << "      Population: " << Population << "      Date: "<< CurrentDate[0]<<"."<<CurrentDate[1]<<"."<<CurrentDate[2]<<"      Happiness: "<<CityHappiness<<"%"<<endl;
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

int GamePopulator(char (Base)[ROWCOUNT][COLUMNCOUNT], int Population, int CityLevel)
{
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

void DateChanger(vector<int> &Date)
{
    bool IsLeapYear = false;
    if (Date[0] % 400 == 0 || (Date[0] % 100 != 100 && Date[0] % 4 == 1)) IsLeapYear = true;
    vector<int> Months30 = { 4,6,9,11 };
    vector<int> Months31 = { 1,3,5,7,10,12 };
    if (find(Months30.begin(), Months30.end(), Date[1]) != Months30.end() && Date[2] + 1 == 31)
    {
        if (Date[1]+1 == 13) Date[1] = 1;
        else
        {
            Date[1]++;
            Date[2]=1;
        }
    }
    else if (find(Months31.begin(), Months31.end(), Date[1]) != Months31.end() && Date[2] + 1 == 32)
    {
        if (Date[1]+1 == 13) Date[1] = 1;
        else
        {
            Date[1]++;
            Date[2]=1;
        }
    }
    else if ((Date[1] == 2 && Date[2] + 1 == 29 && IsLeapYear == false) || Date[1] == 2 && Date[2] + 1 == 30 && IsLeapYear == true)
    {
        Date[1]++;
        Date[2] = 1;
    }
    else Date[2]++;
}