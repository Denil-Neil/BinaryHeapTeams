#include <iostream>
#include <fstream>
#include "json.hpp"
#include "priorityqueue.h"

using namespace std;
using json = nlohmann::json;
// Function to read data from a file and return a JSON object
json readInstructionsFromFile(const char* fileName) {
    ifstream file(fileName);
    return json::parse(file);
}

// Function to process the data in a JSON object and update a priority queue
void processInstructions(const json& data, PriorityQueue& queue) {
    for (auto itr = data.begin(); itr != data.end() && itr.key() != "metadata"; itr++) {
        if (data[itr.key()]["operation"] == "insert") {
            double key = data[itr.key()]["key"];
            queue.insert(key);
        }
        else if (data[itr.key()]["operation"] == "removeMin") {
            queue.removeMin();
        }
    }
}

// Function to convert a priority queue to a JSON object
json priorityQueueToJson(const PriorityQueue& queue, const json& data) {
    json result = queue.JSON();
    result["metadata"]["maxHeapSize"] = data["metadata"]["maxHeapSize"];
    result["metadata"]["numOperations"] = data["metadata"]["numOperations"];
    return result;
}

int main(int argc, char** argv) {
    json data = readInstructionsFromFile(argv[1]);

    int numOperations = data["metadata"]["maxHeapSize"];
    PriorityQueue queue(numOperations);

    processInstructions(data, queue);

    json result = priorityQueueToJson(queue, data);
    cout << result.dump(2) << endl;

    return 1;
}

