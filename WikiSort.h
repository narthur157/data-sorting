/** Wikipedia processing tool to take in a simplified file
 * with Wikipedia articles, defined by <TITLE>title</TITLE>
 * containing real text.
 * 
 * stop.txt is a file containing arbitrary stop words which are not
 * considered in analysis
 * 
 * Wiki_small.txt is a test case
 * 
 * 1. determine most frequently used words (top 5%) as well as the
 * 	  article title that each occurs most in and report this in report.txt
 * 	  as: word, #_occurrences, article_title
 * 
 * 2. compute percentage of words which are stop words.  if 'the' is a
 *    stop word, all permutations such as 'THE' and 'thE' also count.
 * 
 * 3. print out all of the words in the article alphabetically and the 
 * 	  number of times they occur, including stop words
 * 
 * Read everything in, strip punctuation, and break it off into chunks 
 * based on <TITLE> tags
 * TODO: data structure for chunks
 * For each chunk: 
 *   - read words into an unordered map with <string, int[]> association. 
 *   The array size is fixed by the number of articles contained
 *   in the file and each entry contains the number of occurrenes of a 
 * 	 string hash per file. 
 * 
 * The number of total words as well as the number of stop words is counted.
 * 
 * Calculate (.05 * wordCount * stopCount) and keep a priority queue that
 * stays at the size of this calculated value, pushing out lower values
 * as higher values are discovered
 * 
 * Store all the keys in a vector, sort the vector alphabetically, and 
 * iterate through the vector, printing their mapped values.
 *   
 */
#ifndef WIKI_SORT_H
#define WIKI_SORT_H
#include <unordered_map>
#include <vector>
#include <iostream>
class WikiSort {
	public:
		void analyze(std::string fileName);	// all we need to expose to the driver
	private:
		bool isStop(std::string s);	// compare hash of lowercase s with hash of every stop word
		void reportTop();		//
		void reportStopWords();
		void readFile();				// read file into the map
		void readFileOptimized();	// optimize later hack sooner
		std::unordered_map<string, int*> stripRetrieve(std::string articles);	// strip punctuation, set articleNames and numTitles
		
        std::unordered_map<std::string, int*> wordMap;
		std::vector<std::string> alphabeticKeys;
		std::string fileName;
		int numTitles;			// the number of articles, also length articleNames
		std::string* articleNames;
		int wordCount;
		int stopCount;
};
#endif
