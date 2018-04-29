#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdlib.h>
using namespace std;

class Article{
public:
  Article();//constructor
  ~Article();//destructor
  char letter;//letter assigned to article
  void print();//print function
  int numDepOn; //number of articles it is dependent on
  vector<Article*> dependencies; //list of articles dependent on it
};

Article::Article(){
  letter ='.'; //set letter character to a period, a value that will never actually be used to stand in for an article name
  numDepOn =-1;//set numDepOn to -1, so that no manipulation will cause it to have a value of 0, so will not be printed out
}
Article::~Article(){}
void Article::print(){
  cout<<this->letter<<" ";
}

class Graph{
public:
  Graph();//constructor
  ~Graph();//destructor
  Article* findZeroDep();//find article with no dependencies
  Article* findLeastDep();//find article with fewest dependencies, to take care of cicular dependencies
  void decDep(Article* b);//decrement numDepOn for a given Article
  void deleteArticle(Article* a);//remove article from consideration for being printed out
  int numArt; // number of articles in the graph that need to be "published"
  Article* graph[26];//stores articles (and dummy articles), used like a hash table, f(letter) = ascii code of letter character - 65
};

Graph::Graph(){
  numArt=0; //set total number of articles to 0
  //initialize graph vector with dummy default articles
  for (int i=0;i<26;i++){ 
    Article* a = new Article();
    graph[i]=a;
  }
}
Graph::~Graph(){}

Article* Graph::findZeroDep(){
  //iterate through all of the articles in the graph
  for(int i=0;i<26;i++){
    Article* a = this->graph[i];
    //return the first article pointer that depends on no other articles
    if(a->numDepOn==0){
      return a;
    }
  }//if there are none that have no dependencies, there is a cycle. Find the item with the fewest dependencies
  return this->findLeastDep();
}

Article* Graph::findLeastDep(){
  Article* result = this->graph[0];
  int val = result->numDepOn;
  //iterate through graph to find article with fewest dependencies
  for(int i=1;i<26;i++){
    Article* a = this->graph[i];
    if((a->numDepOn < val)&&(a->numDepOn>0)){
      val = a->numDepOn;
      result = a;
    }
  }return result;

}

void Graph::decDep(Article* b){
  //calculate the ascii value, subtract 65 to get location in array
  int ascii = ((int)(b->letter))-65;
  //if we have found the correct article, decrement the number of dependencies it has on other articles
  if(this->graph[ascii]->letter==(b->letter)){
    this->graph[ascii]->numDepOn -=1;
    return;
  }
}

void Graph::deleteArticle(Article* a){
  //this method does not actually delete it, just sets the number of dependencies to -1, so that is will not be in consideration to be printed out again, or found using findZeroDep()
  //calculate the ascii value, subtract 65 to get location in array
  int ascii = ((int)(a->letter))-65;
  //if we have found the correct article, set numDepOn to -1
  if(this->graph[ascii]->letter==(a->letter)){
    this->graph[ascii]->numDepOn=-1;
    return;
  }
}

vector<char> topologicalSort(Graph g){
  //create a vector of results
  vector<char> result;
  //only need to print out the number of articles that were actually stored in the graph, do not consider dummy default articles
  for(int i=0; i<g.numArt;i++){
    //find the first article that does not depend on any other articles
    Article* a = g.findZeroDep();
    //add this article's letter identifier to the vector of results
    result.push_back(a->letter);
    //for every article that depends on this article, deprement its number of dependencies
    for(Article* b: a->dependencies){
      g.decDep(b);
    }
    //remove the article we just processed from consideration for being found by findZeroDep() again
    g.deleteArticle(a);
  }
  return result;
}

void process(vector<string> vec){
  //create a graph object
  Graph info;
  char s1;
  char s2;
  //iterate through the given vector
  for(int i=0; i<vec.size();i++){
    //identify the letters used for articles
    s1 = vec[i][0];
    s2 = vec[i][3];
    //convert to ascii values, we only want capital letters
    int ascii1 = ((int)(s1))-65;
    int ascii2 = ((int)(s2))-65;
    //if they are lowercase letters, subtract 35 to store in same place as uppercase letters
    if (ascii1>25){
      ascii1 -=32;
      s1 = (char)ascii1;
    }if(ascii2>25){
      ascii2 -= 32;
      s2 = (char)ascii2;
    }
    //check to see if in graph, if not, then add them
    if(info.graph[ascii1]->letter!=(s1)){
      delete info.graph[ascii1];
      Article* x = new Article();
      x->letter = s1;
      x->numDepOn=0;
      info.graph[ascii1]=x;
      info.numArt+=1;
    }
    if(info.graph[ascii2]->letter==(s2)){
      info.graph[ascii2]->numDepOn+=1;
    }else{
      delete info.graph[ascii2];
      Article* x = new Article();
      x->letter = s2;
      x->numDepOn=1;
      info.graph[ascii2]=x;
      info.numArt+=1;
    }
    //update dependencies
    Article* a1 = info.graph[ascii1];
    Article* a2 = info.graph[ascii2];
    (a1->dependencies).push_back(a2);
  }
  //do the topological sort
  vector<char> output = topologicalSort(info);
  //print output vector
  for(int i=0;i<output.size();i++){
    cout<<output[i]<<" ";
  }cout<<endl;
  
  for(int i=0;i<26;i++){
    delete info.graph[i];
  }
}


int main(){
  //vector strings should be of the form "Letter1->Letter2"
  
  //Test 1: Given a list of A, B, C, and D, where C depends on A, D depends on B, and A depends on B, find the proper order.
  vector<string> test1;
  test1.push_back("A->C");
  test1.push_back("B->D");
  test1.push_back("B->A");
  process(test1);
  //output is B A C D

  //Test 2: Given the same list above, check that your algorithm holds when A depends on C, D on A, and B on D
  vector<string> test2;
  test2.push_back("C->A");
  test2.push_back("A->D");
  test2.push_back("D->B");
  process(test2);
  //output is C A D B

  //Test 3: Solve for: A->B, A->D, B->C, B->E, C->D, C->E
  vector<string> test3;
  test3.push_back("A->B");
  test3.push_back("A->D");
  test3.push_back("B->C");
  test3.push_back("B->E");
  test3.push_back("C->D");
  test3.push_back("C->E");
  process(test3);
  //output is A B C D E 

  //Test 4: Testing output with circular dependencies
  vector<string> test4;
  test4.push_back("A->B");
  test4.push_back("B->C");
  test4.push_back("C->D");
  test4.push_back("D->A");
  process(test4);
  //output is A B C D
  
  return 0;
}
