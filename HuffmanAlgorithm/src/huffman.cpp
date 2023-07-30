//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: MELİS KEŞEN
//---Student Number: 504211561
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>

#include "huffman.h"
#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-----------------------------------------------------//
//-----------Reads the key from text file--------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::readKey(const char *argv)
{
    ifstream readKeyFile;
    readKeyFile.open(argv);

    if (readKeyFile.is_open())
    {
        while (!readKeyFile.eof())
        {
            readKeyFile >> key;
        }
    }
    readKeyFile.close();
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------Sorts the key in an alpabetic order---------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::sortKey()
{
    sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------Finds the frequency of the characters---------//
//-----------------------------------------------------//
void Huffman::findFrequency()
{
    // DO NOT CHANGE THIS
    sortKey();
    // DO NOT CHANGE THIS
    unsigned int freq[256] = {0};
    for (unsigned int i = 0; sortedKey[i] != '\0'; i++)
    {
        freq[(unsigned char)sortedKey[i]]++;
    }
    /*Loop through all alpahbets as ascii code and returns the frequencies in sorted key. After queue one by one to the priorty queue*/
    for (unsigned int i = 0; i < 256; i++)
    {
        Node *d = new Node;
        if (freq[i] != 0)
        {
            // cout << "Frequency of alphabet " << (char)i << " in the string is " << freq[i] << endl;
            d->token.val = freq[i];
            d->token.symbol = (char)i;

            queue.enque(d);
        }
    };
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//----------------Creates Huffman Tree-----------------//
//-----------------------------------------------------//
void Huffman::createHuffmanTree()
{
    findFrequency();
    Node *min = new Node();
    Node *sec_min = new Node();
    /*After finding the frequencies as a value and symbol from priority queue, find minimum and second minimum values as a first and merge it*/
    min = queue.dequeue();
    sec_min = queue.dequeue();
    huffmanTree.root = huffmanTree.mergeNodes(min, sec_min);
    queue.enque(huffmanTree.root);
    /*After first merge, until head and head's next is null, merge all minimum and second minimums in priorty queue as a tree*/
    while (queue.head != NULL && queue.head->next != NULL)
    {
        Node *temp;
        min = queue.dequeue();
        sec_min = queue.dequeue();
        temp = huffmanTree.mergeNodes(min, sec_min);
        /*As merge one by one enqueu merged node to the priorty queue again*/
        queue.enque(temp);
    }
    /*Remove one last node from queue at last*/
    huffmanTree.root = queue.dequeue();
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Prints the Huffman Tree---------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printHuffmanTree()
{
    huffmanTree.printTree(huffmanTree.root, 0);
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Finds and returns the binary------------//
//----------------value to given character-------------//
//-----------------------------------------------------//
string Huffman::getTokenBinary(char tokenChar, Node *traverse, string tokenBinary)
{
    /*Given character traverse all three as a left or right and returns binary result of the character of the three*/
    if (traverse->right != NULL && traverse->right->token.symbol.find(tokenChar) != std::string::npos)
    {
        tokenBinary = "1";
        return tokenBinary + getTokenBinary(tokenChar, traverse->right, tokenBinary);
    }
    else if (traverse->left != NULL && traverse->left->token.symbol.find(tokenChar) != std::string::npos)
    {
        tokenBinary = "0";
        return tokenBinary + getTokenBinary(tokenChar, traverse->left, tokenBinary);
    }
    else
    {
        return "";
    }
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//--------------Encodes the given password-------------//
//-----------------------------------------------------//
void Huffman::encodePassword(string password)
{

    string encodedBinaryPasswordtemp = "";
    encodedBinaryPassword = "";
    encodedValPassword = "";
    string count = "";
    /*Find one by one characters from password and send to getTokenBinary function*/
    for (unsigned int i = 0; i < password.length(); i++)
    {

        encodedBinaryPasswordtemp += getTokenBinary(password[i], huffmanTree.root, "");
        encodedValPassword += to_string(encodedBinaryPasswordtemp.length());
        encodedBinaryPassword += encodedBinaryPasswordtemp;
        encodedBinaryPasswordtemp = "";
    }
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the encoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printEncodedPassword()
{
    cout << "Encoded Password Binary: " << encodedBinaryPassword << endl;
    cout << "Encoded Password Value: " << encodedValPassword << endl;
};

//-----------------------------------------------------//
//--------------Decodes the given password-------------//
//-----------------------------------------------------//
void Huffman::decodePassword(string encodedBinaryPassword, string encodedValPassword)
{

    int lastIdx = 0;
    string tempToken;
    /*Given depth and binary values loop through and send to decodeToken function to search the three*/
    for (unsigned int i = 0; i < encodedValPassword.length(); i++)
    {
        int len = (int)encodedValPassword[i] - '0';
        tempToken = encodedBinaryPassword.substr(lastIdx, len);
        decodeToken(tempToken);
        lastIdx += len;
    }
};

//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Decodes the given binary--------------//
//-----------------------------------------------------//
void Huffman::decodeToken(string encodedToken)
{
    string dec[256];
    string decodedPasswordtemp = "";
    /*For given encoded value search the tree if it is right is 1 or left is 0 */
    for (unsigned int i = 0; i < encodedToken.length(); i++)
    {

        if (encodedToken[i] == '1' && huffmanTree.root->right != NULL)
        {

            decodedPasswordtemp = huffmanTree.root->right->token.symbol[0];
            huffmanTree.root = huffmanTree.root->right;
        }
        else if (encodedToken[i] == '0' && huffmanTree.root->left != NULL)
        {

            decodedPasswordtemp = huffmanTree.root->left->token.symbol[0];
            huffmanTree.root = huffmanTree.root->left;
        }
        else
        {
            decodedPasswordtemp = "(.*)";
        }
    }
    decodedPassword += decodedPasswordtemp;
    /*To search through tree from begining*/
    createHuffmanTree();
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the decoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printDecodedPassword()
{
    cout << "Decoded Password: " << decodedPassword << endl;
};