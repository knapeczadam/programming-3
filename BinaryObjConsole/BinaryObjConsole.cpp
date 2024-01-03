#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <iterator>

// Data structure to store OBJ data
struct OBJData {
    std::vector<std::string> comments; // let's assume that comments are situated at the beginning of the file
    std::vector<std::string> vertices;
    std::vector<std::string> vertexNormals;
    std::vector<std::string> faces;
};

struct Vertex
{
    float x, y, z;
};

struct VertexNormal
{
    float x, y, z;
};

struct Face
{
    int v1, v2, v3;
};

// Function to read OBJ file
OBJData readOBJ(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    OBJData objData;
    std::string line;

    while (std::getline(file, line)) {
        if (line[0] == '#') {
            // ignore "#"
            objData.comments.push_back(line.substr(1));
        } else if (line.compare(0, 2, "v ") == 0) {
            // ignore "v "
            objData.vertices.push_back(line.substr(2));
        } else if (line.compare(0, 3, "vn ") == 0) {
            // ignore "vn "
            objData.vertexNormals.push_back(line.substr(3));
        } else if (line.compare(0, 2, "f ") == 0) {
            // ignore "f "
            objData.faces.push_back(line.substr(2));
        }
    }

    return objData;
}

// Function to write bOBJ file
void writeBOBJ(const OBJData& objData, const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + filename);
    }

    // Write comments
    // first write the number of comments
    int numComments = static_cast<int>(objData.comments.size());
    file.write(reinterpret_cast<const char*>(&numComments), sizeof(int));
    
    for (const auto& comment : objData.comments) {
        file << comment << '\n';
    }
    file.put(0x00);

    // Write vertices
    // first write the number of vertices
    int numVertices = static_cast<int>(objData.vertices.size());
    file.write(reinterpret_cast<const char*>(&numVertices), sizeof(int));
    for (const auto& vertex : objData.vertices) {
        Vertex v;
        std::istringstream iss(vertex);
        iss >> v.x >> v.y >> v.z;
        file.write(reinterpret_cast<const char*>(&v), sizeof(Vertex));
    }
    // file.put(0x00);

    // Write vertex normals
    // first write the number of vertex normals
    int numNormals = static_cast<int>(objData.vertexNormals.size());
    file.write(reinterpret_cast<const char*>(&numNormals), sizeof(int));
    for (const auto& normal : objData.vertexNormals) {
        VertexNormal vn;
        std::istringstream iss(normal);
        iss >> vn.x >> vn.y >> vn.z;
        file.write(reinterpret_cast<const char*>(&vn), sizeof(VertexNormal));
    }
    // file.put(0x00);

    // Write faces
    // first write the number of faces
    int numFaces = static_cast<int>(objData.faces.size());
    file.write(reinterpret_cast<const char*>(&numFaces), sizeof(int));
    for (const auto& face : objData.faces) {
        Face f;
        std::istringstream iss(face);
        iss >> f.v1 >> f.v2 >> f.v3;
        file.write(reinterpret_cast<const char*>(&f), sizeof(Face));
    }
    // file.put(0x00);
}

// Function to read bOBJ file
OBJData readBOBJ(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }

    OBJData objData;
    char marker;

    // Read comments
    int numComments;
    file.read(reinterpret_cast<char*>(&numComments), sizeof(int));
    while (file.get(marker) && marker != 0x00)
    {
        std::string comment;
        std::getline(file, comment);
        std::ostringstream oss;
        oss << "# " << comment;
        objData.comments.push_back(oss.str());
    }

    // Read vertices
    int numVertices;
    file.read(reinterpret_cast<char*>(&numVertices), sizeof(int));
    for (int i = 0; i < numVertices; ++i) {
        Vertex v;
        file.read(reinterpret_cast<char*>(&v), sizeof(Vertex));
        std::ostringstream oss;
        oss << std::scientific << std::setprecision(8);
        oss << "v " << v.x << " " << v.y << " " << v.z;
        objData.vertices.push_back(oss.str());
    }

    // Read vertex normals
    int numNormals;
    file.read(reinterpret_cast<char*>(&numNormals), sizeof(int));
    for (int i = 0; i < numNormals; ++i) {
        VertexNormal vn;
        file.read(reinterpret_cast<char*>(&vn), sizeof(VertexNormal));
        std::ostringstream oss;
        oss << std::scientific << std::setprecision(8);
        oss << "vn " << vn.x << " " << vn.y << " " << vn.z;
        objData.vertexNormals.push_back(oss.str());
    }

    // Read faces
    int numFaces;
    file.read(reinterpret_cast<char*>(&numFaces), sizeof(int));
    for (int i = 0; i < numFaces; ++i) {
        Face f;
        file.read(reinterpret_cast<char*>(&f), sizeof(Face));
        std::ostringstream oss;
        oss << "f " << f.v1 << " " << f.v2 << " " << f.v3;
        objData.faces.push_back(oss.str());
    }

    return objData;
}

// Function to write OBJ file
void writeOBJ(const OBJData& objData, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + filename);
    }

    // Write comments
    for (const auto& comment : objData.comments) {
        file << comment << '\n';
    }

    // Write vertices
    for (const auto& vertex : objData.vertices) {
        file << vertex << '\n';
    }

    // Write vertex normals
    for (const auto& normal : objData.vertexNormals) {
        file << normal << '\n';
    }

    // Write faces
    for (const auto& face : objData.faces) {
        file << face << '\n';
    }
}

int main() {
    try {
        // Read OBJ file
        OBJData objData = readOBJ("input.obj");

        // Write bOBJ file
        writeBOBJ(objData, "output.bobj");

        // Read bOBJ file
        OBJData bobjData = readBOBJ("output.bobj");

        // Write OBJ file from bOBJ data
        writeOBJ(bobjData, "output.obj");
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
