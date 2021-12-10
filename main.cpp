#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <limits>
#include <math.h>
#include <time.h>
//function that returns the accuracy given a dataset, a set of features, and a feature to add
//uses nearest neighbor algorithm to calcualte accuracy
double knn_accuracy(std::vector<std::vector<double>>* data, std::vector<unsigned> current_set) {
	double accuracy;
	double total_correct = 0;
	double total_num_samples = data->size();

	for (unsigned hidden_sample_index = 0; hidden_sample_index < data->size(); hidden_sample_index++) {
		double actual_label = data->at(hidden_sample_index).at(0);
		double nearest_neighbor_distance = std::numeric_limits<double>::max();
		unsigned nearest_neighbor_location = 0;
		for (unsigned testing_sample_index = 0; testing_sample_index < data->size(); testing_sample_index++) {
			//dont compare sample to itself
			if (hidden_sample_index == testing_sample_index) {
				continue;
			}

			double squared_sums = 0;
			//adds up all squared sums for each feature we want to compare between the two samples
			for (unsigned feature_index = 0; feature_index < current_set.size(); feature_index++) {
				squared_sums += pow(data->at(hidden_sample_index).at(current_set.at(feature_index)) - data->at(testing_sample_index).at(current_set.at(feature_index)), 2);
			}

			double total_distance = sqrt(squared_sums);
			if (total_distance < nearest_neighbor_distance) {
				nearest_neighbor_location = testing_sample_index;
				nearest_neighbor_distance = total_distance;
			}
		}
		if (actual_label == data->at(nearest_neighbor_location).at(0)) {
			total_correct++;
		}

	}
	accuracy = total_correct / total_num_samples;
	return accuracy;
}

//helper function that checks if a feature has already been included in the current set
bool is_in(unsigned feature_to_add, std::vector<unsigned> current_set_of_features) {
	//if current set is empty return false
	if (!current_set_of_features.size()) {
		return false;
	}
	//iterates through each element in the set to see if the feature is in the set
	for (unsigned i = 0; i < current_set_of_features.size(); i++) {
		if (current_set_of_features.at(i) == feature_to_add) {
			return true;
		}
	}
	return false;
}

//searches for the best features in a data set to correctly label samples using forward selection
std::vector<unsigned> forward_selection_search(std::vector<std::vector<double>>* data) {
	std::vector<unsigned> best_set_of_features;
	double highest_accuracy = 0;
	std::vector<unsigned> current_set_of_features;
	std::cout << "Beginning Search." << std::endl;
	//since the maximum number of features we can have in a set of features is all of them,
	//the number of levels we will have in our tree is equal to the number of features
	//start at index 1 since index 0 contains the labels
	for (unsigned level_index = 1; level_index < data->at(0).size(); level_index++) {
		std::cout << "On level " << level_index << " of the search tree" << std::endl;
		unsigned feature_to_add_at_this_level = 0;
		
		std::cout << "Current set of features is {";
		for (unsigned i = 0; i < current_set_of_features.size(); i++) {
			if (i != current_set_of_features.size() - 1) {
				std::cout << current_set_of_features.at(i) << ", ";
			}
			else {
				std::cout << current_set_of_features.at(i);
			}
		}
		std::cout << "}"<< std::endl;

		double best_so_far_accuracy = 0;
		for (unsigned feature_index = 1; feature_index < data->at(0).size(); feature_index++) {
			//skip if feature is already in current set
			if (is_in(feature_index, current_set_of_features)) {
				continue;
			}

			std::vector<unsigned> current_set_with_new_feature = current_set_of_features;
			current_set_with_new_feature.push_back(feature_index);
			double accuracy = knn_accuracy(data, current_set_with_new_feature);
			std::cout << "If we add feature " << feature_index << " with accuracy becomes " << accuracy * 100 << "%" << std::endl;

			if (accuracy > best_so_far_accuracy) {
				best_so_far_accuracy = accuracy;
				feature_to_add_at_this_level = feature_index;
			}
		}
		std::cout << "On level " << level_index << ", added feature " << feature_to_add_at_this_level << " to current set" << std::endl;
		current_set_of_features.push_back(feature_to_add_at_this_level);
		if (best_so_far_accuracy > highest_accuracy) {
			best_set_of_features = current_set_of_features;
			highest_accuracy = best_so_far_accuracy;
		}
		else if (level_index != 1) {
			std::cout << "Warning: Accuracy has decreased! Continuing search in case of local maxima. ";
			std::cout << "Feature set {";
			for (unsigned i = 0; i < best_set_of_features.size(); i++) {
				if (i != best_set_of_features.size() - 1) {
					std::cout << best_set_of_features.at(i) << ", ";
				}
				else {
					std::cout << best_set_of_features.at(i);
				}
			}
			std::cout << "} is best with accuracy " << highest_accuracy * 100 << "%" << std::endl;
		}
	}
	std::cout << "Best set of features is {";
	for (unsigned i = 0; i < best_set_of_features.size(); i++) {
		if (i != best_set_of_features.size() - 1) {
			std::cout << best_set_of_features.at(i) << ", ";
		}
		else {
			std::cout << best_set_of_features.at(i);
		}
	}
	std::cout << "} with accuracy " << highest_accuracy * 100 << "%" << std::endl;
	return best_set_of_features;
}

//searches for the best features in a data set to correctly label samples using backwards elimination
std::vector<unsigned> backwards_elimination_search(std::vector<std::vector<double>>* data) {
	std::vector<unsigned> best_set_of_features;
	double highest_accuracy = 0;
	std::vector<unsigned> current_set_of_features;
	//initialize vector with all features
	for (unsigned i = 1; i < data->at(0).size(); i++) {
		current_set_of_features.push_back(i);
	}
	std::cout << "Beginning Search." << std::endl;
	//since the maximum number of features we can have in a set of features is all of them,
	//the number of levels we will have in our tree is equal to the number of features
	//start at index 1 since index 0 contains the labels
	for (unsigned level_index = 1; level_index < data->at(0).size(); level_index++) {
		std::cout << "On level " << level_index << " of the search tree" << std::endl;
		unsigned feature_to_remove_at_this_level = 0;

		std::cout << "Current set of features is {";
		for (unsigned i = 0; i < current_set_of_features.size(); i++) {
			if (i != current_set_of_features.size() - 1) {
				std::cout << current_set_of_features.at(i) << ", ";
			}
			else {
				std::cout << current_set_of_features.at(i);
			}
		}
		std::cout << "}" << std::endl;

		double best_so_far_accuracy = 0;
		for (unsigned feature_index = 1; feature_index < data->at(0).size(); feature_index++) {
			//skip if feature is already removed from current set
			if (!is_in(feature_index, current_set_of_features)) {
				continue;
			}

			std::vector<unsigned> current_set_without_feature = current_set_of_features;
			unsigned i = 0;
			for (std::vector<unsigned>::iterator it = current_set_without_feature.begin(); it != current_set_without_feature.end(); ++i, ++it) {
				if (current_set_without_feature.at(i) == feature_index) {
					current_set_without_feature.erase(it);
					break;
				}
				
			}
			double accuracy = knn_accuracy(data, current_set_without_feature);
			std::cout << "If we remove feature " << feature_index << " with accuracy becomes " << accuracy * 100 << "%" << std::endl;

			if (accuracy > best_so_far_accuracy) {
				best_so_far_accuracy = accuracy;
				feature_to_remove_at_this_level = feature_index;
			}
		}
		std::cout << "On level " << level_index << ", removed feature " << feature_to_remove_at_this_level << " from current set" << std::endl;
		unsigned i = 0;
		for (std::vector<unsigned>::iterator it = current_set_of_features.begin(); it != current_set_of_features.end(); ++i, ++it) {
			if (current_set_of_features.at(i) == feature_to_remove_at_this_level) {
				current_set_of_features.erase(it);
				break;
			}
		}
		if (best_so_far_accuracy > highest_accuracy) {
			best_set_of_features = current_set_of_features;
			highest_accuracy = best_so_far_accuracy;
		}
		else if (level_index != 1) {
			std::cout << "Warning: Accuracy has decreased! Continuing search in case of local maxima. ";
			std::cout << "Feature set {";
			for (unsigned i = 0; i < best_set_of_features.size(); i++) {
				if (i != best_set_of_features.size() - 1) {
					std::cout << best_set_of_features.at(i) << ", ";
				}
				else {
					std::cout << best_set_of_features.at(i);
				}
			}
			std::cout << "} is best with accuracy " << highest_accuracy * 100 << "%" << std::endl;
		}
	}
	std::cout << "Best set of features is {";
	for (unsigned i = 0; i < best_set_of_features.size(); i++) {
		if (i != best_set_of_features.size() - 1) {
			std::cout << best_set_of_features.at(i) << ", ";
		}
		else {
			std::cout << best_set_of_features.at(i);
		}
	}
	std::cout << "} with accuracy " << highest_accuracy * 100 << "%" << std::endl;
	return best_set_of_features;
}

int main() {
	clock_t tStart = clock();
	std::string filename = "Ver_2_CS170_Fall_2021_LARGE_data__29.txt";
	std::ifstream input;
	std::vector<std::vector<double>> data;

	input.open(filename);
	if (!input.is_open()) {
		return 1;
	}

	double temp;
	//references used for this parsing: 
	//https://stackoverflow.com/questions/3263323/c-read-from-istream-until-newline-but-not-whitespace
	//https://stackoverflow.com/questions/6283632/how-to-know-if-the-next-character-is-eof-in-c
	while (!input.eof()) {
		std::vector<double> newSample;
		while ((input.peek() != '\n') && (input >> temp)) {
			//read all values for a certain sample
			newSample.push_back(temp);
		}
		input.ignore();
		//add sample to data vector
		if (!input.eof()) {
			data.push_back(newSample);
		}
	}

	//testing to make sure all data is parsed
	/*for(unsigned sample_index = 0; sample_index < data.size(); sample_index++) {
		std::cout << "At sample " << sample_index << ": ";
		for (unsigned feature_index = 0; feature_index < data.at(sample_index).size(); feature_index++) {
			std::cout << data.at(sample_index).at(feature_index) << " ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
	}*/

	while (true) {
		std::cout << "Select a search algorithm(input '0' for forward selection search, input '1' for backwards elimination search):";
		int selection;
		std::cin >> selection;
		if (selection == 0) {
			forward_selection_search(&data);
			break;
		}
		else if (selection == 1) {
			backwards_elimination_search(&data);
			break;
		}
		std::cout << "Invalid input!" << std::endl;
	}
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	
	return 0;
}