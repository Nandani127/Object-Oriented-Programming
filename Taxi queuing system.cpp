//A Taxi Queuing System

#include<iostream>
using namespace std;

//Information of driver
struct Driver
{
	string name;            //name of the driver
	int id;                 //id of the driver
};

//Information of taxi
struct LinkedTaxi
{
	int id;                //id of the taxi
	Driver *drv;           //Pointer to object of Driver
	LinkedTaxi *next;      //pointer to next taxi
};

//Overall Queue
struct Queue
{
	LinkedTaxi *front;     //pointer to first taxi in Queue
	LinkedTaxi *end;       //pointer to last taxi in Queue
	int numTaxis;          //Number of taxis in Queue
};

int main()
{
	Queue q;
	q.front = NULL;
	q.end = NULL;
	q.numTaxis = 0;
	while(true)
	{
		cout << "Command: 'j' to join queue, 'd' to dispatch, 'x' to exit." << endl;
		char command;
		cin >> command;
		switch(command)
		{
			case 'j':
				//Adding a taxi at 'end' of queue
				Driver *newDrv;
				newDrv = new Driver;            //allocating a new object of type Driver
				if(newDrv == NULL)              //if memory allocation fails
				{
					cout << "Memory allocation failure"<<endl;
					return -1;
				}
				cout << "Give name of driver: ";
				cin >> newDrv -> name;
				cout << "Give id of driver: ";
				cin >> newDrv -> id;
				LinkedTaxi *newTaxi;
				newTaxi = new LinkedTaxi;        //allocating a new object of type LinkedTaxi
				if(newTaxi == NULL)              //if memory allocation fails
				{
					cout << "Memory allocation failure"<<endl;
					return -1;
				}
				newTaxi -> drv = newDrv;
				newTaxi -> next = NULL;
				cout << "Give id of taxi: ";
				cin >> newTaxi -> id;
				if(q.end == NULL)             //Initially queue is empty
                    {
                    	q.front = newTaxi;
                    	q.end = newTaxi;
                    	q.numTaxis = 1;
				}
				else                           //there are already some taxis in the queue
				{
					(q.end) -> next = newTaxi;
					q.end = newTaxi;
					q.numTaxis++;
				}
				break;
			case 'd' :
				//Dispatching a taxi from 'front' of queue
				if(q.front == NULL)              //If queue is empty
				    cout << "Sorry! No taxis in queue at present!"<<endl;
				else
				{
					LinkedTaxi *dispatchTaxi;
					dispatchTaxi = q.front;
					if(q.front == q.end)            //If there is only one taxi in queue
					{
						q.front = NULL;
						q.end = NULL;
						q.numTaxis = 0;
					}
					else
					{
						q.front = (q.front) -> next;
						q.numTaxis--;
					}
					if(dispatchTaxi != NULL)             //Deleting the space allocated to taxi
					{
						cout << "Dispatching taxi with id "<< dispatchTaxi -> id << endl;
						if(dispatchTaxi -> drv != NULL)
						    delete dispatchTaxi -> drv;
						delete dispatchTaxi;
					}
				}
				break;
			case 'x' :
			     //Exiting from loop
				cout << "Thank you" << endl;
				return 0;
			default :
				cout << "Invalid command." << endl;
		}
	}
}
