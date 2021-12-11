# Introduction
This is a project for UCR CS170 Introduction to AI. This program uses cross validation and the nearest neighbor algorithm to determine the best features to classify samples. The features can be searched for using forwards selection search or backwards elimination search.  

The program takes an input of either 0 or 1 from the user to determine whether to use forwards selection search or backwards elimination search. The program will then read the file specified by the string filename and parse the data from that file to run the search on.


The following are the results of running searches on different datasets:

# Forward Selection Search

This is a bar graph showing the accuracy versus the amount of features added for data in Ver_2_CS170_Fall_2021_Small_data__93.txt. Features were added in this order: {1, 5, 6, 8, 10, 7, 2, 3, 9, 4}  
![alt text](https://github.com/Chhurio/K-Nearest-Neighbor-classifier/blob/main/images/smallforward.png "Accuracies for forward selection on small dataset")

