// Library Management System

#include<iostream>
using namespace std;

//Properties of book
struct Book
{
	char title[50];               //Title of the book
	char authors[200];            //Authors of book
	double price;                 //Price of book
	int accNum;                   //Accession number of book
	bool checkOutStatus;          //Check out status of book (True for checked out and False for not checked out
	int claimantId;               //Id of the patron who has claimed for the book (-1 if there is no claimant)
	int borrowerId;               //Id of patron who has borrowed the book
};

//Properties of patron
struct Patron
{
	char name[50];                //Name of Patron
	char address[50];             //Address of Patron
	int uniueId;                  //Uniue Id of Patron
	int numBooksChkdOut;          //Number of books checked out by patron (not more than 3)
	int claimdBookAccNum;         //Accession number of book that is claimed by Patron
	int borrowedAccNum[3];        //array containing Accession numbers of borrowed book
};

//Function for checking out of book
void checkOutBook(Patron &currPatron, Book &currBook)
{
	//PRECONDITION : Members of currPatron and currBook are properly initialized - no garbage values
	if(currPatron.numBooksChkdOut < 3)              //Checking if 3 books already checked out by patron
	{
		if(currBook.checkOutStatus == true)        //Checking if book is already checked out by another patron
		{
			cout << "Sorry! Book already checked out." << endl;
			return;
		}
	
	     else
	     {
			if((currBook.claimantId != -1) && (currBook.claimantId != currPatron.uniueId))    
			//Checking if there is already a claimant for the book
			{
				cout << "Sorry! There is already a pending claim on book" << endl;
				return;
			}
			else
			{
				for(int i=0; i<3; i++)
			    		if(currPatron.borrowedAccNum[i] == -1)
			    		{
			    			currPatron.borrowedAccNum[i] = currBook.accNum;
			    			break;
			    		}
				currBook.borrowerId = currPatron.uniueId;       //copying id of patron to book borrower id
				currBook.checkOutStatus = true;                 //updating check out status of book to true
				currPatron.numBooksChkdOut++;                   //Increasing number of books checked out by patron
				if(currBook.claimantId == currPatron.uniueId)   //if book was checked out by the same patron as claimed
				{
					currPatron.claimdBookAccNum = -1;          
					currBook.claimantId = -1 ;
				}
				return;
			}
		}
	}
	else
	{
		cout << "Sorry! Three books have already been checked out" << endl;
		return;
	}
	
	//POSTCONDITION : If currPatron is lent to currPatron ,members currPatron and currBook appropriately updated
}

//Function for claiming a book
void claimBook(Patron &currPatron, Book &currBook)
{
	//PRECONDITION : Members of currPatron and currBook are properly initialized - no garbage values
	if((currPatron.numBooksChkdOut == 3) || (currPatron.claimdBookAccNum != -1))    
	{
	//If 3 books are already checked out by patron or there is already a book claimed, then not allowed to claim another book
		cout << "Sorry! No longer allowed to claim anybook." << endl;
		return;
	}
	if(currBook.checkOutStatus == false)
	{
	//If book is not checked out by any other patron
		cout << "Book not yet checked out. No need froa claim." << endl;
		return;
	}
	if((currBook.claimantId != -1) && (currBook.claimantId != currPatron.uniueId))
	{
	//If book is already claimed by any other patron, then patron is not allowed to claim for it	
	     cout << "Sorry! Book already claimed." << endl;
	     return;
	}
	if(currBook.borrowerId == currPatron.uniueId)
	{
	//Checking if patron is claiming a book already checked out by him 	
		cout << "Claimed book checked out by same patron." << endl;
		return;
	}
	else
	{
		currPatron.claimdBookAccNum = currBook.accNum;   //Copying accession no of book to patron's claimed book accession no
		currBook.claimantId = currPatron.uniueId;        //Copying id of patron to claimant id of book
		return;
	}
	
	//POSTCONDITION : Register a claim of currPatron on currBook if allowed.Update members of currPatron, currBook appropriately
}

//Function for returning a book
void returnBook(Patron &currPatron, Book &currBook)
{
	/*PRECONDITION : Members of currPatron and currBook are properly initialized - no garbage values.
	  currPatron had indeed checked out currBook*/
	if(currBook.borrowerId == currPatron.uniueId)   //If book is indeed checked out by patron
	{
		currPatron.numBooksChkdOut--;          //Decreasing number of books checked out by patron
		currBook.checkOutStatus = false;       //Updating check out status of book to false
		for(int i=0; i<3; i++)
		    if(currPatron.borrowedAccNum[i] == currBook.accNum)
		    {
		    	//Updating array of accession number of borrowed books
		    	    currPatron.borrowedAccNum[i] = -1;     //Setting book as returned
		    	    break;
		    }
		currBook.borrowerId = -1;
	}
	else           //If patron is trying to return book not really checked out by him
	{
		cout << "Something strange! Returning somebody else's book?" << endl;
		return;
	}
	//POSTCONDITION : Update members of currBook, currPatron to register return of currBook by currPatron
}






