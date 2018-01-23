//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "wordList.h"

using namespace LanguageGames;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
}

void LanguageGames::MainPage::plainBoxChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{
	std::wstring selectedItem(gameBox->SelectedItem->ToString()->Data());
	int selectedIndex = gameBox->SelectedIndex;

	std::wstring input(inBox->Text->Data());
	int strLen = inBox->Text->Length();

	switch (selectedIndex)
	{
		case 0:
			break;
		case 1:
			outBox->Text = doEncryption(input, strLen);
			break;
		case 2:
			outBox->Text = doTutnese(input, strLen);
			break;
		default:
			outBox->Text = "Not implemented";
			break;
	}
}


/**********************************************************
* For each letter in the input string, if it is a letter, *
* check to see if it's lowercase, and record.             *
* Check to see if a vowel, if not, it's a consonant.      *
* Using the appropriate array (consonant or vowel),       *
* and the number of approriate letter types,              *
* find the encrypted letter and output.                   *
* I.e., the string "ABCD" would come out "ECFH"           *
* (adding 1 to the A to get E, then 1 to B to get C,      *
* then 2 to C to get F, and 3 to D to get H).             *
* Then outputs the complete string.                       *
**********************************************************/
Platform::String^ LanguageGames::MainPage::doEncryption(std::wstring input, int strLen)
{
	int letterPosition = -1;
	int numConst = 1;
	int numVowel = 1;
	char outLetter;

	std::wstring output;

	for (int i = 0; i < strLen; i++)
	{
		if (isalnum(input[i]))
		{
			char transLetter = input[i];
			bool isLower = islower(transLetter);

			if (!isLower)
			{
				transLetter = tolower(transLetter);
			}

			letterPosition = isVowel(transLetter);

			char outLetter;

			// Changing to ">=", fails on "a" otherwise.
			if (letterPosition >= 0)
			{
				int outCode = letterPosition + numVowel;
				for (; outCode > vowels.size() - 1; outCode -= vowels.size());
				outLetter = vowels[outCode];
				numVowel++;
			}
			else
			{
				letterPosition = isConsonant(transLetter);
				int outCode = letterPosition + numConst;
				for (; outCode > consonants.size() - 1; outCode -= consonants.size());
				outLetter = consonants[outCode];
				numConst++;
			}

			if (!isLower)
			{
				outLetter -= 32;
			}

			output += outLetter;
		}
		else
		{
			output += input[i];
		}
	}

	return ref new Platform::String(output.c_str());
}

/*********************************************************
* For each character in the string, save whether or not  *
* the letter is uppercase, then, if it is a consonant,   *
* find the appropriate output word in the tutOut array,  *
* convert to wstring, and add to the output string.      *
* If the character is anything else, simply output it.   *
*********************************************************/
Platform::String^ LanguageGames::MainPage::doTutnese(std::wstring input, int strLen)
{
	std::wstring output;

	for (int i = 0; i < strLen; i++)
	{
		bool isLower = islower(input[i]);
		char toTrans = tolower(input[i]);
		int letterPosition = isConsonant(toTrans);

		if (letterPosition > -1)
		{
			std::string outSTR = tutOut[letterPosition];

			if (!isLower)
			{
				outSTR[0] = toupper(outSTR[0]);
			}

			std::wstring outWSTR;

			output += outWSTR.assign(outSTR.begin(), outSTR.end());
		}
		else
		{
			output += input[i];
		}
	}

	return ref new Platform::String(output.c_str());
}

/******************************************************
* Helper function to find if a letter is a consonant, *
* and what position in the array if it is.            *
******************************************************/
int LanguageGames::MainPage::isConsonant(char toCheck)
{
	for (int i = 0; i < consonants.size(); i++)
	{
		if (consonants[i] == toCheck)
		{
			return i;
		}
	}

	return -1;
}

/**************************************************
* Helper function to find if a letter is a vowel, *
* and what position in the array if it is.        *
**************************************************/
int LanguageGames::MainPage::isVowel(char toCheck)
{
	for (int i = 0; i < vowels.size(); i++)
	{
		if (vowels[i] == toCheck)
		{
			return i;
		}
	}

	return -1;
}