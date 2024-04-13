#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define COLUMNCOUNT 40
#define ROWCOUNT    20

using namespace std;

void PrintBoard(char Base[][COLUMNCOUNT], int Money, int Population);

int DifficultyChecker(string difficulty);

int GamePopulator(char Base[][COLUMNCOUNT], int Population, int CityLevel);

int main()
{
    srand(time(NULL));
    string PlayerName="";
    string Difficulty ="";
    int Money=10000;
    int Population = 10;
    int CityLevel = 1;
    int HouseholdCount = 0;
    char Base[ROWCOUNT][COLUMNCOUNT];
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
    cout << "\033[2J\033[1;1H";
    HouseholdCount=GamePopulator(Base, Population, CityLevel);
    PrintBoard(Base,Money,Population);

    return 0;
}

void PrintBoard(char Base[][COLUMNCOUNT], int Money, int Population)
{
    cout << "Money: $" << Money << "\tPopulation: " << Population << endl;
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