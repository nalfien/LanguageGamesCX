//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace LanguageGames
{
	/// <summary>
	/// Main Page that shows all output of the games.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		// Updating to use vectors, because they're easier to work with than arrays.
		std::vector<char> consonants = { 'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z' };
		std::vector<char> vowels = { 'a','e','i','o','u' };
		std::vector<char> wordEnds = { '.', '?', '!', ',', '/', '\\' };
		// Shifting to "Long" strings to accomodate wstring.
		std::vector<std::wstring> tutOut = { L"bub", L"cash", L"dud", L"fuf", L"gug", L"hash", L"jay", L"kuck", L"lul", L"mum", L"nun", L"pub", L"quack", L"Rug", L"sus", L"tut", L"vuv", L"wack", L"ex", L"yub", L"zub" };

		void plainBoxChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e);
		Platform::String ^ doEncryption(std::wstring input);
		Platform::String ^ doTutnese(std::wstring input);
		Platform::String ^ doPigLatin(std::wstring input);
		int GetConsonant(char toCheck);
		int GetVowel(char toCheck);
		bool ArrayContains(std::vector<char> haystack, wchar_t needle);
		std::vector<std::wstring> Split(std::wstring sentence, char separator);
		std::wstring STR2WSTR(const char * input);
		std::wstring STR2WSTR(std::string input);
	};
}
