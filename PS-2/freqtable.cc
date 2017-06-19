#include "freqtable.h"
#include <iostream>
#include <string.h>
FreqTable::FreqTable(){
    root=NULL;
}
FreqTable::~FreqTable(){
    delete(root);
}
void FreqTable::convert(char *str){
     int i=0;
     while(*(str+i)!='\0'){
         if(*(str+i)>'A' && *(str+i)<'Z')
             *(str+i)=*(str+i)-'A'+'a';
         else 
             *(str+i)=*(str+i);
        i++;
     }
     return ;
}
void FreqTable::inserthelper(char *str, BSTNode *p){
     if(p==0){

        p=new BSTNode(str);
        n_elem++;
        //insert  node, if this str doesn't exist in this tree.
        return;
    }
    if(p->word== str  ){
        // check  the p->word;
        p->count++;
        return;
        }
    //recursively 
    if(p->word > str)
        inserthelper( str, p->left);
    if(p->word < str)
        inserthelper( str, p->right);
}

void FreqTable::insert(const char *str){
    int n = strlen(str);
    char *newstr = new char[n+1];
    strcpy(newstr, str);
    convert(newstr);
    inserthelper(newstr, root);
}

int FreqTable::containshelper(char *str,BSTNode *p){
     if(p==0)   //check the node is NULL first or (p->word =NULL)
         return 0;    
     else if( p->word == str ) // check the word in this node is equal to str
         return 1;
         // recursively
     else if( p->word > str)
         return containshelper(str, p->left);
     else 
         return containshelper(str, p->right);
}    
bool FreqTable::contains(const char *str){
    int n = strlen(str);
    char *newstr = new char[n+1];
    strcpy(newstr, str);
    convert(newstr);
    if( containshelper(newstr, root)==1){
          return true;}
    else {
          return false;}
}

void FreqTable::erasehelper( char *str, BSTNode *p){
     if(p==0)
         return;
     if( p->word == str  ){
        if( p->count==1){
            
                //delete but we should think about different case, if this is a leaf, directly delete it. if this only has one kid, make the point behind this point to this it's kid; when this has two kids, choose successor to be the parent.
            return;
        }
        if (  p->count> 1){
              p->count--;
             return;
        }
     }
     if( p->word > str)
        erasehelper(str, p->left);
     if( p->word< str)
        erasehelper(str, p->right);
}

void FreqTable::erase(const char *str){
     int n = strlen(str);
    char *newstr = new char[n+1];
    strcpy(newstr, str);
    convert(newstr);
   erasehelper(newstr, root);
}

bool FreqTable::empty(){
    if(!root)
       return true;
    else 
       return false;
}


unsigned int FreqTable::size(){
    return n_elem;
}

void FreqTable::clearhelper(BSTNode *p){   //inorder clear
    if(p){
        clearhelper( p->left );
        p->count=0;
        delete p;
        n_elem--;
        clearhelper( p->right);
    }
}

void FreqTable::clear(){
     clearhelper(root);
}

void FreqTable::print_allhelper( BSTNode *p){
    if(p!=NULL){
        print_allhelper( p->left );
        std::cout << p->word <<" "<< p->count <<"\n";
        print_allhelper(p->right);
    }
    else return;
    
}
void FreqTable::print_all(){
   print_allhelper(root);
}