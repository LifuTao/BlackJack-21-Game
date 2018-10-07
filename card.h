#pragma once
// Card Class


#include <cstdlib> //provides size_t
#include <stdexcept> //provides runtime errors
#include <string>

class Card {
public:
	// card constructor
	Card(std::string suit_value_0, std::string face_value_0, int integer_value_0);
	
	//get suit_value method
	std::string get_suit();// (s)pade, (d)iamond,(c)lover,(h)eart
	//get face_value method
	std::string get_face(); // A,2,3,...10,J,Q,K 
	//get integer value method
	std::string get_card();
	// return the concatenation of suit and face
	int get_integer_value();
	
private:
	std::string suit_value, face_value;
	int integer_value;
};
// acts on bags but doesn't need access to private attributes

//Implementation of Card class methods







