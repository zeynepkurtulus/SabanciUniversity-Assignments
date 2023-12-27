
%{
#include <stdio.h>    
#include <stdlib.h>
#include <string.h>
#include "zeynepkurtulus-hw3.h"

void yyerror (const char *msg) /* Called by yyparse on error */ {
return; }


SetNode ** sets;
int setsSize = 100;
int setIndex = 0;

int error = 0;

char ** errors;
int errorSize = 100;
int errorIndex = 0;

%}


%union {
    StringNode stringNode;
    IdentNode identNode;
    DateNode dateNode;
    SetNode * setNodePtr;
    int lineNum;
    RecipNode * recipNodePtr;
    AdressNode adressNode;
    RecipListNode * recipListNodePtr;
    SendNode * sendNodePtr;
    SendListNode * sendListNodePtr;
    StatementNode * statementNodePtr;

}


%token <stringNode> tSTRING
%token <identNode> tIDENT
%token <adressNode> tADDRESS
%token <dateNode> tDATE
%token tMAIL tENDMAIL tSCHEDULE tENDSCH tSEND tTO tFROM tSET tCOMMA tCOLON tLPR tRPR tLBR tRBR tAT tTIME
%start program


%type <setNodePtr> setStatement
%type <recipNodePtr> recipient;
%type <recipListNodePtr> recipientList;
%type <sendNodePtr> sendStatement;
%type <sendListNodePtr> sendStatements;



%%

program : statements 
;

statements :                  
            | setStatement statements
            | mailBlock statements
;

mailBlock : tMAIL tFROM tADDRESS tCOLON statementList tENDMAIL {
                
            }
;

statementList : 
                | setStatement statementList
                | sendStatement statementList
                | scheduleStatement statementList
;

sendStatements : sendStatement {
                    $$ = addSendToList($1);
                }
                 | sendStatement sendStatements {
                     $$ = addSendListToList($1, $2);
                 }
;

sendStatement : tSEND tLBR tIDENT tRBR tTO tLBR recipientList tRBR {
                    identifierChecker($3);
                   
                    $$ = makeSendNodeFromIdent($3, $7);

                }
                | tSEND tLBR tSTRING tRBR tTO tLBR recipientList tRBR{
                    
                    $$ = makeSendNodeFromString($3,$7);
                }
;

recipientList : recipient  {
                $$ = addRecipToList($1);
            }
            | recipient tCOMMA recipientList {
                $$ = addRecipListToList($1,$3);
            }
;

recipient : tLPR tADDRESS tRPR {
                $$ = makeRecipNodeFromAdd($2);
            }
            | tLPR tSTRING tCOMMA tADDRESS tRPR{
                $$ = makeRecipNodeString($2,$4);
            }
            | tLPR tIDENT tCOMMA tADDRESS tRPR {
                identifierChecker($2);
                $$ = makeRecipNodeIdent($2,$4);
            }
;

scheduleStatement : tSCHEDULE tAT tLBR tDATE tCOMMA tTIME tRBR tCOLON sendStatements tENDSCH {

}
;

setStatement : tSET tIDENT tLPR tSTRING tRPR { 
        makeSetNodeFromIdent($2, $4);
        

    }
;


%%

void makeSetNodeFromIdent(IdentNode ident, StringNode currString) {
    SetNode * setNode = (SetNode *)malloc(sizeof(SetNode));
    setNode->identifier = ident.value;
    setNode->value = currString.value;
    setNode->lineNum = ident.lineNum;
   
    
    if(setIndex < setsSize) {
        sets[setIndex] = setNode;
        setIndex += 1;
    }

    
    else {
        setsSize = setsSize + setsSize;
        sets = realloc(sets, setsSize);
        sets[setIndex] = setNode;
        setIndex += 1;
    }
    


    
}


SendNode * makeSendNodeFromString(StringNode currString, RecipListNode * recipList) {
    SendNode * sendNode = (SendNode *)malloc(sizeof(SendNode));

    sendNode->recips = recipList;
    sendNode->value = currString.value;
    sendNode->identifier = "-1";

    return sendNode;
}

RecipNode * makeRecipNodeIdent(IdentNode ident, AdressNode adress) {
    RecipNode * newNode = (RecipNode *)malloc(sizeof(RecipNode));

    newNode->identifier = ident.value;
    newNode->mail = adress.mail;

    int i = 0;

    SetNode * newIdentNode = (SetNode *)malloc(sizeof(SetNode));
    newIdentNode->identifier = ident.value;
    newIdentNode->lineNum = ident.lineNum;

    for(;i<setIndex;i++) {
        //printf("ident 1 %s - ident 2 %s\n", newNode->identifier, sets[i]->identifier);
        if(strcmp(newIdentNode->identifier, sets[i]->identifier) == 0) {
            newNode->name = sets[i]->value;
        }
    }



    
    return newNode;

}

RecipNode * makeRecipNodeString(StringNode string, AdressNode adress) {
    RecipNode * recipNode = (RecipNode *)malloc(sizeof(RecipNode));

    recipNode->name = string.value;
    recipNode->mail = adress.mail;
    recipNode->identifier = "-1";
    return recipNode;

}

RecipNode * makeRecipNodeFromAdd(AdressNode adress) {
    RecipNode * recipNode = (RecipNode *)malloc(sizeof(RecipNode));

    recipNode->name = "-1";
    recipNode->mail = adress.mail;
    recipNode->identifier = "-1";
    return recipNode;

}





SendListNode * addSendToList (SendNode * send) {
    SendListNode * sendNode = (SendListNode *)malloc(sizeof(SendListNode));

    sendNode->SendIndex = 0;
    sendNode->SendSize = 100;
    int SendSize = sendNode->SendSize;
    sendNode->sends = (SendNode**)malloc(SendSize * sizeof(SendNode*));

    int index = sendNode->SendIndex;
    sendNode->sends[index] = send;
    index += 1;
    sendNode->SendIndex = index;

    return sendNode;
}

RecipListNode * addRecipListToList(RecipNode * recip, RecipListNode * recipList) {
  
            
    int index = recipList->RecipIndex;
    recipList->recips[index] = recip;
    index += 1;
    recipList->RecipIndex = index;
    return recipList;
}

SendListNode * addSendListToList (SendNode * send, SendListNode * sendList) {
    int index = sendList->SendIndex;
    sendList->sends[index] = send;
    index += 1;
    sendList->SendIndex = index;

    return sendList;
}


int identifierChecker(IdentNode ident) {
    /* returns -1 -> when not found index when found*/
    
    int i = 0;

    SetNode * newNode = (SetNode *)malloc(sizeof(SetNode));
    newNode->identifier = ident.value;
    newNode->lineNum = ident.lineNum;

    for(;i<setIndex;i++) {
        //printf("ident 1 %s - ident 2 %s\n", newNode->identifier, sets[i]->identifier);
        if(strcmp(newNode->identifier, sets[i]->identifier) == 0) {
            return i;
        }
            
    }


    error = 1;

    

    char * src = "ERROR at line %d: %s is undefined\n";
    char * dest = (char *)malloc(strlen(src) + strlen(ident.value) + ident.lineNum + 10);
    sprintf(dest, src, ident.lineNum, ident.value);

    if(errorIndex < errorSize) {
        errors[errorIndex] = dest;
        errorIndex += 1;
    }
    else {
        errorSize = errorSize + errorSize;
        errors = realloc(errors, errorSize);
        errors[errorIndex] = dest;
        errorIndex += 1;
    }
    
}



SendNode * makeSendNodeFromIdent(IdentNode ident, RecipListNode * recipList) {
    SendNode * sendNode = (SendNode *)malloc(sizeof(SendNode));

    sendNode->recips = recipList;
    sendNode->identifier = ident.value;

    int i = 0;

    SetNode * newIdentNode = (SetNode *)malloc(sizeof(SetNode));
    newIdentNode->identifier = ident.value;
    newIdentNode->lineNum = ident.lineNum;

    for(;i<setIndex;i++) {
 
        if(strcmp(newIdentNode->identifier, sets[i]->identifier) == 0) {
            sendNode->value = sets[i]->value;
        }
    }

    return sendNode;


}

RecipListNode * addRecipToList(RecipNode * recip) {
    RecipListNode * recipNode = (RecipListNode *)malloc(sizeof(RecipListNode));
    
    recipNode->RecipIndex = 0;
    recipNode->RecipSize = 100;
    int RecipSize = recipNode->RecipSize;
    recipNode->recips = (RecipNode**)malloc(RecipSize * sizeof(RecipNode*));

    int index = recipNode->RecipIndex;

    recipNode->recips[index] = recip;
    index += 1;
    recipNode->RecipIndex = index;

    return recipNode;
}





int main () 
{   

   sets = (SetNode**)malloc(setsSize * sizeof(SetNode*)); 
   errors = (char**)malloc(errorSize * sizeof(char*));

   if (yyparse())
   {
      // parse error
      printf("ERROR\n");
      return 1;
    } 
    else 
    {
        // successful parsing
        if(error == 0) {
            int i = 0;
           
            
        }
        else {
            int i = 0;
            for(;i<errorIndex;i++) {
                printf(errors[i]);
            }
        }
        //printf("OK\n");    
        return 0;
    } 
}
