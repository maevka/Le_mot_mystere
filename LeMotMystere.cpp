#include <iostream>
#include <string>
#include <locale>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

string toUppercase(string const wordLowercase)
{
    string wordUppercase;

    for (char c : wordLowercase)
    {
        if (!isupper(c))
            wordUppercase.push_back(toupper(c));
        else
            wordUppercase.push_back(c);
    }
    return wordUppercase;
}

string mixLetters(string word)
{
    int pos;
    string mixedWord;

    while(!word.empty())
    {
        pos = rand() % word.size();
        mixedWord.push_back(word[pos]);
        word.erase(pos, 1);
    }

    return mixedWord;
}

bool getWordFromFile(string& word)
{
    int wordsCnt = 0;
    string line;
    ifstream file("words_to_guess.txt");

    if (!file)
    {
        cerr << "Problème de fichier.\n" << endl;
        return false;
    }

    getline(file, line);
    wordsCnt = stoi(line);

    if (wordsCnt <= 0)
    {
        cerr << "Problème dans le fichier.\n" << endl;
        return false;
    }

    int randPos = rand() % wordsCnt;
    for (int i = 0; i < randPos; i++)
    {
        getline(file, line);
    }    

    word = line;
    return true;
}

void clearConsole()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
}

void clearHalfConsole()
{
    cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
}

string getUserInput()
{
    string input;

    cin >> input;
    cin.ignore();
    input = toUppercase(input);

    return input;
}

int main()
{
    string word, answer;
    bool stillWantToPlay = true, modeSelected = false;

    srand(time(0));

    while (stillWantToPlay)
    {
        do
        {
            /* Select the mode */
            cout << "A quel mode de jeu voulez vous jouer ?" << endl;
            cout << "  1 : mode 1 joueur" << endl << "  2 : mode 2 joueurs" << endl;
            cout << "  q : Quitter le jeu" << endl << endl;
            clearHalfConsole();

            answer = getUserInput();

            if (answer == "Q")
            {
                modeSelected = true;
                stillWantToPlay = false;
                return 0;
            }
            else if (answer == "1")
            {
                if(getWordFromFile(word))
                    modeSelected = true;
            }
            else if (answer == "2")
            {
                clearHalfConsole();
                /* Enter the mysterious word */
                cout << "***** PLAYER 1 ***** " << endl;
                cout << "Saisissez un mot : " << endl;
                word = getUserInput();
                clearConsole();
                cout << "***** PLAYER 2 ***** " << endl;
                modeSelected = true;
            }
            else
            {
                modeSelected = false;
                answer.clear();
                clearConsole();
            }

        } while (!modeSelected /*&& stillWantToPlay*/);

        clearConsole();
        
        /* Ask about the mysterious word */        
        do
        {
            cout << "Quel est ce mot ? " << mixLetters(word) << endl;
            clearHalfConsole();
            answer = getUserInput();

            if (answer != word)
            {
                if (answer == "Q") /* Quit the game */
                {
                    stillWantToPlay = false;
                    clearConsole();
                    return 0;
                }

                /* Wrong word => new guess*/
                clearConsole();
                cout << "Ce n'est pas le bon mot.\n" << endl;
            }
            else
            {
                clearConsole();
                cout << "\n Bravo !" << endl << " Le mot etait : " << word << endl;
                clearHalfConsole();
            }

        } while (answer != word /*&& stillWantToPlay*/);

        /* Try again? */
        cout << "Une autre partie ? (o/n)" << endl;
        answer = getUserInput();

        if (answer == "N")
            stillWantToPlay = false;
        else
            clearConsole();
    }

    return 0;
}
