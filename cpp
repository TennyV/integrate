#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

/*
Description:
To call this function, simply pass the function name in Python that you wish to call.
Example:
callProcedure("printsomething");
Output:
Python will print on the screen: Hello from python!
Return:
None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("CS210_Starter_PY_Code");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
int x = callIntFunc("PrintMe","Test");
Output:
Python will print on the screen:
You sent me: Test
Return:
100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
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

/*
Description:
To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
int x = callIntFunc("doublevalue",5);
Return:
25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
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
		pValue = Py_BuildValue("(i)", param);
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

	return _PyLong_AsInt(presult);
}


int main()
{

	int num1;
	int choice;

	do {
		cout << "\n1: Display a Multiplication Table" << endl;
		cout << "2: Double a value" << endl;
		cout << "3: Exit" << endl;
		cout << "Enter your selection as a number 1, 2, or 3." << endl;
		cin >> choice;   // accepting user input
		switch (choice)   
		{
		case 1:
			CallProcedure("printsomething");   // utilizes function "printsomething"
			cin >> num1;  // receives user input
			cout << callIntFunc("MultiplicationTable", to_string(num1));   // utilizes function and takes user input
			break;
		case 2:
			CallProcedure("printsomething");   // utilizes function "print something"
			cin >> num1;
			cout << callIntFunc("DoubleValue", num1);  // utilizes function and takes userinput
			break;
		case 3:
			cout << "Exiting program" << endl;
			exit(3);
			return 3;  // exits program
		default:
			cout << "Invalid selection" << endl;   // telling the user they selected a wrong input
			break;
		}
	} while (choice > 0 || choice <= 3);   // validates user input
	return 0;
}

	

