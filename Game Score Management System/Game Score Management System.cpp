// Name: Nafis Uddin


#include <iostream>
#include<fstream>
#include <string>
#include <iomanip>
using namespace std;


struct node
{
    string name, initial;
    int high_score, plays;
    double revenue;
    node *next = nullptr;
};


void add_from_db(node *& head, string line);
void add(node *&head, string line);
void search(node *head, string term);
void update(node *&head, string line);
node *remove(node *& head, string line);
void sort(node *&head, string line);
void store_database(node*head, ofstream &file_for_database);
void delete_linked_list(node *& head);


// add the data to the linked list from the database file
void add_from_db(node *& head, string line)
{
    node *newnode = new node;

    std::string::size_type index;   // tracking the index of the line

    index = line.find(',');
    newnode->name = line.substr(0, index);      // get the name
    line = line.substr(index+1);

    index = line.find(',');
    newnode->high_score = stoi(line.substr(0, index));     // get the high score
    line = line.substr(index+2);

    index = line.find(',');
    newnode->initial = line.substr(0, index);   // parse the initial
    line = line.substr(index+1);

    index = line.find(',');
    newnode->plays = stoi(line.substr(0, index));       // parse the plays
    line = line.substr(index+3);
    newnode->revenue = stod(line);      // remaining line is the revenue
    
    if(!head)   head = newnode;     // if the linked list is empty assign the new node as the head
    else
    {
        node *ptr = head;   
        while(ptr->next)    // traverse the linked list 
        {   
            ptr = ptr->next;
        }
        ptr->next = newnode;    // add the new node after the last existed node
    }
}


// adding the data to the linked list from the batch file
void add(node *&head, string line)
{
    node * newnode = new node;
    newnode->next = nullptr;

    std::string::size_type index;       // tracking the index of the line
    index = line.find('"', 1);
    newnode->name = line.substr(1, index-1);    // parse the name

    line = line.substr(index+1);
    index = line.find(' ', 1);
    newnode->high_score = stoi(line.substr(1, index));  // parse the high score

    line = line.substr(index+1);
    index = line.find(' ', 1);
    newnode->initial = line.substr(0, index);       // parse the initial

    line = line.substr(index+1);
    index = line.find(' ', 1);
    newnode->plays = stoi(line.substr(0, index));   // parse the plays

    line = line.substr(index+1);
    index = line.find(' ', 1);
    line = line.substr(index+2);    
    newnode->revenue = stod(line);      // parse the revenue

    if(!head) head = newnode;       // if the linked list is empty assign the new node as the head
    else 
    {
        node *ptr = head;
        while(ptr->next)    // traverse the linked list 
        {
            ptr = ptr->next;
        }
        ptr->next = newnode;        // add the new node after the last existed node
    }

    // display the added record
    cout<<"RECORD ADDED"<<endl;
    cout<<"Name: "<<newnode->name<<endl<<"High Score: "<<newnode->high_score<<endl;
    cout<<"Initials: "<<newnode->initial<<endl<<"Plays: "<<newnode->plays<<endl;
    cout<<"Revenue: $"<<fixed << setprecision(2)<<newnode->revenue<<endl<<endl;
}


// check the search term and print the data if found 
void search(node *head, string term)
{
    if(!head) 
    {
        cout<<term<<" NOT FOUND"<<endl<<endl;  /// if the linked list is empty, display not found and return
        return;
    }

    bool test = false;          // check whether the term found

    node *ptr = head;
    while(ptr)
    {
        if(ptr->name.find(term) != string::npos)        // if the term found 
        {
            test = true; 

            //if found, display the searched data
            cout<<ptr->name<<" FOUND"<<endl;
            cout<<"High Score: "<<ptr->high_score<<endl;
            cout<<"Initials: "<<ptr->initial <<endl;
            cout<<"Plays: "<<ptr->plays << endl;
            cout<<"Revenue: $"<<fixed<<setprecision(2)<<ptr->revenue<<endl<<endl;
        }
        ptr = ptr->next;    
    }
    if(!test) cout<<term<<" NOT FOUND"<<endl<<endl;     // if not found, display the term not found
}



// update the data in the linked list
void update(node *&head, string line)
{
    if(!head) return;

    std::string::size_type index;
    int  field, updated_high_score, updated_plays;
    string name_search, updated_initial;
    double updated_revenue;

    node *ptr = head;

    index = line.find('"', 1);
    name_search = line.substr(1, index-1);
    line = line.substr(index+2);     // (index+2) == for double quote and the space after that 

    index = line.find(' ');
    field = stoi(line.substr(0, index));  // to be string, if there is only one digit, keep a space with that 
    line = line.substr(index+1);   // a space after the field
    
    while(ptr)
    {
        if(ptr->name.find(name_search) != string::npos)         // if the term found 
        {
            if(field == 1) 
            {
                updated_high_score = stoi(line);        // if the field is 1, get the high score
                ptr->high_score = updated_high_score;
            }

            else if(field == 2) 
            {
                updated_initial = line;
                ptr->initial = updated_initial;         // if the field is 2, parsse the initial
            }

            else
            {
                updated_plays = stoi(line);         // else parse the plays 
                updated_revenue = updated_plays*0.25;       // update the revenue by 25 percent of the play

                ptr->plays = updated_plays;         
                ptr->revenue = updated_revenue;
            }

            cout << ptr->name<< " UPDATED" << endl;
            cout << "UPDATE TO ";

            // display the data according to the field 
            if(field == 1) cout<< "high score";
            else if(field == 2) cout<<"initials";
            else cout<<"plays";
            
            // display the updated data
            cout<< " - VALUE "<< line<<endl;
            cout << "Name: " << ptr->name <<endl;
            cout << "High Score: "<< ptr->high_score <<endl;
            cout << "Initials: "<< ptr->initial << endl; 
            cout << "Plays: " << ptr->plays << endl;
            cout<<"Revenue: $" << fixed <<setprecision(2) << ptr->revenue <<endl<<endl;
        }

        ptr = ptr->next;
    }
}



// remove the data from the linked list 
node *remove(node *& head, string line)
{
    if(!head) return nullptr;   // if the linked list is empty return nullptr

    node *ptr = head;
    node *hold = nullptr;

    if(head->name.find(line) != string::npos)       // if the term found 
    {
        hold = head;            // hold the head 
        head = head->next;      // make the next node of the head as the head
    }

    else 
    {
        while(ptr->next)        // traverse the linked list
        {
            if(ptr->next->name.find(line) != string::npos)      // if the term found
            {   
                hold = ptr->next;       // hold the address of the term node
                ptr->next = hold->next;  // connect the previous and next node of the hold node
                break;      // if the term found, break the loop 
            }
            ptr = ptr->next;

        }
    }

    if(hold)        // if the hold is not empty
    { 
        // display the removed data
        cout << "RECORD DELETED"<<endl;
        cout << "Name: " << hold->name<<endl;
        cout << "High Score: " << hold->high_score <<endl;
        cout << "Initials: " << hold->initial <<endl; 
        cout<<"Plays: " << hold->plays <<endl;
        cout<<"Revenue: $" << fixed <<setprecision(2) << hold->revenue <<endl<<endl;
    }
    return hold;

}



// sort the data in the linked list
void sort(node *&head, string line) 
{
    if (!head || !head->next) return;       // if the linked list is empty or there is only one node, return

    if (line == "name")         // if the "name" is asked to sort
    {
        cout<<"RECORDS SORTED BY name"<<endl;
        bool test = false;      // check whether sorted

        do 
        {
            test = false;       // reset the test after every iteration
            node *tmp = nullptr;
            node *ptr = head;

            while (ptr->next)      // check the next node of the linked list and traverse
            {
                if (ptr->name > ptr->next->name)        // if the current node name is greater than the next node name 
                {   
                    node *next_node = ptr->next->next;      // hold the next pointer address of the next node 
                    if (tmp) 
                    {
                        tmp->next = ptr->next;  // Link the node before the current node to the next node
                    } 

                    else 
                    {
                        head = ptr->next;         // If that's the first node, update the head to the next node
                    }

                    ptr->next->next = ptr;
                    ptr->next = next_node;
                    test = true;

                    if (!tmp) 
                    {
                        ptr = head;    // reset the pointer to head
                    } 

                    else 
                    {
                        ptr = tmp->next;
                    }
                } 

                else 
                {
                    tmp = ptr;
                    ptr = ptr->next;
                }
            }
        } 
        while (test);       // run the loop as long as the test is true
    }


    else if (line == "plays")           // if the "plays" is asked to sort
    {
        cout<<"RECORDS SORTED BY plays"<<endl;          
        bool test = false;          // check whether sorted

        do 
        {   
            test = false;       // reset the rest after every iteration
            node *tmp = nullptr;
            node *ptr = head;

            while (ptr->next)               // check the next node of the linked list and traverse
            {
                if (ptr->plays > ptr->next->plays)  // if the current node plays is greater than the next node plays 
                {
                    node *next_node = ptr->next->next;   // hold the next pointer address of the next node 
                    if (tmp) 
                    {
                        tmp->next = ptr->next;      // Link the node before the current node to the next node
                    } 

                    else 
                    {
                        head = ptr->next;
                    }

                    ptr->next->next = ptr;
                    ptr->next = next_node;
                    test = true;

                    if (!tmp) 
                    {
                        ptr = head;         // reset the pointer to head
                    } 

                    else 
                    {
                        ptr = tmp->next;            // If that's the first node, update the head to the next node
                    }
                } 

                else 
                {
                    tmp = ptr;        
                    ptr = ptr->next;  
                }
            }
        } 

        while (test);           // run the loop as long as the test is true
    }
    
    node *ptr = head;

    while(ptr)          // traverse the linked list
    {
        // display the sorted data
        cout<<ptr->name<<", "<<ptr->high_score<<", "<<ptr->initial<<", "<<ptr->plays;
        cout<<", $"<< fixed << setprecision(2) << ptr->revenue<<endl;

        ptr = ptr->next;
    }
    cout<<endl;
}



// store the data to the database file from the linked list  recursively
void store_database(node*ptr, ofstream &file_for_database)      
{
    if(!ptr) return;        // if the linked list empty return
    else 
    {   
        // else store the data to the database file
        file_for_database<<ptr->name<<", "<<ptr->high_score<<", "<<ptr->initial<<", "<<ptr->plays;
        file_for_database<<", $"<< fixed << setprecision(2) << ptr->revenue<<endl;
        
        ptr = ptr->next;
        store_database(ptr, file_for_database);     // used recursive function
    }    

}

// delete the linked list
void delete_linked_list(node *& head)
{
    while(head)     // traverse the linked list
    {
        node *hold = head;      // hold the head of the linked list
        head = head->next;      // make the head as the next node of the head
        delete hold;            // delete the node
    }
}


// taking all input from the user and calling other functions

int main()
{
    node *head = nullptr;
    string batchfile, database_file, line;

    cout<<"Enter the database file name"<<endl;
    cout<<"Enter the batch file name"<<endl;

    cin>>database_file>>batchfile;

    //opening the database file for taking input

    ifstream data_in_db(database_file, ios::binary);
    if(data_in_db)
    {
        while(getline(data_in_db, line))   //take data from the database file line by line
        {
            if(line == "") break;
            add_from_db(head, line);  // call the fuction to process the data and add to the linked list
        }
        data_in_db.close();
    }
    else cout<<"Sample database file doesn't open"<<endl;



    int action;

    ifstream file(batchfile, ios::binary);  // open the batch file and take input for the following actions
    if(file)
    {
        while(getline(file, line))      // take input line by line
        {
            if(line == "") break;
            action = (line.at(0)) - 48;      // parse the first number from the line 

            line = line.substr(2);      // substract the first action number and the space

            switch (action)
            {
                case 1:
                {
                    add(head, line);        // adding the data to the linked list 
                    break;
                }
                case 2:
                {
                    search(head, line);     // searching the term in the linked list
                    break;
                }
                case 3: 
                {
                    update(head, line);     // updating the data of the searched term in the linked list
                    break;
                }
                case 4:
                {
                    remove(head, line);     // removing the data from the linked list
                    break;
                }
                case 5: 
                {
                    sort(head, line);       // sorting the data in the linked list
                    break;
                }
                default: break;
            }
        }
        file.close();       // batch file close
    }
    else cout<<"Batch file doesn't open"<<endl;

    string datafile = "freeplay.dat";                   // new database file name
    ofstream file_for_database(datafile, ios::binary);  // new database file open

    store_database(head, file_for_database);      // store all the data to the new database file from the linked list

    delete_linked_list(head);       // delete the entire linked list

    return 0;
}