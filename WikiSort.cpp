#include "WikiSort.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <boost/algorithm/string.hpp>
#include <iomanip>
#include <map>
    // Nick
    // George
    // Arthur
    // NGA
    
using namespace std;

WikiSort::WikiSort(): grandCount(0), nonStopCount(0), stopCount(0), numTitles(0) {
	
}
void WikiSort::analyze(string f) {
	
	fileName=f;
	readFile();
	reportAlpha();
	reportStop();
    reportTop();
    
    /*
	int uniqueNonStop = 0;
	int uniqueStop = 0;
    for (unordered_map<string, vector<int>>::iterator it=wordAcc.begin(); it != wordAcc.end(); it++) {
    	cout << setw(15) << it->first << "~ ";
    	int topFive = grandCount * .05;
    	if (isStop(it->first)) {
    		stopCount+= sumVec(it->second);
    		uniqueStop++;
    	}
    	else {
    		nonStopCount+= sumVec(it->second);
    		uniqueNonStop++;
    	}
    	for (int n = 0; n < it->second.size(); n++)
	    	cout << titles[n] << ":" << it->second[n] << " | ";
	    
	    cout << endl << endl;
    }
//    for (unordered_set<string>::iterator it=stopWords.begin(); it != stopWords.end(); it++) 
    //	cout << *it << endl;
    
    cout << "Grand Count: " << grandCount << " Stop Count: " << stopCount << " Non-Stop Count: " << nonStopCount << endl;
    cout << "Unique stop count: " << uniqueStop << " Unique non-stop count: " << uniqueNonStop << endl;*/
    
}
int WikiSort::sumVec(vector<int> v) {
	int total = 0;
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++) total += *it;
	return total;
}

bool WikiSort::isStop(string s) {
	boost::algorithm::to_lower(s);
    unordered_set<string>::iterator element = stopWords.find(s);
    /*if (element != stopWords.end()) {
    	stopCount++;
    	return true;
    }
    else return false;*/
    return element != stopWords.end();
}
int WikiSort::vecMax(vector<int> a) {
	int max=0;
	for (int i = 0; i < a.size(); i++) if (a[i] > a[max]) max = i;
	return max; 
}
void WikiSort::reportTop(){
	vector<string> values;
	int topFive = grandCount * 0.05;
	//cout << "top five: " << topFive << endl;
	int oldMax = -1;
	int maxVal=-1;
	string maxWord="";
	ofstream out("report.txt");
	vector<int> keepVec;
	for (int i = 0; i < topFive; i++) {
		if (wordAcc.empty()) break;		
		maxVal=0;
		for (const auto& kv : wordAcc) {
			if (!isStop(kv.first)) {
				if (sumVec(kv.second) > maxVal) {
					maxVal = sumVec(kv.second);
					maxWord = kv.first;
					keepVec = kv.second;
				}
			}
		}
		wordAcc.erase(maxWord);
		oldMax=maxVal;
		out << maxWord << ", " << maxVal << ", " << titles[vecMax(keepVec)] << endl;
		//cout << "Top:" << i << " Count:" << maxVal << " Word:<" << maxWord << ">" << endl;
	}
	bool tied = true;
	string oldWord = maxWord;
	while (tied) {
		
		for (const auto& kv : wordAcc) {
			if (!isStop(kv.first)) {
				if (sumVec(kv.second) == maxVal) {
					maxVal = sumVec(kv.second);
					maxWord = kv.first;
					keepVec = kv.second;
				}
			}
		}
		if (oldWord == maxWord) tied=false;
		else {
			wordAcc.erase(maxWord);
			oldWord=maxWord;
			out << maxWord << ", " << maxVal << ", " << titles[vecMax(keepVec)] << endl;
			//cout << "Count:" << maxVal << " Word:<" << maxWord << ">" << endl;
		}
	}
}
void WikiSort::reportAlpha() {
	// put keys into a vector for sorting
	for(auto wordPair: wordAcc) {
		alphabeticKeys.push_back(wordPair.first);
	}
	sort(alphabeticKeys.begin(), alphabeticKeys.end());
	ofstream sortedFile("sorted_words.txt");
	for (auto key : alphabeticKeys) {
		sortedFile << key << " " << sumVec(wordAcc[key]) << endl;
	}
	
}
void WikiSort::reportStop() {
	float total = 0;
	float stop = 0;
	for (auto wordPair : wordAcc) {
		if (isStop(wordPair.first)) stop+= sumVec(wordPair.second);
		total+=sumVec(wordPair.second);
	}	
	cout << (stop/total) * 100 << "% stop words" << endl;
}
void WikiSort::insertWord(string s, int n) {
	// insert string s into wordAcc and increment position n in wordAcc int vector
	unordered_map<string, vector<int>>::iterator it;
	it = wordAcc.find(s);
	if (it != wordAcc.end()) {
		//if (it->second.size() == n) it->second.push_back(1);
		if (it->second.size() <= n) {
			for (int i = 0; i < (it->second.size()-n); i++) it->second.push_back(0);
			it->second.push_back(1);
		}
		else (it->second)[n]++;
	}
	else {
		// insert a pair with string s and a vector	with size one holding one one
		//wordAcc.insert(pair<string, vector<int>>(s, vector<int>(1,1)));
		pair<string, vector<int>> emptyPair(s, vector<int>(numTitles,0));
		wordAcc.insert(emptyPair);
		insertWord(s,n);
		grandCount++;
	}
}


void WikiSort::readFile() {
    ifstream input(fileName);
    stringstream words;
    string line;
    string word;
    while (getline(input, line)) {
    	words.clear();
    	words.str(line);
    	while (words >> word)
	        articleVec.push_back(word);
    }
    input.close();
    input.open("stop.txt");
    while (getline(input, line)) {
    	stopWords.emplace(line);
    }
   stripRetrieve();
}

string noPunc(string word) {
    // remove punctuation, return new string.  recursive, also make lowercase
    if (ispunct(word.front())) 
        return noPunc(word.substr(1, word.size()-1));
    else if (ispunct(word.back())) 
        return noPunc(word.substr(0, word.size()-1));
    else return word;
}
void WikiSort::stripRetrieve() {
    // handle titles separately
    stringstream returnString;
    stringstream titleString;
    string iteratorBugFix;
    for (vector<string>::iterator it=articleVec.begin(); it != articleVec.end(); it++) 
    {
        // iterating through vector containing words in article
        iteratorBugFix = *it;
        if (iteratorBugFix.size() > 0 && iteratorBugFix.at(0) == '<' && iteratorBugFix == "<TITLE>") 
        {    
               // found title
                it++;    // next word
                numTitles++;
                titleString.str("");
                string s = *it;
                int count = 0;
                while (s != "<\\TITLE>")//s.compare("</TITLE>") == 0) 
                {
                    titleString << s << " ";
                    it++;
                    s=*it;
                }
//                titleString
                // title text has been iterated through
                titles.push_back(titleString.str().erase(titleString.str().size()-1)); // next iteration starts body of article
            
        }
        else 
        {
        	// body text
        	string word=*it;
        	word = noPunc(word);
        	if (word.size() > 0) insertWord(word, numTitles-1);
        }     
    }
}
