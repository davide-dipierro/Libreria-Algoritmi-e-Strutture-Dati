#include "zmytest/test.hpp"

#include "zlasdtest/test.hpp"

/* ************************************************************************** */

#include <iostream>
#include <bitset>

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

#include "hashtable/hashtable.hpp"
#include "hashtable/clsadr/htclsadr.hpp"
#include "hashtable/opnadr/htopnadr.hpp"

/* **************************************************************************

ALL'INTERNO DI CONTAINER.HPP E' STATO DEFINITO IL TIPO ULONG


TODO:
  - Mancano i test sulle resize e su vecSize

NOTE:
  - Se chiamo una clear ad una HT che ho utilizzato con move, che deve succedere?
  - Resize a N<Size() mi crea una HT comunque sufficiente a contenere tutti gli elementi
  - Perché devo richiamare i costruttori?
  - Perché lo swap tra *this e *tmp mi da errore e mi chiama il move constructor?

************************************************************************** */

void printmap(const int& dat){
  cout<<"\nDAT: "<<dat<<endl;
}

void temptest() {
  // cout<<"\n\tEMPTY TEST\n";  
  lasd::HashTableClsAdr<int> ht1;
  lasd::HashTableOpnAdr<int> ht2;

  // cout<<"\nARE EQUALS: "<<(ht1.HashTable<int>::operator==(ht2));

  // ht1.Insert(1);ht2.Insert(1);
  // ht1.Insert(2);ht2.Insert(2);
  // ht1.Insert(3);ht2.Insert(3);

  // cout<<"\nARE EQUALS: "<<(ht1.HashTable<int>::operator==(ht2));

  // ht1.Remove(1);

  // cout<<"\nARE DIFFERENT: "<<(ht1.HashTable<int>::operator!=(ht2));

  // ht1.Insert(5);
  
  // cout<<"\nARE DIFFERENT: "<<(ht1.HashTable<int>::operator!=(ht2));

  // lasd::List<int> l1;
  // for(int i=0; i<200; i++) l1.Insert(1+(i*16));

  // lasd::Vector<int> vec(127);
  // for (uint i = 0; i < 10; i++) {
  //   vec[i] = pow(-2, i % 24) * ((61 * i + 29) % 127);
  // }
  // ht.InsertAll(vec);
  // ht.printTable();

  // for(int i=0; i<6; i++) ht.Remove(i+1);
  // ht.printTable();

  // ht.Remove(5+(16*3));
  // ht.Remove(5+(16*2));
  // // ht.Remove(5+(16*1));
  // ht.printTable();

  // ht.Exists(5+(16*4));
  // cout<<"\nDOPO EXISTS INSERT:";
  // ht.printTable();

  // ht.Clear();
  // for(int i=0; i<5; i++) ht.Insert(5+(16*i));
  // ht.printTable();

  // ht.Remove(5+(16*1));
  // ht.Remove(5+(16*2));
  // ht.Remove(5+(16*3));
  // ht.printTable();

  // cout<<"\nDOPO EXISTS REMOVE:";
  // ht.Exists(5+(16*4));
  // ht.printTable();



}

int main(){

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
    cout<<"Ecco cosa puoi fare:\n1. Eseguire davtest_ex1()\n2. Eseguire davtest_ex2()\n3. Eseguire davtest_ex3()\n4. Eseguire lasdtest()\n5. temptest()\n0. Uscire\n";
    cout<<"Inserisci la scelta: ";
    cin>>choose;
    switch(choose){
      case 1 : davtest_ex1(); break;
      case 2 : davtest_ex2(); break;
      case 3 : davtest_ex3(); break;
      case 4 : lasdtest(); break;
      case 5 : temptest(); break;
      case 0 : exit=true;
    }
    cout<<endl<<endl;
  }

  cout<<"GOODBYE!"<<endl;

  return 0;
};