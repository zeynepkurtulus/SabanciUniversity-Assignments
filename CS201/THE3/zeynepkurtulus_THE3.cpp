#include <iostream>
#include <string>
using namespace std;

string reverse(string str)
{
    string temp = "";
    for (int i=str.length()-1; i>=0; i--)
        temp += str[i];
    return temp;
}

void ToLower(string & s)
{
    int len = s.length();
    for(int k=0; k < len; k++)
    {
        s[k] = tolower(s[k]);
    }
}

bool isWordNumerical(string s3){
    bool validator = false;
    if (s3 == "")
        validator = true;
    for (int i = 0; i<s3.length(); i++)
    {
        if (s3.at(i)< 58 && s3.at(i) > 47){
            validator = true;
        }
        else {
            validator = false;
        }
    }
    if (validator){
        return true;
    }
    else
    {
        return false;
    }
}

bool inputCheck(string s1)
{
    if (s1.find('.') == -1)
    {
        if (s1.at(0) == '@')
            cout << "Input string should not be empty." << endl;
        else
            cout << "There should be at least one sentence." << endl;
        return false;
    }
    else
    {
        bool validation2 = true;
        int pos = 0;
        for (int i = 0; i < s1.length(); i++)
        {
            if (s1.at(i) == ' ')
            {
                string refer = s1.substr(pos,(i-pos));
                if (isWordNumerical(refer)){
                    validation2 = false;
                }
                pos = i+1;
            }
            else if (s1.at(i) == '.')
            {
                string refer2 = s1.substr(pos,(i-pos));
                if (isWordNumerical(refer2)){
                    validation2 = false;
                }
                pos = i+2;
            }
        }
        if (validation2 == false)
        {
            cout << "There should be no words without alphabetical characters." << endl;
            return false;
        }
        else
        {
            return true;
        }
    }

}
void PrintResult(string word)
{
    int sentenceCountTotal = 0;
    int i = 0;
    int pos = word.length();
    string wordStack;
    string sentenceStack;
    
    while (i<word.length())
    {
        if(word.at(i) == '.')
            sentenceCountTotal++;
        i++;
    }
    int sentenceCount = sentenceCountTotal+1;
    for (int j = word.length()-1; j >= 0; j--)
    {
        if (word.at(j) == '.')
        {
            sentenceCount--;
            string refer = word.substr(j+2,(pos-j)-1);
            wordStack = refer;
            if (wordStack.length() == 1)
            {
                sentenceStack = wordStack;
                wordStack.erase();
            }
            else
            {
                wordStack.push_back(' ');
                int k= 0;
                int pos1= 0;
                while (k < wordStack.length())
                {
                    if(wordStack.at(k) == ' ')
                    {
                        string refer2 = wordStack.substr(pos1,(k-pos1));
                        string temp = refer2;
                        temp = reverse(temp);
                        if(temp == refer2)
                        {
                            temp = temp + ' ';
                            sentenceStack.insert(0,temp);
                        }
                        else
                        {
                            sentenceStack.insert(0,"notpalindrome ");
                        }
                        pos1 = k+1;
                    }
                    k++;
                }

            }
            pos = j-1;
            cout << "Sentence (" << sentenceCount << '/' << sentenceCountTotal << "):" << endl;
            if(sentenceStack.length() != 1)
                sentenceStack.pop_back();
            cout << sentenceStack << endl;
            sentenceStack.erase();
        }
    }

}

string RemoveNonLetters(string word)
{
    string temp = "";
    for (int i = 0; i < word.size(); i++)
    {
        if (((word[i] >= 'a' && word[i] <= 'z') || (word[i] >= 'A' && word[i] <= 'Z')) || word[i] == '.' || word[i] == ' ')
        {
            temp = temp + word[i];
        }
    }
    word = temp;
    ToLower(word);
    return word;
}
int main()
{
    string s,word,l,word1;
    bool isValid=false;
    while (!isValid)
    {
        cout << "Please enter the input sentences: ";
        while (cin >> l)
        {
            if (l == "@")
            {
                if (word.length() == 0)
                    word = "@ ";
                break;
            }
            else
            {
                word = word + l +' ';
            }
        }
        
        word.pop_back();
        isValid = inputCheck(word);
        cout << endl;
        if (isValid == false)
            word.erase();
    }
    word = RemoveNonLetters(word);
    word.pop_back();
    word.insert(0," ");
    word.insert(0,".");
    PrintResult(word);
    return 0;

}
