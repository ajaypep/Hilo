//
// Created by ajay on 8/26/22.
//
#include "game.h"
#include"my_utilities.h"
#include"hilo_config.h"
#include<iostream>
#include<string>
#include<cassert>
#include <iomanip>

static constexpr int HILO_UPPER_BOUND = 100;
static constexpr int MAX_TRIES = 7;
enum class Message
{
    GUESS_TOO_HIGH,
    GUESS_TOO_LOW,
    GUESS_CORRECT,
    TRIES_EXHAUSTED,
    WELCOME,
    REPLAY_ASK,
    END_GAME,
};

static void print_message(const Message& message)
{
    switch (message)
    {

        case Message::GUESS_TOO_HIGH:
            std::cout << "Your guess is too high.\n";
            break;
        case Message::GUESS_TOO_LOW:
            std::cout << "Your guess is too low.\n";
            break;
        case Message::GUESS_CORRECT:
            std::cout << "Correct! You've won!\n";
            break;
        case Message::TRIES_EXHAUSTED:
            std::cout << "You've ran out of tries. GAME OVER.\n";
            break;
        case Message::WELCOME:
            std::cout << "Let's play! I'm thinking of a number from 1-"
                      << HILO_UPPER_BOUND << ". You have "
                      << MAX_TRIES << " tries to guess what it is.\n";
            break;
        case Message::REPLAY_ASK:
            std::cout << "Would you like to play again?\n";
            break;
        case Message::END_GAME:
            std::cout << "Bye!\n";
            break;
        default:
            assert(false && "Wrong enumeration constant was passed.");
    }
}

static bool ask_for_replay()
{
    print_message(Message::REPLAY_ASK);
    while (true)
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
                std::cout << "Please enter only Y or N.\n";
                ignore_line();
        }
    }
}

static void init_game()
{
    print_message(Message::WELCOME);
    const int random_num{get_random_int(1, 100)};
    for (int guess = 1; guess <= MAX_TRIES; ++guess)
    {
        int user_guess{get_int("Guess No." + std::to_string(guess))};
        if (user_guess > random_num)
        {
            print_message(Message::GUESS_TOO_HIGH);
        } else if (user_guess < random_num)
        {
            print_message(Message::GUESS_TOO_LOW);
        } else
        {
            print_message(Message::GUESS_CORRECT);
            return;
        }
    }
    print_message(Message::TRIES_EXHAUSTED);
}

static void end_game()
{
    print_message(Message::END_GAME);
}

static void print_version_and_usage()
{
    std::cout << "Hilo v" << Hilo_VERSION_MAJOR << '.'
              << Hilo_VERSION_MINOR << '.' << Hilo_VERSION_PATCH << '\n';
    std::cout << "Usage: hilo\n"
              << std::setw(16) << "hilo run\n";
}

void run_game(bool print_info)
{
    if(print_info)
    {
        print_version_and_usage();
        return;
    }
    while (true)
    {
        init_game();
        if (!ask_for_replay())
        {
            end_game();
            return;
        }
    }
}