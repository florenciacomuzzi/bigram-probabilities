//Florencia Salinas-Comuzzi
//Program will calculate bigram probabilities
//C++ 11 or later must be used
//Input: text file and pair of words
//Output: bigram probability

#include <iostream>
#include <map>
#include <string>
//input file stream
#include <fstream>
//#include <cstring>
#include <vector>
#include <iterator>
//using namespace std;




//takes text file names as cmd-line arguments
int main(int argc, const char * argv[]) {
     /*
     std::cout << "Total # of Args= " << argc << "\n";
     std::cout << "prog name= " << argv[0] << std::endl;
     std::cout << "1st argD= " << argv[1] << std::endl;
     */
     
     std::map<std::string,int> wordCount;
     std::map<std::pair<std::string, std::string>,int> pairMap;
     
     //for every file
     for(int i = 1; i < argc; ++i ){
          std::ifstream the_file(argv[i]);
          if (!the_file.is_open()){
               std::cout<< "Could not open file\n";
          }
          else {
               /* TO PRINT FILE TO SCREEN
               char x;
               // the_file.get (x) returns false if the end of the file
               // is reached or an error occurs
               while (the_file.get(x))
                    std::cout<< x;
               */
               
               
               /*  For every word in the file
                     if string has punctuation
                          handle as if no punct
                             if word not present, strip punct else, increment count
               */
               
               std::string str;
               std::string prev = "";
               
               std::pair<std::map<std::string,int>::iterator, bool> p1;
               std::pair<std::map<std::pair<std::string, std::string>,int>::iterator, bool> p2;
               
               
               while(the_file >> str){
                    /*
                     if prev is empty string,
                     you are at beginning of file
                     else, insert word pair
                     */
                    if(prev != ""){
                         std::pair<std::string, std::string> toInsert = std::make_pair(prev, str);
                         p2 = pairMap.emplace(std::map<std::pair<std::string, std::string>,int>::value_type(toInsert, 1));
                         if(!p2.second){
                              p2.first->second++;
                         }
                    }
                    
                    //insert current word
                    p1 = wordCount.emplace(std::map<std::string,int>::value_type(str, 1));
                    if(!p1.second){
                         p1.first->second++;
                    }
                    prev = str;
               }
               
               
                    
                    
               /*
               std::cout << std::endl;
               //now print this map for testing
               for(std::map<std::string,int>::iterator it = wordCount.begin(); it != wordCount.end(); ++it){
                    std::cout << it->first << " appears " << it->second << std::endl;
                    
               }
               */
               
               
               std::string firstWord = "error";
               std::string secWord = "error";
               double denom = 0;
               double num = 0;
               double bigramProb = 0;
               char status = 'n';
               do{
                    std::cout << "Please enter (2) words >";
                    std::cin >> firstWord;
                    std::cin >> secWord;
                    
                    std::map<std::string,int>::iterator denom_prel = wordCount.find(firstWord);
                    if(denom_prel != wordCount.end()){
                         denom = denom_prel->second;
                    }
                    std::map<std::pair<std::string, std::string>,int>::iterator num_prel = pairMap.find(std::make_pair(firstWord,secWord));
                    if(num_prel != pairMap.end()){
                         num = num_prel->second;
                    }
                    
                    if(denom != 0){
                         bigramProb = num/denom;
                         std::cout << "Bigram probability for \"" << firstWord << " " << secWord << "\": " << bigramProb << std::endl;
                    } else {
                         //cannot divide by zero!
                         std::cout << std::endl << "ERROR: could not find " << firstWord << "and cannot divide by 0!\n";
                    }
                    
                    std::cout << std::endl;
                    std::cout << "To go again, enter 'y'>";
                    std::cin >> status;
               }while( status == 'y');
               
          }
     }
     return 0;
}


