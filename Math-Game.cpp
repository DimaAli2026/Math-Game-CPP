#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
using namespace std;
enum enQuestionsLevel{easy=1,med=2,hard=3,mix=4};
enum enQuestionsType{add=1,sub=2,mul=3,div=4,Mix=5};
struct stQuestionInfo{	
int number1;
int number2;
enQuestionsType currentType;
enQuestionsLevel QuestionsLevel;
string QuestionsTypeForm;
enQuestionsType QuestionsType;
int userAnswer;
int correctAnswer;
};
struct stMathGameResults{
short numberOfQuestions;
string questionsLevel;
string questionsType;
short rightAnswers=0;
short wrongAnswers=0;
};
int randomNumber(int From,int To)
{
	 int randNum=0;
	 randNum=rand()%(To-From+1)+From;
	 return randNum;
}
int readNumber(string messege)
{
	   int Number;
	   cout<<messege<<endl;
	   cin>>Number;
	   return Number;
}	   
int readUserAnswer()
{
	int answer=0;
	cin>>answer;
	return answer;
}	
string questionsLevelName(enQuestionsLevel QuestionsLevel)
{
	string arrLevels[4]={"Easy","Med","Hard","Mix"};
	return arrLevels[QuestionsLevel-1];
}
enQuestionsType choiceRandQuestionsType()	 
{
	 return (enQuestionsType)randomNumber(1,4);
}
string questionsTypeForm(enQuestionsType QuestionsType)
{
   
   string arrForms[5]={" +"," -"," *"," /","Mix"};
   return arrForms[QuestionsType-1];
   
}
int findRandNumberForQuestion(const stQuestionInfo& QuestionInfo)
{
	switch(QuestionInfo.QuestionsLevel)
	{
		case enQuestionsLevel::easy:
		    return randomNumber(1,10);
		case enQuestionsLevel::med:
		    return randomNumber(10,50);
		case enQuestionsLevel::hard:
		    return randomNumber(50,100);
		case enQuestionsLevel::mix:
		   return randomNumber(1,100);
	}
}		               
int findCorrectAnswer(const stQuestionInfo& QuestionInfo)
{
     enQuestionsType opType;
     if(QuestionInfo.QuestionsType==enQuestionsType::Mix)
        opType=QuestionInfo.currentType;
     else
         opType=QuestionInfo.QuestionsType;    
     switch(opType)
	    {
	            case enQuestionsType::add:
	                    return QuestionInfo.number1+QuestionInfo.number2;
	            case enQuestionsType::sub:
	                    return QuestionInfo.number1-QuestionInfo.number2;
	            case  enQuestionsType::mul:
	                   return QuestionInfo.number1*QuestionInfo.number2;
	            case enQuestionsType::div:
	                   return QuestionInfo.number1/QuestionInfo.number2;
                 
        }                
         
     
}	 
bool IsAnswerCorrect(const stQuestionInfo& QuestionInfo)      
{
	if(QuestionInfo.userAnswer==QuestionInfo.correctAnswer)
	   return 1;
	else
	   return 0;
}	                                 
void printResult(const stQuestionInfo& QuestionInfo)
{
    bool IfAnswerIsCorrect=IsAnswerCorrect(QuestionInfo);
	switch(IfAnswerIsCorrect)
	  {
	  	 case 1:
	                cout<<"Right answer : - )"<<endl;
	       break;         
	       case 0: 
       	{
	            cout<<"wrong answer : - (" <<endl;
	            cout<<"the right answer is "<<QuestionInfo.correctAnswer<<endl<<endl<<endl;
       	}
       	break;
      }     
}	 
void setWinnerScreenColor(stQuestionInfo QuestionInfo)
{
	if(IsAnswerCorrect(QuestionInfo)==1)
	   system("color 2F");
   else
      system("color 4F");
}
void resetSreenColor()      
{
        system("cls");
	    system("color 0F");
}
stMathGameResults fillMathGameResults(short numQuestions,short RAns,short WrAns,const stQuestionInfo& QuestionInfo)
{
   stMathGameResults MathGameResults;
   MathGameResults.numberOfQuestions=numQuestions;
   MathGameResults.questionsLevel=questionsLevelName(QuestionInfo.QuestionsLevel);
   MathGameResults.questionsType=questionsTypeForm(QuestionInfo.QuestionsType);
   MathGameResults.rightAnswers=RAns;
   MathGameResults.wrongAnswers=WrAns;
   return MathGameResults;
} 
stMathGameResults playGame(short numQuestions,short RAns,short WrAns,stQuestionInfo QuestionInfo)
{
          stMathGameResults MathGameResults;
          RAns=0,WrAns=0;
	      numQuestions=readNumber("How many Questions do you want to answer  ?");
	      QuestionInfo.QuestionsLevel=enQuestionsLevel(readNumber("Enter Questions level [1]   Easy,   [2]   Med,  [3]   Hard,   [4]  Mix  ?"));
	      QuestionInfo.QuestionsType=enQuestionsType(readNumber("Enter Questions Type [1]  Add, [2]  Sub ,[3]  Mul,[4]  Div  ,[5] Mix  ?"));
          for(int numberOfQuestion=1;numberOfQuestion<=numQuestions;numberOfQuestion++)
	       {
	            cout<<"Question ["<<numberOfQuestion<<"/"<<numQuestions<<"]\n\n";
                QuestionInfo.number1=findRandNumberForQuestion(QuestionInfo);
                cout<<QuestionInfo.number1<<endl;
                QuestionInfo.number2=findRandNumberForQuestion(QuestionInfo);
                cout<<QuestionInfo.number2<<" ";
                if(QuestionInfo.QuestionsType==enQuestionsType::Mix)
                {
                   QuestionInfo.currentType=choiceRandQuestionsType();
                   string OpForm=questionsTypeForm(QuestionInfo.currentType);
                   cout<<OpForm;
                }
                else
                {
                    QuestionInfo.QuestionsTypeForm= questionsTypeForm(QuestionInfo.QuestionsType);
                    cout<<QuestionInfo.QuestionsTypeForm;
                }
                cout<<"\n________________\n";
                QuestionInfo.userAnswer=readUserAnswer();
                QuestionInfo.correctAnswer=findCorrectAnswer(QuestionInfo);
                if(IsAnswerCorrect(QuestionInfo))
                    RAns++;
                else
                    WrAns++;    
                setWinnerScreenColor(QuestionInfo);
                printResult(QuestionInfo);
                   
           }     
          return fillMathGameResults(numQuestions,RAns,WrAns,QuestionInfo);
}
void printMathGameResults(const stMathGameResults& MathGameResults)
{
   cout<<"Number of Questions: "<<MathGameResults.numberOfQuestions<<endl;
   cout<<"Questions level    : "<<MathGameResults.questionsLevel<<endl;
   cout<<"OpType             : "<<MathGameResults.questionsType<<endl;
   cout<<"Number of Right Answers:"<<MathGameResults.rightAnswers<<endl;
   cout<<"Number of wrong Answers:"<<MathGameResults.wrongAnswers<<endl;
   cout<<"\n__________________________________________\n\n";
}
bool IsPlayerPassOrFail(stMathGameResults MathGameResults)
{
     if(MathGameResults.rightAnswers>=MathGameResults.wrongAnswers)
         return 1;
     else
         return 0;
}
void showFinalGameResults(stMathGameResults MathGameResults)
{
   cout<<"____________________________________________\n\n";
   cout<<" Final Results is ";
   if(IsPlayerPassOrFail(MathGameResults))
      cout<<"Pass :-)\n";
   else
      cout<<"Fail :-(\n\n";
   cout<<"____________________________________________\n\n";   
}                          
void startGame()
{
    stQuestionInfo QuestionInfo;
    stMathGameResults MathGameResults;
    short numQuestions,RAns,WrAns;
    char playAgain='y';
    do{
           resetSreenColor();
           MathGameResults=playGame(numQuestions,RAns,WrAns,QuestionInfo);
           showFinalGameResults(MathGameResults);
           printMathGameResults(MathGameResults);
           cout<<"Do you want to play again? Y/N?";
           cin>>playAgain;
      }while((playAgain=='y') || (playAgain=='Y'));  
}
int main()
{
    srand((unsigned)time(NULL));
    startGame();
    return 0;
}            
           
           
                
 