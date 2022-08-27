//
// Created by ajay on 8/26/22.
// contains all the game logic
#include "game.h"
#include"my_utilities.h"
#include<iostream>
#include<string>
#include<cassert>

enum class Message
{
    GUESS_TOO_HIGH,
    GUESS_TOO_LOW,
    GUESS_CORRECT,
    WELCOME,
    REPLAY_ASK,
    END_GAME,
};
void print_message(const Message& message,int num_of_tries=0)
{
    switch (message)
    {

        case Message::GUESS_TOO_HIGH:
            std::cout<<"Your guess is too high.\n";
            break;
        case Message::GUESS_TOO_LOW:
            std::cout<<"Your guess is too low.\n";
            break;
        case Message::GUESS_CORRECT:
            std::cout<<"Correct! You've won!\n";
            break;
        case Message::WELCOME:
            std::cout<<"Let's play! I'm thinking of a number. You have "
                     <<num_of_tries<<" tries to guess what it is.\n";
            break;
        case Message::REPLAY_ASK:
            std::cout<<"Would you like to play again?\n";
            break;
        case Message::END_GAME:
            std::cout<<"Bye!\n";
            break;
        default:
            assert(false && "Wrong enumeration constant was passed.");
    }
}
bool ask_for_replay()
{
    print_message(Message::REPLAY_ASK);
    //run loop until the user enters the right character
    while(true)
    {
        std::cout << "Enter Y or N: ";
        switch (get_char())
        {
            case 'y':
            case 'Y':
                return true;
            case 'n':
            case 'N':
                return false;
            default:
                std::cout<<"Please enter only Y or N.\n";
                ignore_line();
        }
    }
}
void init_game(int num_of_tries)
{
    print_message(Message::WELCOME,num_of_tries);
    for(int guess=1;guess<=num_of_tries;++guess)
    {
        int num{get_int("Guess No."+std::to_string(guess))};
        std::cout<<"You entered "<<num<<'\n';
    }
}
void end_game()
{
    print_message(Message::END_GAME);
}
void run_game(int num_of_tries)
{
    /*
    while(true)
    {
        init_game(num_of_tries);
        if(!ask_for_replay())
        {
            end_game();
            return;
        }
    }
     */
    if(ask_for_replay())
        std::cout<<"Play again\n";
    else
        std::cout<<"End game\n";
}