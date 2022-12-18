#ifndef table_h_
#define table_h_

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <utility>


class movie
{
public:
    movie(const std::string &name1, const int &year1, const int &run1, const int &genre_num1, const int &actor_num1, const int &role_num1,
          const std::vector<std::string> &genres1, const std::vector<std::string> &actors1, const std::vector<std::string> &roles1);
    
    void print(std::map<std::string, std::string>& actor_data) const;
    void print() const;

    friend bool operator==(const movie& rhs, const movie& lhs) {
        bool x = (rhs.name == lhs.name && rhs.year == lhs.year && rhs.run == lhs.run && rhs.genre_num == lhs.genre_num 
            && rhs.actor_num == lhs.actor_num && rhs.role_num == lhs.role_num);
        if (!x) {
            return x;
        }
        int g = 0;
        int a = 0;
        int r = 0;
        for (int i = 0; i < rhs.genre_num; i++) {
            if (rhs.genres[i] == lhs.genres[i]) {
                g += 1;
            }
        }
        if (g != rhs.genre_num) {
            return false;
        }

        for (int i = 0; i < rhs.actor_num; i++) {
            if (rhs.actors[i] == lhs.actors[i]) {
                a += 1;
            }
        }
        if (a != rhs.actor_num) {
            return false;
        }

        for (int i = 0; i < rhs.role_num; i++) {
            if (rhs.roles[i] == lhs.roles[i]) {
                r += 1;
            }
        }
        if (r != rhs.role_num) {
            return false;
        }
        return true;
    }

    std::string name;
    int year, run, genre_num, actor_num, role_num;
    std::vector<std::string> genres, actors, roles;
};

class query
{
public:  
    query() : name("0"), year(0), run(0), genre_num(0), actor_num(0), role_num(0) {}
    query(const std::string &str1, const std::string &name1, const int &year1, const int &run1, const int &genre_num1, const int &actor_num1, const int &role_num1, 
    const std::vector<std::string> &genres1, const std::vector<std::string> &actors1, const std::vector<std::string> &roles1);
    
    // makes a query out of a movie
    query(const movie& mov) : name(mov.name), year(mov.year), run(mov.run), genre_num(mov.genre_num), actor_num(mov.actor_num), role_num(mov.role_num), 
        genres(mov.genres), actors(mov.actors), roles(mov.roles) {}

    std::string getstr() const {return str;}
    void makestr();
    void print() const;

    friend bool operator==(const query& rhs, const query& lhs) {
        bool x = (rhs.name == lhs.name && rhs.year == lhs.year && rhs.run == lhs.run && rhs.genre_num == lhs.genre_num 
            && rhs.actor_num == lhs.actor_num && rhs.role_num == lhs.role_num);
        if (!x) {
            return x;
        }
        int g = 0;
        int a = 0;
        int r = 0;
        for (int i = 0; i < rhs.genre_num; i++) {
            if (rhs.genres[i] == lhs.genres[i]) {
                g += 1;
            }
        }
        if (g != rhs.genre_num) {
            return false;
        }

        for (int i = 0; i < rhs.actor_num; i++) {
            if (rhs.actors[i] == lhs.actors[i]) {
                a += 1;
            }
        }
        if (a != rhs.actor_num) {
            return false;
        }

        for (int i = 0; i < rhs.role_num; i++) {
            if (rhs.roles[i] == lhs.roles[i]) {
                r += 1;
            }
        }
        if (r != rhs.role_num) {
            return false;
        }
        return true;
    }

    void addname(const std::string name1) {name = name1;}
    void addyear(const int year1) {year = year1;}
    void addrun(const int run1) {run = run1;}
    void addgenrenum(const int genre_num1) {genre_num = genre_num1;}
    void addactornum(const int actor_num1) {actor_num = actor_num1;}
    void addrolenum(const int role_num1) {role_num = role_num1;}
    void addgenres(const std::vector<std::string> genres1) {genres = genres1;}
    void addactors(const std::vector<std::string> actors1) {actors = actors1;}
    void addroles(const std::vector<std::string>&roles1) {roles = roles1;}
    void addindx(int x) {indx = x;}
    int getindx() const {return indx;} 
    


private:
    std::string name;
    int year, run, genre_num, actor_num, role_num;
    std::vector<std::string> genres, actors, roles;
    std::string str;
    int indx;
};

class table
{
private:
    std::vector< std::pair<query, std::list<movie> > > m_table;
    unsigned int size;
    typedef typename std::list<movie>::iterator indx_itr;
    float occ;
public:
    table() : m_table(100), size(0) {}
    table(unsigned int size1) : m_table(size1), size(0) {}
    table(const table &old) : m_table(old.m_table), size(old.size) {}

    std::vector< std::pair<query, std::list<movie> > > getdata() const {return m_table;}
    int hashfunc(const query& query1) const;
    void insert(query &key, const movie &movie1);
    void setocc(float x) {occ = x;}
    void settablesize(unsigned int x) {m_table.resize(x);}
    unsigned int getsize() const {return size;}
    void print(const query& indx, std::map<std::string, std::string>& actor_data) const;

    // iterator class to iterate through the hash table (used in lab 11)
    class iterator
    {
    public:
        friend class table;
    private:
        // ITERATOR REPRESENTATION
        table *tbl;
        int indx;          // current index in the hash table
        indx_itr list_itr; // current iterator at the current index

        // private constructors for use by the ds_hashset only
        iterator(table *it) : tbl(it), indx(-1) {}
        iterator(table *it, int index, indx_itr loc)
            : tbl(it), indx(index), list_itr(loc) {}

    public:
        // Ordinary constructors & assignment operator
        iterator() : tbl(0), indx(-1) {}
        iterator(iterator const &itr)
            : tbl(itr.tbl), indx(itr.indx), list_itr(itr.list_itr) {}
        iterator &operator=(const iterator &old)
        {
            tbl = old.tbl;
            indx = old.indx;
            list_itr = old.list_itr;
            return *this;
        }


        // The dereference operator need only worry about the current
        // list iterator, and does not need to check the current index.
        const movie &operator*() const { return *list_itr; }

        // The comparison operators must account for the list iterators
        // being unassigned at the end.
        friend bool operator==(const iterator &lft, const iterator &rgt)
        {
            return lft.tbl == rgt.tbl && lft.indx == rgt.indx && (lft.indx == -1 || lft.list_itr == rgt.list_itr);
        }
        friend bool operator!=(const iterator &lft, const iterator &rgt)
        {
            return lft.tbl != rgt.tbl || lft.indx != rgt.indx || (lft.indx != -1 && lft.list_itr != rgt.list_itr);
        }

        // increment and decrement
        iterator &operator++()
        {
            this->next();
            return *this;
        }
        iterator operator++(int)
        {
            iterator temp(*this);
            this->next();
            return temp;
        }

    private:
        //  Find the next entry in the table
        void next()
        {
            ++list_itr; // next item in the list

            // If we are at the end of this list
            if (list_itr == (tbl->m_table[indx].second).end())//////////////////
            {
                // Find the next non-empty list in the table
                for (++indx;
                    indx < int(tbl->m_table.size()) && (tbl->m_table[indx].second).empty();//////////////////
                    ++indx)
                {
                }

                // If one is found, assign the m_list_itr to the start
                if (indx != int(tbl->m_table.size()))
                    list_itr = (tbl->m_table[indx].second).begin();//////////////////

                // Otherwise, we are at the end
                else
                    indx = -1;
            }
        }
    };

    // Find the first entry in the table and create an associated iterator
    iterator begin()
    {
        iterator p(this);
        for (p.indx = 0; p.indx < int(this->m_table.size()); ++p.indx)
        {
            if (!(m_table[p.indx].second).empty())/////////////////////
            {
                indx_itr q = (m_table[p.indx].second).begin();///////////////
                p.list_itr = q;
                return p;
            }
        }
        p.indx = -1;
        return p;
    }//

    // Create an end iterator.
    iterator end()
    {
        iterator p(this);
        p.indx = -1;
        return p;
    }

public:
  // resize the table with the same values 
  void resize_table(unsigned int new_size) {
    std::vector< std::pair<query, std::list<movie> > > old_table = m_table;
    m_table.clear();
    m_table.resize( new_size );

    for ( unsigned int i=0; i<old_table.size(); i++ )

      for ( indx_itr p = old_table[i].second.begin(); p!=old_table[i].second.end(); p++ )
	{
        this -> insert(old_table[i].first, *p);
	}

  }
};

movie::movie(const std::string &name1, const int &year1, const int &run1, const int &genre_num1, const int &actor_num1, const int &role_num1,
             const std::vector<std::string> &genres1, const std::vector<std::string> &actors1, const std::vector<std::string> &roles1)
{
    name = name1;
    year = year1;
    run = run1;
    genre_num = genre_num1;
    actor_num = actor_num1;
    role_num = role_num1;
    genres = genres1;
    actors = actors1;
    roles = roles1;
}
void movie::print(std::map<std::string, std::string>& actor_data) const
{
    std::cout << name << std::endl;
    std::cout << year << std::endl;
    std::cout << run << std::endl;
    std::cout << genre_num;
    for (int i = 0; i < genre_num; i++)
    {
        std::cout << " " << genres[i];
    }
    std::cout << std::endl;
    std::cout << actor_num;
    for (int i = 0; i < actor_num; i++)
    {
        std::cout << " " << actor_data[actors[i]] << " (" << roles[i] << ")";
    }
    std::cout << std::endl;
}

void query::makestr() {
    str = name + std::to_string(year) + std::to_string(run) + std::to_string(genre_num);
    for (int i = 0; i < genre_num; i++) {
        str += genres[i];
    }
    str += std::to_string(actor_num);
    for (int i = 0; i < actor_num; i++) {
        str += actors[i];
    }
    str += std::to_string(role_num);
    for (int i = 0; i < role_num; i++) {
        str += roles[i];
    }
}

void query::print() const
{
    std::cout << name << std::endl;
    std::cout << year << std::endl;
    std::cout << run << std::endl;
    std::cout << genre_num;
    for (int i = 0; i < genre_num; i++)
    {
        std::cout << " " << genres[i];
    }
    std::cout << std::endl;
    std::cout << actor_num;
    for (int i = 0; i < actor_num; i++)
    {
        std::cout << " " << actors[i];
    }
    std::cout << std::endl;
    std::cout << role_num;
    for (int i = 0; i < role_num; i++)
    {
        std::cout << " " << roles[i];
    }
    std::cout << std::endl;
}

void movie::print() const
{
    std::cout << name << std::endl;
    std::cout << year << std::endl;
    std::cout << run << std::endl;
    std::cout << genre_num;
    for (int i = 0; i < genre_num; i++)
    {
        std::cout << " " << genres[i];
    }
    std::cout << std::endl;
    std::cout << actor_num;
    for (int i = 0; i < actor_num; i++)
    {
        std::cout << " " << actors[i];
    }
    std::cout << std::endl;
    std::cout << role_num;
    for (int i = 0; i < role_num; i++)
    {
        std::cout << " " << roles[i];
    }
    std::cout << std::endl;
}


void table::insert(query &key, const movie &movie1)
{
    float x = size / m_table.size();
    if (occ < x) {
        this -> resize_table(2*m_table.size());
    }

    unsigned int hash_value = hashfunc(key);
    unsigned int index = hash_value % m_table.size();
    if (m_table[index].first == key) {
        std::list<movie>::const_iterator it = m_table[index].second.begin();
        for (; it != m_table[index].second.end(); it++) {
            if (*it == movie1) {
                return;
            }
        }
        m_table[index].second.push_back(movie1);
    }
    if (m_table[index].second.size() == 0) {
        m_table[index].first = key;
        m_table[index].second.push_back(movie1);
        size++;
        return;
    }

    // handles collisions
    if (!(m_table[index].first == key) || m_table[index].second.size() > 1) {
        int i = 1;
        if (index == m_table.size()-1) {
            i = -1;
        }
        while(m_table[index+i].second.size() != 0) {
            if (index+i == m_table.size()-1 ) {
                i = -1;
            }
            if (i > 0) 
                i++;
            else
                i--;
        }
        m_table[index+i].first = key;
        m_table[index+i].second.push_back(movie1);
        size++;
        key.addindx(index+i);
        return;
    }
    

}

void table::print(const query& a, std::map<std::string, std::string>& actor_data) const {
    int indx = a.getindx();
    if (m_table[indx].second.size() == 0 || !(m_table[indx].first == a)) {
        std::cout << "No results for query." << std::endl;
        return;
    }
    std::cout << "Printing " << m_table[indx].second.size() << " result(s):" << std::endl;
    std::list<movie>::const_iterator it = m_table[indx].second.begin();
    for (; it != m_table[indx].second.end(); it++) {
        it -> print(actor_data);
    }
}

int table::hashfunc(const query &query1) const {
    int n = query1.getstr().size();

    unsigned long hash = 0;

    for (int i = 0; i < n; i++)
        hash = query1.getstr()[i] + (hash << 6) + (hash << 16) - hash;
    return hash % m_table.size();
}


#endif