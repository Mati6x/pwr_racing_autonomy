#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>

struct Point {
    int id;
    float x;
    float y;
    std::vector<int> merged_ids;
    bool deleted;
    bool in_rim;
};

float distance_squared(const Point& p1, const Point& p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

float cross_product(const Point& p1, const Point& p2, const Point& p3) {
    return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

void print_merged_points(std::vector<Point>& points, size_t n) {
    for (size_t i = n; i < points.size(); i++){
        if (points[i].deleted) continue;
        std::cout << "CONE " << points[i].id << std::fixed << std::setprecision(3) << " " << points[i].x << " " << points[i].y << " [" << std::defaultfloat << std::setprecision(6);
        for (size_t j = 0; j < points[i].merged_ids.size(); j++){
            std::cout << points[i].merged_ids[j];
            if (j != points[i].merged_ids.size() - 1) std::cout << ",";
        }
        std::cout << "]" << std::endl;
    }
}

// Function to merge points that are within a certain distance m
void merge_points(std::vector<Point>& points, size_t max_id, float m) {
    int new_ids = max_id + 1;
    for (size_t i = 0; i < points.size(); i++){
        for (size_t j = i+1; j < points.size(); j++){
            if (points[i].deleted || points[j].deleted) continue;
            // Check if the distance between points i and j is less than m
            if (distance_squared(points[i], points[j]) < m * m){
                Point new_point;
                new_point.id = new_ids++;
                // Update x and y coordinates of the new point to the midpoint of all the points in the cluster
                float sum_x = 0;
                float sum_y = 0;
                float count = 0;
                
                sum_x += points[i].x * points[i].merged_ids.size();
                sum_y += points[i].y * points[i].merged_ids.size();
                count += points[i].merged_ids.size();
                
                sum_x += points[j].x * points[j].merged_ids.size();
                sum_y += points[j].y * points[j].merged_ids.size();
                count += points[j].merged_ids.size();

                new_point.x = sum_x / count;
                new_point.y = sum_y / count;

                //combine the merged_ids of points i and j into new_point
                new_point.merged_ids.insert(new_point.merged_ids.end(), points[i].merged_ids.begin(), points[i].merged_ids.end());

                new_point.merged_ids.insert(new_point.merged_ids.end(), points[j].merged_ids.begin(), points[j].merged_ids.end());

                new_point.deleted = false;
                new_point.in_rim = false;

                points.push_back(new_point);

                points[i].deleted = true;
                points[j].deleted = true;
            }
        }
    }
}

void print_rim(std::vector<int>& rim, float rim_length) {
    std::cout << "ENCLOSURE " << std::fixed << std::setprecision(3) << rim_length << std::defaultfloat << std::setprecision(6) << " [";
    for (size_t i = 0; i < rim.size(); i++) {
        std::cout << rim[i];
        if (i != rim.size() - 1) std::cout << ",";
    }
    std::cout << "]" << std::endl;
}

// Function to find the rim of the merged points
float find_rim(std::vector<Point> points, std::vector<int>& rim) {
    // Find the starting point
    float max_distance_squared = 0;
    size_t start_point_index = 0;
    for(size_t i = 1; i < points.size(); i++){
        if(points[i].deleted) continue;
        if(distance_squared(points[i], points[0]) > max_distance_squared){
            max_distance_squared = distance_squared(points[i], points[0]);
            start_point_index = i;
        }
    }
    // go trough the points to find the rim
    float rim_length = 0;
    size_t current_rim_point_index = start_point_index;
    do{
        std::vector<int> candidates_indexes;
        for(size_t i = 0; i < points.size(); i++){
            if(points[i].deleted || points[i].in_rim || i == current_rim_point_index){
                continue;
            }
            bool is_candidate = true;
            for(size_t j = 0; j < points.size(); j++){
                if(points[j].deleted || points[j].in_rim || i == j ){
                    continue;
                }
                float result = cross_product(points[current_rim_point_index], points[i], points[j]);
                if( result < 0){
                    is_candidate = false;
                    break;
                }
            }
            if(is_candidate){
                candidates_indexes.push_back(i);
            }
        }
        float max_distance_squared = 0;
        size_t max_distance_index = 0;
        for(size_t i = 0; i < candidates_indexes.size(); i++){
            float distance_squared_var = distance_squared(points[candidates_indexes[i]], points[current_rim_point_index]);
            if(distance_squared_var > max_distance_squared){
                max_distance_squared = distance_squared_var;
                max_distance_index = i;
            }
        }
        
        current_rim_point_index = candidates_indexes[max_distance_index];
        for(size_t i = 0; i < candidates_indexes.size(); i++){
            rim.push_back(points[candidates_indexes[i]].id);
        }
        rim_length += sqrt(max_distance_squared);
        for(size_t i = 0; i < candidates_indexes.size(); i++){
            points[candidates_indexes[i]].in_rim = true;
        }
        
    }while(current_rim_point_index != start_point_index);

    return rim_length;
}

int main(int argc, char *argv[]){
    std::string input_file;
    if(argc > 2){
        std::cerr << "Too many arguments!" << std::endl;
        return 1;
    }else if(argc == 1){
        std::cerr << "No input file provided! using example_input.txt" << std::endl;
        input_file = "example_input.txt";
    }else{
        input_file = argv[1];
    }
    // Open the input file
    std::ifstream f(input_file);

    // Check if the file was opened successfully
    if (!f.is_open()) {
        std::cerr << "Error opening the file!";
        return 1;
    }

    // Read the number of points and the minimal distance from the file
    size_t n = 0;
    f >> n;
    float m = 0;
    f >> m;

    if (n <=1 ){
        std::cerr << "Not enough points to do antything!" << std::endl;
        return 1;
    }

    int max_id = 0;
    std::vector<Point> points(n);

    // Read the points from the file
    for (size_t i = 0; i < n; i++) {
        f >> points[i].id >> points[i].x >> points[i].y;
        if (points[i].id > max_id) {
            max_id = points[i].id;
        }
        points[i].deleted = false;
        points[i].in_rim = false;
        points[i].merged_ids.push_back(points[i].id);
    }

    merge_points(points, max_id, m);
    print_merged_points(points, n);

    int deleted_points_count = 0;
    for (size_t i = 0; i < points.size(); i++) {
        if (points[i].deleted) {
            deleted_points_count++;
        }
    }
    int remaining_points_count = points.size() - deleted_points_count;
    if (remaining_points_count < 3) {
        std::cerr << "Not enough points to find the rim!" << std::endl;
        return 1;
    }

    std::vector<int> rim;
    float rim_length = find_rim(points, rim);
    print_rim(rim, rim_length);

    return 0;
}