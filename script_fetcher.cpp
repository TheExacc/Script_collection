#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <curl/curl.h>
#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;

// Callback function for libcurl to write fetched data into a std::string.
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    std::string* s = static_cast<std::string*>(userp);
    size_t totalSize = size * nmemb;
    s->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

// Utility function to convert a string to lowercase.
std::string toLower(const std::string &s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

//split a string into words based on whitespace.
std::vector<std::string> splitWords(const std::string& s) {
    std::vector<std::string> words;
    std::istringstream iss(s);
    std::string word;
    while (iss >> word) {
        words.push_back(word);
    }
    return words;
}

// compute a matching score by checking if each query word is contained in the entire description.
int computeScore(const std::string& query, const std::string& description) {
    int score = 0;
    std::vector<std::string> queryWords = splitWords(query);
    std::string lowerDesc = toLower(description);
    
    for (const auto& qword : queryWords) {
        std::string lowerQ = toLower(qword);
        if (lowerDesc.find(lowerQ) != std::string::npos) {
            score++;
        }
    }
    return score;
}

int main() {
    // Ask the user for a query.
    std::cout << "Enter your query (e.g., sys info, backup, cleanup): ";
    std::string query;
    std::getline(std::cin, query);
    query = toLower(query);

    // url of the bash_scripts.json file on my gitHub.
    std::string url = "https://raw.githubusercontent.com/TheExacc/Script_collection/refs/heads/master/bash_scripts.json";

    CURL* curl = curl_easy_init();
    std::string readBuffer;

    if (curl) {
        // libcurl options setting.
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); 
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "Failed to fetch JSON: " << curl_easy_strerror(res) << std::endl;
            curl_easy_cleanup(curl);
            return 1;
        }
        curl_easy_cleanup(curl);
    } else {
        std::cerr << "Error initializing libcurl" << std::endl;
        return 1;
    }

    try {
        
        auto jsonData = json::parse(readBuffer);

        int bestScore = 0;
        std::vector<std::pair<std::string, json>> bestMatches;

        // Iterate over entryes
        for (auto& [key, value] : jsonData.items()) {
            std::string description = value["description"];
            int score = computeScore(query, description);

            //clear previous best matches  when the score is higher
            if (score > bestScore) {
                bestScore = score;
                bestMatches.clear();
                bestMatches.push_back({key, value});
            } else if (score == bestScore && score > 0) {
                bestMatches.push_back({key, value});
            }
        }

        if (bestScore > 0 && !bestMatches.empty()) {
            std::cout << "\nBest matching script(s):\n";
            for (const auto& match : bestMatches) {
                std::cout << "\nKey: " << match.first << "\n";
                std::cout << "Description: " << match.second["description"] << "\n";
                std::cout << "Script:\n" << match.second["script"] << "\n";
            }
        } else {
            std::cout << "\nNo matching scripts found for your query." << std::endl;
        }
    } catch (json::parse_error &e) {
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
