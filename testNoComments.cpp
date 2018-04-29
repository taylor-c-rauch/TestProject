#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdlib.h>
using namespace std;

class Article{
public:
  Article();
  ~Article();
  char letter;
  void print();
  int numDepOn; 
  vector<Article*> dependencies; 
};

Article::Article(){
  letter ='.';
  numDepOn =-1;
}
Article::~Article(){}
void Article::print(){
  cout<<this->letter<<" ";
}

class Graph{
public:
  Graph();
  ~Graph();
  Article* findZeroDep();
  Article* findLeastDep();
  void decDep(Article* b);
  void deleteArticle(Article* a);
  int numArt;
  Article* graph[26];
};

Graph::Graph(){
  numArt=0; 
  for (int i=0;i<26;i++){ 
    Article* a = new Article();
    graph[i]=a;
  }
}
Graph::~Graph(){}

Article* Graph::findZeroDep(){
  for(int i=0;i<26;i++){
    Article* a = this->graph[i];
    if(a->numDepOn==0){
      return a;
    }
  }
  return this->findLeastDep();
}

Article* Graph::findLeastDep(){
  Article* result = this->graph[0];
  int val = result->numDepOn;
  for(int i=1;i<26;i++){
    Article* a = this->graph[i];
    if((a->numDepOn < val)&&(a->numDepOn>0)){
      val = a->numDepOn;
      result = a;
    }
  }return result;

}

void Graph::decDep(Article* b){
  int ascii = ((int)(b->letter))-65;
  if(this->graph[ascii]->letter==(b->letter)){
    this->graph[ascii]->numDepOn -=1;
    return;
  }
}

void Graph::deleteArticle(Article* a){
  int ascii = ((int)(a->letter))-65;
  if(this->graph[ascii]->letter==(a->letter)){
    this->graph[ascii]->numDepOn=-1;
    return;
  }
}

vector<char> topologicalSort(Graph g){
  vector<char> result;
  for(int i=0; i<g.numArt;i++){
    Article* a = g.findZeroDep();
    result.push_back(a->letter);
    for(Article* b: a->dependencies){
      g.decDep(b);
    }
    g.deleteArticle(a);
  }
  return result;
}

void process(vector<string> vec){
  Graph info;
  char s1;
  char s2;
  for(int i=0; i<vec.size();i++){
    s1 = vec[i][0];
    s2 = vec[i][3];
    int ascii1 = ((int)(s1))-65;
    int ascii2 = ((int)(s2))-65;
    if (ascii1>25){
      ascii1 -=32;
      s1 = (char)ascii1;
    }if(ascii2>25){
      ascii2 -= 32;
      s2 = (char)ascii2;
    }
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
    Article* a1 = info.graph[ascii1];
    Article* a2 = info.graph[ascii2];
    (a1->dependencies).push_back(a2);
  }
  vector<char> output = topologicalSort(info);
  for(int i=0;i<output.size();i++){
    cout<<output[i]<<" ";
  }cout<<endl;
  
  for(int i=0;i<26;i++){
    delete info.graph[i];
  }
}


int main(){
  vector<string> test1;
  test1.push_back("A->C");
  test1.push_back("B->D");
  test1.push_back("B->A");
  process(test1);

  vector<string> test2;
  test2.push_back("C->A");
  test2.push_back("A->D");
  test2.push_back("D->B");
  process(test2);

  vector<string> test3;
  test3.push_back("A->B");
  test3.push_back("A->D");
  test3.push_back("B->C");
  test3.push_back("B->E");
  test3.push_back("C->D");
  test3.push_back("C->E");
  process(test3);

  vector<string> test4;
  test4.push_back("A->B");
  test4.push_back("B->C");
  test4.push_back("C->D");
  test4.push_back("D->A");
  process(test4);
  
  return 0;
}
