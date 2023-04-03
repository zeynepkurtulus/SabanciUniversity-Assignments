#include <iostream>
#include <string>

using namespace std;


string getInput(){
    string res = "", word;
    cout << "Please enter the input sentences: ";
    while(cin>>word && word != "@"){
        res += (word + " ");
    }
    res = res.substr(0, res.length()-1);
    return res;
}


bool isUpper(char c){
    return (c>='A' && c<='Z');
}


bool isLower(char c){
    return (c>='a' && c<='z');
}


bool isNonAlpha(char c){
    return !(isUpper(c) || isLower(c));
}


void toLower(string & s){
    for(int i =0; i<s.length(); i++){
        if(isUpper(s.at(i))){
            // s= s.substr(0, i) + ('a' + s.at(i) - 'A') + s.substr(i+1, s.length());
            s[i]= ('a' + s.at(i) - 'A');
        }
    }
}


bool isAllNonAlphabetical(string word){
    bool result = true;
    for(int i=0; i<word.length() && result; i++){
        if(!isNonAlpha(word.at(i))){
            result = false;
        }
    }
    return result;
}


bool isAllWordsValid(string s){
    string word;
    int index;
    bool result = true;
    while(s.find(" ") != string::npos && result){
        index = s.find(" ");
        word = s.substr(0, index);
        s = s.substr(index+1, s.length());
        if(isAllNonAlphabetical(word)){
            result = false;
        }
    }
    if(isAllNonAlphabetical(s)){
        result = false;
    }
    return result;
}


bool inputCheck(string s){
    bool res = true;
    if(s.length() == 0){
        cout << "Input string should not be empty." << endl;
        res = false;
    }
    else if(s.find(".") == string::npos){
        cout << "There should be at least one sentence." << endl;
        res = false;
    }
    else if(!isAllWordsValid(s)){
        cout << "There should be no words without alphabetical characters." << endl;
        res = false;
    }
    cout << endl;
    return res;
}


string eliminateNonAlpha(string s){
    for(int i=0; i<s.length(); i++){
        if(isNonAlpha(s.at(i)) && s.at(i) != ' ' && s.at(i) != '.'){
            s = s.substr(0,i) + s.substr(i+1, s.length());
            i--;
        }
    }
    return s;
}


int countSentences(string s){
    int res = 0, index;
    while(s.find(".") != string::npos){
        index = s.find(".");
        s = s.substr(index+1, s.length());
        res++;
    }
    return res;
}


bool isPalindrome(string s){
    bool res = true;
    for(int i=0; i<s.length()/2 && res; i++){
        if(s.at(i) != s.at(s.length()-i-1)){
            res = false;
        }
    }
    return res;
}


void processReverse(string s){
    string word;
    int index;
    while(s.rfind(" ") != string::npos){
        index = s.rfind(" ");
        word = s.substr(index+1, s.length());
        s = s.substr(0, index);
        if(isPalindrome(word)){
            cout << word << " ";
        }
        else{
            cout << "notpalindrome ";
        }
    }
    if(isPalindrome(s)){
        cout << s << endl;
    }
    else{
        cout << "notpalindrome" << endl;
    }
}


void runner(){
    string input;
    do{
        input = getInput();
    }while(!inputCheck(input));
    input = eliminateNonAlpha(input);
    toLower(input);
    int nofSentences = countSentences(input);
    for(int i=0; i<nofSentences; i++){
        cout << "Sentence (" << nofSentences-i << "/" << nofSentences << "):" << endl;
        int index = input.substr(0, input.length()-1).rfind(".");
        string sentence = input.substr(index+1, input.length());
        if(sentence.at(0) == ' '){
            sentence = sentence.substr(1, sentence.length());
        }
        sentence = sentence.substr(0, sentence.length()-1);
        input = input.substr(0, index+1);
        processReverse(sentence);
    }
}


int main(){
    runner();
    return 0;
}