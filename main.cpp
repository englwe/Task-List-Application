#include "main.h"
void main(void)
{
	bool bQuit = false;
	char cInput;
	std::string sInput;

	TaskList Tasks;
	std::string menu = "1) Display all tasks\n2) Add a task\n3) Delete a task\n4) Mark task complete\n5) Check Due Tasks\n6) Sort\nq) Quit";
	while (1)
	{	
		std::cout << "\nTask List Viewer" << std::endl;
		std::cout << menu << std::endl;
		std::cin >> cInput;
		std::cin.ignore(); // clear buffer
		switch (cInput)
		{
		case '1':
		{
			Tasks.DisplayAllTasks();
		}
		break;
		case '2':
		{
			Tasks.AddTask();
		}
		break;
		case '3':
		{
			Tasks.DeleteTask();
		}
		break;
		case '4':
		{
			Tasks.MarkTaskComplete();
		}
		break;
		case '5':
		{
			Tasks.CheckDueDate();
		}
		break;
		case '6':
		{
			Tasks.SortDueDate();
		}
		break;
		case 'q':
		case 'Q':
		{
			bQuit = true;
			std::cout << "Quitting application..." << std::endl;
		}
		break;
		default:
		{
			std::cout << "Invalid input" << std::endl;
		}
		break;
		}
		if (bQuit)
			break;
	}
}
