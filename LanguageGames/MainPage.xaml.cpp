//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"

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

struct WordNode;

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
			outBox->Text = doEncryption(input);
			break;
		case 2:
			outBox->Text = doTutnese(input);
			break;
		case 3:
			outBox->Text = doPigLatin(input);
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
Platform::String^ LanguageGames::MainPage::doEncryption(std::wstring input)
{
	int letterPosition = -1;
	int numConst = 1;
	int numVowel = 1;
	char outLetter;

	std::wstring output;

	for (int i = 0; i < input.length(); i++)
	{
		if (isalpha(input[i]))
		{
			char transLetter = input[i];
			bool isLower = islower(transLetter);

			if (!isLower)
			{
				transLetter = tolower(transLetter);
			}

			letterPosition = GetVowel(transLetter);

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
				letterPosition = GetConsonant(transLetter);
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
Platform::String^ LanguageGames::MainPage::doTutnese(std::wstring input)
{
	std::wstring output;

	for (int i = 0; i < input.length(); i++)
	{
		bool isLower = islower(input[i]);
		char toTrans = tolower(input[i]);
		int letterPosition = GetConsonant(toTrans);

		if (letterPosition > -1)
		{
			std::wstring outSTR = tutOut[letterPosition];

			if (!isLower)
			{
				outSTR[0] = toupper(outSTR[0]);
			}

			output += outSTR;
		}
		else
		{
			output += input[i];
		}
	}

	return ref new Platform::String(output.c_str());
}

/**************************************************************
* Split the input into words. For each word, find two things: *
* 1) The position of the first consonant in the word (if any) *
* 2) The last position of a "word ender" piece of punctuation *
*        (i.e., a comma, period, and so on)                   *
* Split the word into three pieces: pre-vowel, post-vowel,    *
* and punctuation. Add "ay" if the word starts with a         *
* consonant, "yay" if it doesn't, then put the word back      *
* together as post-vowel, pre-vowel, punctuation.             *
**************************************************************/
Platform::String^ LanguageGames::MainPage::doPigLatin(std::wstring input)
{
	if (input.size() == 0)
	{
		return "";
	}

	std::wstring output;

	std::vector<std::wstring> sentence = Split(input, ' ');

	for (std::wstring& currWord : sentence)
	{
		bool isUpper = false;

		if (isalpha(currWord[0]) && isupper(currWord[0]))
		{
			isUpper = true;
			currWord[0] = tolower(currWord[0]);
		}

		int i = 0;
		int j = currWord.size() - 1;

		for (; i < currWord.size() && !ArrayContains(vowels, currWord[i]); i++);
		for(; j >= 0 && ArrayContains(wordEnds, currWord[j]); j--);

		std::wstring punct;

		if (j > 0 || (currWord.size() > 1) && ArrayContains(wordEnds, currWord[1]))
		{
			punct = currWord.substr(j + 1, currWord.size() - 1);
			currWord.erase(j + 1, currWord.size() - 1);
		}

		if (i > 0)
		{
			std::wstring preVowel = currWord.substr(0, i);
			currWord.erase(0, i);
			currWord += preVowel + L"ay";
		}
		else if (currWord != std::wstring())
		{
			currWord += L"yay";
		}

		if (isUpper)
		{
			currWord[0] = toupper(currWord[0]);
		}

		output += L" " + currWord + punct;
	}

	return ref new Platform::String(output.c_str());
}

/******************************************************
* Helper function to find if a letter is a consonant, *
* and what position in the array if it is.            *
******************************************************/
int LanguageGames::MainPage::GetConsonant(char toCheck)
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
int LanguageGames::MainPage::GetVowel(char toCheck)
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

bool LanguageGames::MainPage::ArrayContains(std::vector<char> haystack, wchar_t needle)
{
	for (int i = 0; i < haystack.size(); i++)
	{
		if (haystack[i] == needle)
		{
			return true;
		}
	}

	return false;
}

/**************************************************************
* String splitter. Finds each instance of a separator,        *
* and splits each piece into a different element of a vector. *
**************************************************************/
std::vector<std::wstring> LanguageGames::MainPage::Split(std::wstring sentence, char separator)
{
	std::vector<std::wstring> output;
	output.resize(std::count(sentence.begin(), sentence.end(), separator) + 1);

	size_t pos = 0;
	for (int i = 0; (pos = sentence.find(separator)) != std::wstring::npos; i++)
	{
		output[i] = sentence.substr(0, pos);
		sentence.erase(0, pos + 1);
	}

	output[output.size() - 1] = sentence;

	return output;
}