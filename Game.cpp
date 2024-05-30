/*****************************************
** File:    Game.cpp
** Description: This file implements the Game class and uses functions to build the core game logic.
***********************************************/

#include "Game.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Game::Game(string filename) : m_filename(filename)
{
  // Name: Game Constructor
  // Desc - Sets m_filename based on string passed
  // Preconditions - Input file passed
  // Postconditions - m_filename updated
}

void Game::LoadFile()
{
  // Name: LoadFile
  // Desc - Opens file and reads in each Pokemon into m_PokeDex
  // Preconditions - Input file passed and populated with Pokemon
  // Postconditions - m_pokeDex populated with Pokemon

  // Opens file and reads in each Pokemon into m_PokeDex
  ifstream file(m_filename);
  if (!file.is_open())
  {
    cerr << "Unable to open file: " << m_filename << endl;
    return; // return if file cannot be opened
  }

  int num, cp, rarity;
  string name;
  int index = 0;

  // Loop through each line in the file, extracting Pokemon attributes and creating Pokemon objects/instances
  while (file >> num >> name >> cp >> rarity)
  {
    Pokemon newPokemon(num, name, cp, rarity);
    m_pokeDex[index] = newPokemon; // Store the Pokemon object in the array
    index++;
  }

  cout << "Successfully loaded " << index << " Pokemon into the PokeDex." << endl;
  file.close(); // Close the file after reading is complete
}

void Game::DisplayPokeDex()
{
  // Name: DisplayPokeDex
  // Desc - Display all Pokemon in the m_pokeDex
  // Preconditions - m_pokeDex populated with Pokemon
  // Postconditions - None

  for (int i = 0; i < TOTAL_POKEMON; i++)
  {
    cout << m_pokeDex[i].GetNum() << ". " << m_pokeDex[i].GetName() << endl;
  }
}

void Game::DisplayTeam()
{
  // Name: DisplayTeam
  // Desc - Iterates through m_team to display information about team
  // Preconditions - m_team exists
  // Postconditions - None

  int teamSize = TeamSize(); // Get the current size of the team

  // Check if the team is empty
  if (teamSize == 0)
  {
    cout << "You have no team yet. Maybe search for a Pokemon?" << endl;
    return; // Exit the function if there are no Pokémon in the team
  }

  // Display team information, including position, name, CP, and rarity for each Pokemon
  cout << "Your Team:" << endl;
  cout << left << setw(NUM_WIDTH) << "Pos" << setw(NAME_WIDTH) << "Name"
       << setw(NUM_WIDTH) << "Num" << setw(NUM_WIDTH) << "CP"
       << "Rarity" << endl;

  // Iterate through the team array and display each Pokémon's details with its position
  for (int i = 0; i < teamSize; i++)
  {
    cout << left << setw(NUM_WIDTH) << i + 1 // Display position starting from 1
         << setw(NAME_WIDTH) << m_team[i].GetName()
         << setw(NUM_WIDTH) << m_team[i].GetNum()
         << setw(NUM_WIDTH) << m_team[i].GetCP()
         << m_team[i].GetRarity() << endl;
  }
}

int Game::CatchMenu()
{
  // Name: CatchMenu
  // Desc - User chooses which rarity of Pokemon to try and catch
  // Preconditions - m_pokeDex has rarities of 1-3
  // Postconditions - Returns choice of 1-3

  int choice = 0;
  do
  {
    // Prompt user to choose a Pokemon rarity to attempt to catch
    cout << "What rarity of Pokemon would you like to catch?:" << endl;
    cout << "1. Common (High Probability)" << endl;
    cout << "2. Uncommon (Normal Probability)" << endl;
    cout << "3. Ultra Rare (Extremely Low Probability)" << endl;
    cin >> choice;
    if (cin.fail())
    {
      cout << "Invalid input. Please enter a number." << endl;
      choice = 0; // Reset choice to force loop continuation
    }
    // Check for valid int input range
    else if (choice < 1 || choice > 3)
    {
      cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
    }
  } while (choice < 1 || choice > 3); // re-prompt if out of range
  return choice;
}

void Game::CatchPokemon()
{
  // Name: CatchMenu
  // Desc - User chooses which rarity of Pokemon to try and catch
  // Preconditions - m_pokeDex has rarities of 1-3
  // Postconditions - Returns choice of 1-3

  int choice = CatchMenu(); // Use CatchMenu to get the user's choice of rarity
  FoundPokemon(choice);     // Attempt to catch pokemon
}

int Game::FindPokemon(string name)
{
  // Name: FindPokemon
  // Desc - Iterates through m_pokeDex to see if matching name exists
  //        Returns index if found else -1
  // Preconditions - m_pokeDex exists
  // Postconditions - Returns index of match, else -1

  // Iterate through the m_pokeDex array
  for (int i = 0; i < TOTAL_POKEMON; i++)
  {
    // Compare the current Pokemon's name with the name passed to the function
    // Use .compare() for string comparison, which returns 0 if strings are equal
    if (m_pokeDex[i].GetName().compare(name) == 0)
    {
      return i; // If found, return the current index
    }
  }
  return -1; // If no match is found, return -1
}

Pokemon Game::FoundPokemon(int rarity)
{
  // Name: FoundPokemon
  // Desc - Based on rarity passed in, randomly chooses one Pokemon
  //        from the m_pokeDex, updates the CP, and adds to m_team
  // Preconditions - m_pokeDex has maximum CP for Pokemon
  // Postconditions - After random Pokemon of that rarity is chosen,
  //                  this function reduces the CP of between 30-50%
  //                  and adds to m_team

  int count = 0; // Initialize count here to avoid redeclaration later

  cout << "You start to search" << endl;

  if (rarity == 1)
  {
    int chanceOfFind = rand() % 100;
    if (chanceOfFind < COMMON) // 45% chance a num 0-99 is < 45
    {
      for (int i = 0; i < TOTAL_POKEMON; i++)
      {
        // Count how many rarity 1 pokemon
        if (m_pokeDex[i].GetRarity() == rarity)
        {
          count++;
        }
      }
    }
    else
    {
      // If no common Pokemon is found, inform the user and return a default Pokemon
      cout << "No common Pokémon found." << endl;
      return Pokemon();
    }
  }
  else if (rarity == 2)
  {
    int chanceOfFind = rand() % 100;
    if (chanceOfFind < UNCOMMON) // 25% chance
    {
      for (int i = 0; i < TOTAL_POKEMON; i++)
      {
        // count how many rarity 2 pokemon
        if (m_pokeDex[i].GetRarity() == rarity)
        {
          count++;
        }
      }
    }
    else
    {
      cout << "No Uncommon Pokémon found." << endl;
      return Pokemon();
    }
  }
  else if (rarity == 3)
  {
    int chanceOfFind = rand() % 100;
    if (chanceOfFind < ULTRA) // 1% chance
    {
      for (int i = 0; i < TOTAL_POKEMON; i++)
      {
        // count the number of pokemon with rarity 3
        if (m_pokeDex[i].GetRarity() == rarity)
        {
          count++;
        }
      }
    }
    else
    {
      cout << "No Rare Pokémon Found." << endl;
      return Pokemon();
    }
  }
  // randly select one of the counted pokemon
  int randomCount = rand() % count;
  int selectedCount = 0;

  // Iterate to find and return the randomly selected Pokémon
  for (int i = 0; i < TOTAL_POKEMON; i++)
  {
    if (m_pokeDex[i].GetRarity() == rarity)
    {
      if (selectedCount == randomCount)
      {
        // Adjust CP of the selected Pokemon by reducing it between 30% to 50%
        int originalCP = m_pokeDex[i].GetCP();
        int reductionPercentage = rand() % 21 + 30; // Randomly choose between 30% and 50%
        int reducedCP = originalCP * (100 - reductionPercentage) / 100;

        // Create a new Pokemon with the adjusted CP and add it to the team
        Pokemon caughtPokemon = m_pokeDex[i]; // Copy the Pokémon
        caughtPokemon.SetCP(reducedCP);       // Modify its CP

        cout << "You found a " << caughtPokemon.GetName() << endl;
        cout << "You caught a " << caughtPokemon.GetName() << " with CP: " << caughtPokemon.GetCP() << "!" << endl;
        AddPokemon(caughtPokemon); // Add the modified Pokemon to the team

        return caughtPokemon; // Return the modified Pokémon
      }
      selectedCount++; // Increment selectedCount to go through pokemon of chosen rarity
    }
  }

  // In case something goes wrong, return a default "null" Pokémon
  return Pokemon();
}

void Game::TrainPokemon()
{
  // Name: TrainPokemon
  // Desc - If m_team size is 0. If 0, tells user and returns to main menu
  //        If m_team size > 0, displays team (DisplayTeam)
  //        Asks user to chose one team member
  //        Calls Train on chosen team member and passes corresponding CP
  //             value from m_pokeDex (m_pokeDex holds max CP for all)
  // Preconditions - m_team and m_pokeDex exists
  // Postconditions - Calls Train on chosen team

  // Check if there are any Pokémon in the team
  int teamSize = TeamSize();
  if (teamSize == 0)
  {
    // If team is empty, notify the user and exit the function

    cout << "Your team is currently empty." << endl;
    return;
  }

  // Display the team for the user to choose a Pokémon to train
  DisplayTeam();

  int choice = -1;          // Initialize choice to an invalid value
  bool validChoice = false; // Flag to track whether the user has made a valid choice

  // Prompt the user until a valid Pokemon is selected
  while (!validChoice)
  {
    cout << "Choose a Pokemon to train (enter the number): ";
    if (cin >> choice)
    {
      choice--; // Adjust for array indexing

      // Check if the choice is within the range of the team size
      if (choice >= 0 && choice < teamSize)
      {
        validChoice = true; // Valid choice made, exit loop
      }
      else
      {
        cout << "Invalid choice. Please enter a number between 1 and " << teamSize << "." << endl;
      }
    }
    else
    {
      cout << "Invalid input. Please enter a number." << endl;
    }
  }

  // At this point, 'choice' is valid
  // Get the Pokémon's current and maximum CP
  int currentCP = m_team[choice].GetCP();
  int pokeDexNum = m_team[choice].GetNum();      // The Pokemon's number in the PokeDex
  int maxCP = m_pokeDex[pokeDexNum - 1].GetCP(); // Get the max CP from PokeDex (adjusting for index)

  // Calculate a random increase in CP, ensuring it doesn't exceed the Pokemon's maxCP
  int increase = rand() % (maxCP - currentCP + 1);
  if (currentCP + increase > maxCP)
  {
    increase = maxCP - currentCP; // Cap the increase to not exceed maxCP
  }

  // Train the Pokémon-Apply the CP increase to the selected Pokemon

  m_team[choice].SetCP(currentCP + increase);

  cout << m_team[choice].GetName() << " has been trained! New CP: " << m_team[choice].GetCP() << endl;
}

void Game::AddPokemon(Pokemon newPokemon)
{
  // Name: AddPokemon
  // Desc - Figures out where to insert newly found Pokemon
  //        If m_team has opening, inserts into first open slot
  //        If m_team is full, inserts into first slot with lower CP
  //        If m_team is full, and new Pokemon has lower CP, does not insert
  //        Tells user if not inserted
  // Preconditions - None
  // Postconditions - New Pokemon is added to m_team if possible
  //                  or user is notified that there is no room

  int openSlot = -1;         // Index of an open slot or slot with lower CP, initialize to -1 indicating not found
  bool replaced = false;     // Boolean Flag to indicate if a Pokemon has been replaced in the team.
  bool slotFound = false;    // Boolean Flag to control the loop, true if a suitable slot is found.
  int teamSize = TeamSize(); // Get the current size of the team

  // Iterate to find an open slot or, if the team is full, a slot with a lower CP Pokémon
  for (int i = 0; i < NUM_TEAM && !slotFound; i++)
  {
    if (m_team[i].GetName().empty())
    {
      openSlot = i;     // Found an open slot
      slotFound = true; // Set flag to true to exit the loop
    }
    else if (teamSize == NUM_TEAM && m_team[i].GetCP() < newPokemon.GetCP())
    {
      // Team is full but found a Pokemon with lower CP, mark for replacement.
      openSlot = i;     // Found a slot with a lower CP Pokémon
      replaced = true;  // Indicate that we're replacing due to lower CP
      slotFound = true; // Assuming you want to replace immediately upon finding a weaker Pokémon
    }
  }

  // If an open slot or replaceable slot is found
  if (openSlot != -1)
  {
    // A slot is found for the new Pokemon, either open or for replacement.
    m_team[openSlot] = newPokemon; // Add or replace the Pokémon in the team
    if (replaced)
    {
      cout << newPokemon.GetName() << " has been added to your team, replacing a weaker Pokémon." << endl;
    }
    else
    {
      cout << newPokemon.GetName() << " has been added to your team in an open slot." << endl;
    }
  }
  else
  {
    // No open slots and no lower CP Pokémon to replace
    cout << "Your team is full. " << newPokemon.GetName() << " could not be added as there are no weaker Pokémon to replace." << endl;
  }
}

void Game::BattlePokemon()
{
  // Name: BattlePokemon
  // Desc - If m_team size is 0. If 0, tells user and returns to main menu
  //        If m_team size > 0, randomly chooses Pokemon to fight from
  //        m_pokeDex. Asks which team member to use in battle.
  //        Random enemy has a CP of 0 - max CP + 200.
  //        Compares CP for random enemy and team member.
  //        If team member wins, indicates and returns to main menu
  //        If team member loses, indicates, sets CP to 0, returns to menu
  // Preconditions - m_team exists
  // Postconditions - Either the player wins or team member's CP is set to 0

  // First, check the player's team size to ensure there are Pokemon available for battle.
  int teamSize = TeamSize();
  if (teamSize == 0)
  {
    cout << "Your team is empty." << endl;
    return;
  }

  // Randomly choose an opponent Pokémon
  int randOppIndex = rand() % TOTAL_POKEMON;           // random index
  int randOppMaxCP = m_pokeDex[randOppIndex].GetCP();  // gets the CP of randomly selected enemy pokemon
  int randOppCP = rand() % (randOppMaxCP + ENEMY_ADD); // assigns new CP between 0 and Max CP + 200

  // Inform the player about the opponent Pokemon and its CP.
  cout << "You are going to fight " << m_pokeDex[randOppIndex].GetName() << " with CP: " << randOppCP << endl;

  // Display team and prompt user to choose a Pokémon
  DisplayTeam();
  int choice = -1;          // Initialize choice to an invalid value to start the selection process.
  bool validChoice = false; // Boolean flag for tracking if a valid choice is made

  // Loop for proper input validation
  while (!validChoice)
  {
    cout << "Choose one of your Pokémon to battle (enter the number): ";
    cin >> choice;
    choice--; // adjust for arr indexing accuracy
    if (cin.fail())
    {
      cout << "Invalid input. Please enter a valid number." << endl;
    }
    else if (choice >= 0 && choice < teamSize)
    {
      validChoice = true; // Valid choice made, exit loop
    }
    else
    {
      // Choice is out of bounds.
      cout << "Invalid choice. Please enter a number between 1 and " << teamSize << "." << endl;
    }
  }

  // Compare the CPs of the chosen Pokemon and the opponent to determine the battle outcome.
  if (m_team[choice].GetCP() >= randOppCP) // Player's Pokemon wins if its CP is higher.
  {
    cout << m_team[choice].GetName() << " wins the battle!" << endl;
  }
  else
  {
    cout << "Your " << m_team[choice].GetName() << " loses the battle and faints!" << endl;
    m_team[choice].SetCP(0); // Set CP to 0 since the Pokémon lost
    cout << "You shoudld replace it " << endl;
  }
}

int Game::TeamSize()
{
  // Name: DisplayTeam
  // Desc - Iterates through m_team to display information about team
  // Preconditions - m_team exists
  // Postconditions - None

  int size = 0; // Initialize a counter to track the number of Pokemon in the team.

  // Loop through the team array to count the number of non-empty Pokemon names.
  for (int i = 0; i < NUM_TEAM; i++)
  {
    // Assuming a valid Pokemon has a non-empty name
    if (!m_team[i].GetName().empty())
    {
      size++;
    }
  }
  return size; // Return the total count of Pokemon in the player's team.
}

void Game::MainMenu()
{
  // Name: MainMenu
  // Desc - Displays main menu
  // Preconditions - m_pokeDex populated
  // Postconditions - Keeps calling until quit chosen

  int choice = 0; // Variable to store the user's menu choice

  do
  {
    // Display the main menu options to the user
    cout << "What would you like to do?:" << endl;
    cout << "1. Display Complete PokeDex" << endl;
    cout << "2. Display your Team" << endl;
    cout << "3. Search for a new Pokemon" << endl;
    cout << "4. Battle your Pokemon" << endl;
    cout << "5. Train your Pokemon" << endl;
    cout << "6. Exit" << endl;

    // Get the user's choice
    cin >> choice;

    // Process the user's choice
    switch (choice)
    {
    case 1:
      DisplayPokeDex(); // Display the complete PokeDex.
      break;
    case 2:
      DisplayTeam(); // Display the user's current team of Pokemon.
      break;
    case 3:
      CatchPokemon(); // Initiate Pokemon catching sequence.
      break;
    case 4:
      BattlePokemon(); // Initiate a Pokemon battle.
      break;
    case 5:
      TrainPokemon(); // Train a Pokemon to increase its CP.
      break;
    case 6:
      cout << "Exiting the game. Goodbye!" << endl;
      break;
    default:
      cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
      break;
    }
  } while (choice != 6); // Continue until the user inputs '6' to exit
}

void Game::Start()
{
  // Name: Start
  // Desc - Calls LoadFile then MainMenu
  // Preconditions - m_fileName is populated
  // Postconditions - Exits game when done running

  LoadFile(); // Load Pokemon data into PokeDex from the file.
  MainMenu(); // Display the main menu and start the game loop.
}
