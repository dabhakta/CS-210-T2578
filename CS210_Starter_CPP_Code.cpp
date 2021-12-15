#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

// Calls the parameter named function from Python file
void CallProcedure(string pName)
{
	char *procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("CS210_Starter_PY_Code");
	PyErr_Print();	
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

// Calls a Python fuction with one parameter
int CallFuncOneParam(string proc, string param)
{
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char *paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210_Starter_PY_Code");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;

	return _PyLong_AsInt(presult);
}

// Validate an integer input
void validateInt(int& userInput) {

	while (!(cin >> userInput)) {
		cin.clear();
		cin.ignore(123, '\n');
		cout << "Enter a number option from the following:" << endl;
		cout << "1: Determine the number of times each individual item appears." << endl;
		cout << "2: Determine the frequency of a specific item." << endl;
		cout << "3: Display all items sold along with the quantitiy sold." << endl;
		cout << "4: Exit" << endl;
	}

}

// Get user input for program functions
void getUserInput(int& userInput) {

	cout << "Enter a number option from the following:" << endl;
	cout << "1: Determine the number of times each individual item appears." << endl;
	cout << "2: Determine the frequency of a specific item." << endl;
	cout << "3: Display all items sold along with the quantitiy sold." << endl;
	cout << "4: Exit" << endl;
	validateInt(userInput);
	while (userInput <= 0 && userInput > 4) {
		getUserInput(userInput);
	}

}

// Get user value for item to search in grocery list
void getUserValue(string& userVal) {
	cout << "Enter item:" << endl;
	while (!(cin >> userVal)) {
		cin.clear();
		cin.ignore(123, '\n');
		cout << "Enter item:" << endl;
	}

}

void main()
{
	// Variables
	int userInput = 0;
	ifstream inFS;
	string item;
	int quantity;

	// Execute program until user enters '4' to exit.
	while (userInput != 4) {

		getUserInput(userInput);
		string userVal;

		if (userInput == 1) { // User option 1
			CallProcedure("printItemCount");
		}
		else if (userInput == 2) { // User option 2
			getUserValue(userVal);
			cout << endl;
			cout << userVal << ": " << CallFuncOneParam("printCount", userVal) << endl;
			cout << endl;
		}
		else if (userInput == 3) { // User option 3
			CallFuncOneParam("createFile", "frequency.dat");
			inFS.open("frequency.dat");
			if (!inFS.is_open()) {
				cout << "Could not open frequency.dat file." << endl;
				break;
			}
			cout << endl;
			while (!inFS.eof()) {
				inFS >> item;
				inFS >> quantity;
				cout << item << " ";
				for (int i = 0; i < quantity; ++i) {
					cout << "*";
				}
				cout << endl;
			}
			cout << endl;
			inFS.close();
		}

	}

}