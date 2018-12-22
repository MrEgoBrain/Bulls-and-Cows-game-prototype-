/* The game logic (no view code or direct user interaction)
The game is a simple guess the word based on Mastermind
*/

#pragma once
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>

// to make syntax Unreal friendly
#define TMap std::map
using FString = std::string;
using int32 = int;

/* Class for counting right guesses*/
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

const struct FBullCowWordLimits 
{
	int32 ShortestWord = 3;
	int32 LongestWord = 7;
};

/* Storiging errors in guess*/
enum class EGuessStatus 
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase_Latin_Symbols,
};

class FBullCowGame 
{
public:
	FBullCowGame(); //constructor

	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	FString GetHiddenWord() const;

	int32 GetMaxTries() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidiy(FString) const;
	
	void Reset(int32); 
	
	FBullCowCount SubmitValidGuess(FString);


private:
	// see constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;
	
	bool IsIsogram(FString) const;
	bool IsLowercaseLatinSymbols(FString) const;
	FString NewHiddenWord(int32) const;
};

