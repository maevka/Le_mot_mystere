#include <iostream>
#include <string>
#include <locale>
#include <ctime>
#include <cstdlib>

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

void clearConsole()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl;
}

void clearHalfConsole()
{
    cout << "\n\n\n\n\n\n\n\n\n\n" << endl;
}

int main()
{
    string word, answer;
    bool stillWantToPlay = true;

    srand(time(0));

    while (stillWantToPlay)
    {
        /* Enter the mysterious word */
        cout << "***** PLAYER 1 ***** " << endl;
        cout << "Saisissez un mot : " << endl;
        cin >> word;
        cin.ignore();
        word = toUppercase(word);

        clearConsole();

        /* Ask about the mysterious word */
        cout << "***** PLAYER 2 ***** " << endl;
        do
        {
            cout << "Quel est ce mot ? " << mixLetters(word) << endl;
            clearHalfConsole();
            cin >> answer;
            cin.ignore();
            answer = toUppercase(answer);

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

        } while (answer != word && stillWantToPlay);

        /* Try again? */
        cout << "Une autre partie ? (o/n)" << endl;
        cin >> answer;
        cin.ignore();

        if (answer == "n" || answer == "N")
            stillWantToPlay = false;
        else
            clearConsole();
    }

    return 0;
}
