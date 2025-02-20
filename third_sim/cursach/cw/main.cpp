#include "sfTree.h"
#include "analyze_time.h"
using namespace std;

int main(){
    string text = "abcabbd";
    SuffixTree sfTree(text);

    sfTree.PrintSuffixs();

    analyze_time("find", 50, 1234567890);
}