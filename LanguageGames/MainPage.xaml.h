//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace LanguageGames
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		std::array<char, 21> consonants = { 'b','c','d','f','g','h','j','k','l','m','n','p','q','r','s','t','v','w','x','y','z' };
		std::array<char, 5> vowels = { 'a','e','i','o','u' };
		std::array<std::string, 21> tutOut = { std::string("bub"), std::string("cash"), std::string("dud"), std::string("fuf"), std::string("gug"), std::string("hash"), std::string("jay"), std::string("kuck"), std::string("lul"), std::string("mum"), std::string("nun"), std::string("pub"), std::string("quack"), std::string("Rug"), std::string("sus"), std::string("tut"), std::string("vuv"), std::string("wack"), std::string("ex"), std::string("yub"), std::string("zub") };

		void plainBoxChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e);
		Platform::String ^ doEncryption(std::wstring input, int strLen);
		Platform::String ^ doTutnese(std::wstring input, int strLen);
		int isConsonant(char toCheck);
		int isVowel(char toCheck);
	};
}
