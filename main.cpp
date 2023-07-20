#include<iostream>
#include<string>
#include<stdlib.h>
//#include<conio.h>
//#include<windows.h>
#include <thread>
#include <chrono>
using namespace std;


//stores the position and symbol of the players
struct Coordinates{
    int position;
    char symbol;
//initialize to 0 and ' '
    Coordinates(){
        position = 0;
        symbol = ' ';
    }
};

class Player;
class Game{
    static Coordinates c[9];
    //store how many time players position was taken as input
    static int play_count;
    public:
    void set_comp_pos(Player&);
    void check_comp_pos(Player&);
    void display() const;
    void input(Player&, Player&);
    void displayGraphics(Player&, Player&);
    void checkWinner(Player&);
};

class Player{
    string name;
    char symbol;
    bool is_my_turn,is_winner,is_comp;
    static int count;
    static char sym;
    friend class Game;
    public:
    Player(){
        is_winner = false;
        is_comp = false;
        is_my_turn = true;
    }
    void input_player_detail();
    void  make_comp(){
        is_comp = !is_comp;
    }
};

void Game::display() const{
    system("clear");
    cout<<"This is Tic Tac Toe By Alisha Khatri\n";
    system("clear");
    
    // sleep for a second
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    system("clear");
}

void Game::displayGraphics(Player& p1,Player& p2){
  //take position for maximum of 9 times.
    for(int i = 0 ; i < 9 ; i++)
    {
        play_count++;
    //select the current player 
    Player& curr_player = p1.is_my_turn?p1:p2;
    Player& next_player = p1.is_my_turn?p2:p1;

    //display's game board
    cout<<c[0].symbol<<'\t'<<"|"<<c[1].symbol<<'\t'<<"|"<<c[2].symbol<<'\n';
    cout<<"\t"<<"|"<<"\t"<<"|"<<'\n';
    cout<<"-----------------------\n";
    cout<<c[3].symbol<<'\t'<<"|"<<c[4].symbol<<'\t'<<"|"<<c[5].symbol<<'\n';
    cout<<"\t"<<"|"<<"\t"<<"|"<<'\n';
    cout<<"-----------------------\n";
    cout<<c[6].symbol<<'\t'<<"|"<<c[7].symbol<<'\t'<<"|"<<c[8].symbol<<'\n';
    cout<<"\t"<<"|"<<"\t"<<"|"<<'\n';

//Take input for position 
    if(!curr_player.is_comp){
    cout<<curr_player.name<<" ( "<<(curr_player.symbol)<<" )"<<" Choose position (1-9)"<<'\n';
    int choice;
    cin>>choice;
    //check for range input by the user
    while(choice<1 || choice>9){
        cout<<"OOps !Choose in between 1-9\n";
        cin>>choice;
    }
    //check if input position is already occupied
    while(c[choice - 1].symbol == curr_player.symbol||c[choice - 1].symbol == next_player.symbol){
      cout<<"OOPs! Position "<<choice<<" is already Occupied. Select another Position\n";
      cin>>choice;
      while(choice<1 || choice>9){
        cout<<"OOps !Choose in between 1-9\n";
        cin>>choice;
       }
     }
    //assigning symbol to the designated position
    c[choice-1].symbol = curr_player.symbol;
    }
    //Setting up computer's Move
    else{
        set_comp_pos(curr_player);
    }
    //Check for winner
    checkWinner(curr_player);
    system("clear");

    if(curr_player.is_winner){
        if(curr_player.is_comp){
            cout<<"Computer won\n";
        }
        else{
          //display positions after victory
            cout<<curr_player.name<<" is winner\n";
        }
        cout<<c[0].symbol<<'\t'<<"|"<<c[1].symbol<<'\t'<<"|"<<c[2].symbol<<'\n';
        cout<<"\t"<<"|"<<"\t"<<"|"<<'\n';
        cout<<"-----------------------\n";
        cout<<c[3].symbol<<'\t'<<"|"<<c[4].symbol<<'\t'<<"|"<<c[5].symbol<<'\n';
        cout<<"\t"<<"|"<<"\t"<<"|"<<'\n';
        cout<<"-----------------------\n";
        cout<<c[6].symbol<<'\t'<<"|"<<c[7].symbol<<'\t'<<"|"<<c[8].symbol<<'\n';
        cout<<"\t"<<"|"<<"\t"<<"|"<<'\n';
        break;
    }
    if(play_count == 9){
        if(!curr_player.is_winner){
          //display position after game draws
            cout<<"Game drawn\n";
            cout<<c[0].symbol<<'\t'<<"|"<<c[1].symbol<<'\t'<<"|"<<c[2].symbol<<'\n';
            cout<<"\t"<<"|"<<"\t"<<"|"<<'\n';
            cout<<"-----------------------\n";
            cout<<c[3].symbol<<'\t'<<"|"<<c[4].symbol<<'\t'<<"|"<<c[5].symbol<<'\n';
            cout<<"\t"<<"|"<<"\t"<<"|"<<'\n';
            cout<<"-----------------------\n";
            cout<<c[6].symbol<<'\t'<<"|"<<c[7].symbol<<'\t'<<"|"<<c[8].symbol<<'\n';
            cout<<"\t"<<"|"<<"\t"<<"|"<<'\n';

            break;
        }
    }

   //setting up the turn for player
    curr_player.is_my_turn = false;
    next_player.is_my_turn = true;
   }
}

//Find the best move for Computer.
void Game::set_comp_pos(Player& P){
  cout<<"Computers Turn...\n";
  cout<<"Thinking...\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));

//place computers symbol in between opponent's symbol (X   O   X)
    if((c[0].symbol ==' ' || c[1].symbol == ' ' || c[2].symbol == ' ') && (((c[0].symbol == c[2].symbol) && c[0].symbol != ' ') || ((c[0].symbol == c[1].symbol) && (c[0].symbol != ' ')) || ((c[1].symbol == c[2].symbol) && c[1].symbol!=' '))){
       if(c[0].symbol == ' '){
          if(c[1].symbol != P.symbol){
            //check for move which lead to victory
            check_comp_pos(P);
          }
          else{
              c[0].symbol = P.symbol;
          }
       }
        else if(c[1].symbol == ' '){
            if(c[0].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
              c[1].symbol = P.symbol;
          }
        }
        else if(c[2].symbol == ' '){
            if(c[0].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
              c[2].symbol = P.symbol;
          }
       }
    }
   else if((c[3].symbol ==' ' || c[4].symbol ==' ' || c[5].symbol == ' ') && (((c[3].symbol == c[5].symbol) && c[3].symbol !=' ') || ((c[3].symbol == c[4].symbol) && (c[3].symbol !=' '))|| ((c[4].symbol == c[5].symbol) && c[4].symbol !=' '))){
     if(c[3].symbol == ' '){
         if(c[4].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
           c[3].symbol = P.symbol; 
          }
     }

      else if(c[4].symbol == ' '){
            if(c[3].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
           c[4].symbol = P.symbol; 
          }
        }

      else if(c[5].symbol == ' '){
          if(c[3].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
           c[5].symbol = P.symbol; 
          }
        }
   }
   else if((c[6].symbol ==' ' || c[7].symbol ==' '|| c[8].symbol == ' ') && (((c[6].symbol == c[8].symbol) && c[6].symbol !=' ') || ((c[6].symbol == c[7].symbol) && (c[6].symbol !=' ')) || ((c[7].symbol == c[8].symbol) && c[7].symbol !=' '))){
       if(c[6].symbol == ' '){
           if(c[7].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
           c[6].symbol = P.symbol; 
          }
       }

        else if(c[7].symbol == ' '){
            if(c[6].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
           c[7].symbol = P.symbol; 
          }
        }

        else if(c[8].symbol == ' '){
            if(c[7].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
        c[8].symbol = P.symbol; 
          }
        }
   }
   else if((c[0].symbol ==' ' || c[3].symbol==' '|| c[6].symbol == ' ') && (((c[0].symbol==c[6].symbol) && c[0].symbol !=' ') ||  ((c[0].symbol == c[3].symbol) && (c[0].symbol !=' ')) || ((c[3].symbol == c[6].symbol) && c[3].symbol != ' '))){
       if(c[0].symbol == ' '){
           if(c[3].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
              c[0].symbol = P.symbol;
          }
       }

        else if(c[3].symbol == ' '){
            if(c[0].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
        c[3].symbol = P.symbol; 
          }
        }

    else if(c[6].symbol == ' '){
        if(c[0].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
        c[6].symbol = P.symbol; 
          }
       } 
   }
   else if((c[1].symbol ==' ' || c[4].symbol == ' '|| c[7].symbol == ' ') && (((c[1].symbol==c[7].symbol)&& c[1].symbol !=' ') ||  ((c[1].symbol == c[4].symbol)&&(c[1].symbol!=' ')) || ((c[4].symbol== c[7].symbol) && c[4].symbol !=' '))){
       if(c[1].symbol == ' '){
           if(c[4].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
        c[1].symbol = P.symbol; 
          }
       }

        else if(c[4].symbol == ' '){
            if(c[1].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
        c[4].symbol = P.symbol; 
          }
        }

        else if(c[7].symbol == ' '){
            if(c[1].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
        c[7].symbol = P.symbol; 
          }
        }
   }
   else if((c[2].symbol ==' ' || c[5].symbol == ' '|| c[8].symbol == ' ') && (((c[2].symbol==c[8].symbol)&&c[2].symbol !=' ') || ((c[2].symbol == c[5].symbol)&& (c[2].symbol !=' ')) || ((c[5].symbol== c[8].symbol) && c[5].symbol !=' '))){
       if(c[2].symbol == ' '){
           if(c[5].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
        c[2].symbol = P.symbol; 
          }
       }

        else if(c[5].symbol == ' '){
            if(c[2].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
        c[5].symbol = P.symbol; 
          }
        }

        else if(c[8].symbol == ' '){
            if(c[2].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
        c[8].symbol = P.symbol; 
          }
        }
   }
   else if((c[0].symbol ==' ' || c[4].symbol ==' '|| c[8].symbol == ' ') && (((c[0].symbol == c[8].symbol) && c[0].symbol !=' ') || ((c[0].symbol == c[4].symbol)&&(c[0].symbol!=' ')) || ((c[4].symbol== c[8].symbol) && c[4].symbol !=' '))){
       if(c[0].symbol == ' '){
           if(c[4].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
              c[0].symbol = P.symbol;
          }
       }

        else if(c[4].symbol == ' '){
            if(c[0].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
        c[4].symbol = P.symbol; 
          }
        }

        else if(c[8].symbol == ' '){
            if(c[0].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
        c[8].symbol = P.symbol; 
          }
        }
   }
   else if((c[2].symbol ==' ' || c[4].symbol==' ' || c[6].symbol==' ') && (((c[2].symbol == c[6].symbol) && c[2].symbol !=' ') || ((c[2].symbol == c[4].symbol)&& (c[2].symbol !=' ')) || ((c[4].symbol == c[6].symbol) && c[4].symbol!=' '))){
       if(c[2].symbol == ' '){
           if(c[4].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
        c[2].symbol = P.symbol; 
          }
       }
        else if(c[4].symbol == ' '){
            if(c[2].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
        c[4].symbol = P.symbol; 
          }
        }

        else if(c[6].symbol == ' '){
            if(c[2].symbol != P.symbol){
            check_comp_pos(P);
          }
          else{
        c[6].symbol = P.symbol; 
          }
        }
     }
     //move against corner input by opponent
     else if((c[0].symbol != ' ' && c[4].symbol == ' ' || c[6].symbol != ' ' && c[4].symbol == ' ')){
       if(c[0].symbol != ' ' && c[4].symbol == ' '){
         c[4].symbol = P.symbol;
       }
       
       else if(c[6].symbol != ' ' && c[4].symbol == ' '){
         c[4].symbol = P.symbol;
       }
       
     }
     else if((c[0].symbol != ' ' && c[4].symbol != ' ' && c[3].symbol == ' '|| c[6].symbol != ' ' && c[4].symbol != ' ' && c[3].symbol ==' ')){
       if(c[0].symbol != ' ' && c[4].symbol != ' '){
         c[3].symbol = P.symbol;
       }
       
       else if(c[6].symbol != ' ' && c[4].symbol != ' '){
         c[3].symbol = P.symbol;
       }
       
     }
   else{
       
       //target bottom left corner
        if(c[6].symbol == ' ' && c[4].symbol !=' '){
            c[6].symbol = P.symbol;
       }
       //target top right corner
       else if(c[2].symbol == ' '&& c[4].symbol !=' '){
           c[2].symbol = P.symbol;
       }
       //top left
       else if(c[0].symbol == ' '&& c[4].symbol !=' '){
           c[0].symbol = P.symbol;
       }
       //Always target the center first
       else if(c[4].symbol == ' '){
           c[4].symbol = P.symbol;
       }

       else if(c[6].symbol !=' ' && c[6].symbol != P.symbol && c[7].symbol == ' '){
         c[7].symbol = P.symbol;
       }

       else if(c[1].symbol !=' ' && c[1].symbol != P.symbol && c[2].symbol == ' '){
         c[2].symbol = P.symbol;
       }
       //if no condition satisfies randomly choose a empty position
       else{
           for(int i = 8 ; i >= 0 ; i--){
               if(c[i].symbol ==' '){
                   c[i].symbol = P.symbol;
                   break;
               }
           }
       }
  }
}

void Game::check_comp_pos(Player& P){
  if((c[2].symbol ==' ' || c[4].symbol==' ' || c[6].symbol==' ') && (((c[2].symbol == c[6].symbol) && c[2].symbol !=' ') || ((c[2].symbol == c[4].symbol)&& (c[2].symbol !=' ')) || ((c[4].symbol == c[6].symbol) && c[4].symbol!=' '))){
       if(c[2].symbol == ' ')
        c[2].symbol = P.symbol; 

        else if(c[4].symbol == ' ')
        c[4].symbol = P.symbol; 

        else if(c[6].symbol == ' ')
        c[6].symbol = P.symbol; 
   }
   else if((c[0].symbol ==' ' || c[4].symbol ==' '|| c[8].symbol == ' ') && (((c[0].symbol == c[8].symbol) && c[0].symbol !=' ') || ((c[0].symbol == c[4].symbol)&&(c[0].symbol!=' ')) || ((c[4].symbol== c[8].symbol) && c[4].symbol !=' '))){
       if(c[0].symbol == ' ')
        c[0].symbol = P.symbol; 

        else if(c[4].symbol == ' ')
        c[4].symbol = P.symbol; 

        else if(c[8].symbol == ' ')
        c[8].symbol = P.symbol; 
   }
   else if((c[2].symbol ==' ' || c[5].symbol == ' '|| c[8].symbol == ' ') && (((c[2].symbol==c[8].symbol)&&c[2].symbol !=' ') || ((c[2].symbol == c[5].symbol)&& (c[2].symbol !=' ')) || ((c[5].symbol== c[8].symbol) && c[5].symbol !=' '))){
       if(c[2].symbol == ' ')
        c[2].symbol = P.symbol; 

        else if(c[5].symbol == ' ')
        c[5].symbol = P.symbol; 

        else if(c[8].symbol == ' ')
        c[8].symbol = P.symbol; 
   }
   else if((c[1].symbol ==' ' || c[4].symbol == ' '|| c[7].symbol == ' ') && (((c[1].symbol==c[7].symbol)&& c[1].symbol !=' ') ||  ((c[1].symbol == c[4].symbol)&&(c[1].symbol!=' ')) || ((c[4].symbol== c[7].symbol) && c[4].symbol !=' '))){
       if(c[1].symbol == ' ')
        c[1].symbol = P.symbol; 

        else if(c[4].symbol == ' ')
        c[4].symbol = P.symbol; 

        else if(c[7].symbol == ' ')
        c[7].symbol = P.symbol; 
   }
   else if((c[0].symbol ==' ' || c[3].symbol==' '|| c[6].symbol == ' ') && (((c[0].symbol==c[6].symbol) && c[0].symbol !=' ') ||  ((c[0].symbol == c[3].symbol) && (c[0].symbol !=' ')) || ((c[3].symbol == c[6].symbol) && c[3].symbol != ' '))){
       if(c[0].symbol == ' ')
        c[0].symbol = P.symbol; 

        else if(c[3].symbol == ' ')
        c[3].symbol = P.symbol; 

        else if(c[6].symbol == ' ')
        c[6].symbol = P.symbol; 
   }
   else if((c[6].symbol ==' ' || c[7].symbol ==' '|| c[8].symbol == ' ') && (((c[6].symbol == c[8].symbol) && c[6].symbol !=' ') || ((c[6].symbol == c[7].symbol) && (c[6].symbol !=' ')) || ((c[7].symbol == c[8].symbol) && c[7].symbol !=' '))){
       if(c[6].symbol == ' ')
        c[6].symbol = P.symbol; 

        else if(c[7].symbol == ' ')
        c[7].symbol = P.symbol; 

        else if(c[8].symbol == ' ')
        c[8].symbol = P.symbol; 
   }
   else if((c[3].symbol ==' ' || c[4].symbol ==' ' || c[5].symbol == ' ') && (((c[3].symbol == c[5].symbol) && c[3].symbol !=' ') || ((c[3].symbol == c[4].symbol) && (c[3].symbol !=' '))|| ((c[4].symbol == c[5].symbol) && c[4].symbol !=' '))){
     if(c[3].symbol == ' ')
        c[3].symbol = P.symbol; 

        else if(c[4].symbol == ' ')
        c[4].symbol = P.symbol; 

        else if(c[5].symbol == ' ')
        c[5].symbol = P.symbol; 
   }
    else if((c[0].symbol ==' ' || c[1].symbol == ' ' || c[2].symbol == ' ') && (((c[0].symbol == c[2].symbol) && c[0].symbol != ' ') || ((c[0].symbol == c[1].symbol) && (c[0].symbol != ' ')) || ((c[1].symbol == c[2].symbol)&&c[1].symbol!=' '))){
       if(c[0].symbol == ' '){
          c[0].symbol = P.symbol;
       }

        else if(c[1].symbol == ' '){
              c[1].symbol = P.symbol;
          
        }
        else if(c[2].symbol == ' '){
              c[2].symbol = P.symbol;
        }
   }
       
}

//check if the winner already exist or not
void Game::checkWinner(Player& P){
 
   if(c[0].symbol !=' ' && c[0].symbol == c[1].symbol && c[1].symbol == c[2].symbol){
       P.is_winner = true;
   }
   else if(c[3].symbol !=' ' && c[3].symbol == c[4].symbol && c[4].symbol == c[5].symbol){
     P.is_winner = true;
   }
   else if(c[6].symbol !=' ' && c[6].symbol == c[7].symbol && c[7].symbol == c[8].symbol){
       P.is_winner = true;
   }
   else if(c[0].symbol !=' ' && c[0].symbol == c[3].symbol && c[3].symbol == c[6].symbol){
       P.is_winner = true;
   }
   else if(c[1].symbol !=' ' && c[1].symbol == c[4].symbol && c[4].symbol== c[7].symbol){
       P.is_winner = true;
   }
   else if(c[2].symbol !=' ' && c[2].symbol == c[5].symbol && c[5].symbol== c[8].symbol){
       P.is_winner = true;
   }
   else if(c[0].symbol !=' ' && c[0].symbol == c[4].symbol && c[4].symbol== c[8].symbol){
       P.is_winner = true;
   }
   else if(c[2].symbol !=' ' && c[2].symbol == c[4].symbol && c[4].symbol == c[6].symbol){
       P.is_winner = true;
   }
}

void Player::input_player_detail(){
  //input only if player is not a computer
if(!is_comp){
  //no need to ask for the symbol of the second player
 if(count == 0)
 {
    cout<<"Enter Player1 Name\n";
    //cin doesn't take characters after space
    cin>>name;
      cout<<"Choose a symbol 'X' or 'O',X will be the first Player"<<'\n';
      char ch;
      std::cin >> ch;
    if(ch == 'X'||ch == 'x')
    {
        symbol= 'X';
        cout<<"X selected as symbol for "<<this->name<<'\n';
        count++;
        sym = symbol;
    }
    else if(ch == 'O'||ch =='o')
    {
        symbol= 'O';
        cout<<"O selected as symbol for "<<this->name<<'\n';
        count++;
        sym = symbol;

        is_my_turn = !is_my_turn;

    }
    //Automatically select 'X' for invalid selection by user
    else{
        cout<<"Invalid Input\n";
        cout<<"X selected as symbol for "<<this->name<<" by default"<<'\n';
        //input count increased
        count++;
        symbol= 'X';
        sym = symbol;
       }

   }

//only take the players detail if game mode is multiplayer
    else
    {
        cout<<"Enter Player2 Name\n";
        cin>>name;
        if(sym == 'X')
        {
         symbol = 'O';
         cout<<"O is the symbol for "<<this->name<<'\n';
         //Not your turn if you choose 'O';
         is_my_turn = !is_my_turn;
        }

        else
        {
            symbol = 'X';
            cout<<"X is the symbol for "<<this->name<<'\n';
        }
    }
 
    
//Sleep(1000);
system("clear");
 }
 //automatically select symbol for second player
 else
 {
     if(sym == 'X'){
         symbol = 'O';
         cout<<"O is the symbol for Computer\n";

          is_my_turn = !is_my_turn;
        }

        else{
            symbol = 'X';
            cout<<"X is the symbol for Computer\n";
        }
   }
//Sleep(1000);
system("clear");
}

void Game::input(Player& p1, Player& p2){
p1.input_player_detail();
p2.input_player_detail();
system("clear");
displayGraphics(p1,p2);
}

int Player::count;
char Player::sym;
Coordinates Game::c[9];
int Game::play_count;


int main(){
  Game G;
  G.display();
  int choice;
  cout<<"Select Game Mode\n";
  cout<<"1.Single Player(vs Com)\n";
  cout<<"2.Multiplayer\n";
  cin>>choice;
    //Force the choice among 1 and 2
  while(choice!=1 && choice!=2){
    cout<<"Choose In Between 1 and 2\n";
    cin>>choice;
  }
  Player p1,p2;
  if(choice == 1){
      //one player is computer
    p2.make_comp();
  }
  system("clear");
  G.input(p1,p2);
return 0;
}
