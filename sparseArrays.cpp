#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

//creates the base type for elements in a linkedList
class node{
public:
	//this type of node has two values and a next pointer
	int val1;
	int val2;
	node * next;
	node(int v1, int v2);
};

//linkedList class: data object containing a sequence of integers connected to pointers
//in which each pointer connects to the next integer/pointer object
class linkedList{
public:
	//only data field is the pointer to its beginning
	node * head;
	//each of these methods is explained when defined
	void fill();
	linkedList();
	void output();
	linkedList add(linkedList other);
	pair<node *, node *> search(int val, int row);
};

//creates a new node with given values and null pointer
node::node(int v1,int v2):
	val1(v1),
	val2(v2),
	next(NULL){}

//fills a linkedList with integer inputs
void linkedList::fill(){

	//if the list is not empty, don't fill it
	if(head){
		cout << "List is non-empty; cannot fill.\n";
		return;
	}

	//take in the size of the array
	int numInList; cin >> numInList;

	//catch if there's an invalid number to be inserted
	if(numInList < 1){
		if(numInList < 0)
			cout << "Not a valid number of list elements.\n";
		return;
	}

	//take in first node, set it as the head
	int c; cin >> c;
	int x; cin >> x;
	head = new node(c, x);

	//hold a pointer to the current node
	node * current = head;

	//take in values, create nodes, and add them to the list
	for(int j = 1; j<numInList; j++){

		cin >> c;
		cin >> x;

		current -> next = new node(c,x);
		current = current -> next;
		
	}
}

//create an empty linkedList
linkedList::linkedList():
	head(NULL){}

//output a linkedList
void linkedList::output(){
	node * current = head;
	while (current != NULL){
		cout << to_string(current->val1) << " " << to_string(current -> val2) << " ";
		current = current -> next;
	}
	cout << "\n";
}

//adds this linkedList to another one
linkedList linkedList::add(linkedList other){
	
	//create a new linkedList to hold the sum
	linkedList newList;
	//create a pointer to a dummy node (to be eliminated at the end)
	node * curNew = new node(-1,-1);
	//set the newList's head to the current node (to keep track of the list's beginning)
	newList.head = curNew;
	//hold pointers to locations in the lists being added
	node * curOther = other.head;
	node * curThis = head;


	int colOther;
	int colThis;

	//while both lists have elements that have not been traversed
	while(curThis && curOther){

		//store current column values of lists
		colThis = curThis -> val1;
		colOther = curOther -> val1;

		//whichever pointer has lower column value, copy it into the summed list and increment the respective pointer
		if(colThis < colOther){
			curNew -> next = new node(colThis, curThis -> val2);
			curThis = curThis -> next;
		}
		else if(colOther < colThis){
			curNew -> next = new node(colOther, curOther -> val2);
			curOther = curOther -> next;
		}
		//if the column values are equal, create a node with the two values summed
		//increment both pointers
		else{
			curNew -> next = new node(colThis, curThis -> val2 + curOther -> val2);
			curThis = curThis -> next;
			curOther = curOther -> next;
		}

		//increment the curNew pointer
		curNew = curNew -> next;
	}

	//if either list ran out, append the list that still has elements
	//to the end of the summed list
	if(!curThis){
		curNew -> next = curOther;
		curOther = NULL;
	}
	else if(!curOther){
		curNew -> next = curThis;
		curThis = NULL;
	}

	//eliminate the dummy node
	newList.head = newList.head ->next;

	return newList;

}

//search the linkedList for a given value and return the beginning and ending
//pointers of a linkedList filled with the row and column values of the locations
//at which the value was found
pair<node *, node *> linkedList::search(int val,int row){
	pair<node*, node*> ans;

	//create dummy node so that current can be incremented to the head upon entering the loop
	node * current = new node(-1,-1);
	current -> next = head;

	node * newNode;

	//while current-> next exists
	while(current -> next){
		//move to next
		current = current -> next;

		//if the value is found
		if(current -> val2 == val){

			//create a new node with the row and column at which the value was found
			newNode = new node(row, current->val1);

			//if first hasn't been filled yet (no value was found)
			if(!ans.first){
				//set both first and second equal to the new node
				ans.first = newNode;
				ans.second = newNode;
			}
			//otherwise
			else{
				//attach the new node to the end of the list
				ans.second -> next = newNode;
				//increment the pointer to the end of the list
				ans.second = ans.second -> next;
			}
		}
	}

	return ans;
}

//search a vector of linkedLists for a value and return the linkedList
//of the array indices at which the value was found
static linkedList search(vector<linkedList> arr){
	linkedList searchList;
	//create a dummy node to be eliminated later
	searchList.head = new node(-1,-1);
	//create a pointer to the end of the list for quick insertion
	node * listEnd = searchList.head;

	pair<node*,node*> results;
	int val; cin >> val;

	//for every row of the array
	for(int i = 0; i< arr.size(); i++){
		//get pointers to the beginning and end of a list containing
		//the rows and columns of where the value was found
		results = arr.at(i).search(val, i);

		//append that list to the searchList
		listEnd -> next = results.first;
		if(results.second){
			listEnd = results.second;
		}
	}

	//eliminate the dummy node
	searchList.head = searchList.head -> next;

	return searchList;
}

//output an array of linkedLists
static void output(vector<linkedList> arr){
	for(int i = 0; i < arr.size(); i++){
		arr.at(i).output();
	}
}

int main(){

	//take in both arrays
	//create a vector of linkedLists
	vector<linkedList> arr1;
	int nRows; cin >> nRows;
	//for the given number of rows,
	for(int i = 0; i<nRows; i++){
		//create a new linkedList
		linkedList newRow;
		//fill it with inputted values
		newRow.fill();
		//add it to the array
		arr1.push_back(newRow);
	}

	//see same comments for above array
	vector<linkedList> arr2;
	cin >> nRows;
	for(int i = 0; i<nRows; i++){
		linkedList newRow;
		newRow.fill();
		arr2.push_back(newRow);
	}

	//create an array to hold the sum of the arrays and
	//add it in by row by summing the arrays by row
	vector<linkedList> sumArr;
	for(int i = 0; i<nRows; i++){
		sumArr.push_back(arr1.at(i).add(arr2.at(i)));
	}


	int numSearches;
	cin >> numSearches;

	//create an array to hold the search results
	//and add it in by successive searches for inputted values
	vector<linkedList> searches;
	for(int i = 0; i<numSearches; i++){
		searches.push_back(search(sumArr));
	}

	//output the results
	output(searches);

	ios::sync_with_stdio(false);

	return 0;
}
