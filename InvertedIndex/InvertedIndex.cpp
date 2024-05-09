#include <iostream>
#include <fstream>  
#include <chrono> 
#include <thread>
#include <vector> 
#include <string> 
#include <unordered_map> 
using namespace std::chrono; 
using namespace std; 

// numero de archivos y threads
const int THREAD_TOTAL = 5; 
// para guardar (string, archivo en el que aparece)
unordered_map<string, int> cnts[THREAD_TOTAL]; 


// trabajo para cada hilo
// los archivos llevan por nombre file1.txt, file2.txt... 
void thread_work(int id, unordered_map<string, int> &mp) {
    string filename = "file" + to_string(id + 1) + ".txt"; 
    ifstream input(filename, ifstream::binary);
    for(string s; input >> s; ) {
        mp[s] = id + 1; 
    }
}


int main(){
    high_resolution_clock::time_point inicio = high_resolution_clock::now();

    vector<thread> threads; 

    for(int id = 0; id < THREAD_TOTAL; id++) threads.emplace_back(thread_work, id, ref(cnts[id]));
    for(auto& th : threads) th.join();
         
    

    ofstream output("output3.txt");
  
    unordered_map<string, vector<int> > final_map; 

    for(int i = 0; i < THREAD_TOTAL; i++) {
        for(auto &[s, file] : cnts[i]) final_map[s].push_back(file);
    }

    for(auto &[s, v] : final_map) {
        output << s << " \t-> " ; 
        for(int i : v) output << i << " " ; 
        output << "\n"; 
    }

    high_resolution_clock::time_point fin = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double> > (fin - inicio);
    
    cout << "duracion " << time_span.count() << " segundos\n"; 
}   