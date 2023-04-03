#ifndef zeynepkurtulus_Kurtulus_Zeynep_HW7_PrintQueue_H
#define zeynepkurtulus_Kurtulus_Zeynep_HW7_PrintQueue_H


struct PrintJobNode 
{
	int PrintJobId, numberOfPages;
	PrintJobNode* next;
	PrintJobNode(int num, int nPages, PrintJobNode* ptr = NULL)
	{
		PrintJobId = num;
		numberOfPages = nPages;
		next = ptr;
	}
};

class HW7PrintQueue 
{
private:
	// These track the front and rear of the queue.
	PrintJobNode* front;
	PrintJobNode* rear;
	int currentSize; 
public:
	// Constructor.
	HW7PrintQueue();
	HW7PrintQueue(const HW7PrintQueue& rhs); // copy constructor
	// Member functions.
	int getCurrentSize() const; 
	HW7PrintQueue& operator=(const HW7PrintQueue& rhs); 
	void enqueue(int id, int numberOfPages);
	void dequeue(int& id, int & pages);
	bool isEmpty() const;
	//Destructor
	~HW7PrintQueue();
};
#endif
