#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <utility>


typedef std::pair<long,long int> pr;

using namespace std;

//Two viewers have at least three movies in common and they have given the rating to each of the movies in the year “2001” and “2000”.
void criteria_1()
{
	string files[] = {"assignment/ratings_data_1.txt", "assignment/ratings_data_2.txt","assignment/ratings_data_3.txt", "assignment/ratings_data_4.txt"};
	unordered_map <long int, vector<int> > user_to_rated_movies;//stores the all the movies rated by corresponding customerId
	for(int f = 0; f < 2; f++)// reading only first two ratings while as system may crash for reading more file
	{
		ifstream ratings(files[f]);
		
		string line;
		string movie, user, rate, year;
		int movie_id;
		while(getline(ratings, line))
		{
			int n = line.length();
			if(line[n-1] == ':')
			{
				movie = line.substr(0, n - 1);
				movie_id = stoi(movie);
				continue;	
			}
			istringstream s(line);
			getline(s, user, ',');
			getline(s, rate, ',');
			getline(s, year, ',');
			if(year.substr(0,4) == "2000" || year.substr(0,4) == "2001")//reading only ratings given in the uaer 2000 and 2001
			user_to_rated_movies[stoi(user)].push_back(movie_id);
		}

		ratings.close();
	}
		ofstream movies_to_user_file("criteria_1_edges.txt", std::ios::app);

		unordered_map<long int, vector<int> > :: iterator itr;
		map<pr, int> lookup;// will keep track of pairs of nodes already added to the file
		itr = user_to_rated_movies.begin(); 
		while(itr != user_to_rated_movies.end())
		{
			auto i = itr;
			for(++i; i != user_to_rated_movies.end(); i++)
			{
				vector<int> temp(10);
				auto j = set_intersection(itr->second.begin(), itr->second.end(), i->second.begin(), i->second.end(), temp.begin());
				if(j - temp.begin() >= 3 && !lookup[{itr->first, i->first}] && !lookup[{i->first, itr->first}])
					{
						movies_to_user_file << itr->first << " "<< i->first<<endl;
						lookup[{itr->first, i->first}] = 1;
						lookup[{i->first, itr->first}] = 1;	
					}
			}
			itr++;
		}

		movies_to_user_file.close();
	
	
}

//Two viewers have at least five movies in common and they have given a full rating to the movie (i.e. 5) and the rating is given in the year “2005”
void criteria_2()
{
	string files[] = {"assignment/ratings_data_1.txt", "assignment/ratings_data_2.txt","assignment/ratings_data_3.txt", "assignment/ratings_data_4.txt"};
	unordered_map <long int, vector<int> > user_to_rated_movies;
	for(int f = 0; f < 4; f++)
	{
		ifstream ratings(files[f]);
		
		string line;
		string movie, user, rate, year;
		int movie_id;
		while(getline(ratings, line))
		{
			int n = line.length();
			if(line[n-1] == ':')
			{
				movie = line.substr(0, n - 1);
				movie_id = stoi(movie);
				continue;	
			}
			istringstream s(line);
			getline(s, user, ',');
			getline(s, rate, ',');
			getline(s, year, ',');
			if(rate == "5" && year.substr(0,4) == "2005")// reading the ratings that are given as 5 and given in the year 2005
			user_to_rated_movies[stoi(user)].push_back(movie_id);
		}

		ratings.close();
	}
		ofstream movies_to_user_file("criteria_2_edges.txt", std::ios::app);

		unordered_map<long int, vector<int> > :: iterator itr;
		map<pr, int> lookup;
		itr = user_to_rated_movies.begin(); 
		while(itr != user_to_rated_movies.end())
		{
			auto i = itr;
			for(++i; i != user_to_rated_movies.end(); i++)
			{
				vector<int> temp(10);
				auto j = set_intersection(itr->second.begin(), itr->second.end(), i->second.begin(), i->second.end(), temp.begin());
				if(j - temp.begin() >= 5 && !lookup[{itr->first, i->first}] && !lookup[{i->first, itr->first}])
					{
						movies_to_user_file << itr->first << " "<< i->first<<endl;
						lookup[{itr->first, i->first}] = 1;
						lookup[{i->first, itr->first}] = 1;	
					}
			}
			itr++;
		}

		movies_to_user_file.close();
	
	
}

//Two viewers have at least five movies in common and they have given ratings equal to or greater than 4 and the rating is given between years “2003” and “2005”.
void criteria_3()
{
	string files[] = {"assignment/ratings_data_1.txt", "assignment/ratings_data_2.txt","assignment/ratings_data_3.txt", "assignment/ratings_data_4.txt"};
	unordered_map <long int, vector<int> > user_to_rated_movies;
	for(int f = 0; f < 4; f++)
	{
		ifstream ratings(files[f]);
		
		string line;
		string movie, user, rate, year;
		int movie_id;
		while(getline(ratings, line))
		{
			int n = line.length();
			if(line[n-1] == ':')
			{
				movie = line.substr(0, n - 1);
				movie_id = stoi(movie);
				continue;	
			}
			istringstream s(line);
			getline(s, user, ',');
			getline(s, rate, ',');
			getline(s, year, ',');
			//reading the ratings that are given as 4 or 5 and in the year 2003, 2004, 2005
			if((rate == "5" || rate == "4") && (year.substr(0,4) == "2004" || year.substr(0,4) == "2005" || year.substr(0,4) == "2003"))
			user_to_rated_movies[stoi(user)].push_back(movie_id);
		}
	
		ratings.close();
	}	
		ofstream movies_to_user_file("criteria_3_edges.txt", std::ios::app);

		unordered_map<long int, vector<int> > :: iterator itr;
		map<pr, int> lookup;
		itr = user_to_rated_movies.begin(); 
		while(itr != user_to_rated_movies.end())
		{
			auto i = itr;
			for(++i; i != user_to_rated_movies.end(); i++)
			{
				vector<int> temp(10);
				auto j = set_intersection(itr->second.begin(), itr->second.end(), i->second.begin(), i->second.end(), temp.begin());
				if(j - temp.begin() >= 5 && !lookup[{itr->first, i->first}] && !lookup[{i->first, itr->first}])
					{
						movies_to_user_file << itr->first << " "<< i->first<<endl;
						lookup[{itr->first, i->first}] = 1;
						lookup[{i->first, itr->first}] = 1;	
					}
			}
			itr++;
		}

		movies_to_user_file.close();
	
	
}