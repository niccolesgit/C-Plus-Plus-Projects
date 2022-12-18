#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>


template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;

public:
  priority_queue() {}

  priority_queue( std::vector<T> const& values )
  {
    for(unsigned int i = 0; i < values.size();i++){
      m_heap.push_back(values[i]);
      percolate_down(m_heap);
    }
  }

  const T& top() const 
  {
    assert( !m_heap.empty() );
    return m_heap[0]; 
  }

  void push( const T& entry )
  {
    m_heap.push_back(entry);
    percolate_up(m_heap);
  }
  void percolate_up(std::vector<T> & v){
    if(v.size() == 0){
      return;
    }
    unsigned int i = v.size()-1;
    while(i>0){
      unsigned int j = (i-1)/2;
      if(v[j]>v[i]){
        std::swap(v[i], v[j]);
      }
      i--;
    }
  }

  void pop() 
  {
    assert( !m_heap.empty() );
    m_heap.erase(m_heap.begin());
    percolate_down(m_heap);
  }
  void percolate_down(std::vector<T> & v){
    unsigned int i = 0;
    while(i < v.size()){
      unsigned int j = (2*i) +1;
      unsigned int k = (2*i) +2;
      if(j < v.size() && v[j] < v[i]){
        std::swap(v[i], v[j]);
      }else if(k < v.size()&& v[k] < v[i]){
        std::swap(v[i], v[k]);
      }
      i++;
    }
  }

  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }


  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap( )
  {
    return this->check_heap( this->m_heap );
  }

  //  Check an external vector to see that the heap property is realized.
  bool check_heap( const std::vector<T>& heap )
  {
    if(heap.size() == 0){
      return true;
    }
    unsigned int i = heap.size()-1;
    while(i>0){
      unsigned int j = (i-1)/2;
      if(heap[j]>heap[i]){
        return false;
      }
      i--;
    }
    return true;
  }

  //  A utility to print the contents of the heap.  Use it for debugging.
  void print_heap( std::ostream & ostr )
  {
    for ( unsigned int i=0; i<m_heap.size(); ++i )
      ostr << i << ": " << m_heap[i] << std::endl;
  }
  
};


template <class T>
void heap_sort( std::vector<T> & v, unsigned int i)
{
  if(v.size() < 2){
    return;
  }else if(i == v.size()-1){
    return;
  }
  T min_val = v[i];
  unsigned int min_ind = i;

  for(unsigned int j = i; j < v.size(); j++){
    if(v[j] < min_val){
      min_val = v[j];
      min_ind = j;
    }
  }
  std::swap(v[i], v[min_ind]);
  heap_sort(v, i+1);
}
template <class T>
void heap_sort(std::vector<T> & v){
  heap_sort(v, 0);
}

#endif
