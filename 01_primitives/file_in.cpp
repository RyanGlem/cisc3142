// This file shows basic functions of reading in a CSV file using C++98
// Please add your name to your code! 
// Ryan Glemad
// 2/16/2022

/* Homework Objective: fix this program to match the requirements listed: 
  1. successfully reads all lines of the input file
  2. calculate the average price per brand, average price per category 
  3. writes to an output file
  4. for each unique year, list the count of skus and also print out the skus as a list i.e. 2000 (3): 111, 211, 311 and make a new line per year.

All programs must be able to compile in C++98 standard (the default version on Linux Machine). That means you cannot use the new features of C++11! :(
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <map>

using namespace std; 

int main() {

  // define variables
  string sku, brand, category, year, price;
  vector<int>vSKU;
  vector<string>vBrand;
  vector<string>vCategory;
  vector<int>vYear;
  vector<float>vPrice;

  ofstream out_stream;
  ifstream in_stream;
  in_stream.open("data.csv"); //opening the file.

  if (!in_stream.fail()) { //if the file is open

    string line;

    while (getline(in_stream, sku, ',')) { //while the end of file is NOT reached
     stringstream ssku(sku); 
     int iSKU;
     ssku >> iSKU;
     vSKU.push_back(iSKU);

     getline(in_stream, brand, ',');
     vBrand.push_back(brand);

     getline(in_stream, category, ',');
     vCategory.push_back(category);

     getline(in_stream, year, ','); 
     stringstream syear(year);
     int iYear;
     syear >> iYear;
     vYear.push_back(iYear);

     getline(in_stream, price); 
     stringstream sprice(price);
     float fPrice;
     sprice >> fPrice;
     vPrice.push_back(fPrice);
    }
    in_stream.close(); //closing the file in_stream <

   } else {
    out_stream << "Unable to open file"; 
   }

    // Using maps as dictionary, we can dynamically store the price of each catgory, their total price, and the SKUs for each year as key value pairs
    // that avoid duplicates

    // Stores brand and total price
    map <string, float> branding;

    // Stores category and total price
    map <string, float> categories;

    // Stores the year and a string of the respective SKUs
    map <int, string> SKUYears;

    // The count of each category, brand, and year
    map <string, int> count;

    out_stream.open ("music.txt");

    for (int i = 1; i < vSKU.size(); i++) {

      // Summing each unique entry price for the dictionary
      branding [vBrand[i]] += vPrice[i];
      categories [vCategory[i]] += vPrice[i];

      // Counting the number of each unique entry
      count [vBrand[i]] += 1;
      count [vCategory[i]] += 1;
      count [to_string (vYear[i])] += 1;

      // Adding each SKU entry as a string and appending white space for formatting
      SKUYears [vYear[i]] += to_string (vSKU[i]).append(" ");
    }
    
    // Iterates through the map of SKUYears and displays the number of SKUs, the list of SKUs, and the year
    for (map<int, string>::iterator it=SKUYears.begin(); it!=SKUYears.end(); ++it) {
      out_stream << it->first << "\t" << "(" << count[to_string (it->first)] << ")"<< " " << it->second << '\n';
    }
    
    out_stream << "Average price of ABC brands: " << '$' << branding ["ABC"] / count["ABC"] << '\n';
    out_stream << "Average price of XYZ brands: " << '$' << branding ["XYZ"] / count["XYZ"] << '\n';
    out_stream << "Average price of A category: " << '$' << categories ["A"] / count["A"] << '\n';
    out_stream << "Average price of B category: " << '$' << categories ["B"] / count["B"] << '\n';
    out_stream << "Average price of C category: " << '$' << categories ["C"] / count["C"] << '\n';
    out_stream.close();

    return 0;
}
