#include "analyze_time.h"
// #include "sfTree.h"
#include <fstream>

string generateString(int length, string alphabet, unsigned int seed){
    mt19937 random(seed);
    uniform_int_distribution<> letter(0, 25);

    string textString;
    for (int i=0; i<length; i++){
        textString += alphabet[letter(random)];
    }
    return textString;
}

void analyzeBuildFunction(int countRuns, string alphabet, unsigned int seed){
    ofstream outputFile("./dataSuffixBuild.dat");

    mt19937 random(seed);
    uniform_int_distribution<> letter(0, 25);

    for(int currLength = 0; currLength < countRuns; currLength++){
        string testString = generateString(currLength, alphabet, seed);

        auto start = chrono::steady_clock::now();
        SuffixTree sfTree(testString);
        auto end = chrono::steady_clock::now();
        auto time = chrono::duration_cast<chrono::microseconds>(end - start).count();

        outputFile << currLength << " " << time << endl;
    }
    outputFile.close();
}

void analyzeFindFunction(int countRuns, string alphabet, unsigned int seed){
    ofstream outputFile("./dataSuffixFind.dat");
    
    for(int currLength = 0; currLength < countRuns; currLength++){
        mt19937 random(seed);
        uniform_int_distribution<> letter(0, 25);

        string test_string;
        string rand_substring;

        uniform_int_distribution<> substr_pos(0,currLength);

        int rand = substr_pos(random);
    
        for (int k = 0; k < currLength; k++){
            test_string += alphabet[letter(random)];
        }
        SuffixTree sfTree(test_string);
        rand_substring = test_string.substr(min(rand, currLength - rand), max(rand, currLength - rand*2));
        
        auto start_ukk = chrono::steady_clock::now();
        sfTree.Find(rand_substring);
        auto end_ukk = chrono::steady_clock::now();
        auto time_ukk = chrono::duration_cast<chrono::nanoseconds>(end_ukk - start_ukk).count();
        
        auto start_find_function = chrono::steady_clock::now();
        test_string.find(rand_substring);
        auto end_find = chrono::steady_clock::now();
        auto time_find = chrono::duration_cast<chrono::nanoseconds>(end_find - start_find_function).count();

        outputFile << currLength << " " << time_ukk / 10 << " " << time_find / 10 << endl;
    }
    outputFile.close();
}

void analyze_time(string function, int countRuns, unsigned int randSeed){
    random_device generate;
    unsigned int seed;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";

    if (randSeed == 0){
        seed = generate();
    }
    else {
        seed = randSeed;
    }

    cout << "generation_seed: " << seed << endl;

    if (function == "build"){
        analyzeBuildFunction(countRuns, alphabet, seed);
    }
    else if (function == "find"){
        analyzeFindFunction(countRuns, alphabet, seed);
    }
    else return;
}
