#include <stdio.h>
#include <stdlib.h>
#define MAX_TREE_HT 100
#include "fileRead.c"
// The node of the Huffman Tree which stores the character , its frequency and the pointers to the left and right variables
struct treeNode
{
  int freq;
  char alpha;
  struct treeNode *left,*right;
};

// Minimum Heap of all the Huffman Tree Nodes
struct heapNode
{
  int size; //current size
  int cap; //overall capacity
  struct treeNode **array;
};

//Standard Heapify function

void heapify(struct heapNode* heap, int x)
{
  // Starting from the bottom node.
  // Finding the smallest of the two nodes( left and right)
  // If smallest < root -> switch them

  int small=x;
  int i1=2*x +1;
  int i2=2*x+2;


  // Checking if left node exists and comparing their frequency values
  if(i1<heap->size && heap->array[i1]->freq< heap->array[small]->freq )
  {
    small=i1;
  }
  if(i2<heap->size && heap->array[i2]->freq<heap->array[small]->freq)
  {
    small=i2;
  }

  //  One of the sub nodes has a lower freq
  // So we have to switch them
  if(small!=x)
  {
    struct treeNode *temp=heap->array[small];
    heap->array[small]=heap->array[x];
    heap->array[x]=temp;

    // Continue this wit the next set of nodes
      heapify(heap,small);

  }
}


//Building the minimum heap from the array
void buildMinimunHeap( struct heapNode * heap)
{
  int count=(heap->size)-1;

  for(int i=(count-1)/2;i>=0;--i)
  {
    heapify(heap,i);
  }
}

// Program to create the Heap Initially

struct heapNode* createHeap(char alpha[], int freq[], int size)
{

  // Creating the heap to store the character and frequencies values
  // the freq and character values are stores as the values of a node in a node array
  struct heapNode *heap;
  heap=(struct heapNode*)malloc(sizeof(struct heapNode));
  heap->size=0;
  heap->cap=size;
  // Array to store the nodes
  heap->array=(struct treeNode**)malloc(sizeof(struct treeNode*)*heap->cap);

  //Storing Values into the array of the heapNode

  int i;

  for(i=0;i<size;i++)
  {
    heap->array[i]=(struct treeNode * )malloc(sizeof(struct treeNode));
    heap->array[i]->left=heap->array[i]->right=NULL;
    heap->array[i]->alpha=alpha[i];
    heap->array[i]->freq=freq[i];
  }

  heap->size=size;

  // Now building a minimun heap out of this array.

  buildMinimunHeap(heap);

  return heap;

}
// Adding an element into the min heap and making it min again

void insertIntoHeap(struct heapNode *heap, struct treeNode* top)
{
  heap->size+=1;

  int i = heap->size - 1;
	while (i && top->freq < heap->array[(i - 1)/2]->freq)
	{
		heap->array[i] = heap->array[(i - 1)/2];
		i = (i - 1)/2;
	}
	heap->array[i] = top;
}


//Returning the minimun node
struct treeNode* minNode(struct heapNode *heap)
{
  struct treeNode* temp = heap->array[0];
	heap->array[0] = heap->array[heap->size - 1];
	--(heap->size);
	heapify(heap, 0);
	return temp;
}
// the main treeCreation function

struct treeNode* createTree(char alpha[], int freq[], int size)
{
  struct treeNode *left, *right, *top;

  // Creating the minimum heap
  struct heapNode* n=createHeap(alpha,freq,size);

  // Iterate to merge two nodes each of lowest two freq
  // Delete the two and replace by their root
  // Do this till only one root node is left

  while(n->size!=1)
  {
    // Extract the least two elements

    left=minNode(n);
    right=minNode(n);

    // Create their root node
    // root's freq is equal to sum of the child node's freq
    //Store some special character as the alpha of the root

    top=(struct treeNode*)malloc(sizeof(struct treeNode));
    top->alpha='#';
    top->freq=left->freq + right->freq;
    top->left=left;
    top->right=right;

    // Insert this node into the minimun heap
    insertIntoHeap(n,top);
  }

  // Now there is only one main element left
  //This is the root node

  return minNode(n);



}

void inorder( struct treeNode *heap)
{
  if(heap!=NULL)
  {
    printf("%c",heap->alpha);
    printf("<->%d \n",heap->freq);
    inorder(heap->left);
    inorder(heap->right);
  }
}
int q=0;
char array[150];
int bitLength[150];
// A utility function to print an array of size n
void printArr(int arr[], int n,char ch)
{
    int i;
    int count=0;
    for (i = 0; i < n; i++)
    {   count++;
        printf("%d", arr[i]);
    }
    printf("\n");
    printf("Actual Bit Size: 8\n");
    printf("Reduced Bit Size: %d\n",count);
    printf("\n");
    array[q]=ch;
    bitLength[q]=count;
    q++;

}

void printCodes(struct treeNode* temp, int arr[], int top)
{
    // Assign 0 to left edge and recur
    if (temp->left)
    {
        arr[top] = 0;
        printCodes(temp->left, arr, top + 1);
    }

    // Assign 1 to right edge and recur
    if (temp->right)
    {
        arr[top] = 1;
        printCodes(temp->right, arr, top + 1);
    }

    // If this is a leaf node, then it contains one of the input
    // characters, print the character and its code from arr[]
    if (temp->right==NULL && temp->left==NULL)
    {
        printf("%c: ", temp->alpha);
        printArr(arr, top,temp->alpha);
        top=0;
    }
}
int returnTotalSpace(char alphaInitial[],char alphaFinal[],int freq[], int bitLength[],int range)
{
  int i=0;
  int j;
  int totalLength=0;
  for(;i<range;i++)
  {
    char ch=alphaFinal[i];
    for(j=0;j<range;j++)
    {
      if(alphaInitial[j]==ch)
        break;
    }
    int length=freq[j]*bitLength[i];
    totalLength+=length;
  }
  return totalLength;
}
void main()
{
  char *alpha;
  int *freq;
  int size=returnSize();
  alpha=returnAlphaArray();
  freq=returnFreqArray();

  struct treeNode* temp;
  temp=(struct treeNode*)malloc(sizeof(struct treeNode));
  temp=createTree(alpha,freq,size);
  int arr[MAX_TREE_HT], top = 0;
  printCodes(temp, arr, top);

  int actualSpace=returnTotalSpace(alpha,array,freq,bitLength,size);
  int totalSpace=0;
  for(int i=0;i<size;i++)
  {
    totalSpace+=freq[i];
  }
  totalSpace*=8;
  printf("Space Consumption using Normal Technique: %d bits\n",totalSpace);
  printf("Space Consumption after Compression: %d bits\n",actualSpace);
  double percReduction=(totalSpace-actualSpace);
  double next=percReduction*100;
  double next1=next/totalSpace;
  printf("Percentage of Reduction in Space Used : %f %%",next1);

}
