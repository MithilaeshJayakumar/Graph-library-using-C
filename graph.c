#include<stdio.h>//Required Header files
#include<stdlib.h>
#include<string.h>
#include "graph.h"

#define MAX_LENGTH 50

int row =0;//Initializing all variables 
int column =0;
int size = 0;
int traversed[MAX_VERTICES],walker[MAX_VERTICES],flag = 0, count = 0;

Graph *graph_initialize()//Function to create and initialize the graph structure
	{
		Graph *NewGraph = malloc(sizeof(Graph));//Dynamic creation of Graph structure
		if(NewGraph == NULL)
			{
				return NULL;//Return NULL if graph not created successfully
			}
		else
			{
				for(row = 0; row < MAX_VERTICES; row++)//Initializing each component of adj_matrix[][] and visited[] with -1
					{
						NewGraph->visited[row] = -1;
						for(column = 0; column < MAX_VERTICES; column++)
							{
								NewGraph->adj_matrix[row][column] = -1;
							}
					}
				return NewGraph;//Return pointer to graph on successful creation
			}
	}

int graph_add_vertex(Graph *graph, int v1)// Functio to add a vertex
	{
		if(graph != NULL)//Check if the graph is not NULL
			{
				if(v1 >= 0 && v1 < MAX_VERTICES)//Check if the vertex is a legal vertex
					{
						if(graph->visited[v1] == 1)//Check if the vertex is already present in graph
							{
								return 0;
							}
						else//Add the vertex if not already present in graph
							{
								graph->visited[v1] = 1;
								return 0;
							}
					}
				else//Return -1 if not a legal vertex
					{
						return -1;
					}
			}
		else//Return -1 if graph is NULL
			{
				return -1;
			}
	}

int graph_contains_vertex(Graph *graph, int v1)//Function to check if a vertex is present in graph
	{
		if(graph != NULL)//Check if the graph is not NULL
			{
				if(v1 >= 0 && v1 < MAX_VERTICES)//Check if the vertex is a legal vertex
					{
						if(graph->visited[v1] == 1)//Return 1 if vertex already in graph
							{
								return 1;
							}
						else//Return 0 if vertex not in graph
							{
								return 0;
							}
					}
				else//Return 0 if vertex not legal vertex
					{
						return 0;
					}
			}
		else//Return 0 if graph is NULL
			{
				return 0;
			}
	}

int graph_remove_vertex(Graph *graph, int v1)//Function to remove a vertex
	{
		if(graph != NULL)//Check if the graph is not NULL
			{
				if(v1 >=0 && v1 < MAX_VERTICES && graph->visited[v1]== 1)//Check if the vertex is a legal vertex and is present in graph
					{
						for(row = 0; row < MAX_VERTICES; row++)//Remove all the edges associated with the vertex
							{
								graph->adj_matrix[v1][row] = -1;
								graph->adj_matrix[row][v1] = -1;
							}
						graph->visited[v1]= -1;//Remove the vertex and return 0
						return 0;
					}
				else
					{
						if(graph->visited[v1] == -1)//Return 0 if vertex already not in graph
							{
								return 0;
							}
						return -1;//Return -1 vertex not legal vertex
					}
			}
		else
			{
				return -1;//Return -1 if graph is NULL
			}
	}

int graph_add_edge(Graph *graph, int v1, int v2, int wt)//Function to add edge between vertices
	{
		if(graph != NULL)//Check if graph is not NULL
			{
				if(graph->visited[v1] == 1 && graph->visited[v2] == 1 && wt > 0)//Check if vertices are present and wt > 0
					{
						graph->adj_matrix[v1][v2] = wt;//Add or update the weight and return 0
						return 0;
					}
				else//Return -1 if vertices not in graph
					{
						return -1;
					}
			}
		else//Return -1 if graph is NULL
			{
				return -1;
			}
	}

int graph_contains_edge(Graph *graph, int v1, int v2)//Function to check if edge exist
	{
		if(graph != NULL)//Check if graph is not NULL
			{
				if(graph->visited[v1] == 1 && graph->visited[v2] == 1)//Check if vertices are present
					{
						if(graph->adj_matrix[v1][v2] > 0 )//Check if edge is present between vertices
							{
								return 1;//Return 1 if present
							}
					}
				else
					{
						return 0;//Return 0 if vertices or edge not present
					}
			}
		else
			{
				return 0;//Return 0 if graph is NULL
			}
	}

int graph_remove_edge(Graph *graph, int v1, int v2)//Function to remove edge
	{
		if(graph != NULL)//Check if graph is not NULL
			{
				if(graph->visited[v1] == 1 && graph->visited[v2]== 1)//Check if vertices are present
					{
						if(graph->adj_matrix[v1][v2]>0)//Check if edge is present
							{
								graph->adj_matrix[v1][v2]= -1;//Remove the edge and return 0
								return 0;
							}
						else//Return 0 if vertex present but no edge
							{
								return 0;
							}
					}
				else//Return -1 if vertex not present
					{
						return -1;
					}
			}
		else//Return -1 if graph is NULL
			{
				return -1;
			}
	}

int graph_num_vertices(Graph *graph)//Function to get number of vertices
	{
		if(graph != NULL)//Check if the graph is not NULL
			{
				int vertex_count = 0;//Initialize counter
				for(row =0; row<MAX_VERTICES; row++)
					{
						if(graph->visited[row]>0)//Check if a vertex exit and increment counter
							{
								vertex_count++;
							}
					}
				return vertex_count;// Return the counter
			}			
		else//Return -1 if graph not exist
			{
				return -1;
			}
	}

int graph_num_edges(Graph *graph)//Function to count the number of edges 
	{
		if(graph != NULL)//Check if graph is not NULL
			{
				int edge_count = 0;//Initialize the counter
				for(row = 0; row<MAX_VERTICES; row++)
					{
						for(column = 0; column<MAX_VERTICES; column++)
							{
								if(graph->adj_matrix[row][column]>0)//Check if an edge exist and increment counter
									{
										edge_count++;
									}
							}
					}
				return edge_count;//Return the counter
			}
		else//Return -1 if graph is NULL
			{
				return -1;
			}
	}

int graph_total_weight(Graph *graph)//Function to count total weights
	{
		if(graph != NULL)//Check if graph is not NULL
			{
				int sum_weight =0;//Initialize the counter
				for(row = 0; row<MAX_VERTICES; row++)
					{
						for(column=0; column<MAX_VERTICES; column++)
							{
								if(graph->adj_matrix[row][column]>0)//Check if a edge exist
									{
										sum_weight = sum_weight + graph->adj_matrix[row][column];//Add the weight of the edge to counter
									}
							}
					}
				return sum_weight;//Return the total weight
			}
		else//Return -1 if graph is NULL
			{
				return -1;
			}
	}

int graph_get_degree(Graph *graph, int v1)//Function to get the degree of vertex
	{
		if(graph != NULL)//Check if graph is not NULL
			{
				int degree_count = 0;//Initialize the counter
				if(graph->visited[v1] > 0)//Check if vertex exist
					{
						for(row =0; row<MAX_VERTICES; row++)
							{
								if(graph->adj_matrix[row][v1]>0)//Add edges row-wise for that vertex
									{
										degree_count++;
									}
							}
						for(column=0;column<MAX_VERTICES; column++)
							{
								if(graph->adj_matrix[v1][column]>0)//Add edges column-wise for that vertex
									{
										degree_count++;
									}
							}
						return degree_count;//Return the total degree
					}
				else
					{
						return -1;//Return -1 if vertex not exist
					}
			}
		else//Return -1 if graph not exist
			{
				return -1;
			}
	}

int graph_get_edge_weight(Graph *graph, int v1, int v2)//Function to get the edge between vertices
	{
		if(graph != NULL)//Check if graph is not NULL
			{
				if(graph->visited[v1] > 0 && graph->visited[v2] > 0)//Check if vertices exist
					{
						if(graph->adj_matrix[v1][v2] > 0)//Check if edge exist
							{
								return graph->adj_matrix[v1][v2];//Return the edge weight
							}
						else
							{
								return -1;//Return -1 if no edge
							}
					}
				else
					{
						return -1;//Return -1 if vertices not exist
					}
			}
		else
			{
				return -1;//Return -1 if graph is NULL
			}
	}

int graph_is_neighbor(Graph *graph, int v1, int v2)//Function to check if two vertices are neighbors
	{
		if(graph != NULL)//Check if graph is not NULL
			{
				if(graph->visited[v1] == 1 && graph->visited[v2]== 1)//Check if vertices exist
					{
						if(graph->adj_matrix[v1][v2]>0 || graph->adj_matrix[v2][v1]>0)//Check if edge exist in either direction 
							{
								return 1;//Return 1 if exist
							}
						else
							{
								return 0;//Return 0 if edge not present in either way
							}
					}
				else
					{
						return 0;//Return 0 if vertices not present
					}
			}
		else
			{
				return 0;//Return 0 if graph is NULL
			}
	}

int *graph_get_predecessors(Graph *graph, int v1)//Function to get predecessors of a vertex
	{
		size = 0;//Initialize variable for dynamic array size
		if(graph != NULL)//Check if graph is not NULL
			{
				if(graph->visited[v1] == 1)//Check if vertex exist
					{
						for(row = 0;row < MAX_VERTICES;row++)
							{
								if(graph->adj_matrix[row][v1] > 0)//Keep count of predecessors
									{
										size++;
									}
							}
						if(size != 0)//Check if predecessors exist
							{
								int *pred_array = (int *)malloc(sizeof(int)*(size + 1));//Dynamic creation of array with required size
								if(pred_array != NULL)//Check if array created
									{
										size = 0;//Reinitialize the size to loop through new array
										for(row = 0;row < MAX_VERTICES;row++)
											{
												if(graph->adj_matrix[row][v1] > 0)
													{
														pred_array[size] = row;//copy each predecessor vertex to new array through loop
														size++;
													}
											}
										pred_array[size] = -1;//Assign last index of new array to -1
										return pred_array;//Return pointer new array
									}
								else
									{
										return NULL;//Return NULL if error in dynamic creation
									}
							}
						else
							{
								return NULL;//Return NULL if no predecessors
							}
					}
				else
					{
						return NULL;//Return NULL if vertex not exist
					}
			}
		else
			{
				return NULL;//Return NULL if graph not exist
			}
	}

int *graph_get_successors(Graph *graph, int v1)//Function to get successors of vertex
	{
		size = 0;//Initialize variable for dynamic array size
		if(graph != NULL)//Check if graph is not NULL
			{
				if(graph->visited[v1] == 1)//Check if vertex exist
					{
						for(column = 0;column < MAX_VERTICES;column++)
							{
								if(graph->adj_matrix[v1][column] > 0)//Count the number of successors
									{
										size++;
									}
							}
						if(size != 0)//Check if successor exist
							{
								int *succ_array = (int *)malloc(sizeof(int)*(size + 1));//Dynamic array creation with size of successors count
								if(succ_array != NULL)//Check if array created
									{
										size = 0;//Reinitialize variable to loop and add successors
										for(column =0;column < MAX_VERTICES;column++)
											{
												if(graph->adj_matrix[v1][column] > 0)
													{
														succ_array[size] = column;//Add each successor to new array
														size++;
													}
											}
										succ_array[size] = -1;//Set last index of array to -1
										return succ_array;//Return pointer to new array
									}
								else
									{
										return NULL;//Return NULL if error in array creation
									}
							}
						else
							{
								return NULL;//Return NULL if no successors
							}
					}
				else
					{
						return NULL;//Return NULL if vertex not exist
					}
			}
		else
			{
				return NULL;//Return NULL if graph not exist
			}
	}

void graph_output_dot(Graph *graph, char *filename)//Function to generate dot file
	{
		if(graph != NULL)//Check if graph is not NULL
			{
				FILE *fp = NULL;//Initialize file pointer
				fp = fopen(filename,"w");//Open the file passed
				if(fp != NULL)//Check if no error in file handling
					{
						fputs("digraph {\n",fp);//Write the graph in the specified format to the file
						for(row = 0;row < MAX_VERTICES; row++)
							{
								if(graph->visited[row] > 0)
									{
										fprintf(fp,"%d\n",row);
										for(column = 0;column < MAX_VERTICES;column++)
											{
												if(graph->adj_matrix[row][column] > 0)
													{
														fprintf(fp,"%d -> %d [label = %d]\n",row,column,graph->adj_matrix[row][column]);
													}
											}
									}
							}
						fputs("}",fp);
						fclose(fp);//Close the opened file
					}
				else//Return if any error in file handling
					{
						return;
					}
			}
		else//Return if graph not exist
			{
				return;
			}
	}

int graph_save_file(Graph *graph, char *filename)//Function to save graph as file
	{
		if(graph != NULL)//Check if graph is not NULL
			{
				int flag = 0;
				FILE *fp = NULL;//Initialize the file pointer
				fp = fopen(filename,"w");//Open the specified file
				if(fp != NULL)//Check if no errors in file handling
					{
						for(row = 0;row < MAX_VERTICES; row++)//Logic to write the graph to file in specified format
							{
								if(graph->visited[row] > 0)
									{
										flag = 0;
										for(column = 0;column < MAX_VERTICES;column++)
											{
												if(graph->adj_matrix[row][column] > 0)
													{
														fprintf(fp,"%d,%d,%d\n",row,column,graph->adj_matrix[row][column]);
														flag++;
													}
											}
										if(flag == 0)
											{
												fprintf(fp,"%d\n",row);
											}
									}
							}							
						fclose(fp);//Close the file opened
						return 0;//Return 0 if success
					}
				else
					{
						return -1;//Return -1 if any error in file handling
					}
			}
		else
			{
				return -1;//Return -1 if graph not exist
			}
	}	

int graph_load_file(Graph *graph, char *filename)//Function to load graph from file
	{
			if(graph != NULL)//Check if graph is not NULL
				{
					FILE *fp = NULL;//Initialize the file pointer
					fp = fopen(filename,"r");//Open the specified file
					if(fp != NULL)//Check if no error in file handling
						{
							char string[MAX_LENGTH];//Initialize the variables
							int result,v1,v2,wt;
							while(fgets(string,MAX_LENGTH,fp)!= NULL) //Loop until there is content to read in file
								{
									char temp[MAX_LENGTH];
									strcpy(temp,string);//Tokenize the read content and add it to graph as vertex and edges
									if(strlen(string) == 6)//Logic to add vertices and edges 
										{
											char *token = strtok(temp, ","); 
											v1 = atoi(token);
											result = graph_add_vertex(graph,v1);
											if(result != 0)//Return -1 if error in adding vertex v1
												{
													return -1;
												}
											token = strtok(NULL, ",");
											v2 = atoi(token);
											result = graph_add_vertex(graph,v2);
											if(result != 0)//Return -1 if error in adding vertex v2
												{
													return -1;
												}
											token = strtok(NULL, ",");
											wt = atoi(token);
											result = graph_add_edge(graph,v1,v2,wt);
											if(result != 0)//Return -1 if error in adding wt
												{
													return -1;
												}
										}
									else if(strlen(string) == 2)//Logic to add just vertex if no edge
										{
											v1 = atoi(string);
											result = graph_add_vertex(graph,v1);
											if(result != 0)//Return -1 if error in adding vertex
												{
													return -1;
												}
										}
									else
										{
											return -1;
										}										 
								}
									fclose(fp);//Close file pointer
									return 0;//Return 0 if successful
						}
					else
						{
							return -1;//Return -1 on any file handling error
						}
				}
			else
				{
					return -1;//Return -1 if graph not exist
				}
	}

void graph_print(Graph *graph)//Function to print graph
	{
		if(graph != NULL)//Check if graph is not NULL
			{//Logic to print the graph
				printf("Vertices present in the graph\n\n");
				for(row = 0;row < MAX_VERTICES;row++)
					{
						if(graph->visited[row] > 0)
							{
								printf("%d\t",row);
							}
					}
				printf("\n\nMatrix representation of edges and weights between vertices\n\n");
				for(row = 0;row < MAX_VERTICES;row++)
					{
						if(graph->visited[row] > 0)
							{
								printf("\t%d",row);
							}
					}
				printf("\n");
				for(row = 0;row < MAX_VERTICES;row++)
					{
						if(graph->visited[row] > 0)
							{
								printf("%d\t",row);
								for(column = 0;column < MAX_VERTICES;column++)
									{
										if(graph->adj_matrix[row][column] > 0 && (graph->visited[row] > 0 || graph->visited[column] > 0))
											{
												printf("%d\t",graph->adj_matrix[row][column]);
											}
										else
											{
												if(graph->visited[column] > 0)
													{
														printf("0\t");
													}
											}
									}
							}
						if(graph->visited[row] > 0)
							{
								printf("\n");
							}
					}	
			}
		else//Return if graph is NULL
			{
				return;
			}
	}

void breadth_first_search(Graph *graph ,int v1);//Function declaration for Breadth First Search

int graph_has_path(Graph *graph, int v1, int v2)//Function to check if path exists between vertices
	{
		int present = 0;//Initialize the variable
		if(graph != NULL)//Check if graph is not NULL
			{
				if(graph->visited[v1] > 0 && graph->visited[v2] > 0)//Check if vertices exist
					{
						for(row = 0; row < MAX_VERTICES ; row++)
							{
								traversed[row] = -1;//Initialize temporary array values to -1
								walker[row] = -1;
							}
						flag = 0;
						count = 0;
						traversed[count]= v1;
						breadth_first_search(graph, v1);//Call breadth first search function
						for(row = 0; row < MAX_VERTICES; row++) 
							{
								if(traversed[row]== v2)
									{
										present++;
										return 1;//Return 1 if path to specified vertex exist
									}
							}
						if(present == 0)
							{
								return 0;//Return 0 if no path exist
							}
					}
				else
					{
						return 0;//Return 0 if Verticres do not exist
					}
			}			
		else
			{
				return 0;//Return 0 if graph ios NULL
			}
	}

void breadth_first_search(Graph *graph ,int v1) //Function to traverse the graph using breadth first search
	{
		for(column = 0; column < MAX_VERTICES ; column++)
			{
				if(graph->adj_matrix[v1][column] > 0 && walker[column] != 1)
					{
						traversed[++count] = column;
					}
			}
		if(flag <= count) 
			{
				walker[traversed[flag]] = 1;
				if(traversed[++flag] != -1)
					{
						breadth_first_search(graph,traversed[flag]);
					}
			}
	}

