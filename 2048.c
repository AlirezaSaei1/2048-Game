#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int main() {
    int n,m,empty_spaces;
    int score=0,undo_score=0,stored_score=0;
    time_t t;
    srand((unsigned) time(&t));//intializes random number generator
    while (1)
    {
        printf("enter size of the game between 2 and 10:");
        scanf("%d%d",&n,&m);
        if (n<2||n>10||m<2||m>10)
        {
            printf("invalid input\n");
            continue;
        }
        break;
    }
    int stored_matrix[n][m];

    // intializes file and storage ditales
    FILE *file_pointer;
    int min_score_index=0,min_score;
    int score_arr[5];
    char name_arr[5][16];
    char strn[3];
    strn[2]='\0';
    strn[1]=(n%10)+'0';
    strn[0]=(n/10)+'0';
    char strm[3];
    strm[2]='\0';
    strm[1]=(m%10)+'0';
    strm[0]=(m/10)+'0';
    char file_name[10];
    strcpy(file_name,strn);
    strcat(file_name,",");
    strcat(file_name,strm);
    strcat(file_name,".txt");
    int queris=0;
    int saved=0;
    file_pointer=fopen(file_name,"r");
    if (file_name==NULL)
    {}

    // get data from file
    else
    {
        fscanf(file_pointer,"%d %d",&queris,&saved);
        for (int i = 0; i < queris; i++)
        {

            fscanf(file_pointer,"%s %d",&name_arr[i],&score_arr[i]);
            if(i==0){
                min_score=score_arr[i];
            }
            else if (min_score>score_arr[i])
            {
                min_score=score_arr[i];
                min_score_index=i;
            }
             
        }
        if (saved)
        {
            fscanf(file_pointer,"%d ",&stored_score);
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    fscanf(file_pointer,"%d ",&stored_matrix[i][j]);
                }
            }
        }
        
        
    }
    fclose(file_pointer);

    //print score chart 
    system("cls");
    for (int i = 0; i < queris; i++){
        printf("%s : %d\n",name_arr[i],score_arr[i]);
    }



    int new_game=1;
    if (saved)
    {
        char input_char[10];
        while (1)
        {
            printf("Would you like to continue the last game? y/n:\n");
            scanf("%s",input_char);
            if (input_char[0]=='y')
            {
                new_game=0;
                break;
            }
            else if (input_char[0]=='n')
            {
                new_game=1;
                break;
            }
            printf("invalid input");
        }
    }
    
    int matrix[n][m];
    int undo_matrix[n][m];
    


    //restore the saved game if nesesery
    if (new_game==1)
    {
        // initializes a new board
        empty_spaces=n*m;
        int init1=rand()%empty_spaces,init2=rand()%(empty_spaces-1),temp_zero=0;
        empty_spaces-=2;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                matrix[i][j]=0;
                undo_matrix[i][j]=0;
                if (i*n+j==init1){
                    matrix[i][j]=2;
                    undo_matrix[i][j]=2;
                }
            }
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (matrix[i][j]==0)
                {
                    if (temp_zero==init2){
                        matrix[i][j]=2;
                    }
                    temp_zero++;
                }
            }
        }
    }
    else if (new_game==0)
    {
        // initializes the old board
        empty_spaces=0;
        score=stored_score;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                matrix[i][j]=stored_matrix[i][j];
                undo_matrix[i][j]=stored_matrix[i][j];
                if (matrix[i][j]==0)
                {
                    empty_spaces++;
                }
            }
        }
    }
    
    
    

    int step_counter=0;
    while (1)
    {
        // prints the board
        if (step_counter!=0)
        {
            system("cls");
        }
        step_counter++;
        printf("score:%d\n\n",score);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                printf("%6d",matrix[i][j]);
            }
            printf("\n");
        }

        // takes user input
        char user_input,input_array[10];
        printf("\nplease enter the direction to move in format of (u, d, r, l, z, s) for (Up, Down, Right, Left, Undo, Save):");
        scanf("%9s",input_array);
        user_input=input_array[0];

        // undos the board
        if (user_input=='z')
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    matrix[i][j]=undo_matrix[i][j];
                }
            }
            score=undo_score;
            continue;
        }

        if (user_input=='s')
        {

            file_pointer=fopen(file_name,"w");
            fprintf(file_pointer,"%d %d ",queris,1);
            for (int i = 0; i < queris; i++)
            {
                fprintf(file_pointer,"%s %d ",name_arr[i],score_arr[i]);
            }
            fprintf(file_pointer,"%d ",score);
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                        fprintf(file_pointer,"%d ",matrix[i][j]);
                }
                    
            }
            fclose(file_pointer);
                
            return 0;
        }
        

        // saves the board state and score in undo
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                undo_matrix[i][j]=matrix[i][j];
            }
        }
        undo_score=score;


        // calculate the new board state and score for u input
        if (user_input=='u')
        {
            for (int j = 0; j < m; j++)
            {
                int column[n],last_elemet=0,column_index=0;
                for (int i= 0; i < n; i++)
                    column[j]=0;
                for (int i = 0; i < n; i++)
                {
                    if (matrix[i][j]==0)
                        continue;
                    if (matrix[i][j]==last_elemet)
                    {
                        column[column_index-1]=last_elemet*2;
                        score+=last_elemet*2;
                        last_elemet=0;
                        empty_spaces+=1;
                    }
                    else if (matrix[i][j]!=last_elemet)
                    {
                        column[column_index]=matrix[i][j];
                        last_elemet=matrix[i][j];
                        column_index++;
                    }
                }

                int temp_column_index=0;
                for (int i = 0; i <n; i++)
                {
                    if (temp_column_index>=column_index)
                    {
                        matrix[i][j]=0;
                    }
                    else
                    {
                        matrix[i][j]=column[temp_column_index];
                    }
                    temp_column_index++;
                }    
            }
        }


        // calculate the new board state and score for d input
        else if (user_input=='d')
        {
            for (int j = 0; j < m; j++)
            {
                int column[n],last_elemet=0,column_index=0;
                for (int i= 0; i < n; i++)
                    column[j]=0;
                for (int i = n-1; i >=0; i--)
                {
                    if (matrix[i][j]==0)
                        continue;
                    if (matrix[i][j]==last_elemet)
                    {
                        column[column_index-1]=last_elemet*2;
                        score+=last_elemet*2;
                        last_elemet=0;
                        empty_spaces+=1;
                    }
                    else if (matrix[i][j]!=last_elemet)
                    {
                        column[column_index]=matrix[i][j];
                        last_elemet=matrix[i][j];
                        column_index++;
                    }
                }
                for (int i = n-1; i >=0; i--)
                {
                    if (n-i-1>=column_index)
                    {
                        matrix[i][j]=0;
                    }
                    else
                    {
                        matrix[i][j]=column[n-i-1];
                    }
                }    
            }
        }


        // calculate the new board state and score for r input
        else if (user_input=='r')
        {
            for (int i = 0; i < n; i++)
            {
                int row[m],last_elemet=0,row_index=0;
                for (int j= 0; j < m; j++)
                    row[j]=0;
                for (int j = m-1; j >=0; j--)
                {
                    if (matrix[i][j]==0)
                        continue;
                    if (matrix[i][j]==last_elemet)
                    {
                        row[row_index-1]=last_elemet*2;
                        score+=last_elemet*2;
                        last_elemet=0;
                        empty_spaces+=1;
                    }
                    else if (matrix[i][j]!=last_elemet)
                    {
                        row[row_index]=matrix[i][j];
                        last_elemet=matrix[i][j];
                        row_index++;
                    }
                }
                for (int j = m-1; j >=0; j--)
                {
                    if (m-j-1 >=row_index)
                    {
                        matrix[i][j]=0;
                    }
                    else
                    {
                        matrix[i][j]=row[m-j-1];
                    }
                }    
            }
        }


        // calculate the new board state and score for l input
        else if (user_input=='l')
        {
            for (int i = 0; i < n; i++)
            {
                int row[m],last_elemet=0,row_index=0;
                for (int j= 0; j < m; j++)
                    row[j]=0;
                for (int j = 0; j < m; j++)
                {
                    if (matrix[i][j]==0)
                        continue;
                    if (matrix[i][j]==last_elemet)
                    {
                        row[row_index-1]=last_elemet*2;
                        score+=last_elemet*2;
                        last_elemet=0;
                        empty_spaces+=1;
                    }
                    else if (matrix[i][j]!=last_elemet)
                    {
                        row[row_index]=matrix[i][j];
                        last_elemet=matrix[i][j];
                        row_index++;
                    }
                }
                int temp_row_index=0;
                for (int j = 0; j <m; j++)
                {
                    if (temp_row_index>=row_index)
                    {
                        matrix[i][j]=0;
                    }
                    else
                    {
                        matrix[i][j]=row[temp_row_index];
                    }
                    temp_row_index++;
                }    
            }
        }


        else
        {
            system("cls");
            printf("invalid input");
            continue;
        }
        

        // add new 2 blocks
        int zero_spaces=0;
        int init1=rand()%empty_spaces;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (matrix[i][j]==0)
                {
                    if (zero_spaces==init1)
                    {
                        matrix[i][j]=2;
                    }
                    zero_spaces++;
                }
            }
        }


        //checks for game over 
        empty_spaces-=1;
        if (empty_spaces==0)
        {
            int not_game_over=0;
            for (int i = 0; i < n; i++)
            {
                int last_element=0;
                for (int j = 0; j < m; j++)
                {
                    if (last_element==matrix[i][j])
                    {
                        not_game_over=1;
                        break;
                    }
                    last_element=matrix[i][j];
                }
                if (not_game_over)
                    break;
            }
            for (int j = 0; j < m; j++)
            {
                int last_element=0;
                for (int i = 0; i < n; i++)
                {
                    if (last_element==matrix[i][j])
                    {
                        not_game_over=1;
                        break;
                    }
                    last_element=matrix[i][j];
                }
                if (not_game_over)
                    break;
            }

            // game is over
            if (not_game_over==0)
            {
                system("cls");
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < m; j++)
                    {
                        printf("%6d",matrix[i][j]);
                    }
                    printf("\n");
                }
                char name[16];
                printf("games over\n");
                printf("score:%d\nenter yor name:\n",score);
                scanf("%15s",name);
                if (queris==5)
                {
                    if (score >min_score){
                        score_arr[min_score_index]=score;
                        strcpy(name_arr[min_score_index],name);
                    }                
                }
                else
                {
                    score_arr[queris]=score;
                    strcpy(name_arr[queris],name);
                    queris++;
                }
                
                file_pointer=fopen(file_name,"w");
                fprintf(file_pointer,"%d %d ",queris,0);
                for (int i = 0; i < queris; i++)
                {
                    fprintf(file_pointer,"%s %d ",name_arr[i],score_arr[i]);
                }

                fclose(file_pointer);
                return 0;
            }            
        }
    }

    return (0);
}