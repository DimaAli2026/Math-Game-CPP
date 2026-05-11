#include<iostream>
#include<cstdlib>
#include<string>
#include<ctime>
using namespace std;
enum enQuestionsLevel{easy=1,med=2,hard=3,mix=4};

enum enQuestionsOperation{add=1,sub=2,mul=3,div=4,Mix=5};

struct stQuizz{
short numberOfQuestion=0;
int number1=0;
int number2=0;
string symbol="+";
enQuestionsLevel QuestionsLevel;
enQuestionsOperation QuestionsOperation;
int playerAnswer=0;
int correctAnswer=0;
bool isAnswerRight=1;
};

struct stMathGameResults{
stQuizz QuestionList[100];
short numberOfQuestions=0;
string operationSymbol;
string questionsLevel;
short rightAnswers=0;
short wrongAnswers=0;
bool isPass=true;
};


short readNumberOfQuestions()
{
    short number=0;
    do{
          cout<<"How many Questions do you want to answer?1 to 10? ";
          cin>>number;
      }while(number<1 || number>10);
    return number;
}

enQuestionsLevel readQuestionsLevel()
{
    short number=0;
    do{
         cout<<"Enter Questions Level [1] Easy,[2] Med,[3] Hard,[4] Mix? ";
         cin>>number;
      }while(number<1 || number>4);
    return (enQuestionsLevel)number;
}     
  
enQuestionsOperation readQuestionsOperation()
{
    short number=0;
    do{
         cout<<"Enter Operation Type [1] Add,[2] Sub,[3] Mul,[4] Div ,[5] Mix? ";
         cin>>number;
      }while(number<1 || number>5);
    return (enQuestionsOperation)number;               
}

int randomNumber(int From,int To)
{
    int randNum;
    randNum=rand()%(To-From+1)+From;
    return randNum;
}

int readPlayerAnswer()
{
   int number;
   cin>>number;
   return number;
}

int simpleCalculator(int number1,int number2,enQuestionsOperation OpType)
{
   switch(OpType)
   {
       case enQuestionsOperation::add:
           return number1+number2;
       case enQuestionsOperation::sub:
            return number1-number2;
       case enQuestionsOperation::mul:
            return number1*number2;
       case enQuestionsOperation::div:
            return number1/number2;
   
   }         
} 
              
void askAboutPlayerAnswer(stQuizz& Quizz)
{
    Quizz.playerAnswer=readPlayerAnswer();
}

bool determineIsPlayerAnswerCorrect(stQuizz& Quizz)
{    
    Quizz.isAnswerRight=(Quizz.playerAnswer==Quizz.correctAnswer);
    return Quizz.isAnswerRight;
}

void getPlayerScreenAnswer(stQuizz& Quizz)
{
   if(Quizz.isAnswerRight==1)
      system("color 2F");
   else
      system("color 4F");
}     
     
void printQuesResAndCaleNumRigAnsAndWrAns(stMathGameResults& MathGameResults,stQuizz& Quizz)
{
   if(determineIsPlayerAnswerCorrect(Quizz)==true)
     {
        MathGameResults.rightAnswers++;
        cout<<"Right Answer :-)\n";
     }
   else
   {
      MathGameResults.wrongAnswers++;
      cout<<"Wrong Answer :-(\n";
      cout<<"the right answer is "<<Quizz.correctAnswer<<endl;
      cout<<endl<<"\n";
   }
   getPlayerScreenAnswer(Quizz);
}   

string questionsOperationSymbol(enQuestionsOperation QuesOp)
{
   string arr1[5]={"+","-","*","/","Mix"};
   return arr1[QuesOp-1];
}  

void printQuestion(stQuizz& Quizz,short numberOfQuestions)
{
    cout<<"Question[ "<<Quizz.numberOfQuestion+1<<"/"<<numberOfQuestions<<" ]:\n";
    cout<<Quizz.number1<<endl;
    cout<<Quizz.number2<<" ";
    cout<<Quizz.symbol<<endl;
    cout<<"______________\n";
}  

void generateQuestionList(stQuizz& Quizz,enQuestionsLevel level,enQuestionsOperation QuesOp)
{
    if(QuesOp==enQuestionsOperation::Mix)
    {
       Quizz.QuestionsOperation=(enQuestionsOperation)randomNumber(1,4);
    }
    else{
         Quizz.QuestionsOperation=QuesOp;
        }
         
    Quizz.symbol=questionsOperationSymbol(Quizz.QuestionsOperation);
    if(level==enQuestionsLevel::mix)
    {
       Quizz.QuestionsLevel=(enQuestionsLevel)randomNumber(1,3);
    }
    else{
            Quizz.QuestionsLevel=level; 
        }   
    switch(Quizz.QuestionsLevel)
    {
       case enQuestionsLevel::easy:
       {
          Quizz.number1=randomNumber(1,10);
          Quizz.number2=randomNumber(1,10);
          
       }
       break;
       case enQuestionsLevel::med:
       {
           Quizz.number1=randomNumber(10,50);
           Quizz.number2=randomNumber(10,50);  
       }
       break;
       case enQuestionsLevel::hard:
       {
           Quizz.number1=randomNumber(50,100);
           Quizz.number2=randomNumber(50,100);  
       }
    }  
    Quizz.correctAnswer=simpleCalculator(Quizz.number1,Quizz.number2,Quizz.QuestionsOperation);
    
           
}  

void getQuestions(stQuizz& Quizz,stMathGameResults& MathGameResults,enQuestionsLevel level,enQuestionsOperation QuesOp)
{
   for(int numberOfQuestion=Quizz.numberOfQuestion;numberOfQuestion<MathGameResults.numberOfQuestions;numberOfQuestion++)
    {
      generateQuestionList(MathGameResults.QuestionList[numberOfQuestion],level,QuesOp);
      printQuestion(MathGameResults.QuestionList[numberOfQuestion],MathGameResults.numberOfQuestions);
      askAboutPlayerAnswer(MathGameResults.QuestionList[numberOfQuestion]);
      printQuesResAndCaleNumRigAnsAndWrAns(MathGameResults,MathGameResults.QuestionList[numberOfQuestion]);
      cout<<"\n\n";
    }  
      
}  

bool isPassQuizz(stMathGameResults& MathGameResults)
{
     MathGameResults.isPass=(MathGameResults.rightAnswers>=MathGameResults.wrongAnswers);
     return MathGameResults.isPass;
}   

void showMathGameResultsToPlayer(stMathGameResults& MathGameResults)
{
    cout<<"________________________________________\n\n";
    if(isPassQuizz(MathGameResults)==1)
       cout<<"Final Results is Pass :-)\n";
    else
       cout<<"Final Results is Fail :-(\n";
    cout<<"\n_________________________________________\n\n";  
}

string questionsLevelName(enQuestionsLevel Level)
{
   string arr2[4]={"Easy","Med","Hard","Mix"};
   return arr2[Level-1];
} 
          
void resetScreenColor()
{
    system("cls");
    system("color 0F");
}

void playGame(stQuizz& Quizz,stMathGameResults& MathGameResults)
{
   enQuestionsLevel level;
   enQuestionsOperation QuesOp;
   MathGameResults.numberOfQuestions=readNumberOfQuestions();
   level=readQuestionsLevel();
   MathGameResults.questionsLevel=questionsLevelName(level);
   QuesOp=readQuestionsOperation();
   MathGameResults.operationSymbol=questionsOperationSymbol(QuesOp);
   getQuestions(Quizz,MathGameResults,level,QuesOp);
   showMathGameResultsToPlayer(MathGameResults);
}

void printMathGameResults(stMathGameResults& MathGameResults)
{
   cout<<"Number of Questions is: "<<MathGameResults.numberOfQuestions<<endl;
   cout<<"Questions level : "<<MathGameResults.questionsLevel<<endl;
   cout<<"Op Type : "<<MathGameResults.operationSymbol<<endl;
   cout<<"Number of Right Answers : "<<MathGameResults.rightAnswers<<endl;
   cout<<"Number of Wrong Answers : "<<MathGameResults.wrongAnswers<<endl;
   cout<<"___________________________________________\n\n";
}   

void startMathGame()
{
  stMathGameResults MathGameResults;
  stQuizz Quizz;
  char playAgain='y';
  do{
      resetScreenColor();
      playGame(Quizz,MathGameResults);
      printMathGameResults(MathGameResults);
      cout<<"Do you want to play again ? Y/N ?";
      cin>>playAgain;
     }while((playAgain=='y') || (playAgain=='Y'));
}    


int main()
{
    srand((unsigned)time(NULL));
    startMathGame();
    return 0;
}    
      
   



         
            
    
    
       
                    
    
             


