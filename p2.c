#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

 
int main() {

    FILE * fp; 
    fp = fopen("networkGraph.txt", "r");

    //******** BEGIN CREATE MATRIX **********

    char line[100];
    int numberOfNodes = atoi(fgets(line, 100, fp));
    int matrix[numberOfNodes][numberOfNodes];
    
    // Initialize the matrix with INT_MAX
    for (int i = 0; i < numberOfNodes; i++) {
        for (int j = 0; j < numberOfNodes; j++) {
            matrix[i][j] = INT_MAX;
        }
    }

    while(fgets(line, 100, fp) > 0){
        int first, second, cost;
        int count = 0;

        // Extract the first token
        char * token = strtok(line, ",");
        // loop through the string to extract all other tokens
        while( token != NULL ) {

            if(count == 0){
                first = atoi(token);
            }else if(count == 1){
                second = atoi(token);
            }else if (count == 2){
                cost = atoi(token);
            }else{
                printf("invalid input: %s", line);
                return -1;
            }
            token = strtok(NULL, ",");
            count++;
        }

        matrix[first-1][second-1] = cost;
        matrix[second-1][first-1] = cost;
    }

    //******** END CREATE MATRIX **********


    //________ BEGIN Dijkstra/Link state _________

    int distances[numberOfNodes];
    bool visited[numberOfNodes]; 

    for (int i = 0; i < numberOfNodes; i++) {
        distances[i] = INT_MAX;
        visited[i] = false;
    }

    // printf("\n");

    int source = 0;
    int newSource = 0;
    visited[0] = true;
    distances[0] = 0;
    int min = INT_MAX;
    printf("Source = %d\n", source+1);
    for(int i=0; i<numberOfNodes-1; i++){

        for(int j=0; j<numberOfNodes; j++){

            if(matrix[source][j] < INT_MAX && visited[j] == false){
                
                if(matrix[source][j] + distances[source] < distances[j]){

                    if(distances[j] == INT_MAX){
                        printf("Updating distance vector of Node %d, New = %d, Old = infinity\n", j+1, matrix[source][j] + distances[source]);
                    }
                    else{
                        printf("Updating distance vector of Node %d, New = %d, Old = %d\n", j+1, matrix[source][j] + distances[source], distances[j]);
                    }
                    
                    distances[j] = matrix[source][j] + distances[source];
                }

                if (distances[j] < min){
                    min = distances[j];
                    newSource = j;
                }
            }

            if(distances[j] < min && visited[j] == false){
                min = distances[j];
                newSource = j;
            }     
        }

        visited[newSource] = true;
        source = newSource;
        min = INT_MAX;

        printf("\nNext node = %d\n", source+1);
    }
    printf("\n");

    printf("The final distances are:\n");
    for(int i=0; i<numberOfNodes; i++){
        printf("1 -> %d = %d\n", i+1, distances[i]);
    }
}