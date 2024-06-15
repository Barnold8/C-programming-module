#include "rpn.h"
#include "stdio.h"
#include "stack.h"
#include "queue.h"
#include <string.h>


int is_operator(char op){

	char valid[] = {'+','-','*','/','^','(',')'};
	int validSize = sizeof(valid)/sizeof(valid[0]); /* Returns size of the valid array. Code doesnt need to be updated to since it scales automatically */
	int i;
	int isOp = 0;

	for(i = 0; i < validSize; i++){

		if(op == valid[i]){
			
			isOp = 1;
		}

	}

	return isOp;

}

int is_left_associative(char op){

	if(is_operator(op) && op != '^'){
		return 1;
	}
	else if(is_operator(op) && op == '^'){

		return 0;
	}else{

		return -1;
	}


}

int operator_presedence(char op){

	char operators[] = {'+','-','*','/','^'};
	int pres[] = {1,1,2,2,3};
	int opSize = sizeof(operators)/sizeof(operators[0]); /* Returns size of the valid array. Code doesnt need to be updated to since it scales automatically */
	int i,presedence;
	presedence = 0 ;
	for(i = 0; i < opSize; i++){
		if(op == operators[i]){
			presedence = pres[i];	
		}
	}
	return presedence;

}

int test_presedence(char op1,char op2){

	if(operator_presedence(op1) > operator_presedence(op2)){

		return 1;
	}else if(operator_presedence(op1) < operator_presedence(op2)){

		return -1;
	}else{return 0;}
}

void AddRestOps(Queue* Q, Stack* S, int choice){ /* Choice determines if this is based on the ) or if its adding the rest of the operators on the end */
	
	char str[] = {' ','\0'};

	/* Add remaining operators to the Notation*/
	
	
	if(choice){

		/* Add ops till ( is found, the remove ( from the stack*/

		while(*(char*)peek_stack(S) != '('){

			
			str[0] = *(char*)peek_stack(S);
			push_queue(Q,&str,sizeof(char)*2);
			free(peek_stack(S));
			pop_stack(S);
			

		}
		free(peek_stack(S));
		pop_stack(S);

	}else{

		/* Add ops till stack is empty */

		while(peek_stack(S)!= NULL){

			str[0] = *(char*)peek_stack(S);
			push_queue(Q,&str,sizeof(char)*2);
			free(peek_stack(S));
			pop_stack(S);

		}
	}


	/* -------------------------------------- */
	
}

int isNum(char data){

	if((int)data < 48 || (int)data > 57){

		return 0;
	}
	else{return 1;}

}

int validity(char * string){
	int valid  = 1;
	int leftBr = 0;
	int rightBr = 0;

	while(*string != 0){ /* Finally it steps through the string properly for validity checks */
		
		if(!(isNum(*string) || is_operator(*string) || *string == ' ' || *string == '.')){
			
			valid = 0;
		}

		if(*string == '('){leftBr++;}
		else if(*string == ')'){rightBr++;}
		string++;

	}	

	if(leftBr - rightBr != 0){

		valid = 0;

	}

	return valid; /* by default return invalid validity */

}

int EmptyStack(Stack* S){

	if(peek_stack(S) == NULL){return 1;}
	else{return 0;}

}

void OpMagic(Queue* Q, Stack* S, char op){

	char res;
	char str[] = {' ','\0'};
	if(EmptyStack(S)){
		push_stack(S,&op,sizeof(char));
	}
	else{

		res = *(char*)peek_stack(S); /* This is the top of the stack */

		if(op == '('){

			push_stack(S,&op,sizeof(char));

		}else if(op == ')'){

			AddRestOps(Q,S,1);

		}else{
			
			if(test_presedence(op,res) == 1){ /* WORK ENDED HERE GO BACK TO https://www.youtube.com/watch?v=LQ-iW8jm6Mk&lc=z23nt5sjkw2lzf42cacdp4334bqa3knx45ouajpcl5tw03c010c */
				
				push_stack(S,&op,sizeof(char));

			}else{/* if stack var is higher presedence than the op, pop off stack, push. Do this until stack var presedence is less than op presedence, when this happens, push op to stack */

				if(test_presedence(op,res)<1){

					while(test_presedence(op,res) < 1 && peek_stack(S) != NULL){
						str[0] = res;
						
						
						push_queue(Q,&str,sizeof(char)*2);
						free(peek_stack(S));
						pop_stack(S);
						if(peek_stack(S) != NULL){
							res = *(char*)peek_stack(S);
						}
					}
					push_stack(S,&op,sizeof(char));

				

				}
			}
			
			

		}
		
	}
	
}


/* Higher pres snippet for my own sanity test_presedence(LookingChar,peek_stack(S)peek_stack(stack))); */

/* convert an infix expression to postfix (rpn) using the */
/* shunting yard algorithm. */
/* return a queue containing the postfix expression. */
/* if an error occurs during evaluation, return silently with NULL. */
Queue *infix_to_postfix(char *expr)										/* Decimal numbers in one line and - or + on the correct side of a number FIX THIS*/									 
{

	char* ErrorMessage = "error: unable to parse expression.";
	char* special_str;
	int count = 0;
	int iter = 0;
	Queue* Notation = initialise_queue();
	Stack* stack = initialise_stack();
		
	if(!validity(expr)){
		free_queue(Notation);
		free_stack(stack);
		printf("%s\n",ErrorMessage);
		exit(EXIT_FAILURE);
	}
	
	while(*expr != 0){ /* Go through the string */
		
		if(is_operator(*expr)){
				
			/*OpMagic(Notation,stack,*expr);*/

			if(isNum(expr[1])){
				count = 0;
				while(isNum(*expr)||*expr =='.'|| *expr == '-'|| *expr == '+'){ /* this is legit just to get count up */
					count++;
					expr++;
				}

				special_str = malloc((sizeof(char)*count)+1);
				expr-= count;
				

				for(iter = 0; iter < count; iter++){

					special_str[iter] = *expr;
					expr++;

				}
				
				special_str[count] = '\0';
				push_queue(Notation,special_str,sizeof(char)*count+1);
				free(special_str);	
				
			}
			else{
				OpMagic(Notation,stack,*expr);

			}
		
		}


		else if(isNum(*expr)){ 
			count = 0;
			while(isNum(*expr)||*expr =='.'){
				count++;
				expr++;
			}
			special_str = malloc((sizeof(char)*count)+1);
			expr-= count;
			/* assign chars to the string.... */
			
			for(iter = 0; iter < count;iter++){
				special_str[iter] = *expr;
				expr++;
			}

			/* ----------------------------- */

			special_str[count] = '\0';
			push_queue(Notation,special_str,sizeof(char)*count+1);
			free(special_str);			
		}		
		expr++;

	}

	AddRestOps(Notation,stack,0);

	free_stack(stack);
	return Notation;
}

/* evaluate the rpn expression given in *queue. */
/* return the value of the evaluated expression. */
/* if an error occurs during evaluation, return silently with HUGE_VAL. */
/* assume a precision of eight decimal places when performing arithmetic. */
double evaluate_rpn(Queue *queue)
{
	/* this is just a placeholder return */
	/* you will need to replace it */
	return 0.0;
}



/*					printf("%c %c LESS THAN\n",op,res);
					printf("\n-------Stack-----------\n");
					print_stack(S,print_char);
					printf("\n-----------------------\n");
					
					*/
