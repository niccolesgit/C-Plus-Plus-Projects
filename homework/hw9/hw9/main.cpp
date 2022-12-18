#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <utility>

#include "Table.h"

//from starter_code.cpp:
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
        
        //filters through checking if there is one for each parameter,
        // if so sets the for that parameter
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
        //creates a string for the hash function
        q.createString();
        //sets the index using the hashfunction to the data in the table
        q.setIndex(t_data.hashFunction(q));
        //inserts the movie into the query
        t_data.insert(q, m);
        return;
		
	}
    //if not, push back a 0, meaning that there is none of the specific parameter 
    // there
	filter.push_back("0");
    //copy the filter
	std::vector<std::string> new_filter = filter;
    //set the last value to one
	new_filter.back() = "1";
    //recusiveley check again through the new and old filter
	permute_filters(pos+1, new_filter, m, t_data);
	permute_filters(pos+1, filter, m, t_data);

}

//Driver function, feel free to modify to pass more arguments
void permute_filters(Table& t_data, const Movie& m){
		permute_filters(0, std::vector<std::string>(), m, t_data);
}

int main() {
    //string to take in the specified command
	std::string command;
    //creates a map that holds the data for the actors
    std::map<std::string, std::string> a_data;
    //table object to hold table data
    Table t_data;
    //variables for size and occupancy
    unsigned int t_size;
    float occupancy;
    //while loop when taking in all the inputs
	while(true) {
        //gets the command
		std::cin >> command;
        //if its quit, break out of the program
		if (command == "quit") {
			break;
        //if its table size
		}else if (command == "table_size") {
            //get the table size
            std::cin >> t_size;
            //set the table size
            t_data.resize_table(t_size);
        //if its occupancy
        }else if (command == "occupancy") {
            //get the occupancy
            std::cin >> occupancy;
            //sets the occupancy
            t_data.setOccupancy(occupancy);
        //if its movies
        }else if (command == "movies") {
            //variable movie text file
            std::string m_file;
            //gets the movie's file name
            std::cin >> m_file;
            //creates an input stream from the movie file
            std::ifstream infile(m_file);
            //checks if the file can be opened
            if (!infile.is_open()) {
                //if not, prints an error message
                std::cerr << m_file << " cannot be opened/found. \n";
            }
            //creates a variable for the movie title
            std::string title;
            //while the input file has found a valid movie title
            while(infile >> title) {
                //creates variables for genre, actor, and role
                std::string genre, actor, role;
                //variables for the year, runtime, genrecount, actorcount, and 
                // role count
                int year, runtime, genrecount, actorcount, rolecount;
                //vectors to hold multiple genres, actors, and roles
                std::vector<std::string> genres, actors, roles; 
                //reads fror the year, runtime and genre count
                //stops for now at genre count to get the list
                // of all possible genres
                infile >> year >> runtime >> genrecount;
                int g = 0;
                //gets all the genres
                while (g<genrecount){
                    infile >> genre;
                    genres.push_back(genre);
                    g++;
                }
                //gets all the actors
                infile >> actorcount;
                int a = 0;
                while (a<actorcount){
                    infile >> actor;
                    actors.push_back(actor);
                    a++;
                }
                //gets all the roles
                infile >> rolecount;
                int r = 0;
                while (r<rolecount){
                    infile >> role;
                    roles.push_back(role);
                    r++;
                }
                //creates a movie object with the inputs in the file found
                Movie m(title, year, runtime, genrecount, actorcount, rolecount, genres, actors, roles);
                //checks the filters
                permute_filters(t_data, m);
            }
        //if te command is actors
        }else if (command == "actors") {
            //string variable for the file name
            std::string a_file;
            //gets the file name
            std::cin >> a_file;
            //makes an input stream from the file name
            std::ifstream infile(a_file);
            //checks if its a valid file to be opened
            if (!infile.is_open()) {
                std::cerr << a_file << " cannot be opened/found. \n";
            }
            //creates a variable for the number of titles
            std::string titlecount;
            //variable for the titles
            std::string title;
            //while the infile goes though 
            // the number of movies there are
            while (infile >> titlecount) {
                infile >> title;
                //adds the title at the title counter
                a_data[titlecount] = title;
            }
        //if the command is query
        }else if (command == "query") {
            //creates query object
            Query q;
            //variables for the parameters (explained in above code):
            std::string title, genre, actor, role, year, runtime; 
            int genrecount, actorcount, rolecount;
            std::vector<std::string> genres, actors, roles; 
            //again, goes through the title till the genre count
            std::cin >> title >> year >> runtime >> genrecount;
            //if perameters have a ? set the value to 0
            // then set the values normally or 0
            if (title == "?"){
                title = "0";
            }
            q.setTitle(title);
            if (year == "?"){
                year = "0";
            }
            //uses stoi to convert int to string
            q.setYear(stoi(year));
            if (runtime == "?"){
                runtime = "0";
            }
            q.setRunTime(stoi(runtime));
            //goes through all the genres
            int g = 0;
            while (g<genrecount){
                std::cin >> genre;
                genres.push_back(genre);
                g++;
            }
            //sets the genres
            q.setGenreCount(genrecount);
            q.setGenres(genres);

            std::cin >> actorcount;
            //goes through all the actors
            int a =0;
            while (a<actorcount){
                std::cin >> actor;
                actors.push_back(actor);
                a++;
            }
            //sets all the actors
            q.setActorCount(actorcount);
            q.setActors(actors);

            std::cin >> rolecount;
            //goes through all the roles
            int r = 0;
            while (r<rolecount){
                std::cin >> role;
                roles.push_back(role);
                r++;
            }
            //sets all the roles
            q.setRoleCount(rolecount);
            q.setRoles(roles);
            //creates a string from the query
            q.createString();
            //gets the indexes using the hash function
            q.setIndex(t_data.hashFunction(q));
            //prints all the data in the table from the query and actor data
            t_data.print(q, a_data);
        }else {
            //else, it means the user input an invalid command
            std::cerr << "Invalid command(s)" << "\n";
        }
	}
    return 0;
}