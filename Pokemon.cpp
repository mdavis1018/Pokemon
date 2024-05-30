/*****************************************
** File:    Pokemon.cpp
** Description: This file implements the Pokemon class and creates functions to access attributes of each pokemon.
***********************************************/

#include "Pokemon.h"
using namespace std;
#include "Pokemon.h"

// Default constructor
Pokemon::Pokemon()
{
  // Initialize member variables to default values
  m_num = 0;
  m_name = "";
  m_CP = 0;
  m_rarity = 0;
}

// Overloaded constructor
Pokemon::Pokemon(int num, string name, int cp, int rarity)
    : m_num(num), m_name(name), m_CP(cp), m_rarity(rarity)
{
  // Member initializer list is used to initialize the member variables
}

// GetCP function
int Pokemon::GetCP()
{
  return m_CP;
}

// GetRarity function
int Pokemon::GetRarity()
{
  return m_rarity;
}

// GetName function
string Pokemon::GetName()
{
  return m_name;
}

// GetNum function
int Pokemon::GetNum()
{
  return m_num;
}

// SetRarity function
void Pokemon::SetRarity(int newRarity)
{
  m_rarity = newRarity;
}

// SetName function
void Pokemon::SetName(string newName)
{
  m_name = newName;
}

// SetCP function
void Pokemon::SetCP(int newCP)
{
  m_CP = newCP;
}

// Train function
void Pokemon::Train(int maxCP)
{
  // Increase m_CP by TRAIN_VALUE without exceeding maxCP
  if (m_CP + TRAIN_VALUE <= maxCP)
  {
    m_CP += TRAIN_VALUE;
  }
  else
  {
    m_CP = maxCP;
  }
}
