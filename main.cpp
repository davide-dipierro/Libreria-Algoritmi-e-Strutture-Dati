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
  std::bitset<2> bits[10];

  for(int i{0}; i<10; i+=2) cout<<"i: "<<bits[i][0]<<"\t"<<bits[i][1]<<endl;

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