#include <iostream>
#include<string.h>
#include<map>
#include<fstream>
#include<cctype>
int countSname =0;
int countReal =0;
int countInt =0;
int tokenCount = 0;
using namespace std;
string word = "";
string wordTemp="";

class Project{
public:
    void sort(string s[], int n)
    {
        for (int i=1 ;i<n; i++)
        {
            string temp = s[i];

            // Insert s[j] at its correct position
            int j = i - 1;
            while (j >= 0 &&(stof(temp) - stof(s[j]))<0 )
            {
                s[j+1] = s[j];
                j--;
            }
            s[j+1] = temp;
        }
    }
    ///////////////////////////////////////
    bool checkInt() {
        bool intCheck =false;
        if ( (word.at(0) == '-') || (isdigit(word.at(0)))) {
            intCheck = true;
        }
        if(intCheck==true) {
            intCheck = false;
            for (int i = 1; i < word.length(); i++) {
                if (isdigit(word.at(i))) {
                    intCheck = true;
                } else return false;
            }
        }
        return intCheck;
    }
    bool checkReal( ) {
        bool check =false;
        tokenCount =0;
        if (( (word.at(0) == '-') || (isdigit(word.at(0))))) {
            check = true;
        }
        if(word.at(0)=='.'||word.at(word.length()-1)=='.'){
            check=false;
        }
        ////////////////////////
        for(char i : word){
            if(i=='.'){
                tokenCount+=1;
            }
        }
        if((word.at(0)=='-') ){
            if( 2<=word.length() && (word.at(1)=='.')) {
                check = false;
            }
        }
        ////////////////////////////////////////
        if (check == true && tokenCount==1 ) {
            for (int i = 1; i < word.length(); i++) {
                check = false;
                if (isdigit(word.at(i)) || word.at(i) == '.') {
                    check = true;
                }
            }return check;
        }
        return false;
    }};
///////////////////////////////////////////////////////////////////////////////////
int main(int arg, char *argv[]) {
    Project obj;
    fstream file;
    string filename = "";
    ///////////////Test file availality///////////////////
    if (arg > 1) {
        filename = argv[1];
    }
    string line;
    int countInt = 0;
    int countReal = 0;
    int countSname = 0;
    if (filename.empty()) {
        cout << "NO SPECIFIED INPUT FILE NAME." << endl;
        exit(0);
    }
    string filename2 = filename+".txt";
    file.open(filename2, ios::in);
    if (!file.is_open()) {
        cout << "CANNOT OPEN THE FILE " << filename << endl;
        exit(1);
    }
    map<string, int> Sname;
    map<string, int> Int;
    map<string, int> Real;

    ifstream filee(filename2, ios::binary | ios::ate);
    if (filee.tellg() < 1) {
        cout << "File is empty.\n";
        exit(1);
    }
    //////////end////////////////////

    while (file >> wordTemp) {

        if((wordTemp.at(0)=='+') && wordTemp.length()>2){
            int i = (wordTemp.length()-1);
            word =wordTemp.substr(1,i);
        }else word = wordTemp;
/////////////////////////////////////////Test INT//////////////////////////////////

        /////////////////////Test Real/////////////////////////////////
        if (obj.checkReal( ) ) {
            countReal+=1;
            if((word.length()==6)&&(word.at(3)=='.')&&(word.at(5)=='0')){
                word.erase(5);

            }

            if (Real.count(word) < 0) {
                Real[word] = 1;
            } else {
                Real[word] = Real[word] + 1;
            }
        } else if (obj.checkInt()== true) {
            countInt+=1;
            if (Int.count(word) < 0) {
                Int[word] = 1;
            } else {
                Int[word] = Int[word] + 1;
            }
////////////////Test word///////////////////////////
        } else if (word.at(0) == '$' && isalpha(word.at(1)) && word.at(word.length()-1)!='$'&& word.at(word.length()-1)!=',') {
            countSname+=1;
            if (Sname.count(word) < 0) {
                Sname[word] = 1;
            } else {
                Sname[word] = Sname[word] + 1;
            }
        }
    }
    map<string, int>::iterator itS = Sname.begin();
    map<string, int>::iterator itI = Int.begin();
    map<string, int>::iterator itR = Real.begin();
    ////////////display
    cout<<"Number of integers in the file: "   <<countInt    <<endl;
    cout<<"Number of reals in the file: "   <<  countReal  <<endl;
    cout<<"Number of special names in the file: "   <<countSname    <<endl;
    //cout<<endl;
    /////////////////////
    ///////////////////////////////////////////////
//cout<< Real.size() <<endl;
    string realArr[Real.size()];
   // cout<<"\n" <<sizeof(realArr);
    string intArr[Int.size()];
    for(int i =0; i<Real.size();i++){

        if(itR!=Real.end()){
            realArr[i]= (itR->first);
        }
        ++itR;

    }
    for(int j=0; j<Int.size();j++){
        if(itI!=Int.end()){
            intArr[j]=(itI->first);
        }
        ++itI;
    }
    ///////////////////////////////////////////////////
    if (Int.size() > 0) {
        int sizeIntArr=(sizeof(intArr)/sizeof(intArr[0]));
        obj.sort(intArr,sizeIntArr);
        cout << "\nList of integer values and their number of occurrences:" << endl;
        for (int i =0; i<(sizeof(intArr)/sizeof(intArr[0]));i++) {
            cout << intArr[i] << ": " << Int[intArr[i]] << endl;

        }

    }
//cout<<sizeof(realArr) <<endl;
    if (Real.size() > 0) {
        int sizeRealArr =(sizeof(realArr)/sizeof(realArr[0]));
       obj.sort(realArr,sizeRealArr);
        cout << "\nList of real values and their number of occurrences:" << endl;
        for(int i=0; i<(sizeof(realArr)/sizeof(realArr[0]));i++ ) {
            cout << realArr[i] << ": " << Real[realArr[i]] << endl;

        }
    }
    //////////////////////////////
    if (Sname.size() > 0) {
        cout << "\nList of special names and their number of occurrences:" << endl;
        while (itS != Sname.end()) {
            cout << itS->first << ": " << itS->second << endl;
            ++itS;
        }
    }


}