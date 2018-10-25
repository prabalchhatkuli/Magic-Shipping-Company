#include<iostream>
#include <iomanip>
#include <ctime>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Owl.h"
#include "Griffin.h"
#include "VanishingCabinet.h"

using namespace std;

/* required functions.  you cannot change the return type or the identifiers 
 * but you can add parameters */
void print_menu(); //displays the menu
size_t get_selection();//gets the menu selection from the user
void schedule_new_delivery(string &name, char &type, double &weight);//adds a new delivery
string input_name();
char input_shipping();
double input_weight();
string generate_id(char shipping_type);//generates a random numbers according to the shipping types
void display_all(vector<Delivery*> main_list, unsigned int number_of_deliveries); //displays all deliveries
void display_type(vector<Delivery*> main_list,unsigned int number_of_deliveries); //displays deliveries of chosen type
void save_file(vector<Delivery*> main_list ,unsigned int num);
void load_file(vector<Delivery*> &main_list, unsigned int &num);
string time_stamp();// creates and returns time stamp
bool duplicates(vector<Delivery*> main_list,string id, int num);//checks for duplicates
void bubble_sort(vector<Delivery*> &unsorted_vec);

int main()
{
    //variable declaration
    //create main array, containing the pointer of objects, just one array, where array is the vector
    vector<Delivery*> main_list; 
    
    string name_of_sender;
    string timestamp;
    double weight;
    string id;
    char shipping_type;
    size_t select;
    unsigned int remove_selection; 
   
    //counter for array
    unsigned int number_of_deliveries = 0;
   
    //seed random genrator
    srand (time(NULL));


    //menu loop driven by user selection
    do
    {
        //display menu and select option
        print_menu();
        select=get_selection();   

	switch(select)
	{
	   case 1:
	   	   schedule_new_delivery(name_of_sender,shipping_type, weight);//remove id form here
                
                   //input tiemstamp from the system
                      timestamp= time_stamp();
		   //evaluating the type of shipping for the delivery
		   if('y'==shipping_type)
		   {
			   if(weight>1.58)
			   {
				 shipping_type='g';//find id after finding this
                                   //create griffin object pointer and object and insert in the array;
                                 do
                                 {
                                    id=generate_id(shipping_type);
                                 }while(duplicates(main_list, id,number_of_deliveries ));
                                   //create objects and pointers
                                 main_list.push_back( new Griffin(name_of_sender, timestamp, weight, id));

			   }
			   else
                           {
				 shipping_type='o';                             
                                 //create owl object pointer and object; store the relevant information in the array; 
                                 do
                                 {
                                    id=generate_id(shipping_type);
                                 }while(duplicates(main_list, id,number_of_deliveries ));
                                 main_list.push_back( new Owl(name_of_sender, timestamp, weight, id));                                 
		           }
                   }
		   else
		   {
		   	   shipping_type='v';
                           //create vanishingCabinet object pointer and object ; store the related information in the object;
                           do
                           {
                              id=generate_id(shipping_type);
                           }while(duplicates(main_list, id,number_of_deliveries ));
                           main_list.push_back( new VanishingCabinet(name_of_sender, timestamp, weight, id));   
		   }

	   	   // increasing number of customers after new delivery
		   number_of_deliveries++;			
		   		break;

           case 2: 
	 	   //diplay prompt
		   cout<<"Remove a delivery"<<endl;
		   cout<<"-----------------"<<endl<<endl;


		   //if numbevoid display_all(deliveries** main_list, unsigned int number_of_deliveries)r of deliveries is equal to 0; print error
		   if(number_of_deliveries==0)
		   {
			cout<<"\t ERROR: Nothing to remove"<<endl;
			        break;
		   }
		   //else display and get selection
  		   display_all(main_list,number_of_deliveries);  
		   do
		   {
		      cout<<"Which would you like to remove (enter the index): ";
		      cin>>remove_selection;
		   }while(!(remove_selection>=0 && remove_selection<number_of_deliveries));
		   
		   //replace the remove_selection element with the last element of the array;		
		   delete main_list[remove_selection];
                   main_list[remove_selection]=main_list[number_of_deliveries-1];
                   //remove last element
                   main_list.pop_back();                  

		   //decreaseing the number of customers after removing a delivery
		   number_of_deliveries--;
			        break;


	   case 3: 
                   load_file(main_list, number_of_deliveries);
				break;


	   case 4:
                   save_file(main_list, number_of_deliveries);
				break;

           case 5:
                  {
                     //sorting according to type of delivery then according to ID
                     //create 3 different vectors to store information of single type
                     vector<Delivery*> Owl_vec;
                     vector<Delivery*> Griffin_vec;
                     vector<Delivery*> VanishingCabinet_vec;

                     //check the type of delivery
                     for(int i=0; i<number_of_deliveries; i++)
                     {
                        switch((main_list[i]->get_id()).length())
                        {
                           case 4:
                                  Owl_vec.push_back(main_list[i]);
                                        break;
                           case 8:
                                  Griffin_vec.push_back(main_list[i]);
                                        break;
                           case 17:
                                  VanishingCabinet_vec.push_back(main_list[i]);
                                        break;
                        }
                     }

                     //sort using bubble sort
                        bubble_sort(Owl_vec);
                        bubble_sort(Griffin_vec);
                        bubble_sort(VanishingCabinet_vec);
                  
                        //insert griffin into owl
                        Owl_vec.insert(Owl_vec.end(),Griffin_vec.begin(),Griffin_vec.end());
                        
                        //insert Vanishingcabinet into owl
                        Owl_vec.insert(Owl_vec.end(),VanishingCabinet_vec.begin(),VanishingCabinet_vec.end());
                        
                        //copy form owl vector to main_list vector
                        for(int i=0; i<Owl_vec.size(); i++)
                        {
                           main_list[i]=Owl_vec[i];
                        }
                     
                  }

                                break;

           case 6:
                  //suffling the deliveries in the list randomly
                  {
                     for(int i=0; i<main_list.size(); i++)
                     {
                        int r = rand()%main_list.size();
                        Delivery* tmp = main_list[i];
                        main_list[i] = main_list[r];
                        main_list[r] = tmp;
                     }
                  }
                                break;

	   case 7: 
	   	   display_all(main_list,number_of_deliveries);
                                break;

	   case 8: 
	   	   display_type(main_list,number_of_deliveries);
			        break;

	   case 9: 
                   //delete each element deallocate the memory    
                   for(int i=0; i<number_of_deliveries; i++)
                   {
                      delete main_list[i];
                   }
                   cout<<"Thank you for using HOGWARTS."<<endl<<endl;
			        break;
    	   default: 
	   	    cout<<"Invalid selection: Please enter a number"<<
	   	    " between 1 and 5"<<endl;
			        break;
	}	
    }while(!(select==9));

    return 0;
}


//print menu
void print_menu() 
{
   cout<<endl<<"Please select from the following choices:"<<endl;
   cout<<"\t (1) Schedule a new delivery"<<endl;
   cout<<"\t (2) Remove a delivery"<<endl;
   cout<<"\t (3) Load deliveries from file"<<endl;
   cout<<"\t (4) Save deliveries to file"<<endl;
   cout<<"\t (5) Sort Deliveries"<<endl;
   cout<<"\t (6) Shuffle Deliveries"<<endl;
   cout<<"\t (7) Display all scheduled deliveries"<<endl;
   cout<<"\t (8) Display deliveries by tranportation type"<<endl;
   cout<<"\t (9) Exit"<<endl;
}

//bubble sort array
void bubble_sort(vector<Delivery*> &unsorted_vec)
{
   Delivery* tmp;
   for(int i=0;i<unsorted_vec.size();i++)
   {
      for(int j=0; j<(unsorted_vec.size()-1);j++)
      {
         if(((unsorted_vec[j])->get_id())>((unsorted_vec[j+1])->get_id()))
         {
            //swap elements if true
            tmp = unsorted_vec[j];
            unsorted_vec[j] = unsorted_vec[j+1];
            unsorted_vec[j+1] = tmp;
         }
      }
   }
}
//get user selection
size_t get_selection()
{
   //var declaration
   size_t select;

   //input and validate variable

      cout<<"Selection: ";
      cin>>select;

   cout<<endl;
   //return
   return select;
}

//input new delivery: calls to input name, type, weight and, id
void schedule_new_delivery(string &name, char &type, double &weight)
{
   cout<<"Schedule a new delivery"<<endl;
   cout<<"-----------------------"<<endl;
   name=input_name();
   type=input_shipping();
   weight=input_weight();    
 
   cout<<endl;

}

//input name
string input_name()  
{
   //var declare
   string nameOfCustomer;

   //input
   if(cin.peek()=='\n')
   {
      cin.ignore();
   }
   cout<<"\t Please enter the sender's name: ";
   getline(cin,nameOfCustomer);

   //return 
   return nameOfCustomer;
   
}



//input shipping type
char input_shipping()
{
   //declare var
   char typeOfShipping;

   //input type
   do
   {
      cout<<"\t Standard Shipping (Y/N): ";
      cin>>typeOfShipping;
      typeOfShipping=tolower(typeOfShipping);
   }while(!(typeOfShipping=='y'||typeOfShipping=='n')); 
 
   //return
   return typeOfShipping;  
}

//input weight of shipping material
double input_weight()
{
   //declare variable
   double weight;

   //input weights
   do
   {
      cout<<"\t Enter weight (kgs): ";
      cin>>weight;
   }while(!(weight>0));

   //return
   return weight;
}

//generate random id for customer
string generate_id(char shipping_type)
{
   long long int num;
   string id;
   stringstream ss;

   //create randomly generated numbers and then convert them into strings
   switch(shipping_type)
   {
      case 'o':
               num=rand()%999;
               ss.width(3);
               ss.fill('0');
               ss << num;
               id=ss.str();

               id.insert(0,"o");
                        break;
      case 'g':
               num=rand()%9999999;
               ss.width(7);
               ss.fill('0');
               ss << num;
               id=ss.str();

               id.insert(0,"g");
                        break;
      case 'v':
               num=rand()%9999999999999999;
               ss.width(16);
               ss.fill('0');
               ss << num;
               id=ss.str();

               id.insert(8,"-");
                        break;
    }
   return id;
}


//function to generate time stamp of delivery
string time_stamp()
{

   time_t systemtime;
   tm * timeinfo;

   time(&systemtime);
   timeinfo = localtime(&systemtime);
   string time_stamp = asctime(timeinfo);
  
   return time_stamp;

}

//function to display all cusotmers with their information
void display_all(vector<Delivery*> main_list, unsigned int number_of_deliveries)
{
   //declare variable
   unsigned int i;

   //run for loop and print elements of array
   cout<<endl;
   cout<<"All Deliveries"<<endl;
   cout<<"----------------"<<endl;
   for(i=0;i<number_of_deliveries;i++)
   {
      cout<<"["<< i <<"]"<<" ";
      (main_list[i])->print_info();
      
      cout<<endl;  
      
   }
   cout<<endl;
   //return
}

//function to display the list of customer who have a specific type of shipping
void display_type(vector<Delivery*> main_list,unsigned int number_of_deliveries)
{
   //declare variable
   unsigned int i,option;


   // display and input choices of type
   cout<<"All Deliveries"<<endl;
   cout<<"----------------"<<endl<<endl;
   do
   {
      cout<<"Which type (1) Griffin, (2) Owl, (3) Vanishing Cabinet? ";
      cin>>option;
   }while(!(option>=1&&option<=3));

   //diplay output according to option
   for(i=0;i<number_of_deliveries;i++)
   {
      switch(option)
      {
         case 1:
	     if((main_list[i]->get_id()).length()==8)
	     {
                cout<<"["<< i <<"]"<<" ";
                main_list[i]->print_info();
                cout<<endl;  
             }
	        break;
 	     
         case 2:
	     if((main_list[i]->get_id()).length()==4)
             {
                cout<<"["<< i <<"]"<<" ";
                main_list[i]->print_info();
                cout<<endl; 
      	     }
		break;
	  
         case 3:
	     if(((main_list[i])->get_id()).length()==17)
	     {
                cout<<"["<< i <<"]"<<" ";
                main_list[i]->print_info();
                cout<<endl;                 
	     }
                break;
	      
      }
   }  
   cout<<endl;

}

//function to save the file
void save_file(vector<Delivery*> main_list ,unsigned int num)
{
   //insert ofstream class output object
   ofstream output;
   string filename;
   
   //input filename
   if(cin.peek()=='\n')
   {
      cin.ignore();
   }
   cout<<"Please enter the secret filename to save: ";
   getline(cin,filename);
   
   //open the file
   output.open(filename.c_str());
   
   //prompt and condition for the secret filename
   if(output.fail())
      cout<<filename<<" does not exist."<<endl;
   else
   {
      cout<<filename<<" exists."<<endl;

      //output number of customers at the time of save
      output<<num<<endl;
    
      //output information onto the output file 
      for(int i=0;i<num;i++)
      {
         output<< (main_list[i])->get_sender_name()<<endl;
	 output<< (main_list[i])->get_weight()<<endl;
	 output<< (main_list[i])->get_id()<<endl;
	 output<< (main_list[i])->get_time_stamp()<<endl;
              
      }
   //save prompt
   cout<<"File saved."<<endl;
   }
   
   //close stream
   output.close();
   


}

//function to check for duplicates
bool duplicates(vector<Delivery*> main_list,string id, int num)
{
   for(int i=0; i<num; i++)
   {
      if(id== (*main_list[i]).get_id())
      {
         return true;
      }
   }
   return false;
}

//to load from a saved file
void load_file(vector<Delivery*> &main_list, unsigned int &num)
{
   //insert ofstream class output object
   ifstream input;
   string filename;
   
   //input filename
   if(cin.peek()=='\n')
   {
      cin.ignore();
   }
   cout<<"Please enter the secret filename to load: ";
   getline(cin,filename);
   
   //open the file
   input.open(filename.c_str());
   
   //declaring variable to input from the save file
   unsigned int cus_num;
   string cus_name;
   double cus_weight;
   char cus_shipping_type;
   string cus_id;
   string cus_time_stamp;

   //prompt and condition for the secret filename
   if(input.fail())
      cout<<filename<<" does not exist."<<endl;
   else
   {
      cout<<filename<<" exists."<<endl;

      //input the number of saved deliveries
      input>>cus_num;
      input.ignore();

      //correct upto here
      for(int i=0;i<cus_num;i++)
      {
	 //ingnore new line and read the name with getline, input others normally
         //put.ignore();

	 //receiveing the value then assigning will be more effective and less errror prone
         getline(input,cus_name);


	 input>>cus_weight;

         input.ignore();
         getline(input,cus_id);

         //input.ignore();
         getline(input,cus_time_stamp);
 
         switch((cus_id).length())
         {
            case 4:
                   main_list.push_back( new Owl(cus_name, cus_time_stamp, cus_weight, cus_id));

	               break;
 	     
            case 8:
                   main_list.push_back( new Griffin(cus_name, cus_time_stamp, cus_weight, cus_id)); 
		        break;
	  
            case 17: 
                   main_list.push_back( new VanishingCabinet(cus_name, cus_time_stamp, cus_weight, cus_id));

                         break;
         }  
   
	 num++;
         input.ignore();

      }
      //save prompt
      cout<<"File Loaded."<<endl;
   }
   
   //close stream
   input.close();
}

