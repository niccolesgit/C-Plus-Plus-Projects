#ifndef unrolled_h_
#define unrolled_h_
#include <cassert>
//sets const because each list can only have 6 elements
//before making next node
const int NUM_ELEMENTS_PER_NODE = 6;
//layout taken from dslist_partial.h (Lecture 11), variable names are based
//off of the grid given in the hw pdf
// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node {
public:
//sets next and prev to NULL and num_elements to 0
  Node(): next_(NULL), prev_(NULL), num_elements(0) {}

    // REPRESENTATION
    //creates default list with size of 6
    T elements[NUM_ELEMENTS_PER_NODE];
    //creates pointers for the next
    Node<T>* next_;
    //creates pointers for the prev
    Node<T>* prev_;
    int num_elements; //creates num_elements
};

//declares he class
template <class T> class UnrolledLL;

// -----------------------------------------------------------------
// UNROLLED ITERATOR
template <class T>
class list_iterator {
public:
    // default constructor, copy constructor, assignment operator, & destructor
    list_iterator() : ptr_(NULL), offset(0){} //default pointer and offset
    //makes iterator based on node pointer and offset int
    list_iterator(Node<T>* p, int offset_) : ptr_(p), offset(offset_) {}
    //creates an iterator based on the old pointer and old offset when copying
    list_iterator(const list_iterator<T>& old) : ptr_(old.ptr_), offset(old.offset) {}
    //creates an equal operator that can set current offset and pointer to old
    //and current offset
    list_iterator<T>& operator=(const list_iterator<T>& old) {
      offset = old.offset;
      ptr_ = old.ptr_;
      //returns the specified object
      return *this;
    }
    //deconstructor, but we use destroy list function 
    ~list_iterator() {}

    // incrementing & decrementing operators
    list_iterator<T>& operator++() {  // pre-increment, e.g., ++iter
        if (offset != ptr_ -> num_elements - 1){
            offset+=1;
        }else{
          ptr_ = ptr_->next_;
          offset = 0;
        }
        return *this;
    }
    list_iterator<T> operator++(int) { // post-increment, e.g., iter++
        list_iterator<T> temp(*this);
        if (offset != ptr_ -> num_elements - 1){
            offset+=1;
        }else{
          ptr_ = ptr_-> next_;
            offset = 0;
        }
        return temp;
    }
    list_iterator<T>& operator--() { // pre-decrement, e.g., --iter
        if (offset != 0){
           offset-=1;
        }else{
            ptr_ = ptr_->prev_;
            offset = ptr_ -> num_elements -1;
        }
        return *this;
    }

    list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
        list_iterator<T> temp(*this);
        if (offset != 0){
          offset-=1;
        }else{
          ptr_ = ptr_->prev_;
          offset = ptr_ -> num_elements -1;
        }
        return temp;
    }
    // dereferencing operator returns the element in the iterator
    T& operator*()  { return ptr_->elements[offset]; } 

    // the UnrolledLL class needs access to the private ptr_ member variables
    friend class UnrolledLL<T>;

    // Comparison operators
    bool operator==(const list_iterator<T>& r) const {
        return (offset == r.offset) && (ptr_ == r.ptr_) ;
    }
     bool operator!=(const list_iterator<T>& r) const {
        return (offset != r.offset) || (ptr_ != r.ptr_);
    }

private:
    // REPRESENTATION
    Node<T>* ptr_;    // ptr to node in the list
    int offset; // offset used like an index for array
};


// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T>
class UnrolledLL {
public:
    // default constructor, copy constructor, assignment operator, & destructor
    UnrolledLL& operator= (const UnrolledLL<T>& old); //equal operator to set old to current
    //sets head, tail to null and size to 0
    UnrolledLL() : head_(NULL), tail_(NULL), size_(0) {}
    //uses the old and uses the copy list function
    UnrolledLL( UnrolledLL<T>& old) { this->copy_list(old); }
    //when using the destructor, call to the destroy list function
    ~UnrolledLL() { this->destroy_list(); }
 
    // simple accessors & modifiers
    unsigned int size() const { return size_; } //gets the size
    void clear() { this->destroy_list(); } //clears the nodes
    bool empty() const { return head_ == NULL; } //checks if the head is empty
    void push_front(const T& v); //pushes an item to the front of the nodes
    void push_back(const T& v); //pushes an item to the back of the nodes
    void pop_front(); //removes the first item in a node
    void pop_back(); //removes the last item in a node
    void print(std::ostream &cout) const; //prints the nodes

    //gets elements in the list
    const T& front() const { return head_ -> elements [0];} //returns the first element in the nodes
    const T& back() const { return tail_-> elements[tail_-> num_elements-1];}//returns the last element in the nodes
    T& front() { return head_-> elements [0]; } //returns the first element in the nodes
    T& back() { return tail_-> elements[tail_-> num_elements-1]; } //returns the last element in the nodes

    //iterators 
    typedef list_iterator<T> iterator; //default iterator
    iterator insert(iterator itr, const T& v); //for insert
    iterator erase(iterator itr); //for erase
    iterator begin() { return iterator(head_, 0);} //starts at the beginning
    iterator end() { return iterator();} //starts at the end

//private variables
private:
    // private helper functions
    void destroy_list(); //detsroys the list
    void copy_list( UnrolledLL<T>& old); //copies the list 

    //REPRESENTATION
    Node<T>* head_; //makes pointer for the head (start)
    Node<T>* tail_; //makes pointer for the tail (end)
    unsigned int size_; //makes a variable for size
};


// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
template <class T> UnrolledLL<T>& UnrolledLL<T>::operator= (const UnrolledLL<T>& old) {
  //makes sure the old list isnt the new list
     if (old != this) {
         //if its the old list
         //destroy the current list and copy the old list
        this->destroy_list();
        this->copy_list(old);
    }
    //return the list 
    return *this;
}

//push_front function, intended to push the item sent in to the front of the node
template <class T> 
void UnrolledLL<T>::push_front(const T& v) {
    //changes the size, since we are adding an element
    ++size_;
    //if the current node is empty (meaning no elements are inside)
    if (empty()) {
        //creates a new node
        Node<T>* node = new Node<T>;
        //sets the node to its head and tail
        //since the head and tail are new
        head_ = node;
        tail_ = node;
        //sets the first element to the item
        node -> elements[0] = v;
        //increases the counter to the number of elements
        node -> num_elements++;
    //if the head's number of elements is greater than or equal to the number of nodes 
    }else if (head_-> num_elements >= NUM_ELEMENTS_PER_NODE){
        //create a new node
        Node<T>* node = new Node<T>;
        //set the pointers to point to 
        head_ -> prev_ = node; //new node equals the prev node
        node -> next_ = head_; //head equals the next node
        head_ = node; //sets the node to the head (next node)
        node -> elements[0] = v; //sets the first element to the item sent in
        node -> num_elements++; //increments the num_elements
    }else{
        //if the head is less than the number of elements per node
        //loops through the head and number of elements in that array
      for (int i = head_ -> num_elements ; i > 0; i--){ 
          //sets the head to the item before it
            head_ -> elements[i] = head_ -> elements[i-1];
        }
        //sets the head from the second element to the first element
        head_-> elements[1] = head_->elements[0];
        //sets the first element to the item sent in
        head_ -> elements[0] = v;
        //increments the number of elements
        head_ -> num_elements++;
        
    }
}
//push back function (places item into the end of the array)
template <class T> 
void UnrolledLL<T>::push_back(const T& v) {
    //increment the size since we are adding an element
    ++size_;
    //if the list is empty (nothing added yet)
    if (empty()) {
        //create a new node
        Node<T>* node = new Node<T>;
        //set the head and tail to the new node
        head_ = node;
        tail_ = node;
        //set the first element of this node to the first element
        node -> elements[0]=v;
        //inrement the number of elements inside
        node -> num_elements++;
    //if the tail's elements are greater than or equal to num elements per node
    }else if (tail_-> num_elements >= NUM_ELEMENTS_PER_NODE){
        //create a new node
        Node<T>* node = new Node<T>;
        //set the tail's next to this new node
        tail_ -> next_ = node;
        //set the tail to the prev (end) of the node
        node -> prev_ = tail_;
        //set the node to the tail (new node is now at the end of the nodes)
        tail_ = node;
        //adds the item to the end of the array (whatever index the tail's elements has)
        node -> elements[tail_ -> num_elements] = v;
        //increments the number of elements 
        node -> num_elements++;
    }else{
        //if the tail's number of element is less than the number of elements per node
        //adds the item to the end of the array (whatever index the tail's elements has)
        tail_ -> elements[tail_ -> num_elements] = v;
        //increments the number of elements 
        tail_ -> num_elements++;
    }
}
//pop_front which removes the first element in the array of the first nodes
template <class T> 
void UnrolledLL<T>::pop_front() {
    //decrement the size since we are removing an element
    --size_;
    //if the head has more than one element
    if (head_-> num_elements != 1) {
        //loop through the head, and set all the elements to the element after it
        for (int i = 0; i < head_->num_elements - 1; i++) { 
            //through setting the heads elements one element ahead, it
            //removes the first element
            head_->elements[i] = head_->elements[i + 1];
        }
        //decrement the number of elements because the first element was removed
        head_->num_elements--;
    }else{ //if there is only one element
      if (head_ == tail_){ //and the there is only one node
      //destory the entire array (since only 1 element and 1 node
      //entire array dissapears)
            destroy_list(); 
        }else{//but if there are multiple nodes
            head_ = head_ -> next_; //move the head to the next 
            delete head_ -> prev_; //delete the previous head (only 1 element
            // so you have to remove the entire node)
            head_ -> prev_ = NULL; //set the previous head to null (since it doesn't exist anymore)
        }
  }
}
//pop_back removes the last element in the last node 
template <class T> 
void UnrolledLL<T>::pop_back() {
    //if the number of elements is less than or equal to one
    if (tail_-> num_elements <= 1){ //meaning there is only one element in the tail
      //create a new iterator of the tail and the offset to its number of elements -1 (index)
      iterator itr(tail_, tail_-> num_elements-1); 
      //use the erase function to delete it (since there is only one element in it
      //must remove the entire array in the node)
      erase(itr);
    }
    else{ //else if there is multiple elements in the tail
        tail_ -> num_elements--; //set the tail to a decremented number of elements
                                // since we removed the last element we push 
                                // all the elements back 1
        //decrement the size since we removed an element
        size_--;
    }
}
//prints the nodes and arrays
template <class T> void UnrolledLL<T>::print(std::ostream& cout) const{
    //format
    cout << "UnrolledLL, size: " << size_ << std::endl;
    //creates a temp variable for the head
    Node<T>* temp = head_;
    //while the head exists 
    while(temp != NULL){
        //print the head's number of elements
        cout<< "node:["<< temp ->num_elements <<"]";
        //loops through and prints all of the elements in the array
        for (int i = 0; i < temp->num_elements ; i++) {
            cout << " " << temp->elements[i];
        }
        //moves to the next line
        cout<<std::endl;
        //sets the temp to the next node
        temp = temp->next_;
    }

}
//inserts an element in an array from specified conditions 
template <class T> 
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v) {
    //increases the size since we are inserting and adding an element to the array
    ++size_;
    //if the iterators pointer of elements is greater than or equal to the 
    // num elements per node (meaning we have to add a node)
    if (itr.ptr_ -> num_elements >= NUM_ELEMENTS_PER_NODE){
        //create a new node
        Node<T>* new_node = new Node<T>;
        //sets the new nodes next to the pointer's next
        new_node -> next_ = itr.ptr_ -> next_; 
        //sets the pointer's next to the new node's next
        itr.ptr_ -> next_ = new_node;
        //sets the new node's prev to the pointer
        new_node -> prev_ = itr.ptr_;
        //if the new node's next is empty
        if (new_node -> next_ != NULL){
            //set the new node's next's prev to the node node
            new_node -> next_ -> prev_ = new_node;
        }else{ //if not empty
        //set the tail to the new node
            tail_ = new_node;
        }
        //loop through the iterator and set the new node's elements to any of the
        //pushed elements (moving from the prev node to the new one) 
        // and pushes elements based on where the element is being
        // inserted
        for (int i = itr.offset; i < itr.ptr_->num_elements ; i++){
            new_node -> elements[i-itr.offset] = itr.ptr_->elements[i];
            new_node -> num_elements++;
        }
        //inserts the item sent in
        itr.ptr_ -> elements[itr.offset] = v;
        //increases the num elements based on the offset and adding 
        // 1 because we inserted an element in the array
        itr.ptr_-> num_elements = itr.offset + 1;
    }else{ //if the number of elements is less than the num of elements per node
    //loop through the elements in the array and push the elements ahead to give a space
    // to insert the element
        for (int i= itr.ptr_ -> num_elements; i > itr.offset; i--){
            itr.ptr_ -> elements[i] = itr.ptr_ -> elements[i-1];
        }
        //inserts the element
        itr.ptr_ -> elements[itr.offset] = v;
        //increments the number of elements since we inserted an element
        itr.ptr_ -> num_elements++;
    }
    //returns the iterator at the end of all the potential if statements
    return itr;
}
//erases the elements and the node if it erases all the elements in the array
template <class T> 
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) {
    //decrementing the size because we are removing elements
    --size_;
    //if there are more than 1 elements in the array
    if (itr.ptr_-> num_elements != 1) { 
        //loop through the elements and sets elements to the one ahead of it
        for (int i = itr.offset; i < itr.ptr_-> num_elements-1; i++) {
            //in doing so, it erases the element
            itr.ptr_->elements[i] = itr.ptr_->elements[i + 1];
        }
        //decrease the number of elements since we erased the element
        itr.ptr_ -> num_elements--;
        //if the offset equals the number of elements 
        if (itr.offset == itr.ptr_->num_elements){
            //set the pointer to the next node
            itr.ptr_ = itr.ptr_ -> next_;
            //set the offset to zero
            itr.offset = 0;
        }
        //return the iterator 
        return itr;
    }else{ //if there is only 1 element
        if (head_ != tail_){  //but more than 1 node
            if(itr.ptr_ != head_ ){//if the pointer isnt the head
            //removing the node
                itr.ptr_ -> prev_ -> next_ = itr.ptr_ -> next_;
            }else{
                //else set the head to the pointer of the next node
                head_ = itr.ptr_ -> next_;
            }
            if(itr.ptr_ != tail_){//if the pointer isnt the tail
            //removing the node
                itr.ptr_ -> next_ -> prev_ = itr.ptr_ -> prev_ ;
            }else{
                //else set the tail to the prev node
                tail_ = itr.ptr_-> prev_;
            }
            //create a new iterator based on the if statments
            // and set the offset to 0
            iterator newIt(itr.ptr_ -> next_, 0);
            //delete hte pointer
            delete itr.ptr_;
            //return the new iterator
            return newIt;
        }else{ //if there is only 1 node
        //destroy the entire list
            destroy_list();
            //return the end
            return end();
        }
    }
}
//destroys the list by removing all the data
template <class T> void UnrolledLL<T>::destroy_list() {
    //while there isn't 1 node
    while (head_ != tail_){
        //set head to the next
        head_ = head_ -> next_;
        //and delete its prev
        delete(head_ -> prev_);
    }
    //if there is only 1 node left
    //remove the head
    delete(head_);
    //reset all values to default values in the constructor
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
}
//copies the entire list to another one
template <class T> 
void UnrolledLL<T>::copy_list( UnrolledLL<T>& old) {
    //sets all of the current values to those in the constructor
    head_ = NULL;
    tail_ = NULL;
    size_ = 0;
    //goes through the old list saved and pushes the iterator back to the new list
    for (UnrolledLL<T>::iterator itr = old.begin(); itr != old.end(); itr++){
        push_back(*itr);
    }
}
//assignement operator ==
template <class T> bool operator== (UnrolledLL<T>& left, UnrolledLL<T>& right) {
    //if the left and right size isn't the same, it means its not the same, and false
    if (left.size() != right.size()){
        return false;
    }
    //but if it is the same you have to check that the element are the same
    //creates iterators for the beginning of the right and left 
    typename UnrolledLL<T>::iterator l_itr = left.begin();
    typename UnrolledLL<T>::iterator r_itr = right.begin();
    //checks both lists starting from the beginning to the end
    //while you aren't at the end of the list
    while (l_itr != left.end()) {
        //if the left and right element arent the same
        if (*l_itr != *r_itr){
            //then its immediately false
            return false;
        }else{
        //else, keep iterating though the lists
        l_itr++; 
        r_itr++;
        }
    }
    //if its checked through both lists and all the elements
    //then the lists are the same, returning true
    return true;
}
//assignement operator !=
template <class T> bool operator!= (UnrolledLL<T>& left, UnrolledLL<T>& right){
    //return the == operator but not symbol, changing the results to be when it's not true
    //if its not equal above, returning false, it returns true here, because it is not equal
    return !(left==right);
}

#endif //end if guard for the header file
