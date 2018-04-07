#include <iostream>
#include <fstream>
#include <cstring>


using namespace std;

class hash
{
private:
    static const int tableSize = 30;

    struct item
       {
           string word;
           item * next;
       };

       item* HashTable[tableSize];

   public:
       hash();
       int Hash( string key);
       void AddItem( string word);
       int NumberOfItemsInIndex( int index );
       void PrintTable();
       void PrintItemsInIndex( int index);
};

void hash::PrintItemsInIndex(int index)
{
    item* Ptr = HashTable[index];
    if( Ptr->word == "empty" )
    {
        cout<<" index = "<<index<<" is empty"<<endl;
    }
    else
    {
        cout<<" index "<<index<<" contains the following items"<<endl;
        while( Ptr != NULL )
        {
            cout<<"______________________________"<<endl;
            cout<<Ptr->word<<endl;
            Ptr= Ptr->next;
        }
    }
}

void hash::PrintTable()
{
    int number;
    int count0fDistinctWords = 0;

    for( unsigned int i = 0; i < tableSize; i++ )
    {
        if( (HashTable[i]->word != HashTable[i+1]->word ) && (HashTable[i]->word != "empty") )
            count0fDistinctWords++;

        number = NumberOfItemsInIndex(i);
        cout<<"index = "<<i<<endl;
        cout<<HashTable[i]->word<<endl;
        cout<<"# of items in this bucket = "<<number<<endl;
        cout<<"____________________________"<<endl;
        cout<<"                             "<<endl;

    }


    cout<<"There are "<<count0fDistinctWords<<" different words in the text."<<endl;
    cout<<"                                                   "<<endl;

}

int hash::NumberOfItemsInIndex( int index )
{
    int count = 0 ;

    if( HashTable[index]->word == "empty" )
    {
        return count;
    }

    else
    {
        count++;

        item* Ptr = HashTable[index];

        while(Ptr->next != NULL )
        {
            count++;
            Ptr = Ptr->next;
        }
    }

    return count;
}


void hash::AddItem( string word)
{
    int index =Hash(word);

    if( HashTable[index]->word == "empty")
    {
        HashTable[index]->word = word;
    }

    else
    {
       item *Ptr = HashTable[index];
       item *n = new item;
       n->word = word;
       n->next = NULL;

       while(Ptr->next != NULL)
       {
           Ptr = Ptr->next;
       }
       Ptr->next = n;
    }
}

hash::hash()
{
    for( int i = 0; i<tableSize; i++)
    {
        HashTable[i] = new item;
        HashTable[i]->word = "empty";
        HashTable[i]->next = NULL;
    }
}

int hash::Hash(string key)
{
    int index;
    int number = 0;

    index = key.length();

    for( unsigned int i = 0; i<key.length(); i++ )
    {
        number = number + (int)key[i];
    }

    index = number % tableSize;

    return index;
}


string convert( string s)
{
   for( unsigned int i = 0; i<s.length(); i++ )
   {
       s[i] = tolower(s[i]);
   }
   return s;
}

int main()
{
    hash Hashy;
    int count = 0;
    string rawWord, case_Corrected_Word;

    ifstream myFile;
    myFile.open("zvenharo.txt");

    if( myFile.fail())
        cout<<"Error in opening file"<<endl;

    else
    {
        cout<<"File opened successfully!"<<endl;
        cout<<"                           "<<endl;

        while( myFile >> rawWord)
        {
            case_Corrected_Word = convert(rawWord);

            Hashy.AddItem(case_Corrected_Word);
            count++;
        }
    }

    Hashy.PrintTable();

    //Hashy.PrintItemsInIndex(0);

    cout<<"                       "<<endl;
    cout<<count<<" words have been input."<<endl;

    return 0;
}
