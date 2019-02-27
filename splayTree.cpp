//splayTree.cpp

#include <iostream>
#include <cstdio>
#include <cstdlib>

#include "splayTree.h"

//Constructor
splayTree::splayTree() {
  this->rootKey = NULL;
}

Node* newNode(int i) {
  Node *n = new Node;
  n->key = i;
  n->left = n->right = n->parent = NULL;
  return n;
}

void splayTree::rightRotate(Node* oldRoot) {
  std::cout<<"right rotation..."<<std::endl;
  Node *parent_OR = oldRoot->parent;
  if(parent_OR) {
    std::cout<<"parent_OR "<<parent_OR->key<<"   (should be same as g)"<<std::endl;
  } else {
    std::cout<<"old root is the root"<<std::endl;
  }
  Node *y = oldRoot->left;
  oldRoot->left = y->right;
  if(y->right) {
    y->right->parent = oldRoot;
  }
  y->right = oldRoot;
  oldRoot->parent = y;

  std::cout<<"y value...."<<y->key<<std::endl;
  return;
}

void splayTree::leftRotate(Node* oldRoot) {
  std::cout<<"left rotation..."<<std::endl;
  Node *parent_OR = oldRoot->parent;
  if(parent_OR) {
    std::cout<<"parent_OR "<<parent_OR->key<<std::endl;
  } else {
    std::cout<<"old root is the root"<<std::endl;
  }

  Node *y = oldRoot->right;
  oldRoot->right = y->left;
  if(y->left) {
    y->left->parent = oldRoot;
  }
  y->left = oldRoot;
  oldRoot->parent = y;
  return;
}

Node* splayTree::findKey(int findMe, Node *n) {
  std::cout<<"in findKey, n is "<<n->key<<std::endl;
  
  if(findMe == n->key) {
    std::cout<<"found "<<n->key<<" in tree!"<<std::endl;
    return n;
  } else if(findMe < n->key && n->left != NULL) {
    return findKey(findMe, n->left);
  } else if(findMe > n->key && n->right != NULL) {
    return findKey(findMe, n->right);
  } else if(findMe < n->key && n->left == NULL) {
    return n;
  } else {
    std::cout<<"in else"<<std::endl;
    return n;
  }

}

void splayTree::splay(Node *current) {
  std::cout<<"\n"<<std::endl;
  std::cout<<"IN SPLAYFUNC...SPLAYING "<<current->key<<std::endl;
  std::cout<<"before: ";
  print();

  Node *p = current->parent;
  Node *g = current->parent->parent;

  if(g) {
    std::cout<<"p: "<<p->key<<" and g: "<<g->key<<std::endl;
  }
  while(current != rootKey) {
    //std::cout<<"current is "<<current->key<<std::endl;
    //Node *p = current->parent;
    //std::cout<<"p: "<<p->key<<std::endl;
    //Node *g = current->parent->parent;
    //std::cout<<"p: "<<p->key<<" and g: "<<g->key<<std::endl;


    if(p == rootKey)
      { //single rotation (zig or zag)
	std::cout<<"single rotation"<<std::endl;
	if(p->left == current) {
	  rightRotate(p);
	  current->parent = NULL;
	  std::cout<<"after single right rotation.. "<<std::endl;
          std::cout<<"current = "<<current->key<<std::endl;
	  //std::cout<<"p = "<<p->key<<std::endl;
	  
	  if(!current->parent){
	    std::cout<<"current has NO parent"<<std::endl;
	  } else {
	    std::cout<<"ERROR: current still has parent "<<current->parent->key<<std::endl;
	  }
	} else {
	  leftRotate(p);
	  std::cout<<"left rotation is done"<<std::endl;
	}
	rootKey = current;
	break;
      }
    else
      {
	if(g->left && g->left->left == current) {

	  Node *GGparent = g->parent;
	  //std::cout<<"before: ";
	  print();
	  std::cout<<"right-right rotation"<<std::endl;
	  rightRotate(g);
	  
	  std::cout<<"after 1st right rotation.. "<<std::endl;
	  std::cout<<"current = "<<current->key<<std::endl;
	  std::cout<<"p =  "<<p->key<<std::endl;
	  std::cout<<"g =  "<<g->key<<std::endl;
	  
	  rightRotate(p);

	  std::cout<<"after 2nd right rotation.. "<<std::endl;
	  
          if(g == rootKey) {
	    //grandparent is the root, so make current the new root
	    rootKey = current;
	  } else  {
	    current->parent = GGparent;
	    std::cout<<"current->parent is NOW "<<current->parent->key<<std::endl;
	    GGparent->left = current;
	  }
	  
	} else if(g->right && g->right->right == current) {
	  std::cout<<"left-left rotation"<<std::endl;
	  leftRotate(g);
	  leftRotate(p);
	} else if(g->left && g->left->right == current) {
	  std::cout<<"left-right rotation"<<std::endl;
	  leftRotate(p);
	  rightRotate(g);
	} else {
	  std::cout<<"right-left rotation"<<std::endl;
	  rightRotate(p);
	  std::cout<<"RRdone"<<std::endl;
	  leftRotate(g);
	  std::cout<<"LRdone"<<std::endl;
	}
	if(g == rootKey) {
	  rootKey = current;
	}
      
      }
    
    p = current->parent;
    g = p->parent;
    //have to update current
  }
  std::cout<<"end of splay func"<<std::endl;
  std::cout<<"tree after splay: ";
  print();
}

Node* splayTree::access(int i) {
  Node *splayMe = findKey(i, rootKey); //node that will be splayed

  std::cout<<"splayMe's key: "<<splayMe->key<<std::endl;

  if(rootKey != splayMe) {
    splay(splayMe);
  }
  return splayMe; //returns whatever will be the new root
  
}

std::pair<Node*, Node*> splayTree::split(int i, Node *tree) {
  std::cout<<"in split, i is "<<i<<std::endl;
  Node *n = access(i); //whatever the new root is
  std::cout<<"finish with access, n is "<<n->key<<std::endl;
  std::pair<Node*, Node*> twoTrees;

  //new code:
  if(i >= n->key) { //if i is less than root of tree
    twoTrees.first = n;
    twoTrees.second = n->right;
    n->right = NULL;
  } else {//if i is greater than or equal to root of tree
    twoTrees.first = n->left;
    twoTrees.second = n;
    n->left = NULL;
  }

  /*

  
  twoTrees.second = n->right;
  if(twoTrees.second == NULL) {
    std::cout<<"t2 is null"<<std::endl;
  } else {
    std::cout<<twoTrees.second->key<<" is t2"<<std::endl;
  }
  
  twoTrees.first = n;
  std::cout<<n->key<<" is t1"<<std::endl;
  twoTrees.first->right = NULL;
  std::cout<<"t1's right is null"<<std::endl;
  
  if(twoTrees.second != NULL) {  
    twoTrees.second->parent = NULL; //SEG FAULT HERE
  }
  */
  return twoTrees;
  
}

void splayTree::insert(int i) {
  
  std::cout<<"inserting "<<i<<std::endl;
  //empty tree
  if(rootKey == NULL) {
    Node *insertMe = newNode(i);
    rootKey = insertMe;
    std::cout<<"PRINTING"<<std::endl;
    print();
    return;
  }

  std::pair<Node*, Node*> subtrees = split(i, rootKey); //splits the tree into 2 subtrees
  std::cout<<"back in insert"<<std::endl;

  if(subtrees.first) {
    std::cout<<"t1 is "<<subtrees.first->key<<std::endl;
  }else {
    std::cout<<"t1 is null"<<std::endl;
  }
  if(subtrees.second) {
    std::cout<<"t2 is "<<subtrees.second->key<<std::endl;
  } else {
    std::cout<<"t2 is null"<<std::endl;
  }

  std::cout<<"before if-else"<<std::endl;
  //seg fault after this
  if(subtrees.first->key == i) {
    std::cout<<"in if"<<std::endl;
    std::cout<<"item "<<subtrees.first->key<<" not inserted; already present"<<std::endl;
  } else {
    std::cout<<"in else"<<std::endl;
    Node *insertMe = newNode(i);
    std::cout<<"here"<<std::endl;

    //subtrees.first->parent = insertMe;
    //subtrees.second->parent = insertMe;
    
    insertMe->left = subtrees.first;
    insertMe->right = subtrees.second;
    rootKey = insertMe;

    std::cout<<"rootKey is "<<rootKey->key<<std::endl;
    if(rootKey->left) {
      std::cout<<"left is "<<rootKey->left->key<<std::endl;
    }
    if(rootKey->right) {
      std::cout<<"right is "<<rootKey->right->key<<std::endl;
    }
    if(subtrees.first) {
      subtrees.first->parent = insertMe;
    } if(subtrees.second) {
      subtrees.second->parent = insertMe;
    }
    //subtrees.first->parent = insertMe;
    //subtrees.second->parent = insertMe;
    
    //rootKey->left->parent = insertMe;
    //rootKey->right->parent = insertMe;
    std::cout<<"item "<<i<<" inserted"<<std::endl;
    std::cout<<"PRINTING"<<std::endl;
    print();
  }

  return;
}

int splayTree::findMax(Node *n) {
  Node *current = n;
  while(current->right != NULL) {
    current = current->right;
  }
  return current->key;
}

//should return root of new JOINED tree
Node* splayTree::join(Node *T1, Node *T2) {
  std::cout<<"IN JOIN..."<<std::endl;
  Node *n;
  if(T1) {
    n = access(findMax(T1)); //will return new root of T1
    if(n->right == NULL) {
      n->right = T2;
      T2->parent = n;
    } else {
      std::cout<<"i did something wrong here"<<std::endl;
    }

  } else {
    std::cout<<"left subtree is empty"<<std::endl;
    return T2;

  }
  return n;
}

void splayTree::remove(int i) {
  std::cout<<"removing "<<i<<std::endl;

  Node *n = access(i); //n has the key that needs to be deleted
  
  if(n->key != i) {
    std::cout<<"item "<<i<<" not deleted; not present"<<std::endl;
  } else {

    //i is currently at root
    std::pair<Node*, Node*> children;
    children.first = n->left;
    children.second = n->right;
    if(children.first) {
      std::cout<<"c.first is ... "<<children.first->key<<std::endl;
    } else {
      std::cout<<"left subtree is empty "<<std::endl;
    }

    if(children.second) {
      std::cout<<"c.second is ...  "<<children.second->key<<std::endl;
    } else {
      std::cout<<"right subtree is empty"<<std::endl;
    }

    delete n;
    
    rootKey = join(children.first, children.second);
    

    std::cout<<"item "<<i<<" deleted"<<std::endl;
  }
  
  std::cout<<"printing tree after delete"<<std::endl;
  print();
  return;
}

void splayTree::find(int i) {
  std::cout<<"in find"<<std::endl;

  Node *n = access(i); //returns the new root
  if(n->key != i) {
    std::cout<<"item "<<i<<" not found"<<std::endl; 
  } else {
    std::cout<<"item "<<i<<" found"<<std::endl; 
  }
  std::cout<<"printing tree after find"<<std::endl;
  print();
  return;
}

int splayTree::findHeight(Node *n) {
  if(n == NULL) {
    return 0;
  } else {
    
    int lheight = findHeight(n->left);
    int rheight = findHeight(n->right);

    if(lheight > rheight) {
      return (lheight+1);
    } else {
      return (rheight+1);
    }
  }
}

void splayTree::printGivenLevel(Node *root, int level) {
  if(root==NULL) {
    return;
  }
  if(level == 1) {
    std::cout<<root->key<<" ";
  } else if (level > 1) {
    
    printGivenLevel(root->left, level-1);
    
    printGivenLevel(root->right, level-1);
    //std::cout<<"\n";
  }
}

void splayTree::print() {

  int h = findHeight(rootKey);
  for(int i = 1; i <= h; i++) {
    //std::cout<<"print at height "<<i<<std::endl;
    printGivenLevel(rootKey,i);
    //std::cout<<"\n"<<std::endl;
  }
  std::cout<<"\n"<<std::endl;
  return;
}
