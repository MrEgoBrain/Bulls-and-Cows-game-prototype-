#pragma once
#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(3); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
FString FBullCowGame::GetHiddenWord() const { return MyHiddenWord; }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,9}, { 4,12 }, { 5,15 }, { 6,18 }, { 7,21 } };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset(int32 UserWordLength) //TODO add an int WordLength to all Reset
{
	MyHiddenWord = NewHiddenWord(UserWordLength); //TODO add take UserWordLength and its CheckValidity
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidiy(FString Guess) const
{
	if (!IsLowercaseLatinSymbols(Guess))
	{
		return EGuessStatus::Not_Lowercase_Latin_Symbols;
	}
	else if (!IsIsogram(Guess)) // if guesss insn't an isogram, works only after check for latin symbols 
	{
		return EGuessStatus::Not_Isogram;
	}
	else  if (GetHiddenWordLength() != Guess.length()) // if length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}


// receives a VALID guess, inctements turn, and returns count
// cheks for bulls and cows. Bulls - letter right place, COW - letter wrong place
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	// loop through all letters in the hiddem word
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{	
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{	
			if (Guess[MHWChar] == MyHiddenWord[GChar])
			{
				if (MHWChar == GChar) // if they are in the same place, incrent bulls, else its cows
					BullCowCount.Bulls++;
				else
					BullCowCount.Cows++;
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) // check for game win condition
	{
		bGameIsWon = true;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }//treat 0 and 1 letter words as isogram
	
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercaseLatinSymbols(FString Word) const
{
	for (auto Letter : Word)
	{
		if (Letter > 255 || Letter < 0)
		{
			return false;
		}
		else if (!islower(Letter)) 
		{
			return false;
		}
	}
	return true;
}

FString FBullCowGame::NewHiddenWord(int32 NewWordLength) const //randomise hidden word
{
	const int32 WORDS_IN_LENGTH = 15;
	FString ListOfWords[5][WORDS_IN_LENGTH]{
		"ant", "ape", "one", "any", "bat", "boy", "dog", "cat", "bus", "car", "cup", "dot", "van", "tea", "ten",
		"wage", "walk", "west", "east", "exam", "date", "deal", "deck", "maid", "male", "taxi", "mind", "monk", "muse", "pack",
		"gamer", "globe", "glove", "gnome", "magic", "major", "panel", "paste", "phone", "plant", "radio", "saint", "sauce", "scale", "shark",
		"backer", "binary", "detail", "donate", "double", "fluent", "folder", "abuser", "admire", "absurd", "sailor", "scream", "second", "shadow", "zenith",
		"zonated", "whisper", "wildcat", "workday", "tragedy", "triceps", "trilogy", "painter", "parking", "rebound", "jackpot", "justice", "haircut", "holiday", "implant" };
	srand(time(NULL));
	return ListOfWords[NewWordLength-3][rand() % 15];
}
