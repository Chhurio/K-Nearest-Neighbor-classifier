# Introduction
This is a project for UCR CS170 Introduction to AI. This program uses cross validation and the nearest neighbor algorithm to determine the best features to classify samples. The features can be searched for using forwards selection search or backwards elimination search.  

The program takes an input of either 0 or 1 from the user to determine whether to use forwards selection search or backwards elimination search. The program will then read the file specified by the string filename and parse the data from that file to run the search on.


The following are the results of running searches on different datasets:

# Forward Selection Search

This is a bar graph showing the accuracy versus the amount of features added for data in Ver_2_CS170_Fall_2021_Small_data__93.txt. Features were added in this order: {1, 5, 6, 8, 10, 7, 2, 3, 9, 4}. Highest accuracy was set {1, 5} with accuracy 96.8%.   
![alt text](https://github.com/Chhurio/K-Nearest-Neighbor-classifier/blob/main/images/smallforward.png "Accuracies for forward selection on small dataset")

This is a bar graph showing the accuracy as features get added in the forward selection search for the Ver_2_CS170_Fall_2021_LARGE_data__29.txt file. Note: since the actual number of features was too large to include all of them in the graph and the fact that accuracy only decreased past two features {46, 10}, the features added after those two are counted in multiples of 5 to save space. Highest accuracy was set {46, 10} with accuracy 97.5%.  
![alt text](https://github.com/Chhurio/K-Nearest-Neighbor-classifier/blob/main/images/largeforward.PNG "Accuracies for forward selection on large dataset")

# Backward Elimination Search

This is a bar graph showing the accuracy versus the amount of features removed for data in Ver_2_CS170_Fall_2021_Small_data__93.txt. Features were removed in this order: {4, 9, 7, 10, 6, 3, 2, 8, 1, 5}. Highest accuracy was set {1, 5} with accuracy 96.8%.  
![alt text](https://github.com/Chhurio/K-Nearest-Neighbor-classifier/blob/main/images/smallbackward.png "Accuracies for backward elimination on small dataset")

This is a bar graph showing the accuracy as features get removed in the backward elimination search for the Ver_2_CS170_Fall_2021_LARGE_data__29.txt file. Highest accuracy was set {} with accuracy 85.45%. Note: This strange output is due to useful features like feature 10 getting removed from the dataset early on which made overall accuracy of the solution much lower. I only put the features removed in multiples of 5 because the graph would been too big otherwise and none of the sets searched had an accuracy higher than the one found in forward selection(set {46, 10} with accuracy 97.5%).  
![alt text](https://github.com/Chhurio/K-Nearest-Neighbor-classifier/blob/main/images/largebackward.png "Accuracies for backward elimination on large dataset")
