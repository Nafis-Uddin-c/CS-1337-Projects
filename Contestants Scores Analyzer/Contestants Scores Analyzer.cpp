// Name: Nafis Uddin



#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;


void answer_read(string, char *&, int &);
void contest_read(string, char *&, string *&, int &, int);
void contest_score(char *&, char *&, int*&, int *&, float *&, char*, char *&, int, int, int &);
void display_data(string *, float *, int, int *, int *, char *, char *, int);
void sort_arr(float *, float *&, int);
void stat_report(float *, int);
void most_missed(int *, int, int, int);


int main()
{
    int contestants = 0, questions = 0, total_missed = 0;
    char *answer_arr = nullptr;               // answer key
    char *contestant_key = nullptr;          // keys of all the contestants
    string *contestant_ID = nullptr;        // ID of the contestant
    float *contestant_score = nullptr;     // contestant's score
    int *question_missed = nullptr;       // number of missed questions by every contestant
    int *missed_ques = nullptr;          // the number of the question that missed
    char *correct_ans = nullptr;        // correct answer of the missed question
    char *incorrect_ans = nullptr;     // the incorrect answer of the contestant
    float *sort_score = nullptr;      // sorted score

    string answer_file, contest_file;
    cout<<"Enter the answer file "<<endl;
    cin>>answer_file;

    cout<<"Enter the contestant file "<<endl;
    cin>>contest_file;


    // reading the answer file
    answer_read(answer_file, answer_arr, questions);

    //reading the contestant file
    contest_read(contest_file, contestant_key, contestant_ID, contestants, questions);
    
    //calculating the contestant score
    contest_score(correct_ans, incorrect_ans, missed_ques, question_missed, contestant_score, 
    answer_arr, contestant_key, questions, contestants, total_missed);
    
    // printing the contestant data
    display_data(contestant_ID, contestant_score, contestants, question_missed, missed_ques, 
    correct_ans, incorrect_ans, total_missed);
    
    // sorting the score
    sort_arr(contestant_score, sort_score, contestants);
   
    // calculating the mean, mode, and median
    stat_report(sort_score, contestants);
    
    // calculating and printing the most missed questions and perchantages
    most_missed(missed_ques, total_missed, contestants, questions);


    // deleting all the dynamic arrays
    delete [] answer_arr;
    delete [] contestant_key;
    delete [] contestant_ID;
    delete [] contestant_score;
    delete [] question_missed;
    delete [] missed_ques;
    delete [] correct_ans;
    delete [] incorrect_ans;
    delete [] sort_score;

    return 0;
}



// reading the answer file word by word and store them into the answer_arr (pointer array)
void answer_read(string answer_file, char *&answer_arr, int &questions)
{
    char ch;
    fstream file(answer_file, ios::in | ios::out | ios:: binary); //open tbe answer file

    if(!file) cout<<"Answer file doesn't open"<<endl;   //check the file
    
    else 
    {
        while(file>>ch)     //reading character
        {
            questions++;   // collecting total questions
        }
    }   

    file.clear();
    file.seekg(0, ios::beg);        // file pointer goes to beggining


    answer_arr = new char [questions];   

    if(file)
    {
        while(file>>ch)     //reading character
        {
            *answer_arr = ch;
            answer_arr++;
        }

        file.close();   //close the file
    }   
    answer_arr -= questions;   //repointing to the intial address

}



// reading the contestant file and store the ID and contestant key into the pointer
void contest_read(string contest_file, char *& contestant_key, string *& contestant_ID, int &contestants, int questions)
{
    string line;
    int number;

    fstream file(contest_file, ios::in | ios::out | ios::binary);  // open the contestant file

    if(!file) cout<<"Contest file doesn't open"<<endl;  // check the file
    
    else
    {
        // reading every line to get the total contestants
        while(getline(file, line))     
        {
            if(line == "") break;      
            contestants++;
        }

        file.clear();           
        file.seekg(0, ios::beg);        // file pointer goes to beggining

        contestant_ID = new string [contestants];   


    // reading the file to get the contestant ID
        for(int i = 0; i<contestants; i++)
        {
            getline(file, line);
            *contestant_ID = line.substr(0, line.find(' '));      //storing contestant ID
            contestant_ID++;
        }

        contestant_ID -= contestants;  // repointing to the initial address of the pointer

        file.clear();
        file.seekg(0, ios::beg);        // file pointer to the beginning

        contestant_key = new char[contestants * questions];
        

    // reading the file to get the contestant keys
        for(int i = 0; i<contestants; i++)
        {
            file>>number;             // reading the ID number to ignore

            for(int j = 0; j<questions; j++)
            {
                file>>*contestant_key;          // reading the character
                contestant_key++;           
            }
        }

        contestant_key -= (questions*contestants);   // pointing to the intial address
        file.close();       //close the file
    }
}


// calculating the contestant score
void contest_score(char *& correct_ans, char *& incorrect_ans, int *& missed_ques, 
int *& question_missed, float *& contestant_score, char* answer_arr, char *& contestant_key, 
int questions, int contestants, int &total_missed)

{
    contestant_score = new float[contestants];
    question_missed = new int[contestants];


    // calculating the total_missed question to get the size of the below pointers
    for(int i = 0; i<contestants; i++)
    {
        for(int j = 0; j<questions; j++)
        {
            if(*contestant_key != *answer_arr) 
            {
                total_missed++;     // counting the total missed question
            }

            contestant_key++;
            answer_arr++;
        }
        answer_arr -= questions;
    }

    contestant_key -= (contestants * questions);
    
    // dynamic pointers with size
    missed_ques = new int[total_missed];
    correct_ans = new char[total_missed];
    incorrect_ans = new char[total_missed];



    for(int i = 0; i<contestants; i++)
    {
        float score = 0;

        for(int j = 0; j<questions; j++)
        {
            if(*contestant_key == *answer_arr)  score++;
            else
            {
                //storing the number of the missed questions
                *missed_ques = (j+1);

                // storing the correct answer of the missed questions
                *correct_ans = *answer_arr;

                //storing the incorrect answer of the missed questions
                *incorrect_ans = *contestant_key;

                missed_ques++;
                correct_ans++;
                incorrect_ans++;
                
            }
            contestant_key++; 
            answer_arr++;
        }

        answer_arr -= questions;

        //calculating the total missed question of an individual contestant
        *question_missed = (questions - static_cast<int>(score));  

        // calculating the score of the contestant     
        *contestant_score = (score/static_cast<float>(questions))*100;

        question_missed++;
        contestant_score++;
    }
    

    // pointing to the initial address
    contestant_key -= (contestants * questions);
    contestant_score -= contestants;
    question_missed  -= contestants;

    missed_ques -= total_missed;
    correct_ans -= total_missed;
    incorrect_ans -= total_missed;
    
}



// printing the contestant's data
void display_data(string *contestant_ID, float *contestant_score, int contestants, int *question_missed, 
int *missed_ques, char *correct_ans, char *incorrect_ans, int total_missed)

{
    for(int i = 0; i<contestants; i++)
    {
        cout<<*contestant_ID<<" - ";        // contestant ID
        cout<<fixed<<setprecision(2)<<*contestant_score<<endl;  // contestant score

        if(*question_missed > 0)        // if any contestant missed more than 0 question
        {
            for(int j = 0; j<*question_missed; j++)
            {
                cout<<*missed_ques<<" ";        // missed number of the questions
                missed_ques++;
            }
            cout<<endl;
            
            for(int j = 0; j<*question_missed; j++)
            {
                cout<<*incorrect_ans<<" ";      // contestant answer of the missed question
                incorrect_ans++;
            }
            cout<<endl;

            for(int j = 0; j<*question_missed; j++)
            {
                cout<<*correct_ans<<" ";        // correct answer of the missed question
                correct_ans++;
            }

            cout<<endl<<endl;
        }

        else cout<<endl;
        contestant_score++;
        contestant_ID++;
        question_missed++;
    }
    
    // pointing to the initial address of the pointer
    contestant_ID -= contestants;
    contestant_score -= contestants;
    question_missed -= contestants;
    missed_ques -= total_missed;
    correct_ans -= total_missed;
    incorrect_ans -= total_missed;
}




//sorting the score into new array
void sort_arr(float *contestant_score, float *& sort_score, int contestants)
{
    sort_score = new float [contestants];

    for(int i = 0; i<contestants; i++)
    {
        *sort_score = *contestant_score;        //copy the value into new array
        contestant_score++;
        sort_score++;
    }

    sort_score -= contestants;
    contestant_score -= contestants;

    std::sort(sort_score, sort_score + contestants);    //sort the array
}



// calculating mean, mode, and median
void stat_report(float*sort_score, int contestants)
{
    // Mean calculation
    float mean = 0;

    // calculating the mean from the sort_score (vector) array
    for(int i = 0; i<contestants; i++)
    {
        mean += *sort_score;        // adding all the value
        sort_score++;
    }
    sort_score -= contestants;

    mean /= float(contestants);         


    // Median calculation
    float median = 0;
    
    //calculating the median if total contestants are even number
    if(contestants %2 == 0)
    {
        sort_score += ((contestants-1)/2);  
        median += *sort_score;      

        sort_score++;
        median += *sort_score;

        median /= 2;        // the average of the sum of the two middle values

        sort_score--;
        sort_score -= ((contestants-1)/2);
        
    }

    // calculating the median if total contestants are odd
    else 
    {
        sort_score += (contestants/2);      // the middle value of the sort array
        median = *sort_score;

        sort_score -= (contestants/2);
    }



    //Mode calculation
    vector<float>mode;
    
    int counter = 1;
    int max_counter = 0;

    float current_score;
    float next_score;
    
    if(contestants == 1) max_counter = 1;

    else
    {
        for(int i = 0; i<contestants-1; i++)
        {
            current_score = *sort_score;
            sort_score++;
            next_score = *sort_score;

            if(current_score == next_score) 
            {
                counter++;      // calculating the counter of every score
            }
            
            if(max_counter <counter) 
            {
                max_counter = counter;          //find the max counter
            }

            if(current_score != next_score) 
            {
                counter = 1;           // reassing the counter value 1 since it finds new score
            }
        }
        sort_score -= (contestants-1);
    }

    counter = 1;     // reassign counter is 1


    if(max_counter == 1)     // if that happens, every element of the array should store
    {
        for(int i = 0; i<contestants; i++)
        {
            mode.push_back(*sort_score);   //store all the score existed in the sort array
            sort_score++;
        }
        sort_score -= contestants;
    }

    else
    {
        for(int i = 0; i<contestants-1; i++)
        {
            current_score = *sort_score;
            sort_score++;
            next_score = *sort_score;

            if(current_score == next_score) 
            {
                counter++;
                if(max_counter == counter)      // if counter is same as max_counter
                {
                    sort_score--;
                    mode.push_back(*sort_score);  // push back that score into the mode (vector) array
                
                    sort_score++;
                }
            }

            else 
            {
                counter = 1;        // reassing the counter value 1 since it finds new score
            }
        }
        sort_score -= contestants;
    }



        // printing the mean, median, and mode

    cout<<"Mean: "<<mean<<endl<<"Median: "<<median<<endl<<"Mode: ";


    bool tmp = false;
    for(int i = 0; i<contestants; i++)
    {
        if(*sort_score > 0) tmp = true;    // check the last score is that is more than zero
        sort_score++;
    }
    sort_score -= contestants;


    if(tmp == false) cout<<0.00<<endl;      // if there is no value that's more than zero, it will print mode is 0.00

    else 
    {
        for(int i = 0; i<mode.size(); i++)
        {
            cout<<mode.at(i);

            // if vector size if more than 1 and index is less than the size number, it will print the comma
            if(mode.size() > 1 && i<(mode.size()-1)) cout<<", ";  
        }
    }

    cout<<endl<<endl;

}


//calculating the most missed questions
void most_missed(int *missed_ques, int total_missed, int contestants, int questions)
{ 
    cout<<"MOST MISSED QUESTIONS"<<endl;  

    for(int i = 1; i<=questions; i++)
    {
        float counter = 0; 
        for(int j = 0; j<total_missed; j++)
        {
            if(i == *missed_ques)       // if the question number matched with missed question 
            counter++;
            missed_ques++;
        }
        
        // calculate the perchantage
        counter /= float(contestants);
        counter *= 100;

        if(counter > 60)        // if the perchantage is more than 60%
        {
            // print the most missed question
            cout<<left<<setw(8)<<i<<counter<<"%"<<endl;  
        }
        missed_ques -= total_missed;       
    }
}
