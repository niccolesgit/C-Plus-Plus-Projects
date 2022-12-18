#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <utility>
#include "table.h"

/*
These two functions are not required for your program, but may be helpful!
The recursive function will generate every combination of 0/1 for 6 positions
in a vector. Whenever pos == 6, the vector is complete.

Hint: There are 6 different "fields" in a query, this may be useful in constructing
your hash table.
*/

void permute_filters(int pos, std::vector<std::string> filter, const movie& mov, table& data){
	if(pos == 6){
		//Add other code here if you want to use the completed vectors
        query a;
        int x = 0;
        if (filter[0] == "1") {
            a.addname(mov.name);
            x+=1;
        }
        if (filter[1] == "1") {
            a.addyear(mov.year);
            x+=1;
        }
        if (filter[2] == "1") {
            a.addrun(mov.run);
            x+=1;
        }
        if (filter[3] == "1") {
            a.addgenrenum(mov.genre_num);
            a.addgenres(mov.genres);
            x+=1;
        }
        if (filter[4] == "1") {
            a.addactornum(mov.actor_num);
            a.addactors(mov.actors);
            x+=1;
        }
        if (filter[5] == "1") {
            a.addrolenum(mov.role_num);
            a.addroles(mov.roles);
            x+=1;
        }
        
        a.makestr();
        a.addindx(data.hashfunc(a));
       
        data.insert(a, mov);
        
        //std::cout << a.getindx() <<"\n"<< std::endl;
		return;
	}

	filter.push_back("0");
	std::vector<std::string> filter_new = filter;
	filter_new.back() = "1";
	permute_filters(pos+1, filter_new, mov, data);
	permute_filters(pos+1, filter, mov, data);

}

//Driver function, feel free to modify to pass more arguments
void permute_filters(table& data, const movie& mov){
		permute_filters(0, std::vector<std::string>(), mov, data);
}

int main() {
	std::string inp;
    std::map<std::string, std::string> actor_data;

    table data;

    unsigned int tablesize;
    float occ;
	while(true) {
		std::cin >> inp;

		if (inp == "quit") {
			break;
		}
        else if (inp == "table_size") {
            std::cin >> tablesize;
            data.resize_table(tablesize);
        }
        else if (inp == "occupancy") {
            std::cin >> occ;
            data.setocc(occ);

        }
        else if (inp == "movies") {
            std::string file;
            std::cin >> file;

            std::ifstream in_str(file);
            if (!in_str.good()) {
                std::cerr << "Can't open " << inp << " to read.\n";
                exit(1);
            }
            std::string name;
            while(in_str >> name) {
                //in_str >> name;
                std::string genre, actor, role;
                int year, run, genre_num, actor_num, role_num;
                std::vector<std::string> genres, actors, roles; 
                in_str >> year;
                in_str >> run;
                
                in_str >> genre_num;
                for (int i = 0; i < genre_num; i++) {
                    in_str >> genre;
                    genres.push_back(genre);
                }

                in_str >> actor_num;
                for (int i = 0; i < actor_num; i++) {
                    in_str >> actor;
                    actors.push_back(actor);
                }

                in_str >> role_num;
                for (int i = 0; i < role_num; i++) {
                    in_str >> role;
                    roles.push_back(role);
                }

                movie a(name, year, run, genre_num, actor_num, role_num, genres, actors, roles);
            
                permute_filters(data, a);
                //a.print();
            }
        }
        else if (inp == "actors") {
            std::string file;
            std::cin >> file;

            std::ifstream in_str(file);
            if (!in_str.good()) {
                std::cerr << "Can't open " << inp << " to read.\n";
                exit(1);
            }
            
            std::string i;
            std::string name;
            while (in_str >> i) {
                in_str >> name;
                actor_data[i] = name;
            }

        }
        else if (inp == "query") {
            query a;
            std::string name, genre, actor, role, year, run; 
            int genre_num, actor_num, role_num;
            std::vector<std::string> genres, actors, roles; 

            std::cin >> name;
            if (name == "?")
                name = "0";
            a.addname(name);
            std::cin >> year;
            if (year == "?")
                year = "0";
            a.addyear(stoi(year));
            std::cin >> run;
            if (run == "?")
                run = "0";
            a.addrun(stoi(run));

            std::cin >> genre_num;
            for (int i = 0; i < genre_num; i++) {
                std::cin >> genre;
                genres.push_back(genre);
            }
            a.addgenrenum(genre_num);
            a.addgenres(genres);

            std::cin >> actor_num;
            for (int i = 0; i < actor_num; i++) {
                std::cin >> actor;
                actors.push_back(actor);
            }
            a.addactornum(actor_num);
            a.addactors(actors);

            std::cin >> role_num;
            for (int i = 0; i < role_num; i++) {
                std::cin >> role;
                roles.push_back(role);
            }
            a.addrolenum(role_num);
            a.addroles(roles);

            a.makestr();
            a.addindx(data.hashfunc(a));
            
            data.print(a, actor_data);
        }
        else {
            std::cerr << "Invalid Input" << std::endl;
        }
	}
    return 0;
}