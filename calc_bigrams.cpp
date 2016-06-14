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


template <typename T>
void printDict(std::map<T,int>&);

template <typename T>
void calcBigramProb(std::map<T,int>& dictionary, std::map<std::pair<T, T>,int>& pairDict, std::pair<T,T>& input);

std::pair<std::string,std::string> getInput(void);

template <typename T>
void play(std::map<T,int>& dictionary, std::map<std::pair<T, T>,int>& pairDict);


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
    
    play(wordCount, pairMap);
    
    std::cout << "Goodbye.\n";
    return 0;
}


template <typename T>
void play(std::map<T,int>& dictionary, std::map<std::pair<T, T>,int>& pairDict){
    int playing = 1;
    while(playing == true){
        auto input = getInput();
        calcBigramProb(dictionary, pairDict, input);
        std::cout << "To try another pair, press 1 >";
        std::cin >> playing;
        std::cout << std::endl;
    }
    return;
}


template <typename T>
void printDict(std::map<T,int>& dictionary){
    std::cout << std::endl << "************" << std::endl;
    std::cout << "\nNow printing list of words...\n";
    for(typename std::map<T,int>::iterator it = dictionary.begin(); it != dictionary.end(); ++it){
        std::cout << it->first << " appears " << it->second << " time(s)"<< std::endl;
    }
    std::cout << std::endl << "************"<< std::endl;
    return;
}



std::pair<std::string,std::string> getInput(void){
    std::string word1 = "";
    std::string word2 = "";
    std::cout << "Please enter (2) words >";
    std::cin >> word1;
    std::cin >> word2;
    return std::make_pair(word1, word2);
}


template <typename T>
void calcBigramProb(std::map<T,int>& dictionary, std::map<std::pair<T, T>,int>& pairDict, std::pair<T,T>& input){
    T firstWord = input.first;
    T secWord = input.second;
    
    double bigramProb = 0;
    
    //if pair appears together, at least 1 instance of 1st word so denom will never equal 0
    //if pair never appears together, num = 0
    typename std::map<std::pair<T, T>,int>::iterator bigram = pairDict.find(input);
    if(bigram != pairDict.end()){
        double unigramFreq = dictionary[firstWord];
        double bigramFreq = bigram->second;
        bigramProb = bigramFreq/unigramFreq;
    }
    
    std::cout << "Bigram probability for \"" << firstWord << " " << secWord << "\": " << bigramProb << std::endl;
    return;
}



