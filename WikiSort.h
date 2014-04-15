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
 * 
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
#include <unordered_map>
#include <iostream>
class WikiSort.h {
	public:
		void analyze(string fileName);	// all we need to expose to the driver
	private:
		bool isStop(string s);	// compare hash of lowercase s with hash of every stop word
		void reportTop();		//
		void reportStopWords();
		unordered_map<string, int*> readFile();				// read file into the map
		unordered_map<string, int*> readFileOptimized();	// optimize later hack sooner
		void stripRetrieve
		unordered_map wordMap;
		string fileName;
		int numTitles;			// the number of articles, also length articleNames
		string[] articleNames;
		int wordCount;
		int stopCount;
		//me trying to edit
}
	
