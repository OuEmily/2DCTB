#include <cement/cement.hpp>


std::random_device rd; // Генератор случайных чисел
std::mt19937 gen(rd());
std::uniform_real_distribution<double> dist(0.0, 1.0);

CementStructureGenerator::CementStructureGenerator(double width, double height, int numPolygons, int minPoints, int maxPoints, int rows, int cols, double minDistance, int extraIterations)
    : width(width), height(height), numPolygons(numPolygons), minPoints(minPoints), maxPoints(maxPoints), rows(rows), cols(cols), minDistance(minDistance), extraIterations(extraIterations) {}

Polygons CementStructureGenerator::generateCementStructure() {
        Polygons polygons;

        for (int i = 0; i < numPolygons; i++) {
            double cellWidth = width / cols;
            double cellHeight = height / rows;

            double startX = dist(gen) * width;
            double startY = dist(gen) * height;

            double sizeFactor = 1.0 - static_cast<double>(i) / numPolygons;

            // Вычисляем координаты конечной точки
            double endX = std::min(startX + cellWidth * sizeFactor, width);
            double endY = std::min(startY + cellHeight * sizeFactor, height);

            // Создаем случайный многоугольник
            Polygon newPolygon = createRandomConvexPolygon(startX, startY, endX, endY, minPoints, maxPoints, sizeFactor);

            // Проверяем наличие пересечений и минимального расстояния
            if (checkMinDistance(polygons, newPolygon, minDistance)) {
                polygons.push_back(newPolygon);
            } else {
                // Если не удалось создать многоугольник, добавляем маленькую выпуклую оболочку в виде единственной вершины
                //polygons.push_back(Polygon{{Point{dist(gen) * (endX - startX) + startX, dist(gen) * (endY - startY) + startY}}});
            }
        }

        return polygons;
    }

void CementStructureGenerator::visualizeModel(const Polygons& polygons, double width, double height) {
    cv::Mat image(height, width, CV_8UC3, cv::Scalar(255, 255, 255));

    for (const auto& polygon : polygons) {
        // Исключаем точки-пустоты
        if (bg::is_empty(polygon)) {
            continue;
        }

        cv::Scalar color(dist(gen) * 255, dist(gen) * 255, dist(gen) * 255);
        for (size_t i = 0; i < polygon.outer().size(); i++) {
            const auto& p1 = polygon.outer()[i];
            const auto& p2 = polygon.outer()[(i + 1) % polygon.outer().size()];
            cv::line(image, cv::Point(p1.get<0>(), p1.get<1>()), cv::Point(p2.get<0>(), p2.get<1>()), color, 1);
        }
    }

    cv::imshow("Cement Structure", image);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

void CementStructureGenerator::saveImageAsSVG(const Polygons& polygons, double width, double height, const std::string& filename) {
    std::ofstream svgFile(filename);
    svgFile << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n";
    svgFile << "<svg width=\"" << width << "\" height=\"" << height << "\" xmlns=\"http://www.w3.org/2000/svg\">\n";

    for (const auto& polygon : polygons) {
        // Исключаем точки-пустоты
        if (bg::is_empty(polygon)) {
            continue;
        }

        svgFile << "  <polygon points=\"";
        for (const auto& point : polygon.outer()) {
            svgFile << point.get<0>() << "," << point.get<1>() << " ";
        }
        svgFile << "\" fill=\"none\" stroke=\"black\" stroke-width=\"1\" />\n";
    }

    svgFile << "</svg>\n";
}


bool CementStructureGenerator::checkIntersection(const Polygon& polygon1, const Polygon& polygon2) {
    // Проверяем наличие пересечений
    return bg::intersects(polygon1, polygon2);
}

bool CementStructureGenerator::checkMinDistance(const Polygons& existingPolygons, const Polygon& newPolygon, double minDistance) {
    for (const auto& existingPolygon : existingPolygons) {
        if (checkIntersection(existingPolygon, newPolygon)) {
            return false;
        }

        // Проверка минимального расстояния
        double distance = bg::distance(existingPolygon, newPolygon);
        if (distance < minDistance) {
            return false;
        }
    }
    return true;
}

Polygon CementStructureGenerator::createRandomConvexPolygon(double startX, double startY, double endX, double endY, int minPoints, int maxPoints, double sizeFactor) {
    Polygon polygon;

    // Создаем случайный невыпуклый многоугольник
    Polygon nonConvexPolygon;
    int numPoints = minPoints + dist(gen) * (maxPoints - minPoints);
    for (int i = 0; i < numPoints; i++) {
        double x = dist(gen) * (endX - startX) * sizeFactor + startX;
        double y = dist(gen) * (endY - startY) * sizeFactor + startY;
        bg::append(nonConvexPolygon.outer(), Point(x, y));
    }
    bg::correct(nonConvexPolygon);

    // Преобразуем в выпуклую оболочку
    bg::convex_hull(nonConvexPolygon, polygon);

    bg::correct(polygon);
    return polygon;
}

