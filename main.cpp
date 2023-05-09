#include "zmytest/test.hpp"

#include "zlasdtest/test.hpp"

/* ************************************************************************** */

#include <iostream>
using namespace std;

#include "stack/vec/stackvec.hpp"
#include "queue/vec/queuevec.hpp"
#include "queue/lst/queuelst.hpp"
#include "stack/lst/stacklst.hpp"

#include "binarytree/binarytree.hpp"
#include "binarytree/lnk/binarytreelnk.hpp"
#include "iterator/iterator.hpp"
#include "bst/bst.hpp"

#include "vector/vector.hpp"
#include "list/list.hpp"

/* **************************************************************************

ALL'INTERNO DI CONTAINER.HPP E' STATO DEFINITO IL TIPO ULONG

NOTE:
- BinaryTreeLnk.hpp il distruttore di Nodo deve cancellare anche i figli?
- Il prof pare che tiene l'operator == e != negli iterator come  =0 o =delete o default
- Il MAKEFILE o i file oggetto generati nelle cartelle possono causare problemi alla compilazione del prof?
- Perché dovrei riscrivere la clear in BST? Non va bene quella da BT e perché eredito da Clearable Container se già BT?

TODO:
- Aggiungere eccezione a IsLeaf

************************************************************************** */

void print(int value){
  cout<<"\t"<<value;
}

void print2(int value, bool acc){
  cout<<"\t"<<value;
}

void temptest(){
  lasd::Vector<int> v1(15);
  for(int i{0}; i<v1.Size(); i++) v1[i]=v1.Size()-i;
  lasd::Vector<int> v2(15);
  for(int i{0}; i<v2.Size(); i++) v2[i]=i;

  lasd::BST<int> bst1;
  // lasd::BST<int> bst2;

  bst1.Insert(5);
  bst1.Insert(1);
  bst1.Insert(3);
  bst1.Insert(7);
  bst1.Insert(2);
  bst1.Insert(4);
  bst1.Insert(9);
  bst1.Insert(8);


  cout<<"\nBST1("<<bst1.Size()<<") Breadth: ";
  bst1.BreadthMap(print);cout<<endl;
  cout<<"\nBST1("<<bst1.Size()<<") InOrder: ";
  bst1.InOrderMap(print);cout<<endl;



  // // v2[4]=100;

  // lasd::BinaryTreeLnk<int> bt1(v1);
  // lasd::BinaryTreeLnk<int> bt2(v2);

  // cout<<"BT1==BT2: "<<(bt1==bt2);

  // cout<<"\nVettore:";
  // for(int i{0}; i<10; i++) print(i);

  // bool acc = false;

  // cout<<"\nBT Fold:";
  // bt1.Fold(print2, (void*)acc);
  
  // cout<<"\nBT PreOrderFold::";
  // bt1.PreOrderFold(print2, (void*)acc);

  // cout<<"\nBT PostOrderFold::";
  // bt1.PostOrderFold(print2, (void*)acc);

  // cout<<"\nBT InOrderFold::";
  // bt1.InOrderFold(print2, (void*)acc);

  // cout<<"\nBT BreadthFold::";
  // bt1.BreadthFold(print2, (void*)acc);

  // cout<<"\nBT Map:";
  // bt1.Map(print);

  // cout<<"\nBT Breadth:";
  // bt1.BreadthMap(print);

  // cout<<"\nBT InOrder:";
  // bt1.InOrderMap(print);

  // cout<<"\nBT PostOrder:";
  // bt1.PostOrderMap(print);

  // cout<<"\nBT PreOrder:";
  // bt1.PreOrderMap(print);

  // cout<<"\nBT1 size: "<<bt1.Size()<<"\nBT2 size: "<<bt2.Size();

  // lasd::BinaryTreeLnk<int> bt3(bt1);
  // cout<<"\nBT1 Map:";
  // bt1.BreadthMap(print);
  // cout<<"\nBT3 Map:";
  // bt3.BreadthMap(print);

  // cout<<"\nUguali 3=1: "<<(bt3 == bt1);

  // bt1.Clear();
  // cout<<"\nBT1.Clear(): "<<(bt1.Empty());

  // cout<<"\nBT1 Map:";
  // bt1.BreadthMap(print);
  // cout<<"\nBT3 Map:";
  // bt3.BreadthMap(print);

  // bt1 = move(bt3);

  // cout<<"\nDopo la move\nBT1 Map:";
  // bt1.BreadthMap(print);
  // cout<<"\nBT3 Map:";
  // bt3.BreadthMap(print);

  // cout<<"\nUguali 3=1: "<<(bt3 == bt1);


  // cout<<"\nbt3.Empty(): "<<(bt3.Empty());

  // cout<<"\nBT1 size: "<<bt1.Size()<<"\nBT2 size: "<<bt2.Size()<<"\nBT3 size: "<<bt3.Size();

  
  // cout<<"\nBT1 Breadth:";
  // bt1.BreadthFold(print2, (void*)acc);
  // cout<<"\nBT2 Breadth:";
  // bt2.BreadthFold(print2, (void*)acc);
  // cout<<"\nBT3 Breadth:";
  // bt3.BreadthFold(print2, (void*)acc);

  cout<<endl;
}

int main(){

  // temptest();

  int choose;
  bool exit=false;
  while(!exit){
    std::cout << R"(
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⡶⠿⠿⠷⣶⣄⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣰⡿⠁⠀⠀⢀⣀⡀⠙⣷⡀⠀⠀⠀
⠀⠀⠀⡀⠀⠀⠀⠀⠀⢠⣿⠁⠀⠀⠀⠘⠿⠃⠀⢸⣿⣿⣿⣿
⠀⣠⡿⠛⢷⣦⡀⠀⠀⠈⣿⡄⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣿⠟
⢰⡿⠁⠀⠀⠙⢿⣦⣤⣤⣼⣿⣄⠀⠀⠀⠀⠀⢴⡟⠛⠋⠁⠀
⣿⠇⠀⠀⠀⠀⠀⠉⠉⠉⠉⠉⠁⠀⠀⠀⠀⠀⠈⣿⡀⠀⠀⠀
⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⡇⠀⠀⠀
⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⡇⠀⠀⠀
⠸⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⡿⠀⠀⠀⠀
⠀⠹⣷⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣰⡿⠁⠀⠀⠀⠀
⠀⠀⠀⠉⠙⠛⠿⠶⣶⣶⣶⣶⣶⠶⠿⠟⠛⠉⠀⠀
)"<<endl;

    cout<<R"(
    __     ___    _____    ____ 
   / /    /   |  / ___/   / __ \
  / /    / /| |  \__ \   / / / /
 / /___ / ___ | ___/ /  / /_/ / 
/_____//_/  |_|/____/  /_____/                          
    )"<<endl;
    std::cout << "Libraries 2023" << std::endl<<std::endl;
    cout<<"Ecco cosa puoi fare:\n1. Eseguire davtest()\n2. Eseguire lasdtest()\n3. temptest()\n0. Uscire\n";
    cout<<"Inserisci la scelta: ";
    cin>>choose;
    switch(choose){
      case 1 : davtest(); break;
      case 2 : lasdtest(); break;
      case 3 : temptest(); break;
      case 0 : exit=true;
    }
    cout<<endl<<endl;
  }

  return 0;
};