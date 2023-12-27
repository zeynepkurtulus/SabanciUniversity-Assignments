#ifndef __ZEYNEPKURTULUSHW3_H
#define __ZEYNEPKURTULUSHW3_H

 
typedef struct SetNode
{
    char *value;
    char *identifier;
    int lineNum;


} SetNode;

typedef struct StringNode
{
    char *value;
    int lineNum;

} StringNode;

typedef struct IdentNode
{
    char *value;
    int lineNum;

} IdentNode;

typedef struct RecipNode 
{
    char *name;
    char *mail;
    char *identifier;
} RecipNode;

typedef struct AdressNode
{
    char *mail;
} AdressNode;

typedef struct RecipListNode
{
    RecipNode ** recips;
    int RecipIndex;
    int RecipSize;

   

} RecipListNode;

typedef struct SendNode 
{
    RecipListNode * recips;
    char *identifier;
    char *value;
} SendNode;

typedef struct SendListNode 
{
    SendNode ** sends;
    int SendIndex;
    int SendSize;
}SendListNode;

typedef struct StatementNode 
{
    SendNode * send;
}StatementNode;

typedef struct DateNode 
{
    char * day;
    char * month;
    char * year;
}DateNode;

int identifierChecker(IdentNode); 
int checkRecipIdentifier(RecipListNode *);

void makeSetNodeFromIdent(IdentNode, StringNode);
RecipNode * makeRecipNodeIdent(IdentNode, AdressNode);
RecipNode * makeRecipNodeString(StringNode, AdressNode);
RecipNode * makeRecipNodeFromAdd(AdressNode);

RecipListNode * addRecipToList(RecipNode *);
RecipListNode * addRecipListToList(RecipNode * , RecipListNode * );

SendNode * makeSendNodeFromString(StringNode, RecipListNode *);
SendNode * makeSendNodeFromIdent(IdentNode, RecipListNode *);

SendListNode * addSendToList (SendNode * );
SendListNode * addSendListToList (SendNode *, SendListNode *);


void sendNotification(AdressNode, SendNode *);

#endif
