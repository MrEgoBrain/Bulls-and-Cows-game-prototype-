/* This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is resonsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void PrintArt();
void PrintWinner();
void PrintLoser();
void PrintGamesSummary();
void PlayGame();
FText GetValidGuess();
int32 GetPreferWordLength();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

int main()	//main module with upper aplication logic
{	
	do {
		PrintIntro();
		PlayGame();
		PrintGamesSummary();
	}
	while (AskToPlayAgain());
	return 0; //return application
}

// block of printing and ASCII art functions
void PrintIntro()
{
	PrintArt();
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	return;
}

void PrintArt() 
{
	std::cout << "                             ******            **  **\n";
	std::cout << "                            /*////**          /** /**\n";
	std::cout << "                            /*   /**  **   ** /** /**  ******\n";
	std::cout << "                            /******  /**  /** /** /** **////\n";
	std::cout << "                            /*//// **/**  /** /** /**//*****\n";
	std::cout << "                            /*    /**/**  /** /** /** /////**\n";
	std::cout << "                            /******* //****** *** *** ******\n";
	std::cout << "                            ///////   ////// /// /// //////\n";
	std::cout << "                                                        **\n";
	std::cout << "        /)  (\\                                         /**\n";
	std::cout << "   .-._((,~~.))_.-,              ******   *******      /**\n";
	std::cout << "    `=.   99   ,=\'              //////** //**///**  ******\n";
	std::cout << "      / ,o~~o. \\                 *******  /**  /** **///**\n";
	std::cout << "     { { .__. } }               **////**  /**  /**/**  /**\n";
	std::cout << "      ) `~~~\\\' (               //******** ***  /**//******\n";
	std::cout << "     /`-._  _\\.-\\                //////// ///   //  //////\n";
	std::cout << "    /         )  \\           ******\n";
	std::cout << "  ,-X        #   X-.        **////**\n";
	std::cout << " /   \\          /   \\      **    //   ******  ***     **  ******\n";
	std::cout << "(     )| |  | |(     )    /**        **////**//**  * /** **////\n";
	std::cout << " \\   / | |  | | \\   /     /**       /**   /** /** ***/**//*****\n";
	std::cout << "  \\_(.-( )--( )-.)_/      //**    **/**   /** /****/**** /////**\n";
	std::cout << "  /_,\\ ) /  \\ ( /._\\       //****** //******  ***/ ///** ******\n";
	std::cout << "      /_,\\  /._\\            //////   //////  ///    /// //////\n";
	std::cout << std::endl;
	return;
}

void PrintWinner()
{
	std::cout << "  ___________\n";
	std::cout << " \'._==_==_=_.\'\n";
	std::cout << " .-\\:      /-.\n";
	std::cout << "| (|:.     |) |\n";
	std::cout << " \'-|:.     |-\'\n";
	std::cout << "   \\::.    /\n";
	std::cout << "    \'::. .\'\n";
	std::cout << "      ) (\n";
	std::cout << "    _.\' \'._\n";
	std::cout << "   `\"\"\"\"\"\"\"`\n";
	std::cout << std::endl << "WINNER, take your trophey, you are great!\n\n";
	return;
}

void PrintLoser()
{
	std::cout << "	  )\n";
	std::cout << "         (.)\n";
	std::cout << "         .|.\n";
	std::cout << "         | |\n";
	std::cout << "     _.--| |--._\n";
	std::cout << "  .-\';  ;`-\'& ; `&.\n";
	std::cout << " & &  ;  &   ; ;   \\\n";
	std::cout << " \\      ;    &   &_/\n";
	std::cout << "  F\"\"\"---...---\"\"\"J\n";
	std::cout << "  | | | | | | | | |\n";
	std::cout << "  J | | | | | | | F\n";
	std::cout << "   `---.|.|.|.---\'\n";
	std::cout << std::endl << "LOST, it was \"" << BCGame.GetHiddenWord() << "\", but dont be upset.\nTake this cupcake and may be try one more time?\n\n";
	return;
}

void PrintGamesSummary()
{
	if (BCGame.IsGameWon()) 
		PrintWinner();
	else
		PrintLoser();
	return;
}

void PlayGame() // plays a single game
{	
	
	BCGame.Reset(GetPreferWordLength());	//TODO add word lenth chose
	int32 MaxTries = BCGame.GetMaxTries();
	
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << "; Cows = " << BullCowCount.Cows << std::endl << std::endl;
	}
	return;
}

//loop continually until the user gives a valid guess, printing what mistake user has in guessa 
FText GetValidGuess()  
{	
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText Guess = "";
	do 
	{	
		Guess = "";
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of "<< BCGame.GetMaxTries() << ". Enter your guess: ";
		getline(std::cin, Guess);
	
		Status = BCGame.CheckGuessValidiy(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters. \n\n";
			break;
		case EGuessStatus::Not_Lowercase_Latin_Symbols:
			std::cout << "Please enter a word without uppercase not latin letters. \n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}		
	} while (Status != EGuessStatus::OK); 
	return Guess;
}

int32 GetPreferWordLength()
{
	const int32 ASCII_POINTER = 48;
	FText WordLength = "";
	int32 ValidWordLength = 0;
	std::cout << "Isogram word of how many letters do you want me to guess?\n";
	do
	{
		std::cout << "Please enter only digits from 3 to 7\n";
		getline(std::cin, WordLength);
		std::cout << std::endl;
	} while ((ValidWordLength = WordLength[0] - ASCII_POINTER) <3 || ValidWordLength>7); // convert user input to int digit and looping until its valid
	return ValidWordLength;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (Y/N) :";
	FText Response = "";
	getline(std::cin, Response);
	std::cout << std::endl;
	return (Response[0] == 'y') || (Response[0] == 'Y') ;
}
