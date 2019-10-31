#include<bits/stdc++.h>

using namespace std;

int degree,c;

struct Node{
	bool leaf;
	Node *parent;
	string *engWord,*bangWord;
	Node **child;
	int numberOfData;

} *root=NULL, *tempNode=NULL;


Node* initialize()
{
	Node *temp = new Node;
	temp->leaf=true;
	temp->parent=NULL;
	temp->engWord = new string[degree];
	temp->bangWord = new string[degree];
	temp->child = new Node *[degree+1];
	temp->numberOfData=0;

	for(int i=0;i<degree;i++)
	{
		temp->engWord[i]="\0";
		temp->bangWord[i]="\0";
		temp->child[i]=NULL;
	}

	return temp;
}


void sort(Node *temp)
{
	string eng,bang;
	for(int i=0;i<temp->numberOfData;i++)
	{
		for(int j=i+1;j<temp->numberOfData;j++)
		{
			if(temp->engWord[i]>temp->engWord[j])
			{
				eng=temp->engWord[i];
				bang=temp->bangWord[i];
				temp->engWord[i]=temp->engWord[j];;
				temp->engWord[j]=eng;
				temp->bangWord[i]=temp->bangWord[j];;
				temp->bangWord[j]=bang;
			}
		}
	}
	
}

void searchWord(string eng)
{
    tempNode = root;

    while(tempNode->leaf==false)
    {
        int i;
        for(i=0;i<tempNode->numberOfData;i++)
        {
            if(eng < tempNode->engWord[i]) break;
        }

        tempNode=tempNode->child[i];
        c++;
    }

    for(int i=0;i<tempNode->numberOfData;i++)
    {
        if(eng == tempNode->engWord[i])
        {
            cout << tempNode->bangWord[i] << endl;
            return;
        }
    }

    cout << "not found in dictionary!!" << endl;

}

void traverse(Node *temp)
{
	cout<<endl;
	int i;
	for(i=0;i<temp->numberOfData;i++)
	{
		if(temp->leaf==false)
		{
			traverse(temp->child[i]);
		}
		if(temp->leaf==false) cout << " IN: " << temp->engWord[i] << " " 
		<< temp->bangWord[i];
		
		else cout << " LN: " << temp->engWord[i] << " " << temp->bangWord[i];

	}

	if(temp->leaf==false)
	{
	    traverse(temp->child[i]);
	}

	cout << endl;

}

void leafTraverse(Node *temp)
{
    if(temp->leaf==true)
    {
        while(temp!=NULL)
        {
            for(int i=0;i<temp->numberOfData;i++) cout << " " << temp->engWord[i] << " "
             << temp->bangWord[i] << endl;
            temp=temp->child[degree-1];
            if(temp==NULL) return;
        }

    }

    else
    {
        leafTraverse(temp->child[0]);
    }

}

void splitInternalNode(Node *leftNode)
{
    Node *rightNode=NULL,*parentNode=NULL;
    rightNode = initialize();
    rightNode->leaf=false;

    int j;
    for(j=((degree/2)+1);j<degree;j++)
    {
        rightNode->child[j-((degree/2)+1)]=leftNode->child[j];

        rightNode->engWord[j-((degree/2)+1)]=leftNode->engWord[j];
        rightNode->bangWord[j-((degree/2)+1)]=leftNode->bangWord[j];
        leftNode->engWord[j]="\0";
        leftNode->bangWord[j]="\0";
        leftNode->numberOfData--;
        rightNode->numberOfData++;

        leftNode->child[j]->parent = rightNode;
        leftNode->child[j]=NULL;

    }

    rightNode->child[j-((degree/2)+1)]=leftNode->child[j];
    leftNode->child[j]->parent = rightNode;
    leftNode->child[j]=NULL;

    if(leftNode->parent==NULL)
    {
        parentNode = initialize();
        parentNode->leaf=false;

        parentNode->engWord[parentNode->numberOfData]=leftNode->engWord[degree/2];
        parentNode->bangWord[parentNode->numberOfData]=leftNode->bangWord[degree/2];
        leftNode->numberOfData--;

        parentNode->child[parentNode->numberOfData]=leftNode;
        parentNode->numberOfData++;
        parentNode->child[parentNode->numberOfData]=rightNode;

        leftNode->parent=parentNode;
        rightNode->parent=parentNode;
        root=parentNode;
    }

    else
    {
        int i=0;
        parentNode = leftNode->parent;

        for(i=0;i<parentNode->numberOfData;i++) if(rightNode->engWord[0] < 
        parentNode-> engWord[i]) break;

        for(int j=parentNode->numberOfData;j>i;j--)
        {
           parentNode->child[j+1] = parentNode->child[j];
           parentNode->engWord[j] = parentNode->engWord[j-1];
           parentNode->bangWord[j] = parentNode->bangWord[j-1];
        }

        parentNode->engWord[i]=leftNode->engWord[degree/2];
        parentNode->bangWord[i]=leftNode->bangWord[degree/2];
        leftNode->engWord[degree/2]="\0";
        leftNode->bangWord[degree/2]="\0";
		parentNode->numberOfData++;
		leftNode->numberOfData--;

		parentNode->child[i+1]=rightNode;
		rightNode->parent = parentNode;

        if(parentNode->numberOfData==degree)
        {
            splitInternalNode(parentNode);
        }
    }

}


void splitLeaf(Node *leftChild)
{
    Node *rightChild=NULL,*Parent=NULL;
    rightChild = initialize();

    for(int i=degree/2;i<degree;i++)
	{
		rightChild->engWord[i-degree/2]=leftChild->engWord[i];
		rightChild->bangWord[i-degree/2]=leftChild->bangWord[i];
		leftChild->engWord[i]="\0";
		leftChild->bangWord[i]="\0";
		rightChild->numberOfData++;
		leftChild->numberOfData--;
	}
	rightChild->child[degree] = leftChild->child[degree];
	leftChild->child[degree] = rightChild;

	if(leftChild->parent==NULL)
	{
		Parent= initialize();
        Parent->leaf=false;

		Parent->engWord[Parent->numberOfData]=rightChild->engWord[0];
		Parent->bangWord[Parent->numberOfData]=rightChild->bangWord[0];
		Parent->child[Parent->numberOfData]=leftChild;
		Parent->numberOfData++;
		Parent->child[Parent->numberOfData]=rightChild;
		leftChild->parent = Parent;
		rightChild->parent = Parent;

		root=Parent;

	}

	else
    {
        int i=0;
        Parent = leftChild->parent;

        for(i=0;i<Parent->numberOfData;i++) if(rightChild->engWord[0] < 
        Parent->engWord[i]) break;

        for(int j=Parent->numberOfData;j>i;j--)
        {
           Parent->child[j+1] = Parent->child[j];
           Parent->engWord[j] = Parent->engWord[j-1];
           Parent->bangWord[j] = Parent->bangWord[j-1];
        }

        Parent->engWord[i]=rightChild->engWord[0];
        Parent->bangWord[i]=rightChild->bangWord[0];
		Parent->numberOfData++;
		Parent->child[i+1]=rightChild;
		rightChild->parent = Parent;

		if(Parent->numberOfData==degree)
        {
            splitInternalNode(Parent);
        }
    }


}


void insert(string eng, string bang)
{

	tempNode=root;

	if(tempNode==NULL)
	{
		root=initialize();
		tempNode=root;
	}


    while(tempNode->leaf!=true)
    {
        for(int i=0;i<tempNode->numberOfData;i++)
        {
            if(eng < tempNode->engWord[i])
            {
                tempNode=tempNode->child[i];
                break;
            }

            else if(i==tempNode->numberOfData-1)
            {
                tempNode=tempNode->child[i+1];
                break;
            }

        }

    }

    tempNode->engWord[tempNode->numberOfData]=eng;
    tempNode->bangWord[tempNode->numberOfData]=bang;
	tempNode->numberOfData++;
	sort(tempNode);

    if(tempNode->numberOfData==degree)
    {
        splitLeaf(tempNode);
    }

}


int main (void)
{
    cout << "Enter the degree of b+ tree : ";
	cin >> degree;

    ifstream inputFile;
    string engWord,bangWord;
    inputFile.open("words.txt");


    while(inputFile >> engWord)
    {
        getline(inputFile,bangWord);
        insert(engWord,bangWord);
    }
    inputFile.close();

    while(true)
	{
		int choice;
		cout << "1.search\n2.traverse\n3.leaf Traverse\n4.exit" << endl;
		cin >> choice;

		if(choice==1)
		{
            string eng;
            cout << "Enter English word: ";
            cin >> eng;
            cout << "Meaning :";
            c=0;
            searchWord(eng);
            cout << "depth " << c+1 << endl;
		}

		else if(choice==2) traverse(root);
		else if(choice==3) leafTraverse(root);

		else break;
	}

	return 0;
}



