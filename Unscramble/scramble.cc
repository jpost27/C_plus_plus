#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<vector>
#include<sstream>

using namespace std;

vector<string>wordlist;
vector<string>words;
vector<int>final;


int main ()
{	
	int x=0;
	string word;
	ifstream listin;
	listin.open("wordlist.txt",ios::in);
	while(getline(listin, word))
	{	
		wordlist.push_back (word);
	}
	listin.close();
	ifstream wordsin;
        wordsin.open("words.txt",ios::in);
        while(getline(wordsin, word))
        {
                words.push_back (word);
        }
        wordsin.close();
	cout<<words[0]<<words[1]<<words[2]<<endl;
	string w;
	for(int n=0;n<words.size();n++) //GO THROUGH WORDS LIST
	{
		vector<int>nums;
		vector<string>length;
		int num=0;
		for(int m=0;m<wordlist.size();m++) //GO THROUGH WORDLIST LIST
		{
			if (words[n].length()==(wordlist[m].length()-1)) //CREATE LENGTH LIST NARROWED FROM WORDLIST LIST
			{
				length.push_back(wordlist[m]);
				nums.push_back(m);
			}
		}
		for(int p=0;p<length.size();p++) //GO THROUGH LENGTH LIST
                {	
			int flag=0;
			for (int r=0;r<words[n].length();r++) //GO THROUGH EACH LETTER IN WORD FROM WORDS LIST******
			{
				if(length[p].find(words[n].at(r)) != string::npos)
					flag++;
				
			}
			if (flag>=words[n].length())
			{
	                        int f=0;
        	                for (int r=0;r<length[p].length();r++) //GO THROUGH EACH LETTER IN WORD IN LETTERS LIST
                	        {
                	                if(words[n].find(length[p].at(r)) != string::npos) 
                	                        f++;
	
	                        }
	                        if (f==flag)
	                        {
	                                final.push_back(nums[p]); //CREATE FINAL LIST OF WORDS CONTAINING UNSCRAMBLED WORDS
	                        }
			}
                }

	}
	int wid=0;
	for(int b=0;b<final.size();b++)
		wid=wid+wordlist[final[b]].length();

	for(int a=final.size()-1;a>=0;a--)
	{
		cout<<setw(wid)<<right<<","<<wordlist[final[a]];
		wid=wid-wordlist[final[a-1]].length();
	}
	cout<<endl;
	return 0;
}
