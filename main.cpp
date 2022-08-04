
#include <bits/stdc++.h>
#include <algorithm>
#define up 8 //Used for total paths 
// always put some large number greater than total paths
#define down 7 // total nodes in path
// put some large number than nodes in total path
using namespace std;



int arr[up][down]; // Used to store all paths
int arr2[up][down]; // Used to compare paths
int flag = 0; // used for finding total path in each unit
  

// utility function for printing
// the found path in graph


void printpath(vector<int>& path)
{
  flag++;
  
  static int j = 0;
  
	int size = path.size();
	for (int i = 0; i < size; i++)
  {
    
    cout << path[i] << " ";
    
    
      arr2[j][i] =  path[i];
      if(i != size-1)
      {
        arr[j][i] = path[i+1]*10+path[i];
      }
    

  }
		
  
  j++;
  
	cout << endl;
}

// utility function to check if current
// vertex is already present in path
int isNotVisited(int x, vector<int>& path)
{
	int size = path.size();
	for (int i = 0; i < size; i++)
		if (path[i] == x)
			return 0;
	return 1;
}

// utility function for finding paths in graph
// from source to destination
void findpaths(vector<vector<int> >&g, int src,
								int dst, int v)
{
	// create a queue which stores
	// the paths
	queue<vector<int> > q;

	// path vector to store the current path
	vector<int> path;
	path.push_back(src);
	q.push(path);
	while (!q.empty()) {
		path = q.front();
		q.pop();
		int last = path[path.size() - 1];

		// if last vertex is the desired destination
		// then print the path
		if (last == dst)
			printpath(path);	

		// traverse to all the nodes connected to
		// current vertex and push new path to queue
		for (int i = 0; i < g[last].size(); i++) {
			if (isNotVisited(g[last][i], path)) {
				vector<int> newpath(path);
				newpath.push_back(g[last][i]);
				q.push(newpath);
			}
		}
	}
}

struct Pair
{
    int min;
    int max;
};
 
struct Pair getMinMax(int arr[], int n)
{
    struct Pair minmax;    
    int i;
     
    // If there is only one element
    // then return it as min and max both
    if (n == 1)
    {
        minmax.max = arr[0];
        minmax.min = arr[0];    
        return minmax;
    }
     
    // If there are more than one elements,
    // then initialize min and max
    if (arr[0] > arr[1])
    {
        minmax.max = arr[0];
        minmax.min = arr[1];
    }
    else
    {
        minmax.max = arr[1];
        minmax.min = arr[0];
    }
     
    for(i = 2; i < n; i++)
    {
        if (arr[i] > minmax.max)    
            minmax.max = arr[i];
             
        else if (arr[i] < minmax.min)    
            minmax.min = arr[i];
    }
    return minmax;
}

// function to represent graph (Adjacency List)
void representGraph(vector<vector<int> >&g, int v){
  for(int i=0;i<v;i++){
      cout<<i<<"--> ";
      for(int j=0;j<g[i].size();j++){
          cout<<g[i][j]<<" ";
      }
      cout<<endl;
  }
}
// driver program
int main()
{

  cout << "\n\n\t\t\t\tWELCOME TO TRAFFIC CONTROLLER \n\n";
	vector<vector<int> > g;
	// number of vertices
	int v = 5;
	g.resize(5);

	// construct a graph
	g[0].push_back(3);
	g[0].push_back(1);
	g[0].push_back(2);
	g[1].push_back(3);
	g[2].push_back(0);
	g[2].push_back(1);
  g[3].push_back(4);
  g[4].push_back(3);

  representGraph(g,v);
   

  for(int i = 0 ; i < up ; i++)
  {
    for(int j = 0; j < down ; j++)
    {
      arr[i][j] = -1;
      arr2[i][j] = -1;
    }
  }

	int src , dst; //entering source and dest
  cout << "Enter source of first unit : ";
  cin >> src;
  cout << "Enter destination of first unit : ";
  cin >> dst;
	cout << "path from src " << src
		<< " to dst " << dst << " are \n";

    

	// function for finding the paths
	findpaths(g, src, dst, v);

  int one = flag; // Total paths in one unit

   cout << "Enter source of first unit : ";
  cin >> src;
  cout << "Enter destination of first unit : ";
  cin >> dst; //entering second source and dest
	cout << "path from src " << src
		<< " to dst " << dst << " are \n";

	// function for finding the paths
	findpaths(g, src, dst, v);

  int two = flag - one; // Total paths in another unit
  int num = one * two; 
// Now comparing each path with another unit path
  
int overlap[up+down] = {0};


int k = 0;


   for (int i=0;i<one;i++)
        {
            for (int j=one;j<one+two;j++)
            {
              for(int a = 0 ; a < down ; a++)
              {
                for(int b = 0 ; b < down ; b++)
                {
                  if (arr[i][a]==arr[j][b] && arr[i][a] != -1)
                {
                    overlap[k] = overlap[k] + 1;
                }

                }

              }
              k++;
                
            }
        }

  /*  for( int i = 0 ; i < num ; i++)
    {
      cout << overlap[i] << " " ;
    } */
    
    struct Pair minmax = getMinMax(overlap, num);
     cout << endl;
    cout << "Minimum overlap is "
         << minmax.min  << " in following cases\n" << endl;

         int fake[up+down];
         for(int i = 0 ; i < (up+down) ; i++)
         {
           fake[i]= -1;
         }
         int l = 0;

         for(int i = 0 ; i < num ; i++)
         {
           if(overlap[i]==minmax.min)
           {
             fake[l++]= i;

           }
         }
         int m = 0;
         int bestpath[10]={0};
         
         // Printing paths with least overlap

         while(fake[m] != -1)
         {
           int a = fake[m] / two;
           int b = fake[m] % two;
           
           b = one + b;
           //cout << a << " " << b << endl;
           
           cout << "Path of one unit : ";
           for(int i = 0 ; i < down ; i++)
           {
             
             if(arr2[a][i] != -1)
             {
               cout << arr2[a][i] << " ";
               bestpath[m]=bestpath[m]+1;

             }
           }
           cout << endl;

            cout << "Path of another unit : ";
           for(int i = 0 ; i < down ; i++)
           {
             
             if(arr2[b][i] != -1)
             {
               cout << arr2[b][i] << " ";
               bestpath[m]=bestpath[m]+1;

             }
            
           }
            m++;
           cout << endl;
           cout << endl;
         }

         // Printing best path among least overlap path

           struct Pair minimum = getMinMax(bestpath, m);

           int fake1[10];
         for(int i = 0 ; i < 10 ; i++)
         {
           fake1[i]= -1;
         }
         int l1 = 0;

           for(int i = 0 ; i < 10 ; i++)
         {
           if(bestpath[i]==minimum.min)
           {
             fake1[l1++]= i;

           }
         }

         int m1=0;
         cout << "Best path among this is/are : \n\n";

          while(fake1[m1] != -1)
         {
           int a = fake[fake1[m1]] / two;
           int b = fake[fake1[m1]] % two;
           
           b = one + b;
           //cout << a << " " << b << endl;
           
           cout << "Path of one unit : ";
           for(int i = 0 ; i < down ; i++)
           {
             
             if(arr2[a][i] != -1)
             {
               cout << arr2[a][i] << " ";
               //bestpath[m]=bestpath[m]+1;

             }
           }
           cout << endl;

            cout << "Path of another unit : ";
           for(int i = 0 ; i < down ; i++)
           {
             
             if(arr2[b][i] != -1)
             {
               cout << arr2[b][i] << " ";
              // bestpath[m]=bestpath[m]+1;

             }
             
           }
           m1++;
           cout << endl;
           cout << endl;
         }


    


	return 0;
}
