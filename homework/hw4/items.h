#ifndef kitchenlist_h
#define kitchenlist_h
class Item{
    public:
    Item( int c_time, std::string n){
        cook_time = c_time;
        name = n;
    }
    

    private:
    std::string name;
    int cook_time;
}




#endif