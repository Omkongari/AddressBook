#define SUCCESS 0
#define FAILURE 1

typedef struct node{
    int data;
    struct node *prev;
    struct node *next;
}Dlist;

typedef struct{
    Dlist *head;
    Dlist *tail;
}startend;

int validate_operand(char *, char *);
int validate_operator(char *);
int assign_values(startend *, startend *, char *,char *);
int addition(startend *, startend *, startend *,char *,char *);
int subadd(startend *, startend *, startend *);
int substraction(startend *, startend *, startend *,char *,char *);
int multiplication(startend *, startend *, startend *,char *,char *);
int addmul(startend *, startend *, startend *);
int division(startend *, startend *, startend *,char *,char *);
int multiply(Dlist *,int ,startend *);
int copy(startend *, startend *);
int addelement(int ,startend *);
int clear(startend *);
int addelementlast(startend *);
int final(startend *);
int copy_list(startend *,startend *);
int dividesub(startend *,startend *,startend *);
int compare(startend *,startend *);
int muladd(startend *, startend *, startend *);