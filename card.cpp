#include <iostream>
#include "card.h"


Card::Card(std::string suit_value_0, std::string face_value_0, int integer_value_0)
{
	suit_value = suit_value_0; // Clover, Heart, Spade, Diamond
	face_value = face_value_0; // A,2,3,4,...10, J,Q,K
	integer_value = integer_value_0;
}


std::string Card::get_suit()
{
	return suit_value; // Spade, Heart, Clover, Diamond
}
std::string Card::get_face()
{
	return face_value; // A,2,3,4
}
std::string Card::get_card()
{
	return suit_value + face_value;
}
int Card::get_integer_value()
{
	return integer_value;
}


