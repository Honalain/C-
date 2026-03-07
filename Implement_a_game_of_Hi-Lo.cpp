// Online C++ compiler to run C++ program online
#include <iostream>
#include <limits>

#ifndef RANDOM_MT_H
#define RANDOM_MT_H

#include <chrono>
#include <random>

// This header-only Random namespace implements a self-seeding Mersenne Twister.
// Requires C++17 or newer.
// It can be #included into as many code files as needed (The inline keyword avoids ODR violations)
// Freely redistributable, courtesy of learncpp.com (https://www.learncpp.com/cpp-tutorial/global-random-numbers-random-h/)
namespace Random
{
	// Returns a seeded Mersenne Twister
	// Note: we'd prefer to return a std::seed_seq (to initialize a std::mt19937), but std::seed can't be copied, so it can't be returned by value.
	// Instead, we'll create a std::mt19937, seed it, and then return the std::mt19937 (which can be copied).
	inline std::mt19937 generate()
	{
		std::random_device rd{};

		// Create seed_seq with clock and 7 random numbers from std::random_device
		std::seed_seq ss{
			static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
				rd(), rd(), rd(), rd(), rd(), rd(), rd() };

		return std::mt19937{ ss };
	}

	// Here's our global std::mt19937 object.
	// The inline keyword means we only have one global instance for our whole program.
	inline std::mt19937 mt{ generate() }; // generates a seeded std::mt19937 and copies it into our global object

	// Generate a random int between [min, max] (inclusive)
        // * also handles cases where the two arguments have different types but can be converted to int
	inline int get(int min, int max)
	{
		return std::uniform_int_distribution{min, max}(mt);
	}

	// The following function templates can be used to generate random numbers in other cases

	// See https://www.learncpp.com/cpp-tutorial/function-template-instantiation/
	// You can ignore these if you don't understand them

	// Generate a random value between [min, max] (inclusive)
	// * min and max must have the same type
	// * return value has same type as min and max
	// * Supported types:
	// *    short, int, long, long long
	// *    unsigned short, unsigned int, unsigned long, or unsigned long long
	// Sample call: Random::get(1L, 6L);             // returns long
	// Sample call: Random::get(1u, 6u);             // returns unsigned int
	template <typename T>
	T get(T min, T max)
	{
		return std::uniform_int_distribution<T>{min, max}(mt);
	}

	// Generate a random value between [min, max] (inclusive)
	// * min and max can have different types
        // * return type must be explicitly specified as a template argument
	// * min and max will be converted to the return type
	// Sample call: Random::get<std::size_t>(0, 6);  // returns std::size_t
	// Sample call: Random::get<std::size_t>(0, 6u); // returns std::size_t
	// Sample call: Random::get<std::int>(0, 6u);    // returns int
	template <typename R, typename S, typename T>
	R get(S min, T max)
	{
		return get<R>(static_cast<R>(min), static_cast<R>(max));
	}
}

#endif

int main() {
    //s Write C++ code here
    startGame:
     int secret{Random::get(1, 100)}; //generating Random number!!
    std::cout << "Let's play a game. I'm thinking of a number between 1 and 100. You have 7 tries to guess what it is.\n";
    

    for (int trials{1}; trials <= 7; ++trials)
      {
         //input:
         int choice{};
         std::cout << "Guess #" << trials << ":";
         
         //loop for controlling if user enter non interger input!!
         if (!(std::cin >> choice))
            {
                std::cout<<"Invalid Choice!! \n";
                //goto input;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                //break;
                continue;
            }
       
        
        if(secret > choice)
            std::cout<< "Your guess is low.\n";
        if(secret < choice)
            std::cout << "Your guess is high.\n";
        if(secret == choice)
        {
            std::cout << "Correct! You win!\n";
            
            askingAgain: // this label is used to ask user input when anything else apart from "y" / "n" received!
            continue;
            std::cout << "Would you like to play again (y/n)?";
            char response {};
            std::cin >> response;
            if ((response == 'y') || (response == 'n'))
            {
                
                if (response  == 'y')
                    goto startGame;
                else
                    std::cout <<"Thank you for playing.\n";
                    break;
            }
            else
                goto askingAgain;
                
        }
        if (trials == 7)
        {
            std::cout << "Sorry, you lose. The correct number was " << secret<< ".\n";
            goto askingAgain;
        }
                
        
        
      }
        
    
    return 0;
}
