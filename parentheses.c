#include <stdio.h>
#include <stdlib.h>
#define bool int

//creating a struct to store input
struct myNodes{
	char data;
	struct myNodes *next;
};

//prototypes
void push(struct myNodes** itemRef, int entry);

char pop(struct myNodes** itemRef);

bool matches(char, char);

bool isValid(char[]);


int main() {
        char *inputString;
	size_t size = 300;
	//reading logic
	while(!feof(stdin)) {
		inputString = ((char *) malloc(sizeof(char)*300));
		int signal = getline(&inputString, &size, stdin); //sets inputString to the current line from stdin
		
		//logic for exiting program without printing anything more
		if(signal == -1) {
			free(inputString);
			return 0;
		}
		//validity logic
		if(isValid(inputString) == 1) {
			printf("VALID");
		}else if(isValid(inputString) == 0) {
			printf("NOT VALID");
		}
	//freeing inputString
	free(inputString);
	}
	return 0;
}


//push method adds to node stack
void push(struct myNodes** itemRef, int entry) {
      //the linked list logic
      struct myNodes* newNode = (struct myNodes *) malloc(sizeof(struct myNodes));

      if(newNode == NULL) {
	      free(newNode);
	      printf("Error");
	      getchar();
	      exit(0);
      }

      newNode->data = entry;
      newNode->next = *itemRef;
      *itemRef = newNode;      
}


//pop method removes from node stack
char pop(struct myNodes** itemRef) {
      char store;
      struct myNodes *top;

      if(*itemRef == NULL) {
	printf("Error");
  	getchar();
	exit(0);
      } else {
        top = *itemRef;
	store = top->data;
	*itemRef = top->next;
	free(top);
	return store;
      }	
}


//checks if the opening parenthese matches the closing one
bool matches(char open, char close) {
	if(open == '[' && close == ']') {
		return 1;
	}else if(open == '(' && close == ')') {
		return 1;
	}else if(open == '{' && close == '}') {
		return 1;
	}else if(open == '<' && close == '>') {
		return 1;
	}else{ 
		return 0;
	}
}


//simplifies the logic for validity of lines with "parentheses" in them
bool isValid(char line[]) {
	int ct = 0;
	struct myNodes *stack = NULL;

	while(line[ct]) {
		//push
		if(line[ct] == '[' || line[ct] == '(' || line[ct] == '{' || line[ct] == '<') {
			push(&stack, line[ct]);
		}
		//pop
		if(line[ct] == ']' || line[ct] == ')' || line[ct] == '}' || line[ct] == '>') {
			if(stack == NULL) { //if there's nothing to check
				return 0;
			} else if(!matches(pop(&stack), line[ct])) {
				return 0;
			}
		}
		ct++;
	}
	//valid
	if(stack == NULL) {
		return 1;
	}

	//freeing stack
	free(stack);
	

	return 0;
}
