#include<fstream.h>
#include<iostream.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<stdio.h>
#include<graphics.h>


short int worstcase[9][9]={0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,3,0,8,5,
    0,0,1,0,2,0,0,0,0,
    0,0,0,5,0,7,0,0,0,
    0,0,4,0,0,0,1,0,0,
    0,9,0,0,0,0,0,0,0,
    5,0,0,0,0,0,0,7,3,
    0,0,2,0,1,0,0,0,0,
    0,0,0,0,4,0,0,0,9};
int found=0;

class sudoku
{
    short int grid[9][9]; //Stores the grid which is to be solved
    void getgrid();       //Gets user defined grid, displays error messages
    unsigned long iterations; //stores number of iterations performed to solve
    void write(); //writes object of 'sudoku' to file
    void resetgrid(); //sets all grid elements to '0'
    void checkentered(); //checks validity of user defined grid
    int checkgrid(int pos,int a);//returns '0' if second parameter (a) exists >2
    
    
public:
    
    void generate(); //generates and displays unsolved grid
    short int temp[9][9]; //stores solution
    int valid_entered;//in checkentered(), this is set according to grid
    void display_PLAY();//displays while being played
    
    int free(int row,int col)
    {
        return grid[row][col];
    }
    
    void display(); //displays iterations, solved grid
    int check(int pos,int a); //returns 1 if parameter 'a' can be inserted
    void display_grid();//displays unsolved grid
    int solve(int pos=0,int back=0,int gen_var=0);//solves, returns 0 if iterations
    //exceed given value while generating to preserve time
    void getgrid(int def);//gets grid according to user
    int play;
    sudoku();
};

//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//
sudoku::sudoku()
{
    for(int i=0;i<9;++i)
        for(int j=0;j<9;++j)
        {
            temp[i][j]=0;
            grid[i][j]=0;
        }
    valid_entered=1;
    iterations=0;
    play=0;
}

//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//

void sudoku::resetgrid()
{
    for(int i=0;i<9;++i)
        for(int j=0;j<9;++j)
        {
            grid[i][j]=0;
            temp[i][j]=0;
        }
}
//------------------------------------------------------------------------------------//
void sudoku::display_PLAY()
{
    for(int i=0;i<9;++i)
    {
        cout<<"\t\t\t";
        for(int j=0;j<9;++j)
            if(temp[i][j])
                cout<<temp[i][j]<<" ";
            else
                cout<<"* ";
        cout<<"\n";
    }
    cout<<"\nPress ESC to exit, SPACE to select position, 'd' to display original";
}

//------------------------------------------------------------------------------------//

void sudoku::checkentered()
{
    
    for(int i=0;i<81;++i)
    {
        for(int j=1;j<10;++j)
        {
            if(!checkgrid(i,j))
            {
                valid_entered=0;
                return;
            }
        }
        
    }
    valid_entered=1;
    return;
}

//------------------------------------------------------------------------------------//

int sudoku::checkgrid(int pos,int a)
{
    int row=pos/9,col=pos%9;
    int count=0;
    for(int i=0;i<9;++i)
        if(grid[row][i]==a)
        {
            ++count;
            if(count>1)
                return 0;
        }
    
    count=0;
    
    for(i=0;i<9;++i)
        if(grid[i][col]==a)
        {
            ++count;
            if(count>1)
                return 0;
        }
    
    count=0;
    
    for(i=(row/3)*3;i<(row/3)*3+3;++i)
        for(int j=(col/3)*3;j<(col/3)*3+3;++j)
            if(grid[i][j]==a)
            {
                ++count;
                if(count>1)
                    return 0;
            }
    
    return 1;
}

//------------------------------------------------------------------------------------//

void sudoku::display_grid()
{
    cout<<endl<<"\t\t";
    for(int i=0;i<9;++i)
    {
        if(i%3==0)
        {
            for(int x=0;x<25;++x)
                cout<<"_";
            cout<<endl<<"\t\t";
        }
        
        for(int j=0;j<9;++j)
        {
            if(j%3==0) cout<<"| ";
            if(grid[i][j])
                cout<<grid[i][j]<<" ";
            else
                cout<<"* ";
            if(j==8)
                cout<<"| ";
        }
        cout<<endl<<"\t\t";
    }
    for(i=0;i<25;++i)
        cout<<"_";
    cout<<endl;
    
}

//------------------------------------------------------------------------------------//

void sudoku::generate()
{
    
    int puzzlesize;
    srand(time(NULL));
    puzzlesize=(rand())%4+17;
    
    for(int i=0;i<9;++i)
        for(int j=0;j<9;++j)
        {
            grid[i][j]=0;
            temp[i][j]=0;
        }
    
    for(i=0;i<puzzlesize;)
    {
        int x=rand()%81;
        int y=rand()%10;
        
        if(!free(x/9,x%9))
            if(check(x,y))
            {
                grid[x/9][x%9]=y;
                temp[x/9][x%9]=grid[x/9][x%9];
                ++i;
            }
        
        
    }
    if(!solve(0,0,1))
    {
        resetgrid();
        generate();
        return;
    }
    
}

//------------------------------------------------------------------------------------//

void sudoku::getgrid(int def)
{
    iterations=0;
    if(def==4)
        getgrid();
    
    else if(def==1)
    {
        for(int i=0;i<9;++i)
            for(int j=0;j<9;++j)
            {
                grid[i][j]=0;
                temp[i][j]=0;
            }
    }
    else if(def==2)
    {
        for(int i=0;i<9;++i)
            for(int j=0;j<9;++j)
            {
                grid[i][j]=worstcase[i][j];
                temp[i][j]=grid[i][j];
            }
    }
    else
    {
        cout<<"\nGenerating..\n";
        generate();
        cout<<"Generated\n\nPress any key to solve..";
        display_grid();
        getch();
        getch();
        cout<<endl;
    }
    
}

//------------------------------------------------------------------------------------//

void sudoku::getgrid()
{
    cout<<"\nEnter grid (enter out of bound element to exit):\n";
    int temp_store;
    for(int i=0;i<9;++i)
        for(int j=0;j<9;++j)
        {
            cin>>temp_store;
            if(temp_store>9||temp_store<1)
            {
                valid_entered=0;
                cout<<"Exiting..";
                getch();
                return;
            }
            grid[i][j]=temp_store;
            temp[i][j]=grid[i][j];
        }
    
    checkentered();
    if(!valid_entered)
    {
        cout<<"\nInvalid grid\n";
        return;
    }
    
    if(!solve())
        cout<<"\nNo solution\n";
}

//------------------------------------------------------------------------------------//

void sudoku::display()
{
    if(!play)
        cout<<"\nSolved in "<<iterations<<" iterations\n";
    cout<<endl<<"\t\t";
    for(int i=0;i<9;++i)
    {
        if(i%3==0)
        {
            for(int x=0;x<25;++x)
                cout<<"_";
            cout<<endl<<"\t\t";
        }
        
        for(int j=0;j<9;++j)
        {
            if(j%3==0)
                cout<<"| ";
            
            if(temp[i][j])
                cout<<temp[i][j]<<" ";
            else
                cout<<"* ";
            
            if(j==8)
                cout<<"| ";
        }
        cout<<endl<<"\t\t";
    }
    
    for(i=0;i<25;++i)
        cout<<"_";
    cout<<endl;
    
}

//------------------------------------------------------------------------------------//

int sudoku::check(int pos,int a)
{
    int row=pos/9,col=pos%9;
    
    for(int i=0;i<9;++i)
        if(temp[row][i]==a)
            return 0;
    
    for(i=0;i<9;++i)
        if(temp[i][col]==a)
            return 0;
    
    for(i=(row/3)*3;i<(row/3)*3+3;++i)
        for(int j=(col/3)*3;j<(col/3)*3+3;++j)
            if(temp[i][j]==a)
                return 0;
    
    return 1;
}

//------------------------------------------------------------------------------------//

int sudoku::solve(int pos,int back,int gen_var)
{
    
    
    for(unsigned long j=0;;++j)
    {
        
        int row=pos/9,col=pos%9;
        
        if(gen_var)
            if(j>500000)
                return 0;
        
        
        if(pos<0)
        {return 0;}
        if(row>=9)
        {
            if(iterations<j)
                iterations=j;
            return 1;
            
        }
        
        if(free(row,col)!=0)
        {
            if(back==0)
            {
                ++pos;
                back=0;
                continue;
            }
            else
            {
                --pos;
                back=1;
                continue;
            }
        }
        
        if(back==1)
        {
            int backup=temp[row][col];
            temp[row][col]=0;
            for(int i=backup+1;;++i)
            {
                if(i==10)
                {
                    temp[row][col]=0;
                    back=1;
                    --pos;
                    break;
                }
                
                if(check(pos,i))
                {
                    temp[row][col]=i;
                    ++pos;back=0;
                    break;
                }
                
            }
            continue;
        }
        
        if(temp[row][col]==0)
        {
            for(int i=1;i<=10;++i)
            {
                
                if(i==10)
                {
                    back=1;
                    --pos;
                    break;
                }
                
                if(check(pos,i))
                {
                    temp[row][col]=i;
                    ++pos;
                    back=0;
                    break;
                }
            }
            continue;
        }
        else
        {
            ++pos;
            back=0;
            continue;
        }
        
    }
    
}
//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//
void write(sudoku x)
{
    sudoku temp;
    ifstream fi("SudokuSave.dat",ios::in|ios::binary);
    ofstream fo("temp.dat",ios::out|ios::binary);
    for(;;)
    {
        fi.read((char*)&temp,sizeof(temp));
        if(fi.eof())
        {
            fo.write((char*)&x,sizeof(x));
            break;
        }
        fo.write((char*)&temp,sizeof(temp));
    }
    fi.close();
    fo.close();
    remove("SudokuSave.dat");
    rename("temp.dat","SudokuSave.dat");
}

//------------------------------------------------------------------------------------//

void compare(sudoku x)
{
    found=0;
    if(!x.valid_entered)
        return;
    sudoku temp;
    ifstream f("SudokuSave.dat",ios::in|ios::binary);
    if(!f.good())
    {
        cout<<"\nNo file created! Creating file..\n";
        ofstream f1("SudokuSave.dat",ios::out|ios::binary);
        f1.close();
        f.close();
        return;
    }
    
    for(;;)
    {
        f.read((char*)&temp,sizeof(temp));
        if(f.eof())
            break;
        
        for(int i=0;i<9;++i)
        {
            for(int j=0;j<9;++j)
            {
                if(x.free(i,j))
                    if(x.free(i,j)!=temp.temp[i][j])
                    {i=10;j=10;}
                
                if(i==8&&j==8)
                {
                    cout<<"\nSolved grid found in file\n";
                    found=1;
                    f.close();
                    temp.display();
                    return;
                }
                
            }
        }
        
    }
    
    cout<<"\nSolved grid not found in file\n";
    f.close();
    
}

//------------------------------------------------------------------------------------//

void read()
{
    sudoku x;
    ifstream f("SudokuSave.dat",ios::in|ios::binary);
    for(int i=0;;++i)
    {
        f.read((char*)&x,sizeof(x));
        if(f.eof())
            break;
        else
        {
            cout<<"\t\t\t  Grid "<<i+1<<endl<<endl;
            x.display();
        }
        cout<<"\nPress ESC to go back to menu, or any other key to display next grid..\n\n";
        if (getch()==27)
            break;
        
    }
    f.close();
}

//------------------------------------------------------------------------------------//

void read_grids()
{
    sudoku x;
    ifstream f("SudokuSave.dat",ios::in|ios::binary);
    for(int i=0;;++i)
    {
        f.read((char*)&x,sizeof(x));
        if(f.eof())
            break;
        else
        {
            cout<<"\t\t\t  Grid "<<i+1<<endl<<endl;
            x.display_grid();
        }
        cout<<"\nPress ESC to go back to menu, or any other key to display next grid..\n\n";
        if (getch()==27) //esc
            break;
        
    }
    f.close();
}

//------------------------------------------------------------------------------------//

void del()
{
    ofstream x("SudokuSave.dat",ios::out|ios::binary);
    x.close();
    cout<<"\nDeleted\n";
}

//------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------//

void getrowcol(int &a, int &b, sudoku S)
{
    int x=25,y=1;
    gotoxy(x,y);
    
    for(;;)
    {
        int ch=getch();
        if(ch=='d')
        {
            cout<<endl;
            clrscr();
            S.display_grid();
            getch();
            clrscr();
            S.display_PLAY();
        }
        if(ch==32)
        {
            b=(x-1-24)/2;
            a=y-1;
            gotoxy(1,10);
            return;
        }
        else if(ch==27)
        {
            a=-1;
            b=-1;
            gotoxy(1,10);
            return;
        }
        
        else if(ch==0)
        {
            ch+=getch();
            
            if(ch==80)
                y++;
            
            else if(ch==77)
                x+=2;
            
            else if(ch==72)
                --y;
            
            else if(ch==75)
                x-=2;
            
        }
        if(x<25)
            x=25;
        if(x>41)
            x=41;
        if(y>9)
            y=9;
        if(y<1)
            y=1;
        gotoxy(x,y);
    }
    
}

//------------------------------------------------------------------------------------//

void play()
{
    cleardevice();
    closegraph();
    clrscr();
    cout<<"\t\t\t\tIntructions\n";
    cout<<"\t\t\t\t-----------\n\n\n";
    
    cout<<"Sudoku is a logic-based placement puzzle.\n";
    cout<<"The aim is to enter a digit from 1-9 in each cell of a 9x9 grid made up of 3x3\nsubgrids. ";
    
    cout<<"\nEach row, column, and subgrid must contain only one instance of each numeral.\n";
    cout<<"\n\n       Game Instructions: use arrow keys to control cursor. Have fun!";
    cout<<"\n\nPress any key to start..";
    getch();
    clrscr();
    
    sudoku new_game;
    new_game.play=1;
    new_game.generate();
    
    for(int i=0;i<9;++i)
        for(int j=0;j<9;++j)
            new_game.temp[i][j]=new_game.free(i,j);
    
    int breaker,row,col;
    
    for(;;)
    {
        new_game.display_PLAY();
        gotoxy(row,col);
        getrowcol(row,col,new_game);
        
        if(row<0||col<0)
        {
            
            cout<<"\n\n\nExiting..\n";
            getch();
            return;
        }
        
        cout<<"\n\n\nEnter value to be inserted (enter out of bound value to solve grid):";
        cin>>breaker;
        
        
        clrscr();
        
        if(new_game.free(row,col))
        {
            clrscr();
            cout<<"\t\t\t\tInvalid position..";
            getch();
            clrscr();
            continue;
        }
        
        if(breaker<0||breaker>9)
        {
            cout<<"Solving...";
            getch();
            clrscr();
            cout<<"\t\t\t      Solved Grid";
            new_game.solve();
            new_game.display();
            getch();
            return;
        }
        if(breaker&&!new_game.check(row*9+col,breaker))
        {
            cout<<"\t\t\t\tInvalid insertion!";
            getch();
            clrscr();
            new_game.temp[row][col]=0;
        }
        else
            new_game.temp[row][col]=breaker;
        
        for(i=0;i<9;++i)
            for(int j=0;j<9;++j)
                if(!new_game.temp[i][j])
                    break;
                else if(i==8&&j==8)
                {
                    cout<<"\n\n\nCongratulations, you solved it!\n";
                    getch();
                    return;
                }
        
    }
    
    
}

//------------------------------------------------------------------------////

void menu()
{
    int a,a1;
    for(;;)
    {
        cleardevice();
        gotoxy(1,1);
        
        sudoku x;
        cout<<"\t\t\t\t  Menu\n\n\t\t\t\t1.Solve\n\t\t\t\t";
        cout<<"2.View\n\t\t\t\t3.Play\n\t\t\t\t";
        cout<<"4.Delete Data\n\t\t\t\t0.Exit\n\nOption:";
        cin>>a1;
        
        if(a1==0)
            break;
        
        if(a1>4||a1<0)
        {
            cout<<"Invalid Option!";
            getch();
            continue;
        }
        
        if(a1==1)
        {
            cout<<"\n\t\t\t\t  Solve\n\n\t\t\t\t1.Solve Blank Grid\n\t\t\t\t";
            cout<<"2.Solve Worst Case Grid (predefined)\n\t\t\t\t3.Generate Grid and Solve\n\t\t\t\t";
            cout<<"4.Enter Grid and Solve\n\t\t\t\t0.Go Back\n\nOption:";
            cin>>a;
            if(a>4||a<0)
            {
                cout<<"Invalid Option!";
                getch();
                cleardevice();
                gotoxy(1,1);
                continue;
            }
        }
        
        if(a1==2)
        {
            cout<<"\n\t\t\t\t  View\n\n\t\t\t\t1.View Solved Grids\n\t\t\t\t";
            cout<<"2.View Unsolved Grids\n\t\t\t\t0.Go Back\n\nOption:";
            cin>>a;
            if(a<0||a>2)
            {
                cout<<"Invalid Option!";
                getch();
                cleardevice();
                gotoxy(1,1);
                continue;
            }
            
            if(a)
                a+=4;
            
        }
        
        if(a1==3)
            a=8;
        
        if(a1==4)
            a=7;
        
        if(a==8)
        {
            play();
            initgraph(0,0,”c:/tc/bgi”);
            setbkcolor(BLUE);
            continue;
        }
        
        if(a==7)
        {
            del();
            getch();
            continue;
            
        }
        if(a==6)
        {
            read_grids();
            continue;
        }
        if(a==5)
        {
            read();
            continue;
        }
        if(a1<0||a1>4||a<0||a>8)
        {
            cout<<"\nInvalid option..\n";
            cleardevice();
            gotoxy(1,1);
            continue;
        }
        
        if(a==0)
            continue;
        
        x.getgrid(a);
        
        compare(x);
        
        if(found==0)
        {
            if(!x.valid_entered)
                continue;
            
            cout<<"Solving..\n";
            
            x.solve(0,0);
            write(x);
            cout<<"\nNew grid written to file\n";
            x.display();
        }
        found=0;
        getch();
    }
    
}
//--------------------------------------------------------------------------//
//--------------------------------------------------------------------------//
//--------------------------------------------------------------------------//
//--------------------------------------------------------------------------//



void main()
{
    
    initgraph(0,0,”c:/tc:/bgi”);
    cleardevice();
    gotoxy(1,1);
    
    setbkcolor(BLUE);
    menu();
    closegraph();
    
}

/////=======================================/////
