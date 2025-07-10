#include <iostream>
#include<string>
#include<cstdlib>

using namespace std;
enum enGameChoice{Paper=1,stone=2,scissor=3};
enum enWinner{Player1=1,Computer=2,Draw=3};
struct stRoundInfo{
short RoundNumber;
enGameChoice Player1Choice;
enGameChoice ComputerChoice;
enWinner Winner;
string WinnerName;
};
struct stGameResult{
short TotalRounds;
short Player1WinTimes;
short ComputerWinTimes;
short DrawTimes;
enWinner Winner;
string WinnerName;
};
short GetPositiveNum(string Msg)
{
  short Num=0;
  do{
    cout<<Msg<<endl;
    cin>>Num;
  }while(Num<0);
  return Num;
}
enGameChoice ReadPlayer1Choice()
{
  short choice=0;
  do{
    cout << "\033[34m"; // Blue color
    cout<<"\033[2m";
    cout<<"● Please enter your choice:"<<endl;
    cout << "\033[0m";
    cout << "\033[1m";
    cout << "\033[35m";
    cout<<"● [1]Paper 📄,";
    cout << "\033[30m";
    cout<<"[2]Stone🪨 ,";
    cout<<"\033[36m";
    cout<<"[3]Scissor✂️ :\t";
    cout << "\033[0m";
    cin>>choice;
  }while(choice<1||choice>3);
  return (enGameChoice)choice;
}
int RandNum(int from,int to)
{
  return rand()%(to-from+1)+from;
}
enGameChoice GetComputerChoice()
{
  return (enGameChoice)RandNum(1,3);
}
enWinner WhoWinTheRound(stRoundInfo RoundInfo)
{
  if(RoundInfo.Player1Choice==RoundInfo.ComputerChoice)
    return enWinner::Draw;
  switch(RoundInfo.Player1Choice)
    {
      case(enGameChoice::Paper):
      return(RoundInfo.ComputerChoice==enGameChoice::scissor)?enWinner::Computer:enWinner::Player1;
      case(enGameChoice::stone):
        return(RoundInfo.ComputerChoice==enGameChoice::Paper)?enWinner::Computer:enWinner::Player1;
      case(enGameChoice::scissor):
      return(RoundInfo.ComputerChoice==enGameChoice::stone)?enWinner::Computer:enWinner::Player1;
    }
}
string WinnerName(enWinner Winner)
{
  string WinnerNames[3]={
  "Player1 😎","Computer🙁","Draw🫤"};
  return WinnerNames[Winner-1];
  }
string GameChoice(enGameChoice Choice)
{
  string GameChoices[3]={
  "Paper📄","Stone🪨","Scissor✂️"};
  return GameChoices[Choice-1];
  }
enWinner GameWinner(short Player1WinTimes,short ComputerWinTimes)
{if (Player1WinTimes>ComputerWinTimes)
  return enWinner::Player1;
 else if(Player1WinTimes<ComputerWinTimes)
   return enWinner::Computer;
 else
   return enWinner::Draw;
}
      
void PrintRoundResult(stRoundInfo RoundInfo)
{cout<<endl;
 cout<<"\033[3m";
  cout << "\033[21m";
  cout<<"★ Round["<<RoundInfo.RoundNumber<<"]\n";
  cout<<"● Player1 Choice:\t"<<GameChoice(RoundInfo.Player1Choice)<<endl;
  cout<<"● Computer Choice:\t"<<GameChoice(RoundInfo.ComputerChoice)<<endl<<endl;
  cout<<"\033[1m";
  cout<<"♣︎ Winner ♣︎ :\t"<<WinnerName(RoundInfo.Winner)<<endl<<endl;
  cout << "\033[0m";
}
void PrintGameResult(stGameResult GameResult)
{cout << "\033[36m";
    cout<<"\033[1m";
 
  cout<<"------------------\n";
  cout<<" ●● GameOver ●●\n";
 cout<<"------------------\n";
 
 cout<<"\033[0m";
 cout << "\033[96m";
 cout<<"● Total Rounds: \t \t"<<GameResult.TotalRounds<<endl;
  cout<<"● Player1 Win Times:\t"<<GameResult.Player1WinTimes<<endl;
  cout<<"● Computer Win Times:\t"<<GameResult.ComputerWinTimes<<endl;
  cout<<"● Draw Times:\t\t\t"<<GameResult.DrawTimes<<endl;
 cout<<endl;
 cout<<"\033[1m";
 cout << "\033[36m";
 cout<<"------------------------\n";
  cout<<"●● Winner:"<<GameResult.WinnerName<<" ●●"<<endl;
 cout<<"------------------------\n";
 cout << "\033[0m";
  
}
stGameResult PlayGame(short HowManyRounds)
{
  HowManyRounds=GetPositiveNum("How Many Rounds Do You Want To Play?\n");
  short Player1WinTimes=0,ComputerWinTimes=0,DrawTimes=0;
  stRoundInfo RoundInfo;
  for(short Round=1;Round<=HowManyRounds;Round++)
    {
      RoundInfo.RoundNumber=Round;
      RoundInfo.Player1Choice=ReadPlayer1Choice();
      RoundInfo.ComputerChoice=GetComputerChoice();
      RoundInfo.Winner=WhoWinTheRound(RoundInfo);
      RoundInfo.WinnerName=WinnerName(RoundInfo.Winner);
      if(RoundInfo.Winner==enWinner::Player1)
      {Player1WinTimes++;
       cout << "\033[32m";}
else if(RoundInfo.Winner==enWinner::Computer)
  {ComputerWinTimes++;
   cout << "\033[31m";
   }
else {DrawTimes++;
      cout << "\033[33m"; }
  PrintRoundResult(RoundInfo);
  cout << "\033[0m"; }
    
  return{HowManyRounds,Player1WinTimes,ComputerWinTimes,DrawTimes,GameWinner(Player1WinTimes,ComputerWinTimes),WinnerName(GameWinner(Player1WinTimes,ComputerWinTimes))};
}
void    StartGame()
{
    char PlayAgain = 'Y';
  short Num=1;

    do
    {
        (void)system("clear");  
     stGameResult GameResult=  PlayGame(Num);
      PrintGameResult(GameResult);
        cout<<"\033[3m";
      
      cout << "\033[0m";
        cout << "\nDo you want to play again? (Y/N): ";
        cin >> PlayAgain;
      

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
  srand(unsigned(time(NULL)));
    StartGame();
  
    return 0;
}