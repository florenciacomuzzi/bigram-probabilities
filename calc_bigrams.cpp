//Florencia Salinas-Comuzzi
//Program will calculate bigram probabilities
//C++ 11 or later must be used
//Input: text file and pair of words
//Output: bigram probability

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>


template <typename T, typename K>
void printDict(std::map<T,K>);


int main(int argc, const char * argv[]) {
    
    std::map<std::string,int> wordCount;
    std::map<std::pair<std::string, std::string>,int> pairMap;
    
    for(int i = 1; i < argc; ++i ){
        std::ifstream the_file(argv[i]);
        if (!the_file.is_open()){
            std::cout<< "Could not open file(s)";
            exit(-1);
        }

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
    }
    
    printDict(wordCount);
            

    bool playing = true;
    while(playing){
        std::string firstWord;
        std::string secWord;
        double bigramProb = 0;
        
        std::cout << "Please enter (2) words >";
        std::cin >> firstWord;
        std::cin >> secWord;
                
        std::map<std::string,int>::iterator unigram1 = wordCount.find(firstWord);
        std::map<std::string,int>::iterator unigram2 = wordCount.find(secWord);
        std::map<std::pair<std::string, std::string>,int>::iterator bigram = pairMap.find(std::make_pair(firstWord,secWord));
        if(unigram1 != wordCount.end() && unigram2 != wordCount.end()){
            double unigramProb = unigram1->second;
            double bigramCount = bigram->second;
            bigramProb = bigramCount/unigramProb;
        }
        std::cout << "Bigram probability for \"" << firstWord << " " << secWord << "\": " << bigramProb << std::endl;
        std::cout << "To try another pair, press 1 >";
        std::cin >> playing;
        std::cout << std::endl;
    }
    std::cout << "Goodbye.\n";
    return 0;
}



template <typename T, typename K>
void printDict(std::map<T,K> dictionary){
    std::cout << std::endl << "************" << std::endl;
    std::cout << "\nNow printing list of words...\n";
    for(typename std::map<T, K>::iterator it = dictionary.begin(); it != dictionary.end(); ++it){
        std::cout << it->first << " appears " << it->second << " time(s)"<< std::endl;
    }
    std::cout << std::endl << "************"<< std::endl;
    return;
}

template <typename T, typename K>
void calcBigramProb(std::map<T,K>);

                

