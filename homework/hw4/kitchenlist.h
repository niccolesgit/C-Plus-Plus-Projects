#ifndef kitchenlist_h
#define kitchenlist_h
class KitchenList{
    public:
    typedef std::string* iterator;
    typedef std::string* const_iterator;
  // CONSTRUCTORS, ASSIGNMNENT OPERATOR, & DESTRUCTOR
  KitchenList() { this->create(); }
  ~KitchenList() { delete [] m_data; }

  // MEMBER FUNCTIONS AND OTHER OPERATORS
  void push_back(const std::string t);
  iterator erase(iterator p);
  int size() const { return m_size; }
  std::string getName(){return }

  // ITERATOR OPERATIONS
  iterator begin() { return m_data; }
  const_iterator begin() const { return m_data; }
  iterator end() { return m_data + m_size; }
  const_iterator end() const { return m_data + m_size; }
private:  
  // PRIVATE MEMBER FUNCTIONS
  void create();
  // REPRESENTATION
  std::string* m_data;         // Pointer to first location in the allocated array
  int m_size;  // Number of elements stored in the KitchenListtor
  int m_alloc; // Number of array locations allocated,  m_size <= m_alloc
};

// Create an empty KitchenListtor (null pointers everywhere).
void KitchenList::create() {
  m_data = NULL;
  m_size = m_alloc = 0;  // No memory allocated yet
}


// Add an element to the end, resize if necesssary. 
void KitchenList::push_back(const std::string val) {
  if (m_size == m_alloc) { 
    // Allocate a larger array, and copy the old values

    // Calculate the new allocation.  Make sure it is at least one.
    m_alloc *= 2;
    if (m_alloc < 1) m_alloc = 1;
    
    // Allocate and copy the old array
    std::string* new_data = new std::string[ m_alloc ];
    for (int i=0; i<m_size; ++i)
      new_data[i] = m_data[i];
    
    // Delete the old array and reset the pointers
    delete [] m_data;
    m_data = new_data;
  }

  // Add the value at the last location and increment the bound
  m_data[m_size] = val;
  ++ m_size;
}

// Shift each entry of the array after the iterator. Return the iterator, 
// which will have the same value, but point to a different element.
KitchenList::iterator KitchenList::erase(iterator p) {
  // remember iterator and T* are equivalent
  for (iterator q = p; q < m_data+m_size-1; ++q)
    *q = *(q+1);
  m_size --;
  return p;
}




#endif