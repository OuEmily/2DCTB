#include <cement/cement.hpp>

int main() {
    double width = 500.0;
    double height = 400.0;
    int numPolygons = 6000;
    int minPoints = 8;
    int maxPoints = 15;
    int rows = 7;
    int cols = 7;
    double minDistance = 2;
    int extraIterations = 3;

    CementStructureGenerator generator(width, height, numPolygons, minPoints, maxPoints, rows, cols, minDistance, extraIterations);
    Polygons cementStructure = generator.generateCementStructure();

    generator.visualizeModel(cementStructure, width, height);

    // Указываем путь для сохранения файла SVG
    std::string svgFilePath = "./exit/cement_structure.svg";

    // Сохраняем изображение в векторном формате SVG
    generator.saveImageAsSVG(cementStructure, width, height, svgFilePath);

    return 0;
}




