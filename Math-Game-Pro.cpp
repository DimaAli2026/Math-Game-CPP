#include<iostream>
#include<cstdlib>
#include<string>
#include<ctime>
using namespace std;
enum enQuestionsLevel{easy=1,med=2,hard=3,mix=4};
enum enQuestionsOperation{add=1,sub=2,mul=3,div=4,Mix=5};
struct stQuizz{
short NumberOfQuestion=0;
int Number1=0;
int Number2=0;
string symbol="+";
enQuestionsLevel QuestionsLevel;
enQuestionsOperation QuestionsOperation;
int playerAnswer=0;
int correctAnswer=0;
bool IsAnswerRight=1;
};
struct stMathGameResults{
stQuizz QuestionList[100];
short NumberOfQuestions=0;
string operationSymbol;
string questionsLevel;
short rightAnswers=0;
short wrongAnswers=0;
bool IsPass=true;
};
short readNumberOfQuestions()
{
    short Number=0;
    do{
          cout<<"How many Questions do you want to aswers?1 to 10? ";
          cin>>Number;
      }while(Number<1 || Number>10);
    return Number;
}
enQuestionsLevel readQuestionsLevel()
{
    short Number=0;
    do{
         cout<<"Enter Questions Level [1] Easy,[2] Med,[3] Hard,[4] Mix? ";
         cin>>Number;
      }while(Number<1 || Number>4);
    return (enQuestionsLevel)Number;
}       
enQuestionsOperation readQuestionsOperation()
{
    short Number=0;
    do{
         cout<<"Enter Operation Type [1] Add,[2] Sub,[3] Mul,[4] Div ,[5] Mix? ";
         cin>>Number;
      }while(Number<1 || Number>5);
    return (enQuestionsOperation)Number;               
}
int randomNumber(int From,int To)
{
    int randNum;
    randNum=rand()%(To-From+1)+From;
    return randNum;
}
int readPlayerAnswer()
{
   int Number;
   cin>>Number;
   return Number;
}
int simpleCalculator(int Number1,int Number2,enQuestionsOperation OpType)
{
   switch(OpType)
   {
       case enQuestionsOperation::add:
           return Number1+Number2;
       case enQuestionsOperation::sub:
            return Number1-Number2;
       case enQuestionsOperation::mul:
            return Number1*Number2;
       case enQuestionsOperation::div:
            return Number1/Number2;
   
   }         
}               
void askAboutPlayerAnswer(stQuizz& Quizz)
{
    Quizz.playerAnswer=readPlayerAnswer();
}
bool determineIsPlayerAnswerCorrect(stQuizz& Quizz)
{    
    Quizz.IsAnswerRight=(Quizz.playerAnswer==Quizz.correctAnswer);
    return Quizz.IsAnswerRight;
}

void getPlayerScreenAnswer(stQuizz Quizz)
{
   if(Quizz.IsAnswerRight==1)
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
string QuestionsOperationSymbol(enQuestionsOperation QuesOp)
{
   string arr1[5]={"+","-","*","/","Mix"};
   return arr1[QuesOp-1];
}  
void printQuestion(stQuizz Quizz,short NumberOfQuestions)
{
    cout<<"Question[ "<<Quizz.NumberOfQuestion+1<<"/"<<NumberOfQuestions<<" ]:\n";
    cout<<Quizz.Number1<<endl;
    cout<<Quizz.Number2<<" ";
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
         
    Quizz.symbol=QuestionsOperationSymbol(Quizz.QuestionsOperation);
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
          Quizz.Number1=randomNumber(1,10);
          Quizz.Number2=randomNumber(1,10);
          
       }
       break;
       case enQuestionsLevel::med:
       {
           Quizz.Number1=randomNumber(10,50);
           Quizz.Number2=randomNumber(10,50);  
       }
       break;
       case enQuestionsLevel::hard:
       {
           Quizz.Number1=randomNumber(50,100);
           Quizz.Number2=randomNumber(50,100);  
       }
    }  
    Quizz.correctAnswer=simpleCalculator(Quizz.Number1,Quizz.Number2,Quizz.QuestionsOperation);
    
           
}  
void getQuestions(stQuizz& Quizz,stMathGameResults& MathGameResults,enQuestionsLevel level,enQuestionsOperation QuesOp)
{
   for(int NumberOfQuestion=Quizz.NumberOfQuestion;NumberOfQuestion<MathGameResults.NumberOfQuestions;NumberOfQuestion++)
    {
      generateQuestionList(MathGameResults.QuestionList[NumberOfQuestion],level,QuesOp);
      printQuestion(MathGameResults.QuestionList[NumberOfQuestion],MathGameResults.NumberOfQuestions);
      askAboutPlayerAnswer(MathGameResults.QuestionList[NumberOfQuestion]);
      printQuesResAndCaleNumRigAnsAndWrAns(MathGameResults,MathGameResults.QuestionList[NumberOfQuestion]);
      cout<<"\n\n";
    }  
      
}  
bool isPassQuizz(stMathGameResults& MathGameResults)
{
     MathGameResults.IsPass=(MathGameResults.rightAnswers>=MathGameResults.wrongAnswers);
     return MathGameResults.IsPass;
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
string QuestionsLevelName(enQuestionsLevel Level)
{
   string arr2[4]={"Easy","Med","Hard","Mix"};
   return arr2[Level-1];
} 
          
void ResetScreenColor()
{
    system("cls");
    system("color 0F");
}
void playGame(stQuizz& Quizz,stMathGameResults& MathGameResults)
{
   enQuestionsLevel level;
   enQuestionsOperation QuesOp;
   MathGameResults.NumberOfQuestions=readNumberOfQuestions();
   level=readQuestionsLevel();
   MathGameResults.questionsLevel=QuestionsLevelName(level);
   QuesOp=readQuestionsOperation();
   MathGameResults.operationSymbol=QuestionsOperationSymbol(QuesOp);
   getQuestions(Quizz,MathGameResults,level,QuesOp);
   showMathGameResultsToPlayer(MathGameResults);
}
void printMathGameResults(stMathGameResults& MathGameResults)
{
   cout<<"Number of Questions is: "<<MathGameResults.NumberOfQuestions<<endl;
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
      ResetScreenColor();
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
      
   



         
            
    
    
       
                    
    
             

    
