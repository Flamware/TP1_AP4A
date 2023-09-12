#include <iostream>
#include <fstream>
#include <string>
#include <map>

class Server {
public:
    Server() {
        // Constructeur par défaut
    }

    ~Server() {
        // Destructeur
        closeAllFiles();
    }

    // Fonction pour recevoir des données des capteurs
    void receiveDataFromSensor(const std::string& sensorName, const std::string& data) {
        // Stocker les données dans la console
        consoleWrite(sensorName, data);

        // Stocker les données dans le fichier de logs du capteur
        fileWrite(sensorName, data);
    }

private:
    std::map<std::string, std::ofstream> logFiles;

    // Fonction pour écrire les données dans la console
    void consoleWrite(const std::string& sensorName, const std::string& data) {
        std::cout << "Received data from sensor '" << sensorName << "': " << data << std::endl;
    }

    // Fonction pour écrire les données dans le fichier de logs du capteur
    void fileWrite(const std::string& sensorName, const std::string& data) {
        if (logFiles.find(sensorName) == logFiles.end()) {
            // Si le fichier de logs pour ce capteur n'existe pas, le créer
            logFiles[sensorName].open(sensorName + "_log.txt");
        }

        // Écrire les données dans le fichier de logs correspondant au capteur
        if (logFiles[sensorName].is_open()) {
            logFiles[sensorName] << data << std::endl;
        }
    }

    // Fonction pour fermer tous les fichiers de logs
    void closeAllFiles() {
        for (auto& pair : logFiles) {
            if (pair.second.is_open()) {
                pair.second.close();
            }
        }
    }
};


