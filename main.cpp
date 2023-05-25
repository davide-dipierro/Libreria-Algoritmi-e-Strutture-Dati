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
  - Correggere exists (deve essere costante)
  - Implementare con Vector per facilitare la resize oppure modificare il vettore e renderlo un vettore di liste
  - Correggere gli inline operator() (farne uno solo generale, è più figo)
  - Bitest


************************************************************************** */

void printmap(const int& dat){
  cout<<"\nDAT: "<<dat<<endl;
}

void printfold(const std::string& dat, void* acc){
  cout<<"\nDAT: "<<dat<<endl;
  // *((std::string*)acc) =  *((std::string*)acc)->append(&dat);
}

void temptest() {
  // lasd::HashTableOpnAdr<int> ht(8);
  // for(int i{0}; i<50; i++){
  //   ht.Insert(i);
  //   cout<<"\nVecSize: "<<ht.vecSize<<"\tSize: "<<ht.Size();
  //   ht.CheckDirtyBit();
  //   ht.Remove(i);
  //   cout<<"\nVecSize: "<<ht.vecSize<<"\tSize: "<<ht.Size();
  //   ht.CheckDirtyBit();
  // }
  // ht.Exists(10);
  // ht.Exists(1243);
  // cout<<"\nTEST PASSATO\n";


  // lasd::HashTableOpnAdr<int> ht(8);

  // cout<<"\n\nSituazione iniziale: "; ht.printTable();
  // ht.Insert(6);
  // cout<<"\n\nDopo inserito 6: "; ht.printTable();
  // ht.Insert(5);
  // cout<<"\n\nDopo inserito 5: "; ht.printTable();
  // ht.Insert(13);
  // cout<<"\n\nDopo inserito 13(5): "; ht.printTable();
  // ht.Resize(16);
  // ht.Insert(50);
  // cout<<"\n\nDopo inserito 50(2): "; ht.printTable();
  // ht.Insert(5);
  // cout<<"\n\nDopo inserito 5(Esistente): "; ht.printTable();
  // ht.Insert(-45);
  // cout<<"\n\nDopo inserito -45(3): "; ht.printTable();
  // ht.Insert(2);
  // cout<<"\n\nDopo inserito -45(3): "; ht.printTable();
  

  // cout<<"\nExists(13): "<<ht.Exists(13);
  // cout<<"\nExists(5): "<<ht.Exists(5);
  // cout<<"\nExists(21): "<<ht.Exists(21);
  // cout<<"\nExists(7): "<<ht.Exists(7);

  cout<<"\nVec: ";
  lasd::Vector<int> vec(10);
  for (uint i = 0; i < vec.Size(); i++) {
    vec[i] = pow(-2, i % 24) * ((61 * i + 29) % 127);
  }
  for(int i{0}; i<vec.Size(); i++) cout<<"\t"<<vec[i];

  lasd::HashTableOpnAdr<int> ht(83, vec);
  cout<<"\n\nSIZE: "<<ht.Size();


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
    cout<<"Ecco cosa puoi fare:\n1. Eseguire davtest_ex1()\n2. Eseguire davtest_ex2()\n3. Eseguire lasdtest()\n4. temptest()\n0. Uscire\n";
    cout<<"Inserisci la scelta: ";
    cin>>choose;
    switch(choose){
      case 1 : davtest_ex1(); break;
      case 2 : davtest_ex2(); break;
      case 3 : lasdtest(); break;
      case 4 : temptest(); break;
      case 0 : exit=true;
    }
    cout<<endl<<endl;
  }

  cout<<"GOODBYE!"<<endl;

  return 0;
};