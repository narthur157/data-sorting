#include "WikiSort.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <boost/algorithm/string.hpp>
    // Nick
    // George
    // Arthur
    // NGA
    
using namespace std;

void WikiSort::analyze(string fileName) {
    wordMap=readFile();
    
    
}

bool WikiSort::isStop(string s) {
    
}

void WikiSort::reportTop(){

}

void WikiSort::reportStopWords() {

}

void WikiSort::readFile() {
    ifstream input(fileName);
    sstream articleStream = "";
    sstream articles = ""
    while (input >> articleStream) {
        // do nothing
    }
    wordMap=stripRetrieve(to_string(articleStream));
}

string noPunc(string word) {
    // remove punctuation, return new string.  recursive
    if (is_punc(word.front())) 
        return noPunc(word.substr(1, word.size()-1);
    else if (is_punc(word.back())) 
        return noPunc(word.substr(0, word.size()-1);
    else return word;
}
unordered_map<string, int[numArticles]> WikiSort::stripRetrieve(string articles) {
    // handle titles separately
    sstream returnString;
    vector<string> articleVec;
    vector<string> titles;
    sstream titleString;
    // get first title
    boost::split(articleVec,articles,boost::is_any_of("\\w+"));
    sstream ifs( articles );
    string val;
    while( ifs >> val)
       articleVec.push_back( val );
    
    for (vector<string>::iterator it=articleVec.begin; *it != nullptr; it++) 
    {
        // iterating through vector containing words in article
        if (*it.at(0) == '<') 
        {    // performance hack
            if (*it == "<TITLE>") 
            {   // found title
                it++;    // next word
                numArticles++;
                titleString = "";
                while (*it != "</TITLE>") 
                {
                    titleString << noPunc(*it) << " ";
                    it++;
                }
                // title text has been iterated through
                titles.push_back(to_string(titleString)); // next iteration starts body of article
            }
        }
        // if we're here, we're not looking at a title
        
    }
}
