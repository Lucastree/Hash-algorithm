#include<iostream>
#include<string>
#include <stdlib.h> 
using namespace std;
class HashTable
{
    private:
    int size;
    string* elem;
    public:
    HashTable()
    {
        size=200000;
        elem=new string[size];
        for(int i=0;i<size;i++)
        {
            elem[i]="#";
        }
    }
    ~HashTable()
    {
        delete[] elem;
    }
    int hash(string& index)
    {
        int code=0;
        for(size_t i=0;i<index.length();i++)
        {
            if(isupper(index[i]))  
            index[i]=index[i] - 'A' + 'a';  
        }
        for(size_t i=0;i<index.length();i++)
        {
            code=(code*256+index[i]+128)%size;
        }
        return code;
    }
    bool search(string& index, int& pos, int& times)
    {
        pos=hash(index);
        times=0;
        while(elem[pos]!="#" && elem[pos]!=index)
        {
            times++;
            if(times<size)
            {
                pos=(pos+1)%size;
            }
            else
            {
                return false;
            }
        }
        if(elem[pos]==index)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    int insert(string& index)
    {
        int pos,times;
        if(search(index,pos,times))
        {
            return 2;
        }
        else if(times<size/2)
        {
            elem[pos]=index;
            return 1;
        }
        else
        {
            recreate();
            return 0;
        }
    }
    void recreate()
    {
        string* temp_elem;
        temp_elem=new string[size];
        int copy_size=size;
        for(int i=0;i<size;i++)
        {
            temp_elem[i]=elem[i];
        }
        delete[] elem;
        size=size*2;
        elem=new string[size];
        for(int i=0;i<size;i++)
        {
            elem[i]="#";
        }
        for(int i=0;i<copy_size;i++)
        {
            if(temp_elem[i]!="#")
            {
               insert(temp_elem[i]);
            }
        }
        delete[] temp_elem;
    }
};
int main()
{
    HashTable hashtable;
    int n, temp_pos, temp_times;
    cin>>n;
    string buffer;
    cin>>buffer;
    hashtable.insert(buffer);
    cout<<"No"<<endl;
    for(int i=0;i<n-1;i++)
    {
        cin>>buffer;
        if(hashtable.search(buffer,temp_pos,temp_times))
        {
            cout<<"Yes"<<endl;
        }
        else
        {
            cout<<"No"<<endl;
        }
        hashtable.insert(buffer);
    }
    return 0;
}
