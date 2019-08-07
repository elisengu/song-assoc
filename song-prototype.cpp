#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

  //RUNTIME: n^2 + # of rounds 
  //# of rounds * O(1)

vector<string> readWords(istream& instream)
{
  string myline;
  vector<string> wordBank;
  //read each line in input file
  while(getline(instream, myline)){
      int size = wordBank.size();
      int i = 0;
      bool duplicate = false;
      //transform to upper case for uniform comparison
      transform(myline.begin(), myline.end(), myline.begin(), ::toupper); 
      //only add unique values to the wordbank
      while(i != size){
        if(myline.compare(wordBank[i]) == 0){
          duplicate = true;
          break;
        }
        ++i;
      }
      if(duplicate == false){
        wordBank.push_back(myline);
      }
  }
  return wordBank;
}

void game(vector<string> wordBank, int numPlayers, map<string, int>& players, int& rounds){
  bool stop = false;
  srand(time(0));
  //Play as many rounds as the user wants
  while(stop == false){
    string input;
    //increase number of rounds (words played)
    ++rounds;
    //generate random number
    int random_no = rand() % wordBank.size();
    cout << endl;
      cout << wordBank[random_no] << endl;
      cout << endl;

    //timer 10 seconds *TODO*

    //Add score to who won this round
      cout << "Who won?" << endl;
      string winner;
      cin >> winner;
      int oldscore = players[winner];
      players[winner] = ++oldscore;
      cout << winner << " won!" << endl;

      //continue playing?
      cout << endl;
      cout << "Keep playing? [y/n]" << endl;
      cin >> input;
      //Quit
      if(input.compare("n") == 0){
        stop = true;
      }
      //Continue...
  }
}

int main(int argc, char* argv[])
{
  if(argc < 2){
    cerr << "Please provide a word bank file" << endl;
    return 1;
  }
  //Take in input file (word bank)
  ifstream ifile(argv[1]);
  if(ifile.fail()){
    cerr << "Unable to open word bank" << endl;
    return 1;
  }
  vector<string> wordBank = readWords(ifile);

  //Configure players
  int numPlayers;
  cout << "How many players?" << endl;
  cin >> numPlayers;
  map<string, int> players;
  for (int i = 0; i < numPlayers; ++i)
  {
    string name;
    int score = 0;
     cout << "What is Player " << i + 1 << "'s name?" << endl;
     cin >> name;
     players.insert(pair<string, int>(name, score));
  }

  //Begin game
  int rounds = 0;
  game(wordBank, numPlayers, players, rounds);
  map<string, int>::iterator it;
  vector<int> scores;
  int max_score = 0;
  //Find max score
  for (it = players.begin(); it != players.end(); ++it)
  {
    cout << it->first << ": " << it->second << " / " << rounds <<  endl;
    scores.push_back(it->second);
    if (it->second > max_score ){
      max_score = it->second;
    }
  }
  //Declare winner
  cout << "\nThe winner is...\n";
  //Display all players with max score
  for (it = players.begin(); it != players.end(); ++it)
  {
    if(it->second == max_score){
      cout << it->first << ": " << it->second << endl;
    }
  }
  return 0;
}
