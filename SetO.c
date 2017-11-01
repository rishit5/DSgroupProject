#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<conio.h>
typedef struct Node{
	int number;
	struct Node *right_ptr;
	struct Node *left_ptr;
}Node;
Node *Ins_Node(Node *head_ref, int n){
	Node *new_ptr = (Node *)malloc(sizeof(Node));
	new_ptr->number = n;
	new_ptr->right_ptr = NULL;
	new_ptr->left_ptr = NULL;
	if(head_ref == NULL){
		head_ref = new_ptr;
	}else{
		new_ptr->right_ptr = head_ref;
		head_ref->left_ptr = new_ptr;
		head_ref = new_ptr;
	}
	return head_ref;
}
Node *Delete(Node *head_ref, int n){
	Node *temp = head_ref;
	Node *prev = NULL;
	Node *next = NULL;
	while(temp != NULL){
		if(((temp->number == n) && (temp->right_ptr == NULL)) && (temp->left_ptr == NULL) ) {
			head_ref = NULL;
			temp = NULL;
		}else if((temp->number == n) && (temp->left_ptr == NULL)){
			head_ref = head_ref->right_ptr;
			head_ref->left_ptr = NULL;
			temp = temp->right_ptr;
		}else if((temp->number == n) && (temp->right_ptr == NULL)){
			prev = temp->left_ptr;
			prev->right_ptr = NULL;
			temp = temp->right_ptr;
			// printf("hiiii\n");
		}else if(temp->number == n){
			prev = temp->left_ptr;
			next = temp->right_ptr;
			prev->right_ptr = next;
			next->left_ptr = prev;
			temp = next;
			// printf("heylo\n");
		}else{
			temp = temp->right_ptr;
		}
		// printf("hey\n");
	}
	return head_ref;
}
void Display(Node *head_ref){
	Node *temp = head_ref;
	if(head_ref == NULL){
		printf("Empty\n");
		return;
	}
	printf("\n{");
	while(temp->right_ptr != NULL){
		printf("% d ,", temp->number);
		temp = temp->right_ptr;
	}
	printf(" %d }", temp->number);

}
void UnionList(Node *listA, Node *listB){
	Node *res = listA;
	Node *temp = res;
	while(temp->right_ptr!=NULL)	temp = temp->right_ptr;
	temp->right_ptr = listB;
	listB->left_ptr = temp;
	temp = res;
	//Display(temp);
	while(temp!= NULL){
		Delete(temp->right_ptr, temp->number);
		temp = temp ->right_ptr;
	}
	Display(res);
}
void IntersectionList(Node *listA, Node *listB){
	Node *res = NULL;
	Node *temp1 = listA;
	Node *temp2 = listB;
	while(temp1 != NULL){
		// printf("%d", temp1->number);
		while(temp2 != NULL){
			// printf("%d", temp2->number);
			if(temp1->number == temp2->number){
				res = Ins_Node(res, temp2->number);
			}
			temp2 = temp2->right_ptr;
		}
		temp2 = listB;
		temp1 = temp1->right_ptr;
	}
	//Display(res);
	Node *temp = res;
	while(temp!= NULL){
		Delete(temp->right_ptr, temp->number);
		temp = temp ->right_ptr;
	}
	Display(res);
}
void SetMemership(Node *listA, Node *listB, int n){
	int flag1 = 0, flag2 = 0;
	Node *temp1 = listA;
	Node *temp2 = listB;
	while(temp1 != NULL){
		if(temp1->number == n){
			flag1 = 1;
		}
		temp1 = temp1->right_ptr;
	}
	while(temp2 != NULL){
		if(temp2->number == n){
			flag2 = 1;
		}
		temp2 = temp2->right_ptr;
	}
	if(flag1 == 1 && flag2 == 1){
		printf("Present in Both sets");
	}else if(flag1 == 1 && flag2 == 0){
		printf("\nPresent in ListA only");
	}else{
		printf("\nPresent in ListB only");
	}
}
void Complement(Node *Universal, Node *listA){
	Node *res = Universal;
	Node *temp = listA;
	// printf("lol\n");
	while((temp != NULL) && (res != NULL)){
		// printf("\nheyy");
		res = Delete(res, temp->number);
		temp = temp->right_ptr;
		// Display(res);
	}
	// printf("%p", res);
	Display(res);
}
void PowerSet(Node *listA){
	Node *temp = listA;
	int i, j, size = 0;
	int a[100];
	while(temp != NULL){
		a[size++] = temp->number;
		temp = temp->right_ptr;
	}
	for(i = 0; i<pow(2, size); i++){
		printf("{");
		for(j = 0; j<size; j++){
			if(i & (1<<j)){
            	printf(" %d ", a[j]);
            }
		}
		printf("}\n");
	}
}
void SetDifference(Node *listA, Node *listB){
	Node *temp1 = listA;
	Node *temp2 = listB;
	// Node *res = temp1;
	while(temp2 != NULL){
		temp1 = Delete(temp1, temp2->number);
		temp2 = temp2->right_ptr;
	}
	Display(temp1);
}
void SetContainment(Node *listA, Node *listB){
	int flag1 = 0, flag2 = 0;
	Node *temp2 = listA;
	Node *temp1 = listB;
	while(temp1 != NULL){
		while(temp2 != NULL){
			if(temp1->number == temp2->number){
				flag1 = 1;
			}
			temp2 = temp2->right_ptr;
		}
		if(flag1 == 0){
			flag2 = -1;
			break;
		}
		temp1 = temp1->right_ptr;
	}
	if(flag2 == -1){
		printf("Not a Subset\n");
	}else{
		printf("Is a Subset\n");
	}
}
void CartesianProduct(Node *listA, Node *listB){
	Node *temp1 = listA;
	Node *temp2 = listB;
	while(temp1 != NULL){
		while(temp2 != NULL){
			printf("{%d, %d}\n", temp1->number, temp2->number);
			temp2 = temp2->right_ptr;
		}
		temp2 = listB;
		temp1 = temp1->right_ptr;
	}
}
Node *CreateSet(char ch){
    int choice = 0;
    int n;
    Node *head_ref = NULL;
    do{
        printf("InsertElementsIntoSet%c", ch);
        printf("\n1.EnterElement");
        printf("\nAny key to Finish");
        printf("\nCHOICE:");
        scanf("%d", &choice);
        if(choice == 1){
            printf("Enter the number");
            scanf("%d", &n);
            head_ref = Ins_Node(head_ref, n);
        }
    }while(choice == 1);
    return head_ref;
}
Node *Screen(){
    int ch;
    printf("SetOperations");
    printf("\n1.CreateSetA");
    printf("\n2.CreateSetB");
    printf("\n3.Exit");
    printf("Choice: ");
    scanf("%d", &ch);
    Node *head;
    switch(ch){
        case 1: head = CreateSet((char)'A');
                system("clear");
                return head;
                break;
        case 2: head = CreateSet((char)'B');
                system("clear");
                return head;
                break;
        case 3:
                break;

    }
    printf("\n\n\n\n\n\n\n\n");
}
Node *Copy(Node *head_ref){
    Node *head = NULL;
    Node *temp = head_ref;
    while(temp != NULL){
        head = Ins_Node(head, temp->number);
        temp = temp->right_ptr;
    }
    return head;
}
void main(){
	/*Node *head_ref1 = NULL;
	head_ref1 = Ins_Node(head_ref1, 1);
	head_ref1 = Ins_Node(head_ref1, 2);
	head_ref1 = Ins_Node(head_ref1, 3);
	head_ref1 = Ins_Node(head_ref1, 4);
	head_ref1 = Ins_Node(head_ref1, 5);
	head_ref1 = Ins_Node(head_ref1, 6);
	Display(head_ref1);
	Node *head_ref2 = NULL;
	head_ref2 = Ins_Node(head_ref2, 3);
	head_ref2 = Ins_Node(head_ref2, 5);
	head_ref2 = Ins_Node(head_ref2, 0);
	head_ref2 = Ins_Node(head_ref2, 13);
	head_ref2 = Ins_Node(head_ref2, 11);
	head_ref2 = Ins_Node(head_ref2, 9);
	// head_ref2 = Ins_Node(head_ref2, 13);
	// head_ref2 = Ins_Node(head_ref2, 11);
	// head_ref = Delete(head_ref, 3);
	Display(head_ref2);
	printf("Power Set is: \n");
	printf("Φ");
	PowerSet(head_ref2);
	// head_ref = head_ref->right_ptr;
	// printf(" %p ", head_ref);*/
	Node *head_ref1 = Screen();
    Node *head_ref2 = Screen();

    printf("SetA:");
    Display(head_ref1);

    printf("\nSetB:");
    Display(head_ref2);

    Node *temp1 = Copy(head_ref1);
    Node *temp2 = Copy(head_ref2);
    printf("\nSetA Union SetB:");
    UnionList(temp1, temp2);
    free(temp1);
    free(temp2);

    /*printf("\nSetA:");
    Display(head_ref1);
    printf("\nSetB:");
    Display(head_ref2);*/

    temp1 = Copy(head_ref1);
    temp2 = Copy(head_ref2);

    printf("\nSetA Intersection SetB:");
    IntersectionList(temp1, temp2);

    free(temp1);
    free(temp2);

    printf("\nEnter an element to check SetMembership Between SetA and SetB: ");
    int num;
    scanf("%d", &num);
    temp1 = Copy(head_ref1);
    temp2 = Copy(head_ref2);
    SetMemership(temp1, temp2, num);

    free(temp1);
    free(temp2);

    printf("\nConsider SetA as Universal then (~)SetB is: ");
    temp1 = Copy(head_ref1);
    temp2 = Copy(head_ref2);
    Complement(temp1, temp2);
    free(temp1);
    free(temp2);

    printf("\nPowerSet of SetA: \n");
    temp1 = Copy(head_ref1);
    temp2 = Copy(head_ref2);
    PowerSet(temp1);

    printf("\nPowerSet of SetB: \n");
    PowerSet(temp2);

    printf("\nSetA - SetB: ");
    temp1 = Copy(head_ref1);
    temp2 = Copy(head_ref2);
    SetDifference(temp1, temp2);
    free(temp1);
    free(temp2);

    printf("\nSetB - SetA: ");
    temp1 = Copy(head_ref1);
    temp2 = Copy(head_ref2);
    SetDifference(temp2, temp1);
    free(temp1);
    free(temp2);

    printf("\nChecking Subset between SetA and SetB: ");
    temp1 = Copy(head_ref1);
    temp2 = Copy(head_ref2);
    SetContainment(temp1, temp2);
    free(temp1);
    free(temp2);

    printf("\nCartesian product SetA x SetB:\n");
    temp1 = Copy(head_ref1);
    temp2 = Copy(head_ref2);
    CartesianProduct(temp1, temp2);
    free(temp1);
    free(temp2);

    /*printf("\nSetA:");
    Display(head_ref1);
    printf("\nSetB:");
    Display(head_ref2);*/

   // return 0;
}
