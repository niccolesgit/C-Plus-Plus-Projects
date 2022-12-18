template <class T>
const T& smallest_value(TreeNode<T>* p) {
  while (p->left != NULL) {
    p = p->left;
  }
  return p->value;
}


template <class T>
const T& smallest_value(const TreeNode<T>* p) {
  assert (p != NULL);
  if (p->left) {
    return smallest_value (p->left);
  } else {
    return p->value;
  }
}







int count_odd(const TreeNode<int> *p) {
  if (p == NULL) return 0;
  //if (p->value % 2 == 1) 
  // return 1 + count_odd(p->left) + count_odd(p->right);
  //else 
  //return count_odd(p->left) + count_odd(p->right);
  return (p->value % 2) + count_odd(p->left) + count_odd(p->right);

}
