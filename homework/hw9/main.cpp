#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <utility>

#include "Table.h"

//from starter_code.cpp (permute_filters):
/*
These two functions are not required for your program, but may be helpful!
The recursive function will generate every combination of 0/1 for 6 positions
in a vector. Whenever pos == 6, the vector is complete.

Hint: There are 6 different "fields" in a query, this may be useful in constructing
your hash table.
*/
void permute_filters(int pos, std::vector<std::string> filter, const Movie& m, Table& t_data){
	if(pos == 6){
		//Add other code here if you want to use the completed vectors
        Query q;
        //filters through checking if there is one for each
        // parameter, if so, set that parameter to the query
        if (filter[0] == "1") {
            q.setTitle(m.title);
        }
        if (filter[1] == "1") {
            q.setYear(m.year);
        }
        if (filter[2] == "1") {
            q.setRunTime(m.runtime);
            
        }
        if (filter[3] == "1") {
            q.setGenreCount(m.genrecount);
            q.setGenres(m.genres);
            
        }
        if (filter[4] == "1") {
            q.setActorCount(m.actorcount);
            q.setActors(m.actors);
            
        }
        if (filter[5] == "1") {
            q.setRoleCount(m.rolecount);
            q.setRoles(m.roles);
            
        }
        //create a string to use for the hash function
        q.createString();
        //set the index usin the hash function
        q.setIndex(t_data.SDBMHash(q));
        //insert the movie at that query
        t_data.insert(q, m);
		return;
	}
    //else add a 0 to the end after checking
	filter.push_back("0");
    //make a new filter, setting it to the old one
	std::vector<std::string> new_filter = filter;
    //set the new filters last value to one
	new_filter.back() = "1";
    //check again through the new and old filter recursively
	permute_filters(pos+1, new_filter, m, t_data);
	permute_filters(pos+1, filter, m, t_data);

}

//Driver function, feel free to modify to pass more arguments
void permute_filters(Table& t_data, const Movie& m){
		permute_filters(0, std::vector<std::string>(), m, t_data);
}

int main() {
    //variable for the command, actor data, table data,
    //table size, and occupancy
	std::string command;
    std::map<std::string, std::string> a_data;
    Table t_data;
    unsigned int t_size;
    float occupancy;
    //loops until the input is quit
	while(true) {
		std::cin >> command;
        //if quit break from the loop/program
		if (command == "quit") {
			break;
		}
        //if table_size, resize the table
        else if (command == "table_size") {
            std::cin >> t_size;
            t_data.resize_table(t_size);
        }
        //if occupancy, set the occupancy
        else if (command == "occupancy") {
            std::cin >> occupancy;
            t_data.setOccupancy(occupancy);

        }
        //if movies
        else if (command == "movies") {
            //get the movie file
            std::string m_file;
            std::cin >> m_file;
            //create an input stream from the file
            std::ifstream infile(m_file);
            //checks if the file is valid or can be opened
            if (!infile.is_open()) {
                std::cerr << m_file << " cannot be opened/found. \n";
            }
            //variable for the movie title
            std::string title;
            //while the instream can find a movie title
            while(infile >> title) {
                //variables for year, runtime, genrecount, actorcount, and rolecount
                int year, runtime, genrecount, actorcount, rolecount;
                //vectors to hold the genres, actors and roles
                std::vector<std::string> genres, actors, roles; 
                //variables to read each genre, actor and role
                std::string genre, actor, role;
                //while it gets the year, runtime and genrecount
                //(stop there for now to collect all the genres)
                infile >> year >> runtime >> genrecount;
                //gets all the genres
                int g = 0;
                while(g < genrecount){
                    infile >> genre;
                    genres.push_back(genre);
                    g++;
                }
                //gets the actor number and all actors
                infile >> actorcount;
                int a = 0;
                while(a < actorcount){
                    infile >> actor;
                    actors.push_back(actor);
                    a++;
                }
                //gets role number and all the roles
                infile >> rolecount;
                int r = 0;
                while(r < rolecount){
                    infile >> role;
                    roles.push_back(role);
                    r++;
                }
                //creates a movie class from the inputs from the file
                Movie m(title, year, runtime, genrecount, actorcount, rolecount, genres, actors, roles);
                //filters the table with the movie class
                permute_filters(t_data, m);
            }
        }
        //else if the command is actors
        else if (command == "actors") {
            //gets the actor file
            std::string a_file;
            std::cin >> a_file;
            //creates input stream from actor file
            std::ifstream infile(a_file);
            //checks the file
            if (!infile.is_open()) {
                std::cerr << a_file << " cannot be opened/found. \n";
            }
            //gets all of the titles
            std::string titlecount;
            std::string title;
            //looping through the number of titles there are
            while (infile >> titlecount) {
                //sets the actor data with the title count with the title
                infile >> title;
                a_data[titlecount] = title;
            }

        }
        //if its query
        else if (command == "query") {
            //make a query object
            Query q;
            //variables for the movie title, year, runtime
            //genre, actor, and role
            std::string title, year, runtime, genre, actor, role; 
            //variables to hold how many genres, actors, and roles there are
            int genrecount, actorcount, rolecount;
            //vectors to hold all the genres, actors, and roles
            std::vector<std::string> genres, actors, roles; 
            //gets the title, year, runtime and genrecount
            std::cin >> title >> year >> runtime >> genrecount;
            //if the title, year, or runtime is a ? set it to 0.
            if (title == "?"){
                title = "0";
            }
            q.setTitle(title);
            if (year == "?"){
                year = "0";
            }
            //using stoi to convert the ints into strings
            q.setYear(stoi(year));
            if (runtime == "?"){
                runtime = "0";
            }
            q.setRunTime(stoi(runtime));
            //adds the genres
            int g = 0;
            while(g < genrecount){
                std::cin >> genre;
                genres.push_back(genre);
                g++;
            }
            //sets the genre count and vector
            q.setGenreCount(genrecount);
            q.setGenres(genres);
            //adds the actors
            std::cin >> actorcount;
            int a = 0;
            while(a < actorcount){
                std::cin >> actor;
                actors.push_back(actor);
                a++;
            }
            //sets the actor count and vector
            q.setActorCount(actorcount);
            q.setActors(actors);
            //adds the roles
            std::cin >> rolecount;
            int r = 0;
            while(r < rolecount){
                std::cin >> role;
                roles.push_back(role);
                r++;
            }
            //sets the roles count and vector
            q.setRoleCount(rolecount);
            q.setRoles(roles);

            //creates a string from the inputs for the hash function
            q.createString();
            //gets the indexes from the table, using the hashfunction
            q.setIndex(t_data.SDBMHash(q));
            //prints the data at that query and actor data
            t_data.print(q, a_data);
        //else, means the user is using the wrong commands
        }else {
            std::cerr << "Invalid command(s)" << std::endl;
        }
	}
    return 0;
}