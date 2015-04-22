/* This file serves for creating different functions
 */

#include "Functions.h"


// BUG ked v stringu nie je cislo tak vrati nejaku blbostCURRENT
Vector<int> StringToNumbers(String s) {
    Vector<int> numbers;
    String temp = "";
    bool bText = false, bNumber = false;
    int j = 0;
    
    for (int i = 0; i < s.Length(); i++) 
    {
	char c = s[i];
	
	if (isdigit(c)) 
	{
	    temp += c;
	    bNumber = true;
	    bText = false;
	}
	else if (c)
	{
	    bText = true;
	    
	    if (bNumber) 
	    {
		Variant v(temp);
		numbers.Push(v.GetInt());						// write down the number from the temp string into number
	    }
	    
	    j++;
	    bNumber = false;
	}
    }
    
    return numbers;
}

// CHECK creates an array of numbers from string, new array row for each row in the string (row separator \n)
Vector<Vector <int> > StringToNumbersVector(String s)
{
    Vector<Vector <int> > numbers;
    String sTemp;
    int j = 0;
    
    Vector<String> subStrings = s.Split('\n');
    
    for (int i = 0; i < subStrings.Size(); i++)
    {
	// check if it contains atleast one number
	if (subStrings[i].Contains('0') || subStrings[i].Contains('1') || subStrings[i].Contains('2') || subStrings[i].Contains('3') || subStrings[i].Contains('4') || subStrings[i].Contains('5') || subStrings[i].Contains('6')|| subStrings[i].Contains('7') || subStrings[i].Contains('8') || subStrings[i].Contains('9'))
	{
	    Vector<int> n = StringToNumbers(subStrings[i]);
	    numbers.Push(n);
	}
    }
    /*for (int i = 0; i < s.Length(); i++)
    {
	int row = 0;
	
	if (s[i] == '\n')
	{
	    sTemp = s.Substring(j, i-j);
	    numbers[row] = StringToNumbers(sTemp);
	    row++;
	    j = i+1;
	}
    }*/
    
    return numbers;
}