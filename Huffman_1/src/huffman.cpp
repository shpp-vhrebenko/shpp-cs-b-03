#include <iostream>
#include "console.h"
#include <conio.h>
#include <map>
#include <fstream>
#include <list>
#include <string>
#include "bitstream.h"
#include "strlib.h"
#include "myvector.h"



using namespace std;

// Class of tree node Huffman
class Node
{
public:
    int count;// the number of occurrences of a character in the text.
    char value;// a character
    Node *left, *right;// the pointer left and right successor node

    // Designer tree node Huffman
    Node(){
        left = NULL;
        right = NULL;
    }

    // Designer tree node Huffman
    Node(Node *L,Node *R){
        count = L->count + R->count;
        left = L;
        right = R;
        value = NULL;
    }

    bool operator < (Node* R){
        return value < R->value;
    }

    // Destructor
    ~Node(){
        delete left;
        delete right;
    }

};

/*The structure of sorting a list of pointers to the nodes of the tree Huffman*/
struct MyCompare{
    bool operator()(Node *L,Node *R)const{
        return (L->count) < (R->count);
    }
};


/*************The encoding of the source file.***************/
void fileEncoding();

/*
 * It prompts the user to enter a filename and tries to open the file. If the attempt fails,
 * again prompts the user for a filename. If the file is opened returns the file name.
 */
string requestFileName(ifstream & readFile);

/*
 * Counts the number character's occurences in the text
 * @param map <char,int> - an array of associations symbol - the number of occurrences in the text.
 * @param unsigned int - stores the number of characters in the source file.
 * @param ifstream - takes reference to the stream of open file for reading *
 */
void countingNumberInputCharacters(map <char,int> & characterMap,unsigned int & numOfChars,ifstream & readFile);

/*
 * Builds a coding tree for characters of the text according to the Huffman's algoritm
 * @param - map<char,MyVector<bool> >, Table association with the code symbol.
 * @return Node* pointer to the root of the coding tree
 */
Node* buildTree(map <char,int> characterMap);

/*Filling a table of association symbol - code
 *@param - a pointer to the root node
 *@param - MyVector<bool>, character code.
 *@param - map<char,MyVector<bool> >, Table association with the code symbol.
 *@param - int  number of coded symbols.
 */
void BuildTable(Node *root,MyVector<bool> &code,map<char,MyVector<bool> > &table,int &numOfCodes);

/* Write to source file character code table associations. To be able to decrypt the file.
 * @param ofstream -  stream for recording information in the file.
 * @param map<char,MyVector<bool> > - Table association with the code symbol.
 * @param int - number of characters .
 * @param int - the number of character codes.
 */
void writeTable(ofstream &writeFile, map<char,MyVector<bool> >& codeTable,unsigned int numOfChars, int numOfCodes);

/*The encoding of the text input file.
 * @param ifstream - stream for reading the information from the source file.
 * @param map<char,MyVector<bool> > - Table association with the code symbol.
 * @param ofbitstream - stream for recording information in the file.
 */

/*
 * Writes code of character as set of bytes where each bit represens a bool value
 * @param ofstream takes a reference to the stream of open file record as binary
 * @param MyVector<bool> takes a code of the character
 */
void writeCode(ofstream & writeFile,MyVector<bool> code );

/*
 * Encodes the text and writes it to the text file
 * @param string takes a name of the file that will be archived
 * @param map<char,MyVector<bool> > - Table association with the code symbol.
 * @param ofstream takes a reference to the stream of open file to record as binary
 */
void codingText(string filename, map<char,MyVector<bool> >& codeTable, ofstream & writeFile);

/*
 * Writes code of character to the output file by bytes.
 * @param ofstream takes a reference to the stream of open file record as binary
 * @param MyVector<bool> takes a code of the character
 * @param char & takes a reference to the character which represents encoded byte.
 * @param int & takes a reference to the possition of a current bit of encoded byte.
 */
void codingChar(ofstream & writeFile,MyVector<bool> code,char & byte,int & countPosition);

/*
 * Appends the required number of bits for a byte to write.
 * @param ofstream takes a reference to the stream of open file record as binary
 * @param char takes a character which represents encoded byte.
 * @param int takes a possition of a current bit of encoded byte.
 */
void additionToByte(ofstream & writeFile,char byte,int countPossition);




/*****************The decoding of the source file**********************/
void unzipTheFile();

/*
 * It prompts the user to enter a filename and tries to open the file. If the attempt fails,
 * Again prompts the user for a filename. If the file is opened returns the file name.
 * @param ifstream - Byte stream read from the file.
 */
string requestFileNameArh(ifstream & readFile);


/*
 *Reading from a file encoded text.
 *@param ifstream - It takes a reference to an open file stream to read the bitmap
 *@param map<char,MyVector<bool> > - Table association with the code symbol.
 *@return unsigned int -  number of symbols in the source file.
 */
unsigned int readTable(ifstream & readHafArch,map<char,MyVector<bool> > &table);


/*
 * Restores tree coding with which the encoding was done plaintext
 * @param map<char,MyVector<bool> > - Table association with the code symbol.
 * @return a pointer to the node - the tree root.
 */
Node* buildTree(map<char,MyVector<bool> > &table);

/*
 * Return true, if the current node is a leaf,
 * which means that it has an actual value of the symbol.
 * @param - Node* a pointer to the node.
 */
bool isLeaf(Node * n);

/*
 *The decoding of the source text and write the result to a text file.
 *@param int numOfChars - It takes the number of characters in the source text.
 *@param ofstream -  takes a reference to the stream for writing the file.
 *@param ifstream -  takes a reference to an open file stream to read.
 *@param  Node* -  takes a pointer to the root of the tree coding.
 */
void decodingText(unsigned int numOfChars, ofstream & writeFile, ifstream & readHafArch, Node* root);

/*Reading character code byte. Each bit of the byte is part of the value code.
 *@param ifstream takes a reference to an open file stream to read.
 *@param int takes the number of code symbols.
 */
MyVector <bool> readCode(ifstream & readHafArch, int codeSize);



int main() {
    cout<<"\t***************Master Coding***************"<<endl;
    cout<<"Menu: "<<endl;
    cout<<"-------------------------------------------------------------"<<endl;
    cout<<"1.File Archiving (test1.txt, test2.txt, test3.txt, test4.txt)"<<endl;
    cout<<"-------------------------------------------------------------"<<endl;
    cout<<"2.Unzip the file"<<endl;
    cout<<"-------------------------------------------------------------"<<endl;
    int punkt = 0;
    while(true){
        cout<<"Enter the desired menu item: ";
        cin>>punkt;

        switch (punkt) {
        case 1:
            fileEncoding();//text Encoding
            break;
        case 2:
            unzipTheFile();//text Decoding
            break;
        default:
            cout<<"You have entered a non-existent item!!!"<<endl;
            cout<<"Press Enter!!!"<<endl;
            cin.clear();
            cin.ignore( cin.rdbuf()->in_avail());
            break;
        }
    }

    system("pause");

    return 0;
}

/*-----------------------------------------------------------------------------------------------------------*/

/*----------------------------------------text Encoding------------------------------------------------------*/

void fileEncoding(){

    ifstream readFile; // creating a class object flow to open the file.

    string fileName = requestFileName(readFile); // Request filename user.

    // An associative array of characters, the number of occurrences in the text.
    map <char,int> characterMap;

    // the number of characters in the text.
    unsigned int numOfChars = 0;

    /* The cycle of filling character Map associative array values
   (the number of occurrences of a character in the text).*/
    countingNumberInputCharacters(characterMap,numOfChars,readFile);

    MyVector<bool> code;// character code.

    map<char,MyVector<bool> > table;//Table association with the code symbol.

    int numOfCodes = 0;//The number of coded symbols.

    /* Huffman tree construction, and return a pointer to the root of the tree.*/
    Node* root = buildTree(characterMap);

    /* Building a table of associations: the symbol - the situation in the Huffman tree.*/
    BuildTable(root,code,table,numOfCodes);

    //Getting the file name where the results will be recorded decoding.
    string resultFile = fileName.substr(0, fileName.length() - 4) + "_HAF.txt";

    //creating a thread for writing to a file resultFile.
    ofstream writeFile(resultFile.c_str(),ios::binary);

    /*Write to the file table for decoding.*/
    writeTable(writeFile,table, numOfChars, numOfCodes);

    /*Write to file encoded text*/
    codingText(fileName, table, writeFile);

    cout<<"The file has been archived, and be in the main catalog.Name archive file - "<<resultFile<<endl;
}



string requestFileName(ifstream & readFile){
    while (true){
        string fileName = "";

        cout << "Please, enter file name(test1.txt, test2.txt, test3.txt, test4.txt): " << endl;

        cin >> fileName;

        readFile.open(fileName.c_str(),ios::binary); //C ++ converts the string to a string C.

        if(readFile){
            return fileName;
        }

        readFile.clear(); // resets the state indicator in the stream for reuse of this stream.
        cout << "The file can not be found. Check the correctness of the file name." << endl;
    }
}



void countingNumberInputCharacters(map <char,int> & characterMap,unsigned int & numOfChars,ifstream & readFile){
    char ch;
    while(readFile.get(ch) ){
        characterMap[ch]++;
        numOfChars++;
    }
    readFile.close();
}



Node* buildTree(map <char,int> characterMap){

    Node *result;
    // The list of pointers to the nodes of the tree Huffman.
    list<Node*> listNodes;

    // An iterator to iterate over the array elements characterMap.
    map<char,int>::iterator ii;

    // The cycle of filling list Nodes list of pointers to the nodes of the tree Huffman
    for(ii = characterMap.begin();ii != characterMap.end(); ++ii){
        Node *p = new Node;
        p->value = ii->first;
        p->count = ii->second;
        listNodes.push_back(p);
    }

    //While the list does not remain a single item. Which will be the root.
    while(listNodes.size() != 1)
    {
        listNodes.sort(MyCompare());// sort the list
        //Take the first two elements of the list.
        Node *SonL = listNodes.front();
        listNodes.pop_front();
        Node *SonR = listNodes.front();
        listNodes.pop_front();


        //Create a pointer to the parent node.
        //We put it on the list.
        Node *parent = new Node (SonL,SonR);
        listNodes.push_back(parent);
    }

    // The node that was and is the root of the tree.
    return result = listNodes.front();
}



void BuildTable(Node *root,MyVector<bool> &code,map<char,MyVector<bool> > &table,int &numOfCodes){

    if(root->left != NULL){
        code.push_back(0);
        BuildTable(root->left,code,table,numOfCodes);
    }
    if(root->right != NULL){
        code.push_back(1);
        BuildTable(root->right,code,table,numOfCodes);
    }
    if(isLeaf(root)){
        table[root->value] = code;
        numOfCodes++;
    }
    if(code.size() > 0){
        code.pop_back();
    }
}



void writeTable(ofstream &writeFile, map<char,MyVector<bool> >& codeTable,unsigned int numOfChars, int numOfCodes){
    map<char,MyVector<bool>>::iterator ii;
    writeFile.write((char*)&numOfChars,sizeof numOfChars);
    writeFile.put(numOfCodes);
    char ch;
    MyVector<bool> code;
    for(ii = codeTable.begin();ii != codeTable.end(); ++ii){
        ch = ii->first;
        writeFile.put(ch);
        code = ii->second;
        writeFile.put(code.size());
        writeCode(writeFile,code);
    }
}


void writeCode(ofstream & writeFile , MyVector<bool>  code ){
    while(code.size()%8){
        code.add(0);
    }
    int size = (code.size()/8);
    char buff[size];
    char byte = 0;

    for(int i = 0;i<code.size();++i){
        byte = (byte<<1)|code[i];
        if((i+1)%8==0){
            buff[i/8] = byte;
            byte = 0;
        }
    }
    writeFile.write(buff,size);
}



void codingText(string filename, map<char,MyVector<bool> >& codeTable, ofstream & writeFile){
    ifstream readFile;
    readFile.open(filename.c_str(), ios::binary); // open sourse file as binary
    char ch; // to declare a variable to read a file one character.
    // reads the file until it has the following symbol.
    char byte = 0;
    int position = 0;
    while (readFile.get(ch)){
        codingChar(writeFile,codeTable[ch],byte,position);
    }
    if(position > 0){
        additionToByte(writeFile,byte,position);
    }

    writeFile.close();
    readFile.close();// closing the source file
}



void codingChar(ofstream & writeFile,MyVector<bool> code,char & buff,int & countPosition){

    for(int i= 0;i<code.size();++i){
        buff = buff|(code[i] << (7 - countPosition));
        ++countPosition;
        if(countPosition == 8){
            writeFile << buff;
            buff = 0;
            countPosition = 0;
        }
    }
}



void additionToByte(ofstream & writeFile,char byte,int countPosition){
    while(countPosition < 8){
        byte = byte | 0 << (7 - countPosition);
        ++countPosition;
    }
    writeFile << byte;

}

/*-----------------------------------------------------------------------------------------------------------*/

/*------------------------------------------------decoding text----------------------------------------------*/

void unzipTheFile(){
    //ifbitstream readHafArch; //create a class object flow to open the file
    ifstream readHafArch; //create a class object flow to open the file
    string archFilename = requestFileName(readHafArch);

    // Table association with the code symbol.
    map<char,MyVector<bool> > table;

    // generates text file name by removing "_HAF" from the end of the file and adding "_decoded".
    string filename = archFilename.substr(0, archFilename.length() - 8) + "_decoded" + archFilename.substr(archFilename.length() - 4);

    /*Creating a stream for writing the result of decoding the file.*/
    ofstream writeFile(filename);

    /*Reading the table of character codes and obtaining the number of characters of the source file.*/
    unsigned int numOfChars = readTable(readHafArch,table);

    //close a file and complete the program if source file was empty.
    if(numOfChars == 0){
        cerr<<"Error decryption.There are no relevant data.[unzipTheFile]!!!";
        exit(EXIT_FAILURE);
    }

    /*Huffman tree construction, and return a pointer to the root of the tree.*/
    Node* root = buildTree(table);

    /*Decoding file using Huffman tree*/
    decodingText(numOfChars, writeFile, readHafArch, root);

    cout<<"The file has been archived, and be in the main catalog. The file is saved under the name - "<<filename<<endl;
}



string requestFileNameArh(ifstream & readFile){
    while (true){
        string fileName = "";
        cout << "Please, enter file name: ";
        cin >> fileName;
        readFile.open(fileName,ios::binary);
        if(!readFile.fail()){
            return fileName;
        }
        readFile.clear(); // resets the status indicator in the stream to re-use it.
        cout << "The file can not be found. Check the correctness of the file name." << endl;
    }
}

unsigned int readTable(ifstream & readHafArch,map<char,MyVector<bool> > &table){
    unsigned int numChars;
      readHafArch.read((char *)&numChars, sizeof(numChars));
      if (numChars == 0){
          return numChars;
      }
      char ch = 0;
      char vh = 0;
      readHafArch.get(ch); // read a number of coded symbols of the sourse file
      int numCodes = ch;      
      for(int i = 0; i < numCodes; ++i){ // read a code table
           readHafArch.get(vh);         
           readHafArch.get(ch);
           int codeSize = ch;           
           table[vh] = readCode(readHafArch, codeSize);
           vh = 0;
       }
       return numChars;




}

MyVector <bool> readCode(ifstream & readHafArh, int codeSize){
    MyVector<bool> code;
    int size = (codeSize / 8 ) + ((codeSize % 8) ? 1 : 0); // size of buffer for reading bytes
    char buff [size];   
    readHafArh.read(buff,size);
    for (int i = 0; i < codeSize; ++i){
        code.add(buff[i/8] < 0); // check most significant bit that is responsible for the sign of char
        buff[i/8] = buff[i/8] << 1;

    }     
    return code;
}


Node* buildTree(map<char,MyVector<bool> > &table){
    Node * root = new Node();
    Node * current = root;
    map<char,MyVector<bool>>::iterator v;
    for(v = table.begin();v != table.end(); ++v){
        for(int i = 0; i < v->second.size();++i){
            if(v->second[i]){
                if(current->right == NULL){       // If the node does not have a successor who is on the right
                    Node *n = new Node();        // to сreate a new node.
                    current->right = n;
                }
                current = current->right;
            }
            else{
                if(current->left == NULL){        // If the node does not have a successor who is on the left
                    Node *n = new Node();        // to create a new node.
                    current->left = n;
                }
                current = current->left;
            }

        }
        current->value = v->first;             // for the last node writes the value of a symbol
        current = root;

    }

    return root;
}



bool isLeaf(Node * n){
    return ((n->left == NULL) && (n->right == NULL));
}



void decodingText(unsigned int numOfChars, ofstream & writeFile, ifstream & readHafArch, Node* root){    
    Node * current = root;
    char ch;   
    while (readHafArch.get(ch)){
        for (int i = 7; i >= 0; --i){
            if(ch & (1 << i))
                current = current->right;
            else
                current = current->left;
            if(isLeaf(current)){
                writeFile.put(current->value);              
                current = root;
                --numOfChars;
            }
            if (numOfChars == 0){
                break;
            }
        }
    }


    readHafArch.close();
    writeFile.close();
}

/*-----------------------------------------------------------------------------------------------------------*/
