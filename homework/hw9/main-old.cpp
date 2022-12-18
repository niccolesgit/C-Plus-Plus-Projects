#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <cassert>
#include <utility>

#include "ds_hashset.h"
#include "Movie.h"

class hash_string_obj {
public:
 // from http://www.partow.net/programming/hashfunctions/ modified from the 
 // JS hash function by Justin Sobel
  unsigned int operator() ( const std::string& key ) const {
    unsigned int hash = 1315423911;
    for(unsigned int i = 0; i < key.length(); i++)
      hash ^= ((hash << 5) + key[i] + (hash >> 2));
    return hash;
  }   
};
//typedef ds_hashset<pair
typedef ds_hashset<Movie, hash_string_obj> hashtable;

int main() {
  //variables for the input
  std::string command, title, year, min, id, actor;
  std::vector<std::string> genres, ids, roles;
  std::map<std::string, std::string> actors;
  std::vector<Movie> orig_movies;//vector of parent(full) movies
  int table_size = 100;
  float occupancy = .5;
  std::cin >> command;

  while(command != "movies"){//checks if the table size and the occupancy are given 
    if(command == "table_size"){
      std::cin >> table_size;
    }
    std::cin >> command;
    if(command == "occupancy"){
      std::cin >> occupancy;
    }
  }
  hashtable movies(table_size);//creates the table
  movies.setOccupancy(occupancy);//sets the occupancy
  //file of full movies
  if(command == "movies"){
    std::string movie_file;
    std::cin >> movie_file;
    std::ifstream in_movies(movie_file);
    if(!in_movies.is_open()){
      std::cerr << movie_file << " cannot be opened. \n";
    }
    int parent = 0;//holds index
    //gets each movies information
    while(in_movies >> title >> year >> min){
      std::vector<std::string> genres, ids, roles;
      int genre_count, id_count, role_count;
      in_movies >> genre_count;
      std::string genre;
      for(int i = 0; i < genre_count; i++){
        in_movies >> genre;
        genres.push_back(genre);//stores each genre
      }
      in_movies >> id_count;
      for(int i = 0; i < id_count; i++){
        in_movies >> id;
        ids.push_back(id);//stores all ids
      }
      in_movies >> role_count;
      for(int i = 0; i < role_count; i++){
        std::string role;
        in_movies >> role;
        roles.push_back(role);//stores all roles;
      }
      //creates a movie object
      Movie current(title, year, min, genres,ids, roles, 0);
      orig_movies.push_back(current);//stores all movies in vector
      //index of which parent movie in vector 
      parent++;
      //start of making partials for each parent(full) movie
      std::string p_title, p_year, p_min;
      std::vector<std::string> p_genres, p_ids, p_roles;
      //creates 64 different possible combinations by either adding 
      //variable or not adding it to movie
      for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
          for(int k = 0; k < 2; k++){
            for(int l = 0; l < 2; l++){
              for(int m = 0; m < 2 ; m++){
                for(int n = 0; n < 2; n++){
                  if(i == 0){
                    p_title = "?";//no title
                  }
                  if(i == 1){
                    p_title = title;//add title
                  }
                  if(j == 0){
                    p_year = "?";//no year
                  }
                  if(j == 1){
                    p_year = year;//add year
                  }
                  if(k == 0){
                    p_min = "?";//no minutes
                  }
                  if(k == 1){
                    p_min = min;//add minutes
                  }
                  if(l == 0){
                    p_genres.clear();//no genres
                  }
                  if(l == 1){
                    p_genres.clear();//reset genres for each partial
                    for(int i = 0; i < genres.size(); i++){
                      p_genres.push_back(genres[i]);//add genres
                    }
                  }
                  if(m == 0){
                    p_ids.clear();//no ids
                  }
                  if(m == 1){
                    p_ids.clear();//reset ids for each partial
                    for(int i = 0; i < ids.size(); i++){
                      p_ids.push_back(ids[i]);//add partials
                    }
                  }
                  if(n == 0){
                    p_roles.clear();//no roles
                  }
                  if(n == 1){
                    p_roles.clear();//reset roles for each partial
                    for(int i = 0; i < roles.size(); i++){
                      p_roles.push_back(roles[i]);//add roles
                    }
                  }
                  //create movie object of each partial movie
                  Movie parents(p_title, p_year, p_min, p_genres,
                   p_ids, p_roles, parent);//last parameter holds index of parent movie
                  //insert each partial into table(includes full movie)
                  movies.insert(parents);
                }
              }
            }
          }
        }
      }
    }
  }
  std::cin >> command; 
  if( command == "actors"){
      std::string actors_file;
      std::cin >> actors_file;//get actor file
      std::ifstream in_actors(actors_file);
  if(!in_actors.is_open()){
      std::cerr <<"Can't open.\n";//if file can't be opened
      exit(1);
  }
  while(in_actors >> id >> actor){
      actors[id] = actor;//read file input into a map of ids and actors
    }
  }
  //read in queries
  while(true){
    //query input variables
    std::string q_title, q_year, q_min;
    std::vector<std::string> q_genres, q_ids, q_roles;
    int num;
    std::string input;
    std::cin >>command;
    //ends the loop at the end of input file queries
    if(command == "quit"){
      break;
    }
    //gets all input for queries
    if(command == "query"){
      std::cin >> q_title >> q_year >> q_min >> num;
      for(int i = 0; i < num; i++){
        std::cin >> input;
        q_genres.push_back(input);//store genres
      }
      std::cin >> num;
      for(int i = 0; i < num; i++){
        std::cin >> input;
        q_ids.push_back(input);//store ids
      }
      std::cin >> num;
      for(int i = 0; i < num; i++){
        std::cin >> input;
        q_roles.push_back(input);//store roles
      }
      //create a movie object for queries
      Movie query(q_title, q_year, q_min, q_genres, q_ids, q_roles, 0);
      std::list<Movie> answer;
      answer = movies.find(query); //find all movies that match query
      //checks if there were any matches
      if(answer.size() != 0){
        std::list<Movie>::const_iterator iter;
        std::vector<std::string> parent_genres, parent_ids, parent_roles;
        //print how many movies matched the query
        std::cout << "Printing " << answer.size() << " result(s):" << std::endl;
        //goes through list of movies and prints information from original movie vector
        for(iter = answer.begin(); iter != answer.end(); iter++){
          std::cout << orig_movies[(iter->getParent())-1].getTitle()<<std::endl;
          std::cout << orig_movies[(iter->getParent())-1].getYear() << std::endl;
          std::cout << orig_movies[(iter->getParent())-1].getMin() << std::endl;
          parent_genres = orig_movies[(iter->getParent())-1].getGenres();
          std::cout << parent_genres.size();
          for(int i = 0; i < parent_genres.size(); i++){
            std::cout << " " << parent_genres[i];//prints each genre
          }
          std::cout << std::endl;
          parent_ids = orig_movies[iter->getParent()-1].getActors();
          parent_roles = orig_movies[iter->getParent()-1].getRoles();
          std::cout << parent_ids.size();
          //goes through ids and prints out its counterpart from map
          for(int i = 0; i < parent_ids.size(); i++){
            std::cout << " " << actors[parent_ids[i]];//gets info from map
            std::cout << " (" << parent_roles[i] << ")";//prints role
          }
          std::cout << std::endl;
        }
      }else{
          std::cout << "No results for query." << std::endl;
      }
    }
  }
  return 0;
}